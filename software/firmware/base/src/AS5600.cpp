#include "AS5600.h"
#include "I2C_Manager.h"


/************************************************
 * PRIVATE FUNCTIONS
 ************************************************/
void AS5600::WriteEEPROM(int addr, int value)
{
    byte byte1 = value >> 8;
    byte byte2 = value & 0xFF;

    EEPROM.write(addr, byte1);
    EEPROM.write(addr + 1, byte2);
}

int AS5600::ReadEEPROM(int addr)
{

    byte byte1 = EEPROM.read(addr);
    byte byte2 = EEPROM.read(addr + 1);
    return (byte1 << 8) + byte2;
}


/************************************************
 * PUBLIC FUNCTIONS
 ************************************************/
void AS5600::Multiplexing_SetEnable(bool enable)
{
    _enable_multiplexing = enable;
    if (!enable)
    {
        _chanel_index = -1;
    }
}
void AS5600::Multiplexing_SetChanel(uint8_t chanel)
{
    if (chanel < 0)
    {
        _chanel_index = -1;
        return;
    }
    _chanel_index = chanel;
}

int AS5600::Calibrate_SetMinValue(int value)
{
    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    int error = I2C_Manager::WriteRegister_int(AS5600_ADDR, STARTANGLE_REGISTER, value);
    return error;
}

int AS5600::Calibrate_SetMaxValue(int value)
{
    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    int error = I2C_Manager::WriteRegister_int(AS5600_ADDR, STOPANGLE_REGISTER, value);
    return error;
}

int AS5600::Calibrate_GetMinValue()
{

    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    int angle = I2C_Manager::ReadRegister_int(AS5600_ADDR, STARTANGLE_REGISTER);
    return angle;
}

int AS5600::Calibrate_GetMaxValue()
{

    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }
    
    int angle = I2C_Manager::ReadRegister_int(AS5600_ADDR, STOPANGLE_REGISTER);
    return angle;
}

int AS5600::Calibrate_BurnCalibration(){

    //if (_enable_multiplexing)
    //{
    //    I2C_Manager::SelectChannel(_chanel_index);
    //}
    //0x80 indique qu'on burn les angles, sinon c'est 0x40 pour burn les config --> Ca semble ne fonctinné que 3 fois, il y a un compteur interne qui bloque les burn ...
    //int error = I2C_Manager::WriteRegister_byte(AS5600_ADDR, BURN_REGISTER, 0x80);
    
    //0 si ok, 1 si erreur
    //return error;

    /*---------------------------------------
     * V2 Ecrite dans la EPPROM pour sauvegarder les calibration car le burn sur le sensor ne marque que 3 fois visiblement
     ---------------------------------------*/

    //Ecriture de la valeur min
    int addr_min = EPROM_MIN_VALUE_ADDR;
    int addr_max = EPROM_MAX_VALUE_ADDR;

    addr_min += _chanel_index * 2;
    addr_max += _chanel_index * 2;

    int value_min = Calibrate_GetMinValue(); 
    int value_max = Calibrate_GetMaxValue(); 

    WriteEEPROM(addr_min, value_min);
    delay(5);

    WriteEEPROM(addr_max, value_max);
    delay(5);

    // Lecture en retour pour verifier que la donnee est bien ecrite
    if (ReadEEPROM(addr_min) != value_min || ReadEEPROM(addr_max) != value_max)
    {
        return 1;
    }

    return 0;

}

int AS5600::Calibrate_ClearCalibration()
{
    int error1 = Calibrate_SetMinValue(0);
    int error2 = Calibrate_SetMaxValue(4096);

    if(error1 != 0 || error2 != 0){
        return 1;
    }
}

int AS5600::GetRawAngle()
{
    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    int angle = I2C_Manager::ReadRegister_int(AS5600_ADDR, RAWANGLE_REGISTER);
    return angle;
}

int AS5600::GetAngle()
{
    if (_enable_multiplexing)
    {
        I2C_Manager::SelectChannel(_chanel_index);
    }

    int angle = I2C_Manager::ReadRegister_int(AS5600_ADDR, ANGLE_REGISTER);
    return angle;
}

//Cette fonction a été ajouter pour pouvoir sauver la calibratino sans utiliser le burn qui ne peut marcher que 3 fois
int AS5600::Calibrate_reloadCalibrationFromEPPROM()
{
    int addr_min_calibration = EPROM_MIN_VALUE_ADDR;
    int addr_max_calibration = EPROM_MAX_VALUE_ADDR;

    addr_min_calibration += _chanel_index * 2;
    addr_max_calibration += _chanel_index * 2;

    int calibration_min =  ReadEEPROM(addr_min_calibration);
    int calibration_max =  ReadEEPROM(addr_max_calibration);

    Calibrate_SetMinValue(calibration_min);
    Calibrate_SetMaxValue(calibration_max);

    return 0;

}

