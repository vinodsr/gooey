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
#include <fstream.h>
#include "./gui/cwin.h"
#include "./gui/widgets.h"
//#include "./gui/msg_box.h"

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
#include "gen_code.h"

_code_gen :: open_curly()
		  {
		  fp<<"  { \n";
		  return 1;
		  }

_code_gen :: close_curly()
		  {
		  fp<<"  } \n";
		  return 1;
		  }
_code_gen :: close()
		  {
		  int index=0;
		  while(index<option_cnt)
			{
			delete option_list[index];
			index++;
			}
		  fp.close();
		  return 1;
		  }
_code_gen :: init()
		  {
		  
		  fp.open(fname,ios::out);
		  return 1;
		  }
_code_gen :: setfilename(char name[])
		  {
		  strcpy(fname,name);
		  return 1;
		  }
void _code_gen :: findgroup(_form_def *obj)
		{
		int length,i;
		 length = obj->control_list.getsize();
		 i=0;
		while(i<length)
			{
			control_handler=obj->control_list.getitem(i+1);
			switch(control_handler->type)
				{
				case C_OPTION:
					int index=0;
					int flag=0;
					while(index<option_cnt)
						{
						if(strcmp(option_list[index],((f_option*)control_handler)->gpname) == 0)
						  {
						  flag=1;
						  break;
						  }
						index++;
						}
					if(!flag)
						{
						option_list[option_cnt] = new char[50];
						strcpy(option_list[option_cnt],((f_option*)control_handler)->gpname);
						option_cnt++;
						}
				break;
				}
			i++;
			}

		}
_code_gen :: generate(_form_def *obj,int vir,int help,char *fn)
		  {
		  isvir=vir;
		  ishelp=help;
		  strcpy(funcname,fn);
		  findgroup(obj);
		  fp<<"\n #include \"gui/gui_clas.h\" \n";
		  fp<<"//TODO : Add your header files \n";
		  fp<<"\n // The window class \n";
		  fp<<"\n class _"<<obj->name<<":public cwin\n";
		  open_curly();
		  fp<<"   public :\n";
		  declare(obj);

		  constructor(obj);
		  handle_fns(obj);
		  fp<<"  }; //end of class";
		  fp<<"\n   /* Main(Display) function*/ \n";
		  mainfn(obj);
		  return 1;
		  }
_code_gen ::declare(_form_def *obj)
		{
		// option group ..
		int index=0;
		int flag=0;
		if(option_cnt)
		fp<<"   option ";
		while(index<option_cnt)
			{
			fp<<" *"<<option_list[index];
			index++;
			if(index != option_cnt)
				fp<<" , ";
			}
		if(option_cnt)
		fp<<";\n";

int i,length;
length = obj->back_control_list.getsize();
i=0;
		while(i<length)
			{
			control_handler=obj->back_control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_FRAME:
					fp<<"   frame *"<<((f_frame*)control_handler)->name<<";\n";
			    break;


				}
			i++;
			}
		 length = obj->control_list.getsize();
		 i=0;
		while(i<length)
			{
			control_handler=obj->control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_BUTTON:
					fp<<"   button *"<<((f_button*)control_handler)->name<<";\n";
			    break;

			    case C_LABEL:
					fp<<"   label *"<<((f_label*)control_handler)->name<<";\n";
			    break;

			    case C_TEXTBOX:
					fp<<"   textbox *"<<((f_textbox*)control_handler)->name<<";\n";
			    break;

			    case C_CBOX:
					fp<<"   checkbox *"<<((f_cbox*)control_handler)->name<<";\n";
			    break;

			    case C_OPTION:
					fp<<"   option *"<<((f_option*)control_handler)->name<<";\n";
			    break;

				}
			i++;
			}
		  return 1;
		}
_code_gen :: constructor(_form_def *obj)
	{
	fp<<"\n  /* The constructor */ \n";
	fp<<"  _"<<obj->name<<"()\n";
	open_curly();
	init_form(obj);
	init_controls(obj);
	close_curly();
	return 1;
	}

