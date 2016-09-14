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

#include <iostream.h>

#include<graphics.h>
#include<string.h>
#include <conio.h>
#include <direct.h>
#include <stdio.h>
#include<dos.h>
#include<dir.h>
#include<alloc.h>
#include <stdlib.h>
#include "Xmouse.h"
#include "./gui/pre_hed.h"
#include "FBrowser.h"
FileBrowser::FileBrowser(char *fn,char *d,int x1,int y1,int x2,int y2)
	{
	
	
	dir=d;
	strcpy(dir,"");
	fname=fn;
	strcpy(fname,"");
	strcpy(ok_message," Open ");
	
	X1=x1;
	X2=x2;
	Y1=y1;
	Y2=y2;

	statusx=x1+1;
	statusy=y2-22;
	drv_x1 = x1+10;
	drv_y1 = y1+50;
	drv_x2 = drv_x1+90;
	drv_y2 = y2-30;
	open_x1=drv_x2+10;
	open_x2=open_x1+200;
	open_y1=y1+50;
	open_y2=open_y1+15;
	
	dir_x=X1+100;
	dir_y=Y1+19;
	
	file_x1 = drv_x2+10;
	file_y1 = y1+70;
	file_x2 = x2-10;
	file_y2 = y2-80;
	
	tb_x=drv_x2+140;
	tb_y=file_y2+10;
	
	max_files = ((file_x2-file_x1)/125)*((file_y2-file_y1)/15)-2;
	
//	St_Page=1;


	tdl_itemno=0;
	}

void FileBrowser::update_dir()
	{
	getcwd(dir,MAXPATH);
	setfillstyle(1,7);
	bar(dir_x,dir_y,X2-20,dir_y+20);
	setcolor(0);
	outtextxy(dir_x+5,dir_y+10,dir);
	}
int FileBrowser::show (int type,_gdriver *gd)
	{
	
	
	if(type == 0)
		{
	strcpy(ok_message," Open ");
	strcpy(title," Open a File ");
		}
	else
		{
	strcpy(ok_message," Save ");
	strcpy(title," Save a File ");
		}
	if(gd)
	gd->savescreen_up(X1,Y1,X2,Y2);
	Init();
   	InitMainDialog();
 	int retcode = Trace_Mouse_Keyboard();
   	Close();
	if(gd)
 	gd->restorescreen_up(X1,Y1,X2,Y2);

	mouse.show();
    
    
	return retcode;
	}
FileBrowser::Trace_tbox()
	{
	
	int i=0;
    
    
if(Detect_Left_Click())
	{
	Detect_Mouse_Movement();
    if(moux>tb_x && mouy>tb_y && moux<tb_x+100 && mouy<tb_y+20)
    	{
    	char ch;
	
		Hide_Pointer();
		setcolor(0);
		char *_fname,*temp;
		_fname=new char[256];
		temp = new char[256];

		strcpy(temp,fname);
		strcpy(fname,"");
		update_tbox(10);
		fname[0] = char(9);
		fname[1] = '\0';
		

		int index=0;
		int noc=12;
		while( (noc!=0) && (ch=getch()) !=13 )
			{
			if(ch != 8 ) //not a backspace
				{
				if(ch == 27)
					{
				       strcpy(fname,temp);
				       break;
				       //	continue;
					}
				else{

				*(_fname+index)=ch;
				index++;
				--noc;
				     }
				}

			else       // backspace
				{
				if(index)   // if no char
							{
								noc++;
								index--;
							}
				else
					{
					sound(650);
					delay(500);
					nosound();
					}

				}

			*(_fname+index)='\0';
			strcpy(fname,_fname);
			if(noc  !=0)
			{
			fname[index]=char(9);
			fname[index+1]='\0';
			update_tbox(10);
			}
    	}
    	if(fname[index] == char(9))
			fname[index] = '\0';
   		update_tbox();
    	Show_Mouse_Pointer();
    	return 1;

    	}
    

    	}

	}
void FileBrowser::update_tbox(int bgcolor)
	{
	List_Box(tb_x,tb_y,tb_x+100,tb_y+15,bgcolor);
	setcolor(0);
	outtextxy(tb_x+5,tb_y+5,fname);
	


	}





