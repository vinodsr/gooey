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
#include <ctype.h>

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
#include "new_wind.cpp"

int isvalid(char *name)
	{
	int i;
	if(isdigit(*name))
		return 0;
	i=1;
	while(*(name+i) !='\0')	
		{
		if(*(name+i) ==' ')
			return 0;
		i++;
		}
	return 1;
	}
void clearclient();
_form_def :: edit_form()
	{
	main_window *edit;
	edit = new main_window;
	edit->t_win_y->setval(y);
	edit->t_win_x->setval(x);
	edit->t_win_w->setval(wd);
	edit->t_win_h->setval(ht);
	edit->t_win_n->setval(name);
	edit->t_win_t->setval(title);
	strcpy(edit->title," Edit Form ");
	
	run:
	edit->run();
	if(!isvalid(edit->t_win_n->text))
             			{
           				sprintf(message,ln_notvalid,edit->t_win_n->text);
	  				    messagebox(message,MSG_ALERT);
		 	            goto run;
                      		}

	// re-apply the changed value
	x=str2int(edit->t_win_x->text);
	y=str2int(edit->t_win_y->text);
	wd=str2int(edit->t_win_w->text);
	if(wd <80)
	wd=80;
	ht=str2int(edit->t_win_h->text);
	if(ht<title_bar_height)
	ht=title_bar_height;
	strcpy(name,edit->t_win_n->text);
	strcpy(title,edit->t_win_t->text);
	delete edit;
	virx=x+86;
	viry=y+40;
	changed=true;
	clearclient();
	show_form();

	}

