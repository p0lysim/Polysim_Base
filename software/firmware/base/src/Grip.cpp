#include "Grip.h"
#include "I2C_Manager.h"

/************************************************
 * PRIVATE FUNCTIONS
 ************************************************/
void Grip::WriteEEPROM(int addr, int value)
{
    byte byte1 = value >> 8;
    byte byte2 = value & 0xFF;

    EEPROM.write(addr, byte1);
    EEPROM.write(addr + 1, byte2);
}

int Grip::ReadEEPROM(int addr)
{

    byte byte1 = EEPROM.read(addr);
    byte byte2 = EEPROM.read(addr + 1);
    return (byte1 << 8) + byte2;
}

/************************************************
 * PUBLIC FUNCTIONS
 ************************************************/
void Grip::Multiplexing_SetEnable(bool enable)
{
    _enable_multiplexing = enable;
    if (!enable)
    {
        _chanel_index = -1;
    }
}

void Grip::Multiplexing_SetChanel(uint8_t chanel)
{
    if (chanel < 0)
    {
        _chanel_index = -1;
        return;
    }
    _chanel_index = chanel;
}

/*--------------------------------------------------------------------------------
* Retourne des erreur du type :
* 0 : success
* 1 : data too long
* 2 : NACK pas de reponse sur l'adress
* 3 : NACK pas de retour sur la reception des donnees
* 4 : other error ex. timeout
--------------------------------------------------------------------------------*/
int Grip::IsConnectedToTheBase()
{

    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    int value = I2C_Manager::Check_deviceIsConnected(GRIP_ADDR);
    return value == 0;
}

int Grip::Calibrate_JOY_SetMinXValue(int value)
{
    int addr = EPROM_MIN_X_VALUE_ADDR;
    WriteEEPROM(addr, value);

    // Lecture en retour pour verifier que la donnee est bien ecrite
    delay(5);
    if (ReadEEPROM(addr) != value)
    {
        calibration_current_minX = value; // Stock dans la variable de class comme ca pas besoin de relir l'eeprom
        return 1;
    }

    return 0;
}

int Grip::Calibrate_JOY_SetMinYValue(int value)
{
    int addr = EPROM_MIN_Y_VALUE_ADDR;
    WriteEEPROM(addr, value);

    // Lecture en retour pour verifier que la donnee est bien ecrite
    delay(5);
    if (ReadEEPROM(addr) != value)
    {
        calibration_current_minY = value; // Stock dans la variable de class comme ca pas besoin de relir l'eeprom
        return 1;
    }

    return 0;
}

int Grip::Calibrate_JOY_SetMaxXValue(int value)
{
    int addr = EPROM_MAX_X_VALUE_ADDR;
    WriteEEPROM(addr, value);

    // Lecture en retour pour verifier que la donnee est bien ecrite
    delay(5);
    if (ReadEEPROM(addr) != value)
    {
        calibration_current_maxX = value; // Stock dans la variable de class comme ca pas besoin de relir l'eeprom
        return 1;
    }

    return 0;
}

int Grip::Calibrate_JOY_SetMaxYValue(int value)
{
    int addr = EPROM_MAX_Y_VALUE_ADDR;
    WriteEEPROM(addr, value);

    // Lecture en retour pour verifier que la donnee est bien ecrite
    delay(5);
    if (ReadEEPROM(addr) != value)
    {
        calibration_current_maxY = value; // Stock dans la variable de class comme ca pas besoin de relir l'eeprom
        return 1;
    }

    return 0;
}

int Grip::Calibrate_JOY_GetMinXValue()
{
    int addr = EPROM_MIN_X_VALUE_ADDR;
    return ReadEEPROM(addr);
}

int Grip::Calibrate_JOY_GetMinYValue()
{
    int addr = EPROM_MIN_Y_VALUE_ADDR;
    return ReadEEPROM(addr);
}

int Grip::Calibrate_JOY_GetMaxXValue()
{
    int addr = EPROM_MAX_X_VALUE_ADDR;
    return ReadEEPROM(addr);
}

int Grip::Calibrate_JOY_GetMaxYValue()
{
    int addr = EPROM_MAX_Y_VALUE_ADDR;
    return ReadEEPROM(addr);
}

void Grip::Calibrate_ClearCalibration()
{
    Calibrate_JOY_SetMinXValue(0);
    Calibrate_JOY_SetMinYValue(0);
    Calibrate_JOY_SetMaxXValue(1023);
    Calibrate_JOY_SetMaxYValue(1023);
}

bool Grip::isMainButtonPress()
{

    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    bool btn_main = I2C_Manager::ReadRegister_byte(GRIP_ADDR, BTN_REGISTER) > 100;
    return btn_main == 1;
}

bool Grip::isJoyButtonPress()
{

    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    int btn_main = I2C_Manager::ReadRegister_byte(GRIP_ADDR, JOYCLIC_REGISTER) < 100;
    return btn_main == 1;
}

int Grip::GetJoyXRawValue()
{

    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    int angle_X = I2C_Manager::ReadRegister_int(GRIP_ADDR, X_REGISTER);
    return angle_X;
}

int Grip::GetJoyYRawValue()
{

    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    int angle_Y = I2C_Manager::ReadRegister_int(GRIP_ADDR, Y_REGISTER);
    return angle_Y;
}

int Grip::GetJoyXValue()
{
    int angle_X  = RecalibrateAngle( GetJoyXRawValue(), 'X');
    return angle_X;
}

int Grip::GetJoyYValue()
{
    int angle_Y  = RecalibrateAngle( GetJoyYRawValue() , 'Y');
    return angle_Y;
}


int Grip::RecalibrateAngle(int angle, char axis)
{
    int range_original_start = 0;
    int range_original_end = 1023;
    int range_target_start = -1;
    int range_target_end = -1;

    /*---------------------------------------------------
    * Recupere les infos de calibration
    ---------------------------------------------------*/
    if (axis == 'X')
    {
        if (calibration_current_minX == -1)
        {
            calibration_current_minX = Calibrate_JOY_GetMinXValue();
        }
        if (calibration_current_maxX == -1)
        {
            calibration_current_maxX = Calibrate_JOY_GetMaxXValue();
        }

        range_target_start = calibration_current_minX;
        range_target_end = calibration_current_maxX;
    }
    else if (axis == 'Y')
    {
        if (calibration_current_minY == -1)
        {
            calibration_current_minY = Calibrate_JOY_GetMinYValue();
        }
        if (calibration_current_maxY == -1)
        {
            calibration_current_maxY = Calibrate_JOY_GetMaxYValue();
        }

        range_target_start = calibration_current_minY;
        range_target_end = calibration_current_maxY;
    }
    else
    {
        return angle;
    }

    /*---------------------------------------------------
    * Calcul le nouveau angle
    ---------------------------------------------------*/

    //Normalement, on ne devrait pas dépassé lesz valzeurs de calibration
    if(angle < range_target_start){
        return 0;
    }
    if(angle > range_original_end){
        return 1023;
    }

    //Verifie qu'on est pas hors limite
    if (range_target_end < range_target_start) {
        angle += 1023;  
    }

    angle %= 1023;

    if (angle < range_target_start) {
        angle += 1023;
    }

    //remap l'angle
    float angle_in_range = ((float)(angle - range_target_start) / (range_target_end - range_target_start)) * 1023.0;

    return (int)angle_in_range;

}
