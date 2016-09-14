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
#include "./gui/cwin.h"
#include ".\gui\widgets.h"

#include "new_line.h"

	int line_details::handle_event_onclick(object *obj)
	{
	          if( b_continue==obj)
		{
		
		return UNLOAD_CWIN;
		}
		else if( b_del==obj)
		{
			del =true;
		return UNLOAD_CWIN;
		}
		else if( b_cancel==obj)
		{
			return CANCEL_CWIN;
		}
		
	 return OK;

		}
line_details::line_details(int edit )

		{
		width=400;
		height=210;
		x=getmaxx()/2 - (width / 2 );
		y=getmaxy()/2 - (height /2);
		del = false;
			bgcolor=5;
		swapx=swapy=0;
		strcpy(title," Add New Line ");

		b_continue=new button(300,20,80,20," OK ");
		attach(b_continue);
		b_cancel=new button(300,60,80,20," Cancel ");
		attach(b_cancel);
		if(edit)
		{
		b_del=new button(300,100,80,20," Delete ",4,15);
		attach(b_del);
		}
		

		


	attach(new Line(280,10,280,150,8));
    	t_x1=new textbox(120,35,60,20,"10");
    	t_y1=new textbox(120,60,60,20,"10");
		t_x2=new textbox(120,85,60,20,"50");
		t_y2=new textbox(120,110,60,20,"50");
		t_c=new textbox(120,135,60,20,"8");
	c_dl= new checkbox(100,165,80,BLACK,0," 3D ");	
	
	
	l_x1=new label (30,35,80,10,"X1");
	l_y1=new label(30,60,80,10,"Y1") ;
	l_x2=new label (30,85,80,10,"X2");
	l_y2=new label(30,110,80,10,"Y2") ;
		attach(new label(30,135,80,10,"Color")) ;

		attach(l_x1);
		attach(l_x2);
		attach(l_y1);
		attach(l_y2);
	
		attach(c_dl);
		attach(t_x1);
		attach(t_x2);
		attach(t_y1);
		attach(t_y2);
		attach(t_c);
		}



