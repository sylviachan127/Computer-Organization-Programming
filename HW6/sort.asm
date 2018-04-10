; Do not add any comments beginning with @plugin

; Author: Yuen Han Chan
; GtId: 902983019

.orig x3000
	LD R0, ARRAY_SIZE		; R0 is array_size
	LEA R1, ARRAY			; R1 = address(i)
	; Start your code here

LOOP1S	AND R2,R2,0	;R2=0
	ADD R2,R1,1	;R2=ADDRESS(j)
	LDR R3,R1,0	;i content
LOOP2S  LDR R4,R2,0	;j content
	AND R5,R5,0
	NOT R5,R3
	ADD R5,R5,1
	AND R6,R6,0
	ADD R6,R5,R4
	BRP TEMP
LOOP2E	AND R5,R5,0
	NOT R5,R2
	ADD R5,R5,1
	ADD R5,R5,R1
	AND R6,R6,0
	ADD R6,R0,R5	;n-j
	ADD R6, R6, -1	;n-j-1
	BRP LOOP2
	BRZ LOOP1

LOOP2	ADD R2,R2,1	;address(j++)
	BR LOOP2S

LOOP1	ADD R1,R1,1	;address(i++)
	ADD R0,R0,-1
	AND R5,R5,0
	NOT R5,R1
	ADD R5,R5,1
	LEA R6,ARRAY
	ADD R6,R5,R6	;address(aray)-curren(i)address
	AND R5,R5,0
	ADD R5,R6,R0	;check size -R6
	ADD R5,R5,2
	BRZ STOP
	BRP LOOP1S

STOP 	HALT

TEMP	AND R5,R5,0
	ADD R5,R3,0
	STR R4,R1,0
	STR R5,R2,0
	LDR R3,R1,0
	LDR R4,R2,0
	BR LOOP2E
ARRAY_SIZE 	.fill 	5

ARRAY		.fill 	10
		.fill 	100
		.fill	8
		.fill	3
		.fill	96

.end
