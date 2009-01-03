//
// vector<Gummy*> gummy_vector;
// Main devkitArm Headers
#include <gba.h>
#include <gba_sprites.h>
#include "modules.h"
#include "samples.h"
#include "krawall.h"
#include "mtypes.h"

//--------------------------------
// Game specific includes
//--------------------------------
#include "CrazyHero.h"
#include "Gummy.h"
#include "Sprites.h"
#include "interrupts.h"
#include "Debug.h"
#include "BallGreen.h"
#include "BallBlue.h"
#include "BallRed.h"
#include "Heart.h"
#include "CharacterList.h"
#include "Game.h"

//--------------------------------
//	Pictures/effects/etc various includes
//--------------------------------
#ifdef	__cplusplus
extern "C" {
#endif

    extern void displayIntro();
#include <pcx.h>
#include <fade.h>
#include <stdlib.h>
#include "razzlegames_intro_pcx.h"
#include "casper_pcx.h"
#include "casper2_pcx.h"
#include "toolbox.h"
#ifdef	__cplusplus
}
#endif


extern const unsigned short master_Palette[256];

//void vblFunc(void);
//void queryKeys(void);
//void drawObjects(void);
//extern void interruptServiceRoutine(void);
//void vblFuncNoHam(void);

#define TEST_OBJ_NUM   0

/// This is asserted each time a new VBlank screen ISR 
///   is invoked.  Used to find out what to do in 
///   setting up new frames
int new_frame;

CrazyHero* crazy_hero;
Gummy* gummy;
Gummy* gummy2;
Gummy* gummies[TEST_OBJ_NUM];
//Ball* ball;
Heart* heart;


/// Give an account of what button(s) was/were pushed during 
///     the last game loop.  This prevents more 
///     than one push being detected, while depressed 
__attribute__((aligned(4))) struct ButtonStates_
{

    u8 a_pushed;
    u8 b_pushed;
    u8 start_pushed;
    u8 l_pushed;
    u8 r_pushed;
    u8 select_pushed;

}ButtonStates;

// Keep track of pallet creation
int pallet_number = 0;

bool run_music = true;
CharacterList* character_list;
CharacterList* ball_list;
CharacterList* heart_list;
Ball* movable_ball;
Game game;


//*****************************************************************
/**
 *   Called by the main vector ISR for when a VBLANK 
 *   interrupt occurs
 */

void vblFunc(void)
{

    kramWorker();

    // Call this (preferably during a VBL interrupt) to 
    // commit your OAM information to the hardware. Only 
    // after you did this your sprite changes will appear 
    // on screen.
    Sprites::copyObjToOAM();  

}


//*****************************************************************

void handleBallCollision(Ball* c, Vector2D orig_position)
{

    if(!gummy->getCollisionFlag())
    {

        // If gummy is below, don't allow jumping and crap
        if(!(gummy->collision_box+gummy->position).
                above(c->collision_box+c->position))
        {

            //  Handle sound effects
            if(!gummy->getCollisionFlag() && 
                    gummy->getVelocityVector().magnitude() >= 10)
            {

                gummy->playImpactSound(
                        abs(gummy->getVelocityVector().
                            magnitude()));

            }

            gummy->velocity_vector = 
                -Vector2D((int)gummy->velocity_vector.x*.5,
                        abs(gummy->velocity_vector.y)/3);

            iprintf("\x1b[12;0H Gummy: Below");

        }

        else
        {

            gummy->velocity_vector = 
                Vector2D(gummy->velocity_vector.x,
                        abs(gummy->velocity_vector.y/6));

            iprintf("\x1b[12;0H Gummy: Above");
            gummy->setOnGround();

        }				

    }


    gummy->position = orig_position;
    gummy->showCollision();

    if(gummy->velocity_vector.x/5 == 0)
    {

        //gummy->velocity_vector.x = 0;

    }

    if(gummy->velocity_vector.y/10 == 0)
    {

        gummy->velocity_vector.y = 0;

    }

}

//*****************************************************************
/**
 *  @param m
 *  @param c
 *  @param orig_position
 */

void handleBallBallCollision(Ball* m,Ball* c, 
        Vector2D orig_position)
{

    gummy->playImpactSound(20);

}

