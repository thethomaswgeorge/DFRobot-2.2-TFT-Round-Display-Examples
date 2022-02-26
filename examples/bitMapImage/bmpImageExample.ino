#include "DFRobot_ST7687S_Latch.h"

#ifdef __AVR__
uint8_t pin_cs = 3, pin_rs = 5, pin_wr = 6, pin_lck = 7;
#else
uint8_t pin_cs = D3, pin_rs = D5, pin_wr = D6, pin_lck = D7;
#endif

DFRobot_ST7687S_Latch tft(pin_cs, pin_rs, pin_wr, pin_lck);

// Color definitions
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

static const unsigned char arduinoLogo[] PROGMEM = {
    // Your BMP image here
};

void setup() 
{ 
  Serial.begin(115200);
  tft.begin();
  tft.fillScreen(BLACK);
} 

void loop() 
{ 
  drawBitmap(-50, -51, arduinoLogo, 100, 102, WHITE);
}

void bitmap(int pos_x, int pos_y, int c, int r, const unsigned short imagen[]){ //
  int contador = 0;
  for(int i=0; i<r; i++){
    for(int j=0; j<c; j++){
      tft.drawPixel(j + pos_x, i + pos_y, pgm_read_word(&imagen[contador++]));
    }
  }
}

void drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if(byte & 0x80) tft.drawPixel(x+i, y+j, color);
    }
  }
}
