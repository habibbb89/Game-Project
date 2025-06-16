#include "iGraphics.h"

int pic_x=320, pic_y=100;
int idle_idx = 0;
char run_idle[18][100];  
// int groundY = 100;              // Ground level
int jump = 0;                   // Jump flag
int jumpSpeed = 0;              // Current vertical speed
int gravity = 1;                // Gravity strength
int jumpHeight = 14;
int moveSpeed = 10;
bool gameOver = false;
#define MENU 0
#define GAME 1
#define GAME_OVER 2
#define FRONT_PAGE -1
int gameState = FRONT_PAGE;
int gameStartTime = 0;

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


void iDraw()
{
      iClear();

      if (gameState == FRONT_PAGE) {
    iShowImage(0, 0, "c:/Users/user/OneDrive/Desktop/Game Project Pic/1st Cover003.bmp");
    
    iSetColor(0, 0, 0);
    iText(10, 10, "Press Enter to Continue or Click Main Menu", GLUT_BITMAP_HELVETICA_18);
    return;
}


else if(gameState == MENU) {

    /*
        // Background color
        iSetColor(0, 100, 200);
        iFilledRectangle(0, 0, 800, 500);

        // Title
        iSetColor(255, 255, 255);
        iText(330, 400, "SUPER MARIO", GLUT_BITMAP_TIMES_ROMAN_24);

        // Menu options
       // iText(350, 300, "Press S to Start", GLUT_BITMAP_HELVETICA_18);

       // Start Button Rectangle
      iSetColor(0, 150, 0);
         iFilledRectangle(300, 220, 200, 60);

  // Start Button Text
      iSetColor(255, 255, 255);
      iText(360, 240, "START", GLUT_BITMAP_HELVETICA_18);

      //  iText(350, 260, "Press E to Exit", GLUT_BITMAP_HELVETICA_18);
        return;
        */

iShowImage(0, 0,"c:/Users/user/OneDrive/Desktop/Game Project Pic/2nd Cover002.bmp");
    return;


    }

    else if (gameState == GAME) {
        // Game logic goes here
        // Background
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

        if (gameOver) {
            iSetColor(255, 0, 0);
            iText(300, 250, "Game Over! Press R to Restart", GLUT_BITMAP_HELVETICA_18);
        }
    }
}
void iUpdate()
{
    if (gameOver) return;

    if (jump)
    {
        pic_y += jumpSpeed;
        jumpSpeed -= gravity;

        if (pic_y <= 100)
        {
            pic_y = 100;
            jump = 0;
            jumpSpeed = 0;
        }
    }

    // No obstacle logic anymore
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
        if (gameState == FRONT_PAGE) {
            // Click "Main Menu" button on front page
            if (mx >= 455 && mx <= 755  && 
                my >= 20 && my <= 70) {
                gameState = MENU;
            }
        }
       else if (gameState == MENU) {
            // Check if click is inside the start button
            if (mx >= 540 && mx <= 760 &&
                my >= 305 && my <= 360) {
                gameState = GAME;
                gameOver = false;
                gameStartTime = time(NULL);
            }
    }
}
    /*
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
*/
printf("Mouse clicked at: %d %d\n", mx, my);


}

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
    if (gameState == FRONT_PAGE) {
    if (key == 13) { // Enter
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
            gameOver = false;
            pic_x = 320;
            pic_y = 100;
            gameStartTime = time(NULL);
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
    if (key == GLUT_KEY_RIGHT && pic_x + 50 < 800)
    {
        pic_x += moveSpeed;
    }
    if (key == GLUT_KEY_LEFT && pic_x > 0)
    {
        pic_x -= moveSpeed;
    }
    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    // place your own initialization codes here.
   // pic_x = 330;
   //   pic_y = 100;
    populate_run_images();
    iSetTimer(100, update_run);
    iSetTimer(20, iUpdate); // Call iUpdate every 20 ms

    // frontPageImage = iLoadImage("c:/Users/user/OneDrive/Desktop/Game Project Pic/1st Cover003.bmp"); 
    //iLoadImage(&frontPageImage, "c:/Users/user/OneDrive/Desktop/Game Project Pic/1st Cover003.bmp");

    iInitialize(800, 500, "Super Mario");
    return 0;
}