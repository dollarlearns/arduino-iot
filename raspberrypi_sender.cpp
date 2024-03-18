/**
 * @file raspberrypi_sender.cpp
 * @brief File to test the RF24 Wireless Communication Sender for Raspberry Pi to communicate with Arduino, turning devices on and off 
 * Tests the connection between RaspberryPi and Arduino UNO
 */

#include <iostream>
#include <RF24/RF24.h>

using namespace std;

// Define Pin Numbers for RF24 Module
#define PIN_CE  17
#define PIN_CSN 0

// Define a specific address for communication
const uint64_t pipeNum = 0x7878787878LL;
RF24 radio(PIN_CE, PIN_CSN);

/**
 * @brief Initializes RF24 radio module with specified settings
 */
void initializeRadio() {
    radio.begin();
    radio.setChannel(5);
    radio.setDataRate (RF24_1MBPS);
    radio.setPALevel(RF24_PA_HIGH);
    radio.enableDynamicPayloads();
    radio.openWritingPipe(pipeNum);
}

/**
 * @brief Sends data through the RF24 module on a specific channel to control specific devices 
 * @param channel The channel on which to send the data, each channel is unique to a specific device
 * @param command The command to be sent the (int)
 * @return true if data is delivered successfully, false otherwise
 */
bool sendData(int channel, const char* command) {
    radio.setChannel(channel);
    if (radio.write(command, strlen(command)+1)) {
        cout << "Delivered " << strlen(command) + 1 << " bytes" << endl;
        return true;
    } else {
        cout << "Data not delivered" << endl;
        return false;
    }
}

/**
 * @brief Turns on the device on the specified channel
 * @param channel The channel on which to send the command
 */
void turnOn(int channel, const char * colour) {
    if (!sendData(channel, colour)){
        delay(2000);
    };
} 
	
    

/**
 * @brief Turns off the device on the specified channel
 * @param channel The channel on which to send the command
 */
void turnOff(int channel) {
    if (!sendData(channel,"0")) {
        delay(2000);
    }
}

/**
 * @brief Main function, entry point of the program. Prompts the user for ON or OFF and the device they want to control.
 * Will send the appropriate command to the corresponding device.
 */
int main() {
    initializeRadio();
    char userInput[25];
    char channel[2];   
   
    while (true) {
        cout << "Enter 'ON' to turn on the device, 'OFF' to turn it off or a colour: ";
        cin >> userInput;
        cout << "Which device would you like to set? : ";
        cin >> channel;

        //Encoding user input 

        if (strcasecmp(userInput, "ON") == 0) {
            turnOn(stoi(channel),"1");
        } else if (strcasecmp(userInput, "OFF") == 0) {
            turnOff(stoi(channel));
        }
        //RED
        else if (strcasecmp(userInput, "Red") ==0){
            turnOn(stoi(channel), "2");

        //GREEN
        } else if (strcasecmp(userInput, "Green")==0){
            turnOn(stoi(channel), "3");

        //BLUE
        } else if (strcasecmp(userInput, "Blue")==0){
            turnOn(stoi(channel), "4");
        }
        //PURPLE
         else if (strcasecmp(userInput, "purple")==0){
            turnOn(stoi(channel), "5");
        }
        //ORANGE 
        else if (strcasecmp(userInput, "orange")==0){
            turnOn(stoi(channel), "6");
        }

        //YELLOW 
        else if (strcasecmp(userInput, "yellow")==0){
            turnOn(stoi(channel), "7");
        }
        //PINK
        else if (strcasecmp(userInput, "pink")==0){
            turnOn(stoi(channel), "8");
        }

        else {
                cout << "Invalid input. Please enter 'ON' to turn on the device, 'OFF' to turn it off OR a colour: " << endl;
            }
    }
        return 0;

}


    



