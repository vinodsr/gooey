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
 /*
   Name:  llist.h
   Date: 31/07/05 09:00
   Description: for implmenting generic llist
 */

//defining linked list's max size
#define llist_MAX_SIZE 100

template < class R>
class node
	  {
	  public:
	  R data;
	  node <R> * next;

	  };


template <class T>
class llist			//The llist class
	{
	node <T> *start,*curr,*temp;
	int length;
	public:
	llist()
		{
		start = NULL;
		length = 0;
		}
	~llist()
		{

			
		
		
		killall();
		}
	void insert(T);
	int pop(T &);
	int remove(int pos = -1);
	int remove(T);
	int isempty();
	void display();
	int getsize() { return length; }
	T gettop();
	T getitem(int);
	int killall();
	}; 

	template < class T>
	int llist<T>::killall()        //For killing
		{
		temp = start;
		node <T> * killer;
		while(temp)
				   {
				 
				   killer=temp;
				   temp=temp->next;
		
				   free(killer->data);
				   free(killer);
				   }			
		length=0;
		start=NULL;
		return 1;
		}


	template < class T>
	void llist<T>::insert(T item)        //For pushing
		{
		temp=(node <T> *)malloc(sizeof(node<T>)) ;
		if(temp != NULL)
		{
			length ++;
			temp->data=item;
			temp->next=start;
			start=temp;

		}  // End of checking NULL

		}
		  



	template <class T>
	int llist<T>::remove(int pos=-1)           //For poping
		{
		if(pos > length)
			{
			cerr<<" Invalid Postion in remove () : llist.h ";
			dog(" Invalid Postion in remove() : llist.h ");
			exit(0);
			}
		int i=1;
		node <T> * prev=start;
		if(pos == -1 ) pos =length;
		temp=start;
		while(i != pos)
			{
			prev=temp;
			temp=temp->next;
			i++;
			}
		length --;
		if(temp == start)
			{
			start=start->next;
			}
		else
			{
			prev->next=temp->next;
			}

		free(temp->data);
		free(temp);
		}


	template <class T>
	int llist<T>::remove(T item)           //For poping
		{
		int i=1;
		int done =false;
		temp=start;
		while(i <=length && ! done)
			{
			if(temp->data == item)
				{
				remove(i);		
				done=true;
				}
			temp=temp->next;
			i++;
			}
		if(!done)
			dog(" Item Not Found in remove(T) : llist.h");	
		
		}

	template <class T>
	T llist<T>::gettop()                 //To get top element
		{
		return curr->data;
		}

	template <class T>
	int llist<T>::isempty()             // Check llist underflow
		{
		if(length == 0)
		return 1;
		}
	template <class T>
	void llist<T>::display()          // Prints the llist
		{

		cout<<" length : "<<length;
		temp = start;
		while(temp)
				   {
				   cout<<" - "<<temp->data<<" - ";
				   temp=temp->next;
				   }
		} // end of display()

	template <class T>
	T llist<T>::getitem(int pos) 	// gettin item 's' from 0 to ....
		{
		if(pos > length)
			return 0;
			
			int i=1;
	
		temp=start;
		while(i != pos)
			{
			temp=temp->next;
			i++;
			}
    	return temp->data;	
		} //end of getitem()
