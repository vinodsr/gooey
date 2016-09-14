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
 /*
   Name:  qdriver.h
   Date: 04/08/05 17:15
   Description: for implmenting graphics driver class
 */
#define screenfile "gdscr"
int huge detectEGA(void);  

static class _gdriver
	{
	protected:
	int gd,gm;
	char dir[50];

	int palette[15][3];

	public:

	int  screen_index;
	char screens[20][15];
	int maxx,maxy;
	int l_shade;
	int u_shade;
	int sel_border,sel_bgcolor;
	usepalette()
		{
	struct palettetype pal;
	getpalette(&pal);
	setrgbpalette(pal.colors[1], 8, 17, 27);
	setrgbpalette(pal.colors[3],4, 4, 37);
	setrgbpalette(pal.colors[5], 53, 51, 49);
	setrgbpalette(pal.colors[6], 63, 36, 10);
	setrgbpalette(pal.colors[9], 33, 31, 28);
	setrgbpalette(pal.colors[10],17,57, 15);
	setrgbpalette(pal.colors[11], 16, 15, 26);
	setrgbpalette(pal.colors[14], 54, 40, 15);
		return 1;
		}
	_gdriver()
		{
		screen_index=-1;
		l_shade=0;
		u_shade=7;
		sel_border=14;
		sel_bgcolor=2;
		}
	setdir(char d[50])
		{
		strcpy(dir,d);
		return 1;
		}

	void unload()
		{

		   restorecrtmode();
		   closegraph();
		   resume_dog();
		   dog(" : Greetings ! terminator called ); ");
		   close_dog();
		   if(DEBUG_ON)
		   cout<<" : Greetings ! terminator called ); ";
		}


	void init()
		{

		gd=DETECT;
        installuserdriver("EGAVGA",detectEGA);
		initgraph(&gd,&gm,"");
		maxx=getmaxx();
		maxy=getmaxy();
	    }

	void killscreen() {
		remove(screens[screen_index]);
		screen_index --;
		}
		
	//Function declarations ;
	int savescreen();
	int savescreen(int ,int,int ,int);
	int savescreen_up(int ,int,int ,int);
	int savescreen(int ,int,int ,int,char *);
	int restorescreen();
	int restorescreen(int x1,int y1,int x2,int y2,int nokill=0,int op = COPY_PUT);
	int restorescreen_up(int x1,int y1,int x2,int y2,int nokill=0,int op = COPY_PUT);
	int restorescreen(int x1,int y1,int x2,int y2,char * fname,int op = COPY_PUT);
	void draw_3dbar_inv(int bx,int by,int wd,int ht,int color,int border,int t=0,int dec=3);
	void draw_3dbar(int bx,int by,int wd,int ht,int color,int border,int t=0,int dec=2,int style=1,int clear_type =1);
	void draw_bar(int bx,int by,int wd,int ht,int color,int border);
	}gdriver;

