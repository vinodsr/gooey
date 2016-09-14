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
#define true 1
#define false 0
/* general debug info */

static int DEBUG_ON=false;
static int _id=1010;


#define auto_id _id++
#define DRAW true
#define UNLOAD_CWIN 1001
#define UNLOAD_PLAT 1002
#define CANCEL_CWIN 1003
#define NO_INTR 1005

#define EXIT_SUCESS 1111
#define EXIT_FAIL 0000
#define OK 	  1010

/* For control names / types */
#define C_BUTTON 500
#define C_TEXTBOX 501
#define C_LABEL	502
#define C_CBOX 503
#define C_OPTION 504
#define C_FRAME 505
#define	C_LINE 	506

/* For CWin title bar */
#define title_bar_height 15

/* for control classes */
#define BUTTON 2000

