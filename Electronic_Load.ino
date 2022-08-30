#include "menu.h"

#if defined(ESP8266)
#define ROTARY_ENCODER_A_PIN D6
#define ROTARY_ENCODER_B_PIN D5
#define ROTARY_ENCODER_BUTTON_PIN D7
#else
#define ROTARY_ENCODER_A_PIN 32
#define ROTARY_ENCODER_B_PIN 5
#define ROTARY_ENCODER_BUTTON_PIN 25
#endif
#define ROTARY_ENCODER_STEPS 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);

int16_t menu_level[6];
//char buff[10];
int8_t encoderTicks=0;
uint8_t var[]={0,0,0,0};
uint8_t inv_arr[]={0,0,0,0};
uint8_t pos=0;
uint32_t set_val=0;
bool blink = true;
bool button_hold=false;

menu CCMenu;


void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}



void setup()
{

    initStruct(CCMenu,"line1","line2","line3","line4");

    Serial.begin(115200);
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    rotaryEncoder.setBoundaries(0, 1000, false); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
    rotaryEncoder.setAcceleration(250);

      if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
    }
    delay(200);
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
  // Display static text
    display.println("Booting");
    display.display(); 
}

void loop()
{

    if (rotaryEncoder.encoderChanged())
    {   
        
        Serial.println(rotaryEncoder.readEncoder());
        encoderTicks=rotaryEncoder.readEncoder();
        encoderTicks=encoderTicks%10;
        var[pos%5]=encoderTicks;
        
    
    }
    if (rotaryEncoder.isEncoderButtonClicked())
    {
        Serial.println("button pressed");  
        pos++;

    }
    if (rotaryEncoder.isEncoderButtonClicked(200))
    {
        Serial.println("button pressed hold");  
        //pos++;
        button_hold=true;
        zeroArray(var);
        
    }else{
        button_hold=false;
    }




    if(millis()%100==0){
        blink=!blink;
    }


    if(blink){
    //display.drawLine(pos%5*10,10,pos%5*10+10,10,WHITE);
    //display.display();
    }else{
    //display.display();
    }

    if(millis()%16==0){
        char buff[10];
        display.clearDisplay();
        display.drawLine(pos%5*10,16,pos%5*10+10,16,WHITE);
        snprintf(buff,6,"%d%d%d%d",var[0],var[1],var[2],var[3]);
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.println(buff); 
        display.setCursor(0, 20);

        set_val=ChangeArrayToInt(var);

        display.println(set_val); 
        display.setCursor(0, 40);
        display.println(sizeof(var)/sizeof(uint8_t)); 

        display.display();
    }
    
}