void _form_def::showstatus()
			{
			int fx=10,fy=300,fwd=75,fht =100;
			gdriver.draw_bar(fx,fy,fwd,20,1,15);
			gdriver.draw_3dbar(fx,fy+20,fwd,fht,5,5,1,2);
			setcolor(15);
			outtextxy(fx+10,fy+8," Status ");
			setcolor(0);
			if(!loaded)
			outtextxy(fx,fy+20+10,"NotLoaded");
			else
			{  //do rest
		    		char str[50];
		    		switch(mode)
		    			{
		    			case 10 : outtextxy(fx+1,fy+20+18,"Mode : BG"); break;
		    			case 01 : outtextxy(fx+1,fy+20+18,"Mode : FG"); break;
		    			}
			}
		      
			}
		
        _form_def::contains(int _type)
                {
                        int i=0;
                 int length = control_list.getsize();

                 while(i<length)
                 {
                 if((control_list.getitem(i+1))->type == _type)
                         return true;
                 i++;
                 }
                 i=0;
                 length = back_control_list.getsize();
                 while(i<length)
                 {
                 if((back_control_list.getitem(i+1))->type == _type)
			 return true;
                 i++;
                 }
                 
                 return false;
                }

        _form_def::contains(char  _name[128])
                {
                resume_dog();
                dog("Initiating content search ");
                        int i=0;
                 int length = control_list.getsize();
			
                 while(i<length)
                 {
                 control_handler = control_list.getitem(i+1);
                         switch(control_handler->type)
                                {
                                case C_BUTTON:

                                        if(strcmp(((f_button *)control_list.getitem(i+1))->name,_name) == 0)
                                		   return true;
                                        
                                break;
                                case C_LABEL:
                                        if(strcmp(((f_label *)control_list.getitem(i+1))->name,_name) == 0)
                                   				 return true;
                                  break;
                                case C_TEXTBOX:
                                        if(strcmp(((f_textbox *)control_list.getitem(i+1))->name,_name) == 0)
                                                                         return true;
                                break;
 								case C_CBOX:
                                        if(strcmp(((f_cbox *)control_list.getitem(i+1))->name,_name) == 0)
                                                                         return true;
                                break;
                                case C_OPTION:
                                        if(strcmp(((f_option *)control_list.getitem(i+1))->name,_name) == 0)
                                                                         return true;
				break;

							}
					i++;
				
			      }
			  i=0;
              length = back_control_list.getsize();
			
                 while(i<length)
                 {
                 control_handler = back_control_list.getitem(i+1);
                         switch(control_handler->type)
                                {
                                case C_FRAME:
                                
                                        if(strcmp(((f_frame *)control_list.getitem(i+1))->name,_name) == 0)
                                		   return true;
                                        
                                break;

							}
					i++;
				
			      }
			 
			      dog("Failed search ");
			      close_dog();
			      return false;
			      }
        int _form_def::right_clicked(_mouse m)
                {
                 int i; 
                 int length; 
		 int done=false;
		 if(m.x>virx && m.x<virx+wd && m.y>viry &&m.y<viry+title_bar_height)
			edit_form();
                 // for backgound items .. 
                 if(mode == 10)
                 	{
						i=0;
                 		length = back_control_list.getsize();
		                 
    		             region control;
		                 point p(m.x,m.y);
		         
		                 gdriver.savescreen(virx,viry,virx+wd,viry+ht);
		                 while(i<length&&!done)
		                 {
		                 control_handler = back_control_list.getitem(i+1);
		                 control.setval(virx+control_handler->left,
		                                               viry+title_bar_height+control_handler->top,
		                                               virx+control_handler->left+control_handler->width,
		                                               viry+title_bar_height+control_handler->top+control_handler->height);
		                if(control.contains(p))
		                {
		
		                        switch(control_handler->type)
		                                {
		                                case C_FRAME:
							edit_dialog((f_frame*) control_handler);
		
		                                break;
		                                case C_LINE:
		                                        edit_dialog((f_line*) control_handler);
		
		                                break;
		                                }
		
		
		
	    	            done = true;
	    	            } //end of if
	
	    	                    /* checking for the mouse over any control */
	
	    	            i++;
	    	            } // end of while                 	
                 	}
                 else
			{
                 	i=0;
                 	length = control_list.getsize();
	                 
    	             region control;
	                 point p(m.x,m.y);
	         
	                 gdriver.savescreen(virx,viry,virx+wd,viry+ht);
	                 while(i<length&&!done)
	                 {
	                 control_handler = control_list.getitem(i+1);
	                 control.setval(virx+control_handler->left,
	                                               viry+title_bar_height+control_handler->top,
	                                               virx+control_handler->left+control_handler->width,
	                                               viry+title_bar_height+control_handler->top+control_handler->height);
	                if(control.contains(p))
	                {
	
	                        switch(control_handler->type)
	                                {
					case C_BUTTON:
	                                        edit_dialog((f_button*) control_handler);
	
	                                break;
	                                        case C_LABEL:
	                                        edit_dialog((f_label*) control_handler);
	                                        break;
	
	                                        case C_TEXTBOX:
	                                        edit_dialog((f_textbox*) control_handler);
	                                        break;
	                                     	case C_CBOX:
											edit_dialog((f_cbox*) control_handler);
											break;
											case C_OPTION:
											edit_dialog((f_option *) control_handler);
											break;
	
	                                }
	

	
	                done = true;
	                } //end of if
	
	                        /* checking for the mouse over any control */

	                i++;
	                } // end of while
					} // end of the else of the mode .. 
//                show_form();
//control_list.remove(1);
                 if(!done)
                 gdriver.restorescreen(virx,viry,virx+wd,viry+ht);
                 else
                 {
                 gdriver.killscreen();
                 show_form();
                 }
                 
		} //end of the func
         _form_def::new_text_diag(point p)
                {
                             text_details *new_text;
                             new_text=new text_details;
                                 char buf[50];
                                 sprintf(buf,"%d",p.x-virx);
                                 strcpy(new_text->t_x->text,buf);
                                 sprintf(buf,"%d",p.y-viry-title_bar_height);
                                 strcpy(new_text->t_y->text,buf);
                             run:
                             gdriver.savescreen(new_text->x,new_text->y,new_text->x+new_text->width,new_text->y+new_text->height);
                             new_text->run();
                                        //        cout<<w->t1->text;
                                gdriver.restorescreen(new_text->x,new_text->y,new_text->x+new_text->width,new_text->y+new_text->height);
                                        if(new_text->status == CANCEL_CWIN)
                                                                                {
                                                                                delete new_text;
                                                                                return 1;
                                                                                }
					if(!isvalid(new_text->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_text->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	
				if(contains(new_text->t_name->text))
										{
										sprintf(message,ln_cntrl_name_choosen,new_text->t_name->text);
										messagebox(message,MSG_INFO);
										goto run;
										}
                                mouse.hide();
                                setfillstyle(1,0);               // To be done with
                                        //Save screen()..
                                //bar(new_text->x,new_text->y,new_text->width+new_text->x,new_text->y+new_text->height);

                                mouse.show();
                                        tb_handler=new f_textbox (new_text->t_name->text,str2int(new_text->t_x->text),
                                                                          str2int(new_text->t_y->text),
                                                                        str2int(new_text->t_w->text),
                                                                        str2int(new_text->t_h->text),
                                                                    str2int(new_text->t_c->text),
                                                                        new_text->t_text->text);


				control_list.insert((control *)tb_handler);

                                // create the widget at the form ..
                                //lb^x^y^c^0^0^label
                            /*add_record("tb",str2int(new_text->t_x->text)
                                    ,str2int(new_text->t_y->text)
                                    ,str2int(new_text->t_w->text)
                                    ,str2int(new_text->t_h->text)
                                    ,str2int(new_text->t_c->text)
                                    ,new_text->t_text->text);*/
                         delete new_text;    //deletes the window ..
                 show_form();
                }

	_form_def::new_cbox_diag(point p)
		{
			     cbox_details *new_cbox;
			     new_cbox=new cbox_details;
				  char buf[50];
				 sprintf(buf,"%d",p.x-virx);
				 strcpy(new_cbox->t_x->text,buf);
				 sprintf(buf,"%d",p.y-viry-title_bar_height);
				 strcpy(new_cbox->t_y->text,buf);
			     run:
				   new_cbox->run();
				       if(new_cbox->status == CANCEL_CWIN)
						 {
						 delete new_cbox;
						 return 1;
						 }
					//	cout<<w->t1->text;
					if(!isvalid(new_cbox->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_cbox->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	
				if(contains(new_cbox->t_name->text))
						{
					sprintf(message,ln_cntrl_name_choosen,new_cbox->t_name->text);
					messagebox(message,MSG_INFO);
					goto run;
						}
							cbox_handler=new f_cbox(new_cbox->t_name->text,str2int(new_cbox->t_x->text),
						str2int(new_cbox->t_y->text),
						str2int(new_cbox->t_w->text),
						str2int(new_cbox->t_c->text),
						new_cbox->c_checked->checked,
						new_cbox->t_text->text);
										sprintf(buf,"The current Heap size is %ld",heapsize());

				control_list.insert((control *)cbox_handler);
			
				 delete new_cbox;    //deletes the window ..
				 show_form();
		}
	_form_def::new_line_diag(point p)
		{
	
			     line_details *new_line;
			     new_line=new line_details;
			     
				new_line->t_x1->setval(p.x-virx);
				  		
				new_line->t_y1->setval(p.y-viry-title_bar_height);
				new_line->t_x2->setval(p.x-virx);
				new_line->t_y2->setval(p.y-viry-title_bar_height+50);
		
			     run:
				   new_line->run();
			
						if(new_line->status == CANCEL_CWIN)
						 {
						 delete new_line;
						 return 1;
						 }
					
		 line_handler=new f_line(str2int(new_line->t_x1->text),
						str2int(new_line->t_y1->text),
						str2int(new_line->t_x2->text),
						str2int(new_line->t_y2->text),
						str2int(new_line->t_c->text),
						new_line->c_dl->checked); 

//line_handler = new f_line(10,10,100,100,10);

			line_handler->left=line_handler->x1;
			line_handler->top=line_handler->y1;
				back_control_list.insert((control *)line_handler);

				 delete new_line;    //deletes the window ..
				 show_form();
		}
_form_def::new_optn_diag(point p)
		{
			     option_details *new_option;
			     	     new_option=new option_details;
						new_option->t_x->setval(p.x-virx);
				new_option->t_y->setval(p.y-viry-title_bar_height);
			     run:
			     new_option->run();
				if(new_option->status == CANCEL_CWIN)
						 {
						 delete new_option;
						 return 1;
						 }
					//	cout<<w->t1->text;
					if(!isvalid(new_option->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_option->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      if(!isvalid(new_option->t_gpname->text))
                      			{
                      				sprintf(message,ln_notvalid,new_option->t_gpname->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	
				if(contains(new_option->t_name->text))
										{
										sprintf(message,ln_cntrl_name_choosen,new_option->t_name->text);
										messagebox(message,MSG_INFO);
										goto run;
										}
			option_handler=new f_option(new_option->t_name->text,new_option->t_gpname->text,str2int(new_option->t_x->text),
						str2int(new_option->t_y->text),
						str2int(new_option->t_w->text),
						str2int(new_option->t_c->text),
						new_option->c_checked->checked,
						new_option->t_lab->text);
				control_list.insert((control *)option_handler);
				 delete new_option;    //deletes the window ..
				 show_form();
		}


        _form_def::new_label_diag(point p)
		{
                             label_details *new_label;
                             new_label=new label_details;
                                  char buf[50];
                                 sprintf(buf,"%d",p.x-virx);
                                 strcpy(new_label->t_x->text,buf);
                                 sprintf(buf,"%d",p.y-viry-title_bar_height);
                                 strcpy(new_label->t_y->text,buf);
                             run:
                                    gdriver.savescreen(new_label->x,new_label->y,new_label->x+new_label->width,new_label->y+new_label->height);
                             new_label->run();
                                         gdriver.restorescreen(new_label->x,new_label->y,new_label->x+new_label->width,new_label->y+new_label->height);
                            
                                if(new_label->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_label;
                                                                         return 1;
                                                                         }
                                        //        cout<<w->t1->text;
                  					if(!isvalid(new_label->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_label->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	
                  				if(contains(new_label->t_name->text))
										{
										sprintf(message,ln_cntrl_name_choosen,new_label->t_name->text);
										messagebox(message,MSG_INFO);
										goto run;
										}
										
                                if(str2int(new_label->t_h->text) < 20)
                                        {
                                        messagebox(" Label height shold be > 20 ",MSG_ALERT);
                                        goto run;
                                        }
                                mouse.hide();
                                setfillstyle(1,0);               // To be done with
                                        //Save screen()..
                                bar(new_label->x,new_label->y,new_label->width+new_label->x,new_label->y+new_label->height);

                                mouse.show();
                                        lab_handler=new f_label(new_label->t_name->text,str2int(new_label->t_x->text),
                                                                          str2int(new_label->t_y->text),
                                                                        str2int(new_label->t_w->text),
									str2int(new_label->t_h->text),
                                                                    str2int(new_label->t_c->text),
                                                                        new_label->t_lab->text);


                                control_list.insert((control *)lab_handler);

                                // create the widget at the form ..
                                //lb^x^y^c^0^0^label
                         /*   add_record("lb",str2int(new_label->t_x->text)
                                    ,str2int(new_label->t_y->text)
                                    ,str2int(new_label->t_w->text)
                                    ,str2int(new_label->t_h->text)
                                    ,str2int(new_label->t_c->text)
                                    ,new_label->t_lab->text) ;*/
                         delete new_label;    //deletes the window ..
                          show_form();
                }
                
            _form_def::new_frame_diag(point p)
		{
                             frame_details *new_frame;
              
               
                             new_frame=new frame_details;
                          
                                new_frame->t_x->setval(p.x-virx);
                                new_frame->t_y->setval(p.y-viry-title_bar_height);
                               
                             run:
                 
                      new_frame->run();
                 
                    
                                if(new_frame->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_frame;
                                                                         return 1;
                                                                         }
                                        //        cout<<w->t1->text;
							if(!isvalid(new_frame->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_frame->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	
						if(contains(new_frame->t_name->text))
										{
										sprintf(message,ln_cntrl_name_choosen,new_frame->t_name->text);
										messagebox(message,MSG_INFO);
										goto run;
										}
										
                                if(str2int(new_frame->t_h->text) < 20)
                                        {
                                        messagebox(" frame height shold be > 20 ",MSG_ALERT);
                                        goto run;
                                        }
                 
                                        frame_handler=new f_frame(new_frame->t_name->text,str2int(new_frame->t_x->text),
                                                                          str2int(new_frame->t_y->text),
                                                                        str2int(new_frame->t_w->text),
                                                                        str2int(new_frame->t_h->text),
                                                                    str2int(new_frame->t_bg->text),
                                                                     str2int(new_frame->t_c->text),
                                                                      str2int(new_frame->t_bor->text),
									new_frame->t_lab->text);


                                back_control_list.insert((control *)frame_handler);

                       
                          delete new_frame;
                          show_form();
                          
                }
         _form_def::edit_dialog(f_frame * dummy)
                {//bn^x^y^w^h^c^frame


                             frame_details *new_frame;
                             new_frame=new frame_details(true);
                              new_frame->t_x->setval(dummy->left);
                            new_frame->t_y->setval(dummy->top);
                            new_frame->t_w->setval(dummy->width);
                            new_frame->t_h->setval(dummy->height);
			    new_frame->t_c->setval(dummy->color);
                              new_frame->t_bg->setval(dummy->bgcolor);
                                new_frame->t_bor->setval(dummy->border);
                            new_frame->t_lab->setval(dummy->label);
                             new_frame->t_name->setval(dummy->name);

                                strcpy(new_frame->title,"Edit frame");
                             run:
                            
                             delay(150);

                             new_frame->run();
							if(new_frame ->del == true)
                              	{
                            	back_control_list.remove((control *)dummy);
                             // 	control_list.display();
                             //	getch();
                             	
                                delete new_frame;
                                return 1;
				}
                            
                                if(new_frame->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_frame;
                                                                         return 1;
                                                                         }
                                        //        cout<<w->t1->text;
                                
                                	if(!isvalid(new_frame->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_frame->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	

           dummy->left=new_frame->t_x->value;
                                    dummy->top=new_frame->t_y->value;
                                    dummy->width=new_frame->t_w->value;
                                    dummy->height=new_frame->t_h->value;
                                   dummy->color=new_frame->t_c->value;
				    dummy->bgcolor=new_frame->t_bg->value;
                                     dummy->border=new_frame->t_bor->value;
                                    strcpy(dummy->label,new_frame->t_lab->text);
                                    strcpy(dummy->name,new_frame->t_name->text);
                                // create the widget at the form ..
                                //bn^x^y^w^h^c^frame
                        /*    edit_record(num,"lb",str2int(new_frame->t_x->text)
                                    ,str2int(new_frame->t_y->text)
                                    ,str2int(new_frame->t_w->text)
                                    ,str2int(new_frame->t_h->text)
                                    ,str2int(new_frame->t_c->text)
                                    ,new_frame->t_lab->text);*/
                         delete new_frame;    //deletes the window ..
                }


         _form_def::edit_dialog(f_label * dummy)
                {//bn^x^y^w^h^c^label


			     label_details *new_label;
                             new_label=new label_details(true);
                              new_label->t_x->setval(dummy->left);
                            new_label->t_y->setval(dummy->top);
                            new_label->t_w->setval(dummy->width);
                            new_label->t_h->setval(dummy->height);
                            new_label->t_c->setval(dummy->color);
                            new_label->t_lab->setval(dummy->text);
                             new_label->t_name->setval(dummy->name);

                                strcpy(new_label->title,"Edit Label");
                             run:
                            
                             delay(150);

                             new_label->run();
							if(new_label ->del == true)
                              	{
                            	control_list.remove((control *)dummy);
                             // 	control_list.display();
			     //	getch();
                             	
                                delete new_label;
                                return 1;
                              	}
                            
                                if(new_label->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_label;
                                                                         return 1;
                                                                         }
                                        //        cout<<w->t1->text;
                                	if(!isvalid(new_label->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_label->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	
           dummy->left=new_label->t_x->value;
				    dummy->top=new_label->t_y->value;
                                    dummy->width=new_label->t_w->value;
                                    dummy->height=new_label->t_h->value;
                                   dummy->color=new_label->t_c->value;
                                    strcpy(dummy->text,new_label->t_lab->text);
                                    strcpy(dummy->name,new_label->t_name->text);
                                // create the widget at the form ..
                                //bn^x^y^w^h^c^label
                        /*    edit_record(num,"lb",str2int(new_label->t_x->text)
                                    ,str2int(new_label->t_y->text)
                                    ,str2int(new_label->t_w->text)
                                    ,str2int(new_label->t_h->text)
                                    ,str2int(new_label->t_c->text)
                                    ,new_label->t_lab->text);*/
                         delete new_label;    //deletes the window ..
                }

	_form_def::edit_dialog(f_cbox *dummy)
		{			//bn^x^y^w^h^c^label
				cbox_details *new_cbox;
			     new_cbox=new cbox_details(true);
			    new_cbox->t_x->setval(dummy->left);
			    new_cbox->t_y->setval(dummy->top);
			    new_cbox->t_w->setval(dummy->width);
			    new_cbox->t_c->setval(dummy->color);
			    new_cbox->t_text->setval(dummy->text);
				new_cbox->t_name->setval(dummy->name);
			    new_cbox->c_checked->checked=dummy->checked;
				strcpy(new_cbox->title,"Edit Button");
			     run:
			     delay(150);

			     new_cbox->run();
			     	if(new_cbox ->del == true)
                              	{
                            	control_list.remove((control *)dummy);
                                delete new_cbox;
				return 1;
                              	}
                         	  if(new_cbox->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_cbox;
                                                                         return 1;
                                                                         }
					if(!isvalid(new_cbox->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_cbox->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	

				 dummy->left=new_cbox->t_x->value;
				    dummy->top=new_cbox->t_y->value;
				    dummy->width=new_cbox->t_w->value;
				    dummy->checked=new_cbox->c_checked->checked;
				   dummy->color=new_cbox->t_c->value;
				    strcpy(dummy->text,new_cbox->t_text->text);
				    strcpy(dummy->name,new_cbox->t_name->text);
			 delete new_cbox;    //deletes the window ..
		}
		
		
		_form_def::edit_dialog(f_option *dummy)
		{		option_details *new_option;
			     new_option=new option_details(true);
			    new_option->t_x->setval(dummy->left);
			    new_option->t_y->setval(dummy->top);
			    new_option->t_w->setval(dummy->width);
			    new_option->t_c->setval(dummy->color);
			    new_option->t_lab->setval(dummy->text);
			    new_option->t_name->setval(dummy->name);
			    new_option->t_gpname->setval(dummy->gpname);

			    new_option->c_checked->checked=dummy->checked;
				strcpy(new_option->title,"Edit Option");
			     run:
			     delay(150);

			     new_option->run();
			     	if(new_option ->del == true)
                              	{
                            	control_list.remove((control *)dummy);
                                delete new_option;
                                return 1;
                              	}
                         	  if(new_option->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_option;
                                                                         return 1;
                                                                         }
				
					if(!isvalid(new_option->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_option->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      		if(!isvalid(new_option->t_gpname->text))
                      			{
                      				sprintf(message,ln_notvalid,new_option->t_gpname->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      		
				 dummy->left=new_option->t_x->value;
				    dummy->top=new_option->t_y->value;
				    dummy->width=new_option->t_w->value;
				    dummy->checked=new_option->c_checked->checked;
				   dummy->color=new_option->t_c->value;
				    strcpy(dummy->text,new_option->t_lab->text);
				    strcpy(dummy->name,new_option->t_name->text);
				    strcpy(dummy->gpname,new_option->t_gpname->text);
				    
			 delete new_option;    //deletes the window ..
		}

_form_def::edit_dialog(f_line *dummy)
		{		line_details *new_line;
			     new_line=new line_details(true);
			 
			 
			    new_line->c_dl->checked=dummy->dline;
			  
			    new_line->t_x1->setval(dummy->x1);
			    new_line->t_x2->setval(dummy->x2);
			    new_line->t_y1->setval(dummy->y1);
			    new_line->t_y2->setval(dummy->y2);
			    new_line->t_c->setval(dummy->color);			    
				strcpy(new_line->title,"Edit line");
			     run:
			     delay(150);

			     new_line->run();
			     	if(new_line ->del == true)
                              	{
                            	back_control_list.remove((control *)dummy);
                                delete new_line;
                                return 1;
                              	}
               
                		if(new_line->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_line;
                                                                         return 1;
                                                                         }
                   
                   dummy->dline=new_line->c_dl->checked;
                	dummy->x1=new_line->t_x1->value;
                  	dummy->x2=new_line->t_x2->value;
				    dummy->y1=new_line->t_y1->value;
				    dummy->y2=new_line->t_y2->value;  
				    dummy->left=dummy->x1;
				    dummy->top=dummy->y1;
				   dummy->color=new_line->t_c->value;
				    				    
			 delete new_line;    //deletes the window ..
		}

         _form_def::edit_dialog(f_textbox * dummy)
                {


                             text_details *new_text;
                             new_text=new text_details(true);
                              new_text->t_x->setval(dummy->left);
			    new_text->t_y->setval(dummy->top);
                            new_text->t_w->setval(dummy->width);
                            new_text->t_h->setval(dummy->height);
                            new_text->t_c->setval(dummy->color);
                            new_text->t_text->setval(dummy->text);
                             new_text->t_name->setval(dummy->name);

                                strcpy(new_text->title,"Edit textbox");
                             run:
                             
                             

                             new_text->run();
                                  if(new_text ->del == true)
                              	{
                            	control_list.remove((control *)dummy);
                                delete new_text;
				return 1;
                              	}

                               
                                if(new_text->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_text;
                                                                         return 1;
                                                                         }
                                        //        cout<<w->t1->text;
                             	if(!isvalid(new_text->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_text->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	

           dummy->left=new_text->t_x->value;
                                    dummy->top=new_text->t_y->value;
                                    dummy->width=new_text->t_w->value;
				     				dummy->height=new_text->t_h->value;
                                    dummy->color=new_text->t_c->value;
                                    strcpy(dummy->text,new_text->t_text->text);
                                    strcpy(dummy->name,new_text->t_name->text);
                                    delete new_text;    //deletes the window ..
                }


         _form_def::edit_dialog(f_button *dummy)
                {
                                bttn_details *new_bttn;
                             new_bttn=new bttn_details(true);
			    new_bttn->t_x->setval(dummy->left);
                            new_bttn->t_y->setval(dummy->top);
                            new_bttn->t_w->setval(dummy->width);
                            new_bttn->t_h->setval(dummy->height);
                            new_bttn->t_c->setval(dummy->color);
                            new_bttn->t_lab->setval(dummy->label);
                            new_bttn->t_name->setval(dummy->name);

                                strcpy(new_bttn->title,"Edit Button");
                             run:
                           
                             delay(150);

                             new_bttn->run();
                              
                             if(new_bttn ->del == true)
                              	{
                            	control_list.remove((control *)dummy);
                                delete new_bttn;
                                return 1;
                              	}
                                        //        cout<<w->t1->text;

                                
                                if(new_bttn->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_bttn;
                                                                         return 1;
                                                                         }
                                
                                	if(!isvalid(new_bttn->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_bttn->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      	
                                // create the widget at the form ..
                                //bn^x^y^w^h^c^label
				 dummy->left=new_bttn->t_x->value;
                                    dummy->top=new_bttn->t_y->value;
                                    dummy->width=new_bttn->t_w->value;
                                    dummy->height=new_bttn->t_h->value;
                                   dummy->color=new_bttn->t_c->value;
                                    strcpy(dummy->label,new_bttn->t_lab->text);
                                    strcpy(dummy->name,new_bttn->t_name->text);
                         delete new_bttn;    //deletes the window ..
                }

     
        void _form_def::place(int item,point p)
                {
                delay(500);
                while(1)
                        {
                        mouse.getresponse();
                        if(mouse.btn & 1)
                             {
                             point p(mouse.x,mouse.y);
			     region form(virx,viry+15,virx+wd,viry+ht);
                             if(form.contains(p))
                                        {
                 
                             if(item == 1)
                             {
                               new_btn_diag(p);
                        break;
                        }
                        else if(item == 2)
                             {
                               new_label_diag(p);
                        break;
                        }
                        else if(item ==3)
                                {
                                new_text_diag(p);
                                break;
				}
                        else if(item ==4)
							{
							new_cbox_diag(p);
							break;
							}
						else if(item == 5)	
							{
							new_optn_diag(p);
							break; // option
							}
						else if(item == 6)	
							{
							
							if(mode == 01)
								{
								messagebox("This Works only on Background mode",MSG_ALERT);
								break;
								}
								new_frame_diag(p);
							break; // frame
							}
						else if(item == 7)
							{

							if(mode == 01)
								{
								messagebox("This Works only on Background mode",MSG_ALERT);
								break;
								}
								new_line_diag(p);
							break; // frame
							}

                                        }
                            }

                        if(mouse.btn & 2)
                                break;
                        }
		}




       _form_def::new_btn_diag(point p)
                {
                		bttn_details *new_bttn;
                             new_bttn=new bttn_details;
                              char buf[50];
                                 sprintf(buf,"%d",p.x-virx);
                                 strcpy(new_bttn->t_x->text,buf);
                                 sprintf(buf,"%d",p.y-viry-title_bar_height);
                                 strcpy(new_bttn->t_y->text,buf);
			     run:
                             new_bttn->run();
                                if(new_bttn->status == CANCEL_CWIN)
                                                                         {
                                                                         delete new_bttn;
                                                                         return 1;
									 }
                      		if(!isvalid(new_bttn->t_name->text))
                      			{
                      				sprintf(message,ln_notvalid,new_bttn->t_name->text);
									messagebox(message,MSG_ALERT);
									goto run;
                      			}
                      		if(contains(new_bttn->t_name->text))
										{
										sprintf(message,ln_cntrl_name_choosen,new_bttn->t_name->text);
										messagebox(message,MSG_INFO);
										goto run;
										}
                                bttn_handler=new f_button(new_bttn->t_name->text,str2int(new_bttn->t_x->text),
                                                                          str2int(new_bttn->t_y->text),
                                                                        str2int(new_bttn->t_w->text),
                                                                        str2int(new_bttn->t_h->text),
                                                                        9,
                                                                        str2int(new_bttn->t_c->text),
                                                                        new_bttn->t_lab->text);
                                                                                sprintf(buf,"The current Heap size is %ld",heapsize());

                                control_list.insert((control *)bttn_handler);
                         delete new_bttn;    //deletes the window ..
                           show_form();
                }

        int _form_def::draw_controls()
                {


                 int i=0;
                 setviewport(virx,viry+title_bar_height,virx+wd,viry+ht,1);
                int length = back_control_list.getsize();
                
                while(i<length)
                        {
                        control_handler=back_control_list.getitem(i+1);
                        switch(control_handler->type)
                                {
                                case C_FRAME:
                                        ((f_frame*)control_handler)->draw();
                                        
                                break;
                                case C_LINE:
					((f_line*)control_handler)->draw();
                                break;
                                
                                }
                        i++;
                        }
               
				i=0;
				length = control_list.getsize();
			
		
				while(i<length)
				
                        {
                        control_handler=control_list.getitem(i+1);
                        switch(control_handler->type)
                                {
                                case C_BUTTON:
           							                 
                                        bttn_handler=(f_button *)control_handler;
                                       bttn_handler->draw();
                                    
                                break;
                                case C_LABEL:
										lab_handler=(f_label *)control_handler;
                                        lab_handler->draw();
                                break;
                                case C_CBOX:
										cbox_handler=(f_cbox *)control_handler;
                                        cbox_handler->draw();
								break;
                                case C_TEXTBOX:
                                        tb_handler=(f_textbox *)control_handler;
                                        tb_handler->draw();
                                break;
                                case C_OPTION:
                                       option_handler=(f_option *)control_handler;
                                       option_handler->draw();
                                break;
                                }
                        i++;
                        }
                setviewport(0,0,getmaxx(),getmaxy(),1);
                
               
                }



void _form_def::show_form()
        {
		
		if(changed)
		{
	
		changed = false;
        int dec=2;
        clearclient();
        gdriver.draw_3dbar(virx,viry,wd,ht,bgcolor,15,1,dec,-1);
        gdriver.draw_bar(virx+dec+1,viry+dec,wd-dec-3,15,1,1);
        mouse.hide();
                 settextjustify(CENTER_TEXT,RIGHT_TEXT);
                 setcolor(15);
                 settextstyle(0,0,1);
                 /* for title adjustment */
                 char _title[50];
                 strcpy(_title,title);
                 if(textwidth(title)>wd)
			{
                         _title[wd/(textwidth(_title)/strlen(_title)+1)]='\0';
                        }
                 gdriver.draw_bar(virx+wd-15,viry+dec+3,8,10,10,0);
                 setcolor(15);
                 outtextxy((2*virx+wd)/2,viry+dec+3,_title);
                settextjustify(LEFT_TEXT,TOP_TEXT);
             
gdriver.savescreen(virx,viry,virx+wd,viry+ht,_form_pic);
        draw_controls();  
        mouse.show();
        }
        else
        {
        // simply restore it ... 
        gdriver.restorescreen(virx,viry,virx+wd,viry+ht,_form_pic);
        draw_controls();
                }  
        showstatus();
        }
