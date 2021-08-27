/*Free_Keybord.cpp - Library for creating a keyboard on the Wio Terminal .
  Created by Yuta Kurota, August 26, 2021.
  Released into the public domain.*/

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "Free_Fonts.h"
#include "Free_Keybord.h"

extern TFT_eSPI tft;
extern TFT_eSprite spr;

//******************************************//
//           Methods definition             //
//******************************************//
// Method for updating keyboard coordinates
void Keybord::set_xy(int ix, int iy){
  ix_ = ix;
  iy_ = iy;
}
// Method for updating keyboard size
void Keybord::set_wh(int ikw, int ikh){
  ikw_=ikw;
  ikh_=ikh;
}
// Method for updating the keyboad array
void Keybord::set_key(char Keys[KEY_MAX][KEY_C], int type){
  if (type == 1) {
    memcpy(Keys1_, Keys, sizeof(Keys));
  } else if (type == 2) {
    memcpy(Keys2_, Keys, sizeof(Keys));
  } else if (type == 3) {
    memcpy(Keys3_, Keys, sizeof(Keys));
  } else if (type == 4) {
    memcpy(Keys4_, Keys, sizeof(Keys));
  }
}
// Method for getting the current keyboard array
char (*Keybord::get_key())[KEY_C]{
  return Keys_;
}
// Method for getting the character of the current key
String Keybord::get_char(){
  if (flag_ == 1){
    memcpy(Keys_, Keys1_, sizeof(Keys1_));
  } else if (flag_ == 2){
    memcpy(Keys_, Keys2_, sizeof(Keys2_));
  } else if (flag_ == 3){
    memcpy(Keys_, Keys3_, sizeof(Keys3_));
  } else if (flag_ == 4){
    memcpy(Keys_, Keys4_, sizeof(Keys4_));
  }
  return Keys_[cur_];
}
// Method to update the current key number
void Keybord::set_cur(int cur){
  if (cur < 0){
    cur_ = 0;
  } else if (cur >=32){
    cur_=31;
  } else {
    cur_ = cur;
  }
}
// Method for getting the current key number
int Keybord::get_cur(){
  return cur_;
}
// Method for updating the current keyboard number
void Keybord::set_flag(int flag){
  if (flag <= 1){
    flag_ = 1;
  } else if (flag >= 4) {
    flag_ = 4;
  }else {
    flag_ = flag;
  }
}
// Method for getting the current keyboard number
int Keybord::get_flag(){
  return flag_;
}
// Methods for displaying the keyboard
void Keybord::draw(){
  if (flag_ == 1){
    memcpy(Keys_, Keys1_, sizeof(Keys1_));
  } else if (flag_ == 2){
    memcpy(Keys_, Keys2_, sizeof(Keys2_));
  } else if (flag_ == 3){
    memcpy(Keys_, Keys3_, sizeof(Keys3_));
  } else if (flag_ == 4){
    memcpy(Keys_, Keys4_, sizeof(Keys4_));
  }
  int kws = ikw_ / 32;
  int kw;
  int kh;

  if (((ikw_ - kws*2) % 10) == 0){
    kw = (ikw_ - kws*2) / 10;
  } else {
    if ((((ikw_ - kws*2) % 10)%2)==0){
      kws = kws + ((ikw_ - kws*2) % 10)/2;
      kw = (ikw_ - kws*2) / 10;
    } else {
      kws = kws + (((ikw_ - kws*2) % 10)-1)/2;
      kw = (ikw_ - kws*2) / 10;
    }
  }
  
  if (ikh_ >= kw*4){
    kh = kw;
  } else {
    if ((ikh_ % 4) == 0){
      kh = ikh_ / 4;
    } else {
      kh = (ikh_ - (ikh_ % 4)) / 4;
      if ((double)kh/kw <= 0.8){
        kw = kh;
      }
    }
  }

  int rw = kw * 0.87;
  int rh = kh * 0.87;

  int rrk = kw*kh/180;

  
  

  spr.createSprite(ikw_,ikh_);
  spr.fillScreen(TFT_BLACK);
  for  (int i=0; i <= 31; i++){
    if (i == cur_) {
      // Create a keyboard for the first line.
      if (i < 10) {
        spr.fillRoundRect(kws+kw*i,kh*0,rw,rh,rrk,curentKeyColor);
        spr.setTextColor(TFT_BLACK);
        spr.setFreeFont(FSSB12);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],rw/2+kws+kw*i,rh/2+kh*0);
      }
      // Create a keyboard for the second line.
      else if (i < 20){
        spr.fillRoundRect(kws+kw*(i-10),kh*1,rw,rh,rrk,curentKeyColor);
        spr.setTextColor(TFT_BLACK);
        spr.setFreeFont(FSSB12);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],rw/2+kws+kw*(i-10),rh/2+kh*1);
      }
      // Create a keyboard for the third line.
      else if (i == 20){ // Create a 123 key
        spr.fillRoundRect(kws+kw*(i-20),kh*2,rw,rh,rrk,curentKeyColor);
        spr.setTextColor(TFT_WHITE);
        spr.setFreeFont(FSSB9);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],rw/2+kws+kw*(i-20),rh/2+kh*2);
      } else if (i < 28){
        spr.fillRoundRect(kws+kw*(i-20),kh*2,rw,rh,rrk,curentKeyColor);
        spr.setTextColor(TFT_BLACK);
        spr.setFreeFont(FSSB12);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],rw/2+kws+kw*(i-20),rh/2+kh*2);
      } else if (i == 28){
        spr.fillRoundRect(kws+kw*(i-20),kh*2,kw+rw,rh,rrk,curentKeyColor);
        spr.setTextColor(TFT_WHITE);
        spr.setFreeFont(FSSB9);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],kws+kw*9,rh/2+kh*2);
      }
      // Create a keyboard for the fourth line.
      else if (i == 29){ // Create a Shift key
        spr.fillRoundRect(kws+kw*(i-29),kh*3,kw+rw,rh,rrk,curentKeyColor);
        spr.setTextColor(TFT_WHITE);
        spr.setFreeFont(FSSB9);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],kws+kw,rh/2+kh*3);
      } else if (i == 30){ // Create a Space key
        spr.fillRoundRect(kws+kw+kw*(i-29),kh*3,kw*5+rw,rh,rrk,curentKeyColor);
        spr.setTextColor(TFT_BLACK);
        spr.setFreeFont(FSSB12);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],kws+kw*5,rh/2+kh*3);
      } else if (i == 31){ // Create a Enter key
        spr.fillRoundRect(kws+kw*8,kh*3,kw+rw,rh,rrk,curentKeyColor);
        spr.setTextColor(TFT_WHITE);
        spr.setFreeFont(FSSB9);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],kws+kw*9,rh/2+kh*3);
      }
    } else {
      // Create a keyboard for the first line.
      if (i < 10) {
        spr.fillRoundRect(kws+kw*i,kh*0,rw,rh,rrk,mainKeyColor);
        spr.setTextColor(TFT_BLACK);
        spr.setFreeFont(FSSB12);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],rw/2+kws+kw*i,rh/2+kh*0);
      }
      // Create a keyboard for the second line.
      else if (i < 20){
        spr.fillRoundRect(kws+kw*(i-10),kh*1,rw,rh,rrk,mainKeyColor);
        spr.setTextColor(TFT_BLACK);
        spr.setFreeFont(FSSB12);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],rw/2+kws+kw*(i-10),rh/2+kh*1);
      }
      // Create a keyboard for the third line.
      else if (i == 20){ // Create a 123 key
        spr.fillRoundRect(kws+kw*(i-20),kh*2,rw,rh,rrk,otherKeyColor);
        spr.setTextColor(TFT_WHITE);
        spr.setFreeFont(FSSB9);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],rw/2+kws+kw*(i-20),rh/2+kh*2);
      } else if (i < 28){
        spr.fillRoundRect(kws+kw*(i-20),kh*2,rw,rh,rrk,mainKeyColor);
        spr.setTextColor(TFT_BLACK);
        spr.setFreeFont(FSSB12);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],rw/2+kws+kw*(i-20),rh/2+kh*2);
      } else if (i == 28){
        spr.fillRoundRect(kws+kw*(i-20),kh*2,kw+rw,rh,rrk,otherKeyColor);
        spr.setTextColor(TFT_WHITE);
        spr.setFreeFont(FSSB9);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],kws+kw*9,rh/2+kh*2);
      }
      // Create a keyboard for the fourth line.
      else if (i == 29){ // Create a Shift key
        spr.fillRoundRect(kws+kw*(i-29),kh*3,kw+rw,rh,rrk,otherKeyColor);
        spr.setTextColor(TFT_WHITE);
        spr.setFreeFont(FSSB9);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],kws+kw,rh/2+kh*3);
      } else if (i == 30){ // Create a Space key
        spr.fillRoundRect(kws+kw+kw*(i-29),kh*3,kw*5+rw,rh,rrk,spaceKeyColor);
        spr.setTextColor(TFT_BLACK);
        spr.setFreeFont(FSSB12);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],kws+kw*5,rh/2+kh*3);
      } else if (i == 31){ // Create a Enter key
        spr.fillRoundRect(kws+kw*8,kh*3,kw+rw,rh,rrk,otherKeyColor);
        spr.setTextColor(TFT_WHITE);
        spr.setFreeFont(FSSB9);
        spr.setTextDatum(MC_DATUM);
        spr.drawString(Keys_[i],kws+kw*9,rh/2+kh*3);
      }
    }
  }
  spr.pushSprite(ix_, iy_); //push to LCD 
  spr.deleteSprite(); //clear buffer
}
// Method for getting the key number when the current key number is moved 1:up, 2:down, 3:left, or 4:ight
void Keybord::move_cur(int dir){
  // 1:up, 2:down, 3:left, 4:right
  if (dir == 1) {
    cur_ = cur_ - 10;
    if (cur_ <= -9){
      cur_ = 29;
    } else if (cur_ <= -3){
      cur_ = 30;
    } else if (cur_ <= -1){
      cur_ = 31;
    } else if (cur_ == 21){
      cur_ = 28;
    } else if (cur_ == 20){
      cur_ = 22;
    } else if (cur_ == 19){
      cur_ = 20;
    }
  } else if (dir == 2) {
    cur_ = cur_ + 10;
    if (cur_ == 29){
      cur_ = 28;
    } else if ((cur_ >= 30)&&(cur_ <= 31)){
      cur_ = 29;
    } else if ((cur_ >= 32)&&(cur_ <= 37)){
      cur_ = 30;
    } else if (cur_ == 38){
      cur_ = 31;
    } else if (cur_ == 39){
      cur_ = 0;
    } else if (cur_ == 40){
      cur_ = 2;
    } else if (cur_ >= 41){
      cur_ = 8;
    }
  } else if (dir == 3) {
    cur_ = cur_ - 1;
    if (cur_ < 0){
      cur_ = 31;
    }
  } else if (dir == 4) {
    cur_ = cur_ + 1;
    if (cur_ > 31){
      cur_ = 0;
    }
  } 
}


