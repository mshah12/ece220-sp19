;
;
;
.ORIG x3000
	
;your code goes here

; This program takes input in postfix expressions and calculates its result. This is done
; by pushing the operands into a stack, and then pushing out the previously two pushed
; operands when an operator is entered and applying that operator with those two values.
; For negative values, the program determines whether or not one or both of the values are
; negatives and takes the correct approach depending on that. The program pushes the result
; into the stack, so that the next operator can be applied. Whenever an equals sign is entered,
; the program determines if the the number of operators and operands are sufficent enough for 
; the expression to be valid, and then prints out the last pushed value in the stack in ASCII.
;
; partners: ipatel28
;
; REGISTER TABLE -
; R0: Used to hold the value of the number to be pushed onto the stack as well as the final output
; R1: Used for loading ASCII values or other numbers for test cases
; R2: Used as a temporary register to hold values
; R3: Used to hold the first popped stack value
; R4: Used to hold the second popped stack value
; R5: Used as a counter and a temporary register
; R6: Used to count how many operands and operators are entered
; R7: Not used
	
				AND R6,R6,#0 ; clears register
NEXTINPUT		AND R0,R0,#0 ; clears register
				GETC ; takes input from user
				OUT ; echoes the input from the user onto the screen
				LD R1,NEG_SPACE_ASCII ; loads ascii value of negative space into register
				ADD R1,R1,R0 ; checks if input is the space character
				BRz NEXTINPUT ; takes next input if character is space
				LD R1,NEG_NINE ; loads ascii value of negative nine into register
				ADD R1,R1,R0 ; checks if input is greater than '9'
				BRp EVALUATE ; evaluates expression if input is greater than '9'
				LD R1,NEG_ZERO ; loads ascii value of negative zero into register
				ADD R1,R1,R0 ; checks if the input is less than '0'
				BRn EVALUATE ; evaluates expression if input is less than '0'
				LD R1,NEG_ZERO ; loads ascii value of negative zero into register
				ADD R0,R0,R1 ; converts ascii value of operand to binary version
				JSR PUSH ; pushes operand into stack
				ADD R6,R6,#1 ; increments operrand counter
				BRnzp NEXTINPUT ; takes next input








;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX		
					ADD R6,R6,#-1 ; subtracts one from operand counter
					BRnp PRINTINV ; prints invalid if the number of operators exceed operands
					LDI R0, STACK_START ; loads final value after computations into register
					AND R4,R4,#0 ; clears register
					ADD R4,R4,#4 ; sets register to a digit counter of 4
					AND R3,R3,#0 ; clears register
					ADD R3,R0,#0 ; loads contents of current ascii character being printed
					AND R0,R0,#0 ; clears register
					LD R0,X_ASCII ; loads ascii character 'x' into register
					OUT	; prints ascii character 'x'
					AND R0,R0,#0 ; clears register
					ADD R0,R0,#1 ; temporary value to pass the conditional check
NEXTDIGIT			BRz PRINTEDHEX ; checks if all digits in hex are printed
					AND R5,R5,#0 ; clears register
					AND R6,R6,#0 ; clears register
					ADD R6,R6,#4 ; sets register to a bit counter of 4
NEXTBITINDIGIT	    BRz CONVERT_ASCII ; checks if the digit to be printed is complete
					ADD R5,R5,R5 ; left shifts the digit to be printed
					ADD R3,R3,#0 ; clears register
					BRzp POSITIVE ; checks if the valus is positive
					ADD R5,R5,#1 ; adds one to the current digit
					ADD R3,R3,R3 ; left shifts the hexadecimal value
					ADD R6,R6,#-1 ; decrements the bit counter
					BRnzp NEXTBITINDIGIT ; moves onto the next bit
POSITIVE			ADD R5,R5,#0 ; adds zero to the current digit
					ADD R3,R3,R3 ; left shifts the hexadecimal value
					ADD R6,R6,#-1 ; decrements the bit counter
					BRnzp NEXTBITINDIGIT ; moves onto the next bit
