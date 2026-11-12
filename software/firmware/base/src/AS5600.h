#include <stdint.h> 
#include <EEPROM.h>

#ifndef AS5600_H
#define AS5600_H


/**************************************
* I2C ADDR
**************************************/
#define AS5600_ADDR 0x36 // Address of the AS5600

#define STARTANGLE_REGISTER 0x01
#define STOPANGLE_REGISTER 0x03
#define RANGEANGLE_REGISTER 0x05
#define RAWANGLE_REGISTER 0x0C
#define ANGLE_REGISTER 0x0E
#define BURN_REGISTER 0xFF

/**************************************
* EEPROM ADDR 
**************************************/
#define EPROM_MIN_VALUE_ADDR 0x10;
#define EPROM_MAX_VALUE_ADDR 0x20;

class AS5600
{
private:
    uint8_t _chanel_index; //Chanel index, used only if using multiplexer
    bool _enable_multiplexing; //Indiciate that we should switch I2C chanel before calling AS5600
    void WriteEEPROM(int addr, int value);
    int ReadEEPROM(int addr);

public:
    void Multiplexing_SetEnable(bool enable);
    void Multiplexing_SetChanel(uint8_t chanel);
    int Calibrate_reloadCalibrationFromEPPROM();
    int Calibrate_SetMinValue(int value);
    int Calibrate_SetMaxValue(int value);
    int Calibrate_GetMinValue();
    int Calibrate_GetMaxValue();
    int Calibrate_ClearCalibration();
    int Calibrate_BurnCalibration();
    int GetRawAngle();
    int GetAngle();
};

#endif 
 