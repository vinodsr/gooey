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


 class _gen_form:public cwin
  { 
   public :
   button *b_cancel;
   button *b_ok;
   checkbox *c_help;
   label *l_v_help;
   checkbox *c_vir;
   textbox *t_funcname;
   label *l_funname;
   button *b_browse;
   label *l_dirname;
   label *l_dir;
   textbox *t_fname;
   label *l_fname;

int handle_event_onclick(object *obj)
	{
	   
	       if( b_ok==obj)
		{
		
		return UNLOAD_CWIN;
		}
	  else  if( b_browse==obj)
		{
		mouse.hide();
		struct viewporttype viewinfo;
		getviewsettings(&viewinfo);
		setviewport(0,0,getmaxx(),getmaxy(),1);
		FileBrowser *a;
		a= new FileBrowser(t_fname->text,l_dirname->text);
		a->show(1,&gdriver);
		
		delete a;
		
		setviewport(viewinfo.left,viewinfo.top,viewinfo.right, viewinfo.bottom,viewinfo.clip);
    	t_fname->draw();
    	l_dirname->draw();
    	mouse.show();		
		return OK;
		}
	
		else if( b_cancel==obj)
		{
			return CANCEL_CWIN;
		}
	 return OK;

		}
  /* The constructor */ 
  _gen_form()
  { 

  /* Initializing cwin attribute(s) */
    	width=400;
		height=335;
		x=getmaxx()/2 - (width / 2 );
		y=getmaxy()/2 - (height /2);

  
   strcpy(title,"Generate Code");
	char temp[MAXPATH];
	getcwd(temp,MAXPATH);
  /* Initailizing controls */ 
   b_cancel = new  button (310,271,70,20," Cancel"); 
    attach(b_cancel);
   b_ok = new  button (250,271,50,20," OK "); 
    attach(b_ok);
   c_help = new  checkbox (40,233,120,0,0,"Use Help"); 
    attach(c_help);
   l_v_help = new  label (165,185,220,60,"Virtual means the co-ordinates you see in the dev window"); 
    attach(l_v_help);
   c_vir = new  checkbox (40,194,140,0,0,"Virtual X & Y"); 
    attach(c_vir);
    attach(new Line(165,194,165,234,8));
   t_funcname = new  textbox (131,138,160,20,"main"); 
    attach(t_funcname);
   l_funname = new  label (34,129,80,40,"Function Name"); 
    attach(l_funname);
   b_browse = new  button (300,73,80,20," Browse "); 
    attach(b_browse);
   l_dirname = new  label (131,90,160,20,temp); 
    attach(l_dirname);
   l_dir = new  label (36,90,80,20,"Directory"); 
    attach(l_dir);
   t_fname = new  textbox (131,50,160,20,"out.cpp"); 
    attach(t_fname);
   l_fname = new  label (35,50,80,20,"Filename"); 
    attach(l_fname);
    attach(new label(5,255,230,60,"You Should carry EGAVGA.BGI file and the GUI directory with the generated file ..",4,bgcolor,1));
	attach(new frame(30,40,360,135,"File Details",15,bgcolor,0),BACK);
	attach(new frame(30,183,360,80,"Options",15,bgcolor,0),BACK);

  } 
  };