int FileBrowser::GetKey()
{
 union REGS i,o;
 i.h.ah=0;
 int86(22,&i,&o);
 return(o.h.ah);
}

void FileBrowser::Get_Drives()
{
 int i,j=0,disk;
 disk = getdisk();
 Drive_Count = 0;
 for(i=0;i<26;i++)
 {
   setdisk(i);
   if(i == getdisk())
   {
     Num_Drives[j] = (i+'A');
     j++;
     Drive_Count++;
   }
   else
    {
    Num_Drives[j]=(i+'A');
    j++;
    }
 }
 setdisk(disk);
}

void FileBrowser::Get_Drive_Data(int Drv_Letter)
{

  int Drv,done,Name_Len;
  struct ffblk ffblk;
  char Tmp[15],Tmp2[5],Tmp3[5];
  Drv = Drv_Letter + 1;
  File_Count = Dir_Count = 0;
  if(_chdrive(Drv) == 0)
  {

    done = findfirst("*.*",&ffblk,FA_DIREC | FA_ARCH);
    while (!done)
    {
	Name_Len = strlen(ffblk.ff_name);
	if(Name_Len >= 5)
	{
	 strcpy(Tmp,ffblk.ff_name);
	 strrev(Tmp);
	 strncpy(Tmp2,Tmp,4);
	 Tmp2[4] = '\0';
	}
	if(ffblk.ff_attrib == FA_DIREC)
	{
	  Icon[File_Count] = 'D';
	  Dir_Count++;
	}
	else if(strcmp(Tmp2,"EXE.") == 0)
	  Icon[File_Count] = 'E';
	else
	  Icon[File_Count] = 'F';

	strcpy(Tmp,ffblk.ff_name);
	Files[File_Count] = strdup(Tmp);
	done = findnext(&ffblk);
	File_Count++;
    }
  }
  if(File_Count > max_files)
  {

   Page_Found = 1;
  }
}

void FileBrowser::Init()
{
 Disk = getdisk();
 getcwd(Def_Dir,MAXPATH);
 Page_Found = Page = 0;
 TFL_Tmpno = -1;
 H_x = H_y = Open_Dir = 0;
 Init_Mouse();
}

void FileBrowser::Close()
{
 setdisk(Disk);
 chdir(Def_Dir);

}

void FileBrowser::InitScreen()
{

}

void FileBrowser::LinedX(int x,int y,int x1,int y1)
{
  setcolor(8);
  line(x,y,x1,y1);
  setcolor(15);
  line(x,y+1,x1,y1+1);
}

void FileBrowser::LinedY(int x,int y,int x1,int y1)
{
  setcolor(8);
  line(x,y,x1,y1);
  setcolor(15);
  line(x+1,y,x1+1,y1);
}

void FileBrowser::Button(int x,int y,int x1,int y1,char Caption[50],int def)
{
  setcolor(7);
  rectangle(x,y,x1,y1);
  setfillstyle(1,7);
  floodfill(x+2,y+2,7);
  setcolor(15);
  line(x,y,x1,y);
  line(x,y,x,y1);
  setcolor(8);
  line(x,y1,x1,y1);
  line(x1,y,x1,y1);
  setcolor(8);
  rectangle(x-1,y-1,x1+1,y1+1);
  setcolor(8);
  outtextxy( ((x+x1)/2) - (strlen(Caption) * 4 ) + 1,((y+y1)/2)-3,Caption);
  if(def == 1)
  {
   setlinestyle(DOTTED_LINE,1,1);
   rectangle(x+3,y+3,x1-3,y1-3);
   setlinestyle(SOLID_LINE,1,1);
  }
}

void FileBrowser::Down_Button(int x,int y,int x1,int y1)
{
  setcolor(8);
  line(x,y,x1,y);
  line(x,y,x,y1);
  setcolor(15);
  line(x,y1,x1,y1);
  line(x1,y,x1,y1);
  delay(150);
  while(Detect_Left_Click() & 1) ;
  setcolor(15);
  line(x,y,x1,y);
  line(x,y,x,y1);
  setcolor(8);
  line(x,y1,x1,y1);
  line(x1,y,x1,y1);
}

