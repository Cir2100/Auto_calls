#include <LiquidCrystal_1602_RUS.h>
#include <EEPROM.h>
#include <Bounce2.h>
#include <iarduino_RTC.h>
#include <TimeLib.h>

iarduino_RTC time(RTC_DS1307); 
Bounce bouncer = Bounce();
// 127 - влево, 126 - вправо, 232 - корень, 218 - галочка, 165 - точка посередине 

//пищалка
const int pisk_pin = 53;


//пароль
int password = 0;
const int master_password = 1984; 
int pas_8 = 0, pas_9 = 0, pas_10 = 0, pas_11 = 0;

//ячейки ля пароля
const int thousend_yach = 20, houndred_yach = 21, dec_yach = 22, one_yach = 23;

//время для пренастройки
const int hourss = 10, minutess = 11, days = 12, months= 13, years_1 = 14, years_2 = 15, weekdays = 16;

//переменные для управления джостиком
const int x = A1, y = A2, button = 52;

//дисплей
const int rs = 51, en = 50, d4 = 49, d5 = 48, d6 = 47, d7 = 46;
LiquidCrystal_1602_RUS lcd(rs, en, d4, d5, d6, d7);

//батарейка
int chek_zarad = 0;

//для скролла
bool bottom = 0, top = 1;

//звонок
const int zvonok = 44;
bool otzvon_start = 0;
bool otzvon_end = 0;
int lesson_otzvon = 0;
unsigned long long old_check = 0;

//отмена звонков
const int yacheyka_otmena = 28;

//перенос звонков
const int yacheyka_perenos = 18, yacheyka_perenos30 = 24, yacheyka_perenos1 = 25;

//сокращенка
const int yacheyka_short = 19, yacheyka_short40 = 26, yacheyka_short35 = 27;

//меню
unsigned long long pressed_moment;

//вывод времени
int printing_hourss = 0;
int printing_minutess = 0;
unsigned long long miganie_double_point = 0;

//перезагрузка номер ячейки
const int yacheyka_reload = 17;

//пожарная тревога
const int pin_fire_alarm = A0;
int alarm_schet = 0;

