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
#include "./gui/msg_box.h"

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
int copyfile(char *src,char *dest);

class
	{
	public:
	int x,y;
	int wd,ht;
	char title[50];
	char name[50];
	int mode;
	int loaded;
		void setval(char _name[50],int a,int b,int c,int d,char _title[50],int m)
			{
			x=a;
			y=b;
			wd=c;
			ht=d;
			strcpy(name,_name);
			strcpy(title,_title);
			mode=m;
			loaded=1;
			}
	}form_details;

	class
		{
		int b,l,t,c,o,f,L;
		public:
		setval(int data[CNTRL_ITEMS])
			{
			b=data[0];
			l=data[1];
			t=data[2];
			c=data[3];
			o=data[4];
			f=data[5];
			L=data[6];

			}
		getval(int data[CNTRL_ITEMS])
			{
			data[0]=b;
			data[1]=l;
			data[2]=t;
			data[3]=c;
			data[4]=o;
			data[5]=f;
			data[6]=L;
			}
		}cntrl_list;


_form_def::save_form(char *fname)
	{
     // order : bttn , label , txtbox, check ,option,frame,line ...
    int cntrl[CNTRL_ITEMS]={0,0,0,0,0,0,0};
   //	messagebox( "code to save ");
   fstream fobj;
   fobj.open(fname,ios::out|ios::binary);
   form_details.setval(name,x,y,wd,ht,title,mode);
   // write the header record
   fobj.write((char *)&form_details,sizeof(form_details));
   
   findobject_no(cntrl);
   //write the info header ...
   cntrl_list.setval(cntrl);
    fobj.write((char *)&cntrl_list,sizeof(cntrl_list));
   //write the controls ....
   //1 . button
		 int length ,i,mycnt=0,_done=false;
		 length = control_list.getsize();
		 i=0;
		 mycnt=0;
		 _done=false;
		while(i<length && !_done)
			{
			control_handler=control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_BUTTON:
			    f_button *b_dummy;
			    b_dummy =(f_button *)control_handler;
			    fobj.write((char *)b_dummy,sizeof(*b_dummy));
			    mycnt++;
			    if(mycnt == cntrl[0])
			    	_done=true;
			    break;
				}
			i++;
			}
		// 2 . label
		i=0;
		 mycnt=0;
		 _done=false;
		while(i<length && !_done)
			{
			control_handler=control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_LABEL:
			    f_label *b_dummy;
			    b_dummy =(f_label *)control_handler;
			    fobj.write((char *)b_dummy,sizeof(*b_dummy));
			    mycnt++;
			    if(mycnt == cntrl[1])
			    	_done=true;
			    break;
				}
			i++;
			}
		//3.textbox
		i=0;
		 mycnt=0;
		 _done=false;
		while(i<length && !_done)
			{
			control_handler=control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_TEXTBOX:
			    f_textbox *b_dummy;
			    b_dummy =(f_textbox *)control_handler;
			    fobj.write((char *)b_dummy,sizeof(*b_dummy));
			    mycnt++;
			    if(mycnt == cntrl[2])
			    	_done=true;
			    break;
				}
			i++;
			}
			//4. checked
			i=0;
		 mycnt=0;
		 _done=false;
		while(i<length && !_done)
			{
			control_handler=control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_CBOX:
			    f_cbox *b_dummy;
			    b_dummy =(f_cbox *)control_handler;
			    fobj.write((char *)b_dummy,sizeof(*b_dummy));
			    mycnt++;
			    if(mycnt == cntrl[3])
			    	_done=true;
			    break;
				}
			i++;
			}
		//5.Option
		i=0;
		 mycnt=0;
		 _done=false;
		while(i<length && !_done)
			{
			control_handler=control_list.getitem(i+1);
			switch(control_handler->type)
				{
				
			    case C_OPTION:
			    f_option *b_dummy;
			    b_dummy =(f_option *)control_handler;
			    fobj.write((char *)b_dummy,sizeof(*b_dummy));
			    mycnt++;
			    if(mycnt == cntrl[4])
			    	_done=true;
			    break;
				}
			i++;
			}
		//6.Frame
		length = back_control_list.getsize();
		i=0;
		 mycnt=0;
		 _done=false;
		while(i<length && !_done)
			{
			control_handler=back_control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_FRAME:
			    
			    f_frame *b_dummy;
			    b_dummy =(f_frame *)control_handler;
			    fobj.write((char *)b_dummy,sizeof(*b_dummy));
			    mycnt++;
			    if(mycnt == cntrl[5])
			    	_done=true;
			    break;
				
				}
			i++;
			}
			//7.Line
			i=0;
		 mycnt=0;
		 _done=false;
		while(i<length && !_done)
			{
			control_handler=back_control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_LINE:
			    f_line *b_dummy;
			    b_dummy =(f_line *)control_handler;
			    fobj.write((char *)b_dummy,sizeof(*b_dummy));
			    mycnt++;
			    if(mycnt == cntrl[6])
			    	_done=true;
			    break;
				}
			i++;
			}
   fobj.close();
	}