void FileBrowser::Draw_Icon(int x,int y,int Type)
{
  if(Type == ICON_DRIVE)
  {
    setcolor(7);
    setfillstyle(1,7);
    bar(x,y,x+20,y+10);
    setcolor(15);
    line(x,y,x+20,y);
    line(x,y,x,y+10);
    setcolor(8);
    line(x,y+10,x+20,y+10);
    line(x+20,y,x+20,y+10);
    setcolor(8);
    rectangle(x-1,y-1,(x+20)+1,(y+10)+1);
    putpixel((x+20)-2,y+3,2);
    putpixel((x+20)-3,y+3,10);
    putpixel((x+20)-5,y+3,2);
    putpixel((x+20)-6,y+3,10);
    putpixel((x+20)-7,y+3,2);
    LinedX(x+2,y+6,(x+20)-2,y+6);
  }
  if(Type == ICON_FOLDER)
  {
    setcolor(8);
    setfillstyle(1,14);
    bar3d(x,y,x+12,y+8,0,0);
    setcolor(7);
    line(x+1,(y+8)-1,(x+12)-1,(y+8)-1);
    setcolor(14);
    line(x+1,y-3,x+5,y-3);
    line(x,y,x+1,y-3);
    line(x+5,y-3,(x+5)+3,y);
    setfillstyle(1,14);
    floodfill(x+2,y-2,14);
    setcolor(8);
    line(x+1,y-3,x+5,y-3);
    line(x,y,x+1,y-3);
    line(x+5,y-3,(x+5)+3,y);
    line(x,y,(x+12)-1,y);
  }
  if(Type == ICON_FILE)
  {
    setcolor(8);
    setfillstyle(1,15);
    bar3d(x,y,x+12,y+8,0,0);
    rectangle((x+12)-3,y,(x+12),y+3);
    setcolor(15);
    line((x+12)-2,y,(x+12),y);
    line((x+12),y,(x+12),y+2);
    setcolor(8);
    line((x+12)-2,y,(x+12),y+2);
  }
  if(Type == ICON_FILE_EXE)
  {
    setcolor(8);
    setfillstyle(1,15);
    bar3d(x,y,x+12,y+8,0,0);
    setcolor(9);
    setfillstyle(1,9);
    bar3d(x,y,x+12,y+3,0,0);
  }
  if(Type == ICON_TITLEBAR)
  {
    setcolor(15);
    setfillstyle(1,15);
    bar3d(x,y,x+12,y+8,0,0);
    setcolor(9);
    setfillstyle(1,9);
    bar3d(x,y,x+12,y+3,0,0);
  }
  setcolor(8);
}

void FileBrowser::Window(int x,int y,int x1,int y1,char Title[50],int iconinfo)
{
  setcolor(7);
  rectangle(x,y,x1,y1);
  setfillstyle(1,7);
  floodfill(x+2,y+2,7);
  setcolor(15);
  line(x,y,x1,y);
  line(x,y,x,y1);
  setcolor(8);
  line(x,y1,x1,y1);
  line(x1,y,x1,y1);
  setcolor(1);
  setfillstyle(1,1);
  rectangle(x+1,y+1,x1-2,y+15);
  floodfill(x+3,y+3,1);
  if(iconinfo == 0)
  {
   setcolor(15);
   outtextxy(x+4,y+5,Title);
  }
  else
  {
   setcolor(15);
   outtextxy(x+22,y+5,Title);
   Draw_Icon(x+4,y+4,iconinfo);
  }
}

void FileBrowser::Status_Bar(int x,int y,int x1,int y1,char Caption[50],int redraw)
{
  if(redraw == REDRAW)
  {
   setcolor(7);
   setfillstyle(1,7);
   bar(x,y,x1,y1);
  }
  setcolor(8);
  line(x,y,x1,y);
  line(x,y,x,y1);
  setcolor(15);
  line(x1,y,x1,y1);
  line(x,y1,x1,y1);
  setcolor(8);
  settextstyle(0,0,0);
  outtextxy(x+5,((y+y1)/2) - 3,Caption);
  settextstyle(0,0,0);
}

