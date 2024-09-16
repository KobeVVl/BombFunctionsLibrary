#ifndef BOMBFUNCTIONS_H
#define BOMBFUNCTIONS_H

#define DEBUG 0
#define BANANA_DEBUG 0

#define LCD "lcd"

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Preset.h>
#include <EEPROM.h>

#include "BombConstants.h"

bool isGreenLed1On(bool setNew, bool newValue);
bool isGreenLed2On(bool setNew, bool newValue);
bool isGreenLed3On(bool setNew, bool newValue);

uint16_t setGetCodeValues(bool setNew, uint8_t pos, uint16_t newValue);
uint16_t setGetWireValues(bool setNew, uint8_t pos, uint16_t newValue);

void prepare();

int waitForNumber();
uint8_t getDigit();
// String getNumberInt(int lengte, String disp);
// String getNumberInt(int lengte);
// int getNumberInt(int lengte, String disp);
// int getNumberInt(int lengte);
void wait(int number);
void printRepeat(char character, unsigned int count, String device);
unsigned int decreaseInterval(int totalTime, int currentTime);
void beep();
void victoryBlink();
void victory();
void defeatBlink();
void defeat();
void wrongTune();
uint8_t getWire();
uint8_t getWireSimple();
uint8_t getBanana();
void bananaPin(const double *banana, int length, int pin, int *combinatie, int index);

uint16_t calibrateButton(uint8_t key, int length);
void calibrateButtons();
uint16_t calibrateWire(uint8_t key, int length);
void calibrateWires();

void repeatLcdPrint(char character, unsigned int count);

void lightGreenLeds(uint8_t amount);
void controlRedLed(int value);
int punishment(int time);

int writePresetToEEPROM(int address, Preset &preset);
int readPresetFromEEPROM(int address, Preset *preset);

int writeStringToEEPROM(int addrOffset, const String &strToWrite);
int readStringFromEEPROM(int addrOffset, String *strToRead);

void serialDebugCode(char &charac, String &enteredCode, uint8_t &codeIndex, bool &pressed);
void serialDebugPressed(uint8_t &number, bool &pressed);
void serialDebugMain(String &trueCode, uint8_t &trueBanana, uint8_t trueWire, unsigned int &totalTime, bool codeDone, bool wireDone, bool bananaDone, bool questionsDone);

#endif
