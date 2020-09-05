// ref https://raohu69.hatenablog.jp/entry/2018/03/31/223049

#include <Arduboy2.h>

Arduboy2 arduboy;

#define SCREEN_CENTER_X 64
#define SCREEN_CENTER_Y 64
#define SCREEN_LEFT -64
#define SCREEN_RIGHT 63
#define SCREEN_TOP -64
#define SCREEN_BOTTOM 0

typedef struct WordPoint
{
    uint16_t x;
    uint16_t y;
};

typedef struct BytePoint
{
    uint8_t xl; // 小数部
    int8_t xh;  // 整数部
    uint8_t yl; // 小数部
    int8_t yh;  // 整数部
};

typedef union FixPoint {
    WordPoint w;
    BytePoint b;
};

#define X w.x   // xの整数・小数部をひっくるめた値にアクセスする
#define Y w.y   // yの整数・小数部をひっくるめた値にアクセスする
#define XH b.xh // xの整数部にアクセスする
#define XL b.xl // xの小数部にアクセスする
#define YH b.yh // yの整数部にアクセスする
#define YL b.yl // yの小数部にアクセスする

int bPressedTime = 0;
bool isJumping = false;
bool isJumpStart = false;
uint16_t jumpWidth = 0;
int ballRight = 1;
uint16_t crdX = 0;
int crdY = 0;
int maxY = 0;

void setup()
{
    arduboy.begin();
    arduboy.setFrameRate(60);
    arduboy.clear();
}

void loop()
{
    if (!arduboy.nextFrame())
        return;
    arduboy.clear();

    static FixPoint pos;

    if (arduboy.pressed(B_BUTTON) && !isJumping)
    {
        bPressedTime++;
        isJumpStart = true;
    }
    else if (arduboy.notPressed(B_BUTTON) && isJumpStart)
    {
        // 偶数にしておく
        if (bPressedTime % 2 != 0)
        {
            bPressedTime++;
        }
        crdX -= ((bPressedTime / 2) << 8);
        maxY = ((crdX >> 8) * (crdX >> 8)) / 2;
        jumpWidth = (bPressedTime << 8);
        isJumpStart = false;
        isJumping = true;
    }

    // 移動中
    if ((jumpWidth != 0) && isJumping)
    {
        // 横方向の移動
        // 1ずつ移動する
        if (ballRight == 1)
        {
            pos.X += (1 << 6); // 1移動
        }
        else
        {
            pos.X -= (1 << 6); // -1移動
        }

        // 縦方向の移動
        if (crdX < 0)
        {
            // 上
            crdY = maxY - (((crdX >> 8) * (crdX >> 8)) / 2);
            pos.Y -= (crdY << 6);
        }
        else if (crdX > 0)
        {
            // 下
            crdY = maxY - (((crdX >> 8) * (crdX >> 8)) / 2);
            pos.Y += (crdY << 6);
        }
        else
        {
            pos.Y += (maxY << 6);
        }

        jumpWidth -= (1 << 6);
        crdX += (1 << 6);
    }
    // 移動終了
    else if (jumpWidth == 0 && isJumping)
    {
        isJumping = false;
        crdX = 0;
        bPressedTime = 0;
    }

    if (arduboy.pressed(LEFT_BUTTON))
    {
        pos.X -= (1 << 8); // -1移動
        if (pos.XH < SCREEN_LEFT)
            pos.XH = SCREEN_LEFT;
    }
    else if (arduboy.pressed(RIGHT_BUTTON))
    {
        pos.X += (1 << 7); // 0.5移動
        if (pos.XH > SCREEN_RIGHT)
            pos.XH = SCREEN_RIGHT;
    }
    if (arduboy.pressed(UP_BUTTON))
    {
        pos.Y -= (1 << 6); // -0.25移動
        if (pos.YH < SCREEN_TOP)
            pos.YH = SCREEN_TOP;
    }
    else if (arduboy.pressed(DOWN_BUTTON))
    {
        pos.Y += (1 << 5); // 0.125移動
        if (pos.YH > SCREEN_BOTTOM)
            pos.YH = SCREEN_BOTTOM;
    }
    arduboy.fillCircle(pos.XH + SCREEN_CENTER_X, pos.YH + SCREEN_CENTER_Y, 5, WHITE);

    arduboy.print("X=");
    arduboy.print(pos.XH);
    arduboy.print("\n");
    arduboy.print("Y=");
    arduboy.print(pos.YH);
    arduboy.print("\n");

    arduboy.display();
}