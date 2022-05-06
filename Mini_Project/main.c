#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "DE1SoC_WM8731/DE1SoC_WM8731.h"
#include "My_LCD.h"
#include "My_Driver/Audio_Out.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_IRQ/HPS_IRQ.h"
#include "HPS_usleep/HPS_usleep.h"
#include "DE1SoC_SevenSeg/DE1SoC_SevenSeg.h"
#include "global.h"
#include <math.h>
#include "Test.h"
#include <stdlib.h>

volatile unsigned int * Private_timer_ptr   = (unsigned int *) 0xFFFEC600;
volatile unsigned int * KEY_ptr       = (unsigned int *) 0xFF200050;

unsigned int MODE;
double ampl;
unsigned int counter;

//Vector Font Parameters
int fontsize = 60;
int fontcolour = 0XFFFF;
//Draw Line Parameters
unsigned int Linex1 = 1;
unsigned int Liney1 = 1;
unsigned int Linex2 = 240;
unsigned int Liney2 = 320;
unsigned int Linecolour = 0xFFFF;
//Draw Rectangle Parameters
unsigned int recx1 = 10;
unsigned int recy1 = 10;
unsigned int recw = 120;
unsigned int rech = 120;
unsigned int reccolour = 0xFFFF;
//Draw Triangle Parameters
unsigned int Trianglex1 = 120;
unsigned int Triangley1 = 20;
unsigned int Trianglex2 = 60;
unsigned int Triangley2 = 200;
unsigned int Trianglex3 = 180;
unsigned int Triangley3 = 200;
//Draw Text Parameters
unsigned int Textx = 120;
unsigned int Texty = 160;
unsigned int Textnumber = 20;
unsigned int Textcolour = 0xFFFF;


void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}

void pushbuttonISR(HPSIRQSource interruptID, bool isInit, void* initParams) {
    if (!isInit)
    {
    	// Get the button number being pushed.
        unsigned int press;
        press = KEY_ptr[3];
        //switch to another function
        if (press == 0x08)
        {
        	MODE = MODE+1;
        	if (MODE ==6)
        	{
        		DE1SoC_SevenSeg_SetDoubleDec(0x00,MODE);
        		//Disable Timer to disable LCD auto fresh
        		Private_timer_ptr[2] = 0x00;
        		Audio_Out();
        	}

        	if (MODE ==7)
        	{
        		MODE = 1;
        		//Enable Timer to enable LCD auto fresh
        		Private_timer_ptr[2] = 0xE007;
        	}
        }
        //Indicate the MODE number in the 7 segment display
        DE1SoC_SevenSeg_SetDoubleDec(0x00,MODE);
        //Vector Text
        if (MODE == 1)
        {
            if (press==0x01)
            {
            	// Make the text larger
            	fontsize = fontsize * 1.2;
            }
            else if (press==0x02)
            {
            	// Make the text smaller
            	fontsize = fontsize * 0.8;
            }
            else if (press==0x04)
            {
            	// Generate random colour
            	fontcolour = rand()%31+rand()%63*32+rand()%31*2048;
            }
        	FrameBuffer_Clear(0);

        	FrameBuffer_DrawH(100, 0,fontsize, fontcolour);
        	FrameBuffer_DrawY(100, 100, fontsize,fontcolour);
			FrameBuffer_DrawH(100, 200,fontsize, fontcolour);
        }
        //Draw Line
        if (MODE ==2)
        {
            if (press==0x01)
            {
            	// Generate random position for (x1,y1)
            	Linex1 = rand()%240;
            	Liney1 = rand()%320;
            }
            else if (press==0x02)
            {
            	// Generate random position for (x2,y2)
            	Linex2 = rand()%240;
            	Liney2 = rand()%320;
            }
            else if (press==0x04)
            {
            	// Generate random colour for line
            	Linecolour = rand()%31+rand()%63*32+rand()%31*2048;
            }
        	FrameBuffer_Clear(0);
        	FramBuffer_DrawLine(Linex1,Liney1,Linex2,Liney2,Linecolour);
        	FramBuffer_DrawLine(1,160,240,160,0xFFFF);
        	FramBuffer_DrawLine(120,1,120,320,0xFFFF);
        }
        //Draw Rectangle
        if (MODE ==3)
        {
            if (press==0x01)
            {
            	// Generate random position
            	recx1 = rand()%100;
            	recy1 = rand()%100;
            }
            else if (press==0x02)
            {
            	// Generate random size
            	recw = rand()%100;
            	rech = rand()%100;
            }
            else if (press==0x04)
            {
            	// Generate random colour
            	reccolour = rand()%31+rand()%63*32+rand()%31*2048;
            }
        	FrameBuffer_Clear(0);
        	FramBuffer_DrawRectangle(recx1,recy1,recw,rech,reccolour);

        }
        //Draw Triangle
        if (MODE ==4)
        {
            if (press==0x01)
            {
            	// Generate random position for (x1,y1)
            	Trianglex1 = rand()%240;
            	Triangley1 = rand()%320;
            }
            else if (press==0x02)
            {
            	// Generate random position for (x2,y2)
            	Trianglex2 = rand()%240;
            	Triangley2 = rand()%320;
            }
            else if (press==0x04)
            {
            	// Generate random position for (x3,y3)
            	Trianglex3 = rand()%240;
            	Triangley3 = rand()%320;
            }
        	FrameBuffer_Clear(0);
        	FramBuffer_DrawTriangle(Trianglex1,Triangley1,Trianglex2,Triangley2,Trianglex3,Triangley3,0xFFFF);
        }
        //Draw ASCII 1608 Text
        if (MODE ==5)
        {
        	FrameBuffer_Clear(0);
            if (press==0x01)
            {
            	Textx = rand()%180+20;
            	Texty = rand()%280+20;
            }
            else if (press==0x02)
            {
            	Textnumber = rand()%93+1;
            }
            else if (press==0x04)
            {
            	Textcolour = rand()%31+rand()%63*32+rand()%31*2048;
            }
        	FrameBuffer_DrawText(Textx,Texty,Textnumber,Textcolour);
        }
        // Clear the Pushbutton Interrupt Flag
        KEY_ptr[3] = press;
    }
    HPS_ResetWatchdog();
}

