// *** SentandReceive ***

// This example expands the previous Receive example. The Arduino will now send back a status.
// It adds a demonstration of how to:
// - Handle received commands that do not have a function attached
// - Send a command with a parameter to the PC

#include <CmdMessenger.h>  // CmdMessenger


// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial1);

// This is the list of recognized commands. These can be commands that can either be sent or received. 
// In order to receive, attach a callback function to these events

enum
{
  rRobotGo              , // Command to request led to be set in specific state
  rRobotStop              , // Command to report status
  rRobotDefault        ,
};



// Callback function that sets led on or off
void sendGo()
{
  Serial.println("go");
  cmdMessenger.sendCmd(rRobotGo,true);
}

void sendStop()
{
  Serial.println("stop");
  cmdMessenger.sendCmd(rRobotStop,true);
}

// Setup function
void setup() 
{
  // Listen on serial connection for messages from the PC
  Serial.begin(115200); 
  Serial1.begin(600); 
  // Adds newline to every command
  cmdMessenger.printLfCr();   
  cmdMessenger.sendCmd(rRobotDefault,"Arduino has started!");

  
}

// Loop function
void loop() 
{
  // Process incoming serial data, and perform callbacks
//  cmdMessenger.feedinSerialData();
    digitalWrite(13, HIGH); // sendGo();
    delay(20);
    digitalWrite(13, LOW); // sendGo();
    delay(2000);
    
}


