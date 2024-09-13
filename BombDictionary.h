#ifndef BombDictionary_h
#define BombDictionary_h

#define EN 0
#define NL 1
#define AMOUNT_LANGUAGES 2
#define AMOUNT_MODES 3
#define AMOUNT_SETTINGS 4

const String languages[AMOUNT_LANGUAGES] = {"ENGLISH", "NEDERLANDS"};
const String shortLanguages[AMOUNT_LANGUAGES] = {"EN", "NL"};
const String settings[AMOUNT_SETTINGS][AMOUNT_LANGUAGES] = {
    {// 0
     "LANGUAGE       ",
     "TAAL           "},
    {// 1
     "Calibrate btns.",
     "Kalibreer knop "},
    {// 2
     "Calibrate wires",
     "Kalibreer draad"},
    {// 3
     "Turn off       ",
     "Zet uit        "}};

const String modes[AMOUNT_MODES][AMOUNT_LANGUAGES] = {
    {// 0
     "DEFUSE MODE    ",
     "ONTMANTEL MODE "},
    {// 1
     "CSGO MODE      ",
     "CSGO MODE      "},
    {// 2
     "PATTERN MODE   ",
     "PATROON MODE   "}};

const String languageDict[][AMOUNT_LANGUAGES] = {
    {// 0
     "Reuse settings",
     "Hergebruik inst."},
    {// 1
     "NO(X) YES(",
     "NEE(X) JA("},
    {// 2
     "1:DEFUSE MODE",
     "1:ONTMANTEL MODE"},
    {// 3
     "2:CSGO MODE",
     "2:CSGO MODE"},
    {// 4
     "Enter total time",
     "Geef totale tijd"},
    {// 5
     "Set code length:",
     "Stel len code in"},
    {// 6
     "Set code:",
     "Stel code in:"},
    {// 7
     "ENTER RIGHT LENGTH",
     "GEEN JUISTE LEN."},
    {// 8
     "Set wire:",
     "Stel draad in:"},
    {// 9
     "NUMBER TOO BIG",
     "NUMMER TE HOOG"},
    {// 10
     "Set ban cnf + OK",
     "Zet ban cnf + OK"},
    {// 11
     "Set #quest.:",
     "Stel #vragen in:"},
    {// 12
     "Set quest diffic",
     "Moeilijkheid vrg"},
    {// 13
     "Set plant code:",
     "Stel plntcode in"},
    {// 14
     "Set plant time:",
     "Stel plnttijd in"},
    {// 15
     "Press ",
     "Druk op "},
    {// 16
     "to start",
     "om te starten"},
    {// 17
     "Code done!",
     "Code klaar!"},
    {// 18
     "Wire done!",
     "Draad klaar!"},
    {// 19
     "Banana done!",
     "Banana klaar!"},
    {// 20
     "Bomb defused",
     "Bom ontmanteld"},
    {// 21
     "Bomb exploded",
     "Bom ontploft"},
    {// 22
     "Enter plant code",
     "Geef plntcode in"},
    {// 23
     "Hold ",
     "Houd "},
    {// 24
     "to plant",
     "om te planten"},
    {// 25
     "CHANGE LANGUAGE:",
     "VERANDER TAAL:"},
    {// 26
     "CHOSE LANGUAGE:",
     "KIES TAAL:"},
    {// 27
     "CHECK CODE   ",
     "CHECK CODE   "},
    {// 28
     "CHECK WIRE   ",
     "CHECK DRAAD  "},
    {// 29
     "CHECK CONNECT",
     "CHECK CONNECT"},
    {// 30
     "Calibrate btns?",
     "Calibreer knop?"},
    {// 31
     "Calibrate wires?",
     "Calibreer draad?"},
    {// 32
     "Turn off?",
     "Zet uit?"},
    {// 33
     "Wire: ",
     "Draad: "},
    {// 34
     "set",
     "ingesteld"},
    {// 35
     "Select with ",
     "Selecteer met "}};

#endif