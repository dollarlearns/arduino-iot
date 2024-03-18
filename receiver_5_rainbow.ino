/**
 * @file receiver_5_rainbow.ino
 * Rainbow light device on channel 5
 * @brief RF24 Wireless Communication Sketch from Arduino UNO to receive data from Raspberry Pi on channel 5 and control rainbow light device
 * @author Dollar Luo and Simon Feng
 */

#include <RF24.h>

// Define Pin Numbers for RF24 Module
#define PIN_CE  9
#define PIN_CSN 10

// Variables for pipe number and payload size
uint8_t pipeNumber;
uint8_t payloadSize;

// Create an instance of RF24
RF24 radio(PIN_CE, PIN_CSN);

/**
 * @brief Setup function, executed once when Arduino starts
 */
void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);

  // Initialize RF24 module
  radio.begin();
  radio.setChannel(5);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.enableDynamicPayloads();

  // Open reading pipe with a specific address
  radio.openReadingPipe (0, 0x7878787878LL);
  
  // Print RF24 module details to Serial Monitor
  radio.printDetails();

  // Start listening for incoming data
  radio.startListening();

  // Print message to Serial Monitor
  Serial.println("Start listening...");
  
  //Set pinmodes 
  
  pinMode(2,OUTPUT);
  //RED LIGHT
  pinMode(A0,OUTPUT); 

  //GREEN LIGHT
  pinMode(A1,OUTPUT);

  //BLUE LIGHT
  pinMode(A2,OUTPUT);

}

/**
 * @brief Loop function, continuously executed to listen for communications from Raspberry Pi 
 * Will continue listening and turn on and off depending on input received
 */
void loop() {
  // Check if data is available on the specified pipe
  if (radio.available(&pipeNumber)) {
    // Get the size of the incoming payload
    payloadSize = radio.getDynamicPayloadSize(); 

    // Create a character array to store the payload
    char payload[payloadSize];
    
    // Create a string to store the received data from radio
    String receivedData;

    // Read the payload from RF24 module
    radio.read(&payload, sizeof(payload));
 
    // Convert the payload to a string
    for (uint8_t i = 0; i < payloadSize; i++) {
        receivedData += payload[i];
    }
    
    // Control pin 2 based on received data, turn on the light if data is 1, off if 0
    
    if (receivedData == "0"){
      digitalWrite(2,LOW);
      setColour(0,0,0);
    }
    
    if (receivedData == "1"){
      digitalWrite(2, HIGH);
      //digitalWrite(A0,HIGH);
      setColour(255,255,255); //Default to white light
    }
    //RED
    if (receivedData == "2"){
      setColour(255,0,0);
    }
    //GREEN
    if (receivedData == "3"){
      setColour(0,255,0);
    }
    //BLUE
    if (receivedData == "4"){
      setColour(0,0,255);
    }
    //PURPLE
    if (receivedData == "5"){
      setColour(255,0,255);
    }
    //ORANGE
    if (receivedData == "6"){
      setColour(255,165,0);
    }
    //YELLOW
    if (receivedData == "7"){
      setColour(255,255,0);
    }
    //PINK
    if (receivedData == "8"){
      setColour(255,192,203);
    }

    // Print details to Serial Monitor to verify data received
    Serial.print("Pipe : " + String(pipeNumber) + " ");
    Serial.print("Size : " + String (payloadSize) + " ");
    Serial.println("Data : " + receivedData);
    
    // Delay for stability
    delay(100);
    
    

  }
}
 void setColour(int redValue, int greenValue, int blueValue){
      analogWrite(A0, redValue);
      analogWrite(A1, greenValue);
      analogWrite(A2, blueValue);
    }

