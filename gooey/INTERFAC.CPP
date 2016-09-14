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
 #include <alloc.h>
 #include "menu_def.h"
 #include "interfac.h"

 #include "./gui/header.h"
 #include "./gui/def.h"
 #include "./gui/mouse.h"
 #include "./gui/funcs.h"
 extern int option;
  extern int useroption;

  void clearclient()
	{
	mouse.hide();
	setfillstyle(1,0); //fills black ..
	bar(86,42,getmaxx()-1,getmaxy()-20);
	mouse.show();
	}

void draw_bar_anim(int x,int y,int w,int h,int c,int b)
{

mouse.hide();
setfillstyle(1,c);

int i;
sound(1500);
for(i=0;i<=h;i+=15)
	{
	bar(x,y,x+w,y+i);
	delay(50);
	}
nosound();
setcolor(b);
rectangle(x,y,x+w,y+h);
mouse.show();
}

void draw_horizon(int x,int y,int w,int h,int c,int b)
{
mouse.hide();
setfillstyle(1,c);
bar(x,y,x+w,y+h);
setcolor(b);
rectangle(x,y,x+w,y+h);
mouse.show();
}


void set_status(char *status)
{
int y=getmaxy()-20;
draw_horizon(1,y,getmaxx()-2,getmaxy(),7);
mouse.hide();
setcolor(0);
outtextxy(10,y+10,status);
mouse.show();
}


void draw_horizon_sel(int x,int y,char hmenu[20][20],int n)
	{
		draw_horizon(1,y,getmaxx()-2,20,7);
		int sx=x;
		mouse.hide();
		for(int i=0;i<n;i++)
			{

			if(hoption-1 != i)
				{

				 setcolor(4);
				 outtextxy(sx,y+10,hmenu[i]);
				 sx+=strlen(hmenu[i])*8;
				}

			else
				{
				draw_horizon(sx,y,strlen(hmenu[i])*8,20,2);
				setcolor(0);
				outtextxy(sx,y+10,hmenu[i]);
				sx+=strlen(hmenu[i])*8;
				}
			}
			mouse.show();

	}

void draw_vert_sel(int sx,int dupy,int max,int l,char vmenu[][20],int n)
	{
		draw_horizon(sx,dupy,max,l,7);
		mouse.hide();
		 for(int i=0;i<n;i++)
		 {
		 if(voption -1 == i)
			{
			draw_horizon(sx,dupy,max,15,2);
			setcolor(0);
			outtextxy(sx,dupy+5,vmenu[i]);
			}
			else
			{
		   setcolor(4);
		  outtextxy(sx,dupy+5,vmenu[i]);
			}
			dupy+=15;
		 }

		 mouse.show();
	}
