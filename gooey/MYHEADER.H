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
   Name:  myheader.h
   Date: 24/09/05 15:20
   Description: for including my  header files*/


 int i,j;

#include "new_btn.h"
#include "new_lab.h"
#include "new_txt.h"
#include "new_cb.h"
#include "new_frm.h"
#include "new_opt.h"
#include "new_line.h"


#include "abt_dlg.h"

#include "f_bttn.cpp"
#include "f_cbox.cpp"
#include "f_label.cpp"
#include "f_tbox.cpp"
#include "f_frame.cpp"
#include "f_option.cpp"
#include "f_line.cpp"
 int option=0;
 int useroption=0;

#include "menu_def.h"
#include "interfac.h"

#include "form_def.h"


#include "toolbox.h"
#include "con_list.h"

#include "gen_code.h"

#include "getarea.h"
#include "FBrowser.h"
#include "gen_form.h"




#include "new_wind.cpp"

void place_on_form(int i,point o)
	{
		form_def.place(i,o);
	}
int copyfile(char *src,char *dest)
{
	FILE *ptr1,*ptr2;
	ptr1=fopen(src,"rb");
	ptr2=fopen(dest,"wb");
	while(!feof(ptr1))
		{
		putc(getc(ptr1),ptr2);
		}
	fclose(ptr1);
	fclose(ptr2);

}

int exists(char *fname)
	{
	FILE *ptr1;
	ptr1=fopen(fname,"r");
	if(ptr1 == NULL)
		return 0;
	
	fclose(ptr1);
	return 1;
	}
	
	