void FileBrowser::List_Box(int x,int y,int x1,int y1,int bgcolor)
{
  setcolor(15);
  setfillstyle(1,bgcolor);
  bar(x,y,x1,y1);
  setcolor(8);
  line(x,y,x1-1,y);
  line(x,y,x,y1-1);
  LinedY(x1+3,y,x1+3,y1+2);
  LinedX(x,y1+2,x1+4,y1+2);
}

void FileBrowser::Drive_List_Box(int x,int y,int x1,int y1,char item[50],
		    int count,int icon)
{
  int i,t_x,t_y;
  char temp[50];
  List_Box(x,y,x1,y1);
  t_y = y+20;

  for(i=0;i<count;i++)
  {
//  if(item[i] != 0)
  {
   sprintf(temp,"%c:",item[i]);
   Draw_Icon(x+20,(t_y)-2,icon);
   outtextxy(x+50,t_y,temp);
   t_y+=25;
  }
  }
}

void FileBrowser::File_Show_List(int x,int y,int x1,int y1,int start_count,int end_count)
{
  int i,j=0,t_x,t_y;
  char temp[50];
  setcolor(15);
  setfillstyle(1,15);
  bar(x+1,y+1,x1-1,y1-1);
  setcolor(8);
  t_x = x;
  t_y = y+8;
  for(i=start_count;i<end_count;i++)
  {
   strcpy(temp,Files[i]);
   if(Icon[i] == 'F')
    Draw_Icon(t_x+3,(t_y)-2,ICON_FILE);
   else if(Icon[i] == 'E')
    Draw_Icon(t_x+3,(t_y)-2,ICON_FILE_EXE);
   else if(Icon[i] == 'D')
    Draw_Icon(t_x+3,(t_y)-2,ICON_FOLDER);
   outtextxy(t_x+19,t_y,temp);
   t_y+=15;
   j++;
   if(j>=(file_y2-file_y1)/15 -1)
   {
    t_y = y+8;
    t_x+=125;
    j=0;
   }
  }
}

void FileBrowser::Highlight_Item_DLB(char item[50],int itemno,int icon,
			int bkcolor,int textcolor)
{
  int i,x=drv_x1,t_y=drv_y1+20;
  char temp[50];
  for(i=0;i<Drive_Count;i++)
  {
   if(i == itemno)
   {
     sprintf(temp,"%c:",item[i]);
     setcolor(bkcolor);
     setfillstyle(1,bkcolor);
     bar(drv_x1+15,t_y-7,drv_x2-25,t_y+14);
     Draw_Icon(x+20,(t_y)-2,icon);
     setcolor(textcolor);
     outtextxy(x+50,t_y,temp);
   }
   t_y+=25;
  }
  setcolor(8);
}

void FileBrowser::Highlight_Item_FLB(int x,int y,int itemno,int bkcolor,int textcolor)
{
   char temp[50];
   strcpy(temp,Files[itemno]);
   setcolor(bkcolor);
   setfillstyle(1,bkcolor);
   bar(x+17,y+5,x+120,y+17);
   setcolor(textcolor);
   outtextxy(x+19,y+8,temp);
   setcolor(8);
}

int FileBrowser::Check_Click_Button(int x,int y,int x1,int y1)
{
  Detect_Left_Click();
  Detect_Mouse_Movement();
  if(kbhit())
    Key = GetKey();
  if( Detect_Left_Click() && moux>x && mouy>y && moux<x1 && mouy<y1
			 || Key == 57 || Key == 28)
  {
    Hide_Pointer();
    Down_Button(x,y,x1,y1);
    Show_Mouse_Pointer();
    Key = 0;
    return 1;
  }
  else
    return 0;
}

int FileBrowser::Check_Click(int x,int y,int x1,int y1)
{
  Detect_Left_Click();
  Detect_Mouse_Movement();
  if( Detect_Left_Click() && moux>x && mouy>y && moux<x1 && mouy<y1)
  {
    Hide_Pointer();
    return 1;
  }
  else
    return 0;
}


