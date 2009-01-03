/* 
 * File:   interrupts.h
 * Author: Administrator
 *
 * Created on July 3, 2007, 12:15 PM
 */

#ifndef _interrupts_H
#define	_interrupts_H

#include "bit_setting.h"
#include "gba_data_types.h"

#ifdef	__cplusplus
extern "C" {
#endif
    /**
    Interrupt Enable Register bit definitions
    Bit 0: Vertical Blank Interrupt.
    Bit 1: Horizontal Blank Interrupt.
    Bit 2: Vertical Count Interrupt.
    Bit 3: Timer 0 Interrupt.
    Bit 4: Timer 1 Interrupt.
    Bit 5: Timer 2 Interrupt.
    Bit 6: Timer 3 Interrupt.
    Bit 7: Communications Interrupt.
    Bit 8: DMA 0 Interrupt.
    Bit 9: DMA 1 Interrupt.
    Bit A: DMA 2 Interrupt.
    Bit B: DMA 3 Interrupt.
    Bit C: Keyboard Interrupt.
    Bit D: Cart Interrupt.    
    */
    #define     REG_INT_ENABLE        *(volatile u16*)(0x04000200)
    #define     REG_INT_INFO          *(volatile u16*)(0x04000200)
    #define     VERTICAL_BLANK_INT          BIT0
    #define     HORIZONTAL_BLANK_INT        BIT1
    #define     VERTICAL_COUNT_INT          BIT2
    #define     TIMER0_INT                  BIT3
    #define     TIMER1_INT                  BIT4
    #define     TIMER2_INT                  BIT5
    #define     TIMER3_INT                  BIT6
    #define     COMMUNICATIONS_INT          BIT7
    #define     DMA0_INT                    BIT8
    #define     DMA1_INT                    BIT9
    #define     DMA2_INT                    BIT10
    #define     DMA3__INT                   BIT11
    #define     KEYBOARD_INT                BIT12
    #define     CART_INT                    BIT13
    
    // Register to load address of interrupt service routine
    #define REG_INTMAIN                *(function_ptr*)(0x03007FFC)
    //#define REG_IME                     *(volatile u16*)(0x04000208)
#ifdef	__cplusplus
}
#endif

#endif	/* _interrupts_H */

