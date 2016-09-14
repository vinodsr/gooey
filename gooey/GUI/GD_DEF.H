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

	int huge detectEGA(void)
	{
	      return 2;
	}

 _gdriver::restorescreen(int x1,int y1,int x2,int y2,int nokill,int op)
	{
	   FILE *f;
	   char temp_fname[15];
	   void far *bit;
	   unsigned size=imagesize(x1,y1,x2,y2);


   bit=farmalloc(size);
      if(bit== NULL || size ==65535)
	{
	if(bit)
      	farfree(bit);
	return 0;
    }
	strcpy(temp_fname,screens[screen_index]);

	screen_index--;

	f=fopen(temp_fname,"rb");
   
	fread(bit,size,1,f);
	mouse.hide();

	putimage(x1,y1,bit,op);

	mouse.show();
	fclose(f);
	if(!nokill)
	remove(temp_fname);
	farfree(bit);

	return 1;
	}

_gdriver::restorescreen(int x1,int y1,int x2,int y2,char * fname,int op )
	{
	   FILE *f;
	   
	   void *bit;
	   long size=imagesize(x1,y1,x2,y2);

   bit=malloc(size);
     if(bit== NULL || size ==65535)
	{
	if(bit)
      	free(bit);
	return 0;
      }

	f=fopen(fname,"rb");

	fread(bit,size,1,f);
	mouse.hide();
	putimage(x1,y1,bit,op);

	mouse.show();
	fclose(f);
	free(bit);

	return 1;
	}


 _gdriver::restorescreen_up(int x1,int y1,int x2,int y2,int nokill,int op)
	{
	   FILE *f;
	   char temp_fname[15];
	   void *bit;
	   long size = imagesize(x1,y1,x2,y1+(y2-y1)/4);

   bit=malloc(size);
   if(bit == NULL)
	{
	 closegraph();
	 printf("Not Enough Memory : gdriver.h -restorescreen()\n");
	 exit(1);
      }
	strcpy(temp_fname,screens[screen_index]);

	screen_index--;

	f=fopen(temp_fname,"rb");


	fread(bit,size,1,f);
	mouse.hide();
	putimage(x1,y1,bit,op);

	   fread(bit,size,1,f);
	   mouse.hide();
	   putimage(x1,y1+(y2-y1)/4,bit,op);
	   
	   mouse.show();

	   fread(bit,size,1,f);
	   mouse.hide();
	   putimage(x1,y1+(y2-y1)/2,bit,op);
	   mouse.show();
	   fread(bit,size,1,f);
	   mouse.hide();
	   putimage(x1,y1+((y2-y1)*3)/4,bit,op);
	mouse.show();
	fclose(f);
	remove(temp_fname);
	free(bit);
	return 1;

	}


 _gdriver::restorescreen()
	{
	   FILE *f;
	   char temp_fname[15];
	   void *bit;
	   long size=imagesize(0,maxy/4,maxx,maxy/2);

   bit=malloc(size);
   if(bit == NULL)
	{
	 closegraph();
	 printf("Not Enough Memory : gdriver.h -restorescreen()\n");
	 exit(1);
      }

	strcpy(temp_fname,screens[screen_index]);

	screen_index--;

	f=fopen(temp_fname,"rb");

	fread(bit,size,1,f);
	mouse.hide();
	putimage(0,0,bit,COPY_PUT);

	   fread(bit,size,1,f);
	   mouse.hide();
	   putimage(0,maxy/4,bit,COPY_PUT);
	   mouse.show();
	   fread(bit,size,1,f);
	   mouse.hide();
	   putimage(0,maxy/2,bit,COPY_PUT);
	   mouse.show();
	   fread(bit,size,1,f);
	   mouse.hide();
	   putimage(0,(maxy*3/4),bit,COPY_PUT);
	mouse.show();
	fclose(f);
	remove(temp_fname);
	free(bit);
	return 1;

	}

 _gdriver::savescreen(int x1,int y1,int x2,int y2 )
	{
   unsigned size;
   char temp_index[5];
   FILE *f;

   size = imagesize(x1,y1,x2,y2);

   void far *bit;
   bit=farmalloc(size);
      if(bit== NULL || size ==65535)
      {
      if(bit)
	farfree(bit);
	      return 0;
      }

      screen_index++;
      itoa(screen_index,temp_index,10);
      strcpy(screens[screen_index],"");
      strcat(screens[screen_index],screenfile);
      strcat(screens[screen_index],temp_index);
      strcat(screens[screen_index],".scr");

      f=fopen(screens[screen_index],"wb+");
      mouse.hide();

      getimage(x1,y1,x2,y2,bit);
	fwrite(bit,size,1,f);


	   fclose(f);
	   farfree(bit);

	   mouse.show();

	return 1;
	}


