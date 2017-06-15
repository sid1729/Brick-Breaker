#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<fstream.h>
#include<string.h>
struct grid
{
 int xb,yb,c;
};
struct highscores
{
  char name[30];
  int  score;
};
float mx,my;
grid A[6][8];
int level_no,score,gameover;
void page2()
{
 setbkcolor(YELLOW);
 settextstyle(5,0,9);
 outtextxy(100,100,"BRICK");
 outtextxy(200,250,"BREAKER");
 getch();
 cleardevice();
}
void page3()
{
 cleardevice();
 setbkcolor(YELLOW);
 settextstyle(5,0,5);
 setcolor(BLUE);
 outtextxy(100,100,"Level");
 outtextxy(200,250,"Completed");
 sleep(3);
 getch();
 cleardevice();
}
void page4()
{
 cleardevice();
 setbkcolor(YELLOW);
 settextstyle(5,0,5);
 setcolor(BLUE);
 outtextxy(100,100,"Congratulation");
 outtextxy(200,250,"You WON");
 sleep(3);
 getch();
 cleardevice();
}
void page1()
 {
  setbkcolor(MAGENTA);
  settextstyle(1,0,5);
  setcolor(BLUE);
  outtextxy(40,55,"SSSVV");
  settextstyle(4,0,5);
  outtextxy(80,120,"A Computer Project On ");
  settextstyle(10,0,2);
  outtextxy(120,190,"BRICK BREAKER");
  settextstyle(3,0,4);
  outtextxy(40,275,"SUBMITTED BY:");
  outtextxy(340,275,"SUBMITTED TO :");
  outtextxy(40,325,"SIDDHARTH INANI");
  outtextxy(340,325,"JASPAL MA'AM");
  getch();
  cleardevice();
}
void ballmovement(float &x,float &y,float m,float ib,float cb)
{
  static float tempx,tempy;
  float bmove;
  switch(level_no)
  {
   case 1 : bmove=0.2;
	     break;
   case 2 : bmove=0.22;
	     break;
   case 3 : bmove=0.24;
	     break;
   case 4 : bmove=0.26;
	     break;
   case 5 : bmove=0.28;
	     break;
  }
  x=x+(bmove*ib);         //movement of ball
  y=m*x+cb;
  setcolor(RED);
  circle(x,y,20);
  setfillstyle(4,GREEN);
  floodfill(x,y,RED);
  setcolor(BLUE);
  circle(tempx,tempy,20);
  setfillstyle(4,BLUE);
  floodfill(x,y,BLUE);
  tempx=x;
  tempy=y;
}
void bar(float &xd,float &yd)
{
 int k=0;
 float bmove;
 char ch;
 while(kbhit())           //to check whether key was pressed
 {
  ch=getch();
  k=1;
 }
 switch(level_no)
 {
   case 1 : bmove=10;
	     break;
   case 2 : bmove=13;
	     break;
   case 3 : bmove=15;
	     break;
   case 4 : bmove=17;
	     break;
   case 5 : bmove=20;
	     break;
 }
 if(ch==77&&xd+100<mx&&k==1)
 {
  setcolor(BLUE);                       // movement of bar
  rectangle(xd,yd,xd+100,yd+10);
  xd+=bmove;k=0;
  setcolor(WHITE);
  rectangle(xd,yd,xd+100,yd+10);
 }
 if(ch==75&&xd>0&&k==1)
 {
  setcolor(BLUE);
  rectangle(xd,yd,xd+100,yd+10);
  xd-=bmove;k=0;
  setcolor(WHITE);
  rectangle(xd,yd,xd+100,yd+10);
 }
}
void drawbricks()  //to draw bricks
{
 int i=0,j=0,a;
 A[0][0].c=1;
 A[0][0].yb=75;
 for(i=0;i<6;i++)
 {
  A[i][0].xb=65;
  if(i==0)
  {
   a= A[i][j].yb=A[i][j].yb+25;
  }
  else
  {
   a=A[i][j].yb=A[i-1][j].yb+25;
  }
  for(j=0;j<8;j++)
  {
   A[i][j].yb=a;
   if(j==0)
   {
    A[i][j].xb=A[i][j].xb+50;
   }
   else
   {
    A[i][j].xb=A[i][j-1].xb+50;
   }
   switch(level_no)          //to set the pattern of bricks for diff levels
   {
    case 1 : A[i][j].c=1;
	     break;
    case 2 : if(j%2==0)
	      A[i][j].c=1;
	     else
	      A[i][j].c=0;
	     break;
    case 3 : if(j==i||j==8-i)
	      A[i][j].c=1;
	     else
	      A[i][j].c=0;
	     break;
    case 4 : if(i%2==0)
	      A[i][j].c=1;
	     else
	      A[i][j].c=0;
	     break;
    case 5 : if(j%2==0&&i%2==0)
	      A[i][j].c=1;
	     else
	      A[i][j].c=0;
	     break;
   }
  }
  j=0;
 }
 for(i=0;i<6;i++)
 {
  for(j=0;j<8;j++)
  {
   if(A[i][j].c==1)
   {
    setcolor(3);
    rectangle(A[i][j].xb,A[i][j].yb,A[i][j].xb+50,A[i][j].yb+25);
   }
   else
   {
    setcolor(BLUE);
    rectangle(A[i][j].xb,A[i][j].yb,A[i][j].xb+50,A[i][j].yb+25);
   }
  }
 }
}
void level()               //function to run the levels
{
 int a,k=1,i,j;
 float x=30,y=30,m,cb=0,ib=1;
 float xd=0.0,yd=0.0;
 yd=getmaxy()-10;
 mx=getmaxx();
 mx=getmaxx();
 my=getmaxy();
 m=random(4);
 if(m==0)
  m=3;
 setbkcolor(BLUE);
 drawbricks();
 l:
 do
 {
  bar(xd,yd);
  ballmovement(x,y,m,ib,cb);
  for(i=0;i<6;i++)        //to check which brick was hit by the ball
  {
   for(j=0;j<8;j++)
   {
    if(A[i][j].c==1)
    {
     setcolor(3);
     rectangle(A[i][j].xb,A[i][j].yb,A[i][j].xb+50,A[i][j].yb+25);
     if(x>=A[i][j].xb-20&&x<=A[i][j].xb+70&&y>=A[i][j].yb-20&&y<=A[i][j].yb+70)
     {
      A[i][j].c=0;
      setcolor(BLUE);
      rectangle(A[i][j].xb,A[i][j].yb,A[i][j].xb+50,A[i][j].yb+25);
      if(x>=A[i][j].xb-20&&x<=A[i][j].xb-15&&y>=A[i][j].yb-20&&y<=A[i][j].yb+70)
      {
       score++;
       m=-m;               //reflection from bricks
       cb=y-m*x;
       ib=-ib;
       goto l;
      }
      if(x>=A[i][j].xb+65&&x<=A[i][j].xb+70&&y>=A[i][j].yb-20&&y<=A[i][j].yb+70)
      {
       score++;
       m=-m;                 //reflection from bricks
       cb=y-m*x;
       ib=-ib;
       goto l;
      }
      if(x>=A[i][j].xb-20&&x<=A[i][j].xb+70&&y>=A[i][j].yb-20&&y<=A[i][j].yb-15)
      {
       score++;
       m=-m;                 //reflection from bricks
       cb=y-m*x;
       goto l;
      }
      if(x>=A[i][j].xb-20&&x<=A[i][j].xb+70&&y>=A[i][j].yb+65&&y<=A[i][j].yb+70)
      {
       score++;
       m=-m;                 //reflection from bricks
       cb=y-m*x;
       goto l;
      }
     }
    }
   }
  }
 }while(x<=mx-20&&x>=20&&y<=my-30&&y>=20&&k==1);
 k=0;
 for(i=0;i<6;i++)
 {
  for(j=0;j<8;j++)
  {                        //to whether all bricks were destroyed or not
   if(A[i][j].c==1)
    k=1;
  }
 }
 if(y>=my-30&&x>=xd-10&&x<=xd+110&&k==1)
 {
  m=-m;                  //reflection from bar
  cb=y-m*x;
  goto l;
 }
 if(x>=mx-20&&k==1)
 {
  m=-m;
  cb=y-m*x;             //reflection from walls
  ib=-ib;
  goto l;
 }
 if(x<=20&&k==1)
 {
  m=-m;                 //reflection from walls
  cb=y-m*x;
  ib=-ib;
  goto l;
 }
 if(y<=20&&k==1)
 {
  m=-m;                 //reflection from walls
  cb=y-m*x;
  goto l;
 }
 if(k==1&&y>=my-30)
 {
  cleardevice();              //the condition of game over
  setbkcolor(BLUE);
  settextstyle(1,0,2);
  outtextxy(250,150,"Game Over");
  sleep(2);
  gameover=1;
 }
}
void main()
{
 clrscr();
 highscores B;
 char ch[2];
 ch[1]='\0';
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\tc\\BGI");
 randomize();
 fstream f("score.txt",ios::binary|ios::app|ios::in);
 int i,j;
 page1();      //to display page 1
 page2();      //to display page 2
 level_no=1;
 gameover=0;
 score=0;
 for(i=1;i<=5&&!gameover;i++)
 {
  level();
  if(gameover==0)
  {
   page3();
   level_no++;
   if(level_no==6)
    page4();
   score+=10;
  }
 }
 if(gameover==1)
 {
  i=75;                          //to display the score
  B.name[0]='\n';
  cleardevice();
  setbkcolor(BLUE);
  settextstyle(1,0,2);
  j=150;
  outtextxy(j,i,"Enter your name");
  i+=20;
  while(ch[0]!=13)
  {
   ch[0]=getch();
   outtextxy(j,i,ch);
   j+=10;
   strcat(B.name,ch);
  }
  i+=20;
  outtextxy(150,i,"Your score");
  i+=20;
  ch[0]=score%10+48;
  outtextxy(160,i,ch);
  ch[0]=score/10+48;
  outtextxy(150,i,ch);
  sleep(3);
  B.score=score;
  f.write((char*)&B,sizeof(B));
  cleardevice();
  getch();
  closegraph();
  f.close();
  f.open("score.txt",ios::binary|ios::app|ios::out|ios::in);
  f.seekg(0);
  f.read((char*)&B,sizeof(B));
  cout<<"\t"<<B.score<<"\t"<<B.name<<"\n";
  while(!f.eof())
  {
   f.read((char*)&B,sizeof(B));
   cout<<"\t"<<B.score<<"\t"<<B.name<<"\n";
  }
 }
 f.close();
 getch();
}