// end of the save form ()
_form_def :: load_form(char *fname)
	{



	fstream fobj;

	int cntrl[CNTRL_ITEMS];
	int i;
	copyfile(fname,"temp.gui");  // copies fname to temp.gui

   fobj.open("temp.gui",ios::in|ios::binary);
   // reading the header ..
    fobj.read((char *)&form_details,sizeof(form_details));
   if(form_details.loaded != 1)
		{
		messagebox(" Bad Format ! ",MSG_ALERT);
		fobj.close();
		remove("temp.gui");
		return 0;
		}
	if(loaded)         // removing previously stored values ...
		{
		
		kill();
		}

      //storing the details
      x=form_details.x;
      y=form_details.y;
      wd=form_details.wd;
      ht=form_details.ht;
      strcpy(name,form_details.name);
      strcpy(title,form_details.title);

      //reading the info part ..
    fobj.read((char *)&cntrl_list,sizeof(cntrl_list));
    cntrl_list.getval(cntrl);
   // reading the controls
   //button
   i=0;
   while(i<cntrl[0])
		{
		f_button *dummy;
		dummy=new f_button;
		fobj.read((char *)dummy,sizeof(*dummy));
		control_list.insert((control *)dummy);
		i++;
		}
	// label
   i=0;
   while(i<cntrl[1])
		{
		f_label *dummy;
		dummy=new f_label;
		fobj.read((char *)dummy,sizeof(*dummy));
		control_list.insert((control *)dummy);
		i++;
		}
	//textbox
   i=0;
   while(i<cntrl[2])
		{
		f_textbox *dummy;
		dummy=new f_textbox;
		fobj.read((char *)dummy,sizeof(*dummy));
		control_list.insert((control *)dummy);
		i++;
		}
	//check
   i=0;
   while(i<cntrl[3])
		{
		f_cbox *dummy;
		dummy=new f_cbox;
		fobj.read((char *)dummy,sizeof(*dummy));
		control_list.insert((control *)dummy);
		i++;
		}
	//option
   i=0;
   while(i<cntrl[4])
		{
		f_option *dummy;
		dummy=new f_option;
		fobj.read((char *)dummy,sizeof(*dummy));
		control_list.insert((control *)dummy);
		i++;
		}
   //frame -- back
	i=0;
   while(i<cntrl[5])
		{
		f_frame *dummy;
		dummy=new f_frame;
		fobj.read((char *)dummy,sizeof(*dummy));
		back_control_list.insert((control *)dummy);
		i++;
		}
		// line ..
	i=0;
   while(i<cntrl[6])
		{
		f_line *dummy;
		dummy=new f_line;
		fobj.read((char *)dummy,sizeof(*dummy));
		back_control_list.insert((control *)dummy);
		i++;
		}
  fobj.close();
remove("temp.gui");


   init_form();
   //setting mode
    mode=form_details.mode;
   show_form();
   return 1;
	} // end oif loadform()
   _form_def :: findobject_no(int d[CNTRL_ITEMS])
	{
		 int length ,i;
		 length = control_list.getsize();
		 i=0;
		while(i<length)
			{
			control_handler=control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_BUTTON:
					d[0]++;
			    break;

			    case C_LABEL:
					d[1]++;
			    break;
			    case C_TEXTBOX:
					d[2]++;
			    break;

			    case C_CBOX:
					d[3]++;
			    break;

			    case C_OPTION:
					d[4]++;
			    break;

				}
			i++;
			}
		 length = back_control_list.getsize();
		 i=0;
		while(i<length)
			{
			control_handler=back_control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_FRAME:
					d[5]++;
			    break;

			    case C_LINE:
					d[6]++;
			    break;
				}
			i++;
		
		}
			
	}