_gdriver::savescreen(int x1,int y1,int x2,int y2,char *fname)
	{
   unsigned size;
   FILE *f;

   size = imagesize(x1,y1,x2,y2);
   void *bit;
   bit=malloc(size);
        if(bit== NULL || size ==65535)
      {
      if(bit)
      	free(bit);
	      return 0;
      }

   
      f=fopen(fname,"wb+");
      mouse.hide();

    getimage(x1,y1,x2,y2,bit);
	fwrite(bit,size,1,f);


	   fclose(f);
	   free(bit);

	   mouse.show();
	return 1;
	}


 _gdriver::savescreen_up(int x1,int y1,int x2,int y2)
	{
   unsigned size;
   char temp_index[5];
   FILE *f;

   size = imagesize(x1,y1,x2,y1+(y2-y1)/4);
   void *bit;
   bit=malloc(size);
      if(bit== NULL)
      {
	 closegraph();
	 printf("Not Enough Memory : gdriver.h -savescreen()\n");
	 exit(1);
      }

     screen_index++;
     itoa(screen_index,temp_index,10);
     strcpy(screens[screen_index],"");
     strcat(screens[screen_index],screenfile);
     strcat(screens[screen_index],temp_index);
     strcat(screens[screen_index],".scr");

    f=fopen(screens[screen_index],"wb+");
    mouse.hide();

    getimage(x1,y1,x2,(y1+(y2-y1)/4),bit);
	fwrite(bit,size,1,f);
		
	
    getimage(x1,y1+(y2-y1)/4,x2,y1+(y2-y1)/2,bit);

	fwrite(bit,size,1,f);
   getimage(x1,y1+(y2-y1)/2,x2,y1+((y2-y1)*3)/4,bit);
	fwrite(bit,size,1,f);

      getimage(x1,y1+((y2-y1)*3)/4,x2,y2,bit);
	fwrite(bit,size,1,f);



	   fclose(f);
	   free(bit);

	   mouse.show();
	return 1;
	}


 _gdriver::savescreen()
	{
   unsigned size;
   char temp_index[5];
   FILE *f;

   size = imagesize(0,maxy/4,maxx,maxy/2);
   void *bit;
   bit=malloc(size);
      if(bit== NULL)
      {
	 closegraph();
	 printf("Not Enough Memory : gdriver.h -savescreen()\n");
	 exit(1);
      }

      screen_index++;
      itoa(screen_index,temp_index,10);
      strcpy(screens[screen_index],"");
      strcat(screens[screen_index],screenfile);
      strcat(screens[screen_index],temp_index);
      strcat(screens[screen_index],".scr");

      f=fopen(screens[screen_index],"wb+");
      mouse.hide();

      getimage(0,0,maxx,maxy/4 +1 ,bit);
	fwrite(bit,size,1,f);

      getimage(0,maxy/4,maxx,maxy/2,bit);
	fwrite(bit,size,1,f);
   getimage(0,maxy/2,maxx,(maxy*3/4),bit);
	fwrite(bit,size,1,f);

      getimage(0,(maxy*3/4),maxx,maxy,bit);
	fwrite(bit,size,1,f);



	   fclose(f);
	   free(bit);

	   mouse.show();
	return 1;
	}



void _gdriver::draw_bar(int bx,int by,int wd,int ht,int color,int border)
	{
		mouse.hide();
		int bx2=bx+wd;
		int by2=by+ht;
		//clear the area
		setfillstyle(1,15-border);
		bar(bx,by,bx2,by2);

		setcolor(border);
		 rectangle(bx,by,bx2,by2);
		 setfillstyle(1,color);
		 floodfill((bx+bx2)/2,(by+by2)/2,border);
		 mouse.show();
	}