void FileBrowser::Set_SBar(char string1[50],char string2[50])
{
  Status_Bar(statusx+5,statusy,statusx+150,statusy+18,string1,REDRAW);
  Status_Bar(statusx+152,statusy,X2-5,statusy+18,string2,REDRAW);
}



void FileBrowser::InitMainDialog()
{

  Hide_Pointer();
  setfillstyle(1,0);
  bar(X1,Y1,X2,Y2);
  Window(X1,Y1,X2,Y2,title,ICON_TITLEBAR);
  outtextxy(X2-300,Y2-200,"Please wait... ");
  LinedX(X1+5,Y1+40,X2-5,Y1+40);
  //Button(575,25,625,41,"About",0);
  Button(X2-80,Y2-70,X2-20,Y2-55,ok_message,0);
  Button(X2-80,Y2-40,X2-20,Y2-25,"Cancel",0);
  Set_SBar("Select any Drives","Drive Properties");
  Get_Drives();
  Drive_List_Box(drv_x1,drv_y1,drv_x2,drv_y2,Num_Drives,Drive_Count,ICON_DRIVE);
  List_Box(file_x1,file_y1,file_x2,file_y2);

  setcolor(8);
  outtextxy(X1 + 30 ,Y1 + 25 ,"Drives:");
  Draw_Icon(X1+5,Y1+25,ICON_DRIVE);

 
  setcolor(0);
  outtextxy(drv_x2+10 ,file_y2+15 ,"File to operate :");
  update_tbox();
  update_dir();
  
  
 
		 Get_Drive_Data(getdisk());
		 sprintf(SBar1,"Selected Drive %c:",Num_Drives[getdisk()]);
		 sprintf(SBar2,"Total Files: %d, Directories: %d",
				(File_Count-Dir_Count),Dir_Count);
		 Set_SBar(SBar1,SBar2);
		 if(File_Count <= max_files)
		 {
		  File_Show_List(file_x1,file_y1,file_x2,file_y2,0,File_Count);
		  St_Page = 0;
		  End_Page = File_Count;
		  Page_Found = 0;
		  Page = 0;
				 
		 }
		 else      // | more 
		 {
			St_Page=0;
		    File_Show_List(file_x1,file_y1,file_x2,file_y2,0,max_files);
		    End_Page = max_files;
		    Button(file_x2-40,file_y2-14,file_x2-15,file_y2-2,">>",0);
		     Page_Found = 1;
		 }
		 
  Show_Mouse_Pointer();
}  //end of main dialog ... 

void FileBrowser::Clear_Selection_DLB(int itemno)
{
  int i,y1 = drv_y1+16;
  Hide_Pointer();
  for(i=0;i<Drive_Count;i++)
  {
	 setcolor(15);
	 setlinestyle(DOTTED_LINE,1,0);
	 rectangle(drv_x1+16,y1-2,drv_x2-26,y1+17);
	 
	 setlinestyle(SOLID_LINE,1,0);
	 y1+=25;
   }
   Highlight_Item_DLB(Num_Drives,itemno,ICON_DRIVE,15,8);
   Show_Mouse_Pointer();
}

int FileBrowser::Trace_Page_Button()
{
   if(Check_Click(file_x2-40,file_y2-14,file_x2-15,file_y2-2))
   {
     Down_Button(file_x2-40,file_y2-14,file_x2-15,file_y2-2);
     Show_Mouse_Pointer();
     Page++;
     return 1;
   }
   return 0;
}

int FileBrowser::Trace_Back_Button()
{
   if(Check_Click(file_x1+5,file_y2-14,file_x1+35,file_y2-2))
   {
     Down_Button(file_x1+5,file_y2-14,file_x1+35,file_y2-2);
     Show_Mouse_Pointer();
     Page--;
     return 1;
   }
   return 0;
}

int FileBrowser::Trace_Cancel_Button()
{
   if(Check_Click(X2-80,Y2-40,X2-20,Y2-25))
   {
   Hide_Pointer();
     Down_Button(X2-80,Y2-40,X2-20,Y2-25);
     Show_Mouse_Pointer();
 
     return 1;
   }
   return 0;
}
int FileBrowser::Trace_OK_Button()
{
   if(Check_Click(X2-80,Y2-70,X2-20,Y2-55))
   {
    Hide_Pointer();
     Down_Button(X2-80,Y2-70,X2-20,Y2-55);
     Show_Mouse_Pointer();
 
     return 1;
   }
   return 0;
}

