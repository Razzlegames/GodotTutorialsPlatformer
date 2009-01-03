/* 
 * File:   button_definitions.h
 * Author: Kyle Luce
 *
 * Created on July 3, 2007, 10:05 AM
 */

#ifndef _button_definitions_H
#define	_button_definitions_H
#include "gba_data_types.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define R_CTRLINPUT                 *(volatile u16 *)(0x04000130)
#define F_CTRLINPUT_A_PRESSED        (~R_CTRLINPUT & 0x0001)
#define F_CTRLINPUT_B_PRESSED       ((~R_CTRLINPUT & 0x0002)>>1)
#define F_CTRLINPUT_SELECT_PRESSED  ((~R_CTRLINPUT & 0x0004)>>2)
#define F_CTRLINPUT_START_PRESSED   ((~R_CTRLINPUT & 0x0008)>>3)
#define F_CTRLINPUT_RIGHT_PRESSED   ((~R_CTRLINPUT & 0x0010)>>4)
#define F_CTRLINPUT_LEFT_PRESSED    ((~R_CTRLINPUT & 0x0020)>>5)
#define F_CTRLINPUT_UP_PRESSED      ((~R_CTRLINPUT & 0x0040)>>6)
#define F_CTRLINPUT_DOWN_PRESSED    ((~R_CTRLINPUT & 0x0080)>>7)
#define F_CTRLINPUT_R_PRESSED       ((~R_CTRLINPUT & 0x0100)>>8)
#define F_CTRLINPUT_L_PRESSED       ((~R_CTRLINPUT & 0x0200)>>9)

#ifdef	__cplusplus
}
#endif

#endif	/* _button_definitions_H */

