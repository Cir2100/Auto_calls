#include <EEPROM.h>

void setup() {
  // a - 1 - начало, 2 - конец
  // b - 1 - часы, 2 - минуты
  // c - день недели
  // d - № урока

  Serial.begin(9600);
  // 1 урок пн-чт
  Serial.print(EEPROM.read(1111));
  Serial.print(EEPROM.read(1211));
  Serial.print(EEPROM.read(2111));
  Serial.println(EEPROM.read(2211));

  // 2 урок пн-чт
  Serial.print(EEPROM.read(1112));
  Serial.print(EEPROM.read(1212));
  Serial.print(EEPROM.read(2112));
  Serial.println(EEPROM.read(2212));
  
  // 3 урок пн-чт
  Serial.print(EEPROM.read(1113));
  Serial.print(EEPROM.read(1213));
  Serial.print(EEPROM.read(2113));
  Serial.println(EEPROM.read(2213));

  // 4 урок пн-чт
  Serial.print(EEPROM.read(1114));
  Serial.print(EEPROM.read(1214));
  Serial.print(EEPROM.read(2114));
  Serial.println(EEPROM.read(2214));

  // 5 урок пн-чт
  Serial.print(EEPROM.read(1115));
  Serial.print(EEPROM.read(1215));
  Serial.print(EEPROM.read(2115));
  Serial.println(EEPROM.read(2215));

  // 6 урок пн-чт
  Serial.print(EEPROM.read(1116));
  Serial.print(EEPROM.read(1216));
  Serial.print(EEPROM.read(2116));
  Serial.println(EEPROM.read(2216));

  // 7 урок пн-чт
  Serial.print(EEPROM.read(1117));
  Serial.print(EEPROM.read(1217));
  Serial.print(EEPROM.read(2117));
  Serial.println(EEPROM.read(2217));

  // 8 урок пн-чт
  Serial.print(EEPROM.read(1118));
  Serial.print(EEPROM.read(1218));
  Serial.print(EEPROM.read(2118));
  Serial.println(EEPROM.read(2218));

  // 1 урок пт
  Serial.print(EEPROM.read(1151));
  Serial.print(EEPROM.read(1251));
  Serial.print(EEPROM.read(2151));
  Serial.println(EEPROM.read(2251));

  // 2 урок пт
  Serial.print(EEPROM.read(1152));
  Serial.print(EEPROM.read(1252));
  Serial.print(EEPROM.read(2152));
  Serial.println(EEPROM.read(2252));

  // 3 урок пт
  Serial.print(EEPROM.read(1153));
  Serial.print(EEPROM.read(1253));
  Serial.print(EEPROM.read(2153));
  Serial.println(EEPROM.read(2253));

  // 4 урок пт
  Serial.print(EEPROM.read(1154));
  Serial.print(EEPROM.read(1254));
  Serial.print(EEPROM.read(2154));
  Serial.println(EEPROM.read(2254));

  // 5 урок пт (классный час))
  Serial.print(EEPROM.read(1155));
  Serial.print(EEPROM.read(1255));
  Serial.print(EEPROM.read(2155));
  Serial.println(EEPROM.read(2255));

  // 6 урок пт
  Serial.print(EEPROM.read(1156));
  Serial.print(EEPROM.read(1256));
  Serial.print(EEPROM.read(2156));
  Serial.println(EEPROM.read(2256));

  // 7 урок пт
  Serial.print(EEPROM.read(1157));
  Serial.print(EEPROM.read(1257));
  Serial.print(EEPROM.read(2157));
  Serial.println(EEPROM.read(2257));

  // 8 урок пт
  Serial.print(EEPROM.read(1158));
  Serial.print(EEPROM.read(1258));
  Serial.print(EEPROM.read(2158));
  Serial.println(EEPROM.read(2258));

  // 1 урок сб
  Serial.print(EEPROM.read(1161));
  Serial.print(EEPROM.read(1261));
  Serial.print(EEPROM.read(2161));
  Serial.println(EEPROM.read(2261));

  // 2 урок сб
  Serial.print(EEPROM.read(1162));
  Serial.print(EEPROM.read(1262));
  Serial.print(EEPROM.read(2162));
  Serial.println(EEPROM.read(2262));

  // 3 урок сб
  Serial.print(EEPROM.read(1163));
  Serial.print(EEPROM.read(1263));
  Serial.print(EEPROM.read(2163));
  Serial.println(EEPROM.read(2263));

  // 4 урок сб
  Serial.print(EEPROM.read(1164));
  Serial.print(EEPROM.read(1264));
  Serial.print(EEPROM.read(2164));
  Serial.println(EEPROM.read(2264));

  // 5 урок сб
  Serial.print(EEPROM.read(1165));
  Serial.print(EEPROM.read(1265));
  Serial.print(EEPROM.read(2165));
  Serial.println(EEPROM.read(2265));

  // 6 урок сб
  Serial.print(EEPROM.read(11662));
  Serial.print(EEPROM.read(1266));
  Serial.print(EEPROM.read(2166));
  Serial.println(EEPROM.read(2266));

  // 7 урок сб
  Serial.print(EEPROM.read(1167));
  Serial.print(EEPROM.read(1267));
  Serial.print(EEPROM.read(2167));
  Serial.println(EEPROM.read(2267));

 // текущее время, для теста
  Serial.print(EEPROM.read(10)); //hour
  Serial.print(EEPROM.read(11)); //min
  Serial.print(EEPROM.read(12)); //day
  Serial.print(EEPROM.read(13)); //month
  Serial.print(EEPROM.read(14)); //year
  Serial.print(EEPROM.read(15)); //zarbat
}

void loop() {
  

}
