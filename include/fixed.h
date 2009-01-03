#ifndef FIXED_H_
#define FIXED_H_

typedef long fixed;			// Our new fixed point type.

#define itofx(x) ((x) << 8)			// Integer to fixed point
#define ftofx(x) ((x) * 256)			// Float to fixed point
#define dtofx(x) ((x) * 256)			// Double to fixed point
#define fxtoi(x) ((x) >> 8)			// Fixed point to integer
#define fxtof(x) ((float) (x) / 256)		// Fixed point to float
#define fxtod(x) ((double)(x) / 256)	        // Fixed point to double
#define Multfx(x,y) (((y) * (x)) >> 8)		// Multiply a fixed by a fixed
#define Divfx(x,y) ((y << 8) / (x))    		// Divide a fixed by a fixed
#define Printfx(x) printf("%ld.%ld", x >> 8, 100 * (unsigned long) ((x) & 0x00ff) >> 8)
// Print fixed point.
#define NDPrintfx(x) printf("%ld", x >> 8)
// Print fixed point without a decimal point.

#endif /*FIXED_H_*/
