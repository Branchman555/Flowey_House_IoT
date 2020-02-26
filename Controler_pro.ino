#include <SPI.h>
#include <Wire.h>
#include <math.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_APDS9960.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_APDS9960 apds;
WiFiClient espClient;
PubSubClient mqttClient(espClient);
StaticJsonDocument<256> jsonDoc;


static const unsigned char PROGMEM flowey_bmp[4][63] =
{
    0x00, 0x00, 0x00, 0x03,                                                                                             
    0x8e, 0x00, 0x06, 0x73,                                                                                             
    0x00, 0x01, 0xfc, 0x00,                                                                                             
    0x3b, 0xae, 0xe0, 0x7b,                                                                                            
    0xfe, 0xf0, 0x3b, 0x76,                                                                                            
    0xe0, 0x05, 0x8d, 0x00,                                                                                             
    0x0e, 0xfb, 0x80, 0x1f,                                                                                             
    0x07, 0xc0, 0x1f, 0xaf,                                                                                             
    0xc0, 0x0e, 0x33, 0x80,                                                                                             
    0x00, 0x30, 0x00, 0x00,                                                                                            
    0x60, 0x00, 0x00, 0x40,                                                                                            
    0x00, 0x00, 0x60, 0x00,                                                                                            
    0x00, 0x20, 0x00, 0x00,                                                                                            
    0x30, 0x00, 0x00, 0x30,                                                                                            
    0x00, 0x00, 0x70, 0x00,                                                                                            
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,                                                                                            
    0x00, 0x00, 0x00, 0x00,                                                                                            
    0x00, 0x03, 0x8e, 0x00,                                                                                             
    0x06, 0x73, 0x00, 0x01,                                                                                              
    0xfc, 0x00, 0x3b, 0xae,                                                                                            
    0xe0, 0x7b, 0xfe, 0xf0,                                                                                            
    0x3b, 0x76, 0xe0, 0x05,                                                                                             
    0x8d, 0x00, 0x0e, 0xfb,                                                                                             
    0x80, 0x1f, 0x07, 0xc0,                                                                                             
    0x1f, 0xaf, 0xc0, 0x0e,                                                                                             
    0x33, 0x80, 0x00, 0x30,                                                                                            
    0x00, 0x00, 0x60, 0x00,                                                                                            
    0x00, 0x20, 0x00, 0x00,                                                                                            
    0x30, 0x00, 0x00, 0x30,                                                                                            
    0x00, 0x00, 0x70, 0x00,                                                                                            
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,                                                                                            
    0x00, 0x00, 0x00, 0x00,                                                                                            
    0x00, 0x00, 0x00, 0x00,                                                                                            
    0x00, 0x00, 0x00, 0x03,                                                                                             
    0x8e, 0x00, 0x06, 0x73,                                                                                             
    0x00, 0x01, 0xfc, 0x00,                                                                                             
    0x3b, 0xae, 0xe0, 0x7b,                                                                                            
    0xfe, 0xf0, 0x3b, 0x76,                                                                                            
    0xe0, 0x05, 0x8d, 0x00,                                                                                             
    0x0e, 0xfb, 0x80, 0x1f,                                                                                             
    0x07, 0xc0, 0x1f, 0xaf,                                                                                             
    0xc0, 0x0e, 0x33, 0x80,                                                                                             
    0x00, 0x30, 0x00, 0x00,                                                                                            
    0x30, 0x00, 0x00, 0x30,                                                                                            
    0x00, 0x00, 0x70, 0x00,                                                                                            
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,                                                                                            
    0x00, 0x00, 0x00, 0x00,                                                                                            
    0x00, 0x03, 0x8e, 0x00,                                                                                             
    0x06, 0x73, 0x00, 0x01,                                                                                              
    0xfc, 0x00, 0x3b, 0xae,                                                                                            
    0xe0, 0x7b, 0xfe, 0xf0,                                                                                            
    0x3b, 0x76, 0xe0, 0x05,                                                                                             
    0x8d, 0x00, 0x0e, 0xfb,                                                                                             
    0x80, 0x1f, 0x07, 0xc0,                                                                                             
    0x1f, 0xaf, 0xc0, 0x0e,                                                                                             
    0x33, 0x80, 0x00, 0x30,                                                                                            
    0x00, 0x00, 0x60, 0x00,                                                                                            
    0x00, 0x20, 0x00, 0x00,                                                                                            
    0x30, 0x00, 0x00, 0x30,                                                                                            
    0x00, 0x00, 0x70, 0x00,                                                                                            
    0x00, 0x00, 0x00
};

