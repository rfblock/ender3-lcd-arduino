
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#include <SPI.h>
#include <U8g2lib.h>

#define ENC_PIN 20
#define EN1_PIN 14
#define EN2_PIN 17

#define BEEP_PIN 5


#define LCD_CS_PIN 10
#define LCD_CS0_PIN 12
#define LCD_SCK_PIN 18
#define LCD_MOSI_PIN 19

//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0/*, LCD_EN_PIN, LCD_RW_PIN /*,LCD_RS_PIN*/);
//U8G2_ST7567_JLX12864_F_SW_SPI u8g2(U8G2_R0, LCD_RS_PIN, LCD_EN_PIN, LCD_RW_PIN, LCD_RW_PIN);
//U8G2_ST7567_ENH_DG128064_F_4W_SW_SPI u8g2(U8G2_R0, LCD_SCK_PIN, LCD_CS0_PIN, LCD_MOSI_PIN, LCD_CS_PIN);
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, LCD_SCK_PIN, LCD_MOSI_PIN, LCD_CS_PIN);

static unsigned char steggyBMP[] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x80, 0x00, 0x01, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00,
   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
   0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x04, 0x18, 0x18, 0x87, 0x00, 0x70, 0x44, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x02, 0x24, 0x24, 0x89, 0x06,
   0x89, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x6b, 0x00, 0x02,
   0x24, 0x20, 0x91, 0x09, 0x09, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x70, 0xc0, 0x01, 0x72, 0x24, 0x2c, 0x91, 0x10, 0x09, 0x0c, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x03, 0x42, 0x14, 0x22, 0x91, 0x10,
   0x09, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x00, 0x0e, 0x02,
   0x0c, 0x22, 0x91, 0x10, 0x09, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,
   0x41, 0x00, 0x0c, 0x82, 0x34, 0x22, 0x93, 0x10, 0x91, 0x24, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x38, 0xc0, 0x00, 0x0f, 0x6c, 0x44, 0x3c, 0x8d, 0x10,
   0x61, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0x80, 0xc1, 0x09, 0x10,
   0x00, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x73,
   0x00, 0x71, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0x08, 0x00, 0x1b, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x0e, 0x0c, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
   0x00, 0x06, 0x04, 0x00, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x80, 0x03, 0x00, 0x00, 0x03, 0x0c, 0x00, 0x00, 0x10, 0x00, 0x20,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00,
   0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00,
   0x80, 0x01, 0x04, 0x00, 0x00, 0x90, 0x87, 0x03, 0x38, 0x42, 0x00, 0x00,
   0x00, 0xf7, 0x0f, 0x00, 0xc0, 0x00, 0x06, 0x00, 0x00, 0x9f, 0x40, 0x40,
   0x04, 0x46, 0x00, 0x00, 0x80, 0xb1, 0x08, 0x00, 0x40, 0x00, 0x02, 0x00,
   0x80, 0x90, 0x80, 0x40, 0x02, 0x4a, 0x00, 0x00, 0x80, 0xd0, 0x1b, 0x00,
   0x20, 0x00, 0x02, 0x00, 0x80, 0x90, 0x00, 0x41, 0x02, 0x4a, 0x00, 0x00,
   0xc0, 0xd8, 0x17, 0x00, 0x30, 0x00, 0x03, 0x00, 0x80, 0x90, 0x03, 0x46,
   0x7a, 0x52, 0x00, 0x00, 0x40, 0xd0, 0x3f, 0x00, 0x10, 0x00, 0x01, 0x00,
   0x80, 0x90, 0x00, 0x48, 0x42, 0x22, 0x00, 0x00, 0x40, 0xd8, 0x0f, 0x00,
   0x18, 0x80, 0x01, 0x00, 0x00, 0x99, 0x40, 0x48, 0x62, 0x62, 0x00, 0x00,
   0x60, 0x90, 0x03, 0x00, 0x0c, 0xe0, 0xff, 0x01, 0x00, 0x0e, 0x8f, 0x47,
   0x5c, 0x42, 0x00, 0x00, 0x40, 0xf0, 0x00, 0x00, 0x04, 0xb8, 0xe0, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x00, 0x00,
   0x06, 0x0e, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x40, 0x20, 0x00, 0x00, 0x82, 0x03, 0x3f, 0x60, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xc3, 0xe0, 0x03, 0x40,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
   0x01, 0x3c, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x80, 0x00, 0x00, 0x80, 0x01, 0x07, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x80, 0xc0, 0x01, 0x00, 0x80,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x00, 0x00, 0x80,
   0x78, 0x00, 0x00, 0xc0, 0x00, 0x70, 0x00, 0x22, 0x01, 0x00, 0x00, 0x00,
   0x88, 0x01, 0x00, 0x80, 0x0f, 0x00, 0x00, 0x40, 0x00, 0x09, 0x00, 0x22,
   0x21, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x60,
   0x00, 0x11, 0x00, 0x36, 0x21, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0xc0,
   0x00, 0x00, 0x00, 0x30, 0x00, 0x21, 0x00, 0x2a, 0x21, 0x00, 0x00, 0x00,
   0xe2, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x18, 0x00, 0x41, 0x00, 0x22,
   0x21, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x0c,
   0x00, 0x81, 0x00, 0x22, 0x32, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x10,
   0x00, 0x00, 0x00, 0x03, 0x00, 0x89, 0x00, 0x22, 0x2e, 0x00, 0x00, 0x00,
   0x36, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x80, 0x01, 0x00, 0x71, 0x00, 0x42,
   0x20, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x06, 0x00, 0x00, 0xe0, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x02,
   0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
   0x0c, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x20, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x80, 0x01, 0x00, 0x00, 0x07, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x80, 0x00,
   0x00, 0xf0, 0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x18, 0x00, 0xc0, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x3c, 0x18, 0x40, 0x00, 0xc0, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x38, 0x60, 0x00,
   0x70, 0x00, 0x00, 0x0e, 0x0c, 0x87, 0x03, 0x8c, 0x11, 0x02, 0x00, 0x00,
   0x7c, 0x78, 0x20, 0x00, 0x18, 0x00, 0x00, 0x12, 0x92, 0x40, 0x40, 0x52,
   0x32, 0x02, 0x00, 0x00, 0x78, 0x78, 0x30, 0x00, 0x08, 0x00, 0x00, 0x22,
   0x10, 0x81, 0x40, 0x22, 0x52, 0x02, 0x00, 0x00, 0x78, 0xf0, 0x30, 0x00,
   0x0c, 0x00, 0x00, 0x42, 0x16, 0x02, 0x41, 0x04, 0x52, 0x02, 0x00, 0x00,
   0x78, 0x00, 0x10, 0x00, 0x04, 0x00, 0x00, 0x42, 0x11, 0x0c, 0x46, 0x04,
   0x91, 0x02, 0x00, 0x00, 0xf0, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x42,
   0x11, 0x10, 0x48, 0x88, 0x10, 0x01, 0x00, 0x00, 0xe0, 0x00, 0x08, 0x00,
   0x02, 0x00, 0x00, 0x22, 0x91, 0x50, 0x48, 0x90, 0x10, 0x03, 0x00, 0x00,
   0xc0, 0x01, 0x0c, 0x00, 0x02, 0x00, 0x00, 0x1e, 0x1e, 0x8f, 0x47, 0x60,
   0x10, 0x02, 0x00, 0x00, 0xc0, 0x03, 0x04, 0x00, 0x02, 0x00, 0x00, 0x02,
   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x06, 0x00,
   0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x07, 0x02, 0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x02, 0x00, 0x02, 0x00, 0x00, 0x02,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x03, 0x00,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };

Encoder knob(EN1_PIN, EN2_PIN);

void beep(int ms) {
  digitalWrite(BEEP_PIN, 1);
  delay(100);
  digitalWrite(BEEP_PIN, 0);
}

void beep() {
  beep(100);
}

void setup() {
  Serial.begin(9600);
  pinMode(ENC_PIN, INPUT);
  pinMode(EN1_PIN, INPUT);
  pinMode(EN2_PIN, INPUT);
  
  pinMode(BEEP_PIN, OUTPUT);
  
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB14_tr);
}

void loop() {
  bool pressed = digitalRead(ENC_PIN) == 0;
  
  Serial.println(knob.read());
  if (pressed) {
    beep();
    knob.write(0);
  }
  
  u8g2.clearBuffer();
  u8g2.drawXBMP( 0, 0, 128, 64, steggyBMP);
  u8g2.sendBuffer();
}