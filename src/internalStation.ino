#include <SPI.h>
#include <Wire.h>

#include "LCD.h"
#include "DEV_Config.h"
#include "VirtualWire.h"

void setup()
{
  // Radio
  vw_setup(2000);
  vw_set_rx_pin(4);
  vw_rx_start();
  Serial.println("Radio setup");

  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_DC, OUTPUT);

  Serial.begin(9600);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

  LCD_SCAN_DIR Lcd_ScanDir = SCAN_DIR_DFT;
  Serial.println("LCD Init ");
  LCD.LCD_Init(Lcd_ScanDir);

  
  Serial.println("LCD_Show ");
  // LCD.LCD_Show();
  LCD.LCD_Clear(BLACK);
}

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

void loop()
{
  if (vw_get_message(buf, &buflen))
  {
    LCD.LCD_DisplayString(35, 20, (char *)buf, &Font12, LCD_BACKGROUND, GREEN);
    delay(1000);
    LCD.LCD_Clear(BLACK);
    Serial.println((char *)buf);
  }
}