//******************************************//
//          Functions definition            //
//******************************************//
// Function for creating a backspace
String my_back_space(String tx){
    int len = tx.length();
    char charBuf[MAX_TEXT];
    tx.toCharArray(charBuf, MAX_TEXT);
    
    if( len == 0 ) {
        return "";      // str が空文字列の場合は、'\0' を返す
    } else {
        char c = charBuf[len-1];     // 末尾文字を c に代入
        charBuf[len-1] = '\0';       // 終端記号のヌル文字を次の位置に書き込む
        return String(charBuf);                  // 末尾文字を返す
    }
}
// Functions for creating input screens
void tx_box(int ix, int iy, String tx) {
  spr.createSprite(260,50);
  spr.fillScreen(TFT_BLACK);
  spr.fillRect(0,0,250,40,TFT_WHITE);

  spr.setTextColor(TFT_BLACK);
  spr.setFreeFont(FSB12);
  spr.setTextDatum(TL_DATUM);
  spr.drawString(tx,10,10);

  spr.pushSprite(ix, iy); //push to LCD 
  spr.deleteSprite(); //clear buffer
}
// Function for Free_Keybord text input example using 5-waySwitch
String text_input_5waySwitch(Keybord mykey,int xi,int yi){
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
  String text_i;
  tx_box(xi,yi,text_i);
  while (text_i.length() <= MAX_TEXT){
    // keyboard operation
    while (1) {
      if (digitalRead(WIO_5S_UP) == LOW) {
        mykey.move_cur(1);
      } else if (digitalRead(WIO_5S_DOWN) == LOW) {
        mykey.move_cur(2);
      } else if (digitalRead(WIO_5S_LEFT) == LOW) {
        mykey.move_cur(3);
      } else if (digitalRead(WIO_5S_RIGHT) == LOW) {
        mykey.move_cur(4);
      } else if (digitalRead(WIO_5S_PRESS) == LOW) {
        break;
      }
      mykey.draw();
      delay(200);
    }
    String now_char = mykey.get_char();
    int now_flag = mykey.get_flag();
    if (now_char == "Shift"){
      mykey.set_flag(2);
    } else if ((now_char == "shift")||(now_char == "ABC")){
      mykey.set_flag(1);
    } else if ((now_char == "123")||((now_char == "<=>")&&(now_flag==4))){
      mykey.set_flag(3);
    } else if ((now_char == "<=>")&&(now_flag==3)){
      mykey.set_flag(4);
    } else if (now_char == "space"){
      now_char = " ";
      text_i = text_i + now_char;
    } else if (now_char == "back"){
      int char_n = text_i.length();
      text_i = my_back_space(text_i);
  //    String pw_ = String(pw).remove(char_n,1);
    } else if (now_char == "enter"){
      break;
    } else {
      text_i = text_i + now_char;
    }
    tx_box(xi,yi,text_i);
    delay(200);
  }
  return text_i;
}

// Function for displaying the keyboard
void draw_keybord(Keybord mykey, int ix, int iy, int ikw, int ikh, int cur, int flag){
  mykey.set_xy(ix, iy);
  mykey.set_wh(ikw, ikh);
  mykey.set_cur(cur);
  mykey.set_flag(flag);

  mykey.draw();
}
