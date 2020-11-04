
void make_sound(){
  
static int sounds[20][2] = {              // sound_typ
  //  buzz_ms,  #sg
  {0,   0 },   //  0.  OFF
  {100,  2 },  //  1.           bip
  {10,  2 },   //  2. _-_-_-_   2x short   
  {200,  6 },  //  3.  __-__-   3x short
  {1000, 2},   //  4. ___-___-  4x long   
  {1500, 1 },  //  5. ________  1x extra long
  {400,  1 },  //  6. _-_-   2x short  
  {10,  3 },   //  7.  bip 
  {0,  0 },    //  8.  bip            
  {0, 0},      //  9.
  {0, 0},      //  10.
  {10, 1},       //  11.  click_1
  {100, 1},      //  12.  press_2
  {50, 3},       //  13.  double_click_3
  {120, 3},      //  14.  double_press_4
  {30, 7},      //  15.  triple_click_5
  {120, 5},      //  16.  triple_press_6
  {10,1},      //  17.  released_7
  {0, 0},        //  18.  saved 
  {0, 0}         //  19.   
  
};
  
static byte buzz_No=0;
static int  buzz_ms;
static bool buzzer_status=true;

if (sound_typ>0){
  if (!buzzer_ms.isRunning()){
       buzzer_ms.restart();
       buzz_No=sounds[sound_typ][1];
       buzz_ms=sounds[sound_typ][0];
       buzzer_status=true;
       digitalWrite(BUZZER_PIN, buzzer_status);
                             } 
      }else{buzz_No=0;}
      
if (buzzer_ms.isRunning()){
 if (buzz_No>0){            
      if (buzzer_ms.hasPassed(buzz_ms)){
                     buzz_No--;
                     buzzer_ms.restart();
                     buzzer_status=!buzzer_status;
                     digitalWrite(BUZZER_PIN, buzzer_status);
                     Serial.print("buzzer_status");   
                     Serial.println(buzzer_status);}     
  }else{ buzzer_ms.stop();
         sound_typ=0;
         buzzer_status=false;
         digitalWrite(BUZZER_PIN, buzzer_status);
         Serial.println(F("BZZ_OFF"));
                       }   
                         }
}


void dot(byte color, bool flashing) {
  
  byte R = c_matrix[color][0];
  byte G = c_matrix[color][1];
  byte B = c_matrix[color][2];

    
    static bool dot_flag=false;
    dot_flag=!dot_flag;


if (flashing) {  
  if (dot_flag){ 
    dotObj.setPixelColor(0, dotObj.Color(OFF, OFF, OFF));
    dotObj.setPixelColor(1, dotObj.Color(OFF, OFF, OFF));
    dotObj.show();
    } else {
    dotObj.setPixelColor(0, dotObj.Color( R, G, B));
    dotObj.setPixelColor(1, dotObj.Color( R, G ,B));
    dotObj.show();
             }
                }else{
    dotObj.setPixelColor(0, dotObj.Color( R, G, B));
    dotObj.setPixelColor(1, dotObj.Color( R, G, B)); 
    dotObj.show();             
                }
 }


void write_presets_to_eeprom() {
    
 for (byte set = 0; set < 10; set++) {
     for (byte param = 0; param < 4; param++) { 
        eeprom_adr=(set*10)+param;
        eeprom_io=presets_matrix[set][param]/10;
        Serial.print(" ");
        Serial.print (eeprom_io);
        Serial.print(" ");
        EEPROM.write(eeprom_adr,eeprom_io );
     }
 Serial.println();
}
 EEPROM.commit();
 Serial.println(F("Write to EEPROM... Done!")); 
  
}



void read_presets_from_eeprom(){
   
 for (byte set = 0; set < 10; set++) {
     for (byte param = 0; param < 4; param++) {
        eeprom_adr=(set*10)+param;
        eeprom_io=EEPROM.read(eeprom_adr);
        presets_matrix[set][param]=eeprom_io*10;
        Serial.print(" ");
        Serial.print( presets_matrix[set][param]);
        Serial.print(" ");
      }
      Serial.println();
     }
 
 Serial.println(F("Read from EEPROM... Done!"));
 
 }

 
