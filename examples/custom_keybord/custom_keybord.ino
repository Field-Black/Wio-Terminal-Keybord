/*custom_keybord.ino - Example of a custom keyboard display and input/output code for the Wio Terminal.
  Created by Yuta Kurota, August 26, 2021.
  Released into the public domain.*/
/*
----This code will show you how to customize the keyboard to your liking.-------
1: How to change the keyboard layout.
2: How to change the size of the keyboard position.
3: How to change the color of the keyboard.
4：How to move the keys on the keyboard.
5：How to change the function of special keys on the keyboard.
--------------------------------------------------------------------------------
*/

#include "TFT_eSPI.h"
#include "Free_Keybord.h"

// LCD settings
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

Keybord defaultkey; // Cleate a default keybord
Keybord mykey; // Cleate a keybord you want to 

unsigned long prev, curr, interval;

void setup() {
  // LCD settings
  tft.begin();
  tft.setRotation(3);
  tft.setTextColor(TFT_WHITE);

  prev = 0;         // Initialize the last execution time
  interval = 20000;   // Set the execution cycle
}

void loop() {
  /*
  In this example, we will create a program that repeatedly displays the default 
  keyboard and the custom keyboard during the interval.
  --------------------------------------------------------------------------------
  1: How to change the keyboard layout
    Using the "set_key(char Keys[KEY_MAX][KEY_C], int type)" method, 
    you can change the key layout as you wish.
      Keys[KEY_MAX][KEY_C]: The keyboard layout you want to change.
        KEY_MAX = 32, KEY_C = 6
      type: The number of the keyboard you want to change.
        type = {x|x={1,2,3,4}}

     
     For details, refer to the URL below.
     https://github.com/Field-Black/Wio-Terminal-Keybord
  --------------------------------------------------------------------------------
  */
  // Custom Keyboard 1
  char cKeys1[KEY_MAX][KEY_C] = {"p", "y", "f", "g", "c", "r", "l", "a", "o", "e", "u", "i", "d", "h", "t", "n", "s","q", "j", "\'", "123", "k", "x", "b", "m", "w", "v", "z", "back", "Shift", "space", "enter"};
  mykey.set_key(cKeys1,1);
  // Custom Keyboard 2
  char cKeys2[KEY_MAX][KEY_C] = {"P", "Y", "F", "G", "C", "R", "L", "A", "O", "E", "U", "I", "D", "H", "T", "N", "S","Q", "J", "\"", "123", "K", "X", "B", "M", "W", "V", "Z", "back", "shift", "space", "enter"};
  mykey.set_key(cKeys2,2);
  // Custom Keyboard 3
  char cKeys3[KEY_MAX][KEY_C] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "!", "\"", "#", "$", "%", "&", "\'","(", ")", "*", "ABC", "+", ",", "-", ".", "/", ":", ";", "back", "<=>", "space", "enter"};
  mykey.set_key(cKeys3,3);
  // Custom Keyboard 4
  char cKeys4[KEY_MAX][KEY_C] = {"<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "{", "}", "|", "~", "¥", "!","?", ",", ".", "ABC", "+", "-", "*", "/", "%", "&", "^_^", "back", "<=>", "space", "enter"};
  mykey.set_key(cKeys4,4);

  prev = millis();
  int type = 1;
  while(1){
    curr = millis();
    if (type > 4){
      type = 1;
    }
    if ((curr - prev) >= interval){
      break;
    }
    settingMenu("default keybord",18);
    tx_box(35,60,"Kebord: "+String(type));
    draw_keybord(defaultkey,0,110,320,240,32,type);
    delay(1500);
    settingMenu("custom keybord",18);
    tx_box(35,60,"Kebord: "+String(type));
    draw_keybord(mykey,0,110,320,240,32,type);
    delay(1500);
    type += 1;
  }




  /*
   In this example, we will create a program that repeatedly displays a custom 
   keyboard that randomly changes in size and position during an interval.
  --------------------------------------------------------------------------------
  2: How to change the size of the keyboard position.
    Using the "draw_keybord(Keybord mykey, int ix, int iy, int ikw, int ikh, int cur, int flag)" function, 
    you can change the size and position as you wish.
      mykey: The keyboard you want to display.
      ix: x-coordinate of the upper left corner to display the keyboard.
      iy: y-coordinate of the upper left corner to display the keyboard.
      ikw: The width of the keyboard you want to display.
      ikh: The height of the keyboard you want to display.
      cur: Key number of the selected keyboard.
        cur = {x|x E (1,32), x E Z}
      flag: The number of the keyboard you want to change.
        flag = {x|x E {1,2,3,4}}
        
     For details, refer to the URL below.
     https://github.com/Field-Black/Wio-Terminal-Keybord
  --------------------------------------------------------------------------------
  */
  prev = millis();
  type = 1;
  while(1){
    curr = millis();
    tft.setRotation(int(random(0, 4)));
    tft.fillScreen(TFT_BLACK);
    if (type > 4){
      type = 1;
    }
    if ((curr - prev) >= interval){
      break;
    }
    draw_keybord(mykey,int(random(0, 320)),int(random(0, 240)),int(random(100, 420)),int(random(100, 340)),32,type);
    delay(1500);
    type += 1;
  }
  tft.setRotation(3);



  
  /*
   In this example, 

  --------------------------------------------------------------------------------
  3: How to change the color of the keyboard.
        
     For details, refer to the URL below.
     https://github.com/Field-Black/Wio-Terminal-Keybord
  --------------------------------------------------------------------------------
  */ 

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
