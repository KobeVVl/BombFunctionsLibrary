#include "Arduino.h"
#include "BombFunctions.h"

LiquidCrystal liquidCrystal(reset, enable, d4, d5, d6, d7);

bool isGreenLed1On(bool setNew, bool newValue)
{
  static bool value;
  if (setNew)
  {
    value = newValue;
  }
  return value;
}
bool isGreenLed2On(bool setNew, bool newValue)
{
  static bool value;
  if (setNew)
  {
    value = newValue;
  }
  return value;
}
bool isGreenLed3On(bool setNew, bool newValue)
{
  static bool value;
  if (setNew)
  {
    value = newValue;
  }
  return value;
}

uint16_t setGetCodeValues(bool setNew, uint8_t pos, uint16_t newValue)
{
  static uint16_t values[sizeof(codeValues) / sizeof(codeValues[0])];
  if (setNew)
  {
    values[pos] = newValue;
  }
  return values[pos];
}

uint16_t setGetWireValues(bool setNew, uint8_t pos, uint16_t newValue)
{
  static uint16_t values[sizeof(wireValues) / sizeof(wireValues[0])];
  if (setNew)
  {
    values[pos] = newValue;
  }
  return values[pos];
}

/* ------------------- BASICLY SETUP ------------------- */
void prepare()
{
  liquidCrystal.begin(16, 2);
  if (DEBUG)
    Serial.begin(115200);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(relayPin, OUTPUT);
  isGreenLed1On(true, false);
  isGreenLed2On(true, false);
  isGreenLed3On(true, false);
  randomSeed(analogRead(randomPin));

  // Load code values --> eventueel uit EEPROM
  for (uint8_t i = 0; i < sizeof(codeValues) / sizeof(codeValues[0]); i++)
  {
    setGetCodeValues(true, i, codeValues[i]);
  }

  // Load wire values --> eventueel uit EEPROM
  for (uint8_t i = 0; i < sizeof(wireValues) / sizeof(wireValues[0]); i++)
  {
    setGetWireValues(true, i, wireValues[i]);
  }

  delay(250);
  digitalWrite(relayPin, LOW);
}

/* ------------------- HELP FUNCTIONS ------------------- */
int waitForNumber()
{
  while (getDigit() == -1)
  {
  }
  return getDigit();
}

/* Geeft nummer terug voor gegeven waarde of -1 als het geen nummer is */
uint8_t getDigit()
{
  uint16_t value1 = analogRead(codePin);
  delay(20);
  uint16_t value2 = analogRead(codePin);

  if (value2 > value1 + 20 || value2 < value1 - 20)
  {
    return -1;
  }
  uint16_t value = (value1 + value2) / 2;
  for (uint8_t i = 0; i < sizeof(codeValues) / sizeof(codeValues[0]); i++)
  {
    if (value < setGetCodeValues(false, i, 0) + 20 && value > setGetCodeValues(false, i, 0) - 20)
    {
      return codeKeys[i];
      // delay(150);
    }
  }
  return -1;
}

void wait(int number)
{
  while (getDigit() == number)
  {
  }
}

void calibrateButtons()
{
  for (int8_t i = 0; i < sizeof(codeValues) / sizeof(codeValues[0]); i++)
  {
    liquidCrystal.clear();
    liquidCrystal.print("Calibrate " + codeNames[i]);
    setGetCodeValues(true, i, calibrateButton(codeKeys[i], 3));
    wait(codeKeys[i]);
  }
  if (DEBUG)
  {
    Serial.println("New values: ");
    for (int8_t i = 0; i < sizeof(codeValues) / sizeof(codeValues[0]); i++)
    {
      Serial.print("'");
      Serial.print(codeNames[i]);
      Serial.print(": ");
      Serial.print(setGetCodeValues(false, i, 0));
      Serial.println("'");
    }
  }
}

