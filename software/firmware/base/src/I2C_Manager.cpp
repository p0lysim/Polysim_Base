#include "I2C_Manager.h"

// Initialisation des variables privés static, par defaut -1 indique que aucune chanel n'est selectionée
int I2C_Manager::_selectedChannel = -1;
bool I2C_Manager::_wireIsRunning = false;

/****************************************************************
 * public satic functions
 ****************************************************************/

void I2C_Manager::StartI2C()
{

    if (!_wireIsRunning)
    {
        Wire.begin();
        Wire.setWireTimeout(3000 , true /* reset_on_timeout */); //3000us = 3ms
        _wireIsRunning = true;
    }
}

void I2C_Manager::SelectChannel(uint8_t channel)
{
    // Si la channel selectionée est la meme que la precedente selectionné est que wire a été lancé alors on fait rien
    if (channel == _selectedChannel)
    {
        return;
    }

    StartI2C();
    Wire.beginTransmission(TCA_ADDR); // Start transmission to the TCA9548A
    Wire.write(1 << channel);         // Write the channel selection bitmask
    Wire.endTransmission();           // End transmission
    _selectedChannel = channel;
}

/*--------------------------------------------------------------------------------
* Retourne des erreur du type :
* 0 : success
* 1 : data too long
* 2 : NACK pas de reponse sur l'adress
* 3 : NACK pas de retour sur la reception des donnees
* 4 : other error ex. timeout
--------------------------------------------------------------------------------*/
int I2C_Manager::Check_deviceIsConnected(int device_address)
{
    StartI2C();
    Wire.beginTransmission(device_address); // Start transmission to AS5600 OR GRIP
    int error = Wire.endTransmission();     // End transmission
    return error;
}

int I2C_Manager::WriteRegister_int(int device_address, byte register_addr, unsigned int value)
{

    StartI2C();
    Wire.beginTransmission(device_address); // Start transmission to AS5600 OR GRIP
    Wire.write(register_addr);              // Send address of the MANG register
    Wire.write((byte)(value >> 8));         // Send upper byte of value
    Wire.write((byte)(value & 0xFF));       // Send lower byte of value
    int error = Wire.endTransmission();     // End transmission
    return error;
}

int I2C_Manager::WriteRegister_byte(int device_address, byte register_addr, byte value)
{

    StartI2C();
    Wire.beginTransmission(device_address); // Start transmission to AS5600 OR GRIP
    Wire.write(register_addr);              // Send address of the MANG register
    Wire.write(value);                      // Send value
    int error = Wire.endTransmission();     // End transmission
    return error;
}

int I2C_Manager::ReadRegister_int(int device_address, byte register_addr)
{
    StartI2C();
    Wire.beginTransmission(device_address); // Start transmission to AS5600 or GRIP
    Wire.write(register_addr);              // Send address of the MANG register
    Wire.endTransmission(false);            // End transmission (false to keep connection active)

    Wire.requestFrom(device_address, 2); // Request 2 bytes of data from the AS5600

    if (Wire.available() == 2)
    {
        int value = (Wire.read() << 8) | Wire.read(); // Read the 2 bytes and combine them into an integer
        return value;
    }
    else
    {

        return -1; // Return -1 in case of read error
    }
}

int I2C_Manager::ReadRegister_byte(int device_address, byte register_addr)
{
    StartI2C();
    Wire.beginTransmission(device_address); // Start transmission to the device
    Wire.write(register_addr); // Sends Potentiometer Reading (8Bit)

    //pinMode(2, INPUT);
    //pinMode(3, INPUT);
    //if (digitalRead(2) == LOW || digitalRead(3) == LOW)
    //{
    //    Serial.println("I2C STUCK");
    //}

    Wire.endTransmission(false);

    Wire.requestFrom(device_address, 1);

    if (Wire.available() == 1)
    {
        byte received_value = Wire.read();
        return (int)received_value;
    }
    else
    {

        return -1;
    }
}