//*****************************************************************

void detectBallHeroCollisions(Vector2D orig_position)
{

    CharacterList* current = ball_list;

    //	Debug::printSetup();
    //	Character* c = current->c;
    //	iprintf("\x1b[0;0H current.p: %d,%d",c->position.x,c->position.y);
    //	iprintf("\x1b[1;0H ball.p: %d,%d",ball->position.x,ball->position.y);

    // Check if any balls have collided with the hero
    while(current != NULL)
    {

        Ball* c = (Ball*)current->c;

        if((gummy->collision_box+gummy->position)*
                (c->collision_box+c->position))
        {

            handleBallCollision(c, orig_position);

        }

        current = current->next;

        //		Debug::printSetup();
        //		
        //		CollisionBox gc = gummy->collision_box+gummy->position;
        //		CollisionBox cc = c->collision_box+c->position;
        //		iprintf("\x1b[1;0H gummy.c:(%d,%d),(%d,%d)",
        //				gc.bottom_left.x,gc.bottom_left.y,
        //				gc.top_right.x,gc.top_right.y);
        //		iprintf("\x1b[2;0H current.c:(%d,%d),(%d,%d)",
        //						cc.bottom_left.x,cc.bottom_left.y,
        //						cc.top_right.x,cc.top_right.y);
        //		iprintf("\x1b[3;0H current.p: %d,%d",c->position.x,c->position.y);

    }

}

//*****************************************************************

void detectBallBallCollisions(Ball* m, Vector2D orig_position)
{

    CharacterList* current = ball_list;

    //	Debug::printSetup();
    //	Character* c = current->c;
    //	iprintf("\x1b[0;0H current.p: %d,%d",c->position.x,c->position.y);
    //	iprintf("\x1b[1;0H ball.p: %d,%d",ball->position.x,ball->position.y);

    // Check if any balls have collided with the hero
    while(current != NULL)
    {

        Ball* c = (Ball*)current->c;

        if(m != c && 
                (m->collision_box+m->position)*
                (c->collision_box+c->position))
        {

            //Debug::printSetup();
            //iprintf("\x1b[1;0H ball:ball collision happened!");
            handleBallBallCollision(m, c, orig_position);

        }

        current = current->next;

        //		Debug::printSetup();
        //		CollisionBox gc = m->collision_box+m->position;
        //		CollisionBox cc = c->collision_box+c->position;
        //		iprintf("\x1b[1;0H m.c:(%d,%d),(%d,%d)",
        //				gc.bottom_left.x,gc.bottom_left.y,
        //				gc.top_right.x,gc.top_right.y);
        //		iprintf("\x1b[2;0H current.c:(%d,%d),(%d,%d)",
        //						cc.bottom_left.x,cc.bottom_left.y,
        //						cc.top_right.x,cc.top_right.y);
        //		iprintf("\x1b[3;0H current.p: %d,%d",c->position.x,c->position.y);

    }

}

//*****************************************************************
/**
 *  Handle all object collisions
 */

void detectHeroCollisions(Vector2D orig_position)
{

    detectBallHeroCollisions(orig_position);	

}

//*****************************************************************
/**
 *  Handle all Ball object collisions (also updates Ball Physics)
 */

void detectBallCollisions()
{

    CharacterList* current = ball_list;

    while(current != NULL)
    {

        if(current->c->velocity_vector.x || 
                current->c->velocity_vector.y)
        {

            Vector2D orig_position = current->c->position;

            detectBallBallCollisions((Ball*)current->c, 
                    orig_position);

        }

        current = current->next;

    }

    // For testing only!!!!
    detectBallBallCollisions((Ball*)movable_ball, 
            movable_ball->position-Vector2D(5,5));

}

//*****************************************************************
/**
 *   Draw objects does not exactly draw to LCD, but updates 
 *   graphics related  attrubutes such as physics of 
 *   sprites and the backup OAM buffer.
 */

