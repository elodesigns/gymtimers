void load_training_sets_from_matrix(){
   
   mem_work_time   = presets_matrix[preset][0];                //WT
   mem_rest_time   = presets_matrix[preset][1];                //RT
   mem_rounds      = presets_matrix[preset][2]/10;   //div10     ROUNDS                                 
   mem_sig_typ     = presets_matrix[preset][3]/10;   //div 10    sig_typ
   
   
   work_time      = mem_work_time;
   rest_time      = mem_rest_time; 
   rounds         = mem_rounds;
   sig_typ        = mem_sig_typ  ;
 
}

void store_training_sets_to_matrix(){
  
presets_matrix[preset][0] = mem_work_time ;
presets_matrix[preset][1] = mem_rest_time ;
presets_matrix[preset][2] = mem_rounds*10;           //prdct10
presets_matrix[preset][3] = mem_sig_typ*10;          //prdct10

}

void autoIncrement(bool inc){                               // auto increment parameters in "RAM"
  
  if(mod==6 && autoIncrement_ms.isRunning()){
   if (autoIncrement_ms.hasPassed(400)) {
       autoIncrement_ms.restart();  
        if(inc) {
         switch(setup_item){
      case 0: mem_work_time += min_increment_value;   
              break;
      case 1: mem_rest_time += min_increment_value;   //2 p
              break;
      case 2: mem_rounds++; 
              break;
      case 3: mem_sig_typ ++;
              break;  

      default:  
              break;
         }
      }else{
        switch(setup_item){
      case 0: mem_work_time -= min_increment_value;   
              break;
      case 1: mem_rest_time -= min_increment_value;   //2 p
              break;
      case 2: mem_rounds--; 
              break;
      case 3: mem_sig_typ --;
              break;  

      default:  
              break;
                            }
         }
      } } 
}
  

void setup_timer(){
  
  autoIncrement(increase);
  
  switch(setup_item){
      case 0: mem_work_time=constrain(mem_work_time,10,590);    //setup work time 
              work_time= mem_work_time;
              show_time(work_time,1); 
              dot(mod,true);
              break;
      
      case 1: mem_rest_time=constrain(mem_rest_time,10,590);    // setup rest time
              rest_time= mem_rest_time; 
              show_time(rest_time,3); 
              dot(mod,true);
              break;
      
      case 2: mem_rounds=constrain(mem_rounds,1,50);            // setup rounds
              rounds= mem_rounds; 
              show_time(rounds,9);
              segment (3, 12, 9);
              dot(mod,true);
              break;
       
       case 3: mem_sig_typ=constrain(mem_sig_typ,0,9);             // setup sig typ 
               sig_typ= mem_sig_typ; 
               segment (1, sig_typ, 5);
               segment (2, 8, OFF);
               segment (3, 14, 5);
               dot(mod,true);     
               break;

      default:  
       Serial.println(F("ERROR::setup_item>3"));
      break;
    }
}
