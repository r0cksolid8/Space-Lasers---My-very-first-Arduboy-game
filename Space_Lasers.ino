#include "Arduboy2.h"
#include "ArduboyTones.h"

#include "background.h"
Arduboy2 arduboy;

ArduboyTones sound(arduboy.audio.enabled);

int x = 8;
int y = 8;
int del = 0;
int delt = 0;
int lazery = 0;
int lazerx = 0;
int lazertwoy = 0;
int lazertwox = 0;
int aonex = 0;
int aoney = 0;
int atwox = 0;
int atwoy = 0;
int movement = 0;
int gamestate = 0;
int lives = 5;
int score = 0;
int whilee = 1;


const unsigned char PROGMEM ship[] =
{
// width, height,
15, 15,
0x00, 0x00, 0x04, 0x04, 0x0c, 0x98, 0xb0, 0x70, 0x50, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x10, 0x10, 0x18, 0x0c, 0x06, 0x07, 0x05, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM aone [] =
{
// width, height,
14, 14,
0x20, 0x30, 0x30, 0x18, 0xda, 0xd3, 0xf3, 0xe7, 0xef, 0xfb, 0xf3, 0xe3, 0x00, 0x03, 
0x01, 0x03, 0x03, 0x06, 0x16, 0x32, 0x33, 0x39, 0x3d, 0x37, 0x33, 0x31, 0x00, 0x30, 
};

const unsigned char PROGMEM atwo [] =
{
// width, height,
14, 14,
0x20, 0x30, 0x30, 0x18, 0xda, 0xd3, 0xf3, 0xe7, 0xef, 0xfb, 0xf3, 0xe3, 0x00, 0x03, 
0x01, 0x03, 0x03, 0x06, 0x16, 0x32, 0x33, 0x39, 0x3d, 0x37, 0x33, 0x31, 0x00, 0x30, 
};







void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(75);
}