void drawObjects(void)
{    

    //crazy_hero->updateGraphic();
    Vector2D orig_position = gummy->position;
    gummy->updatePhysics();
    gummy->updateGraphic();

    detectHeroCollisions(orig_position);
    detectBallCollisions();

    heart->updateGraphic();

    //----------------------------------------------
    //  Iterate through all the objects (chars) and 
    //		make sure to redraw them
    //----------------------------------------------
    CharacterList* current = character_list;
    while(current != NULL)
    {
        Character* c = current->c;

        c->updateGraphic();
        current = current->next;
    }

    //       for(int i =0; i < TEST_OBJ_NUM; i++)
    //       {
    //       gummies[i]->updatePhysics();
    //       gummies[i]->updateGraphic();
    //       }

}

//*****************************************************************
/**
 *   Capture keypresses:  Find out what that crazy player wants us to do
 */

void queryKeys(void)
{   

    if((~REG_KEYINPUT & KEY_UP) && (~REG_KEYINPUT & KEY_LEFT))
    {                

        //crazy_hero->moveUp();
        //crazy_hero->moveLeft();

        gummy->moveUp();
        if(~REG_KEYINPUT & KEY_B) 
        {

            gummy->moveLeftRunning();

        }

        else
        {

            gummy->moveLeft();

        }


        //movable_ball->moveUp();
        //movable_ball->moveLeft();
    }

    else if((~REG_KEYINPUT & KEY_UP) && 
            (~REG_KEYINPUT & KEY_RIGHT))
    {

        //crazy_hero->moveUp();
        //crazy_hero->moveRight();

        gummy->moveUp();

        if((~REG_KEYINPUT & KEY_B) )
        {

            gummy->moveRightRunning();

        }

        else
        {

            gummy->moveRight();

        }


        //movable_ball->moveUp();
        //movable_ball->moveRight();

    }

    else if((~REG_KEYINPUT & KEY_DOWN) && 
            (~REG_KEYINPUT & KEY_LEFT))
    {

        //crazy_hero->moveDown();
        //crazy_hero->moveLeft();

        gummy->moveDown();

        if((~REG_KEYINPUT & KEY_B) )
        {

            gummy->moveLeftRunning();

        }

        else
        {

            gummy->moveLeft();

        }

        //movable_ball->moveDown();
        //movable_ball->moveLeft();
    }

    else if((~REG_KEYINPUT & KEY_DOWN)&& 
            (~REG_KEYINPUT & KEY_RIGHT))
    {

        //crazy_hero->moveDown();
        //crazy_hero->moveRight();

        gummy->moveDown();

        if((~REG_KEYINPUT & KEY_B) )
        {

            gummy->moveRightRunning();

        }

        else
        {

            gummy->moveRight();

        }

        //movable_ball->moveRight();
        //movable_ball->moveDown();
    }


    else if(~REG_KEYINPUT & KEY_LEFT)
    {		
        //crazy_hero->moveLeft();

        if(~REG_KEYINPUT & KEY_B) 
        {

            gummy->moveLeftRunning();

        }

        else
        {

            gummy->moveLeft();

        }


        for(int i =0; i < TEST_OBJ_NUM; i++)
        {

            if((~REG_KEYINPUT & KEY_B) )
            {

                gummies[i]->moveLeftRunning();

            }

            else
            {

                gummies[i]->moveLeft();

            }

        }

        //movable_ball->moveLeft();

    }


    else if((~REG_KEYINPUT & KEY_RIGHT))
    {

        //crazy_hero->moveRight();

        if((~REG_KEYINPUT & KEY_B) )
        {

            gummy->moveRightRunning();

        }

        else
        {

            gummy->moveRight();

        }


        for(int i =0; i < TEST_OBJ_NUM; i++)
        {

            if((~REG_KEYINPUT & KEY_B) )
            {

                gummies[i]->moveRightRunning();

            }

            else
            {

                gummies[i]->moveRight();

            }

        }

        //movable_ball->moveRight();
    }

    else if((~REG_KEYINPUT & KEY_UP) )
    {

        //crazy_hero->moveUp();
        gummy->moveUp();
        //movable_ball->moveUp();

    }


    else if((~REG_KEYINPUT & KEY_DOWN) )
    {

        //crazy_hero->moveDown();
        gummy->moveDown();
        //movable_ball->moveDown();

    }

    // If nothing was pushed on D-Pad
    else
    {

        gummy->stoppingX();

        for(int i =0; i < TEST_OBJ_NUM; i++)
        {

            gummies[i]->stoppingX();

        }

    }


    if(~REG_KEYINPUT & KEY_A)
    {   

        //crazy_hero->moveDown();
        gummy->jump(1, ButtonStates.a_pushed);

        for(int i =0; i < TEST_OBJ_NUM; i++)
        {

            gummies[i]->jump(1,ButtonStates.a_pushed);

        }

        // Save the button state for this loop
        ButtonStates.a_pushed = 1;

    }

    else
    {

        gummy->jump(0,ButtonStates.a_pushed);

        for(int i =0; i < TEST_OBJ_NUM; i++)
        {

            gummies[i]->jump(0,ButtonStates.a_pushed);

        }

        // Save the button state for this loop
        ButtonStates.a_pushed = 0;

    }

    // Toggle the music
    if((~REG_KEYINPUT & KEY_START) )
    {

        run_music = !run_music; 

    }

}