uint16_t calibrateButton(uint8_t key, int length)
{
  bool calibrated = length <= 0;
  int buttonState = LOW;
  int prevState = LOW;
  unsigned long startTime;
  unsigned long counter = 0;
  uint16_t average = 0;
  while (!calibrated)
  {
    uint16_t value = analogRead(codePin);
    if (value >= 20)
    {
      buttonState = HIGH;
    }
    else
    {
      buttonState = LOW;
      average = 0;
      counter = 0;
    }
    if (buttonState == HIGH && prevState == LOW)
    {                       // Als de knop ingedrukt wordt (en dus nog niet ingedrukt was)
      startTime = millis(); // Sla de tijd op wanneer de knop ingedrukt wordt
      prevState = HIGH;     // Onthoud dat de knop ingedrukt is
    }
    else if (buttonState == HIGH && prevState == HIGH)
    { // Als de knop nog steeds ingedrukt is
      unsigned long currentTime = millis();
      int count = (currentTime - startTime) / (length * 1000 / 16);

      counter++;
      unsigned int intAv = average * (counter - 1) + value;
      average = intAv / counter;

      liquidCrystal.setCursor(0, 1);
      repeatLcdPrint((char)255, count % 16 + 1);
      delay(50);
      if (currentTime - startTime >= length * 1000)
      {
        calibrated = true;
      } // Als de knop voor `length` seconden is ingedrukt (verschil tussen tijdstip dat de knop werd ingedruk met tijdstip op dit moment) dan is programma klaar (done).
    }
    else if (buttonState == LOW && prevState == HIGH)
    { // Als knop losgelaten wordt (en dus ingedrukt was)
      prevState = LOW;
      liquidCrystal.setCursor(0, 1);
      liquidCrystal.print("                ");
    }
  }
  return average;
}

void calibrateWires()
{
  liquidCrystal.clear();
  liquidCrystal.print("Put all wires");
  liquidCrystal.setCursor(0, 1);
  liquidCrystal.print("back");
  while (analogRead(wirePin) <= 1000)
  {
  }
  for (int8_t i = 0; i < sizeof(wireValues) / sizeof(wireValues[0]); i++)
  {
    liquidCrystal.clear();
    liquidCrystal.print("Calibrate " + wireKeys[i]);
    setGetWireValues(true, i, calibrateWire(codeKeys[i], 3));
    liquidCrystal.clear();
    liquidCrystal.print("Put wire back");
    while (analogRead(wirePin) <= 1000)
    {
    }
  }
  if (DEBUG)
  {
    Serial.println("New values: ");
    for (int8_t i = 0; i < sizeof(wireValues) / sizeof(wireValues[0]); i++)
    {
      Serial.print("'");
      Serial.print(wireKeys[i]);
      Serial.print(": ");
      Serial.print(setGetWireValues(false, i, 0));
      Serial.println("'");
    }
  }
}

uint16_t calibrateWire(uint8_t key, int length)
{
  bool calibrated = length <= 0;
  int wireState = LOW;
  int prevState = LOW;
  unsigned long startTime;
  unsigned long counter = 0;
  uint16_t average = 0;
  while (!calibrated)
  {
    uint16_t value = analogRead(wirePin);
    if (value <= 1000)
    {
      wireState = HIGH;
    }
    else
    {
      wireState = LOW;
      average = 0;
      counter = 0;
    }
    if (wireState == HIGH && prevState == LOW)
    {                       // Als de knop ingedrukt wordt (en dus nog niet ingedrukt was)
      startTime = millis(); // Sla de tijd op wanneer de knop ingedrukt wordt
      prevState = HIGH;     // Onthoud dat de knop ingedrukt is
    }
    else if (wireState == HIGH && prevState == HIGH)
    { // Als de knop nog steeds ingedrukt is
      unsigned long currentTime = millis();
      int count = (currentTime - startTime) / (length * 1000 / 16);

      counter++;
      unsigned int intAv = average * (counter - 1) + value;
      average = intAv / counter;

      liquidCrystal.setCursor(0, 1);
      repeatLcdPrint((char)255, count % 16 + 1);
      delay(50);
      if (currentTime - startTime >= length * 1000)
      {
        calibrated = true;
      } // Als de knop voor `length` seconden is ingedrukt (verschil tussen tijdstip dat de knop werd ingedruk met tijdstip op dit moment) dan is programma klaar (done).
    }
    else if (wireState == LOW && prevState == HIGH)
    { // Als knop losgelaten wordt (en dus ingedrukt was)
      prevState = LOW;
      liquidCrystal.setCursor(0, 1);
      liquidCrystal.print("                ");
    }
  }
  return average;
}

void repeatLcdPrint(char character, unsigned int count)
{
  while (count-- > 0)
  {
    liquidCrystal.print(character);
  }
}

