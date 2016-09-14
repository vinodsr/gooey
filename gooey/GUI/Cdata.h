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

const int maxlines=200;
const int maxlen=75;

class database
	{
	char d_field[30][40],field[30][40];
	textbox * d_cntrl[30],*cntrl[30];
	char fields[maxlines];
	char buffer[maxlines][maxlen];
	int open;
	int commited;
	int nof; // No : of fields ...
	int n_o_l;
	int cp; //current pointer;
	char fname[15];
	FILE *fp;


	public:
		void show()
			{
			int k=0;
			char lorry[maxlen];
			while(k<nof)
				{
				strcpy(lorry,buffer[cp+k]);
				lorry[strlen(lorry)-1]='\0';
				if(n_o_l == 0)
				cntrl[k]->setval("",true);
				else
				cntrl[k]->setval(lorry,true);
				k++;
				}
			}
		int addrec()
			{
			int k=0;
			char lorry[maxlen];
			int state=cp;
			cp=n_o_l;
			while(k<nof)
				{
				if(cntrl[k] != NULL)
				strcpy(lorry,cntrl[k]->text);
				else
				strcpy(lorry,"");
				strcat(lorry,"\n\0");
				strcpy(buffer[cp++],lorry);
				k++;
				}
			n_o_l=cp;
			cp=state;
			}

		setfield(char f1[40],textbox *dummy)
			{

			 strcpy(d_field[nof],f1);
			 d_cntrl[nof]=dummy;
			 nof++;
			}
		database()
			{
			nof=0;
				n_o_l=0;
				cp=0;

			}
		void setfile(char * dummy)
			{
			strcpy(fname,dummy);
			}
		int commit()
			{
			fp=fopen(fname,"w");
			int k=0;
			while(k<nof)
			{
			fputs(field[k],fp);
			fputs("|",fp);
			k++;
			}
			fputs("\n",fp);
			k=0;
			while(k<n_o_l)
			{
			fputs(buffer[k],fp);
			k++;
			}
			fclose(fp);
			return 1;
			}
		int search(char f[40],char v[maxlen])
			{
			int n=-1;
			int k=0;
			while(k<nof)
				{
				if(strcmp(field[k],f) ==0 )
					n=k;
				k++;
				}
			int p=n;
			strcat(v,"\n\0");
			if( n!= -1)     // search for the value
				{
				while(p<n_o_l)
					{
					
					if(strcmp(buffer[p],v) == 0)
						{
						cp=p-n;
					    show();
						break;
						}
					p+=nof;
					}
				}
			}
		int connect()
			{
			open = 1;
			// open the file and sort the fields ...
			fp=fopen(fname,"r");
			if(fp == NULL)
				{	// File not found ..
				n_o_l=0;
				cp=0;
				int k=0;
				while(k<nof)
					{
					strcpy(field[k],d_field[k]);
					cntrl[k]=d_cntrl[k];
					k++;
					}
				}
			else     // File exits read the record ...
				{
				fgets(fields,maxlines,fp);
				n_o_l=0;
				while(fgets(buffer[n_o_l++],maxlen,fp)!=NULL);
				n_o_l--;  // adjust the value ..
				cp=0;
				int k=0;
				int d_nof=0;
				int ind=0;
				while(k<strlen(fields))
					{
					if(fields[k]!='|')
					field[d_nof][ind++]=fields[k];
					else
					{
					field[d_nof][ind]='\0';
					d_nof++;
					ind=0;
					}
					k++;
					}
				k=0;
				int j=0,flag=0;
				while(k<d_nof)
					{
					j=0;
					flag=0;
					while(j<nof)
					{
					if(strcmp(field[k],d_field[j])==0)
					   {
					   flag=1;
					   cntrl[k]=d_cntrl[j];
					   break;
					   }
					j++;
					}
					if(flag == 0)
					cntrl[k]=NULL;
					k++;
					}

				nof=d_nof;
				}
			fclose(fp);
			return 1;
			}
		nextrec()
			{
			if(cp+nof >= n_o_l)
				{
				messagebox(" EOF reached ! ",MSG_ALERT);
				}
			else
			       {
			       cp+=nof;
				show();
				}
			}
		prevrec()
			{
			if(cp-nof < 0)
				{
				messagebox(" BOF reached ! ",MSG_ALERT);
				}
			else
				{
				cp-=nof;
				show();
				}
			}
		updaterec()
			{
		     if(!n_o_l)
				{
				messagebox(" No records to Update ! ", MSG_ALERT);
				return 0;

				}
		
			int k=0;
			if(n_o_l)
			while(k<nof)
				{
				strcpy(buffer[cp+k],cntrl[k]->text);
				strcat(buffer[cp+k],"\n\0");
				k++;
				}
			}
		deleterec()
			{
			if(!n_o_l)
				{
				messagebox(" No records to delete ! ", MSG_ALERT);
				return 0;

				}
			int k,j;

			j=0;
			while(j<nof)
			{
			k=cp;
			while(k<n_o_l)
				{
				strcpy(buffer[k],buffer[k+1]);
				k++;
				}
			n_o_l--;
			j++;
			}
			if(cp)
				{
				cp-=nof;
				show();
				}
			else
				{
				k=0;
				while(k<nof)
					{
					cntrl[k]->setval("",true);
					k++;
					}
				}
			}
	};

