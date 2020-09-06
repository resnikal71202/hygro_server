#include <Arduino.h>
#include "satelits.h"
#include "hid.h"
#include "display.h"
#include "rh_master.h"

uint8_t oakku;
uint8_t odegree;
uint8_t ohumidity;
uint8_t onom;
uint8_t ozeig;
uint8_t scroll = 0;

SSD1306AsciiSpi oled;

int oledstate = OLEDIDLE;
bool oledupdate = false;

extern uint8_t data[];
//extern void rh_master_send(uint8_t from);

sensor sensor[5];
actor actor[5];

void oled_setup() {
  oled.begin(&Adafruit128x64, CS_PIN, DC_PIN, RST_PIN);
  oled.setFont(System5x7);
  oled.clear();
  oled.setScrollMode(SCROLL_MODE_AUTO);
  //oled.println("start");
}

void oled_handle() {
  switch (oledstate) {
    case OLEDIDLE:
      oled_print_idle(); break;
    case OLEDMENU:
      oled_print_menu(); break;
    case OLEDMENUSHOWACTORS:
      oled_print_actors_init(); break;
  }
}

void oled_print_idle_init() {
  oled.clear();
  oled.println();
  oled.println("  Satelit 1: [ NAN%");
  oakku = oled.fieldWidth(strlen("  Satelit 1: [ "));
  onom = oled.fieldWidth(strlen("  Satelit "));
  oled.println("     NAN]C  NAN%   ");
  odegree = oled.fieldWidth(strlen("     "));
  ohumidity = oled.fieldWidth(strlen("     100]C  "));
  oled.println();
  oled.println("  Satelit 2: [ NAN%");
  oled.println("     NAN]C  NAN%   ");
  oled.println("_____________________");
  oled.print("         menu       ");
  ozeig = oled.fieldWidth(0);
}

void oled_print_idle() {
  if (oledupdate) {
    oledupdate = false;
    oled.clearField(onom, oled.fontRows(), 1);
    oled.print(scroll + 1);
    oled.clearField(oakku, oled.fontRows(), 4);
    //char* pEnd;
    //voltage = map(strtod(&voltage[0], voltage[3]), 4.5,5.5,0,100);
    oled.print(sensor[scroll].voltage);
    oled.print("V");

    oled.clearField(odegree, oled.fontRows() * 2, 5);
    oled.print(sensor[scroll].degree);
    oled.print("]C");

    oled.clearField(ohumidity, oled.fontRows() * 2, 4);
    oled.print(sensor[scroll].humidity);
    oled.print("%");

    oled.clearField(onom, oled.fontRows() * 4, 1);
    oled.print(scroll + 2);

    oled.clearField(oakku, oled.fontRows() * 4, 4);
    //char* pEnd;
    //voltage = map(strtod(&voltage[0], voltage[3]), 4.5,5.5,0,100);
    oled.print(sensor[scroll + 1].voltage);
    oled.print("V");

    oled.clearField(odegree, oled.fontRows() * 5, 5);
    oled.print(sensor[scroll + 1].degree);
    oled.print("]C");

    oled.clearField(ohumidity, oled.fontRows() * 5, 4);
    oled.print(sensor[scroll + 1].humidity);
    oled.print("%");
  }
  if (digitalRead(BUTTONM) == LOW) {
    delay(30);
    if (digitalRead(BUTTONM) == LOW) {
      oledstate = OLEDMENU;
      scroll = 0;
      oledupdate = true;
      oled_print_menu();
    }
  }
  fscroll(0, 2);
}

void oled_print_menu() {
  if (oledupdate) {
    oledupdate = false;
    oled.clear();
    oled.println("        menu:       ");
    oled.println(" edit actors manual");
    oled.println();
    oled.println();
    oled.println();
    oled.println();
    oled.println("_____________________");
    oled.print(" back         select ");
    oledupdate = false;
    oled.clearField(ozeig, oled.fontRows() * scroll + 1, 1);
    oled.print(">");
  }
  fscroll(0, 3);
  if (digitalRead(BUTTONL) == LOW) {
    delay(30);
    if (digitalRead(BUTTONL) == LOW) {
      oledstate = OLEDIDLE;
      scroll = 0;
      oledupdate = true;
      oled_print_idle_init();
      oled_print_idle();
    }
  }
  if (digitalRead(BUTTONR) == LOW) {
    delay(30);
    if (digitalRead(BUTTONR) == LOW) {
      switch (scroll) {
        case 0:
          oledstate = OLEDMENUSHOWACTORS;
          scroll = 0;
          oledupdate = true;
          oled_print_actors_init();
          break;
      }
    }
  }
}
void oled_print_actors_init() {
  if (oledupdate) {
    oledupdate = false;
    oled.clear();
    oled.print("Act at id:");
    oled.println(actor[1].from);
    oled.print("num of acts:");
    oled.print(actor[1].number);
    oled.println();
    oled.println();
    oled.println();
    oled.println();
    oled.println();
    oled.println("_____________________");
    oled.print(" back    K10    K11 ");
  }
  if (digitalRead(BUTTONL) == LOW) {
    delay(30);
    if (digitalRead(BUTTONL) == LOW) {
      oledstate = OLEDMENU;
      scroll = 0;
      oledupdate = true;
      delay(100);
      oled_print_menu();
    }
  }
  if (digitalRead(BUTTONR) == LOW) {
    delay(30);
    if (digitalRead(BUTTONR) == LOW) {
      strcpy((char *)data, "K11");
      //rh_master_send(2);
      //strcpy(data, "ok");
      oledupdate = true;
    }
  }
  if (digitalRead(BUTTONM) == LOW) {
    delay(30);
    if (digitalRead(BUTTONM) == LOW) {
      strcpy((char *)data, "K10");
      //rh_master_send(2);
      //strcpy(data, "ok");
      oledupdate = true;
    }
  }
}
void fscroll(int u, int o) {
  if (digitalRead(BUTTONU) == LOW) {
    delay(30);
    if (digitalRead(BUTTONU) == LOW) {
      if (scroll > u) {
        scroll--;
        oledupdate = true;
        delay(100);
      }
    }
  }
  if (digitalRead(BUTTOND) == LOW) {
    delay(30);
    if (digitalRead(BUTTOND) == LOW) {
      if (scroll <= o) {
        scroll++;
        oledupdate = true;
        delay(100);
      }
    }
  }
}