CONVERT_ASCII		AND R6,R6,#0 ; clears register
					ADD R6,R5,#-9 ; subtracts 9 from the digit
					BRnz LESS_NINE ; checks whether the digit is <=9
					AND R0,R0,#0 ; clears register
					LD R0,AMINUSTEN_ASCII ; loads value 'A' minus 10 into register
					ADD R0,R0,R5 ; adds digit to the value 'A' minus 10 to convert to ascii
					OUT ; prints digit
					ADD R4,R4,#-1 ; decrements digit counter
					BRnzp NEXTDIGIT ; moves onto next digit
LESS_NINE			AND R0,R0,#0 ; clears register
					LD R0,ZERO_ASCII ; loads '0' into register
					ADD R0,R0,R5 ; adds digit to the value '0' to convert to ascii
					OUT ; prints digit
					ADD R4,R4,#-1 ; decrements digit counter
					BRnzp NEXTDIGIT ; moves onto next digit
PRINTEDHEX			LDI R5,STACK_START
					HALT ; done

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here
				LD R1,NEG_EQUALS ; loads ascii value of negative equals into register
				ADD R1,R1,R0 ; checks if input is the equals sign
				BRz PRINT_HEX ; attempts to print final output if input is equals sign
				ST R0,R0SAVE ; 	saves value of register			
				JSR POP ; pops one value out of stack
				ADD R5,R5,#-1 ; decrements register
				BRz INVALID ; checks whether pop was a success or a failure
				ADD R3,R0,#0 ; stores popped value into register
				JSR POP ; pops one value out of stack
				ADD R5,R5,#-1 ; decrements register
				BRz INVALID ; checks whether pop was a success or a failure
				ADD R4,R0,#0 ; stores popped value into register
				LD R0,R0SAVE ; loads previously stored value of register into register
				LD R1,NEG_PLUS ; loads ascii value of negative plus into register
				ADD R1,R1,R0 ; checks if input is a plus sign
				BRz PLUSOP ; adds popped values if input is plus sign
				LD R1,NEG_MINUS ; loads ascii value of negative minus into register
				ADD R1,R1,R0 ; checks if input is a minus sign
				BRz MINUSOP ; subtracts popped values if input is minus sign
				LD R1,NEG_MULTIPLY ; loads ascii value of negative multiply into register
				ADD R1,R1,R0 ; checks if input is multiplication sign
				BRz MULTIPLYOP ; multiplies popped values if input is multiplication sign
				LD R1,NEG_DIVIDE ; loads ascii value of negative divide sign into register
				ADD R1,R1,R0 ; checks if input is a divide sign
				BRz DIVIDEOP ; divides popped values if input is a divide sign
				LD R1,NEG_POWER ; loads ascii value of negative power sign into register
				ADD R1,R1,R0 ; checks if input is power sign
				BRz POWEROP ; takes the power of popped values if input is power sign
INVALID			GETC ; takes input from user
				OUT ; echoes input from user back onto screen
				LD R1,NEG_EQUALS ; loads ascii value of negative equal sign
				ADD R1,R1,R0 ; checks if input is equal sign
				BRnp INVALID ; takes next input if input is not equals sign
PRINTINV		LEA R0,INVALIDEXP ; loads starting address of string
				PUTS ; displays string to the screen
				HALT ; done
PLUSOP			JSR PLUS ; jumps to plus subroutine
				JSR PUSH ; pushes value into stack
				ADD R6,R6,#-1 ; decrements operand counter
				BRnzp NEXTINPUT ; takes next input from user
MINUSOP			JSR MIN ; jumps to min subroutine
				JSR PUSH ; pushes value into stack
				ADD R6,R6,#-1 ; decrements operand counter
				BRnzp NEXTINPUT ; takes next input from user