#include "toolbox.h"
#define CBB_0  0
#define SBB_0 28

#define CROSS_TX 15
#define CROSS_TY 10

BG_POINT bg0_pt= { 0, 0 } ;

SCR_ENTRY *bg0_map= se_mem[SBB_0];


u32 se_index(u32 tx, u32 ty, u32 pitch)
{	
    u32 sbb= ((tx>>5)+(ty>>5)*(pitch>>5));

    return sbb*1024 + ((tx&31)+(ty&31)*32);
}


void init_map()
{
    int ii, jj;

    // initialize a background
    REG_BG0CNT= BG_CBB(CBB_0) | BG_SBB(SBB_0) | BG_REG_64x64;
    REG_BG0HOFS= 0;
    REG_BG0VOFS= 0;

    // create the tiles: basic tile and a cross
    const TILE tiles[2]= 
    {
        {{0x11111111, 0x01111111, 0x01111111, 0x01111111, 
             0x01111111, 0x01111111, 0x01111111, 0x00000001}
        }
        ,
            {{0x00000000, 0x00100100, 0x01100110, 0x00011000,
                 0x00011000, 0x01100110, 0x00100100, 0x00000000}
            }
        ,
    } ;

    tile_mem[CBB_0][0]= tiles[0];
    tile_mem[CBB_0][1]= tiles[1];

    // create a palette
    pal_bg_bank[0][1]= RGB15(31,  0,  0);
    pal_bg_bank[1][1]= RGB15( 0, 31,  0);
    pal_bg_bank[2][1]= RGB15( 0,  0, 31);
    pal_bg_bank[3][1]= RGB15(16, 16, 16);

    // Create a map: four contingent blocks of 
    //   0x0000, 0x1000, 0x2000, 0x3000.
    SCR_ENTRY *pse= bg0_map;
    for(ii=0; ii<4; ii++)
                for(jj=0; jj<32*32; jj++)
                            *pse++= SE_PALBANK(ii) | 0;
}


//*****************************************************************