_code_gen ::init_form(_form_def *obj)
	{
	fp<<"\n  /* Initializing cwin attribute(s) */\n";
	if(isvir)
		{
		fp<<"   x = "<<obj->virx<<";\n";
		fp<<"   y = "<<obj->viry<<";\n";
		}
	else
		{
		fp<<"   x = "<<obj->x<<";\n";
		fp<<"   y = "<<obj->y<<";\n";
		}
	fp<<"   width = "<<obj->wd<<";\n";
	fp<<"   height = "<<obj->ht<<";\n";
	fp<<"   strcpy(title,\""<<obj->title<<"\");\n";
	  return 1;
	}

_code_gen::handle_fns(_form_def *obj)
	{
		int i,length;
		fp<<"\n  int handle_event_onclick(object *obj)\n";
		open_curly();
		if(ishelp)
		{
		fp<<"   /* the return values are UNLOAD_CWIN --> Unloads the window \n";
		fp<<"                            CANCEL_CWIN -->   \"         \"  ;\n";
		fp<<"				 but status is CANCEL_CWIN (wind->status) \n";
		fp<<"				 OK         --> simply return (no action on window)*/\n";
		}
		 length = obj->control_list.getsize();
		 i=0;
		while(i<length)
			{
			control_handler=obj->control_list.getitem(i+1);
			switch(control_handler->type)
				{
			    case C_BUTTON:
					fp<<"   if( obj == "<<((f_button*)control_handler)->name<<")\n";
					fp<<"      { ";
					fp<<"       /* Do Operations for onclick() of control "<<((f_button*)control_handler)->name<<"*/\n";
					fp<<"      return UNLOAD_CWIN;\n";
					fp<<"      }\n";
			    break;

			    
			    case C_CBOX:
					fp<<"   if( obj == "<<((f_cbox*)control_handler)->name<<")\n";
					fp<<"      { ";
					fp<<"       /* Do Operations for onclick() of control "<<((f_cbox*)control_handler)->name<<"*/\n";
					fp<<"      return OK;\n";
					fp<<"      }\n";
			    break;

			    case C_OPTION:
					fp<<"   if( obj == "<<((f_option*)control_handler)->name<<")\n";
					fp<<"      { ";
					fp<<"       /* Do Operations for onclick() of control "<<((f_option*)control_handler)->name<<"*/\n";
					fp<<"      return OK;\n";
					fp<<"      }\n";
			    break;

				}
			i++;
			}
		close_curly();
		fp<<"\n// Event handling ended ... \n";
		  return 1;

	}

