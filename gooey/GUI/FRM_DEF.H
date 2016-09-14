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
frame::frame(int a,int b,int c ,int d,char *_label,int col,int bgcol,int bor)
		{
		frame();
		left=y=a;
		top=x=b;
		width=c;
		height=d;
		dec=3;
		bgcolor=bgcol;
		color=col;
		border=bor;
		strcpy(label,_label);
		}
void frame::draw(int type)
		{

		 gdriver.draw_bar(left,top,width,height,bgcolor,border);
		 char _label[50];
		 strcpy(_label,label);
		 if(textwidth(label)>width)
			{
			 _label[width/(textwidth(_label)/strlen(_label)+1)]='\0';
			}
		 mouse.hide();

		 settextjustify(LEFT_TEXT,TOP_TEXT);
		 gdriver.draw_bar(left+5,top-dec,textwidth(_label),textheight(_label),border,border);
		 setcolor(color);
		 outtextxy(left+5,top-dec,_label);
		 settextjustify(LEFT_TEXT,TOP_TEXT);
		 mouse.show();
		}

void frame::initvalby(cwin * w)
		{

	  //adding the title bar
		parent=w;
		x=parent->getx()+left;
		y=parent->gety()+top+title_bar_height;
		}


	
