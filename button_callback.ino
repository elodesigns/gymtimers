void link_button1(){
  // link the button 1 functions.

  button1.setClick(click_1);                   //     +10s increment                            ;    toogle Presets while stopped  ;     Play/Pause & Mute/Resume
  button1.setPress(press_2);                   //     +1min/0.5s  auto inc. while holding       
  button1.setDoubleClick(doubleClick_3);       //     -10s decrement                                Start ; Stop 
  button1.setDoublePress(doublePress_4);       //     -1 min/0.5s  auto dec. while holding 
  button1.setTripleClick(tripleClick_5);       //      Exit Setup                                   Enter Setup 
  button1.setTriplePress(triplePress_6);       //      next setup item                              Enter Setup
  button1.setRelease(release_7);               //      stop min/sec auto de/icrementing on release 

}


void click_1() {  // ✓
 sound_typ=11;
 Serial.println(F("CLICK"));
 switch (mod){
  case 0:  if( preset<NO_OF_QUICK_PRESETS-1){ preset++;                                          //toogle PRESETS OR CountTimeStopped
                                              preset=constrain(preset,0,NO_OF_QUICK_PRESETS-1); 
                                              P=preset+1;   // -2-
                                              dot(0,false);
                                              segment (3, 13, 6); 
                                              segment (2, P, 6);
                                              segment (1, 13, 6);
                                              show_type=4;
                                       }else{ preset=0;
                                              P=preset+1;   // -2-
                                              dot(0,false);
                                              segment (3, 13, 6); 
                                              segment (2, P, 6);
                                              segment (1, 13, 6);
                                              show_type=4;
                                               }   
            break;
            
  case 1:   mod=2;              // WT PLAY  --> WT PAUSE
           
            break;
            
  case 2:   mod=1;             //  WT PAUSE --> WT PLAY        
            break;
            
  case 3:   mod=4;             // RT PLAY  --> RT PAUSE
            
            break;
            
  case 4:   mod=3;             // RT PAUSE --> RT PLAY                       
            break;
            
  case 5:   mod=0;             //RAINBOW  --> STOP
            show_type=4;        
            break;
  case 6:                    // SETUP increment parameters in "RAM"
     switch(setup_item){
      case 0: mem_work_time += sec_increment_value;   
              break;
      case 1: mem_rest_time += sec_increment_value;   //2 p
              break;
      case 2: mem_rounds++; 
              break;
      case 3: mem_sig_typ ++;
              break;  

      default:  
              break;
    
  }
      break;
      
  case 7:   mod=8;   // CT PLAY  --> CT PAUSE
            break;
            
  case 8:   mod=7;   // CT PAUSE --> CT PLAY                   
            break;
            
  case 9:   mod=0;           // CT STOPPED
            show_type=4;
            P=preset+1;   // -1-
            dot(0,false);
            segment (3, 13, 6); 
            segment (2, P, 6);
            segment (1, 13, 6);
            break;
  
  
  default:  mod=0;
            break;
          }

} 

void press_2() {   // ✓
sound_typ=12;

   Serial.println(F("PRESS "));
 switch (mod){
  
  case 0:   mod=9;               // STOP  --> CUP
            break;
            
  case 1:   mod=2;               // WT PLAY  --> 
            break;
            
  case 2:   mod=1;               // WT PAUSE -->        
            break;
            
  case 3:   mod=4;               // RT PLAY  --> 
            break;
            
  case 4:   mod=1;               // RT PAUSE -->                        
            break;
            
  case 5:   mod=9;               //RAINBOW  --> CUP        
            break;
            
  case 6:   autoIncrement_ms.restart();    // SETUP autoincrement parameters in "RAM"
            increase=true;
            break;
            
  case 7:   mod=8;            // CT PLAY  --> CT PAUSE
            break;
            
  case 8:   mod=7;           // CT PAUSE --> CT PLAY                   
            break;
            
  case 9:   mod=0;           // CT STOPPED
            show_type=4;
            P=preset+1;   // -1-
            dot(0,false);
            segment (3, 13, 6); 
            segment (2, P, 6);
            segment (1, 13, 6);
            break;
  
  
  default:  mod=0;
            break;
          }
}

