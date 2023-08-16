# CAN Communication

생성자: Daekyung La
생성 일시: 2023년 8월 16일 오전 9:44
태그: 진행중

### ****Table of Contents****

- **2 Channel CAN BUS FD Shield for Raspberry Pi**
- **CAN-BUS Shield V2.0**
- **Connection**

### Reference

- [Raspberry Pi](https://pinout.xyz/pinout/pin3_gpio2/)
- **[2 Channel CAN BUS FD Shield for Raspberry Pi](https://wiki.seeedstudio.com/2-Channel-CAN-BUS-FD-Shield-for-Raspberry-Pi/)**
- **[How to install an Arduino library](https://wiki.seeedstudio.com/How_to_install_Arduino_Library/)**
- **[CAN-BUS Shield V2.0](https://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/)**

### 1.  **2 Channel CAN BUS FD Shield for Raspberry Pi**

![Untitled](CAN%20Communication%206b3f5eb435cc486eba6f4117370d457d/Untitled.png)

- hardware overview

![Untitled](CAN%20Communication%206b3f5eb435cc486eba6f4117370d457d/Untitled%201.png)

![Untitled](CAN%20Communication%206b3f5eb435cc486eba6f4117370d457d/Untitled%202.png)

- software
    
    **• Step 1.** Open **config.txt** file
    
    ```bash
    sudo nano /boot/config.txt
    ```
    
    • **Step 2**. Add the following line at the end of the file
    
    ```bash
    dtoverlay=seeed-can-fd-hat-v2
    ```
    
    • **Step 3**. Press **Ctrl + x**, press **y** and press **Enter** to **save** the file
    • **Step 4**. **Reboot** Raspberry Pi
    
    ```bash
    sudo reboot
    ```
    
    • **Step5**. Check the kernel log to see if CAN-BUS HAT was initialized successfully. You will also see **can0** and **can1** appear in the list of ifconfig results
    
    ```bash
    sudo ip link set can0 up type can bitrate 1000000   dbitrate 8000000 restart-ms 1000 berr-reporting on fd on
    sudo ip link set can1 up type can bitrate 1000000   dbitrate 8000000 restart-ms 1000 berr-reporting on fd on
    
    sudo ifconfig can0 txqueuelen 65536
    sudo ifconfig can1 txqueuelen 65536
    ```
    
    • **Step 6**. Open two terminal windows and enter the following commands in the Windows to test can fd protocol.
    
    ```bash
    #send data
    cangen can0 -mv
    ```
    
    ```bash
    #dump data
    candump can0
    ```
    

### 2. **CAN-BUS Shield V2.0**

![Untitled](CAN%20Communication%206b3f5eb435cc486eba6f4117370d457d/Untitled%203.png)

![Untitled](CAN%20Communication%206b3f5eb435cc486eba6f4117370d457d/Untitled%204.png)

- hardware overview
    1. **DB9 Interface** - to connect to OBDII Interface via a DBG-OBD Cable.
    2. **V_OBD** - It gets power from OBDII Interface (from DB9)
    3. **Led Indicator**:
        - **PWR**: power
        - **TX**: blink when the data is sending
        - **RX**: blink when there's data receiving
        - **INT**: data interrupt
    4. **Terminal** - CAN_H and CAN_L
    5. **Arduino UNO pin out**
    6. **Serial Grove connector**
    7. **I2C Grove connector**
    8. **ICSP pins**
    9. **IC** - MCP2551, a high-speed CAN transceiver ([datasheet](https://files.seeedstudio.com/wiki/CAN_BUS_Shield/resource/Mcp2551.pdf))
    10. **IC** - MCP2515, stand-alone CAN controller with SPI interface
    
- software settings
1. Intstall an  [Arduino library](https://wiki.seeedstudio.com/How_to_install_Arduino_Library/),  download **[Seeed_Arduino_CAN](https://github.com/Seeed-Studio/Seeed_Arduino_CAN)**
2. Open the **send** example (**File > Examples > Seeed_Arduino_CAN > send**) and upload to the **master**.

![Untitled](CAN%20Communication%206b3f5eb435cc486eba6f4117370d457d/Untitled%205.png)

or copy the following to the Arduino IDE and upload:

```cpp
#include <SPI.h>
#include "mcp2515_can.h"

/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif

const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

void setup() {
    SERIAL.begin(115200);
    while(!Serial){};

    while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
        SERIAL.println("CAN BUS Shield init fail");
        SERIAL.println(" Init CAN BUS Shield again");
        delay(100);
    }
    SERIAL.println("CAN BUS Shield init ok!");
}

unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void loop() {
    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    stmp[7] = stmp[7] + 1;
    if (stmp[7] == 100) {
        stmp[7] = 0;
        stmp[6] = stmp[6] + 1;

        if (stmp[6] == 100) {
            stmp[6] = 0;
            stmp[5] = stmp[6] + 1;
        }
    }

    CAN.sendMsgBuf(0x00, 0, 8, stmp);
    delay(100);                       // send data per 100ms
    SERIAL.println("CAN BUS sendMsgBuf ok!");
}
```

### 3. connection

1. **hardware connection**

| 2-Channel CAN-BUS(FD) Shield | CAN-BUS Shield V2 |
| --- | --- |
| CAN_0_L | CANL |
| CAN_0_H | CANH |

Software

- Sender Code(Arduino Code for CAN BUS Shield)

```cpp
#include <SPI.h>
#include <mcp2515_can.h>
/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif
const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
void setup() {
    SERIAL.begin(115200);
    while(!Serial){};
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
        SERIAL.println("CAN BUS Shield init fail");
        SERIAL.println(" Init CAN BUS Shield again");
        delay(100);
    }
    SERIAL.println("CAN BUS Shield init ok!");
}
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void loop() {
    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    stmp[7] = stmp[7] + 1;
    if (stmp[7] == 100) {
        stmp[7] = 0;
        stmp[6] = stmp[6] + 1;
        if (stmp[6] == 100) {
            stmp[6] = 0;
            stmp[5] = stmp[6] + 1;
        }
    }
    CAN.sendMsgBuf(0x00, 0, 0, 8, stmp, true);
    delay(100);                       // send data per 100ms
    SERIAL.println("CAN BUS sendMsgBuf ok!");
}
```

- Receiver Code (Respberry pi setting and **can-util** to receive)

```cpp
#include <SPI.h>
#include <mcp_can.h>

MCP_CAN CAN(9); //spi cs
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(CAN_OK != CAN.begin(CAN_500KBPS, MCP_8MHz))
  {
      Serial.println("CAN BUS Init Failed");
      delay(100);
  }
  Serial.println("CAN BUS Init Success!");
}
void loop() {
  // put your main code here, to run repeatedly:
  unsigned char len =0;
  unsigned char buf[8];
  if(CAN_MSGAVAIL == CAN.checkReceive())
  {
      CAN.readMsgBuf(&len, buf);
      unsigned long canId = CAN.getCanId();
      Serial.print("\nData from ID: 0x");
      Serial.println(canId, HEX);
      for(int i=0; i<len; i++)
      {
        Serial.print(buf[i]);
        Serial.print("\t");
      }
  }
}
```
