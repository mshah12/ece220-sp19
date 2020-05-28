;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
	
; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments
;
;
;
;
; This program prints out a histogram. It counts how many times a specific 
; letter occurs and prints out the value in hexadecimal. The program also
; counts how many times a non-alphabetical character appears, and also prints
; the value of that in hexadecimal. This is done by printing one ASCII character
; and then finding its corresponding memory location to determine how many times
; that character appears in the string. The value in the memory location is 
; converted and printed out by left shifting the value and figuring out if the
; MSB was a "1" or a "0" by using conditional codes. The correct bit is then added
; to temporary register, and once the register holds 4 bits, it has one of the four
; digits of the hexadecimal to be printed. This process is repeated 4 times for each
; character to get 4 digits to be printed. This process is repeated 27 times for all
; non-alphabetical characters and letters to be printed.
;
; partners: ipatel28
;
; TABLE OF REGISTERS:
; R0 - Holds the ASCII value of whatever is to be printed 
; R1 - Holds the ASCII value of the current character whose label needs to be printed
; R2 - Holds the Address of the current ASCII character to be printed (starting at @)
; R3 - Holds the contents that is stored in the address of the current ASCII character 
; 	being printed. Also used to store and keep track of which character is being printed
; R4 - Used as a digit counter for keeping track of which digit in the hexadecimal is 
;      being printed
; R5 - Holds the digit of the hexadecimal being printed
; R6 - Used as a bit counter to keep track of which bit in the digit is being printed. Also
;      used as a temporary register to test values


					AND R1,R1,#0 ; clears register
					AND R2,R2,#0 ; clears register
					AND R3,R3,#0 ; clears register
					LD R3,NUM_BINS ; loads the num_bin count
					LD R1,STARTING_ASCII ; loads value of starting bin
					LD R2,HIST_ADDR ; loads address of starting bin
NEXTBIN				ST R3,NUM_BINS_VALUE ; stores value of current num_bin count to memory
					AND R3,R3,#0 ; clears register
					AND R0,R0,#0 ; clears register
					ADD R0,R1,#0 ; sets register to value of current ascii character
					OUT ; prints out current ascii character
					AND R0,R0,#0 ; clears register
					LD R0,SPACE_ASCII ; loads the space ascii character 
					OUT ; prints out a space
					AND R4,R4,#0 ; clears register
					ADD R4,R4,#4 ; sets register to a digit counter of 4
					AND R3,R3,#0 ; clears register
					LDR R3,R2,#0 ; loads contents of current ascii character being printed
					ADD R0,R0,#1 ; temporary value to pass the conditional check
NEXTDIGIT				BRz PRINTEDHEX ; checks if all digits in hex are printed
					AND R5,R5,#0 ; clears register
					AND R6,R6,#0 ; clears register
					ADD R6,R6,#4 ; sets register to a bit counter of 4
NEXTBITINDIGIT	    			BRz CONVERT_ASCII ; checks if the digit to be printed is complete
					ADD R5,R5,R5 ; left shifts the digit to be printed
					ADD R3,R3,#0 ; clears register
					BRzp POSITIVE ; checks if the valus is positive
					ADD R5,R5,#1 ; adds one to the current digit
					ADD R3,R3,R3 ; left shifts the hexadecimal value
					ADD R6,R6,#-1 ; decrements the bit counter
					BRnzp NEXTBITINDIGIT ; moves onto the next bit
POSITIVE				ADD R5,R5,#0 ; adds zero to the current digit
					ADD R3,R3,R3 ; left shifts the hexadecimal value
					ADD R6,R6,#-1 ; decrements the bit counter
					BRnzp NEXTBITINDIGIT ; moves onto the next bit
CONVERT_ASCII				AND R6,R6,#0 ; clears register
					ADD R6,R5,#-9 ; subtracts 9 from the digit
					BRnz LESS_NINE ; checks whether the digit is <=9
					AND R0,R0,#0 ; clears register
					LD R0,AMINUSTEN_ASCII ; loads value 'A' minus 10 into register
					ADD R0,R0,R5 ; adds digit to the value 'A' minus 10 to convert to ascii
					OUT ; prints digit
					ADD R4,R4,#-1 ; decrements digit counter
					BRnzp NEXTDIGIT ; moves onto next digit
LESS_NINE				AND R0,R0,#0 ; clears register
					LD R0,ZERO_ASCII ; loads '0' into register
					ADD R0,R0,R5 ; adds digit to the value '0' to convert to ascii
					OUT ; prints digit
					ADD R4,R4,#-1 ; decrements digit counter
					BRnzp NEXTDIGIT ; moves onto next digit
PRINTEDHEX				BRnzp NEXTLINE ; moves onto next ascii character to be printed
NEXTLINE				AND R0,R0,#0 ; clears register
					LD R0,NEWLINE_ASCII ; loads new_line ascii character into register
					OUT ; prints new line character
					ADD R2,R2,#1 ; moves onto next ascii character's location
					ADD R1,R1,#1 ; increments to the next ascii character to be printed
					AND R3,R3,#0 ; clears register
					LD R3,NUM_BINS_VALUE ; loads the current num_bins value into register
					ADD R3,R3,#-1 ; decrements num_bins value
					BRp NEXTBIN ; moves onto next ascii character to be printed
					BRnzp DONE ; checks whether all ascii characters have been printed
DONE					HALT ; done


; the data needed by the program
NUM_BINS	  	.FILL #27 ; 27 loop iterations
NEG_AT		 	.FILL xFFC0 ; the additive inverse of ASCII '@'
AT_MIN_Z	  	.FILL xFFE6 ; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	  	.FILL xFFE0 ; the difference between ASCII '@' and '`'
HIST_ADDR	  	.FILL x3F00 ; histogram starting address
STR_START	  	.FILL x4000 ; string starting address
STARTING_ASCII		.FILL x0040 ; ascii value for the starting ascii character to be printed (@)
SPACE_ASCII   		.FILL x0020 ; ascii value for the space ascii character
NEWLINE_ASCII 		.FILL x000A ; ascii value for the new line ascii character
AMINUSTEN_ASCII 	.FILL x0037 ; ascii value for 'A' minus 10
ZERO_ASCII		.FILL x0030 ; ascii value for '0'
NUM_BINS_VALUE 	.BLKW #1 ; reserves one block of memory for the storage of num_bins value

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