int main()
{   
    // Initialize globals
    new_frame = 0;

    // Initialise the interrupt handlers
    irqInit();
    // Make sure VBlank interrupts work
    irqSet(IRQ_VBLANK, vblFunc);

    //crazy_hero = new CrazyHero(50,50,0);  

    // Enable interrupts
    REG_IME = 1;
    irqEnable(IRQ_VBLANK);


    displayIntro();
    init_map();
    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ;

    // Install the krawall +1 interrupt
    irqSet(IRQ_TIMER1, kradInterrupt);

    // Initialize the Krawall sound system, Call this 
    //  function once at startup
    kragInit(KRAG_INIT_STEREO);
    krapPlay(&mod_absnuts_changed,KRAP_MODE_LOOP,0); 

    // the vblank interrupt must be enabled to use VBlankIntrWait
    // no handler is required since the libgba dispatcher 
    // handles the bios flags
    irqEnable(IRQ_TIMER1 | IRQ_VBLANK);

    //while(1);
    // Set up Sprites and Char list
    character_list = new CharacterList();



    Sprites::initSprites();
    gummy = new Gummy(pallet_number++);
    //gummy2 = new Gummy(pallet_number);
    //gummy2->position = Vector2D(70,120);
    //-----------------------------------------
    //		Set up Blue balls
    //-----------------------------------------
    ball_list = new CharacterList();
    Ball* ball = new BallBlue(pallet_number++);

    // For testing
    movable_ball = ball;

    character_list->c = ball;
    ball_list->c = ball;
    Vector2D cv = Vector2D(40,30);
    movable_ball->position = Vector2D(0,0);
    for(int i = 0; i< 5; i++)
    {
        ball = new BallGreen(pallet_number++);
        ball->position = cv;
        character_list->add(ball);
        ball_list->add(ball);
        cv += cv;
    }

    //character_list->add(gummy2);

    //-----------------------------------------
    //		Set up Hearts
    //-----------------------------------------
    heart_list = new CharacterList();
    heart = new Heart(pallet_number++);
    character_list->add(heart);
    heart_list->c = heart;
    for(int i = 0; i < 0; i++)
    {
        heart = new Heart(pallet_number++);
        heart->position += Vector2D(rand()%(SCREEN_WIDTH-16), 
                rand()%(SCREEN_HEIGHT-16));
        character_list->add(heart);
        heart_list->add(heart);
    }


    /*
       for(int i =0; i < TEST_OBJ_NUM; i++)
       {
       gummies[i] = new Gummy(gummy->getPalletNumber(), 
       i, i*40,0, 0);
       }

     */
    //  Load up master pallet (256 16 bit colors, 
    //              Mult*2 since data is short; memcpy size param is in bytes)
    Sprites::addPalletData((unsigned char*)master_Palette, 256*2);    
    gummy->enableSprite();
    //crazy_hero->enableSprite();

    /*
       Debug::printSetup();	     

       iprintf("\x1b[1;0H OAMCopy[6].a[0]: %04x", Sprites::OAMCopy[6].attribute[0]);
       iprintf("\x1b[2;0H OAMCopy[6].a[1]: %04x", Sprites::OAMCopy[6].attribute[1]);
       iprintf("\x1b[3;0H OAMCopy[6].a[2]: %04x", Sprites::OAMCopy[6].attribute[2]);

       iprintf("\x1b[4;0H OAMCopy[7].a[0]: %04x", Sprites::OAMCopy[7].attribute[0]);
       iprintf("\x1b[5;0H OAMCopy[7].a[1]: %04x", Sprites::OAMCopy[7].attribute[1]);
       iprintf("\x1b[6;0H OAMCopy[7].a[2]: %04x", Sprites::OAMCopy[7].attribute[2]);

       iprintf("\x1b[7;0H OAMCopy[2].a[0]: %04x", Sprites::OAMCopy[2].attribute[0]);
       iprintf("\x1b[8;0H OAMCopy[2].a[1]: %04x", Sprites::OAMCopy[2].attribute[1]);
       iprintf("\x1b[9;0H OAMCopy[2].a[2]: %04x", Sprites::OAMCopy[2].attribute[2]);
       iprintf("\x1b[10;0H ball_position(%d,%d)", ball->position.x,ball->position.y);
       iprintf("\x1b[14;0H heart_position(%d,%d)", heart->position.x,heart->position.y);
     */
    SetMode(MODE_0 | OBJ_ENABLE | OBJ_1D_MAP | BG0_ENABLE);

    //REG_BG0CNT |=  BG_256_COLOR;

    if(run_music )
    {
        //  Play music(Volume, Fade)
        krapSetMusicVol(128/2 + 30,0);
    }

    // Infinite loop to keep the program running
    while(1)
    {
        VBlankIntrWait();     
        game.time++;

        queryKeys();
        drawObjects();

        //iprintf("\x1b[11;0H gummy_v(%d,%d)", gummy->velocity_vector.x,gummy->velocity_vector.y);
        //iprintf("\x1b[13;0H Time:%02d:%02d:%02d", game.time.minutes,
        //		game.time.seconds,game.time.sec_1_60th);


        //Sprites::displaySpriteInfo(0);
        new_frame = 0;   
        //Sprites::displaySpriteInfo(ball->getSpriteIndex());

    }

    return 0; 
}
// End of main()