void _gdriver::draw_3dbar(int bx,int by,int wd,int ht,int color,int border,int t,int dec,int style,int clear_type )
		{
		mouse.hide();
     	char pattern[8] = {0xFF,0xFF,0xFF,0xF7,0xE7,0xFF,0xFF,0xFF};
		int bx2=bx+wd;
		int by2=by+ht;
		int type=t;
		int l_br,u_br;
			if(type == 1) { l_br=l_shade;u_br=u_shade;}
			else if(type == 2) { l_br=u_shade;u_br=l_shade;}
			else if(type == 3) { l_br=l_shade;u_br=u_shade; border=sel_border;color=sel_bgcolor;}
		//clear the area
		if(clear_type == 1)
		{
		setfillstyle(1,15-border);
		bar(bx,by,bx2,by2);
		}
		else
		
		{	
		 unsigned size;
  		 size = imagesize(bx,by,bx2,by2);
   		 void *bit;
   		 bit=malloc(size);
      if(bit ==  NULL)
      {
	    	// simple fillig 
		
			setfillstyle(1,15-border);
			bar(bx,by,bx2,by2);
	    
      }
	else
		{
		
		getimage(bx,by,bx2,by2,bit);	
		putimage(bx,by,bit,XOR_PUT);
		free(bit);
		}
		
	
		}	 // end of clear_type if
		setcolor(border);
		rectangle(bx,by,bx2,by2);
		rectangle(bx+dec,by+dec,bx2-dec,by2-dec);
		//setcolor(u_br);
		moveto(bx,by);
		lineto(bx+dec,by+dec);
		moveto(bx2,by);
		lineto(bx2-dec,by+dec);
			//setcolor(l_br);
		 moveto(bx2,by2);
		 lineto(bx2-dec,by2-dec);
		 moveto(bx,by2);
		 lineto(bx+dec,by2-dec);
		 
		 if( style >= 0)
		 setfillstyle(style,color);
		 else if(style == -1)
		 setfillpattern(pattern, color);
		 
		 floodfill((bx+bx2)/2,(by+by2)/2,border);
		 setfillstyle(1,u_br);
		 floodfill(bx+dec/2,(by+by2)/2,border);
		 floodfill((bx+bx2)/2,by+dec/2,border);
		 setfillstyle(1,l_br);
		 floodfill((bx+bx2)/2,by2-dec/2,border);
		 floodfill(bx2-dec/2,(by+by2)/2,border);

		 mouse.show();
	}


void _gdriver::draw_3dbar_inv(int bx,int by,int wd,int ht,int color,int border,int t,int dec)
		{
		mouse.hide();
		int bx2=bx+wd;
		int by2=by+ht;
		int type=t;
		int l_br,u_br;
			if(type == 1) { u_br=l_shade;l_br=u_shade;}
			else if(type == 2) { u_br=u_shade;l_br=l_shade;}
			else if(type == 3) { u_br=l_shade;l_br=u_shade; border=sel_border;color=sel_bgcolor;}
		//clear the area
		 setfillstyle(1,15-border);
		 bar(bx,by,bx2,by2);
		 setcolor(border);
		 rectangle(bx,by,bx2,by2);
		 rectangle(bx+dec,by+dec,bx2-dec,by2-dec);
		 moveto(bx,by);
		 lineto(bx+dec,by+dec);
		  moveto(bx2,by);
		 lineto(bx2-dec,by+dec);
		 moveto(bx2,by2);
		 lineto(bx2-dec,by2-dec);
		 moveto(bx,by2);
		 lineto(bx+dec,by2-dec);
		 setfillstyle(1,color);
		 floodfill((bx+bx2)/2,(by+by2)/2,border);
		 setfillstyle(1,u_br);
		 floodfill(bx+dec/2,(by+by2)/2,border);
		 floodfill((bx+bx2)/2,by+dec/2,border);
		 setfillstyle(1,l_br);
		 floodfill((bx+bx2)/2,by2-dec/2,border);
		 floodfill(bx2-dec/2,(by+by2)/2,border);
		 mouse.show();
	}
