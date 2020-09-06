#include "rh_master.h"
#include "display.h"
#include "satelits.h"

RH_ASK driver(2000, 4, 5);
RHReliableDatagram manager(driver, SERVER_ADDRESS);

uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
uint8_t data[] = "ok";

class sensor;
class actor;

extern SSD1306AsciiSpi oled;
extern sensor sensor[];
extern actor actor[];
extern bool oledupdate;

void rh_master_setup() {
  //manager.setRetries(10);
  //manager.setTimeout(500);
  if (!manager.init())
    oled.println("init failed");
}

void rh_master_handle() {
  if (manager.available())
  {
    // Wait for a message addressed to us from the client
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, &from))
    {
      from -= 2;
      char *ptr = strtok((char *)buf, ",");
      char *pEnd;
      while (ptr != NULL) {
        //oled.println(ptr);

        //v5.08,h41.4,t15.6,a02
        
        switch (ptr[0]) {
          case 'v':
            sensor[from].voltage = ++ptr; break;
          case 'h':
            sensor[from].humidity = ++ptr; break;
          case 't':
            sensor[from].degree = ++ptr; break;
          case 'a':
            actor[from].from = from;
            actor[from].number = strtol(++ptr, &pEnd, 10);
            break;
        }
        ptr = strtok(NULL, ",");
        oledupdate = true;
      }
      // Send a reply back to the originator client
      from += 2;
      if (!manager.sendtoWait(data, sizeof(data), from)) {
        //oled.println("sendtoWait fail");
      }
    }
  }
}

void rh_master_send(uint8_t from) {
  //if (manager.available()) {
    manager.sendtoWait(data, sizeof(data), 3);
  //}
}