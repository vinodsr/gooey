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
static int dog_en=false;

/* Detailed lOGer */

    
static int dog(char *message,int heap = false)
{
  if(!dog_en)
  return 0;
  char buf[50];
  if(heap)
  	{
  	 sprintf(buf," | Heap size : %ld",heapsize());
  	 strcat(message,buf);
  	}
fstream fp;

fp.open("dog.txt",ios::out|ios::app);
fp<<" [ "<<message<<" ]\n";
fp.close();


   return 1;
    }
static int init_dog()
	{
	remove("dog.txt");
	dog_en=true;
	dog("Dog - [D]etailed l[OG]ger v 0.1 - Vinod s.R : vinod_sr@265.com");
	return 1;
	}
static int resume_dog()
	{
	dog_en=true;
	return 1;
	}
static int close_dog()
	{
	dog_en=false;
	return 1;
	}
