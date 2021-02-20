#define none777
#ifdef none777
#include <DNSServer.h>
#include <ESPUI.h>
#include <IOTAppStory.h>                                    // IotAppStory.com library

const byte DNS_PORT = 53;
IPAddress apIP( 192, 168, 1, 1 );
DNSServer dnsServer;

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

//const char* hostname = "espui";

uint16_t button1;
uint16_t switchOne;
uint16_t status;
uint16_t freeHeapCTL;

void numberCall( Control* sender, int type ) {
  Serial.println( sender->value );
}

void textCall( Control* sender, int type ) {
  Serial.print("Text: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println( sender->value );}

void slider( Control* sender, int type ) {
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println( sender->value );}

void buttonCallback( Control* sender, int type ) {
  switch ( type ) {
    case B_DOWN:
      Serial.println( "Button DOWN" );
      sender->color = ControlColor::Carrot;
      ESPUI.updateControl( sender );
      break;

    case B_UP:
      Serial.println( "Button UP" );
      sender->color = ControlColor::Peterriver;
      ESPUI.updateControl( sender );
      /*Serial.println ("after ESPUI.updateControl");
      dnsServer.stop();
      Serial.println ("after dnsServer.stop");
      delay (500);*/
      {
        void IAScallHome (void);
        IAScallHome ();
        Serial.println ("after IAScallHome");
      }
      /*delay (500);
      dnsServer.start (DNS_PORT, "*", apIP );
      delay (500);
      Serial.println ("after dnsServer.start");*/
      break;
  }
}

/*void buttonExample( Control* sender, int type ) {
  switch ( type ) {
    case B_DOWN:
      Serial.println( "Status: Start" );
      ESPUI.updateControlValue( status, "Start" );
    
      ESPUI.getControl( button1 )->color = ControlColor::Carrot;
      ESPUI.updateControl( button1 );
      break;

    case B_UP:
      Serial.println( "Status: Stop" );
      ESPUI.updateControlValue( status, "Stop" );
   
      ESPUI.getControl( button1 )->color = ControlColor::Peterriver;
      ESPUI.updateControl( button1 );
      break;
  }
}

void switchExample( Control* sender, int value ) {
  switch ( value ) {
    case S_ACTIVE:
      Serial.print( "Active:" );
      break;

    case S_INACTIVE:
      Serial.print( "Inactive" );
      break;
  }

  Serial.print( " " );
  Serial.println( sender->id );
}*/

void selectExample( Control* sender, int value ) {
  Serial.print("Select: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println( sender->value );
}

void setupESPUI (void) {

  dnsServer.start (DNS_PORT, "*", apIP);
  Serial.println( "\n\nWiFi parameters:" );
  Serial.print( "Mode: " );
  Serial.println( WiFi.getMode() == WIFI_AP ? "Station" : "Client" );
  Serial.print( "IP address: " );
  Serial.println( WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP() );

  uint16_t tab1 = ESPUI.addControl( ControlType::Tab, "Control", "Control");
  uint16_t tab2 = ESPUI.addControl( ControlType::Tab, "Params", "Params");
  uint16_t tab3 = ESPUI.addControl( ControlType::Tab, "Stats", "Stats");
  //uint16_t tab1 = ESPUI.addControl( ControlType::Tab, "Settings 1", "Settings 1" );
 // uint16_t tab2 = ESPUI.addControl( ControlType::Tab, "Settings 2", "Settings 2" );
//  uint16_t tab3 = ESPUI.addControl( ControlType::Tab, "Settings 3", "Settings 3" );

  // shown above all tabs
  status = ESPUI.addControl( ControlType::Label, "Status:", "Stop", ControlColor::Turquoise );

  // tabbed controls
  uint16_t select1 = ESPUI.addControl( ControlType::Select, "Select:", "", ControlColor::Alizarin, tab1, &selectExample );
    ESPUI.addControl( ControlType::Option, "Option1", "Opt1", ControlColor::Alizarin, select1 );
    ESPUI.addControl( ControlType::Option, "Option2", "Opt2", ControlColor::Alizarin, select1 );
    ESPUI.addControl( ControlType::Option, "Option3", "Opt3", ControlColor::Alizarin, select1 );
  
  freeHeapCTL = ESPUI.addControl (ControlType::Label, "Free Heap:", "0", ControlColor::Emerald, tab3);

  button1 = ESPUI.addControl( ControlType::Button, "Update firmware", "Press", ControlColor::Peterriver, tab2, &buttonCallback );
/*  ESPUI.addControl( ControlType::Button, "Other Button", "Press", ControlColor::Wetasphalt, tab1, &buttonExample );
  switchOne = ESPUI.addControl( ControlType::Switcher, "Switch one", "", ControlColor::Alizarin, tab3, &switchExample );
  ESPUI.addControl( ControlType::Slider, "Slider one", "30", ControlColor::Alizarin, tab1, &slider );
  ESPUI.addControl( ControlType::Slider, "Slider two", "100", ControlColor::Alizarin, tab3, &slider );
  ESPUI.addControl( ControlType::Number, "Number:", "50", ControlColor::Alizarin, tab3, &numberCall );*/

  ESPUI.begin("RoboKite BASE");
//  ESPUI.beginSPIFFS("RoboKite BASE");
}

void loopESPUI (void) {
  dnsServer.processNextRequest();

  static uint32_t savedFreeHeap {0};
  static unsigned long lastMillis {0};

  uint32_t freeHeap = ESP.getFreeHeap ();
  if ((savedFreeHeap != freeHeap) && (millis () - lastMillis > 1000)) {
    savedFreeHeap = freeHeap;
    lastMillis = millis ();
    ESPUI.updateControlValue( freeHeapCTL, String(freeHeap));
  }
}

#else
  //void setupESPUI ( void ) {}
#endif