MULTIPLYOP		JSR MUL ; jumps to mul subroutine
				JSR PUSH ; pushes value into stack
				ADD R6,R6,#-1 ; decrements operand counter
				BRnzp NEXTINPUT ; takes next input from user
DIVIDEOP		JSR DIV ; jumps to div subroutine
				JSR PUSH ; pushes value into stack
				ADD R6,R6,#-1 ; decrements operand counter
				BRnzp NEXTINPUT ; takes next input from user
POWEROP			JSR EXP ; jumps to exp subroutine
				JSR PUSH ; pushes value into stack
				ADD R6,R6,#-1 ; decrements operand counter
				BRnzp NEXTINPUT ; takes next input from user
	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ADD R0,R3,R4 ; adds values and stores
	RET ; returns back to main program
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here

	
	NOT R4,R4 ; nots value of register
	ADD R4,R4,#1 ; increments value of register
	ADD R0,R3,R4 ; adds values and stores
	NOT R0,R0 ; nots value of register
	ADD R0,R0,#1 ; increments value of register
	RET ; returns back to main program
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
			AND R1,R1,#0 ; clears register			
			ADD R3,R3,#0 ; initializes register for condition codes
			BRp NOTNEG ; checks if value in register is positive
			BRz ZEROCASE4 ; checks if value in register is zero
			ADD R1,R1,#-1 ; sets register to a value of -1
			NOT R3,R3 ; nots value in register
			ADD R3,R3,#1 ; increments register
NOTNEG		ADD R4,R4,#0 ; initializes register for condition codes
			BRp NOTNEG2 ; checks if value in register is postive
			BRz ZEROCASE4 ; checks if value in register is zero
			ADD R1,R1,#1 ; sets register to a value of 1
			NOT R4,R4; ; nots value in register
			ADD R4,R4,#1 ; increments register
NOTNEG2		AND R0,R0,#0 ; clears register
			ADD R0,R3,#0 ; stores value of register into another register
			AND R3,R3,#0 ; clears register
ADDAGAIN	ADD R3,R3,R0 ; adds registers together ands stores value in another register
			ADD R4,R4,#-1 ; decrements register
			BRp ADDAGAIN ; add values again if register is still positive
			AND R0,R0,#0 ; clears register
			ADD R0,R3,#0 ; stores value of register into another register
			ADD R1,R1,#0 ; intializes register for condition code
			BRz POSVALUE ; branches to posvalue if value is positive
			NOT R0,R0 ; nots value in register
			ADD R0,R0,#1 ; increments register
POSVALUE	RET ; returns to the main program 
ZEROCASE4	AND R0,R0,#0 ; clears register
			RET ; returns to the main program
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
			ST R4,R0SAVE ; saves value of register 
			ADD R4,R3,#0 ; stores value of register in another register
			LD R3,R0SAVE ; loads value of register			
			AND R1,R1,#0 ; clears register			
			ADD R3,R3,#0 ; initializes register to check condition codes
			BRp NOTNEG3 ; checks if value in register is positive
			BRz ZEROCASE ; checks if value in register is zero
			NOT R3,R3 ; nots value in register
			ADD R3,R3,#1 ; increments register
			ADD R1,R1,#1 ; increments register
NOTNEG3		ADD R4,R4,#0 ; initializes register to check condition codes
			BRp NOTNEG4 ; checks if value in register is positive
			BRz ZEROCASE2 ; checks if value in register is zero
			NOT R4,R4 ; nots value in register
			ADD R4,R4,#1 ; increments register
			ADD R1,R1,#-1 ; decrements register
NOTNEG4		AND R0,R0,#0 ; clears register
			ADD R0,R0,#-1 ; decrements register
			NOT R4,R4 ; nots value in register
			ADD R4,R4,#1 ; increments register
			BRz ZEROCASE2 ; checks if value in register in zero