void printRepeat(char character, unsigned int count, String device)
{
  while (count-- > 0)
  {
    if (device == SERIAL && DEBUG == 1)
      Serial.print(character);
    else if (device == LCD)
      ;
    liquidCrystal.print(character);
  }
}

unsigned int decreaseInterval(int totalTime, int currentTime)
{
  int eersteDeel = (totalTime * 3) / 5;
  int tweedeDeel = totalTime - fastBeepTime;
  if (currentTime < eersteDeel)
  {
    return maxInterval;
  }
  else if (currentTime < tweedeDeel)
  {
    return maxInterval - ((maxInterval - minInterval) / (tweedeDeel - eersteDeel)) * (currentTime - eersteDeel);
  }
  else if (currentTime < totalTime)
  {
    return minInterval;
  }
}

void beep()
{
  tone(piezoPin, beepPitch, beepLength);
}

void victoryBlink()
{
  lightGreenLeds(3);
  delay(500);
  lightGreenLeds(0);
  delay(500);
  lightGreenLeds(3);
  delay(500);
  lightGreenLeds(0);
  delay(500);
  lightGreenLeds(3);
  delay(500);
  lightGreenLeds(0);
  delay(500);
}

void victory()
{
  tone(piezoPin, 262);
  delay(300);
  tone(piezoPin, 392);
  delay(150);
  tone(piezoPin, 523);
  delay(150);
  noTone(piezoPin);
  victoryBlink();
}

void defeatBlink()
{
  controlRedLed(HIGH);
  delay(500);
  controlRedLed(HIGH);
  delay(500);
  controlRedLed(HIGH);
  delay(500);
  controlRedLed(HIGH);
  delay(500);
  controlRedLed(HIGH);
  delay(500);
  controlRedLed(HIGH);
  delay(500);
}

void defeat()
{
  tone(piezoPin, 100);
  delay(1000);
  noTone(piezoPin);
  defeatBlink();
}

void wrongTune()
{
  tone(piezoPin, 233);
  controlRedLed(HIGH);
  delay(100);
  tone(piezoPin, 138);
  controlRedLed(LOW);
  delay(100);
  noTone(piezoPin);
  controlRedLed(HIGH);
  delay(100);
  controlRedLed(LOW);
}

/* ------------------- BOMB STATE FUNCTIONS ------------------- */

/**
 * @brief Geeft de index van de gekozen wire terug
 *
 * @return uint8_t (0 - #draden)
 */
uint8_t getWire()
{
  return getWireSimple();
}

/**
 * @brief Geeft de index van de gekozen wire terug zonder rekening te houden met andere uitgetrokken draden
 *
 * @return uint8_t (0 - #draden)
 */
uint8_t getWireSimple()
{
  int value = analogRead(wirePin);
  for (uint8_t i = 0; i < sizeof(wireValues) / sizeof(wireValues[0]); i++)
  {
    if (value < wireValues[i] + 20 && value > wireValues[i] - 20)
      return i + 1;
  }
  return -1;
}

/**
 * @brief Geeft de index van de (meest waarschijnlijke) banana configuratie
 *
 * @return uint8_t
 */
uint8_t getBanana()
{
  int combinatie[20];
  memset(combinatie, 0, sizeof(combinatie));
  int index = 0;
  int waarschijnlijk = 0; // reset en alles op nul voor elke keer als je terug opnieuw checked
  int biggest = 0;

  bananaPin(banana1, sizeof(banana1) / sizeof(banana1[0]), bananaPin1, combinatie, index);
  bananaPin(banana2, sizeof(banana2) / sizeof(banana2[0]), bananaPin2, combinatie, index); // checkt elke pin en zet de combinatie die mogelijk is bij die waarde in de array "combinatie"
  bananaPin(banana3, sizeof(banana3) / sizeof(banana3[0]), bananaPin3, combinatie, index);
  bananaPin(banana4, sizeof(banana4) / sizeof(banana4[0]), bananaPin4, combinatie, index);

  if (DEBUG && BANANA_DEBUG)
  {
    Serial.print("Combinatie: ");
    for (int k = 0; k < sizeof(combinatie) / sizeof(combinatie[0]); k++)
    {
      Serial.print(combinatie[k]);
    }
    Serial.println();
  }
  for (int j = 0; j < 20; j++)
  { // leest welke dat meest waarschijnlijk voorkomt in "combinatie"
    int count = 0;
    for (int i = 0; i < 20; i++)
    {
      if (combinatie[j] == 0)
      {
        break;
      }
      if (combinatie[j] == combinatie[i])
      {
        if (DEBUG && BANANA_DEBUG)
        {
          Serial.print("Count: ");
          Serial.println(count);
        }
        count++;
      }
    }
    if (biggest < count)
    {
      biggest = count;
      waarschijnlijk = combinatie[j];
      if (DEBUG && BANANA_DEBUG)
      {
        Serial.print("Biggest: ");
        Serial.println(biggest);
        Serial.print("Waarschijnlijk: ");
        Serial.println(waarschijnlijk);
      }
    }
  }
  return waarschijnlijk - 100;
}

