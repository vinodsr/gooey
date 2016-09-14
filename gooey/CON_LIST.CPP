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
#include "./gui/widgets.h"

#include "f_bttn.cpp"
#include "f_cbox.cpp"
#include "f_label.cpp"
#include "f_tbox.cpp"
#include "f_frame.cpp"
#include "f_option.cpp"
#include "f_line.cpp"

#include "new_btn.h"
#include "new_lab.h"
#include "new_txt.h"
#include "new_cb.h"
#include "new_frm.h"
#include "new_opt.h"
#include "new_line.h"


#include "form_def.h"
#include "con_list.h"

int cntrl_browse::handle_event_onclick(object *obj)
	{
	   for(i=0;i<max*4;i++)
		{
		 if(b_group[i] == obj)
			{
			call_dialog(i+(page*max*4));
			//page =0;
	//		getch();
			init_values();
			break;

			}

		}
		if(obj == next)
			{
		page++;
	    init_values();
			}

  if(obj == prev)
			{
		page--;
	    init_values();
			}

  if(obj == b_ok)
	return UNLOAD_CWIN;
		return OK;
		}

void cntrl_browse::call_dialog(int n)
		{
		control_handler = obj->control_list.getitem(n+1);
		switch(control_handler->type)
			{
			case C_BUTTON:
					obj->edit_dialog((f_button *)control_handler);
				break;
				case C_LABEL:
					obj->edit_dialog((f_label *)control_handler);
				break;
				case C_TEXTBOX:
					obj->edit_dialog((f_textbox *)control_handler);
				break;
				case C_CBOX:
					obj->edit_dialog((f_cbox *)control_handler);
				break;
				case C_OPTION:
					obj->edit_dialog((f_option *)control_handler);
				break;
				
			}
		}
void cntrl_browse::init_values()
		{
		length = obj->control_list.getsize();
		int done = false;
		for(i=0; (i<max);i++)
		for(j=0;j<4;j++)
			{
			b_group[(i*4)+j]->visible = false;
			b_group[(i*4)+j]->setvalue(" ");
			}


		for( i=0;((i+(page*max))*4)<length && (i<max)&&!done;i++)
		for( j=0;j<4;j++)
			{
			if(((i+(page*max))*4)+j == length)
				{
				done=true;
				break;
				}
				dog("*");
			control_handler = obj->control_list.getitem(((i+(page*max))*4)+j+1);
			b_group[(i*4)+j]->bgcolor=getbgcolor(control_handler);
			b_group[(i*4)+j]->color=getcolor(control_handler);
			
			b_group[(i*4)+j]->visible =true;
			b_group[(i*4)+j]->setvalue(getname(control_handler));

			}
		if((i+(page*max*4)*4)+j > length)
		next->disabled =true;
		else
		next->disabled =false;
		if(!page)
		prev->disabled = true;
		else
		prev->disabled = false;


				struct viewporttype viewinfo;
		getviewsettings(&viewinfo);

		setviewport(0,0,getmaxx(),getmaxy(),1);
		paint(1);
		setviewport(viewinfo.left,viewinfo.top,viewinfo.right, viewinfo.bottom,viewinfo.clip);
		}
char* cntrl_browse::getname(control *c)
		{
		switch(c->type)
			{
				case C_BUTTON:
					return ((f_button *)control_handler)->name;

				case C_LABEL:
					return ((f_label *)control_handler)->name;

				case C_TEXTBOX:
					return ((f_textbox *)control_handler)->name;

				case C_CBOX:
					return ((f_cbox *)control_handler)->name;
				
				case C_OPTION:
					return ((f_option *)control_handler)->name;



			}
		}
	
int cntrl_browse::getbgcolor(control *c)
		{
		switch(c->type)
			{
				case C_BUTTON:
					return 9;
				break;
				case C_LABEL:
					return 1;
				break;
				case C_TEXTBOX:
					return 2;
				break;
				case C_CBOX:
					return 3;
				break;
				case C_OPTION:
					return 6;
				break;

			}
		     return 0;
		}

int  cntrl_browse::getcolor(control *c)
		{
		switch(c->type)
			{
				case C_BUTTON:
					return 0;
				break;
				case C_LABEL:
				case C_TEXTBOX:
				case C_CBOX:
				case C_OPTION:
					return 15;
				break;

			}
		return 0;
		}



cntrl_browse::cntrl_browse(_form_def *dummy)

		{
		obj=dummy;
		width=500;
		height=300;
		x=getmaxx()/2 - (width / 2 );
		y=getmaxy()/2 - (height /2);
		strcpy(title," Control Browser ");
		bgcolor=5;
		dec =2;
		length = 0;
		page =0;
		max=4; // maximum lines ....
		int done = false;

		if(obj->loaded)
		{
		length = obj->control_list.getsize();
		//do smething with loop ...



		for(i=0; (i<max);i++)
		for(j=0;j<4;j++)
			{
			b_group[(i*4)+j] = new button (10+(j*100),50+(i*30),80,20);
			b_group[(i*4)+j]->visible = false;
			attach(b_group[(i*4)+j]);
			}

		for( i=0;((i+(page*max))*4)<length && (i<max)&&!done;i++)
		for( j=0;j<4;j++)
			{
			if(((i+(page*max))*4)+j == length)
				{
				done=true;
				break;
				}
				dog("*");
			//	cout<<" o "<<(i+(page*max*4))+j+1;
			control_handler = obj->control_list.getitem(((i+(page*max))*4)+j+1);
			b_group[(i*4)+j]->setvalue(getname(control_handler));	
			b_group[(i*4)+j]->bgcolor=getbgcolor(control_handler);
			b_group[(i*4)+j]->color=getcolor(control_handler);

			b_group[(i*4)+j]->visible =true;

			}

		attach(new label(20,200,60,20,"Button",0,9,1));
		attach(new label(80,200,60,20,"Label",15,1,1));
		attach(new label(140,200,80,20,"Textbox",15,2,1));
		attach(new label(220,200,80,20,"Checkbox",15,3,1));
		attach(new label(300,200,80,20,"Option",15,6,1));
		
		attach(new Line(20,230,width-20,230,8));
		attach(new Line(400,20,400,height -100,8));
		b_ok = new button(430,50,50,20,"OK");
		attach(b_ok);
		
		
		next = new button(425,250,50,20,"Next");
		prev = new button(25,250,100,20,"Previous");
		if((i+(page*max*4)*4)+j > length)
		next->disabled =true;
		if(!page)
		prev->disabled = true;
		attach(next);
		attach(prev);
			if(length == 0)
						
				{
				
				message = new label(width/2 - 80,height/2-20,200,20," No Controls Added ! " );
				message->border= true;
				message->centered = true;
				attach(message);
				}
		} // end of loaded 
		else
		{
				message = new label(width/2 - 80,height/2-20,200,20," Form not defined ! " );
				message->border= true;
				message->centered = true;
				attach(message);
		
		}
		//c=new checkbox(10,10,100,1,12,"Select  A Option ?");
		//attach(c);
		//l = new label(2,50,50,20,"label");
		 // attach(l);

		}

int browse_controls(_form_def *obj )
{      


    cntrl_browse *w;

	w=new cntrl_browse(obj);
    run:
      if(w->run() == CANCEL_CWIN)
	goto run;
       delete w;
	  //deletes the window ..
		return 1;
}