static const unsigned char PROGMEM flowey_dead_bmp[63] =
{
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x78, 
    0x00, 0x03, 0x09, 0x00, 
    0x1e, 0x70, 0xc0, 0x3d, 
    0xf9, 0x40, 0x3b, 0xd9, 
    0x80, 0x1b, 0x8b, 0xb0, 
    0x03, 0xde, 0xd0, 0x09, 
    0xfc, 0x58, 0x1c, 0xfe, 
    0xd8, 0x1f, 0x0f, 0xb8, 
    0x0e, 0x27, 0x30, 0x0e, 
    0x60, 0x80, 0x00, 0xc7, 
    0xc0, 0x00, 0xe3, 0xc0, 
    0x00, 0x70, 0xc0, 0x00, 
    0x18, 0x00, 0x00, 0x38, 
    0x00, 0x00, 0x7c, 0x00, 
    0x00, 0x00, 0x00
};

static const unsigned char PROGMEM Status_Icon[4][5] =
{
    0xf8, 0x80, 0xf8, 0x80, 
    0x80, 0xf8, 0x88, 0xf8, 
    0x80, 0x80, 0xf8, 0x20, 
    0x20, 0x20, 0x20, 0x20, 
    0x70, 0xf8, 0xf8, 0x00
};

#define UPDATE_INTERVAL_1 400L
#define UPDATE_INTERVAL_2 15L

#define MAIN 0
#define FEED 1
#define PLAY 2
#define STOVE 3
#define CLEAN 4
#define RESET 5

#define buttonEN 2
#define pulseA 12
#define pulseB 13

char ssid[] = "TestH";
char password[] = "31415926";

const char* mqttServer= "54.159.204.45";
const int mqttPort = 1883;
const char* topic_ctl = "/sensor/ctl/";
const char* topic_json = "/sensor/json/";
char mqString[150] = "";

unsigned long prevUpdateTime[5] = {0L,};
unsigned long currentTime = 0L;
unsigned int count = 0;
unsigned int poo = 2;
unsigned int buttonFlag = 0;
unsigned int EventFlag = 0;
unsigned int PlayCount = 0;
int menu_status = 0;

int MSB = 0;
int LSB = 0;
int sum = 0;
int lastEncoded = 0b0000;
int encoded = 0b0000;
int encoderValue = 0;
int encoderSelect = 0;
char buf[20];

unsigned int Dead_flag = 0;
unsigned int hunger_val = 0;
unsigned int play_val = 0;
unsigned int temp_val = 0;
unsigned int hum_val = 0;
unsigned int cds_val = 0;

void callback(char* topic, byte* payload, unsigned int length){
    
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    if((char)payload[0] == '1'){
        if(Dead_flag == 0){
            Dead_flag = 1;
            menu_status = -1;
        }
    }else{
        Dead_flag = 0;
    }
    deserializeJson(jsonDoc, (char*)payload);
    hunger_val = jsonDoc["HUNGER"];
    play_val = jsonDoc["PLAY"];
    temp_val = jsonDoc["TEMP"];
    hum_val = jsonDoc["HUM"];
    cds_val = jsonDoc["Cds"];
    poo = jsonDoc["POO"];
    // Switch on the LED if an 1 was received as first character
}

void WiFisetup()
{                                              
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to the WiFi network");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void MQTTsetup()
{
    mqttClient.setServer(mqttServer, mqttPort);
    
    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");
        if (mqttClient.connect("ESP32Client")) {
            Serial.println("connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(mqttClient.state());
            delay(2000);
        }
    }
    //mqttClient.subscribe(topic_ctl);
    mqttClient.subscribe(topic_json);
    mqttClient.publish(topic_ctl, "ESP32 logged in");
    mqttClient.setCallback(callback);
}

void setup() {
    Serial.begin(9600);
    pinMode(buttonEN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonEN), DeadButton, FALLING);
    pinMode(pulseA, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pulseA), handleEncoder, CHANGE);
    pinMode(pulseB, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pulseB), handleEncoder, CHANGE);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.display();
    delay(2000);
    if(!apds.begin()){
        Serial.println("failed to initialize device! Please check your wiring.");
    }
    else Serial.println("Device initialized!");
    
    apds.enableProximity(0);
    apds.enableGesture(0);
    WiFisetup();
    mqttClient.setServer(mqttServer, mqttPort);
    
    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");
        if (mqttClient.connect("ESP32Client")) {
            Serial.println("connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(mqttClient.state());
            delay(2000);
        }
    }
    //mqttClient.subscribe(topic_ctl);
    mqttClient.subscribe(topic_json);
    mqttClient.publish(topic_ctl, "ESP32 logged in");
    mqttClient.setCallback(callback);
}