void loop() {
  arduboy.nextFrame();
  
  if (!arduboy.nextFrame()) {
    return;
  }

    
  switch (gamestate){

  case 0:
  
  x = 0;
  y = 8;
  del = 0;
  delt = 0;
  lazery = 0;
  lazerx = 0;
  aonex = 0;
  aoney = 0;
  atwox = 0;
  atwoy = 0;
  movement = 0;
  gamestate = 0;
  lives = 5;
  score = 0;
  whilee = 1;

  arduboy.clear();
  arduboy.drawSlowXYBitmap(0, 0, title, 128, 64);
  arduboy.display();
  
  delay(5000);
  
  arduboy.clear();
  arduboy.setCursor(0,0);
  arduboy.setTextSize(1.3);
  arduboy.println("Welcome to Space");
  arduboy.println("Lasers! Press A");
  arduboy.println("to start.");
  arduboy.setTextSize(1);
  arduboy.display();

  while (whilee == 1){
    if (arduboy.pressed(A_BUTTON)){
      whilee = 0;
    }
  }

  arduboy.clear();
  arduboy.setCursor(0,0);
  arduboy.println("Would you like SFX?");
  arduboy.println("Press up for yes and");
  arduboy.println("and down for no.");
  arduboy.display();

  whilee = 1;

  while (whilee == 1){
    if (arduboy.pressed(UP_BUTTON)){
      arduboy.audio.on();
      whilee = 0;
    }
    if (arduboy.pressed(DOWN_BUTTON)){
      arduboy.audio.off();
      whilee = 0;
    }
  }



  
  gamestate = 1;


  case 1:
  

  
  arduboy.clear();

  lazery = y + 3;
  lazertwoy = y + 11;


    lazerx = lazerx + 24;
    lazertwox = lazertwox + 24;
  arduboy.fillRect(lazerx, lazery, 30, 1, WHITE);
  arduboy.fillRect(lazertwox, lazertwoy, 30, 1, WHITE);
   
  if (arduboy.pressed(UP_BUTTON)){   
    if (y > 8){
      del ++;
      if (del % 1 == 0){
        y = y - 3;
      }
    }
  }
  
  if (arduboy.pressed(DOWN_BUTTON)){
    if (y < 48){
      del ++;
      if (del % 1 == 0){
        y = y + 3;
      }
    }
  }

  if (arduboy.justPressed(A_BUTTON)){
    if (lazerx > 128 && lazertwox > 128){
      lazerx = -60;
      lazertwox = -60;
      if (lazerx == -60 && lazery == -60){
        lazery = y + 3;
        lazertwoy = y + 11;
      }
      sound.tone(500, 10);     
    }
  }


  constexpr uint8_t ShipWidth = 15, ShipHeight = 15;

  Rect shipbox(x, y, ShipWidth, ShipHeight);

  constexpr uint8_t aoneWidth = 15, aoneHeight = 15;

  Rect aonebox(aonex, aoney, aoneWidth, aoneHeight);

  constexpr uint8_t lazerWidth = 30, lazerHeight = 1;

  Rect lazerbox(lazerx, lazery, lazerWidth, lazerHeight);
  
  constexpr uint8_t lazertwoWidth = 30, lazertwoHeight = 1;

  Rect lazertwobox(lazertwox, lazertwoy, lazertwoWidth, lazertwoHeight);
  
  constexpr uint8_t atwoWidth = 14, atwoHeight = 14;

  Rect atwobox(atwox, atwoy, atwoWidth, atwoHeight);

  constexpr uint8_t barrierWidth = 1, barrierHeight = 56;

  Rect barrierbox(-14, 8, barrierWidth, barrierHeight);
   

  if (Arduboy2::collide(aonebox, barrierbox) && aonex < -26){
    arduboy.generateRandomSeed();
    aoney = random(8, 50);

    arduboy.generateRandomSeed();
    aonex = random(400, 750);

    sound.tone(250, 10);
       
    score = score - 75;
  }

  if (Arduboy2::collide(atwobox, barrierbox) && atwox < -26){
    arduboy.generateRandomSeed();
    aoney = random(8, 50);

    arduboy.generateRandomSeed();
    aonex = random(750, 1100);

    sound.tone(250, 10);
       
    score = score - 75;
  }

  if (Arduboy2::collide(shipbox, aonebox)){
    arduboy.generateRandomSeed();
    aoney = random(8, 50);

    arduboy.generateRandomSeed();
    aonex = random(300, 750);

    sound.tone(250, 10);

    lives --;
  }

  if (Arduboy2::collide(shipbox, atwobox)){
    arduboy.generateRandomSeed();
    atwoy = random(8, 50);

    arduboy.generateRandomSeed();
    atwox = random(750, 1100);

    sound.tone(250, 10);

    lives --;
  }
  
  if (Arduboy2::collide(lazerbox, aonebox) && aonex < 135){
    arduboy.generateRandomSeed();
    aoney = random(8, 50);

    arduboy.generateRandomSeed();
    aonex = random(300, 750);   

    sound.tone(200, 15);
    
    score = score + 50;
  }
  if (Arduboy2::collide(lazertwobox, aonebox)  && aonex < 135){
    arduboy.generateRandomSeed();
    aoney = random(8, 50);

    arduboy.generateRandomSeed();
    aonex = random(300, 750);   

    sound.tone(200, 15);
    
    score = score + 50;    
  }

  
  if (Arduboy2::collide(lazerbox, atwobox) && atwox < 135){
    arduboy.generateRandomSeed();
    atwoy = random(8, 50);

    arduboy.generateRandomSeed();
    atwox = random(750, 1100);

    sound.tone(200, 15);

    score = score + 50;
  }
  if (Arduboy2::collide(lazertwobox, atwobox) && atwox < 135){
    arduboy.generateRandomSeed();
    atwoy = random(8, 50);

    arduboy.generateRandomSeed();
    atwox = random(750, 1100);

    sound.tone(200, 15);

    score = score + 50;    
  }
    aonex --;
    aonex --;
    aonex --;
    aonex --;
    
    atwox --;
    atwox --;
    atwox --;
    atwox --;
  
  arduboy.setCursor(0, 0);
  arduboy.print("LIVES:");
  arduboy.print(lives);
  arduboy.print(" ");
  arduboy.print("SCORE:");
  if (score <= 0){
    score = 0;
  }

  arduboy.print(score);
  
  if (lives == 0){
    arduboy.clear();
    arduboy.setTextSize(3);
    arduboy.println(" GAME");
    arduboy.println("  OVER");
    arduboy.setTextSize(1);
    arduboy.display();

    sound.tone(400, 100);
    delay(10);
    sound.tone(370, 100);
    delay(10);
    sound.tone(325, 100);
    
    delay(2000);
    
    arduboy.clear();
    arduboy.setTextSize(1.5);
    arduboy.println("Your score was:");
    arduboy.println(" ");
    if (score <= 0){
      score = 0;
    }

    arduboy.println(score);

    arduboy.println(" ");
    arduboy.println("Press A to play");
    arduboy.print("again.");
    arduboy.setTextSize(1);
    arduboy.display();
    whilee = 1;
    while (whilee == 1){
      if (arduboy.pressed(A_BUTTON)){
        gamestate = 0;
        whilee = 0;
      }
    }
  }

  if (arduboy.justPressed(B_BUTTON)){
    delay(100);
    whilee = 1;
      arduboy.clear();
          
      arduboy.fillRect(46, 17, 16, 40, WHITE);
      
      arduboy.fillRect(66, 17, 16, 40, WHITE);

      arduboy.display();
      delay(1000);
    while (whilee == 1){
      if (arduboy.pressed(B_BUTTON)){
        arduboy.clear();
        delay(100);
        whilee = 0;
        
      }
    }
  }

  arduboy.drawBitmap(0, 0, background, 128, 64);
  Sprites::drawOverwrite(x, y, ship, 0);  
  Sprites::drawOverwrite(aonex, aoney, aone, 0);
  Sprites::drawOverwrite(atwox, atwoy, atwo, 0);
  arduboy.pollButtons(); 
  arduboy.display();
  }
}
