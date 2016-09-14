
 #include "gui/gui_clas.h" 

 class _dataform:public cwin
  { 
   public :
   frame *Frame1;
   textbox *t_name;
   textbox *t_age;
   textbox *t_salary;
   label *l_name;
   label *l_age;
   label *l_sal;
   button *b_add;
   button *b_delete;
   button *b_next;
   button *b_prev;
   button *b_update;
  database db;
  /* The constructor */ 
  _dataform()
  { 

  /* Initializing cwin attribute(s) */
   x = 186;
   y = 142;
   width = 350;
   height = 200;
   strcpy(title,"Database Ex");

  /* Initailizing controls */ 
   attach(new  Line(265,10,265,160,0),BACK);
   attach(new  Line(272,110,340,110,0),BACK);
   Frame1 = new  frame (23,19,221,125,"Data",15,5,0);
    attach(Frame1,BACK);
   t_name = new  textbox (106,43,100,20,""); 
    attach(t_name);
   t_age = new  textbox (107,79,50,20,""); 
    attach(t_age);
   t_salary = new  textbox (107,115,80,20,""); 
    attach(t_salary);
   l_name = new  label (34,43,50,20,"Name"); 
    attach(l_name);
   l_age = new  label (35,78,50,20,"Age"); 
    attach(l_age);
   l_sal = new  label (36,112,60,20,"Salary"); 
    attach(l_sal);
    b_update = new  button (100,150,70,20," Update ",9,0);
    attach(b_update);

   b_add = new  button (275,41,70,20," Add ",9,0);
    attach(b_add);
   b_delete = new  button (275,76,70,20,"Delete",9,0);
    attach(b_delete);
   b_next = new  button (275,125,70,20,"Next",9,0);
    attach(b_next);
   b_prev = new  button (275,161,70,20,"Prev",9,0);
    attach(b_prev);

  }
  int handle_onload()
	{
	db.setfile("mydata.db");
	db.setfield("name",t_name);
	db.setfield("age",t_age);
	db.setfield("salary",t_salary);
	db.connect();
	db.show();
	db.search("age","4542");

		}
  int handle_onclose()
	{
	db.commit();
	}

  int handle_event_onclick(object *obj)
  {
   if( obj == b_update)
      {        /* Do Operations for onclick() of control b_add*/
      db.updaterec();
      return OK;
      }

   if( obj == b_add)
      {        /* Do Operations for onclick() of control b_add*/
      db.addrec();
      return OK;
      }
   if( obj == b_delete)
      {        /* Do Operations for onclick() of control b_delete*/
      db.deleterec();
      return OK;
      }
   if( obj == b_next)
      {        /* Do Operations for onclick() of control b_next*/
      db.nextrec();
      return OK;
      }
   if( obj == b_prev)
      {        /* Do Operations for onclick() of control b_prev*/
      db.prevrec();
      return OK;
      }
  }

// Event handling ended ... 
  };   /* Main function*/ 

  int main () 
  {
   gdriver.init();
	gdriver.usepalette();
		//Display credicts ...
	setcolor(14);
	outtextxy(20,350," Created with gooey 1.0 ");

   _dataform *dataform;
   dataform = new _dataform;
   dataform->run();
   delete dataform;
   gdriver.unload();
   return 0;
  } 
