#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h> // for sleep function

#include "../mqtt/mqtt.h"

#define DATA_PIN	7	/*GPIO 4 */
#define MAX_PULSEWIDTH 255

uint8_t pinState = HIGH;
uint8_t dht11_data[5] = {0, 0, 0, 0, 0};

const char *client_name = "dht11_node1_pub"; 	// -c
const char *ip_addr     = "127.0.0.1";		// -i
uint32_t    port        = 1883;			    // -p
const char *topic       = "node1/dht11";	// -t
mqtt_broker_handle_t *broker;
char pub_msg[128];

void initialize()
{	
	/* Program the DHT11 data pin as OUTPUT */
	pinMode(DATA_PIN, OUTPUT);
	
	/* Pull down the data pin for 18 ms */
	digitalWrite(DATA_PIN, LOW);
	delay(18);
	
	/* Pull up the data pin for 40 us */
	digitalWrite(DATA_PIN, HIGH);
	delayMicroseconds(40);
	digitalWrite(DATA_PIN, LOW);
	
	/* Now program the data pin as INPUT to reeive the data */
	pinMode(DATA_PIN, INPUT);
	pinState = digitalRead(DATA_PIN);
	
}

/* Read one pulse and return its width */
int readPulse()
{
	int pulseWidth = 0;
	
	while(digitalRead(DATA_PIN) == pinState){
		delayMicroseconds(1);
		pulseWidth++;
		if(pulseWidth > MAX_PULSEWIDTH)
		{
			//printf("\nError: Pulse width exceeded max value (actual %d expected %d)", pulseWidth, MAX_PULSEWIDTH);
			return -1;
		}
	}
	
	pinState = digitalRead(DATA_PIN);
		
	//printf("\nPulse width = %d", pulseWidth);
	return pulseWidth;
}
/* Read data */
int readData()
{
	int i = 0;
	int pulseWidth = 0;
	int bitPos = 0;
	int sum = 0;
	double C = 0;
	//double F = 0;
	double H = 0;
	
	for (i = 0; i < 83; i++) {
		pulseWidth = readPulse();
		
		if(pulseWidth <= 0) {
			/* Error occured, restart the cycle again */
			//printf("\n i = %d: Error occured, restarting...", i);
			return -1;
		}
		
		/* Ignore first 2 pulses
		 * Consider the pulse as data, only if current pin state is LOW
		 * (HIGH pulse indicates data. If data transmission is complete 
		 * for the current pulse, then the pin will be in LOW) */
		if ((i >= 3) && (pinState == LOW)) {
			/* Save the bit in appropriate position of the data */
			dht11_data[bitPos/8] = (dht11_data[bitPos/8] << 1);
			
			if(pulseWidth > 28) {
				/* It is 1, so save it */
				dht11_data[bitPos/8] = dht11_data[bitPos/8] | 1;
			}
			/* For 0, we don't have to anything, since left shift 
			 * would have created a 0 in the current bit already */
			bitPos++;
		}
	}
	
	/*printf("\nLast Bit Position = %d", bitPos);*/
	//printf("\nData: 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x", dht11_data[0],dht11_data[1],dht11_data[2],dht11_data[3],dht11_data[4]);
	
	/* 5 bytes of the data would have been filled by now */
	/* Verify the checksum */
	sum = dht11_data[0] + dht11_data[1] + dht11_data[2] + dht11_data[3];
	if((sum & 0xff) != dht11_data[4]) {
		//puts("\nChecksum mismatch, restarting again...");
		return -1;
	}
	
	H = (double)dht11_data[0] + ((double)dht11_data[1] / 100.0);
	C = (double)dht11_data[2] + ((double)dht11_data[3] / 100.0);
	//F = C * 9.0 / 5.0 + 32.0;
	
	//printf( "\nHumidity = %2.2f %% Temperature = %2.2f C (%2.2f F)\n", H, C, F );
	pub_msg[0] = '\0';
	snprintf(&pub_msg[0], 128, "{\"humidity\":%2.2f, \"temperature\":%2.2f}", H, C);
	puts(pub_msg);
	
	return 0;
}

void publish_connect(void)
{
    broker = mqtt_connect(client_name, ip_addr, port);
    if (broker == 0) {
        puts("Failed to connect");
        exit(1);
    }
}

void publish_data(void)
{
    if (broker != 0) {
        if (mqtt_publish(broker, topic, pub_msg, QoS1) == -1) {
            puts("Publish failed");
        }
        else {
            puts("Sent message to broker");
        }
    }
    else {
		puts("Not connected to broker");
		publish_connect();
    }
}

void publish_disconnect(void)
{
	if (broker != 0) {
		mqtt_disconnect(broker);
		broker = 0;
	}
	else {
		puts("Not connected to broker");
	}
}

int main( void )
{
	puts("Raspberry Pi wiringPi DHT11 Temperature & Humidity monitor\n" );
 
	if (wiringPiSetup() == -1 ) {
		puts("wiringPiSetup() failed");
		exit(1);
	}
 
    publish_connect();
	while (1) {
		initialize();
		if (readData() != -1) {
			publish_data();
			sleep(5);
		}
		else {
			//Read failed so sleep for 1 sec only
			sleep(1);
		}
	}
 
    publish_disconnect();
	return(0);
}
