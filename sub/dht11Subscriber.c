/*****************************************************************************
* Filename: dht11Subscriber.c
* 
* Created by BITS PILANI on 11th April 2020
* Copyright 2020 BITS PILANI WILP. All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mqtt/mqtt.h"

/********************************* Global variables ******************************/
const char *client_name = "default_sub";
const char *ip_addr     = "127.0.0.1";
uint32_t    port        = 1883;
const char *topic       = "node1/dht11";

/********************************** Local Functions *******************************/

/********************************************************************************************
* Function: main
* Description: DHT11 Subscriber main loop
********************************************************************************************/
int main (int argc, char** argv)
{
    int ret = -1;
    int result;
    mqtt_broker_handle_t *broker;
    
    puts("MQTT SUB Test Code");

    while(1) {
        if (ret == -1) {
            broker = mqtt_connect(client_name, ip_addr, port);
            if (broker == 0) {
                puts("Failed to connect");
                exit(1);
            }

            result= mqtt_subscribe(broker, topic, QoS0);
            if (result != 1) {
                puts("Failed to Subscribe");
                exit(1);
            }
        }
        ret = mqtt_display_message(broker, &putchar);
        puts("\n");
    }

    return 0;
}
