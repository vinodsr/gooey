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
#include "./gui/header.h"
#include <alloc.h>
 #include "./gui/def.h"
#include "./gui/point.h"
#include "./gui/region.h"
#include "./gui/mouse.h"
#include "./gui/heap.h"
#include "./gui/dog.h"
#include "./gui/gdriver.h"
#include "interfac.h"

#include "toolbox.h"
void place_on_form(int,point);

void _toolbox::setval(int a,int b,int c,int d,int col,int bor)
{
toolbox_screen=NULL;
x=a;
enabled=0;
y=b;
wd=c;
ht=d;
color=col;
border=bor;

}
void _toolbox::enablethis()
	{
	enabled =1 ;

	if(toolbox_screen != NULL)
	{
	farfree(toolbox_screen);
	}
	create_toolbox();

	save_toolbox();

	}
void _toolbox::disablethis()
	{
	enabled=0;
	if(toolbox_screen != NULL)
	farfree(toolbox_screen);

	create_toolbox();
	save_toolbox();

	}

void _toolbox::create_toolbox()
	{
	int b_color=color;
	if(enabled == 0)
		b_color=7;

	 int newy=y+20;  // considering the  titlebar
	 gdriver.draw_bar(x,y,wd,20,1,15);
	 gdriver.draw_3dbar(x,y+20,wd,ht,b_color,border,1,2);
	 mouse.hide();
	 setcolor(15);
	 outtextxy(x+5,y+10,"ToolBox");

	 // Create button
	 newy+=15;
	 gdriver.draw_3dbar(x+5,newy+5,wd-10,20,7,0,1,2);
	 setcolor(0);
	 outtextxy(x+10,newy+10,"Button");

	 // Create label
	 newy+=30;

	 setlinestyle(0,1,1);
	 setcolor(0);
	 rectangle(x+5,newy+8,wd,newy+23);
	 setcolor(0);
	 outtextxy(x+10,newy+13,"Label");
	 setlinestyle(0,1,1);
	 // Create textbox
	 newy+=30;
	 gdriver.draw_3dbar(x+5,newy+5,wd-10,20,15,0,2,3);
	 setcolor(0);
	 outtextxy(x+10,newy+10,"Textbox");

	 // Create checkbox
	 newy+=30;
	 gdriver.draw_3dbar(x+5,newy+5,15,15,15,0,2,2);
	 setcolor(0);
	 outtextxy(x+10,newy+10,"X");
	  setcolor(0);
	 rectangle(x+22,newy+6,x+72,newy+20);
	 setcolor(0);
	 outtextxy(x+25,newy+9,"Check");

	 // Create Radio
	 newy+=30;
	 setcolor(0);
	 circle(x+10,newy+15,5);
	 circle(x+10,newy+15,3);
	 setfillstyle(1,15);
	 floodfill(x+10,newy+15,0);
	 setfillstyle(1,8);
	 floodfill(x+6,newy+15,0);
	 circle(x+10,newy+15,1);
	 setcolor(0);
	 rectangle(x+20,newy+10,x+72,newy+22);
	 setcolor(0);
	 outtextxy(x+23,newy+12,"Option");

	  // Create Frame

	 newy+=30;
	 gdriver.draw_bar(x+5,newy+5,wd-48,20,7,0);
	 setcolor(0);
	 outtextxy(x+35,newy+15,"Frame");

	   // Create Line

	 newy+=30;

	 line(x+5,newy+5,x+wd-45,newy+25);
	 setcolor(0);
	 outtextxy(x+33,newy+20,"Line");

	 mouse.show();
	}
void _toolbox::save_toolbox()
	{
	int size;
	size=imagesize(x,y,x+wd,y+ht+20);
	toolbox_screen=(char far  *)farmalloc(size);
		if(toolbox_screen == NULL)
			{
			dog("Error :Allocating Space :: toolbox.h");
			cout << "Error :Allocating Space ::toolbox.h";
			exit(0);
			}
	mouse.hide();
	getimage(x,y,x+wd,y+ht+20,toolbox_screen);
	mouse.show();
	}
void _toolbox::restore_toolbox()
	{
	mouse.hide();
	putimage(x,y,toolbox_screen,COPY_PUT);
	mouse.show();
	}


void _toolbox::clicked()
	{
	 if(enabled)
	 {
		mouse.getresponse();
		if(mouse.btn &1)
			{

			point p(mouse.x,mouse.y);
			int newy=y+35;
			region widget;
			int item=1;
		while(newy<y+ht)
				{
			widget.setval(x,newy,x+wd,newy+30);

			if(widget.contains(p))
					{
					make_hover(x,newy,x+wd,newy+30);
					set_status(" Click the Mouse on the Design Form ... ");
					place_on_form(item,p);

					set_status(" ");
					restore_toolbox();
					break;
				}
					item++;
					newy+=30;
			}
		}
		}


	}

void _toolbox::make_hover(int hx1,int hy1,int hx2,int hy2)
		{

		mouse.hide();
		setcolor(0);
		rectangle(hx1,hy1,hx2,hy2);
		setfillstyle(1,9);
		floodfill(hx1+1,hy1+1,0);
		mouse.show();

		}
void _toolbox::kill()
	{
	if(toolbox_screen != NULL)
	farfree(toolbox_screen);
	}
