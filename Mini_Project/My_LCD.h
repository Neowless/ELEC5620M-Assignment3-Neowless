

#ifndef MY_LCD
#define MY_LCD

//Include required header files
#include <stdbool.h> //Boolean variable type "bool" and "true"/"false" constants.

signed int My_LT24_copyFrameBuffer(unsigned short* framebuffer, unsigned int xleft, unsigned int ytop, unsigned int width, unsigned int height);

//Change a single Pixel in the LCD buffer
void Change_FrameBuffer_Pixel(int x, int y, unsigned short colour);

// Chaneg the LCD buffer to a certain value
void FrameBuffer_Clear(unsigned short colour);

// Draw a Line
void FramBuffer_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short colour);

// Draw a Rectangle
void FramBuffer_DrawRectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned short colour);

// Draw a ASCII text
void FrameBuffer_DrawText(unsigned int x, unsigned int y,unsigned int fontnumber, unsigned short colour);

// Draw a Triangle
void FramBuffer_DrawTriangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned short colour);
void FramBuffer_SubDrawTriangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned short colour);

// Draw a Vector Text
void FrameBuffer_DrawH(unsigned int hx, unsigned int hy, unsigned int fontsize, unsigned int fontcolour);
void FrameBuffer_DrawY(unsigned int yx, unsigned int yy, unsigned int fontsize, unsigned int fontcolour);

#endif /*DE1SoC_LT24_H_*/
