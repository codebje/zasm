;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.1 #9090 (Nov 13 2014) (Mac OS X x86_64)
; This file was generated Sun Mar  5 13:11:25 2017
;--------------------------------------------------------
	.module ___ulong2fs
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl ___ulong2fs
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:60: float __ulong2fs (unsigned long a )
;	---------------------------------
; Function __ulong2fs
; ---------------------------------
___ulong2fs_start::
___ulong2fs:
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl,#-12
	add	hl,sp
	ld	sp,hl
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:62: int exp = 24 + EXCESS;
	ld	-8 (ix),#0x96
	ld	-7 (ix),#0x00
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:65: if (!a)
	ld	a,7 (ix)
	or	a, 6 (ix)
	or	a, 5 (ix)
	or	a,4 (ix)
	jr	NZ,00115$
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:67: return 0.0;
	ld	hl,#0x0000
	ld	e,l
	ld	d,h
	jp	00111$
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:70: while (a & NORM) 
00115$:
	ld	e,-8 (ix)
	ld	d,-7 (ix)
00103$:
	ld	a,7 (ix)
	or	a, a
	jr	Z,00119$
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:73: a >>= 1;
	push	af
	pop	af
	srl	7 (ix)
	rr	6 (ix)
	rr	5 (ix)
	rr	4 (ix)
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:74: exp++;
	inc	de
	jr	00103$
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:77: while (a < HIDDEN)
00119$:
	ld	-8 (ix),e
	ld	-7 (ix),d
	ld	e,-8 (ix)
	ld	d,-7 (ix)
00106$:
	ld	a,6 (ix)
	sub	a, #0x80
	ld	a,7 (ix)
	sbc	a, #0x00
	jr	NC,00120$
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:79: a <<= 1;
	push	af
	pop	af
	sla	4 (ix)
	rl	5 (ix)
	rl	6 (ix)
	rl	7 (ix)
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:80: exp--;
	dec	de
	jr	00106$
00120$:
	ld	-8 (ix),e
	ld	-7 (ix),d
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:84: if ((a&0x7fffff)==0x7fffff) 
	ld	d,4 (ix)
	ld	e,5 (ix)
	ld	b,6 (ix)
	res	7, b
	ld	c,#0x00
	inc	d
	jr	NZ,00110$
	inc	e
	jr	NZ,00110$
	ld	a,b
	sub	a,#0x7F
	jr	NZ,00110$
	or	a,c
	jr	NZ,00110$
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:86: a=0;
	xor	a, a
	ld	4 (ix),a
	ld	5 (ix),a
	ld	6 (ix),a
	ld	7 (ix),a
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:87: exp++;
	inc	-8 (ix)
	jr	NZ,00140$
	inc	-7 (ix)
00140$:
00110$:
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:91: a &= ~HIDDEN ;
	res	7, 6 (ix)
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:93: fl.l = PACK(0,(unsigned long)exp, a);
	ld	hl,#0x0000
	add	hl,sp
	ld	-2 (ix),l
	ld	-1 (ix),h
	ld	e,-8 (ix)
	ld	d,-7 (ix)
	ld	a,-7 (ix)
	rla
	sbc	a, a
	ld	c,a
	ld	b,a
	ld	a,#0x17
00141$:
	sla	e
	rl	d
	rl	c
	rl	b
	dec	a
	jr	NZ,00141$
	ld	a,e
	or	a, 4 (ix)
	ld	-6 (ix),a
	ld	a,d
	or	a, 5 (ix)
	ld	-5 (ix),a
	ld	a,c
	or	a, 6 (ix)
	ld	-4 (ix),a
	ld	a,b
	or	a, 7 (ix)
	ld	-3 (ix),a
	ld	e,-2 (ix)
	ld	d,-1 (ix)
	ld	hl, #0x0006
	add	hl, sp
	ld	bc, #0x0004
	ldir
;/pub/Develop/Projects/zasm-4.0/Test/SDCC/library/___ulong2fs.c:95: return (fl.f);
	ld	hl,#0x0000
	add	hl,sp
	ld	-6 (ix),l
	ld	-5 (ix),h
	ld	l,-6 (ix)
	ld	h,-5 (ix)
	ld	b,(hl)
	inc	hl
	ld	c,(hl)
	inc	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	l,b
	ld	h,c
00111$:
	ld	sp, ix
	pop	ix
	ret
___ulong2fs_end::
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
