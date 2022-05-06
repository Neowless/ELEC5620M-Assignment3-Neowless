/*
 * DE1SoC_SevenSeg.c
 *
 *  Created on: 12 Feb 2021
 *      Author: Harry Clegg
 *      		You!
 */

#include "DE1SoC_SevenSeg.h"

// ToDo: Add the base addresses of the seven segment display peripherals.

volatile unsigned char *sevenseg_base_lo_ptr = (unsigned char *)0xFF200020;
volatile unsigned char *sevenseg_base_hi_ptr = (unsigned char *)0xFF200030;


// There are four HEX displays attached to the low (first) address.
#define SEVENSEG_N_DISPLAYS_LO 4

// There are two HEX displays attached to the high (second) address.
#define SEVENSEG_N_DISPLAYS_HI 2

void DE1SoC_SevenSeg_Write(unsigned int display, unsigned char value) {
    // Select between the two addresses so that the higher level functions
    // have a seamless interface.
    if (display < SEVENSEG_N_DISPLAYS_LO) {
        // If we are targeting a low address, use byte addressing to access
        // directly.
        sevenseg_base_lo_ptr[display] = value;
    } else {
        // If we are targeting a high address, shift down so byte addressing
        // works.
        display = display - SEVENSEG_N_DISPLAYS_LO;
        sevenseg_base_hi_ptr[display] = value;
    }
}

void DE1SoC_SevenSeg_Clear() {
    // Select between the two addresses so that the higher level functions
    // have a seamless interface.
	int i;
	for (i=0;i<6;i++)
	{
		DE1SoC_SevenSeg_Write(i,0);
	}

}

void DE1SoC_SevenSeg_SetSingle(unsigned int display, unsigned int value) {
    // ToDo: Write the code for driving a single seven segment display here.
    // Your function should turn a real value 0-F into the correctly encoded
    // bits to enable the correct segments on the seven segment display to
    // illuminate. Use the DE1SoC_SevenSeg_Write function you created earlier
    // to set the bits of the display.

	// Mapping_Table array defines the layout of the 7-Segment displays
	//including 0-9 and A-F, which is a mapping or translation between the
	//hex or decimal input and the actual output bit connected to the 7 segment
	//displays.

	// Table for 7 segment displays with common Anode.
	char Mapping_Table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
	// Table for 7 segment display with common Cathode.
	//char Mapping_Table[]={0x79,0x5E,120,0x4F,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};

	//Call the lower function to display the value.
	DE1SoC_SevenSeg_Write(display, Mapping_Table[value]);
}

void DE1SoC_SevenSeg_SetDoubleHex(unsigned int display, unsigned int value) {
    // ToDo: Write the code for setting a pair of seven segment displays
    // here. Good coding practice suggests your solution should call
    // DE1SoC_SevenSeg_SetSingle() twice.
    // This function should show the first digit of a HEXADECIMAL number on
    // the specified 'display', and the second digit on the display to
    // the left of the specified display.

    /** Some examples:
     *
     *    input | output | HEX(N+1) | HEX(N)
     *    ----- | ------ | -------- | ------
     *        5 |     05 |        0 |      5
     *       30 |     1E |        1 |      E
     *     0x60 |     60 |        6 |      0
     */


	// Set the value in the first segment
	// The "&" operation is applied to clear other irrelevant bits
	DE1SoC_SevenSeg_SetSingle(display, value&0x0F);

	// Set the value in the second segment
	// The ">>" operation is applied to move the higher hexadecimal number to the lower position.
	// Each hexadecimal number includes 4 binary bits.
	DE1SoC_SevenSeg_SetSingle(display+1,(value&0xF0)>>4);
}

void DE1SoC_SevenSeg_SetDoubleDec(unsigned int display, unsigned int value) {
    // ToDo: Write the code for setting a pair of seven segment displays
    // here. Good coding practice suggests your solution should call
    // DE1SoC_SevenSeg_SetSingle() twice.
    // This function should show the first digit of a DECIMAL number on
    // the specified 'display', and the second digit on the display to
    // the left of the specified display.

    /** Some examples:
     *
     *	  input | output | HEX(N+1) | HEX(N)
     *    ----- | ------ | -------- | ------
     *        5 |     05 |        0 |      5
     *       30 |     30 |        3 |      0
     *     0x90 |     96 |        9 |      6
     */


	// The "%" operation is applied to calculate the remainder in the ones place.
	DE1SoC_SevenSeg_SetSingle(display, value%10);

	// The result of "/" operation between integers in C language only keeps the integer part.
	DE1SoC_SevenSeg_SetSingle(display+1,value/10);
}


void DE1SoC_SevenSeg_SetHexTimeDec(unsigned int time)
{
	// The time is in decimal, define the variables.
	unsigned int ff;
	unsigned int ss;
	unsigned int mm;
	unsigned int hh;

	// If time is more or equals than 100 hours, 99:59:99 will be displayed
	if(time > 35999999)
	{
		time = 35999999;
	}
	// Calculate the corresponding values in the display.
	ff = time%100;
	ss = time%6000/100;
	mm = time%360000/6000;
	hh = time/360000;

	//Different display modes.
	if(hh)
	{
		DE1SoC_SevenSeg_SetDoubleDec(0x04,hh);
		DE1SoC_SevenSeg_SetDoubleDec(0x02,mm);
		DE1SoC_SevenSeg_SetDoubleDec(0x00,ss);
	}
	else
	{
		DE1SoC_SevenSeg_SetDoubleDec(0x04,mm);
		DE1SoC_SevenSeg_SetDoubleDec(0x02,ss);
		DE1SoC_SevenSeg_SetDoubleDec(0x00,ff);
	}


}
