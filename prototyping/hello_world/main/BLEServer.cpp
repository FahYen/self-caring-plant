//add this file to the cmakelist.txt file

#include <iostream>
#include <string>

#include <BLEDevice.h> //main library that manages BLE. turns on bluetooth, etc. [makes the ble stack]
#include <BLEServer.h> //the server for BLE
#include <BLEUtils.h> //has helper functions
#include <BLE2902.h> //library for descriptoes {they describe how a ble characteristic works}. ex: enables notifications to connected device

using namespace std;


//from bledevice.h, run createServer() to create the BLE server
//use bleserver library to manage the server :
 /*track connected devices, define services [ex: humidity], handles connection and disconnections with devices*/


 class BLEServer {
    public:
        BLEServer(const string &deviceName, const string& serviceUUID, const string& attrUUID);
        void init();
        void update(const std::string& info);
    
    private:
        string deviceName;
        string serviceUUID;
        string attrUUID;
        bool deviceIsConnected;
 }