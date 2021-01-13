/*---------------------------------------------------------------------------------

This is my first attempt at making a SNES program

I also suck at C

---------------------------------------------------------------------------------*/
#include <snes.h>
#include <modem.h>

extern char snesfont;

//---------------------------------------------------------------------------------

// Wait for the modem
void pauseModem() {
	; ; ; ; ; ; ; ;
}

// Start modem
void initModem() {
	consoleDrawText(1,1,"Connecting to modem...");
	char fn[] = "M2ATDT5555555\n";
	int i;
	for (i = 0; i < sizeof(fn); i++) {
		writeModem(fn[i]);
	}
}

// Main process
int main(void) {

    // Initialize SNES 
	consoleInit();
    
    // Initialize text console with our font
	consoleInitText(0, 0, &snesfont);

	// Now Put in 16 color mode and disable Bgs except current
	setMode(BG_MODE1,0);  bgSetDisable(1);  bgSetDisable(2);

	// Start the modem...
	initModem();
	/*detectMPlay5();
	if (snes_mplay5) {
		consoleDrawText(5,5,"MODEM DETECTED");
	}
	else {
		consoleDrawText(5,5,"NO MODEM DETECTED");
	}*/

	// Draw a wonderfull text :P
	consoleDrawText(1,1,"Modem Test");

	// Wait for nothing :P
	setScreenOn();  

	while(1) {
		// Read from modem

		consoleDrawText(10,10,"Value=%d");
		WaitForVBlank();
	}
	return 0;
}