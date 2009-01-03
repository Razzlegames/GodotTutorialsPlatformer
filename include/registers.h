/* 
 * File:   registers.h
 * Author: kyle2
 *
 * Created on July 1, 2007, 3:28 PM
 */

#ifndef _registers_H
#define	_registers_H


#include <gba_dma.h>

#ifdef	__cplusplus
extern "C" {
#endif


// Fast DMA Stuff
#define REG_DMA_BASE    0x40000B0
    //#define REG_DMA0DAD     *(volatile unsigned int*)(REG_DMA_BASE)


#define REG_DMASAD(reg) 
    //#define REG_DMA3SAD *(volatile unsigned int*)0x40000D4
    //#define REG_DMA3DAD *(volatile unsigned int*)0x40000D8
    //#define REG_DMA3CNT *(volatile unsigned int*)0x40000DC
    //#define DMA_ENABLE 0x80000000
#define DMA_TIMING_IMMEDIATE 0x00000000
#define DMA_16 0x00000000
#define DMA_32 0x04000000
#define DMA_32NOW (DMA_ENABLE | DMA_TIMING_IMMEDIATE | DMA_32)
#define DMA_16NOW (DMA_ENABLE | DMA_TIMING_IMMEDIATE | DMA_16)
    
typedef struct tagDMAREC
{
    const void *src;
    void *dst;
    u32 cnt;
} DMAREC;

#define dma_mem ((volatile DMAREC*)0x040000b0)

#define DMA_TRANSFER(_dst, _src, _count, _ch, _mode)    \
do {                                            \
    dma_mem[_ch].cnt= 0;                        \
    dma_mem[_ch].src= (const void*)(_src);      \
    dma_mem[_ch].dst= (void*)(_dst);            \
    dma_mem[_ch].cnt= (_count) | (_mode);       \
} while(0)


static inline void dmaCopy32(const void * source, void * dest, u32 size) {
	DMA_Copy(3, source, dest, DMA32 | size>>2);
}

#ifdef	__cplusplus
}
#endif

#endif	/* _registers_H */