SUBAGAIN	ADD R0,R0,#1 ; increments regiseter
			ADD R3,R3,R4 ; adds value of registers together
			BRzp SUBAGAIN ; checks if value is zero or positive in register
			ADD R1,R1,#0 ; initializes register to check condition codes
			BRz POSQUO ; checks if value in register is zero
			NOT R0,R0 ; nots value in register
			ADD R0,R0,#1 ; increments register
POSQUO		RET ; returns to the main program
ZEROCASE	AND R0,R0,#0 ; clears register 
			RET ; returns to the main program
ZEROCASE2	GETC ; takes input from user
			OUT ; echoes input back to the screen
			LD R1,NEG_EQUALS ; loads ascii value of negative equal into register
			ADD R1,R1,R0 ; checks if input is equal sign
			BRnp ZEROCASE2 ; takes next input if current input is not equal sign
			LEA R0,INVALIDEXP ; loads value of string into register
			PUTS ; prints string to the screen 
			HALT ; done

	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
			ST R4,R0SAVE ; saves value of register
			ADD R4,R3,#0 ; stores value of one register into another
			LD R3,R0SAVE ; loads value into register
			AND R1,R1,#0 ; clears register
			AND R0,R0,#0 ; clears register
			ADD R4,R4,#-1 ; decrements register
			BRn ZERO ; checks if value in register is negative
			BRz ONE ; checks if value in register is zero 
			ST R3,R0SAVE ; saves value of register
POW2		LD R1,R0SAVE ; loads value into register
POW1		ADD R0,R0,R3 ; adds values of register and stores into register
			ADD R1,R1,#-1 ; decrements register
			BRp POW1 ; checks if value is positive
			AND R3,R3,#0 ; clears register
			ADD R3,R3,R0 ; adds value of register and stores into register
			AND R0,R0,#0 ; clears register
			ADD R4,R4,#-1 ; decrements register
			BRp POW2 ; checks if value is positive
			AND R0,R0,#0 ; clears register
			ADD R0,R0,R3 ; loads value of one register into another
			RET ; returns to the main program
ZERO		AND R0,R0,#0 ; clears register
			ADD R0,R0,#1 ; sets register to a value of 1
			RET ; returns to the main program
ONE			AND R0,R0,#0 ; clears register
			ADD R0,R0,R3 ; loads value of one reigster to another
			RET ; returns to the main program
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

NEG_SPACE_ASCII	 .FILL xFFE0 ; negative ascii of space
NEG_ZERO		 .FILL #-48 ; negative ascii of zero
NEG_NINE		 .FILL #-57 ; negative ascii of nine
MEMCHECK		.FILL x3FFE ; location of a place in stack
POP_SaveR3	.BLKW #1	; reserves space for the storage of value in register
POP_SaveR4	.BLKW #1	; reserves space for the storage of value in register
STACK_END	.FILL x3FF0	; end location of stack
STACK_START	.FILL x4000	; start locationn of stack
STACK_TOP	.FILL x4000	; stack pointer
NEG_EQUALS 		 .FILL xFFC3 ; negative ascii of equals
NEG_STACK_TOP 	 .FILL xC000 ; negative ascii of stack pointer
NEG_PLUS		 .FILL #-43 ; negative ascii of plus
NEG_MINUS		 .FILL #-45 ; negative ascii of minus
NEG_MULTIPLY	 .FILL #-42 ; negative ascii of multiply
NEG_DIVIDE		 .FILL #-47 ; negative ascii of divide
NEG_POWER		 .FILL #-94 ; negative ascii of power
AMINUSTEN_ASCII	.FILL x0037 ; negative ascii of A minus ten
ZERO_ASCII		.FILL x0030 ; negative ascii of zerp
X_ASCII			.FILL x0078 ; negative ascii of x 
SPACE_ASCII		.FILL x0020 ; ascii value of space
INVALIDEXP	.STRINGZ "Invalid Expression" ; invalid expression string
R0SAVE			.BLKW #1; reserves space for the storage of value in register



.END
