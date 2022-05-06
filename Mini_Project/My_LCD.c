
#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "My_LCD.h"
#include "Test.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_usleep/HPS_usleep.h" //some useful delay routines


signed int My_LT24_copyFrameBuffer(unsigned short* framebuffer, unsigned int xleft, unsigned int ytop, unsigned int width, unsigned int height)
{
	// Baseed on the example code
    unsigned int cnt;
    signed int status = LT24_setWindow(xleft,ytop,width,height);
    if (status != LT24_SUCCESS) return status;
    cnt = (height * width);
    while (cnt--) {
        LT24_write(true, *framebuffer++);
    }
    return LT24_SUCCESS;
}

void Change_FrameBuffer_Pixel(int x, int y, unsigned short colour)
{
	if(x<240&&y<320&&x>0&&y>0)
	{
		My_Test[y*240+x] = colour;
	}

}

void FrameBuffer_Clear(unsigned short colour)
{
	// Change all the Pixels
    int i;
	for(i = 0; i<76800; i++)
	{
		My_Test[i] = colour;
	}
}


void FramBuffer_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short colour)
{
	// Bresenham Algorithm
	int x = x1;
	int y = y1;
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int s1 = x2 > x1 ? 1 : -1;
	int s2 = y2 > y1 ? 1 : -1;
	int p = 2 * dy - dx;
	int i;
	char interchange = 0;
	if (dy > dx)
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = 1;
	}
	for(i = 0; i < dx; i++)
	{
		Change_FrameBuffer_Pixel(x, y, colour);
		if (p >= 0)
		{
			if (!interchange)
				y += s2;
			else
				x += s1;
			p -= 2 * dx;
		}
		if (!interchange)
			x += s1;
		else
			y += s2;
		p += 2 * dy;
	}
}

void FramBuffer_DrawRectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned short colour)
{
	// Draw Vertical Lines
	int i;
	int j;
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w; i++)
			{
				Change_FrameBuffer_Pixel(x+i, y+j, colour);
			}
	}
}



void FramBuffer_DrawSubTriangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned short colour)
{
	// Draw Lines between a corner of a triangle with the pixels on its diagonal.
	int x = x1;
	int y = y1;
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int s1 = x2 > x1 ? 1 : -1;
	int s2 = y2 > y1 ? 1 : -1;
	int p = 2 * dy - dx;
	int i;
	char interchange = 0;
	if (dy > dx)
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = 1;
	}
	for(i = 0; i < dx; i++)
	{
		FramBuffer_DrawLine(x, y, x3, y3, colour);
		if (p >= 0)
		{
			if (!interchange)
				y += s2;
			else
				x += s1;
			p -= 2 * dx;
		}
		if (!interchange)
			x += s1;
		else
			y += s2;
		p += 2 * dy;
	}
}

void FramBuffer_DrawTriangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned short colour)
{
	// Draw all of the corners
	// Draw Lines between a corner of a triangle with the pixels on its diagonal.
	FramBuffer_DrawSubTriangle(x1,y1,x2,y2,x3,y3,colour);
	FramBuffer_DrawSubTriangle(x1,y1,x3,y3,x2,y2,colour);
	FramBuffer_DrawSubTriangle(x3,y3,x2,y2,x1,y1,colour);
}

void FrameBuffer_DrawText(unsigned int x, unsigned int y,unsigned int fontnumber, unsigned short colour)
{
	// The ASCII bitmap of the text is based on (www.qdtech.net)
	int i;
	int j;
	for(i = 0;i<16;i++)
	{
		for(j = 0;j<8;j++)
		{
			if((font1608[fontnumber][i]>>(8-j))&0x01)
			{
				My_Test[(x-j)+(y+i)*240] = colour;
			}

		}
	}
}


void FrameBuffer_DrawH(unsigned int hx, unsigned int hy, unsigned int fontsize, unsigned int fontcolour)
{
	// Draw a vector "H"
	FramBuffer_DrawRectangle(hx+fontsize*15/100,hy+fontsize*5/100,fontsize*0.2,fontsize*0.9,fontcolour);
	FramBuffer_DrawRectangle(hx+fontsize*15/100,hy+fontsize*40/100,fontsize*0.7,fontsize*0.2,fontcolour);
	FramBuffer_DrawRectangle(hx+fontsize*65/100,hy+fontsize*5/100,fontsize*0.2,fontsize*0.9,fontcolour);
}

void FrameBuffer_DrawY(unsigned int yx, unsigned int yy, unsigned int fontsize, unsigned int fontcolour)
{
	// Draw a vector "Y"
	FramBuffer_DrawTriangle(yx+fontsize*5/100,yy+fontsize*10/100,yx+fontsize*25/100,yy+fontsize*10/100,yx+fontsize*40/100,yy+fontsize*60/100,fontcolour);
	FramBuffer_DrawTriangle(yx+fontsize*50/100,yy+fontsize*40/100,yx+fontsize*25/100,yy+fontsize*10/100,yx+fontsize*40/100,yy+fontsize*60/100,fontcolour);
	FramBuffer_DrawTriangle(yx+fontsize*50/100,yy+fontsize*40/100,yx+fontsize*60/100,yy+fontsize*60/100,yx+fontsize*40/100,yy+fontsize*60/100,fontcolour);
	FramBuffer_DrawTriangle(yx+fontsize*50/100,yy+fontsize*40/100,yx+fontsize*60/100,yy+fontsize*60/100,yx+fontsize*75/100,yy+fontsize*10/100,fontcolour);
	FramBuffer_DrawTriangle(yx+fontsize*95/100,yy+fontsize*10/100,yx+fontsize*60/100,yy+fontsize*60/100,yx+fontsize*75/100,yy+fontsize*10/100,fontcolour);
	FramBuffer_DrawRectangle(yx+fontsize*40/100,yy+fontsize*60/100,fontsize*0.2,fontsize*0.55,fontcolour);
}
