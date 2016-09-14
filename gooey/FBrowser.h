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

#define REDRAW        1
#define NOREDRAW      0
#define ICON_DRIVE    3
#define ICON_FOLDER   4
#define ICON_FILE     5
#define ICON_FILE_EXE 6
#define ICON_TITLEBAR 7


class FileBrowser
	{
public:
char Key,Page_Found;
char Num_Drives[50],SBar1[50],SBar2[50];
char *Files[3000],Icon[3000],Def_Dir[1500],Temp[1500];
char *fname,*dir;
int Drive_Count,File_Count,Dir_Count,Tmpno,TFL_Tmpno,Disk;
int St_Page,End_Page,Page;
int tfl_i,tfl_j,tfl_t_x,tfl_t_y,H_x,H_y,Open_Dir;
int tdl_i,tdl_y1,tdl_itemno;
int drv_x1,drv_x2,drv_y1,drv_y2;
int file_x1,file_x2,file_y1,file_y2;
int open_x1,open_x2,open_y1,open_y2;
int tb_x,tb_y;
int dir_x,dir_y;
int statusx,statusy;
int max_files;
int X1,X2,Y1,Y2;
char ok_message[50];
char title[50];
FileBrowser(char *fn,char *d,int x1=125,int y1=100,int x2=575,int y2=400);
~FileBrowser()
	{

	}
/* functions */
void update_dir();
int show (int type = 0,_gdriver *gd=NULL);
void Button( int x, int y, int x1, int y1, char Caption[ 50], int def );
int Check_Click( int x, int y, int x1, int y1 );

int Check_Click_Button( int x, int y, int x1, int y1 );
void Clear_Selection_DLB( int itemno );
void update_tbox(int bg=15);
Trace_tbox();
void Close();
void Draw_Icon( int x, int y, int Type );
void Down_Button( int x, int y, int x1, int y1 );
void Drive_List_Box( int x, int y, int x1, int y1, char item[ 50], int count, int icon );
void File_Show_List( int x, int y, int x1, int y1, int start_count, int end_count );
void Get_Drive_Data( int Drv_Letter );
void Get_Drives();
int GetKey();
void Highlight_Item_DLB( char item[ 50], int itemno, int icon, int bkcolor, int textcolor );
void Highlight_Item_FLB( int x, int y, int itemno, int bkcolor, int textcolor );
void Init();
void InitMainDialog();
void InitScreen();
void LinedX( int x, int y, int x1, int y1 );
void LinedY( int x, int y, int x1, int y1 );
void List_Box( int x, int y, int x1, int y1,int bgcolor=15 );
void Set_SBar( char string1[ 50], char string2[ 50] );
void Status_Bar( int x, int y, int x1, int y1, char Caption[ 50], int redraw );
int Trace_OK_Button();
int Trace_Cancel_Button();
int Trace_Back_Button();
void Trace_Drive_ListBox();
void Trace_File_ListBox();
int Trace_Mouse_Keyboard();
int Trace_Page_Button();
void Window( int x, int y, int x1, int y1, char Title[ 50], int iconinfo );
	};