void timerISR(HPSIRQSource interruptID, bool isInit, void* initParams)
{
	// Fresh the LCD
	LT24_copyFrameBuffer(My_Test,0,0,240,320);
	// Clear the Timer Interrupt Flag
    if (!isInit) {
    	Private_timer_ptr[3] |= 0x01;
    }
    HPS_ResetWatchdog();
}

int main(void) {
    signed int audio_sample = 0;
    volatile unsigned char* fifospace_ptr;
    volatile unsigned int*  audio_left_ptr;
    volatile unsigned int*  audio_right_ptr;
    volatile unsigned int * LEDR_ptr = (unsigned int *)0xFF200000;

    //Initialise the LCD Display.
    exitOnFail(
            LT24_initialise(0xFF200060,0xFF200080), //Initialise LCD
            LT24_SUCCESS);                          //Exit if not successful
    HPS_ResetWatchdog();

    //Initialise IRQs
    HPS_IRQ_initialise(NULL);
    HPS_ResetWatchdog();

    // Set Private_timer
    // Set the timer period
    // period = 225/(225 MHz) x (1000000) = 1 sec
    // Refresh Rate = 1Hz
    Private_timer_ptr[0] = 1000000;

    // Write to control register to auto reload and interrupt function
    // Set the prescaler value 224
    Private_timer_ptr[2]   = 0xE007;//Start timer

    KEY_ptr[2] = 0x0F;// Enable interrupts for all four KEYs
    HPS_ResetWatchdog();

    // Register interrupt handler for timerISR
    HPS_IRQ_registerHandler(IRQ_MPCORE_PRIVATE_TIMER, timerISR);
    HPS_ResetWatchdog();

    // Register interrupt handler for keys
    HPS_IRQ_registerHandler(IRQ_LSC_KEYS, pushbuttonISR);
    HPS_ResetWatchdog();

    // Default MODE is 1
    MODE = 1;

    //Initialise the Audio Codec.The DAC initialization code is based on the given example
    exitOnFail(
            WM8731_initialise(0xFF203040),  //Initialise Audio Codec
            WM8731_SUCCESS);                //Exit if not successful
    //Clear both FIFOs
    WM8731_clearFIFO(true,true);
    //Grab the FIFO Space and Audio Channel Pointers
    fifospace_ptr = WM8731_getFIFOSpacePtr();
    audio_left_ptr = WM8731_getLeftFIFOPtr();
    audio_right_ptr = WM8731_getRightFIFOPtr();
    //Initialise Phase Accumulator
    ampl  = 1;

    // Clear the periphals
    DE1SoC_SevenSeg_Clear();
    LEDR_ptr[0] = 0x00;
    FrameBuffer_Clear(0);

    // Display text "FUNC" + MODE number
    DE1SoC_SevenSeg_Write(5,0x71);
    DE1SoC_SevenSeg_Write(4,0x3E);
    DE1SoC_SevenSeg_Write(3,0x54);
    DE1SoC_SevenSeg_Write(2,0x39);
    DE1SoC_SevenSeg_SetDoubleDec(0x00,MODE);

    FrameBuffer_DrawH(100, 0,fontsize, fontcolour);
    FrameBuffer_DrawY(100, 100, fontsize,fontcolour);
    FrameBuffer_DrawH(100, 200,fontsize, fontcolour);

    while(1) {
    	__asm("WFI");
        HPS_ResetWatchdog();
    }
}


