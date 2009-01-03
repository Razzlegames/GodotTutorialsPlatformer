// 
// File:   gba_data_types.h
// Author: Administrator
//
// Created on July 2, 2007, 3:09 PM
//

#ifndef _gba_types_H
#define	_gba_types_H
// bool is a standard type in cplusplus, but not in c.    
#ifndef __cplusplus
typedef     unsigned char           bool;
#endif
typedef     unsigned char           u8;
typedef     unsigned short int      u16;
typedef     unsigned int            u32;
typedef     unsigned long long int  u64;

typedef     signed char             s8;
typedef     signed short int        s16;
typedef     signed int              s32;
typedef     signed long long int    s64;

typedef     volatile unsigned char           vu8;
typedef     volatile unsigned short int      vu16;
typedef     volatile unsigned int            vu32;
typedef     volatile unsigned long long int  vu64;

typedef     volatile signed char             vs8;
typedef     volatile signed short int        vs16;
typedef     volatile signed int              vs32;
typedef     volatile signed long long int    vs64;

// fixed point math typedefs

typedef     s16     sfp16;  //1:7:8 fixed point
typedef     s32     sfp32;  //1:19:8 fixed point
typedef     u16     ufp16;  //8:8 fixed point
typedef     u32     ufp32;  //24:8 fixed point

//  Define a type for function pointers
typedef void (*function_ptr)(void);

#define CODE_IN_IWRAM __attribute__((section(".iwram"), long_call))  
// alias type typedefs 

#define FIXED s32

// boolean defines

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif


#endif	/* _gba_types_H */

