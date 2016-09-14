/*
  Author: Vinod S.R
  Date: 30/06/07 12:10
*/
//  ------------------------------------------------------------------------ //
//                Gooey "see"pp - The ultimate GUI Toolkit                      //
//                    Copyright (c) 2007 tenthstone                            //
//                       <http://www.tenthstone.com/gui/>                             //
//  ------------------------------------------------------------------------ //
//  This program is free software; you can redistribute it and/or modify     //
//  it under the terms of the GNU General Public License as published by     //
//  the Free Software Foundation; either version 2 of the License, or        //
//  (at your option) any later version.                                      //
//                                                                           //
//  You may not change or alter any portion of this comment or credits       //
//  of supporting developers from this source code or any supporting         //
//  source code which is considered copyrighted (c) material of the          //
//  original comment or credit authors.                                      //
//                                                                           //
//  This program is distributed in the hope that it will be useful,          //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of           //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
//  GNU General Public License for more details.                             //
//                                                                           //
//  You should have received a copy of the GNU General Public License        //
//  along with this program; if not, write to the Free Software              //
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA //
//  ------------------------------------------------------------------------ //
#define RGB_RESET 0x03C6
#define RGB_READ 0x03C7
#define RGB_WRITE 0x03C8
#define RGB_DATA 0x03C9
#include <dir.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <process.h>
#include <graphics.h>
#include <dos.h>
#include <iostream.h>
#include <stdlib.h>

typedef struct tagBITMAPFILEHEADER
 {
  unsigned int  bfType;
  unsigned long bfSize;
  unsigned int  bfReserved1;
  unsigned int  bfReserved2;
  unsigned long bfOffBits;
 } BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
 {
  unsigned long biSize;
  unsigned long biWidth;
  unsigned long biHeight;
  unsigned int  biPlanes;
  unsigned int  biBitCount;
  unsigned long biCompression;
  unsigned long biSizeImage;
  unsigned long biXPelsPerMeter;
  unsigned long biYPelsPerMeter;
  unsigned long biClrUsed;
  unsigned long biClrImportant;
 } BITMAPINFOHEADER;

typedef struct tagRGBQUAD
 {
  unsigned char rgbBlue;
  unsigned char rgbGreen;
  unsigned char rgbRed;
  unsigned char rgbReserved;
 } RGBQUAD;

FILE             *ptr;
BITMAPFILEHEADER bmfh;
BITMAPINFOHEADER bmih;
RGBQUAD          rgbq[256];
char files[100][14];
int height;

void putPixel(int& i, int& j, char tmp2, int flag)  // draws a pixel in
 {                                                  // correct color from
  putpixel(j, i, tmp2 + 1 - flag);                  // color table at
  j++;                                              // desired location
  if (j == (getmaxx() + bmih.biWidth) / 2)          // on screen.
   {
    j = (getmaxx() - bmih.biWidth) / 2;
    i--;
    height++;
    switch(bmih.biBitCount)  // so that new line is aligned at long word boundary.
     {
      case 8 : if ((bmih.biWidth % 4) != 0)      // for 8-bit BMP.
		for (int k = 4; k > (bmih.biWidth % 4); k--)
		 getc(ptr);
	       break;
      case 4 : if (((bmih.biWidth / 2) % 4) != 0)        // for 4-bit BMP.
		for (int k = 4; k > ((bmih.biWidth / 2) % 4); k--)
		 getc(ptr);
	       break;
     }
   }
 }



int huge DetectVGA256()
 {
  int Vid = 1;
  return Vid;
 }

void setPalette(int index, int red, int green, int blue)
 {
  outp(RGB_RESET, 0xFF);     //Prepare the VGA card for the color change
  outp(RGB_WRITE, index);    //Tell which palette register to write to
  outp(RGB_DATA, red);       //change the red value
  outp(RGB_DATA, green);     //change the green value
  outp(RGB_DATA, blue);      //change the blue value
 }

void ShowInitScreen()
//void main()
 {
  FILE *p;
  unsigned char tmp1, tmp2;
  int i, j, k, flag, no_files;          // flag checks if color table is of max. size.
  char filename[14], ch;
  char *path, drive[2], dir[100], file[10], ext[4];
  path = searchpath("svga256.bgi");
  fnsplit(path, drive, dir, file, ext);
  getcwd(path, 100);

  ptr = fopen("load.pix", "rb");
  flag = 0;

  fread(&bmfh, sizeof(bmfh), 1, ptr);  // read bitmap file header.
  fread(&bmih, sizeof(bmih), 1, ptr);  // read bitmap information header.


  if (bmih.biClrUsed == 0) bmih.biClrUsed = pow(2, bmih.biBitCount);
  if (bmih.biClrUsed > 254) flag = 1;



 rgbq[0].rgbRed = rgbq[0].rgbBlue = rgbq[0].rgbGreen = 0;  // set first entry in palette to black for black background.
  for (i = 1 - flag; i < bmih.biClrUsed + 1 - flag; i++)    // storing the color table.
   {
    rgbq[i].rgbBlue = getc(ptr);
    rgbq[i].rgbGreen = getc(ptr);
    rgbq[i].rgbRed = getc(ptr);
    tmp1 = getc(ptr);
   }
  for (i = bmih.biClrUsed + 1 - flag; i < 255 + flag; i++)    // initialising unused entries.
   rgbq[i].rgbRed = rgbq[i].rgbBlue = rgbq[i].rgbGreen = 0;
  if (!flag) rgbq[255].rgbRed = rgbq[255].rgbBlue = rgbq[255].rgbGreen = 255; // set last entry in palette to white for white foreground.
  int gd = DETECT, gm;               // enter graphics mode to display image.
  installuserdriver("Svga256", DetectVGA256);


  initgraph(&gd, &gm, "");
  outtextxy(1, 1, "Please wait while image loads...");
   for (i = 0; i < 256; i++)
   {
   setPalette(i, rgbq[i].rgbRed / 4, rgbq[i].rgbGreen / 4, rgbq[i].rgbBlue / 4);
 
   }

  clearviewport();

  i = (getmaxy() + bmih.biHeight) / 2;        // start display of image.
  j =(getmaxx() - bmih.biWidth) / 2;
  height = 0;                           // height keeps track of how many lines have been drawn.
  while (!feof(ptr))
   {
    tmp1 = getc(ptr);               // read character from file.
    putPixel(i, j, tmp1, flag);
   }
finish :

  fclose(ptr);
  // Showing messages ...
  int step=6; //6
  char messages[][40] ={ " Preparing to start ...",
  						 " Loading Environment ...",
  						 " Loading palette ...",
  						 " Loading toolbox ..",
  						 " Loading C-FC ... ",

						 " Finished loading .. Going to start "};
  settextstyle(0,0,0);
  setcolor(0);
  rectangle(174,349,476,361);
  for(i=0;i<step;i++)
		{
		setfillstyle(1,getpixel(1,365));
		bar(175,365,476,380);
		outtextxy(175,370,messages[i]);
	for(j=0;j<50;j++)
			{

			setfillstyle(1,getpixel(150,240));
			bar(175,350,175+(i*50)+j,360);
			delay(50 - (j-(i*2)));
			}
		}
  closegraph();
 }
