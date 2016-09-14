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

 #include "gui/gui_clas.h" 
//TODO : Add your header files 

 // The window class 

 class _form1:public cwin
  { 
   public :
   button *B_ok;
   label *L_name;
   textbox *T_name;

  /* The constructor */ 
  _form1()
  { 

  /* Initializing cwin attribute(s) */
   x = 186;
   y = 140;
   width = 200;
   height = 150;
   strcpy(title,"Input data");

  /* Initailizing controls */ 
   B_ok = new  button (77,86,50,20," OK ",9,0);
    attach(B_ok);
   L_name = new  label (30,40,60,20,"Name :"); 
    attach(L_name);
   T_name = new  textbox (100,40,90,20,"name"); 
    attach(T_name);


  } 

  int handle_event_onclick(object *obj)
  { 
   /* the return values are UNLOAD_CWIN --> Unloads the window 
                            CANCEL_CWIN -->   "         "  ;
				 but status is CANCEL_CWIN (wind->status) 
				 OK         --> simply return (no action on window)*/
   if( obj == B_ok)
      {        /* Do Operations for onclick() of control B_ok*/
      return UNLOAD_CWIN;
      }
  } 

// Event handling ended ... 
  }; //end of class
   /* Main(Display) function*/ 

  int main () 
  { 
   gdriver.init();
	gdriver.usepalette();
   _form1 *form1;
   form1 = new _form1;
   form1->run();
   delete form1;
   gdriver.unload();
   return 0;
  } 
