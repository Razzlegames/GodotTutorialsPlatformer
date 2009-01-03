/* 
 * File:   bit_setting.h
 * Author: Administrator
 *
 * Created on July 3, 2007, 12:18 PM
 */

#ifndef _bit_setting_H
#define	_bit_setting_H

#ifdef	__cplusplus
extern "C" {
#endif


// Define OR MASK for every binary bit in a 16 bit register
//      Done in this 'constant number' way to avoid shift instructions at runtime.
    
//#define BIT(n) (1<<(n))
#define BIT0  0x0001
#define BIT1  0x0002
#define BIT2  0x0004
#define BIT3  0x0008
#define BIT4  0x0010
#define BIT5  0x0020
#define BIT6  0x0040
#define BIT7  0x0080
#define BIT8  0x0100
#define BIT9  0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000
#define BIT_SET(value,bit) ((value) & (bit))

#define NOT_BIT0  0xFFFE
#define NOT_BIT1  0xFFFD
#define NOT_BIT2  0xFFFB
#define NOT_BIT3  0xFFF7
#define NOT_BIT4  0xFFEF
#define NOT_BIT5  0xFFDF
#define NOT_BIT6  0xFFBF
#define NOT_BIT7  0xFF7F
#define NOT_BIT8  0xFEFF
#define NOT_BIT9  0xFDFF
#define NOT_BIT10 0xFBFF
#define NOT_BIT11 0xF7FF
#define NOT_BIT12 0xEFFF
#define NOT_BIT13 0xDFFF
#define NOT_BIT14 0xBFFF
#define NOT_BIT15 0x7FFF
#define NOT_BIT_SET(value,bit) (!((value) & (bit)))

#ifdef	__cplusplus
}
#endif

#endif	/* _bit_setting_H */

