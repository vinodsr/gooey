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
label::label(int a,int b,int c,int d,char *txt,int _color,int bcolor,int bor)
		{
		label();
		border = bor;
		centered = false;
		left=y=a;
		top=x=b;
		width=c;
		bgcolor =bcolor;

		if(d <20)
		height = 20;
		else
		height=d;


		dec=0;
		strcpy(text,txt);
		color=_color;
		}


void label::setval(char * _text,int _draw)
		{
		strcpy(text,_text);
		value=atoi(text);
		if(_draw)
		draw(1);
		}
		
void label::setval(int _value,int _draw)
		{
		value=_value;
		itoa(value,text,10);
		if(_draw)
		draw(1);
		}



void label::initvalby(cwin * w)
		{
		parent=w;
		x=parent->getx()+left;
		y=parent->gety()+top+15;  //adding the title bar
	
		if(bgcolor ==-1)
			bgcolor= parent->bgcolor;
		}

void label::draw(int type)
		{

		if(bgcolor != -1 && border) 
	       gdriver.draw_bar(left,top,width,height,bgcolor,0);
	    else if(bgcolor != -1) 
	       gdriver.draw_bar(left,top,width,height,bgcolor,bgcolor);
	    else if(border)
	    	{
	    	setlinestyle(1,1,1);
	    	setcolor(color);
	    	rectangle(left,top,width+left,height+top);
	    	setlinestyle(0,1,1);
	    	}
      
	        char *_text;
	        int lines = height / 20;
	        int y_inc =lines/2;
	        int index=-1;
	        _text = new char[256];
		
		
		 mouse.hide();
		 settextjustify(LEFT_TEXT,TOP_TEXT);
		 setcolor(color);
		 while(lines)
		 {
				 for(int i=0 ;i<(width /8) -1;)
			 	{
			 	index ++;
			 	if(text[index] == '\0')
			 		break;
			 	
			 	_text[i]=text[index];
				i++;		
			 	}
			 
			 	_text[i]='\0';
			 
			if(centered)
		 	outtextxy(left+width/2-((i/2)*8),top+height/2-(y_inc*10)-3,_text);
		 	else
		 	outtextxy(left+5,top+height/2-(y_inc*10)-3,_text);
		 lines --;
		 y_inc--;
		 }
		 settextjustify(LEFT_TEXT,TOP_TEXT);
		 delete _text;
	    mouse.show();
		}



