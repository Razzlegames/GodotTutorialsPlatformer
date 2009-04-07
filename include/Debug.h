#include <gba_console.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <gba.h>
#include <pcx.h> 
#include <fade.h>
#include "casper_pcx.h"

#ifndef _Debug_H
#define	_Debug_H

/**
 *  Class used as a debug toolset
 */
class Debug
{
    public:
        static void printSetup();
    
    
};

//******************************************************************************
/**
*   Set up the print system
*/
inline void Debug::printSetup()
{
    static int setup = 0;
    // Check to make sure that the setup only occures once
    //if(setup == 0)
    //{
        consoleInit( 0 , 4 , 0, NULL , 0 , 15);
        BG_COLORS[0]=RGB8(58,110,165);
        BG_COLORS[241]=RGB5(31,31,31);
        
        //------------------------------------------
        //  Experimental
        //------------------------------------------
        /*
        if(!setup)
        {
	        SetMode( MODE_4 | BG2_ON );
	        u16 PaletteBuffer[256];	    
	        DecodePCX(casper_pcx, (u16*)VRAM , PaletteBuffer);
	        FadeToPalette( PaletteBuffer, 60);
	            
	            // 60 frames/sec
	        	int new_frame = 0;
	            while(new_frame < 60*1)
	            {
	                VBlankIntrWait();
	                new_frame++;
	            }
        }
        */
        //------------------------------------------
        
        SetMode(MODE_0 | BG0_ON | OBJ_ENABLE);
        setup = 1;
    //}
}

//******************************************************************************
/**
*   Print stuff to the screen
*       @param s string to print
*       @param x xcord to print at
*       @param y ycord to print at
*/
inline void debugPrint(char* s, int x, int y)
{

      iprintf("%s",s);

}



#endif //  _Debug_H


