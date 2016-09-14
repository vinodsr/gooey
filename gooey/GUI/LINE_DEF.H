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
Line::Line(int a,int b,int c,int d,int _color,int dl)
		{
		type = C_LINE;
		x1=y=a;
		y1=x=b;
		x2=c;
		y2=d;
		color=_color;
		left=x1;
		top=y1;
		width=height=0;
		dline =dl;
		}

void Line::draw(int type)
		{
			mouse.hide();
			setcolor(color);
			line(x1,y1,x2,y2);
			if(dline)   //double line
				{
				setcolor(15);
				line(x1+1,y1+1,x2+1,y2+1);
				}
			mouse.show();
		}

void Line::initvalby(cwin * w)
		{
		parent=w;
		x=parent->getx()+left;
		y=parent->gety()+top+15;  //adding the title bar
		}

	
