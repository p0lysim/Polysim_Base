#include "SerialPortComManager.h"
#include "Version.h"

bool SerialPortComManager::_serialIsRunning = false;

Grip *SerialPortComManager::_grip = NULL;
AS5600 *SerialPortComManager::_X_encoder = NULL;
AS5600 *SerialPortComManager::_Y_encoder = NULL;

char SerialPortComManager::_current_command_ID = '_';
String SerialPortComManager::_current_command_NAME = "__";
int SerialPortComManager::_current_command_VALUE = 0;

void SerialPortComManager::StartSerial(Grip *grip, AS5600 *X_encoder, AS5600 *Y_encoder)
{
    _grip = grip;
    _X_encoder = X_encoder;
    _Y_encoder = Y_encoder;

    if (!_serialIsRunning)
    {
        Serial.begin(SERIAL_RATE);
        _serialIsRunning = true;
    }
}

/*********************************************************************************
 * Structure des commandes
 * [J | G | _ ] [COMMAND_NAME] [VALUE]
 *
 * [J | G | _ ]   = J = joystick , G = grip , indique le prefierique qu'on veut traiter, _ indique vide
 * [COMMAND_NAME] = 1 char qui indique la donnee qu'on veut traiter, _ indique vide
 * [VALUE]        = La valeur associé a la commande, ne pas laisser vide, mettre 0 par defaut
 *********************************************************************************/