void FileBrowser::Trace_Drive_ListBox()
{
  tdl_y1 = drv_y1+16;
  tdl_itemno = 0;
  if(moux>drv_x1 && mouy>drv_y1 && moux<drv_x2 && mouy<drv_y2)
  {
    if(moux>drv_x1+18 && moux<drv_x2-36)
     {
      if(Detect_Left_Click())
      {
      
	 for(tdl_i=0;tdl_i<Drive_Count;tdl_i++)
	 {
	   if(Check_Click(drv_x1+18,tdl_y1,drv_x2-36,(tdl_y1+15)))
	   {
		 Clear_Selection_DLB(Tmpno);
		 setcolor(8);
		 Highlight_Item_DLB(Num_Drives,tdl_itemno,ICON_DRIVE,9,15);
		 setlinestyle(DOTTED_LINE,1,0);
		 setcolor(15);
		 rectangle(drv_x1+16,tdl_y1-2,drv_x2-26,tdl_y1+17);
		 setlinestyle(SOLID_LINE,1,0);
		 setcolor(8);
		 while( Detect_Left_Click() & 1) ;
		 Tmpno = tdl_itemno;
		 TFL_Tmpno = -1;
		 Get_Drive_Data(Tmpno);
		 sprintf(SBar1,"Selected Drive %c:",Num_Drives[tdl_itemno]);
		 sprintf(SBar2,"Total Files: %d, Directories: %d",
				(File_Count-Dir_Count),Dir_Count);
		 Set_SBar(SBar1,SBar2);
		 if(File_Count <= max_files)
		 {
		  File_Show_List(file_x1,file_y1,file_x2,file_y2,0,File_Count);
		  St_Page = 0;
		  End_Page = File_Count;
		  Page_Found = 0;
		  Page = 0;
				 
		 }
		 else      // | more 
		 {
			St_Page=0;
		    File_Show_List(file_x1,file_y1,file_x2,file_y2,0,max_files);
		    End_Page = max_files;
		    Button(file_x2-40,file_y2-14,file_x2-15,file_y2-2,">>",0);
		     Page_Found = 1;
		 }
		 Show_Mouse_Pointer();
		 break;
	   }
	   tdl_y1+=25;
	   tdl_itemno++;
	 }
	 tdl_y1 = 86;
	 tdl_itemno=0;
	 update_dir();
       }
     }
   }
}

