//#include "Sprites.h"
#include "interrupts.h"
#include "modules.h"
#include "samples.h"
#include "krawall.h"

extern void vblFuncNoHam(void);
/**
*   General vector interrupt service routine.  All interrupts will be serviced 
*   through here
*/

void interruptServiceRoutine(void)
{
    if(REG_INT_INFO && VERTICAL_BLANK_INT != 0)
    {
        //vblFuncNoHam();
        // Register that the interrupt took place
        REG_INT_INFO = VERTICAL_BLANK_INT;
    }
    else if(REG_INT_INFO && TIMER1_INT != 0)
    {
        kradInterrupt();
        // Register that the interrupt took place
        REG_INT_INFO = TIMER1_INT;
    }
    else
    {
      REG_INT_INFO = REG_INT_INFO;  
    }
}

