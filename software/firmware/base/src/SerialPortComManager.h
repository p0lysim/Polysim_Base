#include <Arduino.h>
#include <Wire.h>
#include "I2C_Manager.h"
#include "AS5600.h"
#include "Grip.h"

#ifndef SERIAL_PORT_COM_MANAGER_H
#define SERIAL_PORT_COM_MANAGER_H

#define SERIAL_RATE 11500 //Serial baud rate
#define TIMEOUT = 2000 //2s / command

class SerialPortComManager
{
    private:
        static bool _serialIsRunning; 
        static Grip * _grip;
        static AS5600 * _X_encoder;
        static AS5600 * _Y_encoder;

        /*----------------------------------------
        * Cest variables sont mises a jour par SplitCommand
        * Qui est appelé a chaque fois qu'on recoit une command par ReadAndAnswerCommand
        * Ensuie ReadAndAnswerCommand traite ces variables pour faire une reponse
        ----------------------------------------*/
        static char _current_command_ID;
        static String _current_command_NAME;
        static int  _current_command_VALUE;
        static bool SplitCommand(String command);


    public:
        static void StartSerial(Grip * grip, AS5600 * X_encoder, AS5600 * Y_encoder);
        static void ReadAndAnswerCommand();


};



#endif