#include <Arduino.h>
#include <Joystick.h>
#include "AS5600.h"
#include "Grip.h"
#include "SerialPortComManager.h"


uint8_t joystick_ID = JOYSTICK_DEFAULT_REPORT_ID;
uint8_t joystick_Type = JOYSTICK_TYPE_JOYSTICK;
uint8_t nb_btn = 32;
uint8_t nb_hatSwitch = 0;
bool XAxis = true;
bool YAxis = true;
bool ZAxis = false;
bool RxAxis = true;
bool RyAxis = true;
bool RzAxis = false;
bool Rudder = false;
bool Throttle = false;
bool Accelerator = false;
bool Brake = false;
bool Steering = false;

Joystick_ Joystick(joystick_ID, joystick_Type, nb_btn, nb_hatSwitch, XAxis, YAxis, ZAxis, RxAxis, RyAxis, RzAxis, Rudder, Throttle, Accelerator, Brake, Steering);
AS5600 X_encodeur;
AS5600 Y_encodeur;
Grip grip;

// Realtime variables
int isMainButton;
int isJoyClickButton;
int joy_XAxis;
int joy_YAxis;
int X_Axis;
int Y_Axis;

// Puur le calcul du framerate
void ComputeFrameRate();
int fps = 0;
unsigned long startTime = millis();

void setup()
{
  // Déja géré par SerialPortComManager
  // Serial.begin(11500); // Initialize serial communication for debugging
  
  X_encodeur.Multiplexing_SetEnable(true);
  Y_encodeur.Multiplexing_SetEnable(true);
  grip.Multiplexing_SetEnable(true);

  X_encodeur.Multiplexing_SetChanel(1); // Chanel sur le multiplexer
  Y_encodeur.Multiplexing_SetChanel(0);
  grip.Multiplexing_SetChanel(2);

  //Retrouve les calibration dans leeprom et l'ajoute dans le sensor
  X_encodeur.Calibrate_reloadCalibrationFromEPPROM();
  Y_encodeur.Calibrate_reloadCalibrationFromEPPROM();

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(0, 4096);
  Joystick.setYAxisRange(0, 4096);
  Joystick.setRxAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);

  SerialPortComManager::StartSerial(&grip, &X_encodeur, &Y_encodeur);
}

void loop()
{

  isMainButton = grip.isMainButtonPress();

  isJoyClickButton = grip.isJoyButtonPress();

  joy_XAxis = grip.GetJoyXValue();
  joy_YAxis = grip.GetJoyYValue();

  X_Axis = X_encodeur.GetAngle();
  Y_Axis = Y_encodeur.GetAngle();

  //  Serial.print("[BTN ");
  //  Serial.print(isMainButton);
  //  Serial.print(" ");
  //  Serial.print(isJoyClickButton);
  //  Serial.print(" ] [JOY ");
  //  Serial.print(joy_XAxis);
  //  Serial.print(" ");
  //  Serial.print(joy_YAxis);
  //  Serial.print(" ] [AXIS ");
  //  Serial.print(X_Axis);
  //  Serial.print(" ");
  //  Serial.print(Y_Axis);
  //  Serial.println(" ]");

  // Output usb joystick
  Joystick.setButton(0, isMainButton);
  Joystick.setButton(1, isJoyClickButton);

  Joystick.setRxAxis(1023 -joy_XAxis);
  Joystick.setRyAxis(joy_YAxis);

  Joystick.setXAxis(X_Axis);
  Joystick.setYAxis(4096 - Y_Axis);

  Joystick.sendState();

  // Check s'il y a des commandes et répond
  SerialPortComManager::ReadAndAnswerCommand();

  // ComputeFrameRate();
}

void ComputeFrameRate()
{

  unsigned long elapsedTime = millis() - startTime;
  int framerate = 1000 / elapsedTime;

  Serial.print(framerate);
  Serial.println(" FPS");

  startTime = millis();
}
