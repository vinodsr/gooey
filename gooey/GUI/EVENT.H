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
   Name:  event.h
   Date: 07/08/05 11:14 a
   Description: Event handling class
 */
	class _event_handler
		{

		int type;
		int code;
		int x,y;

		stack <cwin *> _cwin_stack;
		public:
		int ret_code;
			_event_handler ()
				{
				type=code=x=y=0;
				}


			attach(cwin * p)
				{
				_cwin_stack.push(p);
				}

			event()
				{
				
				
				_get_event:
				
				// To remove unwanted keystrokes;
				while(kbhit())
				   getch();
				   
				while(!kbhit())
					{
					mouse.getresponse();
					if(mouse.btn & 1)
						{
						ret_code=_cwin_stack.gettop()->interupt(mouse);
						switch(ret_code)
							{

							case UNLOAD_CWIN:
							case CANCEL_CWIN:
								cwin *dummy;
								_cwin_stack.pop(dummy);
								dummy->handle_onclose();
								dummy->status=ret_code;
								return EXIT_SUCESS;
							}
						}
					else if(mouse.btn & 2)
					{    // Quick Exit mode 
					      
					     gdriver.unload();
					     exit(0);
					}
					else
						_cwin_stack.gettop()->interupt(mouse);
					}
					// For key response;

					code=getch();     //clear buffer
					if(code == 27 )
					{
					cwin *dummy;
					_cwin_stack.pop(dummy);
					dummy->status=CANCEL_CWIN;
					return EXIT_SUCESS;
					}
					goto _get_event;
				}

		}event_handler;