void SerialPortComManager::ReadAndAnswerCommand()
{

    /*---------------------------------------
    * Read command if available
    ---------------------------------------*/
    String command = "";
    bool commandComplete = false;
    // TODO Impltement a timer to timeout

    while (Serial.available() && !commandComplete)
    {
        char inChar = (char)Serial.read();

        if (inChar == '\n')
        {
            commandComplete = true;
            break;
        }
        else
        {
            command += inChar;
        }
    }

    if (!commandComplete)
    {
        // TODO retourner une erreur sur la liaison serie
        // Serial.println("COMMAND INCOMPLETE");
        return;
    }

    bool command_readed = SplitCommand(command);

    /*---------------------------------------
    * Answer the command
    ---------------------------------------*/
    Serial.print("ACK ");
    Serial.print(_current_command_ID);
    Serial.print(" ");
    Serial.print(_current_command_NAME.c_str());
    Serial.print(" ");
    Serial.print(_current_command_VALUE);
    Serial.print(" ");

    /*---------------------------------------
    * Une erreur est survenue pendant le splitCommand
    ---------------------------------------*/
    if (!command_readed)
    {
        Serial.println("ERROR");
        return;
    }

    /*---------------------------------------
    * Commande pour le joystick
    ---------------------------------------*/
    if (_current_command_ID == 'J')
    {

        /*---------------------------------------
        * retourne l'angle X
        ---------------------------------------*/
        if (_current_command_NAME == "VE")
        {
            String version = __VERSION;
            Serial.println(version);
        }
        /*---------------------------------------
        * retourne l'angle X
        ---------------------------------------*/
        else if (_current_command_NAME == "AX")
        {
            int angle = _X_encoder->GetAngle();
            Serial.println(angle);
        }
        /*---------------------------------------
        * retourne l'angle Y
        ---------------------------------------*/
        else if (_current_command_NAME == "AY")
        {
            int angle = _Y_encoder->GetAngle();
            Serial.println(angle);
        }
        /*---------------------------------------
        * retourne l'angle raw X
        ---------------------------------------*/
        else if (_current_command_NAME == "RX")
        {
            int angle = _X_encoder->GetRawAngle();
            Serial.println(angle);
        }
        /*---------------------------------------
        * retourne l'angle raw Y
        ---------------------------------------*/
        else if (_current_command_NAME == "RY")
        {
            int angle = _Y_encoder->GetRawAngle();
            Serial.println(angle);
        }
        /*---------------------------------------
        * retourne la calibration min X
        ---------------------------------------*/
        else if (_current_command_NAME == "C1")
        {
            int calibration_min_X = _X_encoder->Calibrate_GetMinValue();
            Serial.println(calibration_min_X);
        }
        /*---------------------------------------
        * retourne la calibration min Y
        ---------------------------------------*/
        else if (_current_command_NAME == "C2")
        {
            int calibration_min_Y = _Y_encoder->Calibrate_GetMinValue();
            Serial.println(calibration_min_Y);
        }
        /*---------------------------------------
        * retourne la calibration max X
        ---------------------------------------*/
        else if (_current_command_NAME == "C3")
        {
            int calibration_max_X = _X_encoder->Calibrate_GetMaxValue();
            Serial.println(calibration_max_X);
        }
        /*---------------------------------------
        * retourne la calibration min Y
        ---------------------------------------*/
        else if (_current_command_NAME == "C4")
        {

            int calibration_max_Y = _Y_encoder->Calibrate_GetMaxValue();
            Serial.println(calibration_max_Y);
        }
        /*---------------------------------------
        * set calibration min X
        ---------------------------------------*/
        else if (_current_command_NAME == "C5")
        {
            int error = _X_encoder->Calibrate_SetMinValue(_current_command_VALUE);
            Serial.println(error);
        }
        /*---------------------------------------
        * set calibration min Y
        ---------------------------------------*/
        else if (_current_command_NAME == "C6")
        {
            int error = _Y_encoder->Calibrate_SetMinValue(_current_command_VALUE);
            Serial.println(error);
        }
        /*---------------------------------------
        * set calibration max X
        ---------------------------------------*/
        else if (_current_command_NAME == "C7")
        {
            int error = _X_encoder->Calibrate_SetMaxValue(_current_command_VALUE);
            Serial.println(error);
        }
        /*---------------------------------------
        * set calibration min Y
        ---------------------------------------*/
        else if (_current_command_NAME == "C8")
        {

            int error = _Y_encoder->Calibrate_SetMaxValue(_current_command_VALUE);
            Serial.println(error);
        }

        /*---------------------------------------
        * Clear la calibration X
        ---------------------------------------*/
        else if (_current_command_NAME == "CL")
        {

            int error1 = _X_encoder->Calibrate_ClearCalibration();
            int error2 = _Y_encoder->Calibrate_ClearCalibration();

            if (error1 != 0 || error2 != 0)
            {
                Serial.println("1");
            }
            else
            {
                Serial.println("0");
            }
        }
        /*---------------------------------------
        * Burn X calibration
        ---------------------------------------*/
        else if (_current_command_NAME == "BX")
        {
            int error = _X_encoder->Calibrate_BurnCalibration();
            Serial.println(error);
        }
        /*---------------------------------------
        * Burn Y calibration
        ---------------------------------------*/
        else if (_current_command_NAME == "BY")
        {
            int error = _Y_encoder->Calibrate_BurnCalibration();
            Serial.println(error);
        }

        /*---------------------------------------
        * AUCUNE REQUETE CORRESPONDANTE
        ---------------------------------------*/
        else
        {
            Serial.println("UNKNOW");
        }
    }
    /*---------------------------------------
    * Commande pour le GRIP
    ---------------------------------------*/
    if (_current_command_ID == 'G')
    {

        if (_current_command_NAME == "IC")
        {
            int connected = _grip->IsConnectedToTheBase();
            Serial.println(connected);
        }
        /*---------------------------------------
        * retourne l'angle RAW X
        ---------------------------------------*/
        else if (_current_command_NAME == "RX")
        {
            int angle = _grip->GetJoyXRawValue();
            Serial.println(angle);
        }
        /*---------------------------------------
        * retourne l'angle RAW Y
        ---------------------------------------*/
        else if (_current_command_NAME == "RY")
        {
            int angle = _grip->GetJoyYRawValue();
            Serial.println(angle);
        }
        /*---------------------------------------
        * retourne l'angle X
        ---------------------------------------*/
        else if (_current_command_NAME == "AX")
        {
            int angle = _grip->GetJoyXValue();
            Serial.println(angle);
        }
        /*---------------------------------------
        * retourne l'angle Y
        ---------------------------------------*/
        else if (_current_command_NAME == "AY")
        {
            int angle = _grip->GetJoyYValue();
            Serial.println(angle);
        }

        /*---------------------------------------
        * retourne l'etate du bouton principal
        ---------------------------------------*/
        else if (_current_command_NAME == "MB")
        {
            int press = _grip->isMainButtonPress();
            Serial.println(press);
        }
        /*---------------------------------------
        * retourne l'etate du bouton du stick
        ---------------------------------------*/
        else if (_current_command_NAME == "JB")
        {
            int press = _grip->isJoyButtonPress();
            Serial.println(press);
        }
        /*---------------------------------------
        * retourne la calibration min X
        ---------------------------------------*/
        else if (_current_command_NAME == "C1")
        {
            int calibration_min_X = _grip->Calibrate_JOY_GetMinXValue();
            Serial.println(calibration_min_X);
        }
        /*---------------------------------------
        * retourne la calibration min Y
        ---------------------------------------*/
        else if (_current_command_NAME == "C2")
        {
            int calibration_min_Y = _grip->Calibrate_JOY_GetMinYValue();
            Serial.println(calibration_min_Y);
        }
        /*---------------------------------------
        * retourne la calibration max X
        ---------------------------------------*/
        else if (_current_command_NAME == "C3")
        {
            int calibration_max_X = _grip->Calibrate_JOY_GetMaxXValue();
            Serial.println(calibration_max_X);
        }
        /*---------------------------------------
        * retourne la calibration min Y
        ---------------------------------------*/
        else if (_current_command_NAME == "C4")
        {

            int calibration_max_Y = _grip->Calibrate_JOY_GetMaxYValue();
            Serial.println(calibration_max_Y);
        }
        /*---------------------------------------
        * set calibration min X
        ---------------------------------------*/
        else if (_current_command_NAME == "C5")
        {
            int error = _grip->Calibrate_JOY_SetMinXValue(_current_command_VALUE);
            Serial.println(error);
        }
        /*---------------------------------------
        * set calibration min Y
        ---------------------------------------*/
        else if (_current_command_NAME == "C6")
        {
            int error = _grip->Calibrate_JOY_SetMinYValue(_current_command_VALUE);
            Serial.println(error);
        }
        /*---------------------------------------
        * set calibration max X
        ---------------------------------------*/
        else if (_current_command_NAME == "C7")
        {
            int error = _grip->Calibrate_JOY_SetMaxXValue(_current_command_VALUE);
            Serial.println(error);
        }
        /*---------------------------------------
        * set calibration min Y
        ---------------------------------------*/
        else if (_current_command_NAME == "C8")
        {

            int error = _grip->Calibrate_JOY_SetMaxYValue(_current_command_VALUE);
            Serial.println(error);
        }

        /*---------------------------------------
        * AUCUNE REQUETE CORRESPONDANTE
        ---------------------------------------*/
        else
        {
            Serial.println("UNKNOW");
        }
    }
}

/**********************************************************************
 * Recupere une commande complete sous forme de string et la split
 * pour remplir les variables de classe
 **********************************************************************/
bool SerialPortComManager::SplitCommand(String command)
{
    int command_length = command.length();

    if (command_length < 6)
    {
        _current_command_ID = '_';
        _current_command_NAME = "__";
        _current_command_VALUE = 0;
        return false;
    }

    _current_command_ID = command[0];
    _current_command_NAME[0] = command[2];
    _current_command_NAME[1] = command[3];

    char str_command_value[command_length - 5];
    int index = 0;

    for (int i = 5; i < command_length; i++)
    {
        str_command_value[index] = command[i];
        index++;
    }

    _current_command_VALUE = atoi(str_command_value);

    return true;
}