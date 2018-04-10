; Author: Yuen Han han
; GtId: 902983019

.orig x3000
	LD R0, K
	;Your code here
	
	LD R1,PRIME	;isPrime=1
	LD R2,FOUND	;found=0
LOOP2	ADD R0,R0,1	;K++
	AND R1,R1,0	;isPrime=0
	ADD R1,R1,1	;isPrime=1
	AND R3,R3,0	;i=0
	ADD R3,R3,2	;i=2
LOOP1	AND R4,R4,0	;R4=0
	ADD R4,R3,R3	;2i
	AND R5,R5,0	;R5=0
	NOT R5,R4	;R5=-2i
	ADD R5,R5,1
	ADD R5,R5,R0	;k-2i
	BRNz FISPRIME	;if(k<=2i)
	ADD R1,R1,0	;check isPrime
	BRZ FISPRIME	
	AND R6,R6,0	
	NOT R6,R3	;R3=-i
	ADD R6,R6,1
	AND R5,R5,0
	ADD R5,R6,R0
BACK	BRP CONT
	BRZ SKIP
	ADD R1,R5,R3
SKIPB	ADD R3,R3,1
	BR LOOP1

FISPRIME	AND R2,R2,0	;found=0
		ADD R2,R1,0	;found=isPrime
		BRZ LOOP2	
		BR STOP

STOP ST R0,NEXTPRIME
	HALT

SKIP	AND R1,R1,0	;isPrime=0
	BR SKIPB

CONT	ADD R5,R5,R6
	BR BACK


	K		.fill	1987			; K
	NEXTPRIME	.blkw 	1			; store your answer here
	PRIME		.fill	1
	FOUND		.fill 	0
.end