void loop() {
    mqttClient.loop();
    Serial.println(Dead_flag);
    unsigned long currentTime = millis();
    
    if(currentTime > prevUpdateTime[0] + UPDATE_INTERVAL_1) {
        count++;
        if(count > 3) count = 0;
        
        prevUpdateTime[0] = currentTime;
    }
    if(currentTime > prevUpdateTime[1] + UPDATE_INTERVAL_2) {
        
        //display.display(); // Show the display buffer on the screen

        display.display();
        prevUpdateTime[1] = currentTime;
    }
    if(Dead_flag == 0){
        display.clearDisplay(); // Clear the display buff
        display.drawRoundRect(0, 0, display.width(), display.height(),3, SSD1306_WHITE);
        display.drawBitmap(7, 7, flowey_bmp[count], 21, 21, SSD1306_WHITE);
        display.drawBitmap(35, 5, Status_Icon[0], 5, 5, SSD1306_WHITE);
        display.fillRect(44, 6, (int)(20*(hunger_val/30.0)), 3, WHITE);
        display.drawBitmap(35, 12, Status_Icon[1], 5, 5, SSD1306_WHITE);
        display.fillRect(44, 13, (int)(20*(play_val/30.0)), 3, WHITE);
        display.drawBitmap(35, 19, Status_Icon[2], 5, 5, SSD1306_WHITE);
        display.fillRect(44, 20, (int)(20*(temp_val/35.0)), 3, WHITE);
        display.drawBitmap(35, 25, Status_Icon[3], 5, 5, SSD1306_WHITE);
        if(poo > 0)    display.fillRect(44, 27, 8, 2, WHITE);
        if(poo > 1)    display.fillRect(55, 27, 8, 2, WHITE);
    }else if(Dead_flag == 1){
        display.clearDisplay();
        display.drawRoundRect(0, 0, display.width(), display.height(),3, SSD1306_WHITE);
        display.setTextSize(3);             
        display.setTextColor(WHITE);        
        display.setCursor(15,10);             
        display.print("Dead...");             
    }else if(Dead_flag == 2){
        display.clearDisplay();
        display.drawRoundRect(0, 0, display.width(), display.height(),3, SSD1306_WHITE);
        display.drawBitmap(7, 7, flowey_dead_bmp, 21, 21, SSD1306_WHITE);            
    }
    if(menu_status == MAIN){
        if(EventFlag == 0){
            display.drawRoundRect(70, 5, 55, 22, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(WHITE);        
            if(hunger_val<30) {
                display.setCursor(76,7);
                display.print("Hungry..");
                display.setCursor(76,17);
                display.print("TT");
            }
            else if(play_val<30) {
                display.setCursor(76,7);
                display.print("Boring~");
            }
            else if(temp_val<15) {
                display.setCursor(76,7);
                display.print("Isn't it");
                display.setCursor(76,17);
                display.print("Cold?");
            }
            else if(poo>0) {
                display.setCursor(76,7);
                display.print("I shit..");
            }
            else {
                display.setCursor(76,7);
                display.print("Howdy!!");
                display.setCursor(76,17);
                display.print("Flowey!");
            }
            if(buttonFlag == 1){
                Serial.println("MAIN");
                mqttClient.publish(topic_ctl, "MAIN");
                buttonFlag = 0; 
                EventFlag = 1;
            }    
        }else{
            display.fillRoundRect(70, 5, 55, 22, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(BLACK);
            sprintf(buf,"Temp:%2d",temp_val);        
            display.setCursor(76,7);
            display.print(buf);
            sprintf(buf,"Hum:%2d",hum_val);
            display.setCursor(76,17);
            display.print(buf);
        }
    }else if(menu_status == FEED){
        if(EventFlag == 0){
            display.drawRoundRect(83, 5, 35, 17, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(WHITE);        
            display.setCursor(90,10);             
            display.print("FEED");
            if(buttonFlag == 1){
                Serial.println("FEED");
                mqttClient.publish(topic_ctl, "FEED");
                buttonFlag = 0; 
                EventFlag = 1;
            }    
        }else{
            display.fillRoundRect(83, 5, 35, 17, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(BLACK);        
            display.setCursor(90,10);             
            display.print("FEED");
        }
    }else if(menu_status == PLAY){
        if(EventFlag == 0){
            display.drawRoundRect(83, 5, 35, 17, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(WHITE);        
            display.setCursor(90,10);             
            display.print("PLAY");
            if(buttonFlag == 1){
                Serial.println("PLAY");
                buttonFlag = 0; 
                EventFlag = 1;
                apds.enableProximity(true);
                apds.enableGesture(true);
            }    
        }else{
            uint8_t gesture = apds.readGesture();
            if(gesture == APDS9960_LEFT || gesture == APDS9960_RIGHT){
                PlayCount++;
            }
            if(PlayCount == 4){
                apds.enableProximity(0);
                apds.enableGesture(0);
                mqttClient.publish(topic_ctl, "PLAY");
                PlayCount++;
            }
            display.fillRoundRect(83, 5, 35, 17, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(BLACK);        
            display.setCursor(90,10);
            display.print("PLAY");             
            if(PlayCount > 0)    display.fillRect(83, 25, 5, 3, WHITE);
            if(PlayCount > 1)    display.fillRect(91, 25, 5, 3, WHITE);
            if(PlayCount > 2)    display.fillRect(99, 25, 5, 3, WHITE);
            if(PlayCount > 3)    display.fillRect(107, 25, 5, 3, WHITE);
        }
    }else if(menu_status == STOVE){
        if(EventFlag == 0){
            display.drawRoundRect(83, 5, 40, 17, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(WHITE);        
            display.setCursor(90,10);             
            display.print("STOVE");            
            if(buttonFlag == 1){
                Serial.println("STOVE");
                mqttClient.publish(topic_ctl, "STOVE");
                buttonFlag = 0; 
                EventFlag = 1;
            }    
        }else{
            display.fillRoundRect(83, 5, 40, 17, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(BLACK);        
            display.setCursor(90,10);             
            display.print("STOVE");
        }
    }else if(menu_status == CLEAN){
        if(EventFlag == 0){
            display.drawRoundRect(83, 5, 40, 17, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(WHITE);        
            display.setCursor(90,10);             
            display.print("CLEAN");
            if(buttonFlag == 1){
                Serial.println("CLEAN");
                mqttClient.publish(topic_ctl, "CLEAN");
                buttonFlag = 0; 
                EventFlag = 1;
            }    
        }else{
            display.fillRoundRect(83, 5, 40, 17, 2, WHITE);
            display.setTextSize(1);             
            display.setTextColor(BLACK);        
            display.setCursor(90,10);             
            display.print("CLEAN");
        }
    }else if(menu_status == RESET){
        display.drawRoundRect(83, 5, 40, 17, 2, WHITE);
        display.setTextSize(1);             
        display.setTextColor(WHITE);        
        display.setCursor(90,10);             
        display.print("RESET");
        if(EventFlag == 0){
            if(buttonFlag == 1){
                Serial.println("RESET");
                mqttClient.publish(topic_ctl, "RESET");
                buttonFlag = 0; 
                EventFlag = 1;
                menu_status = MAIN;
            }    
        }
    }
}

void testanimate() {


    //for(;;) { // Loop forever...
        display.clearDisplay(); // Clear the display buffer
        
        // Draw each snowflake:
        display.drawBitmap(64, 10, flowey_bmp[0], 21, 21, SSD1306_WHITE);
        //display.drawBitmap(64, 10, flowey_bmp[1], 21, 21, SSD1306_WHITE);
        //display.drawBitmap(64, 10, flowey_bmp[2], 21, 21, SSD1306_WHITE);
        display.display(); // Show the display buffer on the screen
        delay(2000);        // Pause for 1/10 second
    //}
}

ICACHE_RAM_ATTR void handleEncoder()
{
    MSB = digitalRead(pulseA);
    LSB = digitalRead(pulseB);
    encoded = (MSB << 1) | LSB;
    sum = (lastEncoded << 2) | encoded;
    if(sum == 0b1101 || sum == 0b0100 || sum == 0b1011 || sum == 0b0010) encoderValue++;
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue--;
    lastEncoded = encoded;
    if(Dead_flag == 0){
        if(encoderValue > 3){
            if(menu_status == PLAY && EventFlag == 1){
                apds.enableProximity(0);
                apds.enableGesture(0);
                PlayCount = 0;
            }
            menu_status++;
            if(menu_status > 5) menu_status = MAIN;
            encoderValue = 0;
            EventFlag = 0;
            buttonFlag = 0;
        }else if(encoderValue < -3){
            if(menu_status == PLAY && EventFlag == 1){
                apds.enableProximity(0);
                apds.enableGesture(0);
                PlayCount = 0;
            }
            menu_status--;
            if(menu_status < 0) menu_status = RESET;
            encoderValue = 0;
            EventFlag = 0;
            buttonFlag = 0;
        }
    }
    
    //encoderValue = encoderValue > 1024 ? 1024 : encoderValue;
    //encoderValue = encoderValue < 0 ? 0 : encoderValue;
}

ICACHE_RAM_ATTR void DeadButton()
{
    if(Dead_flag == 1){
        Dead_flag = 2;
        menu_status = RESET;            
    }
    else if(Dead_flag == 2){
        buttonFlag = 1;
        encoderValue = 0;          
    }
    else{
        buttonFlag = 1;
        encoderValue = 0;
    }
    
}
