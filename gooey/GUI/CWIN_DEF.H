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
     cwin::cwin()
	{
	dec=2;
	x=100;
	y=100;
	width=200;
	height=200;
	bgcolor=5;
	forecolor=0;
	fontsize=1;
	fontstyle=0;
	strcpy(title," Unamed Form ");

	}

     int cwin::interupt(_mouse m)    // calling with  viewport
	{
	if(m.btn &1)
		{
		// close bttn
		struct viewporttype viewinfo;
		getviewsettings(&viewinfo);
		setviewport(0,0,getmaxx(),getmaxy(),1);

		region r(x+width-15,y+dec+3,x+width-15+8,y+dec+3+10);
		point p(m.x,m.y);
		if(r.contains(p))
		  {
		 gdriver.draw_bar(x+width-title_bar_height,y+dec+3,8,10,4,10);

		 while(mouse.isclicked(1));
		  delay(50);
				 p.setval(mouse.x,mouse.y);
				if(!r.contains(p))
			      {
		       gdriver.draw_bar(x+width-title_bar_height,y+dec+3,8,10,10,0);
		       return OK;
			      }


			    return CANCEL_CWIN;


		  }  
		  // restoring viewport ..
		 setviewport(viewinfo.left,viewinfo.top,viewinfo.right, viewinfo.bottom,viewinfo.clip);
		 // no other work todo goto the control list interupt;

		//setting theviewport
		setviewport(x,y+title_bar_height,x+width,y+height,1);
		control *dummy;
		int count=control_list.getsize() + 1;
		int n=0,code;

		while(n<count)
			{
			dummy=control_list.getitem(n);
			  region r2(dummy->getx(),dummy->gety(),dummy->getx()+dummy->width,dummy->gety()+dummy->height);
			  if(r2.contains(p))
			       {
				code=dummy->interupt(m);
				if(code != NO_INTR)
				return code;
				
				}
			n++;
			}   //end of while

		
		}

	}

     void cwin::attach(control *ctrl,int list)
	{
	if(list == FRONT)
		{
		control_list.push(ctrl);
		ctrl->initvalby(this);
		}
	else if (list == BACK)
		{
		control_list_back.push(ctrl);
		ctrl->initvalby(this);
		}
	}

     int cwin::kill()
			{
		control *dummy;
		int count=control_list_back.getsize() + 1;
		int n=0;
		/* delete back items */
		while(n<count)
		{
		dummy=control_list_back.getitem(n);
		if(dummy)
		delete dummy;
		n ++;
		}

		count=control_list.getsize() + 1;
		n=0;
		/* delete front items */
		while(n<count)
		{
		dummy=control_list.getitem(n);
		if(dummy)
		delete dummy;
		n ++;
		}


	       }
void cwin::paint(int t)
	{
		 mouse.hide();
		 gdriver.draw_3dbar(x,y,width,height,bgcolor,15,t,dec);
		 int x2=x+width;
		 gdriver.draw_bar(x+dec+1,y+dec,width-dec-3,title_bar_height,1,1);
		 settextjustify(CENTER_TEXT,RIGHT_TEXT);
		 setcolor(15);
		 settextstyle(fontstyle,0,fontsize);
		 /* for title adjustment */
		 char _title[50];
		 strcpy(_title,title);
		 if(textwidth(title)>width)
			{
			 _title[width/(textwidth(_title)/strlen(_title)+1)]='\0';
			}
		 gdriver.draw_bar(x+width-title_bar_height,y+dec+3,8,10,10,0);
		 setcolor(15);
		 outtextxy((x+x2)/2,y+dec+3,_title);

		 settextjustify(LEFT_TEXT,TOP_TEXT);
  		 setviewport(x,y+title_bar_height,x+width,y+height,1);
		 control *dummy;

		 int count=control_list_back.getsize() + 1;
		 int n=0;

		 /* drawing the backgroud items */
		 while(n<count)
		 {
		 dummy=control_list_back.getitem(n);
		 dummy->draw(1);
		 n ++;
		 }

		 /* drawing the front items */
		 count=control_list.getsize() + 1;
		 n=0;
		 while(n<count)
		 {
		 dummy=control_list.getitem(n);
		 dummy->draw(1);
		 n ++;
		 }
		 handle_onload();
		 setviewport(0,0,getmaxx(),getmaxy(),1); 
   		 mouse.show();
		 //screen=save_screen();
	}

int cwin::run()
	{
		char buf[80];
		mouse.show();
		struct viewporttype viewinfo;
		getviewsettings(&viewinfo);
		setviewport(0,0,getmaxx(),getmaxy(),1);
		int method;
		method=gdriver.savescreen(x,y,x+width,y+height);
		if(!method)
		gdriver.savescreen();
		paint(1);
		event_handler.attach(this);
		sprintf(buf,"The current Heap size is %ld",heapsize());
			dog("Event Handler Attaching ");
			dog(buf);
		int retcode= event_handler.event();
		setviewport(0,0,getmaxx(),getmaxy(),1);
		
		if(method)
		gdriver.restorescreen(x,y,x+width,y+height);
		else
		gdriver.restorescreen();

		setviewport(viewinfo.left,viewinfo.top,viewinfo.right, viewinfo.bottom,viewinfo.clip);
		return retcode;
	}