void bananaPin(const double *banana, int length, int pin, int *combinatie, int index)
{
  double value = analogRead(pin);
  value = value * 5 / 1024; // in voltage!
  if (DEBUG && BANANA_DEBUG)
    Serial.println(value);
  int j;
  for (int i = 0; i < length; i++)
  {
    if (value < 100 && value < banana[i] + 0.05 && value > banana[i] - 0.05)
    {            // binnen een marge van 0.05V checken of overeenkomt
      j = i + 1; // zie naar volgend element
      while (banana[j] > 100)
      {                                // als dat hoger is als 1000 en dus geen spanning, maar combinatieNr is
        combinatie[index] = banana[j]; // voeg je deze toe aan de mogelijke combinaties
        index++;
        j++;
      }
      break; // als je de juiste waarde al gevonden hebt, break je de for loop, moet je niet verder zoeken!
    }
  }
}

/**
 * @brief Zet amount aantal groene leds aan
 *
 * @param amount Aantal groene leds die aan moeten
 */
void lightGreenLeds(uint8_t amount)
{
  static uint8_t am;
  if (amount != am)
  {
    am = min(amount, 3);
    if (DEBUG)
    {
      Serial.print("Am: ");
      Serial.println(am);
    }
    switch (am)
    {
    case 0:
      digitalWrite(ledPin1, LOW);
      isGreenLed1On(true, false);
      digitalWrite(ledPin2, LOW);
      isGreenLed2On(true, false);
      digitalWrite(ledPin3, LOW);
      isGreenLed3On(true, false);
      break;
    case 1:
      digitalWrite(ledPin1, HIGH);
      isGreenLed1On(true, true);
      digitalWrite(ledPin2, LOW);
      isGreenLed2On(true, false);
      digitalWrite(ledPin3, LOW);
      isGreenLed3On(true, false);
      break;
    case 2:
      digitalWrite(ledPin1, HIGH);
      isGreenLed1On(true, true);
      digitalWrite(ledPin2, HIGH);
      isGreenLed2On(true, true);
      digitalWrite(ledPin3, LOW);
      isGreenLed3On(true, false);
      break;
    case 3:
      digitalWrite(ledPin1, HIGH);
      isGreenLed1On(true, true);
      digitalWrite(ledPin2, HIGH);
      isGreenLed2On(true, true);
      digitalWrite(ledPin3, HIGH);
      isGreenLed3On(true, true);
      break;
    }
  }
}

/**
 * @brief Zet alle rode leds aan/uit door groene uit/aan te zetten
 *
 * @param value HIGH/LOW
 */
void controlRedLed(int value)
{
  if (value == LOW)
  { // LOW
    digitalWrite(ledRed, LOW);
    if (isGreenLed1On(false, false))
      digitalWrite(ledPin1, HIGH);
    if (isGreenLed2On(false, false))
      digitalWrite(ledPin2, HIGH);
    if (isGreenLed3On(false, false))
      digitalWrite(ledPin3, HIGH);
  }
  else
  { // HIGH
    if (isGreenLed1On(false, false))
      digitalWrite(ledPin1, LOW);
    if (isGreenLed2On(false, false))
      digitalWrite(ledPin2, LOW);
    if (isGreenLed3On(false, false))
      digitalWrite(ledPin3, LOW);
    digitalWrite(ledRed, HIGH);
  }
  delay(50);
}

int punishment(int time)
{
  if (DEBUG)
  {
    Serial.println("Punishment: " + String(time) + "sec");
  }
  return time;
}

