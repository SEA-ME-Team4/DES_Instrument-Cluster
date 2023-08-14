 #include <SPI.h>
#include <mcp2515.h>
/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif
#define slave 0x0F6
#define PIN_OUT 3
#define CUSTOM_DELAY 5000
#define lmillis() ((long)millis())
// struct can_frame recvMsg;
struct can_frame canMsg;
const int SPI_CS_PIN = 9;
MCP2515 mcp2515(SPI_CS_PIN); // Set CS pin
long lastAction;
volatile int count = 0;
void isrCount()
{
    count++;
}
void setup() {
    canMsg.can_id = slave;
    canMsg.can_dlc = 8;
    canMsg.data[0]= 0x00;
    canMsg.data[1]= 0x00;
    canMsg.data[2]= 0x00;
    canMsg.data[3]= 0x00;
    canMsg.data[4]= 0x00;
    canMsg.data[5]= 0x00;
    canMsg.data[6]= 0x00;
    canMsg.data[7]= 0x00;
    while(!Serial){};
    SERIAL.begin(115200);
    mcp2515.reset();
    mcp2515.setBitrate(CAN_1000KBPS, MCP_16MHZ);  //header file change
    mcp2515.setNormalMode();
    SERIAL.println("CAN BUS Shield init ok!");
    pinMode(PIN_OUT, INPUT);
    lastAction = lmillis() + CUSTOM_DELAY;
    attachInterrupt(digitalPinToInterrupt(PIN_OUT), isrCount, RISING);
}
// unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void loop() {
    if (lmillis() - lastAction >= 0) {
        detachInterrupt(digitalPinToInterrupt(PIN_OUT));
        lastAction = lmillis() + CUSTOM_DELAY;
        float div = CUSTOM_DELAY / 1000;
        double rpm = (count*3) / div; //[rpm] 
        double speed = rpm*3.40; // [mm/s]
        int int1_spd = speed;
        int int2_spd = round((speed - int1_spd)*100);
        canMsg.data[0] = int1_spd/256;
        canMsg.data[1] = int1_spd%256;
        canMsg.data[2] = int2_spd;
        // Serial.println("COUNT:"+String(count));
        // Serial.println("RPM:"+String(rpm));
        Serial.println("SPEED:"+String(speed)+" [mm/s]");
        Serial.println("int1_spd:"+String(int1_spd)+" [mm/s]");
        Serial.println("int2_spd:"+String(int2_spd)+" [mm/s]");
        Serial.println("");
        count = 0;
        attachInterrupt(digitalPinToInterrupt(PIN_OUT), isrCount, RISING);
    }
  
;
  mcp2515.sendMessage(&canMsg);
  //  Serial.println(canMsg);
   delay(100);
}