void FileBrowser::Trace_File_ListBox()
{

   if(Page_Found == 1)
   {
 
      if(Trace_Page_Button() == 1)
     {

	 Hide_Pointer();
	 St_Page = End_Page;
	 End_Page = St_Page + max_files;
	 if( (End_Page) > File_Count)
	 {
	    End_Page = File_Count;
	 }
	 File_Show_List(file_x1,file_y1,file_x2,file_y2,St_Page,End_Page);
	 if(End_Page == File_Count)
	 {
	    Page_Found = 0;
	 }
	 else
	    Button(file_x2-40,file_y2-14,file_x2-15,file_y2-2,">>",0);
	 if(Page > 0)
	    Button(file_x1+5,file_y2-14,file_x1+35,file_y2-2,"<<",0);
	    
	 Show_Mouse_Pointer();
     }
   }

   if(Page > 0)
   {
     if(Trace_Back_Button() == 1)
     {
	 if( !(End_Page == File_Count) )
	 {
	  End_Page -=max_files;
	  St_Page = End_Page - max_files;
	 }
	 else
	 {
	  End_Page = End_Page - (End_Page - St_Page);
	  St_Page = End_Page - max_files;
	 }

	 Hide_Pointer();
	 File_Show_List(file_x1,file_y1,file_x2,file_y2,St_Page,End_Page);
	 if(Page != 0)
	 {
	    Page_Found = 1;
	    Button(file_x1+5,file_y2-14,file_x1+35,file_y2-2,"<<",0);
	    Button(file_x2-40,file_y2-14,file_x2-15,file_y2-2,">>",0);
	 }
	 else
	 {
	    Page_Found = 1;
	    Button(file_x2-40,file_y2-14,file_x2-15,file_y2-2,">",0);
	  }
	 Show_Mouse_Pointer();
     }
   }

   Detect_Left_Click();
   Detect_Mouse_Movement();

  if(moux>file_x1 && mouy>file_y1 && moux<file_x2 && mouy<file_y2)
  {


    if(Detect_Left_Click())
    {
    
      tfl_t_x = file_x1; tfl_t_y = file_y1;
      tfl_j = 0;
     //cout<<St_Page<<" { "<<End_Page;
     // getch();
      
      for(tfl_i=St_Page;tfl_i<End_Page;tfl_i++)
      {
   
	if(Check_Click(tfl_t_x,tfl_t_y,tfl_t_x+120,tfl_t_y+15))
	{
		  
	 if(TFL_Tmpno != -1)
	   Highlight_Item_FLB(H_x,H_y,TFL_Tmpno,15,8);

	 TFL_Tmpno = tfl_i;
	
	 H_x = tfl_t_x; H_y = tfl_t_y;
	 Highlight_Item_FLB(tfl_t_x,tfl_t_y,tfl_i,9,15);
	 
	 while(Detect_Left_Click() & 1);
	 if(Icon[tfl_i] == 'D')
	 {
	   Button(open_x1,open_y1,open_x2,open_y2,"Open Directory",0);
	   Open_Dir = 1;
	 }
	 else
	 {
	   setcolor(7);
	   setfillstyle(1,7);
	   bar(open_x1-1,open_y1-1,open_x2+1,open_y2+1);
	   Open_Dir = 0;
	  strcpy(fname,Files[tfl_i]);
	  update_tbox();
	 }
	 Show_Mouse_Pointer();

	}
	tfl_t_y+=15;
	tfl_j++;
	if(tfl_j>= (file_y2-file_y1)/15 -1)
	{
	 tfl_t_x+=120+5;
	 tfl_t_y = file_y1;
	 tfl_j=0;
	}

      }
    }
  }

  if(Open_Dir == 1)
  {
    if(Check_Click(open_x1,open_y1,open_x2,open_y2))
    {
     Down_Button(open_x1,open_y1,open_x2,open_y2);
     setcolor(7);
     setfillstyle(1,7);
     bar(open_x1-1,open_y1-1,open_x2+1,open_y2+1);
     Open_Dir = 0;
     getcwd(Temp,MAXPATH);
     if(strlen(Temp)>3)
      strcat(Temp,"\\");
     strcat(Temp,Files[TFL_Tmpno]);
   //  strcat(Temp,"\\");
   chdir(Temp);
     Temp[0] = '\0';

     Get_Drive_Data(Tmpno);
     sprintf(SBar1,"Selected Drive %c:",Num_Drives[Tmpno]);
     sprintf(SBar2,"Total Files: %d, Directories: %d",
			(File_Count-Dir_Count),Dir_Count);
      Set_SBar(SBar1,SBar2);
      	 update_dir();
      TFL_Tmpno = -1;
      if(File_Count <= max_files)
      {
       File_Show_List(file_x1,file_y1,file_x2,file_y2,0,File_Count);
       St_Page = 0;
       End_Page = File_Count;
       Page_Found = 0;
       Page = 0;
      }
      else
      {

	 File_Show_List(file_x1,file_y1,file_x2,file_y2,0,max_files);
	 End_Page = max_files;
	 Button(file_x2-40,file_y2-14,file_x2-15,file_y2-2,">",0);
      }
      Show_Mouse_Pointer();
    }
  }
  
}

int FileBrowser::Trace_Mouse_Keyboard()
{
  Key = 0;
  while(Key != 1)
  {
   if(kbhit())
      Key = GetKey();
    Detect_Left_Click();
    Detect_Right_Click();
    Detect_Mouse_Movement();
    Trace_Drive_ListBox();
    Trace_File_ListBox();
    Trace_tbox();
    if(Trace_OK_Button()) return 1;
    if(Trace_Cancel_Button()) return 0;
  
  }
  return 0;
}










