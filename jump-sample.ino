#include <Arduboy2.h>

Arduboy2 arduboy;
int gameState = 0;
int ballx = 0;
int bally = 63;
int ballSize = 4;
int ballRight = 1;
int ballDown = 1;
int bPressedTime = 0;
int jumpHeight = 0;
int jumpWidth = 0;
bool isJumping = false;
bool isJumpStart = false;

void setup()
{
  arduboy.begin();
  
  arduboy.initRandomSeed();
  arduboy.setFrameRate(60);
  
  arduboy.clear();
}

void loop()
{
  if (!arduboy.nextFrame()){
    return;
  }
  
  arduboy.clear();
  arduboy.pollButtons();
  
  switch (gameState){
    case 0:
      arduboy.setCursor(0, 0);
      arduboy.print("Title Screen");
      if (arduboy.justPressed(A_BUTTON)){
        gameState = 1;
      }
      break;
    
    case 1:
      //Gameplay screen
      arduboy.setCursor(0, 0);
      arduboy.print("Gameplay");
      
      arduboy.fillRect(ballx, bally, ballSize, ballSize, WHITE);
      
      if (arduboy.pressed(B_BUTTON) && !isJumping){
        bPressedTime++;
        isJumpStart = true;
      } else if (arduboy.notPressed(B_BUTTON) && isJumpStart){
        jumpHeight = bPressedTime;
        jumpWidth = bPressedTime;
        bPressedTime = 0;
        isJumpStart = false;
        isJumping = true;
      }
      
      // 上にjump
      if ((bally > 63 - jumpHeight) && isJumping){
        bally--;
        
        if (ballRight == 1){
          ballx++;
        }else{
          ballx--;
        }
      }
      
      // 下に戻る
      if ((bally <= 63 - jumpHeight) && isJumping){
        bally++;
        jumpHeight = 0;
        
        if (ballRight == 1){
          ballx++;
        }else{
          ballx--;
        }
      }
      
      if (ballx + ballSize == 127){
        ballRight = -1;
      }
      if (ballx == 0){
        ballRight = 1;
      }
      
      // 床に到着
      if (bally == 63) {
        isJumping = false;
        jumpHeight = 0;
      }
      
      
      /*if (ballRight == 1){
        ballx++;
      }
      
      if (ballRight == -1){
        ballx--;
      }
      
      if (ballx == 0){
        ballRight = 1;
      }
      
      if (ballx + ballSize == 127){
        ballRight = -1;
      }
      
      //Move the ball down
      if(ballDown == 1) {
        bally++;
      }
      //Move the ball up
      if(ballDown == -1) {
        bally--;
      }
      //Reflect the ball off of the top of the screen
      if(bally == 0) {
        ballDown = 1;
      }
      //Reflect the ball off of the bottom of the screen
      if(bally == 63) {
        ballDown = -1;
      }
      */
      if (arduboy.justPressed(A_BUTTON)){
        gameState = 2;
      }
      break;

    case 2:
      //Win screen
      arduboy.setCursor(0, 0);
      arduboy.print("Win Screen");
      if (arduboy.justPressed(A_BUTTON)){
        gameState = 3;
      }
      break;

    case 3:
      //Game over screen
      arduboy.setCursor(0, 0);
      arduboy.print("Game Over Screen");
      if (arduboy.justPressed(A_BUTTON)){
        gameState = 0;
      }
      break;
  }
  
  

  arduboy.display();
}
