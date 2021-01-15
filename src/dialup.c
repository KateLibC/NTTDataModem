/*---------------------------------------------------------------------------------

This is my first attempt at making a SNES program

I also suck at C

---------------------------------------------------------------------------------*/
#include <snes.h>
#include <modem.h>

extern char snesfont;

//---------------------------------------------------------------------------------

// Writes to the modem
void sendModem(char *x) {
	int i;
	for (i = 0; i < sizeof(x); i++) {
		consoleDrawText(3+i,3,x[i]);
		WaitForVBlank();
		writeModem(x[i]);
		WaitForVBlank();
	}
}

// Start modem
void initModem() {
	consoleDrawText(1,1,"Connecting to modem...");
	char *a[15];
	a[0] = "ATE1Q0V1\n";
	a[1] = "ATE1Q0V1\n";
	a[2] = "AT&F&W0&W1\n";
	a[3] = "ATZ\n";
	a[4] = "ATS7=60\n";
	a[5] = "ATS8=3\n";
	a[6] = "ATT\n";
	a[7] = "ATL2\n";
	a[8] = "AT%B9600\n";
	a[9] = "AT\\N0%C0\n";
	a[10] = "ATS9=6\n";
	a[11] = "ATS10=14\n";
	a[12] = "ATS11=95\n";
	a[13] = "ATS91=15\n";
	a[14] = "ATX4\n";
	a[15] = "ATD5555555\n";
	int i;
	for (i = 0; i < sizeof(a); i++) {
		sendModem(a[i]);
		char r = readModem();
		WaitForVBlank();
		consoleDrawText(1,4,r);
	}
	consoleDrawText(1,6,"Dialed?");
	WaitForVBlank();
}

// Main process
int main(void) {

    // Initialize SNES 
	consoleInit();
    
    // Initialize text console with our font
	consoleInitText(0, 0, &snesfont);

	// Now Put in 16 color mode and disable Bgs except current
	setMode(BG_MODE1,0);  bgSetDisable(1);  bgSetDisable(2);

	// Wait for nothing :P
	setScreenOn();  

	// Start the modem...
	initModem();
}