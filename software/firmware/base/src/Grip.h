#include <stdint.h> 
#include <EEPROM.h>

#ifndef GRIP_H
#define GRIP_H


/**************************************
* I2C ADDR
**************************************/
#define GRIP_ADDR 0x55 // Address of the GRIP

#define BTN_REGISTER 0x01
#define JOYCLIC_REGISTER 0x02
#define X_REGISTER 0x03
#define Y_REGISTER 0x04

/**************************************
* EEPROM ADDR 
**************************************/
#define EPROM_MIN_X_VALUE_ADDR 0x00;
#define EPROM_MIN_Y_VALUE_ADDR 0x02;
#define EPROM_MAX_X_VALUE_ADDR 0x04;
#define EPROM_MAX_Y_VALUE_ADDR 0x06;

class Grip
{
private:
    uint8_t _chanel_index; //Chanel index, used only if using multiplexer
    bool _enable_multiplexing; //Indiciate that we should switch I2C chanel before calling AS5600
    void WriteEEPROM(int addr, int value);
    int ReadEEPROM(int addr);

    int calibration_current_minX = -1;
    int calibration_current_maxX = -1;
    int calibration_current_minY = -1;
    int calibration_current_maxY = -1;


public:
    void Multiplexing_SetEnable(bool enable);
    void Multiplexing_SetChanel(uint8_t chanel);
    int IsConnectedToTheBase();
    int Calibrate_JOY_SetMinXValue(int value);
    int Calibrate_JOY_SetMinYValue(int value);
    int Calibrate_JOY_SetMaxXValue(int value);
    int Calibrate_JOY_SetMaxYValue(int value);
    int Calibrate_JOY_GetMinXValue();
    int Calibrate_JOY_GetMinYValue();
    int Calibrate_JOY_GetMaxXValue();
    int Calibrate_JOY_GetMaxYValue();
    void Calibrate_ClearCalibration();
    bool isMainButtonPress();
    bool isJoyButtonPress();
    int GetJoyXRawValue();
    int GetJoyYRawValue();
    int GetJoyXValue();
    int GetJoyYValue();
    int RecalibrateAngle(int angle, char axis);
};


#endif 