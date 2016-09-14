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

	void textbox::setval(char * _text,int dr)
		{
		strcpy(text,_text);
		value=atoi(text);
		if(dr == DRAW)
			draw();
		}
	void textbox::setval(int _value,int dr)
		{
		value=_value;
		itoa(value,text,10);
			if(dr == DRAW)
				draw();
		}
	textbox::textbox(int a,int b,int c,int d,char _text[128])
		{
		textbox();
		left=y=a;
		top=x=b;
		width=c;

		if(d < 20)
		height =20;
		else
		height=d;

		dec=2;
		color=0;
		bgcolor=15;
		strcpy(text,_text);
		value=atoi(text);
		}

	void textbox::draw(int type)
		{

		 mouse.hide();
		 gdriver.draw_3dbar_inv(left,top,width,height,bgcolor,bgcolor,type,dec);
		 setcolor(color);
		 char _text[50];
		 strcpy(_text,text);
		 if(textwidth(text)>width-8)
			{
		 _text[width/(textwidth(_text)/strlen(_text)+1)]='\0';
			}
		 settextjustify(LEFT_TEXT,TOP_TEXT);
		  outtextxy(left+dec+5,top+5,_text);
		 settextjustify(LEFT_TEXT,TOP_TEXT);
		 mouse.show();
		}

	int textbox::clicked()
		{
		char ch;
		mouse.hide();
		gdriver.draw_3dbar_inv(left,top,width,height,10,10,1,dec);
		setcolor(0);
		char *_text,*temp;
		_text=new char[256];
		temp = new char[256];

		strcpy(temp,text);
		strcpy(text,"");
		text[0] = char(9);
		text[1] = '\0';
		outtextxy(left+dec+5,top+5,text);

		int index=0;
		int noc=(width/8) -1;
		while( (noc!=0) && (ch=getch()) !=13 )
			{
			if(ch != 8 ) //not a backspace
				{
				if(ch == 27)
					{
				       strcpy(text,temp);
				       break;
				       //	continue;
					}
				else{

				*(_text+index)=ch;
				index++;
				--noc;
				     }
				}

			else       // backspace
				{
				if(index)   // if no char
							{
								noc++;
								index--;
							}
				else
					{
					sound(650);
					delay(500);
					nosound();
					}

				}

			*(_text+index)='\0';
			strcpy(text,_text);
			if(noc  !=0)
			{
			text[index]=char(9);
			text[index+1]='\0';
			}
			gdriver.draw_3dbar_inv(left,top,width,height,10,10,1,dec);
			setcolor(color);
			outtextxy(left+dec+5,top+5,text);
			}

		if(text[index] == char(9))
			text[index] = '\0';
		gdriver.draw_3dbar_inv(left,top,width,height,bgcolor,bgcolor,1,dec);
		setcolor(color);
		outtextxy(left+dec+5,top+5,text);
		value=atoi(text);
		delete _text;
		delete temp;
		mouse.show();
		return parent->handle_event_onclick(this);;
		}


	void textbox::initvalby(cwin * w)
		{
		parent=w;
		x=parent->getx()+left;
		y=parent->gety()+top+15;  //adding the title bar
		}


