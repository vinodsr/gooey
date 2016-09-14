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
int isvalid(char *);
class main_window : public cwin
{
public:
button *b_continue,*b_ok;
textbox *t_win_x,*t_win_y,*t_win_w,*t_win_h,*t_win_t,*t_win_n;
label *l_x,*l_y,*l_w,*l_h,*l_t,*l_n;
	int handle_event_onclick(object *obj)
	{
       if( b_continue==obj)
		{
		if(str2int(t_win_w->text) >400)
		{
		messagebox(" Invalid width (choose < 400)",MSG_ALERT);
		return OK;
		}
		else
		return UNLOAD_CWIN;
		}
		if(b_ok == obj)
		return CANCEL_CWIN;
		}

	main_window()
		{
		width=400;
		height=200;
		x=getmaxx()/2 - (width / 2 );
		y=getmaxy()/2 - (height /2);
	strcpy(title,"Add New Form ");
		bgcolor=5;
		b_continue=new button(300,30,80,20,"OK");
		b_ok=new button(300,60,80,20," Cancel ");
		attach(new frame(10,10,260,170,"Form Details ...",15,bgcolor,0),BACK);
	attach(new Line(280,10,280,150,8,1),BACK);
		t_win_n=new textbox(120,20,140,20,"form1");
		t_win_x=new textbox(120,45,60,20,"100");
		t_win_y=new textbox(120,70,60,20,"100");
		t_win_w=new textbox(120,95,60,20,"200");
		t_win_h=new textbox(120,120,60,20,"200");
		t_win_t=new textbox(120,145,140,20,"Unnamed ");
		l_n=new label(30,20,80,10,"Name") ;
		l_x=new label(30,45,80,10,"X") ;
		l_y=new label(30,70,80,10,"Y") ;
		l_w=new label(30,95,80,10,"Width") ;
		l_h=new label(30,120,80,10,"Height") ;
		attach(new label(30,145,80,10,"Title"));
		attach(l_x); 	
		attach(l_y);
		attach(l_w);
		attach(l_h);
		attach(l_n);
		attach(b_continue);
		attach(b_ok);
		attach(t_win_n);
		attach(t_win_x);
		attach(t_win_y);
		attach(t_win_w);
		attach(t_win_h);
		attach(t_win_t);
		}
		}; //end of class
static int show_new_dialog()
{
	DEBUG_ON=false;
    main_window *w;
	char buf[80];
				sprintf(buf,"The current Heap size is %ld",heapsize());
			dog("Before new windows ");
			dog(buf);
	w=new main_window;
     run:
     w->run();
if(w->status==CANCEL_CWIN)
		{
		delete w;
		return 0;
		}
	mouse.hide();
	
	if(!isvalid(w->t_win_n->text))
             			{
           				sprintf(message,ln_notvalid,w->t_win_n->text);
	  				    messagebox(message,MSG_ALERT);
		 	            goto run;
                      		}		
	form_def.x=str2int(w->t_win_x->text);
	form_def.y=str2int(w->t_win_y->text);
	form_def.wd=str2int(w->t_win_w->text);
	form_def.ht=str2int(w->t_win_h->text);
	strcpy(form_def.title,w->t_win_t->text);
	strcpy(form_def.name,w->t_win_n->text);
	form_def.init_form();
	mouse.show();
       delete w;    //deletes the window ..
       return 1;
}

