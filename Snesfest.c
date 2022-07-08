#include <snes.h>

extern char snesfont;

int main(void) {
	consoleInit();
    
    // Initialize text console with our font
	consoleInitText(0, 0, &snesfont);

	consoleDrawText(5,8,"SNES FEST");

	setMode(BG_MODE1,0);
	bgSetDisable(1);
	bgSetDisable(2);

	setBrightness(0xF);  
	
	while(1) {
	}
	
	return 0;
}
