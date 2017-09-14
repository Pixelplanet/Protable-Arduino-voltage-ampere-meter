


#include <Arduino.h>
#include <U8g2lib.h>
#include <ResponsiveAnalogRead.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
//#define VT_PIN = A3
//#define AT_PIN = A2
#define ArduinoVT 5.0


//const int VT_PIN = A3;
//const int AT_PIN = A2;

ResponsiveAnalogRead  VT_PIN (A3, true);
ResponsiveAnalogRead  AT_PIN (A2, true);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);


void setup(void) {
  Serial.begin(9600); // temporary for troubleshoooting
  u8g2.begin();
}

void loop(void) {

  VT_PIN.update();
  AT_PIN.update();

  int vt_temp = VT_PIN.getValue();
  int at_temp = AT_PIN.getValue();

  double voltage = vt_temp * (ArduinoVT / 1023) * 5;
  double current = at_temp * (ArduinoVT / 1023) * 1000;
  Serial.println(voltage);    // temporary for troubleshoooting
  Serial.println(current);    // temporary for troubleshoooting
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB14_tr);	// choose a suitable font
  u8g2.setCursor(0, 15);
  u8g2.print(voltage);
  u8g2.setCursor(55, 15);
  u8g2.print("V");
  u8g2.setCursor(0, 35);
  u8g2.print(current);
  u8g2.setCursor(55, 35);
  u8g2.print("mA");
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(200);
}

