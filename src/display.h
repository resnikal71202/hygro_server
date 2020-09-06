#ifndef __DISPLAY_H__ 
#define __DISPLAY_H__  
#include <Arduino.h>
#include "..\..\hygro_server\lib\SSD1306Ascii-master\src\SSD1306Ascii.h"
#include "..\..\hygro_server\lib\SSD1306Ascii-master\src\SSD1306AsciiSpi.h"

//pin setup
#define CS_PIN  7
#define RST_PIN 8
#define DC_PIN  9

//oled state mashin
#define OLEDIDLE 0
#define OLEDMENU 1
#define OLEDMENUSHOWACTORS 2

void oled_setup();
void oled_handle();
void oled_print_idle_init();
void oled_print_idle();
void oled_print_menu();
void oled_print_actors_init();
void fscroll(int u, int o);
#endif