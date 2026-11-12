#include <Arduino.h>
#include <Wire.h>

#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H


#define TCA_ADDR 0x70    // Address of the TCA9548A multiplexer

class I2C_Manager
{
    private:
        static bool _wireIsRunning; //Indique si le Wire.Begin a été fait ou non
        static int _selectedChannel; //Indique la chanel actuellement selectionée


    public:
        static void StartI2C();
        static void SelectChannel(uint8_t channel); //Used to change chanel when multiplexing enabled
        static int Check_deviceIsConnected(int device_address);
        static int WriteRegister_int(int device_address, byte register_addr, unsigned int value);
        static int WriteRegister_byte(int device_address, byte register_addr, byte value);
        static int ReadRegister_int(int device_address, byte register_addr); 
        static int ReadRegister_byte(int device_address, byte register_addr); 
};



#endif