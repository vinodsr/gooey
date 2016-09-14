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



int get_clicked_area()
	{

			region menu(0,20,getmaxx(),40);
			region tool(10,45,85,440);
			region client(form_def.virx,form_def.viry,form_def.wd+form_def.virx,form_def.ht+form_def.viry);

	while(1)
		{

		mouse.getresponse();
		point p(mouse.x,mouse.y);
		if(mouse.btn &1)
		{
			if(menu.contains(p))
				{
				return 1;
				}
			else if(tool.contains(p))
				return 2;


		} // end of m,ouse click
		else if (mouse.btn &2)
			{
			if(client.contains(p))
					return 3;
			}
		}
	}
