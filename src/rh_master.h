#ifndef __RH_MASTER_H__ 
#define __RH_MASTER_H__
#include <Arduino.h>
#include "..\..\hygro_server\lib\RadioHead-master\RHReliableDatagram.h"
#include "..\..\hygro_server\lib\RadioHead-master\RH_ASK.h"

#define SERVER_ADDRESS 1

void rh_master_setup();
void rh_master_handle();
void rh_master_send(uint8_t from);

#endif