void doubleClick_3() {   // ✓
  sound_typ=13;
   Serial.println(F("DOUBLE_CLICK"));
    // This function will be called when the button was pressed 2 times in a short timeframe.

switch (mod){
  case 0:  mod=1;
           //buzzer_ms.restart();
           break; 
             
  case 1:  mod=0;         // WT_PLAY -->  STOPPED 
           show_type=4;
     
           break; 
                   
  case 2:  mod=0;         // WT_PAUSE -->  STOPPED 
           show_type=4;
     
           break;
           
  case 3:  mod=0;         // RT_PLAY -->  STOPPED 
           show_type=4;
           
           break;
           
  case 4:  mod=0;        // RT_PAUSE -->  STOPPED 
           show_type=4;
        
           break;
           
  case 5:  mod=0;        
           show_type=4;
           P=preset+1;   // -1-
           dot(0,false);
           segment (3, 13, 6); 
           segment (2, P, 6);
           segment (1, 13, 6);
           break;
           
  case 6:  switch(setup_item){ // SETUP decrement parameters in "RAM"
      
              case 0: mem_work_time -= sec_increment_value;
                      break;
              case 1: mem_rest_time -= sec_increment_value; 
                      break;        
              case 2: mem_rounds--; 
                      break;
              case 3: mem_sig_typ--;
                      break;  
              
              default:  
                       break; 
                       }
            break;

  case 7: mod=9;      // CT_PLAY --> CT_STOPPED 
          count_time=0;  
          break; 
               
  case 8: mod=9;     // CT_PAUSE -->  CT_STOPPED 
          count_time=0; 
          break;
          
  case 9: mod=7;    // CT_STOPPED -->  CT_PLAY
          break;
          
  default: mod=5;    // ANIMATE TO RAINBOW ;)
           break;
   }
} 

void doublePress_4() {  // X
   Serial.println(F("DOIBLE_PRESS"));
   sound_typ=14;
switch (mod){
  
  case 0:   mod=1;                // STOP  --> PLAY
            //buzzer_ms.restart();
            break;
            
  case 1:   mod=0;                // WT PLAY  --> STOP
            show_type=4;
            P=preset+1;   // -1-
            dot(0,false);
            segment (3, 13, 6); 
            segment (2, P, 6);
            segment (1, 13, 6);            
            break;
            
  case 2:   mod=9;               // WT PAUSE --> STOP     
            break;
            
  case 3:   mod=9;               // RT PLAY  --> CUP
            break;
            
  case 4:   mod=9;               // RT PAUSE --> CUP                       
            break;
            
  case 5:   mod=9;               //RAINBOW  --> CUP        
            break;
            
  case 6:   autoIncrement_ms.restart();                   // SETUP autoincrement parameters in "RAM"
            increase=false;
            break;
            
  case 7:   mod=9;            // CT PLAY  --> CT STOP
            count_time=0; 
            break;
            
  case 8:   mod=9;           // CT PAUSE --> CT STOP     
            count_time=0;               
            break;
            
  case 9:   mod=7;
            break;
  
  
  default:  mod=0;
            break;
          }
}
  
void tripleClick_5() {   // X
 Serial.println(F("TRIPLE_CLICK"));
 sound_typ=15;  
if (mod==6 ){ setup_item++; }else{mod=6;}
  
 if (setup_item==4){
    setup_item=0;
    write_eeprom=true;
    
    mod=0;                // SETUP  --> STOP
    show_type=4;
    P=preset+1;   // -1-
    dot(0,false);
    segment (3, 13, 6); 
    segment (2, P, 6);
    segment (1, 13, 6);   
  }
  
} 
      
void triplePress_6() {   // X
  sound_typ=16;
    Serial.println(F("TRIPLE_PRESS"));   
if (mod==6 ){ setup_item=0;
              write_eeprom=true;
              mod=0; }else{mod=6;}
             } 

void release_7() {    // X
  if(mod==6){
  sound_typ=17;
  Serial.println(F("RELEASED"));
  autoIncrement_ms.stop();
}}
