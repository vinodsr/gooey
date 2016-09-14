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

#include "new_txt.h"

	int text_details::handle_event_onclick(object *obj)
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
text_details::text_details(int edit)
		{
	    	width=400;
		height=210;
		x=getmaxx()/2 - (width / 2 );
		y=getmaxy()/2 - (height /2);
		del = false;
			bgcolor=5;
		strcpy(title," Add New Textbox ");
		b_continue=new button(300,20,80,20," OK ");
		b_cancel=new button(300,60,80,20," Cancel ");
		if(edit)
		{
		b_del=new button(300,100,80,20," Delete ",4,15);
		attach(b_del);
		}
		attach(new Line(280,10,280,150,8));
	t_name = new textbox(120,10,140,20,"Tbox1"); 
		t_x=new textbox(120,35,60,20,"10");
		t_y=new textbox(120,60,60,20,"10");
		t_w=new textbox(120,85,60,20,"50");
		t_h=new textbox(120,110,60,20,"20");
		t_c=new textbox(120,135,60,20,"0");
		t_text=new textbox(120,160,140,20,"Text");
		attach(new label (30,10,80,10,"Name"));
		l_x=new label(30,35,80,10,"Left") ;
		l_y=new label(30,60,80,10,"Top") ;
		l_w=new label(30,85,80,10,"Width") ;
		l_h=new label(30,110,80,10,"Height") ;
		l_c=new label(30,135,80,10,"Color") ;
		l_t=new label(30,160,80,10,"Label") ;
		attach(l_x);
		attach(l_y);
		attach(l_w);
		attach(l_h);
		attach(l_c);
		attach(l_t);			
		attach(b_continue);
		attach(b_cancel);
		attach(t_name);
		attach(t_x);
		attach(t_y);
		attach(t_w);
		attach(t_h);
		attach(t_c);
		attach(t_text);
		}
