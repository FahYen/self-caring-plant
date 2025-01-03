//add this file to the cmakelist.txt file

#include <iostream>
#include <string>

#include <BLEDevice.h> //main library that manages BLE. turns on bluetooth, etc. [makes the ble stack]
#include <BLEServer.h> //the server for BLE
#include <BLEUtils.h> //has helper functions
#include <BLE2902.h> //library for descriptoes {they describe how a ble characteristic works}. ex: enables notifications to connected device
#include <Wire.h>
#include <Adafruit_OV2640.h> //this allows work with the camera

//using namespace std;


//from bledevice.h, run createServer() to create the BLE server
//use bleserver library to manage the server :
 /*track connected devices, define services [ex: humidity], handles connection and disconnections with devices*/


// server name
const string bleServerName = "ESP32_Camera"

// service and characteristic UUIDs
const string service_UUID = "generate a uuid for transfer service using online generator" //set of related things you can do
const string characteristic_UUID = "generate" //where the actual data is saved 

// make an instance of the camera
Adafruit_OV2640 camera;

// BLE state
bool deviceConnected = false;

// timer variables
/*unsigned long is a type of number that can hold large whole numbers,
 but no negative numbers. used when you need to keep track of time or values that can go up to a very large number
(ex: counting milliseconds since the program started).
using it here because millis() (function that says how long the program has been running) 
returns type unsigned long
*/
unsigned long lastTime = 0;
unsigned long timerDelay = 86400000; // 24 hours in milliseconds. to take 1 picture everyday

//class to handle BLE server events
class MyServerCallbacks: public BLEServerCallbacks {

  void connect(BLEServer* pServer) {

    deviceConnected = true;

    Serial.println("Device connected");
  }

  void disconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Device disconnected");
  }

};

// initialize camera
void initCamera() {

  if (!camera.begin()) {
    Serial.println("OV2640 sensor not found");
    while (1);
  }
  camera.setResolution(OV2640_320x240); // 320x240 resolution -- feel free to change
}

// Setup function
void setup() {
  // starts the serial communication
  Serial.begin(115200); //115200 represents the baud rate, this is the speed that the data is transmitted betweent the esp32 and the computer (this number is the recommended)

  // intiliazes camera
  initCamera();

  // creates = BLE Device
  BLEDevice::init(bleServerName); //server name is what other devices will see when they try to connect

  // create the BLE Server
  BLEServer *pServer = BLEDevice::createServer(); //this will let us advertise and accept conenctisons

  pServer->setCallbacks(new MyServerCallbacks()); //handles connecting and disconnecting using the myservercallbacks class

  // create the BLE service
  BLEService *imageService = pServer->createService(service_UUID); //creates server using the specific service

  // create BLE characteristic for image data
  BLECharacteristic *imageCharacteristic = imageService->createCharacteristic( //makes a ble characteristic in the service to hold the image data

    characteristic_UUID, 

    BLECharacteristic::PROPERTY_NOTIFY //property_notify says that this characteristic will notify the devices that are connected when its value changes

  );

  imageCharacteristic->addDescriptor(new BLE2902()); //adds a descriptor to the characteristic (check doc for defintion)
  //ble2902 enables characteristic notifications

  // start service
  imageService->start();

  // start advertising for devices
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  pAdvertising->addServiceUUID(service_UUID); //specifies the uuid service that we are advertising

  pServer->getAdvertising()->start(); //starts advertising and making the service discoverable

  Serial.println("waiting for the clinet to connect...");
}

void loop() {
  if (deviceConnected) {

    if ((millis() - lastTime) > timerDelay) {

      // captures image from camera
      camera.run();

      uint8_t *imageBuffer = camera.getfb(); //raw image data (uint8_t is an 8 bit unsigned int)

      size_t imageSize = camera.getSize(); //gets image buffer size


      // breaks the image into chunks for BLE
      const size_t chunkSize = 20; // chunk size for ble data transfer

      for (size_t i = 0; i < imageSize; i += chunkSize) { //loop through img buffer in chuncks

        size_t len = min(chunkSize, imageSize - i);

        BLECharacteristic *imageCharacteristic = BLEDevice::getService(service_UUID)->getCharacteristic(characteristic_UUID); //gets a characteristic from a service using its uuid so we can work with it

        imageCharacteristic->setValue(imageBuffer + i, len); //sets characteristic val with current chunk of img data

        imageCharacteristic->notify(); //lets the client (laptop) know that new data is in the characteristic

      }

      Serial.println("Image sent");

      lastTime = millis(); //updates lastTime to give the current time in milliseconds so that the next img capture is exactly after 24 hours (or whatever set time)
    }
  }
}


