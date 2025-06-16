#include "iGraphics.h"
#include <iostream>
#include "iSound.h"
using namespace std;

int pic_x=320, pic_y=135;
int idle_idx = 0;
char run_idle[18][100];
// int groundY = 100;              // Ground level
int jump = 0;                   // Jump flag
int jumpSpeed = 0;              // Current vertical speed
int gravity = 1;                // Gravity strength
int jumpHeight = 14;
int moveSpeed = 10;
bool gameOver = false;
bool isPaused = false;

#define MENU 0
#define GAME 1
#define GAME_OVER 2
#define FRONT_PAGE -1
#define HELP 3

int gameState = FRONT_PAGE;
int gameStartTime = 0;

int bgX = 0;
const int bgScrollSpeed = 2;

Image bg;
int speed= 1;

int bgSoundIdx = -1;
/*
Image bg;
Image golem_idle[2];
Image golem_run_frames[7];
Image golem_jump_frames[11];
Sprite golem;

int tile_x=300,tile_y=122;
int speed=0;
int golem_running=0;
int animation=-1;// 0 idle, 1 run, 2 jump
int direction=0;
*/
void populate_run_images()
{

    for (int i = 0; i < 8; i++)
    {
        sprintf(run_idle[i], "c:/Users/user/OneDrive/Desktop/Game Project Pic/Run%03d.png", i);
    }
}

void update_run()
{
    idle_idx = (idle_idx + 1) % 8;
    // 0 1 2 3 0 1 2 3
}

/*
function iDraw() is called again and again by the system.
*/

/*
void activity(int current_state){
    if( animation != current_state){
        animation =current_state;
        if(current_state == 0) iChangeSpriteFrames(&golem,golem_idle,1);
        if(current_state == 1) iChangeSpriteFrames(&golem,golem_run_frames,7);
        if(current_state == 2) iChangeSpriteFrames(&golem,golem_jump_frames,11);
    }

}


void loadResources(){
    iLoadFramesFromFolder(golem_idle,"c:/Users/user/OneDrive/Desktop/Game Project Pic/OneDrive_30_6-12-2025/walk");
    iLoadFramesFromFolder(golem_run_frames,"c:/Users/user/OneDrive/Desktop/Game Project Pic/OneDrive_30_6-12-2025/run_2");
    iLoadFramesFromFolder(golem_jump_frames,"c:/Users/user/OneDrive/Desktop/Game Project Pic/OneDrive_30_6-12-2025/jump");
    iInitSprite(&golem,-1);
    // if(direction==0){
    iChangeSpriteFrames(&golem,golem_idle,1);
    // }
    // else if(direction==1){
    //     iChangeSpriteFrames(&golem,golem_run_frames,7);
    // }
    iSetSpritePosition(&golem,70,122);
}
*/
void loadResources()
{
    iLoadImage(&bg, "c:/Users/user/OneDrive/Desktop/Game Project Pic/OneDrive_30_6-12-2025/Background1.png");
    iResizeImage(&bg, 800, 500);
}
void iDraw()
{
    iClear();

    if (gameState == FRONT_PAGE)
    {
        iShowImage(0, 0, "c:/Users/user/OneDrive/Desktop/Game Project Pic/1st Cover003.bmp");
        iSetColor(0, 0, 0);
        iText(10, 10, "Press Enter to Continue or Click Main Menu", GLUT_BITMAP_HELVETICA_18);
        return;
    }
    else if(gameState == MENU)
    {

        iShowImage(0, 0,"c:/Users/user/OneDrive/Desktop/Game Project Pic/2nd Cover002.bmp");

        iSetColor(0, 0, 0);
        iText(10, 10, "Press e to Exit or Click Exit button.", GLUT_BITMAP_HELVETICA_18);
        iSetColor(0, 0, 0);
        iText(10, 40, "Press New game to start the game.", GLUT_BITMAP_HELVETICA_18);


        return;

    }
    else if (gameState == HELP)
    {
        iClear();
        // iSetColor(255, 255, 255);
        // iFilledRectangle(0, 0, 800, 500); // White background
        iShowImage(0, 0,"c:/Users/user/OneDrive/Desktop/Game Project Pic/Help Cover001.png");

        iSetColor(0, 0, 0);
        iText(300, 450, "HELP", GLUT_BITMAP_TIMES_ROMAN_24);

        iText(100, 310, "1. Use RIGHT and LEFT arrow keys to move");
        iText(100, 280, "2. Press SPACE to jump");
        iText(100, 250, "3. Avoid obstacles to survive");
        iText(100, 220, "4. Press 'R' to restart the game after Game Over");
        iText(100, 190, "5. Press 'E' to exit the game");

        // Back Button
        iSetColor(100, 100, 100);
        iFilledRectangle(230, 20, 100, 35);
        iSetColor(255, 255, 255);
        iText(265, 35, "Back");
    }


    else if (gameState == GAME)
    {
        // Game logic goes here
        // Background
        /*
        iSetColor(89, 156, 106);
        iFilledRectangle(0, 0, 800, 500);

        // Ground
        iSetColor(56, 21, 3);
        iFilledRectangle(0, 0, 800, 100);

        // Sun
        iSetColor(255, 255, 0);
        iFilledCircle(700, 420, 50);

        // Character
        iShowImage(pic_x, pic_y,  run_idle[idle_idx]);
        */

//loadResources();
        // iShowImage(0, 0,"c:/Users/user/OneDrive/Desktop/Game Project Pic/OneDrive_30_6-12-2025/Background1.png");
        //   iShowImage(bgX, 0, "c:/Users/user/OneDrive/Desktop/Game Project Pic/OneDrive_30_6-12-2025/Background1.png");
        iClear();
//  loadResources();
        iShowLoadedImage(bgX, 0, &bg);
        iShowLoadedImage(bgX + 800, 0, &bg);
        // Update bgX for scrolling (moving left)
        //bgX -= speed;

// Loop the background
       // if (bgX <= -800)
          //  bgX = 0;
          if (!isPaused)
{
    bgX -= speed;
    if (bgX <= -800)
        bgX = 0;
}

//	iWrapImage(&bg, speed);
        iText(70, 30, "Press P to pause and resume.", GLUT_BITMAP_TIMES_ROMAN_24);
          iText(70, 10, "Press M to go to Menu.", GLUT_BITMAP_TIMES_ROMAN_24);

// Character
        iShowImage(pic_x, pic_y,  run_idle[idle_idx]);


        if (gameOver)
        {
            iSetColor(255, 0, 0);
            iText(300, 250, "Game Over! Press R to Restart", GLUT_BITMAP_HELVETICA_18);
        }
    }
}
void iUpdate()
{
    if (gameOver || isPaused)
    return;

    if (jump)
    {
        pic_y += jumpSpeed;
        jumpSpeed -= gravity;

        if (pic_y <= 135)
        {
            pic_y = 135;
            jump = 0;
            jumpSpeed = 0;
        }
    }


}
/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
}

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)

