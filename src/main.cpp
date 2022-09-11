#include <main.h>
#include <smileHappy.h>
#include <smileSad.h>
#include <DNSServer.h> 
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <WiFi.h>

AsyncWebServer server(80);
DNSServer dns;

char raw_data;
char msg;


void setup() {
    AsyncWiFiManager manager(&server, &dns);
    Serial.begin(115200);

    //manager.resetSettings();
    manager.autoConnect("Pixel LED Robbyson");

	InitializeLEDPanel();
    FastLED.clear(true);
}

void loop() {
    // characteristicTX->setValue("Hello World");
    // characteristicTX->notify();
    if ( Serial.available() > 0) {
        msg = Serial.read();
    }
    else{
        if (msg == '4') {
            msg = 5;
        }
        else{
            msg = 5;
        }
        delay(1000);
    }
    if(msg != raw_data || msg == '4' || msg == '5' || msg == '6') {
        raw_data = msg;
        if(raw_data == '1') {
            blink(255, 255, 255);
            blink(0, 0, 0);
        }
        else if(raw_data == '2') {
            goCrazy();
            FastLED.clear();
            FastLED.show();
        }
        else if(raw_data == '3') {
            Fire();
            FastLED.clear();
            FastLED.show();
        }
        else if(raw_data == '4'){
            //FastLED.clear(true);4355
            EVERY_N_MILLISECONDS(100) {
                memcpy(&panel[0], &smileHappy[0], NUM_LEDS * sizeof(CRGB));
                FastLED.show();
            }
        }
        else if(raw_data == '5'){
            //FastLED.clear(true);
            EVERY_N_MILLISECONDS(100) {
                memcpy(&panel[0], &smileSad[0], NUM_LEDS * sizeof(CRGB));
                FastLED.show();
            }
        }
        else if(raw_data == '6'){
            //FastLED.clear(true);
            fill_solid(panel, NUM_LEDS, CRGB::Red);
            FastLED.show();
            delay(500);
            fill_solid(panel, NUM_LEDS, CRGB::Green);
            FastLED.show();
            delay(500);
            fill_solid(panel, NUM_LEDS, CRGB::Blue);
            FastLED.show();
            delay(500);
        }
        else if(raw_data == 'r') {
            fill_solid(panel, NUM_LEDS, CRGB::Red);
            FastLED.show();
        }
        else if(raw_data == 'g') {
            fill_solid(panel, NUM_LEDS, CRGB::Green);
            FastLED.show();
        }
        else if(raw_data == 'b') {
            fill_solid(panel, NUM_LEDS, CRGB::Blue);
            FastLED.show();
        }
        else if(raw_data == '0') {
            FastLED.clear();
            FastLED.show();
        }
        //Serial.println("Finalizado");
    }
    // if(isImage) {
    //     setImage(parseImg(raw_data));
    // }
    // else if(isAnimation) {
    //     setAnimation(parseAni(raw_data));
    // }
    // setImage(parseImg(raw_data));
    //delay(DELAY_TIME * 100);
}