/**
 * @brief Sla preset op in EEPROM zodat het na reset nog gebruikt kan worden
 *
 * @param address Start address in EEPROM, start write
 * @param preset Preset die weggeschreven wordt
 * @return int Eind address na write
 */
int writePresetToEEPROM(int address, Preset &preset)
{
  if (DEBUG)
  {
    Serial.println("write preset");
    preset.print();
  }
  PresetStruct str;
  str = preset.toStruct();
  if (DEBUG)
  {
    Serial.println("Structure:");
    Serial.print("\tBanana: ");
    Serial.println(str.bananaConfig);
    Serial.print("\tWire: ");
    Serial.println(str.wire);
    Serial.print("\tAm questions: ");
    Serial.println(str.amQuestions);
    Serial.print("\tQuestions diff: ");
    Serial.println(str.questionsDiff);
    Serial.print("\tPlant time: ");
    Serial.println(str.plantTime);
    Serial.print("\tTime: ");
    Serial.println(str.time);
  }
  EEPROM.put(address, str);
  address += sizeof(str);
  address = writeStringToEEPROM(address, preset.code);
  address = writeStringToEEPROM(address, preset.plantCode);
  return address;
}

/**
 * @brief Haal laatste preset uit EEPROM
 *
 * @param address Start address in EEPROM, start read
 * @param preset Preset pointer waar preset in wordt gezet
 * @return int Eind adress na read
 */
int readPresetFromEEPROM(int address, Preset *preset)
{
  PresetStruct str;
  String code;
  String plantCode;
  EEPROM.get(address, str);
  if (DEBUG)
  {
    Serial.println("Structure:");
    Serial.print("\tBanana: ");
    Serial.println(str.bananaConfig);
    Serial.print("\tWire: ");
    Serial.println(str.wire);
    Serial.print("\tAm questions: ");
    Serial.println(str.amQuestions);
    Serial.print("\tQuestions diff: ");
    Serial.println(str.questionsDiff);
    Serial.print("\tPlant time: ");
    Serial.println(str.plantTime);
    Serial.print("\tTime: ");
    Serial.println(str.time);
  }
  address += sizeof(str);
  address = readStringFromEEPROM(address, &code);
  address = readStringFromEEPROM(address, &plantCode);
  Preset pre(str, code, plantCode);
  *preset = pre;
  if (DEBUG)
  {
    Serial.println("read preset");
    (*preset).print();
  }
  return address - sizeof(preset);
}

int writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
  return addrOffset + 1 + len;
}
int readStringFromEEPROM(int addrOffset, String *strToRead)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  *strToRead = String(data);
  return addrOffset + 1 + newStrLen;
}

void serialDebugCode(char &charac, String &enteredCode, uint8_t &codeIndex, bool &pressed)
{
  if (DEBUG)
  {
    Serial.print("Character: ");
    Serial.println(charac);
    Serial.print("code: ");
    Serial.println(enteredCode);
    Serial.print("codeIndex: ");
    Serial.println(codeIndex);
    Serial.print("pressed: ");
    Serial.println(pressed);
  }
}

void serialDebugPressed(uint8_t &number, bool &pressed)
{
  if (DEBUG)
  {
    Serial.print("number: ");
    Serial.println(number);
    Serial.print("pressed: ");
    Serial.println(pressed);
  }
}

void serialDebugMain(String &trueCode, uint8_t &trueBanana, uint8_t trueWire, unsigned int &totalTime, bool codeDone, bool wireDone, bool bananaDone, bool questionsDone)
{
  if (DEBUG)
  {
    Serial.println();
    Serial.print("Started loop with:\n  - code: ");
    Serial.print(trueCode);
    Serial.print(",\n  - banana config: ");
    Serial.print(trueBanana);
    Serial.print(",\n  - wire: ");
    Serial.print(wireKeys[trueWire]);
    Serial.print(",\nTime to defuse the bomb: ");
    Serial.print(totalTime);
    Serial.println(" seconds.");
    Serial.print("Code: ");
    Serial.println(codeDone ? "Done" : "Not done");
    Serial.print("Wire: ");
    Serial.println(wireDone ? "Done" : "Not done");
    Serial.print("Banana: ");
    Serial.println(bananaDone ? "Done" : "Not done");
    Serial.print("Questions: ");
    Serial.println(questionsDone ? "Done" : "Not done");
  }
}