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
#define MSG_INFO 501
#define MSG_ALERT 502
#define MSG_WARNING 503
#define YES_NO 401
#define OK 402

#define ID_OK 601
#define ID_YES 602
#define ID_NO 603

class msgbox:public cwin
	{
	public:
	button *ok;
	button *yes,*no;
	label *message;
	int stat;
	int _type;

	int handle_onload()
		{
		if(_type == MSG_ALERT)
		{
		int poly[8]={15,15,5,30,25,30,15,15};
		setfillstyle(1,14);
		fillpoly(4,poly);
		}
		}
	int handle_event_onclick(object *obj)
		{
		if(obj == ok)
		{
			stat=ID_OK;
			return UNLOAD_CWIN;
		}
		else if(obj == yes)
		{
			stat=ID_YES;
			return UNLOAD_CWIN;
		}
		else if(obj == no)
		{
			stat=ID_NO;
			return UNLOAD_CWIN;
		}
		}


	msgbox(char * text, int type,int op=OK)
		{

		int _len = strlen(text)*8 ;

		width = _len+55;
		if(width < 150)
			width = 150;
		height = 80;
		x=320-(width / 2 );
		y=200;


	if(type == MSG_INFO)
		strcpy(title," Information ");
	else if(type == MSG_ALERT)
		strcpy(title," Alert ");
	else if(type == MSG_WARNING)
		strcpy(title," Warning ");
	else
		strcpy(title," Message Box ");

		_type=type;
		message= new label(25,10,_len+8,10,text);
		attach(message);
		if(op == OK)
			{
			ok= new button(width/2-15,40,40,20," OK ");
			attach(ok);
			}
		else
			{
			yes= new button(width/2-15-40,40,50,20," Yes ");
			attach(yes);
			no= new button(width/2-15+40,40,40,20," No ");
			attach(no);

			}
		}
	};
	int messagebox(char * messag, int type = MSG_INFO,int op=OK);
