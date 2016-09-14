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
   Name:  label.h
   Date: 25/08/05 8:15p
   Description: class for label ...
 */
  class label:public control
	{
	protected:
	int dec;

	public:
	int retcode;
	int color;
	int bgcolor;
	int centered;
	int border;
	char text[256];
	int value;
	label() { type =C_LABEL;}
	void initvalby(cwin *);
	void draw(int t=1);

	label(int a,int b,int c,int d=20,char *txt=" Label ",int _color=0,int bcolor=-1,int bor=0);
	void setval(char * _text,int _draw=0);
	void setval(int _value,int _draw);


	int clicked()
		{

		}

	int interupt(_mouse m)
		{

		return NO_INTR;
		}
	}; //end of class
