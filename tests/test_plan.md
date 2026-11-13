Build: gcc -o fin fin.c -lpigpio -lrt -pthread
       gcc -o led led.c -lpigpio -lrt -pthread
Run: sudo ./fin
     sudo ./led

TESTS: Checking Status of Different Temperatures (acceptable range 68-76, inclusive)

Input (F)	Expected Status	Expected LED	Actual Status	Actual LED 
72.0		NORMAL			OFF		NORMAL		OFF
79.0		WARNING		ON		WARNING	ON
65.0		WARNING 		ON		WARNING	ON
68.0		NORMAL			OFF		NORMAL		OFF
76.0		NORMAL			OFF		NORMAL		OFF	
67.9		WARNING 		ON		WARNING	ON	
76.1		WARNING 		ON		WARNING	ON		
71.5		NORMAL			OFF		NORMAL		OFF
0		WARNING		ON		WARNING	ON
-1		WARNING 		ON		WARNING 	ON

Number of Readings Input:
1 is accepted
MAX_READINGS = 100
