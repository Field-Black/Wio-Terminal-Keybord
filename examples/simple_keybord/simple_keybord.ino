/*simple_keybord.ino - Example of a simple keyboard display and input/output code for the Wio Terminal.
  Created by Yuta Kurota, August 26, 2021.
  Released into the public domain.*/
#include "TFT_eSPI.h"
#include "Free_Keybord.h"

// LCD settings
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

Keybord mykey; // Cleate a keybord

void setup() {
  // LCD settings
  tft.begin();
  tft.setRotation(3);
  tft.setTextColor(TFT_WHITE);
}

void loop() {
  String input_char; // Set variables for storing strings output from the keyboard.

  // Function to display the input screen
  settingMenu("Enter the Text",18);
  // Functions to display the input-box
  tx_box(35,60,input_char);

  // Function for displaying the keyboard
  input_char = text_input_5waySwitch(mykey);

  // Processing of input strings
  settingMenu("You have typed",18);
  tft.setFreeFont(FMB12);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(input_char,160,120);
  tft.setTextDatum(TL_DATUM);
  delay(5000);
}

// Function to display the input screen
void settingMenu(String title, int sf) {
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0,0,320,50,TFT_BLUE);
  
  tft.setTextColor(TFT_WHITE);
  if (sf == 9){
    tft.setFreeFont(FMB9);
  } else if (sf == 12){
    tft.setFreeFont(FMB12);
  } else if (sf == 18){
    tft.setFreeFont(FMB18);
  } else if (sf == 24){
    tft.setFreeFont(FMB24);
  } else {
    tft.setFreeFont(FMB12);
  }
  tft.setTextDatum(MC_DATUM);
  tft.drawString(title,160,25);
  tft.setTextDatum(TL_DATUM);
}
