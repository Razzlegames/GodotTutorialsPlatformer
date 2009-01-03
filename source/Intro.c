#include <gba.h>

//--------------------------------
//	Pictures/effects/etc various includes
//--------------------------------
#ifdef	__cplusplus
extern "C" {
#endif
#include <pcx.h>
#include <fade.h>
#include <stdlib.h>
#include "razzlegames_intro_pcx.h"
#include "casper_pcx.h"
#include "casper2_pcx.h"
#ifdef	__cplusplus
}
#endif

extern int new_frame;

//******************************************************************************
/**
 * 			Display the start up splash screens (intro)
 */

void displayIntro()
{
    u16 PaletteBuffer[256];
    SetMode( MODE_4 | BG2_ON );

    DecodePCX(casper_pcx, (u16*)VRAM , PaletteBuffer);
    FadeToPalette(PaletteBuffer, 60);

    // 60 frames/sec
    while(new_frame < 60*1)
    {
        VBlankIntrWait();
        new_frame++;
    }

    new_frame = 1;
    FadeToBlack(60);
    SetMode(MODE_4 | BG2_ON | BG0_ON);    
    DecodePCX(casper2_pcx, (u16*)VRAM , PaletteBuffer);
    FadeToPalette( PaletteBuffer, 60);

    // 60 frames/sec
    while(new_frame < 60*1)
    {
        VBlankIntrWait();
        new_frame++;
    }

    new_frame = 1;
}


