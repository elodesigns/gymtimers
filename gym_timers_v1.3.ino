
//------------------------------------------------LYBRARYS_DEPENDENCY-------------------------------------------  
#include <Chrono.h>
#include <Adafruit_NeoPixel.h>
#include "ButtonKing.h" //requires 1.2 beta for triple click , download from https://github.com/TanPitch/ButtonKing  
#include <EEPROM.h>

#define MAX_COUNT_UP_TIME 35939 //(((9h*60 )+59m)*60s)-1s
#define NO_OF_QUICK_PRESETS 5
#define NO_OF_TOTAL_PRESETS 9
//-----------------------------------------=== ESP_8266_D1_Mini_CONNECTIONS===----------------------------------
const byte BUZZER_PIN = D5;      
const byte PIXELS_PIN = D6;        
const byte DOT_PIN = D7;          
const byte BUILTIN_BUTTON_PIN = D4;
const byte NUMPIXELS = 21;                       //number of LED's

//-----------------------------------------------OBJIECTS_&&_VARIABLES--------------------------------------------
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel dotObj = Adafruit_NeoPixel(2, DOT_PIN, NEO_GRB + NEO_KHZ800);
Chrono timer_ms;                                                          // http://sofapirate.github.io/Chrono/
Chrono buzzer_ms; 
Chrono autoIncrement_ms;

ButtonKing button1 (BUILTIN_BUTTON_PIN , true);

byte c_matrix[10][3] = {           // color matrix referenced by disply stuff and others
  //  R,  G,  B
  {0, 0, 0},                 // MOD 0 STOPPED            BLACK
  {0, 255, 0},               // MOD 1 work_time_play     GREEN
  {0, 150, 70},              // MOD 2 work_time_paused   CIAN
  {255,  0, 0},              // MOD 3 rest_time_play     RED
  {180, 50,0},               // MOD 4 rest_time_paused   ORANGE
  {255, 0, 255},             // MOD 5 rainbow            PURPLE
  {255, 255, 255 },          // MOD 6 setup_mode         WHITE
  {0, 0, 255},               // MOD 7 count_up_play      BLUE
  {50,0, 170},               // MOD 8 count_up_paused    PINKISH
  {255,200,0}                // MOD 9 ct_stopped rounds  YELLOW
};


int presets_matrix[10][4] = {                  //  presets_matrix[set][param]   working sets, load up from eeprom 
  //  0-WT, 1-RT, 2-R/10, 3-sig_Typ/10, 
  {300, 30,  40,   10},         //WS 0 regular training
  {360, 120, 100,  20},         //WS 1 open mat training
  {20,  10,  80 ,  30},         //WS 2 tabata 
  {180, 59,  30 ,  40},         //WS 3
  {240, 59,  40 ,  50},         //WS 4 
  {300, 59,  50 ,  60},         //WS 5 
  {360, 59,  60 ,  70},         //WS 6 
  {420, 59,  70 ,  80},         //WS 7 
  {480, 59,  80 ,  90},         //WS 8 
  {540, 59,  90 ,  0}          //WS 9 

};

const byte sec_increment_value=10;
const byte min_increment_value=60;
const byte OFF=0;
const byte ON=255;

//  training set parameters read from presets_matrix[set][param] matrix
int mem_work_time ;   
int mem_rest_time ;  
int mem_rounds  ;   
int mem_sig_typ  ;   
  

// values decremented /incremented during counting 
int work_time ;
int rest_time ;
int rounds ;
int count_time=0;
byte sig_typ=0;
byte sound_typ=0;

int P=0;

byte eeprom_adr=0;
byte eeprom_io=0;
bool write_eeprom=false;
bool increase=false;


byte preset=0;
byte mod=10;
byte setup_item=0;
int  refresh_ms=1 ;
byte show_type=4;

//unsigned long loop_started=0;
//unsigned long loop_time=0;


void setup() {

  pinMode(BUZZER_PIN , OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(115200);
  Serial.println();
  Serial.println(F("GYM TIMERS v1.3"));   //2020.10.13
  Serial.print(F("UPDATED: "));
  Serial.println(F(__DATE__)); 
  Serial.print(F("BUILD: "));
  Serial.println(F(__TIME__));
  Serial.println(F("https://github.com/elodesigns/gymtimers"));
  
  strip.begin();
  dotObj.begin();
  delay(30);
  dot(5,false); 
  color_wipe (5);
 
   link_button1();

    EEPROM.begin(512);

 // write_presets_to_eeprom();
 read_presets_from_eeprom();
 load_training_sets_from_matrix();  
 
 buzzer_ms.stop();
 autoIncrement_ms.stop();   
   
}

void loop() {
//loop_started=millis();

button1.isClick(); // check built in button if was  short or  doubble pressed or  longpress released  (count up to 3 and than release the button)
make_sound();              // drive piezzo buzzer and neighbours into madness 

Timer();         // light up the LED 's in a time and culture pre-dertiminated logic

if(write_eeprom){
  store_training_sets_to_matrix();
  write_presets_to_eeprom();
  write_eeprom=false;
  Serial.println(F("Checking..."));
  read_presets_from_eeprom();
}
//loop_time=millis()-loop_started;
//Serial.println(loop_time);

}
