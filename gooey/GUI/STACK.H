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
   Name:  stack.h
   Date: 31/07/05 09:00
   Description: for implmenting generic stack
 */

//defining stack's max size
#define STACK_MAX_SIZE 100



template <class T>
class stack			//The stack class
	{
	T stk[STACK_MAX_SIZE];
	int top;
	public:
	stack()
		{
		top=-1;
		}
	void push(T);
	int pop(T &);
	int pop();
	int isempty();
	void display();
	int getsize() { return top; }
	T gettop();
	T getitem(int);
	}; 


	template <class T>
	void stack<T>::push(T item)        //For pushing
		{

		top++;
		if(top == STACK_MAX_SIZE)
			{
			cerr << "\n Stack Overflow : Change STACK_MAX_SIZE in stack.h";
			exit(0);
			}

		stk[top]=item;
		}
	template <class T>
	int stack<T>::pop(T &dump)           //For poping
		{
		if(isempty())	return 0;
		dump=stk[top];
		top--;
		return 1;
		}

	template <class T>
	int stack<T>::pop()           //For poping
		{
		if(isempty())	return 0;
		top--;
		return 1;
		}

	template <class T>
	T stack<T>::gettop()                 //To get top element
		{
		if(isempty())	return 0;
		return stk[top];
		}

	template <class T>
	int stack<T>::isempty()             // Check stack underflow
		{
		if(top !=-1)
			return 0;
		else
			return 1;
		}

	template <class T>
	void stack<T>::display()          // Prints the stack
		{
		int dump=top;
		cout<<endl<<"Top : ";
		while(dump>=0)
			{
			cout<<" <-> "<<(stk[dump]);
			dump --;
			}
		cout<<": End "<<endl;
		} // end of display()

	template <class T>
	T stack<T>::getitem(int s) 	// gettin item 's' from 0 to ....
		{
		if(s>top)
			{
			cerr<<"Out of Stack bounds : stack.h";
			exit(0);
			}
		return stk[s];
		} //end of getitem()
