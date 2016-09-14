
 #include "gui/gui_clas.h" 
//TODO : Add your header files 

 // The window class 

 class _form1:public cwin
  { 
   public :
   textbox *Tbox1;
   button *Button;

  /* The constructor */ 
  _form1()
  { 

  /* Initializing cwin attribute(s) */
   x = 100;
   y = 100;
   width = 200;
   height = 200;
   strcpy(title,"Unnamed ");

  /* Initailizing controls */ 
   Tbox1 = new  textbox (80,42,50,20,"Text"); 
    attach(Tbox1);
   Button = new  button (72,70,50,20,"Label",9,0);
    attach(Button);


  } 

  int handle_event_onclick(object *obj)
  { 
   if( obj == Button)
      {        /* Do Operations for onclick() of control Button*/
      return UNLOAD_CWIN;
      }
  } 

// Event handling ended ... 
  }; //end of class
   /* Main(Display) function*/ 

  int main () 
  { 
   gdriver.init();
   gdriver.usepalette();
   _form1 *form1;
   form1 = new _form1;
   form1->run();
   delete form1;
   gdriver.unload();
   return 0;
  } 
