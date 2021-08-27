#include "TFT_eSPI.h"
#include "Free_Fonts.h"
#include "Free_Keybord.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.setTextColor(TFT_WHITE);
}

void loop() {
  String input_char;
  Keybord mykey;
  settingMenu("Enter the Text",18);
  tx_box(35,60,input_char);
  mykey.draw_keybord();
  // put your main code here, to run repeatedly:
  
  input_char = text_input();
  settingMenu("You have typed",18);
  tft.setFreeFont(FMB12)
  tft.setTextDatum(MC_DATUM);
  tft.drawString(title,160,120);
  tft.setTextDatum(TL_DATUM);
}

void settingMenu(String title, int sf) {
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH);
  spr.fillScreen(TFT_BLACK);
  spr.fillRect(0,0,320,50,TFT_BLUE);
  
  spr.setTextColor(TFT_WHITE);
  if (sf == 9){
    spr.setFreeFont(FMB9);
  } else if (sf == 12){
    spr.setFreeFont(FMB12);
  } else if (sf == 18){
    spr.setFreeFont(FMB18);
  } else if (sf == 24){
    spr.setFreeFont(FMB24);
  } else {
    spr.setFreeFont(FMB12);
  }
  spr.setTextDatum(MC_DATUM);
  spr.drawString(title,160,25);
  spr.setTextDatum(TL_DATUM);
  spr.pushSprite(0, 0); //push to LCD 
  spr.deleteSprite(); //clear buffer
}