//выводит границы урока на экран
void print_time_leson( int week_day, int  numder_of_lesson){

  int yacheyka = week_day * 10 + numder_of_lesson;
  int hour_start = EEPROM.read(1100 + yacheyka);
  int min_start = EEPROM.read(1200 + yacheyka);
  int hour_end = EEPROM.read(2100 + yacheyka);
  int min_end = EEPROM.read(2200 + yacheyka);

  lcd.print(numder_of_lesson);
  lcd.print(".");
  
  if (hour_start < 10){
    
    lcd.print("0");
    lcd.print(hour_start);
    lcd.print(":");
    
  }
  else {
    
    lcd.print(hour_start);
    lcd.print(":");
    
  }
  
  if (min_start < 10){
    
    lcd.print("0");
    lcd.print(min_start);
    lcd.print("-");
    
   }
  else {
    
    lcd.print(min_start);
    lcd.print("-");
    
  }
  
  if (hour_end < 10){ 
    
    lcd.print("0");
    lcd.print(hour_end);
    lcd.print(":");
    
   }
  else {
    
    lcd.print(hour_end);
    lcd.print(":");
    
  }
  
  if (min_end < 10){ 
    
    lcd.print("0");
    lcd.print(min_end);
    
   }
  else {
    
    lcd.print(min_end);
    
  }
  
}
//скроллит вверх
void scroll_top(int week_day){

    printing_hourss = 0;
    printing_minutess = 0;
  
    bottom = 0;
    top = 1;

    lcd.clear();
    lcd.setCursor(0, 0);
    print_time_leson(week_day, 1);
    lcd.setCursor(0, 1);
    print_time_leson(week_day, 2);
    lcd.setCursor(0, 2);
    print_time_leson(week_day, 3); 
    lcd.setCursor(0, 3);
    print_time_leson(week_day, 4); 
    
}
//скроллит вниз
void scroll_bottom(int week_day){

    printing_hourss = 0;
    printing_minutess = 0;

    bottom = 1;
    top = 0;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    print_time_leson(week_day, 5);
    lcd.setCursor(0, 1);
    print_time_leson(week_day, 6);
    lcd.setCursor(0, 2);
    print_time_leson(week_day, 7); 
    lcd.setCursor(0, 3);
    if (week_day != 6 and !EEPROM.read(yacheyka_short)){print_time_leson(week_day, 8);} 
    
}
//проверка скроллов
void scroll(int week_day){

  if(EEPROM.read(yacheyka_short40)){week_day = 7;}
  else if(EEPROM.read(yacheyka_short35)){week_day = 8;}
  
  if (analogRead(y) > 750 and !top){scroll_top(week_day); pisk();}

  if (analogRead(y) < 300 and !bottom){scroll_bottom(week_day); pisk();}
  
}
//выводит старую дату на экран
void print_old_date(){
  
  time.gettime();
  int hour_save = time.Hours;
  int min_save = time.minutes;
  int day_save =  time.day;
  int month_save = time.month;
  int year_save = time.year;
  year_save += 2000;
  
  String p_hour_save, p_min_save, p_day_save, p_month_save, p_year_save; 

  if (hour_save < 10){ p_hour_save = String("0" + String(hour_save));}
  else { p_hour_save = String(hour_save);}
  if (min_save < 10){ p_min_save = String("0" + String(min_save));}
  else {p_min_save = String(min_save);}
  if (day_save < 10){ p_day_save = String("0" + String(day_save));}
  else {p_day_save = String(day_save);}
  if (month_save < 10){ p_month_save = String("0" + String(month_save));}
  else { p_month_save = String(month_save);}
  if (year_save < 10){ p_year_save = String("0" + String(year_save));}
  else { p_year_save = String(year_save);}

  String old_date = String(p_hour_save + ":" + p_min_save + " " + p_day_save + "." + p_month_save + "." + p_year_save);
  lcd.setCursor(2, 1);
  lcd.print(old_date);

}
//выбор изменить дату или нет
void check_old_date(){

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print(L"Дата ");
  lcd.setCursor(9, 0);
  lcd.print(L"и время");
  lcd.setCursor(2, 2);
  print_old_date();
  lcd.setCursor(0, 3);
  lcd.print(L"Настроить");
  lcd.write(byte(127));
  lcd.setCursor(17, 3);
  lcd.write(byte(126));
  lcd.print(L"OK");

  while(chek_zarad){

    if (analogRead(x) < 490){
      
      pisk();
      check_password();   
      delay(300);
      if((pas_8 * 1000 + pas_9 * 100 + pas_10 * 10 + pas_11) == password or (pas_8 * 1000 + pas_9 * 100 + pas_10 * 10 + pas_11) == master_password){

        pisk();
        lcd.clear();
        lcd.setCursor(2, 1);
        print_old_date();
        set_date();
        
        }
      else{pisk_misstake(); break;}
      
      }
    if (analogRead(x) > 650){pisk(); break;}

  }
  
}
//ввод пароля
void check_password(){

  int poz_x = 8;

  pas_8 = 0; 
  pas_9 = 0; 
  pas_10 = 0; 
  pas_11 = 0;

  lcd.setCursor(1, 0);
  lcd.print(L"Введите пароль");
  lcd.clear();
  lcd.setCursor(8, 1);
  lcd.print("0000");
  lcd.setCursor(9,3);
  lcd.print(L"OK");
  lcd.setCursor(8, 1);
  lcd.cursor();

  while(digitalRead(button)){

    if (analogRead(x) < 490 and poz_x > 8){

      poz_x--;
      lcd.setCursor(poz_x, 1);
      pisk();
      delay(300);
      
      }
      
    if (analogRead(x) > 650 and poz_x < 11){
      
      poz_x++;
      lcd.setCursor(poz_x, 1);
      pisk();
      delay(300);
      
      }
      
    if (analogRead(y) > 750){

      if(poz_x == 8){

        if(pas_8 == 9){
          
          pas_8 = 0;
          lcd.print(pas_8);
          lcd.setCursor(poz_x, 1);
          
        }
        else {
          
          pas_8++;
          lcd.print(pas_8);
          lcd.setCursor(poz_x, 1);
          
        }
        
      }

      if(poz_x == 9){

        if(pas_9 == 9){
          
          pas_9 = 0;
          lcd.print(pas_9);
          lcd.setCursor(poz_x, 1);
          
        }
        else {
          
          pas_9++;
          lcd.print(pas_9);
          lcd.setCursor(poz_x, 1);
          
        }
        
      }

      if(poz_x == 10){

        if(pas_10 == 9){
          
          pas_10 = 0;
          lcd.print(pas_10);
          lcd.setCursor(poz_x, 1);
          
        }
        else {
          
          pas_10++;;
          lcd.print(pas_10);
          lcd.setCursor(poz_x, 1);
          
        }
        
      }

      if(poz_x == 11){

        if(pas_11 == 9){
          
          pas_11 = 0;
          lcd.print(pas_11);
          lcd.setCursor(poz_x, 1);
          
        }
        else {
          
          pas_11++;
          lcd.print(pas_11);
          lcd.setCursor(poz_x, 1);
          
        }
        
      }

      pisk();
      delay(300);
      
      }
      
    if (analogRead(y) < 300){

      if(poz_x == 8){

        if(pas_8 == 0){
          
          pas_8 = 9;
          lcd.print(pas_8);
          lcd.setCursor(poz_x, 1);
          
        }
        else {
          
          pas_8--;
          lcd.print(pas_8);
          lcd.setCursor(poz_x, 1);
          
        }
        
      }

      if(poz_x == 9){

        if(pas_9 == 0){
          
          pas_9 = 9;
          lcd.print(pas_9);
          lcd.setCursor(poz_x, 1);
          
        }
        else {
          
          pas_9--;
          lcd.print(pas_9);
          lcd.setCursor(poz_x, 1);
          
        }
        
      }

      if(poz_x == 10){

        if(pas_10 == 0){
          
          pas_10 = 9;
          lcd.print(pas_10);
          lcd.setCursor(poz_x, 1);
          
        }
        else {
          
          pas_10--;;
          lcd.print(pas_10);
          lcd.setCursor(poz_x, 1);
          
        }
        
      }

      if(poz_x == 11){

        if(pas_11 == 0){
          
          pas_11 = 9;
          lcd.print(pas_11);
          lcd.setCursor(poz_x, 1);
          
        }
        else {
          
          pas_11--;
          lcd.print(pas_11);
          lcd.setCursor(poz_x, 1);
          
        }
        
      }
      
      pisk();
      delay(300);
      
      }
    
  }

 lcd.noCursor();
  
}
//установка даты
void set_date(){
  
  lcd.setCursor(9, 3);
  lcd.print(L"ОК");
  lcd.setCursor(2, 1);
  lcd.cursor();
  
  time.gettime();
  int hour_save = time.Hours;
  int min_save = time.minutes;
  int day_save =  time.day;
  int month_save = time.month;
  int year_save = time.year;
  year_save += 2000;
Serial.print(year_save);
  int poz_x = 2, poz_hourss = 2, poz_minutess = 5, poz_days = 8, poz_months = 11, poz_years = 14;

  while(true){
    
    if(!digitalRead(button)){
      setTime(hour_save, min_save, 0, day_save, month_save, year_save);
      time.settime(0, min_save, hour_save, day_save, month_save, year_save, weekday() - 1);
      chek_zarad = 0;
      lcd.noCursor();
      pisk();
      break;
      
      }
      
    if(analogRead(x) > 650){
      
      if(poz_x == poz_months){
        
        poz_x = poz_years; 
        lcd.setCursor(poz_x, 1);
        pisk();
        delay(300);
        
        }
      if(poz_x == poz_days){
        
        poz_x = poz_months;
        lcd.setCursor(poz_x, 1);
        pisk();
        delay(300);
        
        }
      if(poz_x == poz_minutess){
        
        poz_x = poz_days;
        lcd.setCursor(poz_x, 1);
        pisk();
        delay(300);
        
        }
      if(poz_x == poz_hourss){
        
        poz_x = poz_minutess;
        lcd.setCursor(poz_x, 1);
        pisk();
        delay(300);
        
        }
      
      }

    if(analogRead(x) < 490){
      
      if(poz_x == poz_minutess){
        
        poz_x = poz_hourss;
        lcd.setCursor(poz_x, 1);
        pisk();
        delay(300);
        
        }
      if(poz_x == poz_days){
        
        poz_x = poz_minutess;
        lcd.setCursor(poz_x, 1);
        pisk();
        delay(300);
        
        }
      if(poz_x == poz_months){
        
        poz_x = poz_days;
        lcd.setCursor(poz_x, 1);
        pisk();
        delay(300);
        
        }
      if(poz_x == poz_years){
        
        poz_x = poz_months;
        lcd.setCursor(poz_x, 1);
        pisk();
        delay(300);
        
        }
      
      }
    if(analogRead(y) > 750)  {

       if(poz_x == poz_hourss){
        if(hour_save == 23){hour_save = -1;}
        hour_save++;
        
        if(hour_save < 10){lcd.print("0"); lcd.print(hour_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(hour_save); lcd.setCursor(poz_x, 1);}

       }

       if(poz_x == poz_minutess){
        if(min_save >= 60){min_save = -1;}
        min_save++;
        
        if(min_save < 10){lcd.print("0"); lcd.print(min_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(min_save); lcd.setCursor(poz_x, 1); Serial.println(min_save);}

       }

       if(poz_x == poz_days){
        if(day_save == 31){day_save = 0;}
        day_save++;
        
        if(day_save < 10){lcd.print("0"); lcd.print(day_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(day_save); lcd.setCursor(poz_x, 1);}
        
       }

       if(poz_x == poz_months){
        
        if(month_save == 12){month_save = 0;}
        month_save++;
        
        if(month_save < 10){lcd.print("0"); lcd.print(month_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(month_save); lcd.setCursor(poz_x, 1);}

       }

       if(poz_x == poz_years){

        year_save++;
        if(year_save < 10){lcd.print("000"); lcd.print(year_save); lcd.setCursor(poz_x, 1);}
        if(year_save < 100 and year_save > 10){lcd.print("00"); lcd.print(year_save); lcd.setCursor(poz_x, 1);}
        if(year_save < 1000 and year_save > 100){lcd.print("0"); lcd.print(year_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(year_save); lcd.setCursor(poz_x, 1);}
        

       }

      pisk();
      delay(300);
       
    }

    if(analogRead(y) < 300)  {

       if(poz_x == poz_hourss){
        if(hour_save == 0){hour_save = 24;}
        hour_save--;
        
        if(hour_save < 10){lcd.print("0"); lcd.print(hour_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(hour_save); lcd.setCursor(poz_x, 1);}

       }

       if(poz_x == poz_minutess){
        if(min_save == 0){min_save = 61;}
        min_save--;
        
        if(min_save < 10){lcd.print("0"); lcd.print(min_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(min_save); lcd.setCursor(poz_x, 1); Serial.println(min_save);}

       }

       if(poz_x == poz_days){
        if(day_save == 1){day_save = 32;}
        day_save--;
        
        if(day_save < 10){lcd.print("0"); lcd.print(day_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(day_save); lcd.setCursor(poz_x, 1);}
        
       }

       if(poz_x == poz_months){
        
        if(month_save == 1){month_save = 13;}
        month_save--;
        
        if(month_save < 10){lcd.print("0"); lcd.print(month_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(month_save); lcd.setCursor(poz_x, 1);}

       }

       if(poz_x == poz_years){

        year_save--;
        if(year_save < 10){lcd.print("000"); lcd.print(year_save); lcd.setCursor(poz_x, 1);}
        if(year_save < 100 and year_save > 10){lcd.print("00"); lcd.print(year_save); lcd.setCursor(poz_x, 1);}
        if(year_save < 1000 and year_save > 100){lcd.print("0"); lcd.print(year_save); lcd.setCursor(poz_x, 1);}
        else{lcd.print(year_save); lcd.setCursor(poz_x, 1);}

       }

      pisk();
      delay(300);
       
    }
    
  }
  
}
//звонок
void zvon(){
  
  lcd.clear();
  lcd.setCursor(7, 1);
  lcd.print(L"ЗВЕНИТ");
  pisk();
  digitalWrite(zvonok, HIGH);
  delay(3000);
  digitalWrite(zvonok, LOW);
  delay(5000);
  digitalWrite(zvonok, HIGH);
  delay(1000);
  digitalWrite(zvonok, LOW);
  delay(1000);
  digitalWrite(zvonok, HIGH);
  delay(1000);
  digitalWrite(zvonok, LOW);
  print_lesson_stack(time.weekday);
  Check_tochka(time.weekday);
  
  
}
//проверка на подачу звонка
void Check_zvonok(int week_day){

  if(EEPROM.read(yacheyka_short40)){week_day = 7;}
  else if(EEPROM.read(yacheyka_short35)){week_day = 8;}

 if (millis() - old_check >= 10000){

    old_check = millis();
    int count_lessons = 8;
    if(time.weekday == 6){count_lessons = 7;}
    //переделать фалс разделить его
    for(int i = 1; i <= count_lessons;i++){
      if(((time.Hours == EEPROM.read(1100 + week_day * 10 + i)) and (time.minutes == EEPROM.read(1200 + week_day * 10 + i)))
      and (!otzvon_start)){

          zvon();

          otzvon_start = true;
          lesson_otzvon = i;
      
        }

      if((((time.Hours == EEPROM.read(2100 + week_day * 10 + i)) and (time.minutes == EEPROM.read(2200 + week_day * 10 + i))))
      and (!otzvon_end)){
      
          zvon();

          otzvon_end = true;
          lesson_otzvon = i;
      
        }
    

        if(((time.Hours != EEPROM.read(1100 + week_day * 10 + lesson_otzvon)) and (time.minutes == EEPROM.read(1200 + week_day * 10 + lesson_otzvon)))
        and (otzvon_start)){

          otzvon_start = false;
      
        }

      if((((time.Hours != EEPROM.read(2100 + week_day * 10 + lesson_otzvon)) and (time.minutes == EEPROM.read(2200 + week_day * 10 + lesson_otzvon))))
      and (otzvon_end)){

        otzvon_end = false;
      
      }
  }
 }
    
}
//провека на печать точек
void Check_tochka(int week_day){

  if(EEPROM.read(yacheyka_short40)){week_day = 7;}
  else if(EEPROM.read(yacheyka_short35)){week_day = 8;}
    
    int count_lessons = 8;
    if(weekday() - 1 == 6){count_lessons = 7;}
    
    if(top){
    for(int i = 1; i <= 4;i++){
      if((time.Hours > EEPROM.read(1100 + week_day * 10 + i)) 
      or ((time.Hours == EEPROM.read(1100 + week_day * 10 + i)) and (time.minutes >= EEPROM.read(1200 + week_day * 10 + i))))
      {
      
          lcd.setCursor(13, i - 1);
          lcd.write(byte(165));
          
        }

      if((time.Hours > EEPROM.read(2100 + week_day * 10 + i))
      or ((time.Hours == EEPROM.read(2100 + week_day * 10 + i)) and (time.minutes >= EEPROM.read(2200 + week_day * 10 + i))))
      {
      
          lcd.setCursor(14, i - 1);
          lcd.write(byte(165));
          
        }
       
  }
  }

    if(bottom){
    for(int i = 5; i <= count_lessons;i++){
      if((time.Hours > EEPROM.read(1100 + week_day * 10 + i))
      or ((time.Hours == EEPROM.read(1100 + week_day * 10 + i)) and (time.minutes >= EEPROM.read(1200 + week_day * 10 + i))))
      {
      
          lcd.setCursor(13, i - 5);
          lcd.write(byte(165));
          
        }

      if((time.Hours > EEPROM.read(2100 + week_day * 10 + i))
      or ((time.Hours == EEPROM.read(2100 + week_day * 10 + i)) and (time.minutes >= EEPROM.read(2200 + week_day * 10 + i))))
      {
      
          lcd.setCursor(14, i - 5);
          lcd.write(byte(165));
          
        }
       
  }
    }
  
}
//вывод меню
void print_menu(int plus_menu){

  lcd.clear();

  if(plus_menu == 0){
    lcd.setCursor(0, 0);
    lcd.print(L"1.НАСТРОИТЬ ВРЕМЯ");
    lcd.setCursor(0, 1);
    lcd.print(L"2.НАСТРОИТЬ ЗВОНКИ");
    lcd.setCursor(0, 2);
    lcd.print(L"3.ПЕРЕЗАГРУЗКА");
    lcd.setCursor(0, 3);
    lcd.print(L"4.ТЕСТ ЗВОНКА");
  }

  if(plus_menu == 4){
    lcd.setCursor(0, 0);
    lcd.print(L"5.ИЗМЕНИТЬ ПАРОЛЬ");
    lcd.setCursor(0, 1);
    lcd.print(L"6.ИСХОДНЫЕ НАСТРОЙКИ");
    lcd.setCursor(0, 2);
    lcd.print(L"7.ОТМЕНА ЗВОНКОВ");
    lcd.setCursor(0, 3);
    lcd.print(L"8.СОКРАТИТЬ ЗВОНКИ");
  }
 if(plus_menu == 8){
    lcd.setCursor(0, 0);
    lcd.print(L"9.ПЕРЕНЕСТИ ЗВОНКИ");
    lcd.setCursor(0, 1);
    lcd.print(L"10.ВЫХОД");
 }
  
}
//выбор пунктов меню
void menu(){
   
  int poz_y = 0;
  int plus_menu = 0;
  
  print_menu(plus_menu);
  
  lcd.setCursor(0, poz_y);
  lcd.cursor();

  while(digitalRead(button)){

    if (analogRead(y) < 300){

      poz_y++;
      if(poz_y == 4){
        
        if(plus_menu == 0){plus_menu = 4; print_menu(plus_menu);} 
        else if(plus_menu == 4){plus_menu = 8; print_menu(plus_menu);}      
        poz_y = 0;
        
        }
      if(poz_y == 2 and plus_menu == 8){
        
        plus_menu = 0; 
        print_menu(plus_menu);
        poz_y = 0;
      }
        
      lcd.setCursor(0, poz_y);
      pisk();
      delay(300);
      
      }
    if (analogRead(y) > 750){
      
      poz_y--;
      if(poz_y == -1){
        
        if(plus_menu == 0){plus_menu = 8; print_menu(plus_menu); poz_y = 1;} 
        else if(plus_menu == 4){plus_menu = 0; print_menu(plus_menu); poz_y = 3;}  
        
        }

      if(poz_y == -1 and plus_menu == 8){
        
        plus_menu = 4; 
        print_menu(plus_menu);
        poz_y = 3;
      }
        
      lcd.setCursor(0, poz_y);
      pisk();
      delay(300);
      
      }
    
  }
  
  pisk();
  delay(300);

  lcd.noCursor(); 
  if(poz_y + plus_menu == 0){setting_time();}
  if(poz_y + plus_menu == 1){setting_timetable();}
  if(poz_y + plus_menu == 2){reload();}
  if(poz_y + plus_menu == 3){test_zvonok();}
  if(poz_y + plus_menu == 4){change_password();}
  if(poz_y + plus_menu == 5){initial_setup();}
  if(poz_y + plus_menu == 6){otmena_zvonki();}
  if(poz_y + plus_menu == 7){
    
    if(!EEPROM.read(yacheyka_short)){short_timetable();}
    else if(EEPROM.read(yacheyka_short)){canel_short_timetable();}
    }
  if(poz_y + plus_menu == 8){
    
    if(!EEPROM.read(yacheyka_perenos)){transfer_timetable();}
    else if(EEPROM.read(yacheyka_perenos)){canel_transfer_timetable();}
    }
  if(poz_y + plus_menu == 9){}//exit
   
}
//вывод принятия обычного расписания
void print_choise_timetable(){
  
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("ВКЛЮЧИТЬ ОБЫЧНОЕ"); 
  lcd.setCursor(5,2);
  lcd.print("РАСПИСАНИЕ");  
  lcd.setCursor(0, 3);
  lcd.print("НЕТ");
  lcd.write(byte(127));
  lcd.setCursor(17, 3);
  lcd.write(byte(126));
  lcd.print("ОК");
  
}
//отмена короткого расписания
void canel_short_timetable(){
  
  print_choise_timetable();

  while(true){
    
    if (analogRead(x) < 490){pisk(); break;}
    if (analogRead(x) > 650){
      
      EEPROM.write(yacheyka_short, 0);
      EEPROM.write(yacheyka_short35, 0);
      EEPROM.write(yacheyka_short40, 0);
      pisk();
      break;
      
      }
  }
  
  
  }
//отмена переноса расписания
void canel_transfer_timetable(){
  
  print_choise_timetable();

  while(true){
    
    if (analogRead(x) < 490){pisk(); break;}
    if (analogRead(x) > 650){
      
      EEPROM.write(yacheyka_perenos, 0);
      if(EEPROM.read(yacheyka_perenos1)){EEPROM.write(yacheyka_perenos1, 0); transfer_1_hour(-1);}
      else if(EEPROM.read(yacheyka_perenos30)){EEPROM.write(yacheyka_perenos30, 0); transfer_30_mins(-30);}
      pisk();
      break;
      
      }
  }
  
}
//выбор переноса расписания
void transfer_timetable(){

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(L"ПЕРЕНЕСТИ УРОКИ");
  lcd.setCursor(9, 2);
  lcd.print(L"ОК");
  lcd.setCursor(0, 3);
  lcd.print(L"30 МИН");
  lcd.write(byte(127));
  lcd.setCursor(8, 3);
  lcd.print(L"НАЗАД");
  lcd.setCursor(14, 3);
  lcd.write(byte(126));
  lcd.print(L"1  ЧАС");
    
  while(true){

    if(!digitalRead(button)){pisk(); break;}
    else if (analogRead(x) < 490){
      
      pisk();
      transfer_30_mins(30);
      EEPROM.write(yacheyka_perenos, 1);
      break;
      
      }
    
   else if (analogRead(x) > 650){
      
      pisk();
      transfer_1_hour(1);
      EEPROM.write(yacheyka_perenos, 1);
      break;
      
      } 
     
    }
    
  
}
//перенос на 30 мин
void transfer_30_mins(int perenos){

  EEPROM.write(yacheyka_perenos30, 1);
  
  int count_lessons = 8;
  int save_min = 0;
  int j = 1;
  int days = 6;
  if(EEPROM.read(yacheyka_short40)){j = 7; days = 7;}
  if(EEPROM.read(yacheyka_short35)){j = 8; days = 8;}
  
  for(j; j <= days; j++){

    if(j >= 6){count_lessons = 7;}
  
    for(int i = 1; i <= count_lessons; i++){

      save_min = EEPROM.read(1200 + j * 10 + i) + perenos;
      if(save_min >= 60){

         save_min -=60;
         EEPROM.write(1100 + j * 10 + i, EEPROM.read(1100 + j * 10 + i) + 1);
      }
      else if(save_min < 0){

         save_min +=60;
         EEPROM.write(1100 + j * 10 + i, EEPROM.read(1100 + j * 10 + i) - 1);
      }
      EEPROM.write(1200 + j * 10 + i, save_min);
      
      save_min = EEPROM.read(2200 + j * 10 + i) + perenos;
      if(save_min >= 60){

         save_min -=60;
         EEPROM.write(2100 + j * 10 + i, EEPROM.read(2100 + j * 10 + i) + 1);
      }
      else if(save_min < 0){

         save_min +=60;
         EEPROM.write(2100 + j * 10 + i, EEPROM.read(2100 + j * 10 + i) - 1);
      }
      EEPROM.write(2200 + j * 10 + i, save_min);
    
    }
    
  }
  
}
//перенос на 1 час
void transfer_1_hour(int perenos){

  EEPROM.write(yacheyka_perenos1, 1);
  
  int count_lessons = 8;
  int j = 1;
  int days = 6;
  if(EEPROM.read(yacheyka_short40)){j = 7; days = 7;}
  if(EEPROM.read(yacheyka_short35)){j = 8; days = 8;}

  for(j; j <= days; j++){

    if(j >= 6){count_lessons = 7;}
  
    for(int i = 1; i <= count_lessons; i++){

      EEPROM.write(1100 + j * 10 + i, EEPROM.read(1100 + j * 10 + i) + perenos);
      EEPROM.write(2100 + j * 10 + i, EEPROM.read(2100 + j * 10 + i) + perenos);
    
    }
    
  }
  
}
//выбор сокращенного расписания
void short_timetable(){

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(L"СОКРАТИТЬ УРОКИ");
  lcd.setCursor(9, 2);
  lcd.print(L"ОК");
  lcd.setCursor(0, 3);
  lcd.print(L"35 МИН");
  lcd.write(byte(127));
  lcd.setCursor(8, 3);
  lcd.print(L"НАЗАД");
  lcd.setCursor(14, 3);
  lcd.write(byte(126));
  lcd.print(L"40МИН");
    
  while(true){

    if(!digitalRead(button)){pisk(); break;}
    else if (analogRead(x) < 490){
      
      pisk();
      short_mins(35);
      EEPROM.write(yacheyka_short, 1);
      break;
      
      }
    
   else if (analogRead(x) > 650){
      
      pisk();
      short_mins(40);
      EEPROM.write(yacheyka_short, 1);
      break;
      
      } 
     
    }
    
  
}
//функция сокращения
void short_mins(int shorts){
  
  if(shorts == 40){EEPROM.write(yacheyka_short40, 1); EEPROM.write(yacheyka_short35, 0);}
  else if(shorts == 35){EEPROM.write(yacheyka_short40, 0); EEPROM.write(yacheyka_short35, 1);}
  
}
//отмена звонка
void otmena_zvonki(){

  lcd.clear();
  
  if(!EEPROM.read(yacheyka_otmena)){
    
    lcd.setCursor(1, 1);
    lcd.print("ОТМЕНИТЬ ЗВОНКИ?");
    lcd.setCursor(0, 3);
    lcd.print(L"НЕТ");
    lcd.write(byte(127));
    lcd.setCursor(17, 3);
    lcd.write(byte(126));
    lcd.print(L"OK");

    while(true){
      
      if (analogRead(x) < 490){pisk(); break;}
      if (analogRead(x) > 650){
        
        pisk(); 
        EEPROM.write(yacheyka_otmena, 1);
        break;
        
        }
      
    }
    
  }

 else if(EEPROM.read(yacheyka_otmena)){
 
    lcd.setCursor(1, 1);
    lcd.print("ВКЛЮЧИТЬ ЗВОНКИ?");
    lcd.setCursor(0, 3);
    lcd.print(L"НЕТ");
    lcd.write(byte(127));
    lcd.setCursor(17, 3);
    lcd.write(byte(126));
    lcd.print(L"OK");

    while(true){
      
      if (analogRead(x) < 490){pisk(); break;}
      if (analogRead(x) > 650){
        
        pisk(); 
        EEPROM.write(yacheyka_otmena, 0); 
        break;
        
        }
      
    }
  
 }
  
}
//заводские настройки
void initial_setup(){

  // a - 1 - начало, 2 - конец
  // b - 1 - часы, 2 - минуты
  // c - день недели
  // d - № урока

  // 1 урок пн
  EEPROM.write(1111, 8);
  EEPROM.write(1211, 30);
  EEPROM.write(2111, 9);
  EEPROM.write(2211, 15);

  // 2 урок пн
  EEPROM.write(1112, 9);
  EEPROM.write(1212, 30);
  EEPROM.write(2112, 10);
  EEPROM.write(2212, 15);
  
  // 3 урок пн
  EEPROM.write(1113, 10);
  EEPROM.write(1213, 30);
  EEPROM.write(2113, 11);
  EEPROM.write(2213, 15);

  // 4 урок пн
  EEPROM.write(1114, 11);
  EEPROM.write(1214, 35);
  EEPROM.write(2114, 12);
  EEPROM.write(2214, 20);

  // 5 урок пн
  EEPROM.write(1115, 12);
  EEPROM.write(1215, 40);
  EEPROM.write(2115, 13);
  EEPROM.write(2215, 25);

  // 6 урок пн
  EEPROM.write(1116, 13);
  EEPROM.write(1216, 35);
  EEPROM.write(2116, 14);
  EEPROM.write(2216, 20);

  // 7 урок пн
  EEPROM.write(1117, 14);
  EEPROM.write(1217, 30);
  EEPROM.write(2117, 15);
  EEPROM.write(2217, 15);

  // 8 урок пн
  EEPROM.write(1118, 15);
  EEPROM.write(1218, 20);
  EEPROM.write(2118, 16);
  EEPROM.write(2218, 00);


  // 1 урок вт
  EEPROM.write(1121, 8);
  EEPROM.write(1221, 30);
  EEPROM.write(2121, 9);
  EEPROM.write(2221, 15);

  // 2 урок вт
  EEPROM.write(1122, 9);
  EEPROM.write(1222, 30);
  EEPROM.write(2122, 10);
  EEPROM.write(2222, 15);
  
  // 3 урок вт
  EEPROM.write(1123, 10);
  EEPROM.write(1223, 30);
  EEPROM.write(2123, 11);
  EEPROM.write(2223, 15);

  // 4 урок вт
  EEPROM.write(1124, 11);
  EEPROM.write(1224, 35);
  EEPROM.write(2124, 12);
  EEPROM.write(2224, 20);

  // 5 урок вт
  EEPROM.write(1125, 12);
  EEPROM.write(1225, 40);
  EEPROM.write(2125, 13);
  EEPROM.write(2225, 25);

  // 6 урок вт
  EEPROM.write(1126, 13);
  EEPROM.write(1226, 35);
  EEPROM.write(2126, 14);
  EEPROM.write(2226, 20);

  // 7 урок вт
  EEPROM.write(1127, 14);
  EEPROM.write(1227, 30);
  EEPROM.write(2127, 15);
  EEPROM.write(2227, 15);

  // 8 урок вт
  EEPROM.write(1128, 15);
  EEPROM.write(1228, 20);
  EEPROM.write(2128, 16);
  EEPROM.write(2228, 00);

  

  // 1 урок ср
  EEPROM.write(1131, 8);
  EEPROM.write(1231, 30);
  EEPROM.write(2131, 9);
  EEPROM.write(2231, 15);

  // 2 урок ср
  EEPROM.write(1132, 9);
  EEPROM.write(1232, 30);
  EEPROM.write(2132, 10);
  EEPROM.write(2232, 15);
  
  // 3 урок ср
  EEPROM.write(1133, 10);
  EEPROM.write(1233, 30);
  EEPROM.write(2133, 11);
  EEPROM.write(2233, 15);

  // 4 урок ср
  EEPROM.write(1134, 11);
  EEPROM.write(1234, 35);
  EEPROM.write(2134, 12);
  EEPROM.write(2234, 20);

  // 5 урок ср
  EEPROM.write(1135, 12);
  EEPROM.write(1235, 40);
  EEPROM.write(2135, 13);
  EEPROM.write(2235, 25);

  // 6 урок ср
  EEPROM.write(1136, 13);
  EEPROM.write(1236, 35);
  EEPROM.write(2136, 14);
  EEPROM.write(2236, 20);

  // 7 урок ср
  EEPROM.write(1137, 14);
  EEPROM.write(1237, 30);
  EEPROM.write(2137, 15);
  EEPROM.write(2237, 15);

  // 8 урок ср
  EEPROM.write(1138, 15);
  EEPROM.write(1238, 20);
  EEPROM.write(2138, 16);
  EEPROM.write(2238, 00);

  

// 1 урок чт
  EEPROM.write(1141, 8);
  EEPROM.write(1241, 30);
  EEPROM.write(2141, 9);
  EEPROM.write(2241, 15);

  // 2 урок чт
  EEPROM.write(1142, 9);
  EEPROM.write(1242, 30);
  EEPROM.write(2142, 10);
  EEPROM.write(2242, 15);
  
  // 3 урок чт
  EEPROM.write(1143, 10);
  EEPROM.write(1243, 30);
  EEPROM.write(2143, 11);
  EEPROM.write(2243, 15);

  // 4 урок чт
  EEPROM.write(1144, 11);
  EEPROM.write(1244, 35);
  EEPROM.write(2144, 12);
  EEPROM.write(2244, 20);

  // 5 урок чт
  EEPROM.write(1145, 12);
  EEPROM.write(1245, 40);
  EEPROM.write(2145, 13);
  EEPROM.write(2245, 25);

  // 6 урок чт
  EEPROM.write(1146, 13);
  EEPROM.write(1246, 35);
  EEPROM.write(2146, 14);
  EEPROM.write(2246, 20);

  // 7 урок чт
  EEPROM.write(1147, 14);
  EEPROM.write(1247, 30);
  EEPROM.write(2147, 15);
  EEPROM.write(2247, 15);

  // 8 урок чт
  EEPROM.write(1148, 15);
  EEPROM.write(1248, 20);
  EEPROM.write(2148, 16);
  EEPROM.write(2248, 00);

  

  // 1 урок пт
  EEPROM.write(1151, 8);
  EEPROM.write(1251, 30);
  EEPROM.write(2151, 9);
  EEPROM.write(2251, 10);

  // 2 урок пт
  EEPROM.write(1152, 9);
  EEPROM.write(1252, 25);
  EEPROM.write(2152, 10);
  EEPROM.write(2252, 5);

  // 3 урок пт
  EEPROM.write(1153, 10);
  EEPROM.write(1253, 20);
  EEPROM.write(2153, 11);
  EEPROM.write(2253, 0);

  // 4 урок пт
  EEPROM.write(1154, 11);
  EEPROM.write(1254, 20);
  EEPROM.write(2154, 12);
  EEPROM.write(2254, 0);

  // 5 урок пт (классный час)
  EEPROM.write(1155, 12);
  EEPROM.write(1255, 20);
  EEPROM.write(2155, 12);
  EEPROM.write(2255, 50);

  // 6 урок пт
  EEPROM.write(1156, 13);
  EEPROM.write(1256, 0);
  EEPROM.write(2156, 13);
  EEPROM.write(2256, 40);

  // 7 урок пт
  EEPROM.write(1157, 13);
  EEPROM.write(1257, 50);
  EEPROM.write(2157, 14);
  EEPROM.write(2257, 30);

  // 8 урок пт
  EEPROM.write(1158, 14);
  EEPROM.write(1258, 40);
  EEPROM.write(2158, 15);
  EEPROM.write(2258, 20);


  // 1 урок сб
  EEPROM.write(1161, 8);
  EEPROM.write(1261, 30);
  EEPROM.write(2161, 9);
  EEPROM.write(2261, 10);

  // 2 урок сб
  EEPROM.write(1162, 9);
  EEPROM.write(1262, 20);
  EEPROM.write(2162, 10);
  EEPROM.write(2262, 0);

  // 3 урок сб
  EEPROM.write(1163, 10);
  EEPROM.write(1263, 10);
  EEPROM.write(2163, 10);
  EEPROM.write(2263, 50);

  // 4 урок сб
  EEPROM.write(1164, 11);
  EEPROM.write(1264, 0);
  EEPROM.write(2164, 11);
  EEPROM.write(2264, 40);

  // 5 урок сб
  EEPROM.write(1165, 11);
  EEPROM.write(1265, 50);
  EEPROM.write(2165, 12);
  EEPROM.write(2265, 30);

  // 6 урок сб
  EEPROM.write(1166, 12);
  EEPROM.write(1266, 40);
  EEPROM.write(2166, 13);
  EEPROM.write(2266, 20);

  // 7 урок сб
  EEPROM.write(1167, 13);
  EEPROM.write(1267, 30);
  EEPROM.write(2167, 14);
  EEPROM.write(2267, 10);

  

  //сокращенка 40 мин

  // 1 урок 
  EEPROM.write(1171, 8);
  EEPROM.write(1271, 30);
  EEPROM.write(2171, 9);
  EEPROM.write(2271, 10);

  // 2 урок 
  EEPROM.write(1172, 9);
  EEPROM.write(1272, 25);
  EEPROM.write(2172, 10);
  EEPROM.write(2272, 05);
  
  // 3 урок 
  EEPROM.write(1173, 10);
  EEPROM.write(1273, 20);
  EEPROM.write(2173, 11);
  EEPROM.write(2273, 00);

  // 4 урок 
  EEPROM.write(1174, 11);
  EEPROM.write(1274, 20);
  EEPROM.write(2174, 12);
  EEPROM.write(2274, 00);

  // 5 урок 
  EEPROM.write(1175, 12);
  EEPROM.write(1275, 20);
  EEPROM.write(2175, 13);
  EEPROM.write(2275, 00);

  // 6 урок 
  EEPROM.write(1176, 13);
  EEPROM.write(1276, 10);
  EEPROM.write(2176, 13);
  EEPROM.write(2276, 50);

  // 7 урок 
  EEPROM.write(1177, 14);
  EEPROM.write(1277, 00);
  EEPROM.write(2177, 14);
  EEPROM.write(2277, 40);


  //сокращенка 35 мин

  // 1 урок 
  EEPROM.write(1181, 8);
  EEPROM.write(1281, 30);
  EEPROM.write(2181, 9);
  EEPROM.write(2281, 05);

  // 2 урок 
  EEPROM.write(1182, 9);
  EEPROM.write(1282, 20);
  EEPROM.write(2182, 9);
  EEPROM.write(2282, 55);
  
  // 3 урок 
  EEPROM.write(1183, 10);
  EEPROM.write(1283, 10);
  EEPROM.write(2183, 10);
  EEPROM.write(2283, 45);

  // 4 урок 
  EEPROM.write(1184, 11);
  EEPROM.write(1284, 00);
  EEPROM.write(2184, 11);
  EEPROM.write(2284, 35);

  // 5 урок 
  EEPROM.write(1185, 11);
  EEPROM.write(1285, 50);
  EEPROM.write(2185, 12);
  EEPROM.write(2285, 25);

  // 6 урок 
  EEPROM.write(1186, 12);
  EEPROM.write(1286, 35);
  EEPROM.write(2186, 13);
  EEPROM.write(2286, 10);

  // 7 урок 
  EEPROM.write(1187, 13);
  EEPROM.write(1287, 20);
  EEPROM.write(2187, 13);
  EEPROM.write(2287, 55);
  


  EEPROM.write(10, 15); //hour
  EEPROM.write(11, 30); //min
  EEPROM.write(12, 16); //day
  EEPROM.write(13, 3); //month
  EEPROM.write(14, 20); //year_1
  EEPROM.write(15, 19); //year_2
  EEPROM.write(16, 19); //weekday

  EEPROM.write(yacheyka_reload, 0); //reload

  //password
  EEPROM.write(thousend_yach, 1);
  EEPROM.write(houndred_yach, 0);
  EEPROM.write(dec_yach, 0);
  EEPROM.write(one_yach, 0);

  //перенос
  EEPROM.write(yacheyka_perenos, 0); 
  EEPROM.write(yacheyka_perenos30, 0); //30 мин
  EEPROM.write(yacheyka_perenos1, 0); //час
  
  //сокращенное
  EEPROM.write(yacheyka_short, 0); 
  EEPROM.write(yacheyka_short40, 0); //40 мин
  EEPROM.write(yacheyka_short35, 0); //35 мин

  //отмена
  EEPROM.write(yacheyka_otmena, 0);
  

  reload();
  
}
//изменениепароля
void change_password(){

  check_password();

  if(pas_8 != EEPROM.read(thousend_yach)){EEPROM.write(thousend_yach, pas_8);}
  if(pas_9 != EEPROM.read(houndred_yach)){EEPROM.write(houndred_yach, pas_9);}
  if(pas_10 != EEPROM.read(dec_yach)){EEPROM.write(dec_yach, pas_10);}
  if(pas_11 != EEPROM.read(one_yach)){EEPROM.write(one_yach, pas_11);}

  password = EEPROM.read(thousend_yach) * 1000 + EEPROM.read(houndred_yach) * 100 + EEPROM.read(dec_yach) * 10 + EEPROM.read(one_yach);

}
//изменение времени
void setting_time(){

  lcd.clear();
  print_old_date();
  set_date();
  
}
//изменение расписания
void setting_timetable(){
 
  int choice_week_day = choicesing_weekday();
  print_lesson_stack(choice_week_day);
  delay(300);
  change_timetable(choice_week_day);
  
}
//опеределяет номер ячейки в которой происходит смена расписания
int opredelenie_number_yachyki(int poz_x_lesson, int poz_y_lesson, int numer_lesson, int choice_week_day){

  int number_of_yachyka;

   if(poz_x_lesson == 2 or poz_x_lesson == 5){number_of_yachyka = 1000;}
   else{number_of_yachyka = 2000;}

   if(poz_x_lesson == 2 or poz_x_lesson == 8){number_of_yachyka += 100;}
   else{number_of_yachyka += 200;}

   number_of_yachyka += choice_week_day * 10 + numer_lesson;
   
   change_timetable_value(poz_x_lesson, poz_y_lesson, number_of_yachyka);
}
//изменяет значение в выбраной ячейке
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
//выбор ячеек для изменения
void change_timetable(int choice_week_day){

  int plus_numer_lesson = 1;
  lcd.cursor();
  int poz_y_lesson = 0, poz_x_lesson = 2;
  lcd.setCursor(poz_x_lesson, poz_y_lesson);
  int sub_perebros_lesson = 0;
  if(choice_week_day == 6){sub_perebros_lesson = 1;}

  while(true){
    
    if(bouncer.update()){
      if(bouncer.read() == 0){
        pressed_moment = millis();
      }
      else{
        if(millis() - pressed_moment < 1000){
          opredelenie_number_yachyki(poz_x_lesson, poz_y_lesson, poz_y_lesson + plus_numer_lesson, choice_week_day);
        }
        else {break;}
      }
    }

    if(analogRead(y) < 300){

       poz_y_lesson++;
       if(poz_y_lesson == 4 and plus_numer_lesson == 1){

          poz_y_lesson = 0;
          scroll_bottom(choice_week_day);
          plus_numer_lesson = 5;
        
        }
       if(poz_y_lesson == 4 - sub_perebros_lesson and plus_numer_lesson == 5){

          poz_y_lesson = 0;
          scroll_top(choice_week_day);
          plus_numer_lesson = 1;
        
        }
       lcd.setCursor(poz_x_lesson, poz_y_lesson);
       pisk();
       delay(300);
       
    }

  if(analogRead(y) > 750){

       poz_y_lesson--;
       if(poz_y_lesson == -1 and plus_numer_lesson == 1){

          poz_y_lesson = 3 - sub_perebros_lesson;
          scroll_bottom(choice_week_day);
          plus_numer_lesson = 5;
        
        }
       if(poz_y_lesson == -1 and plus_numer_lesson == 5){

          poz_y_lesson = 3;
          scroll_top(choice_week_day);
          plus_numer_lesson = 1;
        
        }
       lcd.setCursor(poz_x_lesson, poz_y_lesson);
       pisk();
       delay(300);
       
    }

  if(analogRead(x) > 650){

       if(poz_x_lesson == 2){poz_x_lesson = 5;}
       else if(poz_x_lesson == 5){poz_x_lesson = 8;}
       else if(poz_x_lesson == 8){poz_x_lesson = 11;}
       else if(poz_x_lesson == 11){poz_x_lesson = 2;}
       lcd.setCursor(poz_x_lesson, poz_y_lesson);
       pisk();
       delay(300);
       
    }

  if(analogRead(x) < 490){

       if(poz_x_lesson == 5){poz_x_lesson = 2;}
       else if(poz_x_lesson == 8){poz_x_lesson = 5;}
       else if(poz_x_lesson == 11){poz_x_lesson = 8;}
       else if(poz_x_lesson == 2){poz_x_lesson = 11;}
       lcd.setCursor(poz_x_lesson, poz_y_lesson);
       pisk();
       delay(300);
       
    }
    
  }
  
  lcd.noCursor();
  
}
//вывод дней недели для выбора
void print_weekday(){

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(L"ПН");
  lcd.setCursor(5, 2);
  lcd.print(L"ЧТ");
  lcd.setCursor(9, 0);
  lcd.print(L"ВТ");
  lcd.setCursor(9, 2);
  lcd.print(L"ПТ");
  lcd.setCursor(13, 0);
  lcd.print(L"СР");
  lcd.setCursor(13, 2);
  lcd.print(L"СБ");
  
}
//выбор дня недели для выбора для изменения расписания
int choicesing_weekday(){

  print_weekday();
  
  int poz_y_weekday = 0, poz_x_weekday = 5;
  lcd.setCursor(poz_x_weekday + 2, poz_y_weekday);
  lcd.write(byte(127));
  lcd.setCursor(poz_x_weekday, poz_y_weekday);

  while(digitalRead(button)){

    if(analogRead(x) > 650){

      if(poz_x_weekday == 5){
        
        poz_x_weekday = 9;
        print_weekday();
        lcd.setCursor(poz_x_weekday + 2, poz_y_weekday);
        lcd.write(byte(127));
        lcd.setCursor(poz_x_weekday, poz_y_weekday);
        pisk();
        delay(300);
        
        }

      else if(poz_x_weekday == 13){
        
        poz_x_weekday = 5;
        if(poz_y_weekday == 0){poz_y_weekday = 2;}
        else{poz_y_weekday = 0;}
        print_weekday();
        lcd.setCursor(poz_x_weekday + 2, poz_y_weekday);
        lcd.write(byte(127));
        lcd.setCursor(poz_x_weekday, poz_y_weekday);
        pisk();
        delay(300);
        
        }
        
      else if(poz_x_weekday == 9){
        
        poz_x_weekday = 13;
        print_weekday();
        lcd.setCursor(poz_x_weekday + 2, poz_y_weekday);
        lcd.write(byte(127));
        lcd.setCursor(poz_x_weekday, poz_y_weekday);
        pisk();
        delay(300);
        
        }
      
    }

  if(analogRead(x) < 490){

      if(poz_x_weekday == 9){
        
        poz_x_weekday = 5;
        print_weekday();
        lcd.setCursor(poz_x_weekday + 2, poz_y_weekday);
        lcd.write(byte(127));
        lcd.setCursor(poz_x_weekday, poz_y_weekday);
        pisk();
        delay(300);
        
        }

      else if(poz_x_weekday == 13){
        
        poz_x_weekday = 9;
        print_weekday();
        lcd.setCursor(poz_x_weekday + 2, poz_y_weekday);
        lcd.write(byte(127));
        lcd.setCursor(poz_x_weekday, poz_y_weekday);
        pisk();
        delay(300);
        
        }
        
      else if(poz_x_weekday == 5){
        
        poz_x_weekday = 13;
        if(poz_y_weekday == 0){poz_y_weekday = 2;}
        else{poz_y_weekday = 0;}
        print_weekday();
        lcd.setCursor(poz_x_weekday + 2, poz_y_weekday);
        lcd.write(byte(127));
        lcd.setCursor(poz_x_weekday, poz_y_weekday);
        pisk();
        delay(300);
        
        }
      
    }

  if(analogRead(y) > 750 or analogRead(y) < 300){

      if(poz_y_weekday == 0){
        
        poz_y_weekday = 2;
        print_weekday();
        lcd.setCursor(poz_x_weekday + 2, poz_y_weekday);
        lcd.write(byte(127));
        lcd.setCursor(poz_x_weekday, poz_y_weekday);
        pisk();
        delay(300);
        
        }

      else if(poz_y_weekday == 2){
        
        poz_y_weekday = 0;
        print_weekday();
        lcd.setCursor(poz_x_weekday + 2, poz_y_weekday);
        lcd.write(byte(127));
        lcd.setCursor(poz_x_weekday, poz_y_weekday);
        pisk();
        delay(300);
        
        }
      
    }
    
  }
  
  int week_day;
  if(poz_x_weekday == 5 and poz_y_weekday == 0){week_day = 1;}
  else if(poz_x_weekday == 9 and poz_y_weekday == 0){week_day = 2;}
  else if(poz_x_weekday == 13 and poz_y_weekday == 0){week_day = 3;}
  else if(poz_x_weekday == 5 and poz_y_weekday == 2){week_day = 4;}
  else if(poz_x_weekday == 9 and poz_y_weekday == 2){week_day = 5;}
  else if(poz_x_weekday == 13 and poz_y_weekday == 2){week_day = 6;}
  return week_day;
  
}
//тест звонка
void test_zvonok(){
  
  digitalWrite(zvonok, HIGH);
  lcd.clear();
  lcd.setCursor(7, 1);
  lcd.print(L"ЗВЕНИТ");
  delay(3000);
  digitalWrite(zvonok, LOW);
  
}
//вывод первых 4 уроков
void print_lesson_stack(int week_day){

  lcd.clear();
  lcd.setCursor(0, 0);
  print_time_leson(week_day, 1); 
  lcd.setCursor(0, 1);
  print_time_leson(week_day,2);
  lcd.setCursor(0, 2);
  print_time_leson(week_day, 3); 
  lcd.setCursor(0, 3);
  print_time_leson(week_day,4); 
  
}
//вывод текущей даты и времени
void print_current_time(){
  
   if(miganie_double_point == 0){miganie_double_point = millis();}
    time.gettime(); 
    printing_hourss = time.Hours;
    printing_minutess = time.minutes;
    lcd.setCursor(15, 0);
    if(printing_hourss < 10){lcd.print("0"); lcd.print(printing_hourss);}
    else{lcd.print(printing_hourss);}
    
    if(1000 + miganie_double_point <= millis()){
      lcd.setCursor(17, 0);
      lcd.print(":");
      }
    if(2000 + miganie_double_point <= millis()){
      lcd.setCursor(17, 0);
      lcd.print(" ");
      miganie_double_point = millis();  
      }   
      
    lcd.setCursor(18, 0);  
    if(printing_minutess < 10){lcd.print("0"); lcd.print(printing_minutess);}
    else{lcd.print(printing_minutess);}

    lcd.setCursor(16, 1);
    if(time.weekday == 1){lcd.print(L"ПН");}
    else if(time.weekday == 2){lcd.print(L"ВТ");}
    else if(time.weekday == 3){lcd.print(L"СР");}
    else if(time.weekday == 4){lcd.print(L"ЧТ");}
    else if(time.weekday == 5){lcd.print(L"ПТ");}
    else if(time.weekday == 6){lcd.print(L"СБ");}
    else if(time.weekday == 7){lcd.print(L"ВС");}
    int print_day = time.day;
    lcd.print(print_day);
    
    

    lcd.setCursor(16, 2);
    if(time.month == 1){lcd.print(L"ЯНВ.");}
    else if(time.month == 2){lcd.print(L"ФЕВ.");}
    else if(time.month == 3){lcd.print(L"МАРТ");}
    else if(time.month == 4){lcd.print(L"АПР.");}
    else if(time.month == 5){lcd.print(L" МАЙ");}
    else if(time.month == 6){lcd.print(L"ИЮНЬ");}
    else if(time.month == 7){lcd.print(L"ИЮЛЬ");}
    else if(time.month == 8){lcd.print(L"АВГ.");}
    else if(time.month == 9){lcd.print(L"СЕН.");}
    else if(time.month == 10){lcd.print(L"ОКТ.");}
    else if(time.month == 11){lcd.print(L"НОЯ.");}
    else if(time.month == 12){lcd.print(L"ДЕК.");}

    lcd.setCursor(16, 3);
    lcd.print("20");
    int print_year = time.year;
    lcd.print(print_year);

    delay(150);
   
}
//перезагрузка
void reload(){

  asm("JMP 0");
  
}
//писк при любом действии
void pisk(){
  
  tone(pisk_pin, 2000, 100);
  
}
//писк при неправильном вводе пароля
void pisk_misstake(){

  tone(pisk_pin, 1000, 100);
          
}
//пожарная тревога
void check_fire_alarm(){

  if(analogRead(pin_fire_alarm) < 500){alarm_schet++;}
  
  if(alarm_schet >= 3){
    
    alarm_schet = 0;
    unsigned long long start_alarm = millis();
    
    while(millis() - start_alarm <= 10000){
      
      if(analogRead(pin_fire_alarm) < 500){alarm_schet++;}
      
      pisk();
      delay(200);
      pisk();
      delay(200);
      pisk();
    
      lcd.clear();
      lcd.setCursor(2, 1);
      lcd.print("ПОЖАРНАЯ ТРЕВОГА");
      digitalWrite(zvonok, HIGH);
      delay(500);
      digitalWrite(zvonok, LOW);
      delay(500);
      digitalWrite(zvonok, HIGH);
      delay(500);
      digitalWrite(zvonok, LOW);
      delay(500);
      digitalWrite(zvonok, HIGH);
      delay(500);
      digitalWrite(zvonok, LOW);
      
    }

    lcd.clear();
    if(time.weekday != 0 and !EEPROM.read(yacheyka_otmena) and !EEPROM.read(yacheyka_short)){scroll_top(time.weekday); Check_tochka(time.weekday);}
    else if(EEPROM.read(yacheyka_short40)){scroll_top(7); Check_tochka(time.weekday);}
    else if(EEPROM.read(yacheyka_short35)){scroll_top(8); Check_tochka(time.weekday);}
    
  }
  
}
//проверка на необходимость запуска меню настройки
void zapusk_menu(){
  if(bouncer.update()){
      if(!digitalRead(button)){

        pressed_moment = millis();
        
        }
      else{

        if(millis() - pressed_moment >= 1500){
        printing_hourss = 0;
        printing_minutess = 0;
        check_password(); 
        delay(300);
        if((pas_8 * 1000 + pas_9 * 100 + pas_10 * 10 + pas_11) == password or (pas_8 * 1000 + pas_9 * 100 + pas_10 * 10 + pas_11) == master_password){
        
          menu();
          lcd.clear();
          if(time.weekday != 0 and !EEPROM.read(yacheyka_otmena) and !EEPROM.read(yacheyka_short)){scroll_top(time.weekday); Check_tochka(time.weekday);}
          else if(EEPROM.read(yacheyka_short40)){scroll_top(7); Check_tochka(time.weekday);}
          else if(EEPROM.read(yacheyka_short35)){scroll_top(8); Check_tochka(time.weekday);}
        
          }
        else{

          pisk_misstake();
          lcd.clear();
          if(time.weekday != 0 and !EEPROM.read(yacheyka_otmena) and !EEPROM.read(yacheyka_short)){scroll_top(time.weekday); Check_tochka(time.weekday);}
          else if(EEPROM.read(yacheyka_short40)){scroll_top(7); Check_tochka(time.weekday);}
          else if(EEPROM.read(yacheyka_short35)){scroll_top(8); Check_tochka(time.weekday);}
          
          }
        }
    
      }
    }
}

void setup() {

  Serial.begin(9600);
  time.begin(); 

  password = EEPROM.read(thousend_yach) * 1000 + EEPROM.read(houndred_yach) * 100 + EEPROM.read(dec_yach) * 10 + EEPROM.read(one_yach);

  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(pisk_pin, OUTPUT);
  pinMode(zvonok, OUTPUT);

  bouncer.attach(button);
  bouncer.interval(5);
  
  lcd.begin(20, 4); //столбец, строка

  lcd.clear();

  if(time.year == 1970){chek_zarad = 1;}
  
  if (chek_zarad){
    
    time.settime(0, EEPROM.read(minutess), EEPROM.read(hourss), EEPROM.read(days), EEPROM.read(months), EEPROM.read(years_1) * 100 + EEPROM.read(years_2), EEPROM.read(weekdays));
    check_old_date();
    
    }
  lcd.clear();
  if(time.weekday != 0 and !EEPROM.read(yacheyka_otmena) and !EEPROM.read(yacheyka_short)){print_lesson_stack(time.weekday); Check_tochka(time.weekday);}
  if(EEPROM.read(yacheyka_short40)){print_lesson_stack(7); Check_tochka(time.weekday);}
  if(EEPROM.read(yacheyka_short35)){print_lesson_stack(8); Check_tochka(time.weekday);}

}

void loop() {

  if(EEPROM.read(yacheyka_reload) == 0 and (time.weekday) == 0){ //0 - воскресенье
  
    EEPROM.write(hourss, time.Hours);
    EEPROM.write(minutess, time.minutes); 
    EEPROM.write(days, time.day);
    EEPROM.write(months, time.month);
    EEPROM.write(years_2, time.year);
    EEPROM.write(weekdays, time.weekday);
    
    EEPROM.write(yacheyka_reload, 1);
    reload();
    
    } 
    
  if(EEPROM.read(yacheyka_reload) == 1 and (time.weekday) != 0){EEPROM.write(yacheyka_reload, 0);}

  while((time.weekday) == 0){
    lcd.setCursor(3, 1);
    lcd.print(L"СЕГОДНЯ");
    lcd.setCursor(1, 2);
    lcd.print(L"ВОСКРЕСЕНЬЕ");
    print_current_time();
    zapusk_menu();
    check_fire_alarm();
    
  }

  if(time.weekday != 0 and EEPROM.read(yacheyka_otmena)){

    lcd.setCursor(5, 1);
    lcd.print(L"УРОКИ");
    lcd.setCursor(3, 2);
    lcd.print(L"ОТМЕНЕНЫ");
    print_current_time();
    zapusk_menu();
    check_fire_alarm();
    
  }
  
  if(time.weekday != 0 and !EEPROM.read(yacheyka_otmena)){
    scroll(time.weekday);
    print_current_time();
    Check_zvonok(time.weekday);
    Check_tochka(time.weekday);
    zapusk_menu();
    check_fire_alarm();
    
  } 
}
