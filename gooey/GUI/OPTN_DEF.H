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
	option::option(int a,int b,int w,int _color ,int _checked,char *_text,option **_dummy)
		{
		type=C_OPTION;
		left=y=a;
		top=x=b;
		cwidth=15;
		width=w;
		height=cwidth;
		if(width<cwidth)
			width=cwidth;
		checked=_checked;
		dec=3;
		color=_color;
		border=0;
		strcpy(text,_text);

		if(checked)
			{
			if(*_dummy)
				{
			(*_dummy)->checked = false;
			*_dummy = this;
				}
			
			}
			
		if(*_dummy == NULL) *_dummy = this;
		mygroup=_dummy;



		}

	void option::makechecked(int dr)
		{
		if(*mygroup)
			{
			(*mygroup)->checked = false;
			}
		checked=true;
		*mygroup = this;
		if(dr == DRAW)
			draw();
		}	
	
	void option::initvalby(cwin * w)
		{

	  //adding the title bar
		parent=w;
		x=parent->getx()+left;
		y=parent->gety()+top+title_bar_height;
		}

	void option::draw(int type )
		{
	 mouse.hide();
	 setcolor(0);
	 circle(left+5,top+5,5);
	 circle(left+5,top+5,3);
	 setfillstyle(1,15);
	 floodfill(left+5,top+5,0);
	 setfillstyle(1,8);
	 floodfill(left+1,top+5,0);
	   if(checked)
	   setcolor(0);
	   else
	   setcolor(parent->bgcolor);
	    circle(left+5,top+5,2);
	    circle(left+5,top+5,1);

	 setcolor(color);
		 char _text[50];
		 int twidth=width-cwidth+8;
		 strcpy(_text,text);
		 if(textwidth(text)>twidth)
			{
			 _text[twidth/(textwidth(_text)/strlen(_text)+1)]='\0';
			}
		outtextxy(left+12,top,_text);
	 mouse.show();
	 }



	int option::clicked()
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
		if(*mygroup)
		{
			if(*mygroup!=this)
			(*mygroup)->checked = false;
			(*mygroup)->draw(1);
			(*mygroup) = this;
		}
			if(!checked && mygroup != NULL)
			checked=!checked;
			else if(mygroup == NULL)
			checked=!checked;

		retcode=parent->handle_event_onclick(this);
		draw();
		return retcode;
		}

