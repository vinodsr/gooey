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

 class _abt_dlg:public cwin
  { 
   public :

   label *l_about;
   button *b_ok;
   int handle_onload()
   	{
   	outtextxy(5,190,"Website : http://busytalk.com/gui");
   	}
  int handle_event_onclick(object *obj)
	{
	return UNLOAD_CWIN;
	}
  /* The constructor */ 
  _abt_dlg()
  { 

  /* Initializing cwin attribute(s) */
   x = 100;
   y = 100;
   width = 300;
   height = 250;
   strcpy(title,"About Us ");

  /* Initailizing controls */
   l_about = new  label (5,48,200,20,"Miniproject by");


    attach(l_about);
     attach(new label(45,70,190,20,"Vinod S R and Suraj R"));
   attach(new label(65,100,100,20,"(c) 2005"));
   
   b_ok = new  button (225,49,50,20,"Ok");
    attach(b_ok);


  } 
  };   /* Main function*/ 

  static void show_about_dlg()
  { 
   _abt_dlg *abt_dlg;
   abt_dlg = new _abt_dlg;
   abt_dlg->run();
   delete abt_dlg;
  }
