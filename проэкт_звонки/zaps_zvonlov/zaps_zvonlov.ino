#include <EEPROM.h>

void setup() {
  // a - 1 - начало, 2 - конец
  // b - 1 - часы, 2 - минуты
  // c - день недели(7 - 40 мин, 8 - 35 мин)
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

  
  
  EEPROM.write(10, 11); //hour
  EEPROM.write(11, 30); //min
  EEPROM.write(12, 16); //day
  EEPROM.write(13, 3); //month
  EEPROM.write(14, 20); //year_1
  EEPROM.write(15, 19); //year_2
  EEPROM.write(16, 6); //weekday

  EEPROM.write(17, 0); //reload

  //password
  EEPROM.write(20, 1);
  EEPROM.write(21, 0);
  EEPROM.write(22, 0);
  EEPROM.write(23, 0);

  //перенос
  EEPROM.write(18, 0); 
  EEPROM.write(24, 0); //30 мин
  EEPROM.write(25, 0); //час
  
  //сокращенное
  EEPROM.write(19, 0); 
  EEPROM.write(26, 0); //40 мин
  EEPROM.write(27, 0); //35 мин

  //отмена
  EEPROM.write(28, 0);
  
}

void loop() {
  

}
