#include "iGraphics.h"

/*
function iDraw() is called again and again by the system.
*/

int pic_x,pic_y;
int golem_idx=0;
int jump_idx=0;
// char golem_idle[17][100];
// char golem_jump[11][100];
int jump=0;
int jump_speed=0;
int gravity=1;
int jump_height=15;
int direction=0;
int tile_x=300,tile_y=122;
Image bg;
Image golem_idle[2];
Image golem_run_frames[7];
Image golem_jump_frames[11];
Sprite golem;
int speed=0;
int golem_running=0;
int animation=-1;// 0 idle, 1 run, 2 jump 
void load_bg(){
    iLoadImage(&bg,"OneDrive_30_6-12-2025/Background1.png");
    iResizeImage(&bg,900,450);
}

void loadResources(){
    iLoadFramesFromFolder(golem_idle,"OneDrive_30_6-12-2025/walk");
    iLoadFramesFromFolder(golem_run_frames,"OneDrive_30_6-12-2025/run_2");
    iLoadFramesFromFolder(golem_jump_frames,"OneDrive_30_6-12-2025/jump");
    iInitSprite(&golem,-1);
    // if(direction==0){
    iChangeSpriteFrames(&golem,golem_idle,1);
    // }
    // else if(direction==1){
    //     iChangeSpriteFrames(&golem,golem_run_frames,7);
    // }
    iSetSpritePosition(&golem,70,122);
}

// void populate_golem_image(){
//     for(int i=0;i<17;i++){
//         sprintf(golem_idle[i],"OneDrive_30_6-12-2025/run/Run%.03d.png",i);
//     }
//     for(int i=2;i<13;i++){
//         sprintf(golem_jump[i-2],"OneDrive_30_6-12-2025/jump/Jump%.03d.png",i);
//     }
// }

void activity(int current_state){
    if( animation != current_state){
        animation =current_state;
        if(current_state == 0) iChangeSpriteFrames(&golem,golem_idle,1);
        if(current_state == 1) iChangeSpriteFrames(&golem,golem_run_frames,7);
        if(current_state == 2) iChangeSpriteFrames(&golem,golem_jump_frames,11);
    }

}

void update_jump(){
    if(jump){
        golem.y+=jump_speed;
        jump_speed-=gravity;

        if(golem.y<=122){
            golem.y=122;
            jump=0;
            jump_speed=0;
            activity(1);
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{
    
    if (key == GLUT_KEY_END)
    {
        printf("%d %d",golem.x,golem.y);
        exit(0);
    }
    if (key == GLUT_KEY_LEFT)
    {
        direction=-1;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        direction=1;
    }
    if(key == GLUT_KEY_UP){
        if(!jump){
            jump=1;
            jump_speed=jump_height;
            activity(2);
        }    
    }
    if (key == GLUT_KEY_DOWN){
        direction=0;
    }
}

// void update_idx(){
//     if(direction==1){
//         golem_idx=(golem_idx+1)%8;
//     }
//     else if(direction==-1){
//         golem_idx=9+(golem_idx+1)%8;
//     }
//     else {
//         golem_idx=8;
//     }
//     if(jump==1){
//         jump_idx=(jump_idx+1)%10;
//     }
// }

void iDraw(){
    iClear();
    iShowLoadedImage(0,0,&bg);
    iShowImage(tile_x,tile_y,"sprites/ezgif-split/tile000.png");
    iWrapImage(&bg,speed);
    iShowSprite(&golem);
    // if(jump==1){
    //     iShowImage(pic_x,pic_y,golem_jump[jump_idx]);
    // }
    // else{   
    //     iShowImage(pic_x,pic_y,golem_idle[golem_idx]);
    // }
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
        // place your codes here
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
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
    // if (key==' '){
    //     if(!jump){
    //         jump=1;
    //         jump_speed=jump_height;
    //         iChangeSpriteFrames(&golem,golem_jump_frames,11);
    //     }
    // }     
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    loadResources();
    // place your own initialization codes here.
    pic_x=66,pic_y=122;

    load_bg();
    // populate_golem_image();
    iSetTimer(100,iAnim);
    iSetTimer(20,update_jump);
    iInitialize(900,450,"demo");
    return 0;
}