void segment (byte pos, byte val, byte col_index) {
  
// LED index map, one segment
//     0
//  1     5
//     6
//  2     4
//     3  

  const byte  delayval = 1; 
  
   
  byte R = c_matrix[col_index][0];
  byte G = c_matrix[col_index][1];
  byte B = c_matrix[col_index][2];
  
  int k = ((pos-1)*7);  //k = 0 ,7, 14, 21 ,28, 35
  
  switch (val) {
    case 0:
      strip.setPixelColor( (0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(R, G, B));
      strip.setPixelColor( (2 + k), strip.Color(R, G, B));
      strip.setPixelColor( (3 + k), strip.Color(R, G, B));
      strip.setPixelColor( (4 + k), strip.Color(R, G, B));
      strip.setPixelColor( (5 + k), strip.Color(R, G, B));
      strip.setPixelColor( (6 + k), strip.Color(OFF, OFF, OFF));

      strip.show();
      delay(delayval);
      break;


    case 1:
      strip.setPixelColor( (0 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (1 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (2 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (3 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (4 + k), strip.Color(R, G, B));
      strip.setPixelColor( (5 + k), strip.Color(R, G, B));
      strip.setPixelColor( (6 + k), strip.Color(0, 0, 0));

      strip.show();
      delay(delayval);
      break;

    case 2:
      strip.setPixelColor( (0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (2 + k), strip.Color(R, G, B));
      strip.setPixelColor( (3 + k), strip.Color(R, G, B));
      strip.setPixelColor( (4 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (5 + k), strip.Color(R, G, B));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));

      strip.show();
      delay(delayval);
      break;

    case 3:
      strip.setPixelColor( (0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (2 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (3 + k), strip.Color(R, G, B));
      strip.setPixelColor( (4 + k), strip.Color(R, G, B));
      strip.setPixelColor( (5 + k), strip.Color(R, G, B));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));

      strip.show();
      delay(delayval);
      break;

    case 4:
      strip.setPixelColor( (0 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (1 + k), strip.Color(R, G, B));
      strip.setPixelColor( (2 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (3 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (4 + k), strip.Color(R, G, B));
      strip.setPixelColor( (5 + k), strip.Color(R, G, B));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));

      strip.show();
      delay(delayval);
      break;

    case 5:
      strip.setPixelColor( (0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(R, G, B));
      strip.setPixelColor( (2 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (3 + k), strip.Color(R, G, B));
      strip.setPixelColor( (4 + k), strip.Color(R, G, B));
      strip.setPixelColor( (5 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));

      strip.show();
      delay(delayval);
      break;


    case 6:

      strip.setPixelColor( (0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(R, G, B));
      strip.setPixelColor( (2 + k), strip.Color(R, G, B));
      strip.setPixelColor( (3 + k), strip.Color(R, G, B));
      strip.setPixelColor( (4 + k), strip.Color(R, G, B));
      strip.setPixelColor( (5 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));

      strip.show();
      delay(delayval);
      break;


    case 7:
      strip.setPixelColor( (0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (2 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (3 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (4 + k), strip.Color(R, G, B));
      strip.setPixelColor( (5 + k), strip.Color(R, G, B));
      strip.setPixelColor( (6 + k), strip.Color(OFF, OFF, OFF));

      strip.show();
      delay(delayval);
      break;

    case 8:
      strip.setPixelColor( (0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(R, G, B));
      strip.setPixelColor( (2 + k), strip.Color(R, G, B));
      strip.setPixelColor( (3 + k), strip.Color(R, G, B));
      strip.setPixelColor( (4 + k), strip.Color(R, G, B));
      strip.setPixelColor( (5 + k), strip.Color(R, G, B));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));

      strip.show();
      delay(delayval);
      break;

    case 9:
      strip.setPixelColor( (0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(R, G, B));
      strip.setPixelColor( (2 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (3 + k), strip.Color(R, G, B));
      strip.setPixelColor( (4 + k), strip.Color(R, G, B));
      strip.setPixelColor( (5 + k), strip.Color(R, G, B));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));

      strip.show();
      delay(delayval);
      break;

    case 10:  // BLACK
      strip.setPixelColor( (0 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (1 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (2 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (3 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (4 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (5 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (6 + k), strip.Color(OFF, OFF, OFF));

      strip.show();
      delay(delayval);
      break;

    case 11:  // P
      strip.setPixelColor((0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(R, G, B));
      strip.setPixelColor( (2 + k), strip.Color(R, G, B));
      strip.setPixelColor( (3 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (4 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (5 + k), strip.Color(R, G, B));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));

      strip.show();
      delay(delayval);
      break;

    case 12: // r  for rounds

      strip.setPixelColor(( 0 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (1 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (2 + k), strip.Color(R, G, B));
      strip.setPixelColor( (3 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (4 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (5 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));

      strip.show();
      delay(delayval);
      break;

      case 13:  //-3-

      strip.setPixelColor(( 0 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (1 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (2 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (3 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (4 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (5 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));
      
      strip.show();
      delay(delayval);
      break;

      case 14: // =

      strip.setPixelColor(( 0 + k), strip.Color(R, G, B));
      strip.setPixelColor( (1 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (2 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (3 + k), strip.Color(R, G, B));
      strip.setPixelColor( (4 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (5 + k), strip.Color(OFF, OFF, OFF));
      strip.setPixelColor( (6 + k), strip.Color(R, G, B));
      strip.show();
      delay(delayval);
      break;

      


    default:
      animate(30, 1, ON, OFF, OFF);
      //Serial.print ( F("Segment Case ERROR,input number is: "));

      break;
  }
}


void rainbowCycle(uint8_t wait) {
  uint16_t m = 0;
  static uint16_t n = 0;

  if (n < 256) {
    n++;
    for (m = 0; m < strip.numPixels(); m++) {
      strip.setPixelColor(m, Wheel(((m * 256 / strip.numPixels()) + n) & 255));
    }
    strip.show();
    delay(wait);
  } else {
    n = 0;
  }

}

void rainbow(uint8_t wait) {
  uint16_t i = 0;
  static uint16_t j = 0;

  if (j < 256) {
    j++;
    for (i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);

  } else {
    j = 0;
  }

}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void color_wipe (byte c) {
  byte R = c_matrix[c][0];
  byte G = c_matrix[c][1];
  byte B = c_matrix[c][2];
  
  for (int i = 0; i < (NUMPIXELS); i++) {
    strip.setPixelColor(i, strip.Color(R, G, B));
  }
  strip.show();
  delay(1);

}

void animate(int spd, byte f, int R, int G, int B) {
  static byte k = 0;

  color_wipe(OFF);
  if (k < 10) {
    k++;
  } else {
    k = 0;
  }


  switch (k) {
    case 0:
      strip.setPixelColor( 5, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 0, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    case 1:
      strip.setPixelColor( 0, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 7, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    case 2:
      strip.setPixelColor( 7, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 14, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    case 3:
      strip.setPixelColor( 14, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 15, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    case 4:
      strip.setPixelColor( 15, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 16, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    case 5:
      strip.setPixelColor( 16, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 17, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    case 6:
      strip.setPixelColor( 17, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 10, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    case 7:
      strip.setPixelColor( 10, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 3, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    case 8:
      strip.setPixelColor( 3, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 4, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    case 9:
      strip.setPixelColor( 4, strip.Color((R / f), (G / f), (B / f)));
      strip.setPixelColor( 5, strip.Color(R, G, B));
      strip.show();
      delay(spd);
      break;
    default:
      break;


  }
}
