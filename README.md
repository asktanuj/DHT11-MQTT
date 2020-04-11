# DHT11-MQTT
Example of MQTT Publisher and Subscriber

C source code to publish and subscribe for Temperature and Humidity from DHT11 sensor connected to Raspberry Pi

Hardware connection:
DHT11 VCC pin connected to Pin 1 of the Raspberry Pi (3.3 v)
DHT11 GND pin connected to Pin 6 of the Raspberry Pi (GND)
DHT11 DATA pin connected to Pin 7 of the Raspberry Pi

See also: https://www.thegeekpub.com/236867/using-the-dht11-temperature-sensor-with-the-raspberry-pi/

Step 1: Install WiringPi library
	git clone git://git.drogon.net/wiringPi
	cd wiringPi
	./build
	## WiringPi library is installed and ready to use

Step 2: Install mosquitto (MQTT Broker, MQTT Publisher and MQTT Subscriber)
	sudo apt-get install mosquitto

Step 3: To run MQTT broker
	mosquitto -v (This will start broker with verbose logging
		      Note broker automatically starts when machine is powered up.
		      Use "sudo killall mosquitto" to kill existing instance)

Step 4: Build and run Publisher code
	cd pub
	make
	./dht11Publisher

Step 5; Open a new terminal and build and run Subscriber code
	cd sub
	make
	./dht11Subscriber
