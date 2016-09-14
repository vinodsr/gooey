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

/* Starter Program for Gui Builder */
/* @ Vinod SR : vinod_sr@265.com*/



#include ".\gui\gui_clas.h"
#include "myheader.h"


void ShowInitScreen();
 
 void main(int argc,char *argv[])
{
 

init_dog();
if(argc>1 && strcmp(argv[1],"nosplash") ==0)
 {  //do nothing
 }
 else
    ShowInitScreen();
dog("Inititiated");
DEBUG_ON=false;

	int x,y;
	int area;
	char title_name[60];
	char fname[20],dir[100];
				int nocancel=true;
				
	strcpy(title_name,"Gooey ++ - THE GUI Devlopment Toolkit For Dos v 1.0");
	gdriver.init();
	gdriver.usepalette();
	mouse.init();
	mouse.show();
	x=getmaxx();
	y=getmaxy();


	draw_horizon(0,0,x,20,1);
	setlinestyle(0,1,1);
	setcolor(15);
	rectangle(0,0,getmaxx(),getmaxy());
	settextjustify(LEFT_TEXT,TOP_TEXT);
	outtextxy(getmaxx()/2-((strlen(title_name)*8)/2),8,title_name);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	draw_menu(10,20,h_menu,hcount);
	dog("Menu Drawn");
	toolbox.setval(10,45,75,230,5);
	form_def.showstatus();
	toolbox.disablethis();
	dog("Toolbox loaded as disabled ");
	// Argument checking ....
	if(argc == 3)
		{
		if(strcmpi(argv[1],"-o")==0)
			{
			strcpy(dir,argv[2]);
			nocancel=true;
			goto fileopen;
			}
		}
	while(1)
	{
			area=get_clicked_area();
			dog("Area Obtained");
if(area ==1)	//menu clicked
		 {
			dog("Area = 1");
			activate_menu();
			mouse.hide();
			switch(option)
				{
				case 1:				// File Menu
					switch(useroption)
						{
						case 1:	     			//New
								if(form_def.loaded)
									messagebox("Form already opened ",MSG_ALERT);

								else if(show_new_dialog())
								{
								char buf[80];
								toolbox.enablethis();
								dog("Going to show form ");
								form_def.show_form();
								dog("Form Shown");
								dog(buf);
								}
						break;
						case 2:			//Open
								if(messagebox("Are you sure to load form ",MSG_INFO,YES_NO) == ID_YES)
									{
								FileBrowser *open;
								open = new FileBrowser(fname,dir);

								nocancel=open->show(0,&gdriver);
								delete open;

								if(strlen(dir)>3)
								strcat(dir,"\\");
								strcat(dir,fname);
								fileopen:
								// to do : check for existence
								if(nocancel && !exists(dir))
									messagebox("File not Found ! ",MSG_ALERT);
								else if( nocancel && form_def.load_form(dir) )
									toolbox.enablethis();
									}
						break;
						case 3:			//Save
								if(!form_def.loaded)
									messagebox("No Form To Save",MSG_ALERT);
								else
									{
									FileBrowser *open;
									open = new FileBrowser(fname,dir);
									nocancel=open->show(1,&gdriver);
									delete open;
									strcat(dir,"\\");
									strcat(dir,fname);
									if(nocancel && exists(dir))
									 { if(messagebox(" File Exists ; Are You sure to replace ? ",MSG_ALERT,YES_NO) == ID_YES)
										{
										form_def.save_form(dir);
										}

									 }
									 else if(nocancel)
									 {
										form_def.save_form(dir);
									 }

									}
						break;
						case 4:			//close
								if(!form_def.loaded)
								   messagebox(" No Form Opened ! ",MSG_ALERT);
								else if(messagebox(" Are You sure to close ? ",MSG_INFO,YES_NO) == ID_YES)
									{
									form_def.kill();
									toolbox.disablethis();
									clearclient();
									}
						break;
						case 5:
							int w=messagebox("Are you sure to Exit ",MSG_INFO,YES_NO);			//Exit
							if(w == ID_YES)	  {
								resume_dog();
								form_def.kill();
								toolbox.kill();
								DEBUG_ON=true;
								gdriver.unload();
								exit(0);
							}
						break;

						}

				break;
				case 2:
					// View Menu
					switch(useroption)
						{
						case 1:
						form_def.mode =01;  // foreground  mode
						break;
						case 2:
						form_def.mode =10;    //background mode
						break;
						}

						form_def.showstatus();
				break;
				case 3:				// Tools
					switch(useroption)
					{
					case 1: 		// Control - Browser
					browse_controls(&form_def);
					form_def.show_form();
					break;
					}

				break;
				case 4:				//Generate
					switch(useroption)
						{
						case 1:	 		// Generate code
						if(!form_def.loaded)
							messagebox("No Form Loaded",MSG_ALERT);
						else
				  			{
							int isvir,ishelp;
					 		char fname[130],funcname[50];
					 		_gen_form *gen_form;
					 		gen_form = new _gen_form;
					 		gen_form->run();
					 		if(gen_form ->status == CANCEL_CWIN)
					 		break;
					 		isvir = gen_form->c_vir->checked;
					 		ishelp =gen_form->c_help->checked;
					 		strcpy(fname,gen_form->l_dirname->text);
					 		if(strlen(fname)>3)
							strcat(fname,"\\");
					 		strcat(fname,gen_form->t_fname->text);	
					 		strcpy(funcname,gen_form->t_funcname->text);
					 		delete gen_form;
					 		code_gen.setfilename(fname);
							code_gen.init();
							code_gen.generate(&form_def,isvir,ishelp,funcname);
							code_gen.close();
							if(messagebox("Code Generated ; Do You Want To See it ? ",MSG_INFO,YES_NO) == ID_YES)
					 			{
					 			char command[160]="edit ";
								strcat(command,fname);
					 			mouse.hide();
					 			gdriver.savescreen();
					 			restorecrtmode();
					 			system(command);
					 			setgraphmode(getgraphmode());
					 			gdriver.usepalette();
					 			gdriver.restorescreen();
					 			mouse.show();
								}
					 		
				  			 }
						break;
						}
				break;
				case 5:				//Help
					switch(useroption)
						{
						case 1:
								mouse.hide();
					 			gdriver.savescreen();
					 			restorecrtmode();
					 			system("edit help.txt");
					 			setgraphmode(getgraphmode());
					 			gdriver.usepalette();
					 			gdriver.restorescreen();
					 			mouse.show();
					 		
						break;
						case 2:			// About
						show_about_dlg();
						break;
						}
				break;

				
				}
		 }
else if(area == 2)
		 {
		 dog("Area - 2");
		 toolbox.clicked();
		 dog("Toolbox clicked calles sucess");
		 }
else if (area == 3 && mouse.btn&2)
		{
			form_def.right_clicked(mouse);
		}

		 mouse.show();
	}		 // End of the Infinite loop :D


	mouse.hide();
	///closegraph();

}
