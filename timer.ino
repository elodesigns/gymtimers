
void Timer(){    

switch (mod){  
  case 0:   refresh_ms=800;  // STOPEDD
  break;
  case 1:   refresh_ms=995;  // WT_PLAY
  break;
  case 2:   refresh_ms=1;    // WT_PAUSED          
  break;
  case 3:   refresh_ms=995;  // RT_PLAY
  break;
  case 4:   refresh_ms=1;   // RT_PAUSED                          
  break;
  case 5:   refresh_ms=1;   //RAINBOW
  break;
  case 6:   refresh_ms=50;  //SETUP MODE
  break;
  case 7:   refresh_ms=995; //CT_PLAY
  break;
  case 8:   refresh_ms=1;  //CT_PAUSED
  break;
  case 9:   refresh_ms=1;  //CT_STOPPED
  break;
  default:  refresh_ms=1;  //Startup

  break;
          }

  
if (timer_ms.hasPassed(refresh_ms)) {
    timer_ms.restart(); 
 
switch (mod){

  
 case 0:   // STOPPED
   
  load_training_sets_from_matrix();
  
  if(show_type<4){show_type++;} else{show_type=0;}  
  
  switch (show_type){
    
  case 0:  preset=constrain(preset,0,NO_OF_QUICK_PRESETS-1); 
           P=preset+1;   // -2-
           dot(0,false);
           segment (3, 13, 6); 
           segment (2, P, 6);
           segment (1, 13, 6);
           break;
  
  case 1:  show_time(work_time,1);
           dot(1,false); 
           break;
  
  case 2:  show_time(rest_time,3);
           dot(3,false);
           break;

  case 3:  show_time(rounds,9);
           segment (3, 12, 9);
           dot(0,false);
           break;     
  case 4:  segment (1, sig_typ, 5);
           segment (2, 8, OFF);
           segment (3, 14, 5);
           dot(0,false);
           break;             
                    }
        break; //case 0

  case 1:    if(work_time>0) {   work_time--;    //PLAY WORK_TIME GREEN
                                 show_time(work_time,mod); 
                                 dot(mod,true);  

                                 
                          }else{  
                                 work_time= mem_work_time;
                                 mod=3;   
                             
                              }     
              break;

  case 2:   show_time(work_time,mod);                        //PAUSED WORK_TIME CIAN
            dot(mod,false);
            break;
  
  case 3:    if(rest_time>0) {  rest_time--;  //PLAY REST_TIME RED
                                show_time(rest_time,mod); 
                                dot(mod,true);
                                
                              //  if (rest_time==1){  buzzer_ms.restart(); }                           
                        }else{ 
                                rest_time= mem_rest_time;  
                                if(rounds==1){
                                              rounds= mem_rounds;  
                                              mod=5;
                                             
                                             
                                      }else{    rounds--;
                                                mod=1;}  
                                                   
                                           }  
            break;
 
  case 4:  show_time(rest_time,mod);                           //PAUSED REST_TIME ORANGE
           dot(mod,false);
           break;

  case 5:  //dot(5,false); 
           rainbowCycle(20);
           break;

  case 6:  setup_timer(); //SETUP
           break;

  case 7:   if(count_time<MAX_COUNT_UP_TIME) {     //CT PLAY PURPLE 1:23
                                 count_time++;
                                 dot(mod,true);
                                 show_time(count_time,mod);
     
                                 }else{ count_time=0;
                                        mod=5;}
            break;

  case 8:  show_time(count_time,mod);               // CT PAUSED :27
           dot(mod,false);
           break;

  case 9:     dot(7,false);
             if(count_time>0){ show_time(count_time,8);  // CT STOPPED 0:00
                         }else{ show_time(count_time,7);                       
                                segment (3, 0, 7); }
             break;
 
  default:  
  dot(0,false);
  animate(30, 1, ON, ON, ON);
  break;
          }
    }
}



  
void show_time(int time_s,byte color) {
  
 // time_s=constrain(time_s,0,35940);
 // hh:mm:ss   pos3 : pos2 pos 1
 
  int _s= (time_s % 60) % 10;
  int s_= (time_s % 60) / 10;
  int _m= (time_s / 60) % 10;
  int m_= ((time_s % 3600) / 60) /10;
  int _h= (time_s / 3600) % 10;
   
 if(time_s<599){     
  segment (1, _s, color);  //  segment(position, value_dec, color);
  segment (2, s_, color);
  if (_m == 0){color=OFF;}     
  segment (3, _m, color);  
  
 }else{
  segment (1, _m, color);
  segment (2, m_, color);
  segment (3, _h, color);
 }
}
