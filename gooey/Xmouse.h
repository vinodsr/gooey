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
/* MOUSE HEADER FILE   */
int moux,mouy;
union REGS regs;
void Init_Mouse();
void Show_Mouse_Pointer();
void Hide_Pointer();
int Detect_Left_Click();

int Detect_Right_Click();
int Detect_Mouse_Movement();
void Init_Mouse()
{int midx, midy, i;
 regs.x.ax=0;    /*check existance of mouse*/
 int86(0x33,&regs,&regs);
 if(regs.x.ax==0)
  system("mouse>NUL");
 regs.x.ax=1;   /*activate mouse pointer*/
 int86(0x33,&regs,&regs);
 regs.x.ax=15;
 regs.x.cx=50;
 regs.x.dx=50;
}
void Show_Mouse_Pointer()
{regs.x.ax=1;   /*activate mouse pointer*/
 int86(0x33,&regs,&regs);
 regs.x.ax=15;
 regs.x.cx=50;
 regs.x.dx=50;
}
int Detect_Left_Click()
{int midx, midy;
 regs.x.ax=3;
 int86(0x33,&regs,&regs);
 midx=regs.x.cx;
 midy=regs.x.dx;
 if(regs.x.bx & 1)
 {moux=midx;
  mouy=midy;
  return 1;
 }
 else return 0;
}
int Detect_Mouse_Movement()
{int midx, midy;
 regs.x.ax=3;
 int86(0x33,&regs,&regs);
 midx=regs.x.cx;
 midy=regs.x.dx;
 if(midx==moux&&midy==mouy)
  return 0;
 else{moux=midx;
      mouy=midy;
      return 1;
     }
}
void Hide_Pointer()
{regs.x.ax=2;
 int86(0x33,&regs,&regs);
}
int Detect_Right_Click()
{int midx, midy;
 regs.x.ax=3;
 int86(0x33,&regs,&regs);
 midx=regs.x.cx;
 midy=regs.x.dx;
 if((regs.x.bx & 2)&&(!(regs.x.bx & 1)))
 {moux=midx;
  mouy=midy;
  return 1;
 }
 else return 0;
}
