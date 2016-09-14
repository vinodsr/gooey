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
	checkbox::checkbox(int a,int b,int w,int _color ,int _checked,char *_text)
		{
		type = C_CBOX;
		checkbox();
		left=y=a;
		top=x=b;
		cwidth=15;
		width=w;
		height=cwidth;
		if(width<cwidth)  	width=cwidth;  //setting minimal width
		checked=_checked;
		dec=3;
		color=_color;
		border=0;
		strcpy(text,_text);
		}

	 void checkbox::draw(int type)	{
		gdriver.draw_3dbar_inv(left,top,cwidth,cwidth,15,0,type,2);
		  setcolor(color);
		 char _text[50];
		 int twidth=width-cwidth;
		 strcpy(_text,text);
		 if(textwidth(text)>twidth)
			{
			 _text[twidth/(textwidth(_text)/strlen(_text)+1)]='\0';
			}
		 mouse.hide();
		 if(checked)
		 outtextxy(left+5,top+5,"X");
		 settextjustify(LEFT_TEXT,TOP_TEXT);
		 setcolor(color);
		 outtextxy(left+cwidth+2,top+cwidth/2-1,_text);
		 settextjustify(LEFT_TEXT,TOP_TEXT);
		 mouse.show();
		}

		int checkbox::interupt(_mouse m)	{
		if(m.btn & 1)
			{
			retcode=clicked();
			}
		return retcode;
		}

	void checkbox::initvalby(cwin * w)
		{
		parent=w;
		x=parent->getx()+left;
		y=parent->gety()+top+title_bar_height;
		}
		
	int checkbox::clicked()
		{
		draw();
		while(mouse.isclicked(1));
		point p(mouse.x,mouse.y);
		region r(x,y,x+width,y+height);
		if(!r.contains(p))
		      {
		       draw();
		       return OK;
		      }
		checked=!checked; 
		retcode=parent->handle_event_onclick(this);
		draw();
		return retcode;
		}
