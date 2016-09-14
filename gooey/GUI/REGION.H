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
   Name:  region.h
   Date: 07/08/05 11:40 a
   Description: class for storing a region
 */
	class region
		{
		public:
		int x1,y1;
		int x2,y2;
			region()
				{
				x1=y1=0;
				x2=y2=0;
				}

			region (int a,int b,int c,int d)
				{
				x1=a;
				y1=b;

				x2=c;
				y2=d;
				}
			void setval (int a,int b,int c,int d)
				{
				x1=a;
				y1=b;

				x2=c;
				y2=d;
				}

			void display()
				 {
				 cout<<" \n X1 = "<<x1 << " y1 = "<<y1;
				 cout<<" \n X2 = "<<x2 << " y2 = "<<y2;				 
				 }
			int contains(point p)
				{
				if(p.x>=x1 && p.x<=x2 && p.y >=y1 && p.y <= y2)
				  {  	return 1;}
				else
					return 0;
				}
		};
