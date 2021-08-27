/*Free_Keybord.h - Library for creating a keyboard on the Wio Terminal .
  Created by Yuta Kurota, August 26, 2021.
  Released into the public domain.*/
#pragma once
#include "Arduino.h"
#include "TFT_eSPI.h"
#include "Free_Fonts.h"

#define KEY_MAX 32 // Keyboard Size
#define KEY_C 6 // Number of characters that can be typed on a key
#define mainKeyColor 0xbdf7 // Silver
#define spaceKeyColor 0xa554 // DarkGray
#define otherKeyColor 0x634c // DimGray
#define curentKeyColor TFT_BLUE // Bule
#define MAX_TEXT 50 // Maximum number of characters to be saved

extern TFT_eSPI tft;
extern TFT_eSprite spr;

// Keyboard class
class Keybord {
  private:
    // The upper left coordinate(ix_,iy_) of the keyboard
    int ix_ = 0;
    int iy_ = 110;
    // Width(ikw_) and height(ikh_) of the keyboard
    int ikw_ = 320;
    int ikh_ = 120;
    // Current key number
    int cur_ = 32;
    // Current keyboard number
    int flag_ = 1;
    // Current keyboard
    char Keys_[KEY_MAX][KEY_C];
    // Keyboard 1
    char Keys1_[KEY_MAX][KEY_C] = {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "a", "s", "d", "f", "g", "h", "j","k", "l", "\'", "123", "z", "x", "c", "v", "b", "n", "m", "back", "Shift", "space", "enter"};
    // Keyboard 2
    char Keys2_[KEY_MAX][KEY_C] = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "A", "S", "D", "F", "G", "H", "J","K", "L", "\"", "123", "Z", "X", "C", "V", "B", "N", "M", "back", "shift", "space", "enter"};
    // Keyboard 3
    char Keys3_[KEY_MAX][KEY_C] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "!", "\"", "#", "$", "%", "&", "\'","(", ")", "*", "ABC", "+", ",", "-", ".", "/", ":", ";", "back", "<=>", "space", "enter"};
    // Keyboard 4
    char Keys4_[KEY_MAX][KEY_C] = {"<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "{", "}", "|", "~", "¥", "!","?", ",", ".", "ABC", "+", "-", "*", "/", "%", "&", "^_^", "back", "<=>", "space", "enter"};
    
  public:
    // Method for updating keyboard coordinates
    void set_xy(int ix, int iy);
    // Method for updating keyboard size
    void set_wh(int ikw, int ikh);
    // Method for updating the keyboad array
    void set_key(char Keys[KEY_MAX][KEY_C], int type = 1);
    // Method for getting the current keyboard array
    char (*get_key())[KEY_C];
    // Method for getting the character of the current key
    String get_char();
    // Method for updating the current key number
    void set_cur(int cur);
    // Method for getting the current key number
    int get_cur();
    // Method for updating the current keyboard number
    void set_flag(int flag);
    // Method for getting the current keyboard number
    int get_flag();
    // Methods for displaying the keyboard
    void draw();
    // Method for getting the key number when the current key number is moved 1:up, 2:down, 3:left, or 4:ight
    // dir = 1:up, 2:down, 3:left, 4:right
    void move_cur(int dir);
};

// functions
// Function for creating a backspace
String back_space(String tx);
// Functions for creating input screens
void tx_box(int ix=35, int iy=60, String tx = "");
// Function for Free_Keybord text input example using 5-waySwitch
String text_input_5waySwitch(Keybord mykey, int xi=35,int yi = 60);
// Function for displaying the keyboard
void draw_keybord(Keybord mykey, int ix=0, int iy=110, int ikw=320, int ikh=120, int cur=32, int flag=1);
