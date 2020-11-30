//This file is generated by a script. 
/*
 * Copyright (c) 2020 by Deqing Sun <ds@thinkcreate.us> (c version for CH552 port)
 * WS2812 library for arduino CH552.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */


#include "WS2812.h"

void neopixel_show_long_P3_4(uint32_t dataAndLen) {
  //'dpl' (LSB),'dph','b' & 'acc'
  //DPTR is the array address, B is the low byte of length
#if F_CPU == 24000000
  __asm__ ("    mov r3, b                           \n"

           ";save EA to R6                          \n"
           "    mov c,_EA                           \n"
           "    clr a                               \n"
           "    rlc a                               \n"
           "    mov r6, a                           \n"
           ";disable interrupt                      \n"
           "    clr _EA                             \n"

           //even may skip a byte, may leaving it 0xFF, and the MOV R7,A may affect R7
           //CH552 can save 1 instruction of jump/branch insctruction go to an even addr
           ".even                                   \n"
           "startNewByte$:                          \n"
           "    movx  a,@dptr                       \n"
           "    inc dptr                            \n"
           "loopbit$:                               \n"
           "    setb _P3_4                          \n"
           "    rlc a                               \n"
           "    nop                                 \n"  //make it even
           "    jnc bit7skipLowNop$                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "bit7skipLowNop$:                        \n"
           "    clr _P3_4                           \n"
           "    jc bit7skipHighNop$                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "    nop                                 \n"
           "bit7skipHighNop$:                       \n"
           "    anl ar2,#7                          \n"

           "    djnz r2,loopbit$                    \n"
           "    djnz r3,startNewByte$               \n"
           "    nop                                 \n"
           "    setb _P3_4                          \n"

           ";restore EA from R6                     \n"
           "    mov a,r6                            \n"
           "    jz  skipRestoreEA_NP$               \n"
           "    setb  _EA                           \n"
           "skipRestoreEA_NP$:                      \n"

          );
          
          (void)dataAndLen;
#else
#error Only support 24M clock for neopixel now
#endif
}