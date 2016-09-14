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
#define ln_cntrl_name_choosen  "Control name \' %s \' has already been choosen ! "
#define ln_notvalid "The name \' %s \' is not a valid one ! "
#define _form_pic "form.scr"
#define CNTRL_ITEMS 7
static char message[130];
static class  _form_def
        {
        public:
        int x,y;
        int mode;   //01 f , 10 -b
        int virx,viry;
        int wd,ht;
        char title[50];
        char name[50];
      	 int index;
        int changed;
        int loaded;
        int bgcolor;
              /* Control List */
        llist <control *> control_list;
        llist <control *> back_control_list;
        f_button *bttn_handler;
        f_textbox *tb_handler;
        f_label *lab_handler;
        f_frame *frame_handler;
        f_cbox *cbox_handler;
        f_option *option_handler;
        f_line *line_handler;
        control *control_handler;
void showstatus();
_form_def()
		{
		loaded = false;
		}
        void init_form()
        {
        mode = 01;   
        changed =true;
        index=-1;
	virx=x+86;
	viry=y+42;
        bgcolor = 5;
        loaded =true;
        showstatus();
        }
        void kill()

                {
            
                loaded=false;
                remove(_form_pic);
                control_list.killall();
                back_control_list.killall();    
              
                }
        void place(int,point);
        void show_form();
        int draw_controls(); 
	 	contains(int);
		contains(char *);
	 save_form(char *);
	 load_form(char *);
	 findobject_no(int [CNTRL_ITEMS]);

	 edit_form();          // = Todo : add an edit form window :x
         edit_dialog(f_button *);
     	 edit_dialog(f_label *);
     	 edit_dialog(f_frame *);
         edit_dialog(f_textbox *);
	 	 edit_dialog(f_cbox *);
	   	 edit_dialog(f_option *);
   	  	 edit_dialog(f_line *);
	  	 new_cbox_diag(point);
	  	 new_optn_diag(point);
         new_btn_diag(point);
         new_label_diag(point);
         new_frame_diag(point);
         new_text_diag(point);
         new_line_diag(point);
        int right_clicked(_mouse);
	}form_def;