int draw_horizon_menu(int x, int y,char hmenu[20][20],int n)
	{
	draw_horizon(1,y,getmaxx()-2,20,7);
	int sx=x,ch=0;
	mouse.hide();
	for(int i=0;i<n;i++)
	 {
	   if(hoption == i+1)
		{
	draw_horizon(sx,y,strlen(hmenu[i])*8,20,2);

	setcolor(0);
	outtextxy(sx,y+10,hmenu[i]);
	sx+=strlen(hmenu[i])*8;
		 }
	else
	{

	    setcolor(4);
	    outtextxy(sx,y+10,hmenu[i]);
	    sx+=strlen(hmenu[i])*8;
	 }

	 }

	 top:
	 mouse.show();

	 if(!kbhit())
		{

		mouse.getresponse();
		if(mouse.btn & 1)
			{
			if(mouse.x>x && mouse.x<getmaxx() && mouse.y>y && mouse.y<y+20)
				{
				int tx=x;
				for(i=0;i<n;i++)
					{
					if(mouse.x>tx && mouse.x<(tx+strlen(hmenu[i])*8))
					{
						hoption=i+1;
						draw_horizon_sel(x,y,hmenu,n);
						ch=13;
						delay(150);
						return hoption;
					}
					tx+=strlen(hmenu[i])*8;
					}

				}
			}// end of if

		}// kbhit end
	 //
	 key:
	 	if(kbhit())
	 	{
			ch=getch();
			
		if(ch == 13 || ch == 80)
			{
			return hoption;
			}
		else if(ch == 75)
			{
			 if(--hoption <1)
				hoption = hcount;
			}
		else if(ch == 77)
			{
			 if(++hoption >hcount)
				hoption = 1;
			
			}

	
	draw_horizon_sel(x,y,hmenu,n);
	}
		goto top;
	}


	int display_vmenu(char hmenu[20][20],int option,char vmenu[10][20],int n)
		{
		int ch=0;
		int max=0;
			voption=1;
		for(int i=0;i<n;i++)
			{
			if(max<strlen(vmenu[i]))
			 max=strlen(vmenu[i]);
			}
			max*=8;

		int l=0;
		for(i=0;i<n;i++)
		l++;

		l*=15;

		int sx=10;
		for(i=0;i<option-1;i++)
			{
			sx=sx+ strlen(hmenu[i])*8;
			}
		 int dupy=40;
//		draw_horizon(sx,dupy,max,l,7);

		// saving the current screen below the menu ..
		void far *s_menu;
		s_menu = farmalloc(imagesize(sx,dupy,sx+max,dupy+l));
		mouse.hide();
		getimage(sx,dupy,sx+max,dupy+l,s_menu);
		mouse.show();
	draw_vert_sel(sx,dupy,max,l,vmenu,n);

		 top:
		 dupy=40;
		  mouse.show();
		 while(!kbhit())
		{

		mouse.getresponse();
		if(mouse.btn & 1)
			{

			if(mouse.x>sx && mouse.x<sx+max && mouse.y>dupy && mouse.y<dupy+l)

				{
				int ty=dupy;
				for(i=0;i<n;i++)
					{
					if(mouse.y>ty && mouse.y<(ty+15))
					{
						voption=i+1;
						ch=13;
						draw_vert_sel(sx,dupy,max,l,vmenu,n);
						delay(100);

						goto key;
					}
					ty+=15;
					}

				}
				ch=13;
				voption=-1;
				//delay(20);
				goto key;
			}// end of if

		}// kbhit end


		ch=getch();
		key:
		if(ch == 13)
			{
			dupy=40;
		   //	draw_horizon(sx,dupy,max,l,0);
		   // restoring the screen
		   mouse.hide();
		   putimage(sx,dupy,s_menu,COPY_PUT);
		   farfree(s_menu);
		   
		   mouse.show();

			return voption;
			}
		else if(ch==27)
			{
			dupy=40;
			  mouse.hide();
		   putimage(sx,dupy,s_menu,COPY_PUT);
		   farfree(s_menu);
		   
		   mouse.show();
			return -1;
			}
		else if(ch == 72)
			{
			 if(--voption <1)
				voption = n;
			}
		else if(ch == 80)
			{
			 if(++voption >n)
				voption = 1;
			}

			draw_vert_sel(sx,dupy,max,l,vmenu,n);
		  goto top;

		}





  void draw_menu(int x, int y,char hmenu[20][20],int n) {
	draw_horizon(1,y,getmaxx()-2,20,7);
	int sx=x,ch=0;
	mouse.hide();
	for(int i=0;i<n;i++)
	 {
	   if(hoption == i+1)
		{
	draw_horizon(sx,y,strlen(hmenu[i])*8,20,2);

	setcolor(0);
	outtextxy(sx,y+10,hmenu[i]);
	sx+=strlen(hmenu[i])*8;
		 }
	else
	{

	    setcolor(4);
	    outtextxy(sx,y+10,hmenu[i]);
	    sx+=strlen(hmenu[i])*8;
	 }

	 }

	 top:
	 mouse.show();
 set_status(" Use Arrow keys to Navigate | Enter - Select MENU  ");
  }
  void activate_menu()
	{
clearipbuffer();
 set_status(" Use Arrow keys to Navigate | Enter - Select MENU  ");
  option=draw_horizon_menu(10,20,h_menu,hcount);

  if(option==1)
	{
	set_status(" Create , Open , Save a Form ");
	useroption=display_vmenu(h_menu,option,v_menu1,vcount1);
	}
  else   if(option==2)
	{
	set_status(" Change Views for Form ");
	useroption=display_vmenu(h_menu,option,v_menu2,vcount2);
	}
  else   if(option==3)
	{
	set_status(" More Tools  ");
	useroption=display_vmenu(h_menu,option,v_menu3,vcount3);
	}
  else   if(option==4)
	{
	set_status(" Generate /  Preview Code  ");
	useroption=display_vmenu(h_menu,option,v_menu4,vcount4);
	}
  else   if(option==5)
	{
	set_status(" More Tools  ");
	useroption=display_vmenu(h_menu,option,v_menu5,vcount5);
	}	

	}