{
    // place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (gameState == FRONT_PAGE)
        {
            if (mx >= 455 && mx <= 755 && my >= 20 && my <= 70)
            {
                gameState = MENU;
            }
        }

        else if (gameState == MENU)
        {
            // New Game
            if (mx >= 540 && mx <= 760 && my >= 305 && my <= 360)
            {
                gameState = GAME;
                gameOver = false;
                gameStartTime = time(NULL);
            }
            // Exit
            else if (mx >= 535 && mx <= 760 && my >= 100 && my <= 150)
            {
                exit(0);
            }
            // Help
            else if (mx >= 535 && mx <= 760 && my >= 170 && my <= 220)
            {
                gameState = HELP;
            }
        }

        else if (gameState == HELP)
        {
            // Back button
            if (mx >= 230 && mx <= 330 && my >= 20 && my <= 55)
            {
                gameState = MENU;
            }
        }

        // For debug (optional)
        printf(" %d %d\n", mx, my);
    }
}

/*
if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
{
    // place your codes here
}
*/

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if (gameState == FRONT_PAGE)
    {
        if (key == 13)   // Enter
        {
            gameState = MENU;
        }
    }

    if (gameState == MENU)
    {
        /*
        if (key == 's' || key == 'S')
        {
            gameState = GAME;
            gameOver = false;
            gameStartTime = time(NULL);
        }
            */
        if (key == 'e' || key == 'E')
        {
            exit(0);
        }
    }
    else if (gameState == GAME)
    {
        if (key == ' ' && !gameOver)
        {
            if (!jump)
            {
                jump = 1;
                jumpSpeed = jumpHeight;
            }
        }
        else if (key == 'r' || key == 'R')
        {
            bgX=0;
            gameOver = false;
            pic_x = 320;
            pic_y = 135;
            gameStartTime = time(NULL);
        }
        else if (key == 'p' || key == 'P')
         {
           isPaused = !isPaused; // toggle pause
         }
        else if (key == 'e' || key == 'E')
        {
            exit(0);
        }
         else if (key == 'm' || key == 'M')
        {
            gameState = MENU;
        }
         

    }
}



/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_RIGHT)
    {
        if (pic_x < 400) // character moves normally until middle
            pic_x += moveSpeed;
        else if (bgX > -800) // then scroll background
            bgX -= bgScrollSpeed;
        else if (pic_x + 50 < 800) // if background fully scrolled, move character
            pic_x += moveSpeed;
    }

    if (key == GLUT_KEY_LEFT)
    {
        if (pic_x > 100)
            pic_x -= moveSpeed;
        else if (bgX < 0)
            bgX += bgScrollSpeed;
    }
    switch (key)
	{
	case GLUT_KEY_UP:
		iIncreaseVolume(bgSoundIdx, 5);
		break;
	case GLUT_KEY_DOWN:
		iDecreaseVolume(bgSoundIdx, 5);
		break;
		// place your codes for other keys here
	default:
		break;
	}

}
/*
void iAnim(){
    if(jump){
        iAnimateSprite(&golem);
        return;
    }

    if(direction==-1){
        golem.x-=3;
        speed=0;
        activity(1);
    }
    else if(direction == 1){
        if(golem.x>350){
            speed=-3;
            tile_x=tile_x+speed;
        }
        else{
            golem.x+=3;
        }
        activity(1);
    }
    else{
        activity(0);
    }

    iAnimateSprite(&golem);
}
*/
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    // place your own initialization codes here.
    // pic_x = 330;
    //   pic_y = 100;
    populate_run_images();
    loadResources();
    iSetTimer(100, update_run);
    iSetTimer(20, iUpdate); // Call iUpdate every 20 ms

    // frontPageImage = iLoadImage("c:/Users/user/OneDrive/Desktop/Game Project Pic/1st Cover003.bmp");
    //iLoadImage(&frontPageImage, "c:/Users/user/OneDrive/Desktop/Game Project Pic/1st Cover003.bmp");
    iInitializeSound();
	bgSoundIdx = iPlaySound("assets/sounds/background.wav", true, 50);
    iInitialize(800, 500, "Super Mario");
    return 0;
}
