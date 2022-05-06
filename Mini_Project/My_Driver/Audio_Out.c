/*
 * Audio_Out.c
 *
 *  Created on: Mar 31, 2022
 *      Author: Neowless
 */

#include "Syphony.h"
#include "../global.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "DE1SoC_WM8731/DE1SoC_WM8731.h"
#include "../My_LCD.h"
#include "Audio_Out.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_IRQ/HPS_IRQ.h"
#include "HPS_usleep/HPS_usleep.h"
#include "../DE1SoC_SevenSeg/DE1SoC_SevenSeg.h"
#include "XYSheldon.h"



void Audio_Out()
{
	// The DAC initialization code is based on the given example
    volatile unsigned char* fifospace_ptr;
    volatile unsigned int*  audio_left_ptr;
    volatile unsigned int*  audio_right_ptr;
    signed int audio_sample = 0;
    exitOnFail(
            WM8731_initialise(0xFF203040),
            WM8731_SUCCESS);
    WM8731_clearFIFO(true,true);
    fifospace_ptr = WM8731_getFIFOSpacePtr();
    audio_left_ptr = WM8731_getLeftFIFOPtr();
    audio_right_ptr = WM8731_getRightFIFOPtr();


    // Display the Album Picture
    exitOnFail(
            LT24_copyFrameBuffer(XYSheldon,0,0,240,320),
            LT24_SUCCESS);

    ampl  = 2;
    counter =0;
    while (MODE==6) {
        if ((fifospace_ptr[2] > 0) && (fifospace_ptr[3] > 0))
        {
            audio_sample = ampl*Syphony[counter];
            // This song's name is ¡°Huan Le Dou Di Zhu(Symphony)" created by XYSheldon. (https://music.163.com/#/song?id=424495239)
            // This song is authorized by XYSheldon for Yuheng Huo to use this song in ELEC5620M Mini Project.
            // The float number is generated form the lossless .wav file via  MATLAB
            *audio_left_ptr = audio_sample;
            *audio_right_ptr = audio_sample;
            counter++;
            if(counter==1571968)
            {
            	counter=0;
            	MODE = MODE+1;
            }
        }
        HPS_ResetWatchdog();
    }
}
