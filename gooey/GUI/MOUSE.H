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
   Name:  mouse.h
   Date: 31/07/05 10:45
   Description: Global Mouse Class : mouse
 */


	static class _mouse
		{
		private:
		REGS in,out;
		int _loaded;
		public:
		int x,y,btn;

			_mouse()
			{
			x=y=btn=_loaded=0;
			}
			int init()
			{
			in.x.ax=0;
			int86(0x33,&in,&out);
			if(out.x.ax == 0)
				{
			    closegraph();
				cerr<<"\nError  :  Mouse init() failed .. ";
				cerr<<"\nI need mouse to work ! myeau ...";
				exit(0);
              
				}
			_loaded=true;	
			return 1;
			}// end of init()

			void show()
				{
				if(!_loaded)
					init();
				in.x.ax=1;
				int86(0x33,&in,&out);
				}
			void hide()
				{
				in.x.ax=2;
				int86(0x33,&in,&out);
				}

			void getresponse()
				{
				in.x.ax=3;
				int86(0x33,&in,&out);
				btn=out.x.bx;
				x=out.x.cx;
				y=out.x.dx;
				}
			  int isclicked(int b)
				{
				getresponse();
				if(btn & b)
				return true;

				return false;
				}

		}mouse; // end of mouse class
