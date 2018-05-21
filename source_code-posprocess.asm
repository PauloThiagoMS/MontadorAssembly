 
 
 
Printxy 
 
 
 
 
 
 
 
 
list p=16f819 
 #include <p16f819.inc> 
 
 
 __config _INTRC_IO & _WDT_OFF & _PWRTE_ON & _MCLR_OFF & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CCP1_RB2 & _CP_OFF 
 
 
 
 org H'0' 
 goto inicio 
 
 
 org H'0004' 
 retfie 
 
 
 
inicio : 
 
 
 cblock 0x20 
 Cont 
 Endc 
 movlw H'1' 
 movwf Cont 
 
 
 BANKSEL ADCON1 
 MOVLW 0x06 
 MOVWF ADCON1 
 
 
 BANKSEL TRISB 
 movlw H'00' 
 movwf TRISB 
 
 
 BANKSEL TRISA 
 movlw H'FF' 
 movwf TRISA 
 
 
 BANKSEL PORTB 
 CLRF PORTB 
 call Print0 
 
Loop : 
 btfsc PORTA , RA0 
 call incremento 
 goto Loop 
 
 
 
incremento : 
 btfsc PORTA , RA0 
 goto incremento 
 call Print 
 incf Cont 
 return 
 
 
Print : 
 movlw D'0' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print0 
 
 movlw D'1' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print1 
 
 movlw D'2' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print2 
 
 movlw D'3' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print3 
 
 movlw D'4' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print4 
 
 movlw D'5' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print5 
 
 movlw D'6' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print6 
 
 movlw D'7' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print7 
 
 movlw D'8' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print8 
 
 movlw D'9' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print9 
 
 movlw D'10' 
 subwf Cont , w 
 btfsc STATUS , 2 
 call Print10 
 return 
 
Print0 : 
 movlw B'00111111' 
 movwf PORTB 
 return 
 
Print1 : 
 movlw B'00000110' 
 movwf PORTB 
 return 
 
Print2 : 
 movlw B'01011011' 
 movwf PORTB 
 return 
 
Print3 : 
 movlw B'01001111' 
 movwf PORTB 
 return 
 
Print4 : 
 movlw B'01100110' 
 movwf PORTB 
 return 
 
Print5 : 
 movlw B'01101101' 
 movwf PORTB 
 return 
 
Print6 : 
 movlw B'01111101' 
 movwf PORTB 
 return 
 
Print7 : 
 movlw B'00100111' 
 movwf PORTB 
 return 
 
Print8 : 
 movlw B'01111111' 
 movwf PORTB 
 return 
 
Print9 : 
 movlw B'01101111' 
 movwf PORTB 
 return 
 
Print10 : 
 movlw D'0' 
 movwf Cont 
 call Print0 
 return 
 
 
 
 end 
 
 
 
 
 
 
