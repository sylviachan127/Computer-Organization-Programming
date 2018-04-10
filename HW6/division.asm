; DO NOT ADD ANY LINES THAT BEGIN WITH @plugin OR YOU RISK GETTING A ZERO FOR THIS PART.

; Author: Yuen Han Chan
; GtId: 902983019

.orig x3000
		LD R0, U				; U
		LD R1, V				; V
		
		; Your code here

		AND R2, R2, 0				; REMAINDER = 0
		AND R3, R3, 0				; QUOTIENT = 0
		ADD R1, R1, 0				; CHECK R1(B)
		BRz ERROR				; IF(B==0)
		NOT R4, R1				; R4 = -B 
		ADD R4, R4, 1	
	LOOP1	ADD R3, R3, 1				; R7 = R7+1
		ADD R0, R0, R4				; R4 = A-B;
		BRz ZERO
		BRn NEG
		BRp LOOP1 
	NEG	ADD R3, R3, -1
		ADD R2, R0, R1				; R2 = R0 + R1
		BR  STORE
	ERROR	ADD R3, R3, -1				; QUOTIENT = -1
		BR  STORE
	ZERO	BR  STORE
	STORE	ST R2, REMAINDER			; R2 <- REMAINDER
		ST R3, QUOTIENT				; R3 <- QUOTIENT
		HALT
		; Change U and V to suit your needs
		U .fill 49				; Initialize U x3012
		V .fill 12				; Initialize V x3013
		QUOTIENT .blkw 1			; Store your quotient here
		REMAINDER .blkw 1			; Store your remainder here
.end