_code_gen::init_controls(_form_def *obj)
	{
	int index=0;
	while(index<option_cnt)
			{
			fp<<option_list[index];
			index++;
			if(index != option_cnt)
				fp<<"=";
			}
			if(option_cnt)
			fp<<"=NULL;\n";
	fp<<"\n  /* Initailizing controls */ \n";
	int i,length;
			length = obj->back_control_list.getsize();
		 i=0;
		while(i<length)
			{
			control_handler=obj->back_control_list.getitem(i+1);
			switch(control_handler->type)
				{
				case C_LINE:
					fp<<"   attach(new  Line("
					  <<((f_line*)control_handler)->x1<<","
					  <<((f_line*)control_handler)->y1<<","
					  <<((f_line*)control_handler)->x2<<","
					  <<((f_line*)control_handler)->y2<<","
					  <<((f_line*)control_handler)->color<<"),BACK);\n";

				break;
				case C_FRAME:
					fp<<"   "<<((f_frame*)control_handler)->name<<" = new  frame ("
					  <<control_handler->left<<","
					  <<control_handler->top<<","
					  <<control_handler->width<<","
					  <<control_handler->height<<","
					  <<"\""<<((f_frame*)control_handler)->label<<"\","
					  <<((f_frame*)control_handler)->color<<","
					  <<((f_frame*)control_handler)->bgcolor<<","
					  <<((f_frame*)control_handler)->border<<");\n";
					fp<<"    attach("<<((f_frame*)control_handler)->name<<",BACK);\n";

				break;
				}
			i++;
			}

	length = obj->control_list.getsize();
	i=0;
		while(i<length)
			{
			control_handler=obj->control_list.getitem(i+1);
			switch(control_handler->type)
				{
				case C_BUTTON:
					fp<<"   "<<((f_button*)control_handler)->name<<" = new  button ("
					  <<control_handler->left<<","
					  <<control_handler->top<<","
					  <<control_handler->width<<","
					  <<control_handler->height<<","
					  <<"\""<<((f_button*)control_handler)->label<<"\","
					  <<((f_button*)control_handler)->bgcolor<<","
					  <<((f_button*)control_handler)->color<<");\n";

					fp<<"    attach("<<((f_button*)control_handler)->name<<");\n"; 
			    	
				break;
				
				case C_LABEL:
					fp<<"   "<<((f_label*)control_handler)->name<<" = new  label ("
					  <<control_handler->left<<","
					  <<control_handler->top<<","
					  <<control_handler->width<<","
					  <<control_handler->height<<","
					  <<"\""<<((f_label*)control_handler)->text<<"\"); \n";
					fp<<"    attach("<<((f_label *)control_handler)->name<<");\n"; 

				break;
				
				case C_TEXTBOX:
					fp<<"   "<<((f_textbox*)control_handler)->name<<" = new  textbox ("
					  <<control_handler->left<<","
					  <<control_handler->top<<","
					  <<control_handler->width<<","
					  <<control_handler->height<<","
					  <<"\""<<((f_textbox*)control_handler)->text<<"\"); \n";
					fp<<"    attach("<<((f_textbox*)control_handler)->name<<");\n"; 
			    	
				break;
				
				case C_OPTION:
					fp<<"   "<<((f_option*)control_handler)->name<<" = new  option ("
					  <<control_handler->left<<","
					  <<control_handler->top<<","
					  <<control_handler->width<<","
					  <<((f_option*)control_handler)->color<<","
					  <<((f_option*)control_handler)->checked<<","
					  <<"\""<<((f_option*)control_handler)->text<<"\",&"
					  <<((f_option*)control_handler)->gpname<<");\n";
					fp<<"    attach("<<((f_option*)control_handler)->name<<");\n";

				break;
				case C_CBOX:
					fp<<"   "<<((f_cbox*)control_handler)->name<<" = new  checkbox ("
					  <<control_handler->left<<","
					  <<control_handler->top<<","
					  <<control_handler->width<<","
					  <<((f_cbox*)control_handler)->color<<","
					  <<((f_cbox*)control_handler)->checked<<","
					  <<"\""<<((f_cbox*)control_handler)->text<<"\"); \n";
					fp<<"    attach("<<((f_cbox*)control_handler)->name<<");\n";

				break;

				}
			i++;
			}
			fp<<"\n\n";
		  return 1;
	}
	_code_gen :: mainfn(_form_def * obj )
		{
		fp<<"\n  int "<<funcname<<" () \n";
		open_curly();
	       //	fp<<"   gdriver.setdir(\"f:\\\\tc3\\\\bgi\\\\\");\n";
		fp<<"   gdriver.init();\n";
		fp<<"	gdriver.usepalette();\n";
		fp<<"   _"<<obj->name<<" *"<<obj->name<<";\n";
		fp<<"   "<<obj->name<<" = new _"<<obj->name<<";\n";
		fp<<"   "<<obj->name<<"->run();\n";
		fp<<"   delete "<<obj->name<<";\n";
		fp<<"   gdriver.unload();\n";
		fp<<"   return 0;\n";
		close_curly();
		  return 1;
		}
