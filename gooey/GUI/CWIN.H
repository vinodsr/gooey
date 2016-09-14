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
   Name:  cwin.h
   Date: 31/07/05 09:56
   Description: class for window ...
 */
 #define BACK 00
 #define FRONT 11
 #include "./gui/pre_hed.h"   //Pre - header
 class cwin:public object
	{
	private :
		int id;
	public:
		int dec;
		int status;
		int width,height;
		int bgcolor,forecolor;
		int fontsize,fontstyle;
		char title[25];
		stack <control *> control_list;
		stack <control *> control_list_back;
		char *screen;

	//methods for cwin
	public:
		~cwin()
		 {  kill(); }
		cwin();
		void paint(int t);
		int interupt(_mouse m);    // calling with  viewport
		int getx() { return x; }
		int gety() { return y; }
		int getwidth() { return width; }
		int getheight() { return height; }
		void setid(int i) { id =i; }
		int getid() {return id; }
		void killme();
		void attach(control *ctrl,int list=FRONT);
		int run();
		//virtual classes for event handling
		virtual int handle_event_onclick(object *) { }
		virtual int handle_onload() { }
		virtual int handle_onclose() { }
		virtual int kill();
	}; // End of cwin class



