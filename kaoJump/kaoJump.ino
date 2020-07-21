//Jonathan Holmes (crait)
//November 1st, 2016
//Moving Character Demo
#include <Arduboy2.h>
Arduboy2 arduboy;

int playerx = 5;
int playery = 10;
Rect playerRect;
Rect objectRect;

const unsigned char PROGMEM background[] = {
// width, height,
8, 8,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
};

const unsigned char PROGMEM player[] = {
// width, height,
16, 16,
0x00, 0xf0, 0x98, 0x08, 0x08, 0x18, 0x70, 0x40, 0x40, 0x70, 0x18, 0x08, 0x08, 0x98, 0xf0, 0x00, 0x7f, 0xc1, 0x80, 0x00, 0x1c, 0x1c, 0x00, 0x40, 0x40, 0x00, 0x1c, 0x1c, 0x00, 0x80, 0xc1, 0x7f,  
};

void setup() {
  arduboy.begin();
  arduboy.clear();
  
}

void loop() {

  arduboy.clear();
  arduboy.pollButtons();
  objectRect = {20,20,30,30};
  arduboy.fillRect(objectRect.x,objectRect.y,objectRect.width,objectRect.height,WHITE);

  if (arduboy.justPressed(LEFT_BUTTON)) {
    playerx = playerx - 1;
  }
  if (arduboy.justPressed(RIGHT_BUTTON)) {
    playerx = playerx + 1;
  }
  if (arduboy.justPressed(UP_BUTTON)) {
    playery = playery - 1;
  }
  if (arduboy.justPressed(DOWN_BUTTON)) {
    playery = playery + 1;
  }
  playerRect = {playerx,playery,16,16};

//  //For each column on the screen
//  for (int backgroundx = 0; backgroundx < 128; backgroundx = backgroundx + 8) {
//  //For each row in the column
//    for ( int backgroundy = 0; backgroundy < 64; backgroundy = backgroundy + 8) {
//      //Draw a background tile
//      Sprites::drawOverwrite(backgroundx, backgroundy, background, 0);
//    }
//  }

  if(arduboy.collide(playerRect, objectRect)){
    arduboy.print("Hit!");
  }
  
  //Draw player sprite
  Sprites::drawOverwrite(playerx, playery, player, 0);
  arduboy.display();
}
