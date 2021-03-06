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

//To find out the heap size

#include<alloc.h>
#include <iostream.h>
#include <string.h>

#include<conio.h>
static long heapsize()
{

    long total = farcoreleft();
    struct farheapinfo heap;
    char heapStr[50];
	strcpy(heapStr,"Current heap Status :");

    switch( farheapcheck() )
	{
	case _HEAPEMPTY:
	    strcat(heapStr, "     No heap");
	    total = -1;
	    break;

	case _HEAPCORRUPT:
	    strcat(heapStr, "Heap corrupt");
	    total = -2;
	    break;

	case _HEAPOK:
		strcat(heapStr, "Heap OK");
	    heap.ptr = NULL;
	    while(farheapwalk(&heap) != _HEAPEND)
		if(!heap.in_use)
		    total += heap.size;

  
	    break;
	}



    return(total);
}
