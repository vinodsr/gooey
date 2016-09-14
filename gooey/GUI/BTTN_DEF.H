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
	button::button(int a,int b,int c ,int d,char *_label,int bcolor,int col)
		{
		button();
		left=y=a;
		top=x=b;
		width=c;
		height=d;
		bgcolor=bcolor;
		color=col;
		dec=3;
		disabled = false;
		visible =true;
		strcpy(label,_label);
		}

	void button::setvalue(char *_t)
		{
		strcpy(label,_t);
		draw(1);
			}
	void button::draw(int type)	{

	if(visible)
	{
	if(!disabled)
		 gdriver.draw_3dbar(left,top,width,height,bgcolor,bgcolor,type,dec,1,2);
	else
		 gdriver.draw_3dbar(left,top,width,height,bgcolor,bgcolor,type,dec,1,2);
	     char *_text;
	     int lines = height / 20;
	     int y_inc =lines/2;
	     int index=-1;
	     _text = new char[256];
		 mouse.hide();
		 settextjustify(LEFT_TEXT,TOP_TEXT);
		if(disabled)
		setcolor(7);
		else
		setcolor(color);
		
		while(lines)
		 {
			 for(int i=0 ;i<(width /8);i++)
				{
				index++;
			 	_text[i]=label[index];
			 	if(label[index] == '\0')
			 		break;
				}
			 	_text[i]='\0';
	  	outtextxy((left+width/2)-(((i)/2)*8),top+height/2-(y_inc*10)-3,_text);
		 lines --;
		 y_inc--;
		 }
		 settextjustify(LEFT_TEXT,TOP_TEXT);
		 delete _text;
	    mouse.show();
	    }
	}

	 int button::interupt(_mouse m)	{
		if(m.btn & 1 && !disabled)	{
			return clicked();
			}
		}


	void button::initvalby(cwin * w)
		{
		parent=w;
		x=parent->getx()+left;
		y=parent->gety()+top+title_bar_height;
		}

	int button::clicked()
		{
		draw(2);
	    while(mouse.isclicked(1));
		point p(mouse.x,mouse.y);
		region r(x,y,x+width,y+height);
		if(!r.contains(p))
		      {
		       draw(1);
		       return OK;
		      }
		retcode=parent->handle_event_onclick(this);
		draw(1);
		// delay the process
	       delay(100);
		return retcode;
		}
