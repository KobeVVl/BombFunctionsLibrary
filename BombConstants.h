#ifndef BombConstants_h
#define BombConstants_h

// PUNISHMENT SEVIRITIES
const uint8_t CODE_SEVERITY = 5;
const uint8_t WIRE_SEVERITY = 15;
const uint8_t BANANA_SEVERITY = 15;

const uint8_t OK = 200;
const uint8_t BAD = 201;
const uint8_t BACK = 100;
const uint8_t RIGHT = 101;
const uint8_t LEFT = 102;

/* ----------------------- DATA ----------------------- */
/* code keyboard */
const uint16_t codeValues[] = {310, 1011, 977, 929, 835, 762, 687, 648, 602, 510, 400, 230, 175, 128, 88};
const uint8_t codeKeys[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, BAD, OK, LEFT, BACK, RIGHT};
const String codeNames[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "BAD", "OK", "LEFT", "BACK", "RIGHT"};

/* bananenklemmen waardes */
const double banana1[] = {4.3, 101, 4.2, 102, 4.1, 103, 3.1, 104, 105, 110, 3.2, 106, 4.0, 107, 3.8, 108, 112, 3.7, 109, 113, 114, 115, 3.5, 111};
const double banana2[] = {4.3, 101, 4.2, 102, 3.8, 103, 104, 108, 3.6, 105, 106, 109, 4.0, 107, 3.5, 110, 2.7, 111, 114, 3.1, 112, 2.6, 113, 3.2, 115};
const double banana3[] = {4.1, 103, 4.0, 107, 3.8, 104, 105, 3.7, 106, 3.6, 101, 114, 3.5, 110, 111, 3.3, 102, 3.2, 113, 115, 2.7, 108, 109, 2.5, 112};
const double banana4[] = {4.0, 107, 3.8, 103, 104, 110, 111, 3.7, 109, 114, 3.6, 101, 105, 3.5, 108, 3.2, 113, 3.1, 112, 2.7, 106, 2.6, 115, 2.5, 102};

/* draden waardes */
const uint16_t wireValues[] = {926, 835, 687, 509, 309, 172};
const String wireKeys[] = {"rood", "oranje", "geel", "groen", "blauw", "paars"};

/* ------------------- CONSTANTS ------------------- */
const int maxInterval = 5000;
const int minInterval = 150;
const int fastBeepTime = 5; // De laaste x seconden beept de bom met minInterval er tussen (snel)

const unsigned int beepPitch = 3000;
const unsigned long beepLength = 75;

/* ------------------- PINS ------------------- */
#define bananaPin1 A0
#define bananaPin2 A1
#define bananaPin3 A2
#define bananaPin4 A3
#define wirePin A5
#define codePin A4
#define randomPin A6
#define ledRed 2
#define ledPin1 5
#define ledPin2 4
#define ledPin3 3
#define piezoPin 6
#define relayPin 13

const uint8_t reset = 7;
const uint8_t enable = 8;
const uint8_t d4 = 9;
const uint8_t d5 = 10;
const uint8_t d6 = 11;
const uint8_t d7 = 12;

#endif