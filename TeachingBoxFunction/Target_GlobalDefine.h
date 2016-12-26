#ifndef _TARGET_GLOBALDEFINE_H_
#define _TARGET_GLOBALDEFINE_H_


#include "Target_Config.h"


 #if (TARGET_SYSTEM == _WIN32_)
	#include "stdio.h"
	#include "string.h"
	#include "stdlib.h"





    #define ROM_INIT                // variables will be initialized directly in ROM (means no copy from RAM in startup)
    #define ROM                     // code or variables mapped to ROM (i.e. flash)
                                    // usage: CONST BYTE ROM foo = 0x00;
    #define HWACC                   // hardware access through external memory (i.e. CAN)

    // These types can be adjusted by users to match application requirements. The goal is to
    // minimize code memory and maximize speed.
    #define GENERIC                 // generic pointer to point to application data
                                    // Variables with this attribute can be located in external
                                    // or internal data memory.
    #define MEM                     // Memory attribute to optimize speed and code of pointer access.

    #ifndef NEAR
        #define NEAR                // variables mapped to internal data storage location
    #endif

    #ifndef FAR
        #define FAR                 // variables mapped to external data storage location
    #endif

    #ifndef CONST
        #define CONST const         // variables mapped to ROM (i.e. flash)
    #endif

    #define LARGE

    //#define REENTRANT
    //#define PUBLIC __stdcall


    //#ifndef NO_QWORD
    //#ifndef QWORD
    //  //#define QWORD long long int // MSVC .NET can use "long long int" too (like GNU)
    //    #define QWORD __int64
    //#endif
    //#endif

   /* #ifndef NDEBUG
        #ifndef TRACE
            #define TRACE trace
            #ifdef __cplusplus
                extern "C"
                {
            #endif
                void trace (const char *fmt, ...);
            #ifdef __cplusplus
                }
            #endif
        #endif
    #endif*/

    #define UNUSED_PARAMETER(par) par

 //   // MS Visual C++ compiler supports function inlining
 //   #define INLINE_FUNCTION_DEF		//__forceinline

 //   // to actually enable inlining just include the following two lines
 //    #define INLINE_FUNCTION     INLINE_FUNCTION_DEF
 //   // #define INLINE_ENABLED      TRUE

	////#define INLINE_FUNCTION
		
	/*#ifndef ASSERT
		#if !defined (__linux__) && !defined (__KERNEL__)
			#include <assert.h>
			#ifndef ASSERT
				#define ASSERT(p)    assert(p)
			#endif
		#else
			#define ASSERT(p)
		#endif
	#endif*/


	/*#ifndef ASSERTMSG
		#ifndef NDEBUG

				#define ASSERTMSG(expr,string)  if (!(expr)) { \
													PRINTF0 ("Assertion failed: " string);\
													for ( ; ; );}
		#else
			#define ASSERTMSG(expr,string)
		#endif
	#endif*/

	//printf once
	#ifndef PRINTFONCE
		#define PRINTFONCE(string, ...) do{static int Flag = 0;\
											if(Flag == 0){\
											Flag = 1;\
											printf(string,##__VA_ARGS__);\
											}}while(0)
	#endif

	//printf count,显示第几次打印
	#ifndef PRINTFCOUNT
	#define PRINTFCOUNT(string, ...) do{static int Count = 0;\
												Count++;\
												printf(string,##__VA_ARGS__);\
												printf(" %d\n",Count);\
										}while(0)
	#endif
	

#ifdef DEBUG
	#ifndef myLog
	void LogDebug(char* pdata_p);
	void LogDebug(char* pdata_p, int error_p);
	/*#define myLog(string, ...) do{static int Flag = 0;\
									if(Flag == 0){\
									Flag = 1;\
									LogDebug(string,##__VA_ARGS__);\
									}}while(0)*/
	//#define myLog(string, ...) LogDebug(string,##__VA_ARGS__)
	#define myLog(string, ...) do{printf(string,##__VA_ARGS__);\
									printf("\n");\
								}while(0)
	#endif
#endif




	#ifndef UCHAR
        #define UCHAR unsigned char
    #endif

	#ifndef SHORT
        #define SHORT short int
    #endif

    /*#ifndef USHORT
        #define USHORT unsigned short int
    #endif*/

    #ifndef INT
        #define INT int
    #endif

    #ifndef UINT
        #define UINT unsigned int
    #endif

	#ifndef USINT
        #define USINT unsigned short
    #endif

    #ifndef LONG
        #define LONG long int
    #endif

    #ifndef ULONG
        #define ULONG unsigned long int
    #endif

    #ifndef ULONGLONG
        #define ULONGLONG unsigned long long int
    #endif


    // --- logic types ---
   // #ifndef BYTE
   //     #define BYTE unsigned char
   // #endif

    #ifndef WORD
        #define WORD unsigned short int
    #endif

    #ifndef DWORD
        #if defined (__LP64__) || defined (_LP64)
            #define DWORD unsigned int
        #else
            #define DWORD unsigned long int
        #endif
    #endif

    #ifndef TYPE_BOOL
        #define TYPE_BOOL	unsigned char
    #endif


	#ifndef REAL
        #define REAL	double	//float
    #endif

	#ifndef LONG_REAL
        #define LONG_REAL	double
    #endif

    // --- alias types ---
    #ifndef TRUE
        #define TRUE  0x01
    #endif

    #ifndef FALSE
        #define FALSE 0x00
    #endif

    #ifndef NULL
        #define NULL ((void *) 0)
    #endif



	#ifndef TARGET_MEMCPY
    #define TARGET_MEMCPY(dst,src,siz)			memcpy((dst),(src),(siz))
	#endif
	#ifndef TARGET_MEMSET
		#define TARGET_MEMSET(dst,val,siz)     memset((dst),(val),(siz))
	#endif
	#ifndef TARGET_MEMCMP
		#define TARGET_MEMCMP(src1,src2,siz)   memcmp((src1),(src2),(siz))
	#endif
	#ifndef TARGET_MALLOC
		#define TARGET_MALLOC(siz)             malloc(siz)
	#endif
	#ifndef TARGET_FREE
		#define TARGET_FREE(ptr)               free(ptr)
	#endif



#endif  // ===> PC










#endif  // #ifndef _TARGET_GLOBALDEFINE_H_

// EOF

