#include "menu.h"

#define CC_Button 16
#define CP_Button 4
#define BAT_Button 0
#define IS_CC_ON 0
#define IS_CP_ON 1
#define IS_BAT_ON 2

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


int8_t encoderTicks=0;
uint8_t var1[]={0,0,0,0};
uint8_t var2[]={0,0,0,0};
uint8_t pos=0;
uint8_t menu_select=0;
uint8_t selected_menu=0;
uint16_t readCurrent = 0;
uint16_t readVoltage = 0;
uint16_t readPower = 0;
uint32_t read_mAh = 0;
uint32_t set_val=0;
char unit[5];       //for changing decimal point on display
char disp_buff[20];
bool blink = true;
bool button_hold = false;
bool is_second_menu = false;
bool is_second_var = false;
bool display_stats = false;

menu CCMenu;
menu CPMenu;
menu BATMenu;
menu CurrentMenu;


void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}



void setup()
{
    pinMode(CC_Button,INPUT_PULLUP);
    pinMode(CP_Button,INPUT_PULLUP);
    pinMode(BAT_Button,INPUT_PULLUP);

    initStruct(&CCMenu, 0,"  CC MODE ","Set I","Set T","Start");
    initStruct(&CPMenu, 1,"  CP MODE ","Set P","Set T","Start");
    initStruct(&BATMenu, 2," BAT MODE ","Set I","Set V","Start");

    setCurrentMenu(&CurrentMenu, &CCMenu);
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

    if(digitalRead(CC_Button)==0 && digitalRead(CP_Button)==1 && digitalRead(BAT_Button)==1){
        setCurrentMenu(&CurrentMenu, &CCMenu);
        is_second_menu=false;
        zeroArray(var1);
        zeroArray(var2);
    }else if(digitalRead(CC_Button)==1 && digitalRead(CP_Button)==0 && digitalRead(BAT_Button)==1){
        setCurrentMenu(&CurrentMenu, &CPMenu);
        is_second_menu=false;
        zeroArray(var1);
        zeroArray(var2);
    }else if(digitalRead(CC_Button)==1 && digitalRead(CP_Button)==1 && digitalRead(BAT_Button)==0){
        setCurrentMenu(&CurrentMenu, &BATMenu);
        is_second_menu=false;
        zeroArray(var1);
        zeroArray(var2);
    }
    

    if (rotaryEncoder.encoderChanged()){   
        
        Serial.println(rotaryEncoder.readEncoder());
        encoderTicks=rotaryEncoder.readEncoder();

        if(is_second_menu == true){
            encoderTicks=encoderTicks%10;
            if(!is_second_var){
                var1[pos%5]=encoderTicks;  
                CurrentMenu.set_val1=ChangeArrayToInt(var1);
            }else if(is_second_var){      
                var2[pos%5]=encoderTicks; 
                CurrentMenu.set_val2=ChangeArrayToInt(var2);
            }

        }else if(is_second_menu == false){
            menu_select=encoderTicks%3;
        }
    
    }
    if (rotaryEncoder.isEncoderButtonClicked()){
        Serial.println("button pressed");

        if(is_second_menu == true){
            pos++;
        }else if(is_second_menu == false){
            
            switch (menu_select)
            {
            case 0:
                is_second_var=false;
                if(strcmp(CurrentMenu.line2,"Set I") == 0){
                    snprintf(unit,5,"mA");
                }else if(strcmp(CurrentMenu.line2,"Set P") == 0){
                    snprintf(unit,5,"W");
                }
                is_second_menu=true;
                break;
            case 1:
                is_second_var=true;
                if(strcmp(CurrentMenu.line3,"Set T") == 0){
                    snprintf(unit,5,"min");
                }else if(strcmp(CurrentMenu.line3,"Set V") == 0){
                    snprintf(unit,5,"V");
                }
                is_second_menu=true;
                break;
            case 2:
                is_second_var=false;
                display_stats = true;
                // Do smth to adjust parameters on a analog part

                break;
            
            default:
                break;
            }           
        }
    }
    if (rotaryEncoder.isEncoderButtonClicked(3000)){
        Serial.println("button pressed hold");  
        //pos++;
        button_hold=true;
        if(is_second_menu){
            if(pos%5!=4){

            if(!is_second_var)
            zeroArray(var1);
            else if(is_second_var)
            zeroArray(var2);

            }else{
            is_second_menu=false;
            }

        }else if(!is_second_menu){
            //is_second_menu=false;

        }

        if(display_stats){
            display_stats=false;
        }        
    }

    if(millis()%16==0){

        char buff[10];
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        
        if(is_second_menu && !display_stats){
        //display.drawLine(pos%5*1+pos%5*11,14,pos%5*1+pos%5*11+10,14,WHITE);
        if(pos%5!=4){
            display.fillRect(pos%5*1+pos%5*11,15,10,2,WHITE);
        } else if(pos%5==4){
            display.fillRect(42,39,44,2,WHITE);
        }

        if(!is_second_var){

        if(strcmp(unit,"V") == 0 || strcmp(unit,"W") == 0)
            snprintf(buff,10,"%d%d.%d%d%s",var1[0],var1[1],var1[2],var1[3],unit);
        else
            snprintf(buff,10,"%d%d%d%d%s",var1[0],var1[1],var1[2],var1[3],unit);

        display.setCursor(0, 0);
        display.println(buff);

        }else if(is_second_var){

        if(strcmp(unit,"V") == 0 || strcmp(unit,"W") == 0)
            snprintf(buff,10,"%d%d.%d%d %s",var2[0],var2[1],var2[2],var2[3],unit);
        else
            snprintf(buff,10,"%d%d%d%d %s",var2[0],var2[1],var2[2],var2[3],unit);

        display.setCursor(0, 0);
        display.println(buff);
   
        }
        display.setCursor(42, 20);
        display.println("BACK");
        display.setCursor(0, 40);
        display.println(sizeof(var1)/sizeof(uint8_t));         

        }else if(!is_second_menu && !display_stats){
        display.setCursor(0, 0);
        display.println(CurrentMenu.line1);
        display.setCursor(16, 16);
        display.println(CurrentMenu.line2);
        display.setCursor(16, 32);
        display.println(CurrentMenu.line3);
        display.setCursor(16, 48);
        display.println(CurrentMenu.line4);
        display.fillRect(0,menu_select*16+16,15,15,WHITE);
        }else if(display_stats){
            switch (CurrentMenu.id)
            {
            case IS_CC_ON:
                display.setTextSize(1);
                display.setCursor(0, 0);
                snprintf(disp_buff,20,"%s%d%s %d%s","Set:",CurrentMenu.set_val1,"mA",CurrentMenu.set_val2,"min");
                display.println(disp_buff);
                break;
            case IS_CP_ON:
                display.setTextSize(1);
                display.setCursor(0, 0);
                snprintf(disp_buff,20,"%s%.2f%s %d%s","Set:",(float)(CurrentMenu.set_val1)/100,"W",CurrentMenu.set_val2,"min");
                display.println(disp_buff);
                break;
            case IS_BAT_ON:
                display.setTextSize(1);
                display.setCursor(0, 0);
                snprintf(disp_buff,20,"%s%d%s %.2f%s","Set:",CurrentMenu.set_val1,"mA",(float)(CurrentMenu.set_val2)/100,"V");
                display.println(disp_buff);
                break;
            default:
                break;
            }   
        }
        display.display();
    }   
}