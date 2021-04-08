void change_timetable_value(int poz_x_lesson, int poz_y_lesson, int number_yachyki){
  
  delay(300);
  pisk();
  lcd.blink();
  int save_time = EEPROM.read(number_yachyki);

  while(digitalRead(button)){
    if(analogRead(y) > 750){

      if(poz_x_lesson == 2 or poz_x_lesson == 8){

        save_time++;
        if(save_time == 25){save_time = 1;}
        if(save_time < 10){lcd.print("0"); lcd.print(save_time); lcd.setCursor(poz_x_lesson, poz_y_lesson);}
        else{lcd.print(save_time); lcd.setCursor(poz_x_lesson, poz_y_lesson);}
    
      }

     if(poz_x_lesson == 5 or poz_x_lesson == 11){

        save_time++;
        if(save_time == 61){save_time = 0;}
        if(save_time < 10){lcd.print("0"); lcd.print(save_time); lcd.setCursor(poz_x_lesson, poz_y_lesson);}
        else{lcd.print(save_time); lcd.setCursor(poz_x_lesson, poz_y_lesson);}
    
      }
      
     pisk();
     delay(300);
     
    }

  if(analogRead(y) < 300){

      if(poz_x_lesson == 2 or poz_x_lesson == 8){

        save_time--;
        if(save_time == 0){save_time = 24;}
        if(save_time < 10){lcd.print("0"); lcd.print(save_time); lcd.setCursor(poz_x_lesson, poz_y_lesson);}
        else{lcd.print(save_time); lcd.setCursor(poz_x_lesson, poz_y_lesson);}
    
      }

     if(poz_x_lesson == 5 or poz_x_lesson == 11){

        save_time--;
        if(save_time == -1){save_time = 60;}
        if(save_time < 10){lcd.print("0"); lcd.print(save_time); lcd.setCursor(poz_x_lesson, poz_y_lesson);}
        else{lcd.print(save_time); lcd.setCursor(poz_x_lesson, poz_y_lesson);}
    
      }
      
     pisk(); 
     delay(300);
     
    }
     
  }
  
  if(save_time != EEPROM.read(number_yachyki)){EEPROM.write(number_yachyki, save_time);} 
  lcd.noBlink();
  pisk();
  delay(300);
  
}
