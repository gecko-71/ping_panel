//---------------------------------------------------------------------------

#pragma hdrstop

#include "wykres.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


TWykres::TWykres(TCanvas *can,int x,int y,int dx , int dy)
{
  Canvas=can;
  xx=x;
  yy=y;
  dxx=dx;
  dyy=dy;
  incxx=xx;
};


TWykres::~TWykres()
{

};

void TWykres::Paint()
{
  Canvas->TextOut(xx,yy,"AAAAAAAAAA");
  //PaintOneBar();
};


void TWykres::SetW(int x,int y,int dx , int dy)
{
  xtime=0;
  zoom=0;
  xx=x;
  yy=y; // wysokosc
  dxx=dx;
  dyy=dy;
  incxx=xx;
};


void TWykres::SetBarZoom(int max_time)
{
   int h;
   h=yy-dyy;
   zoom=h/max_time;
};



void TWykres::PaintOneBar(int time)
{
   int L ;
   L=zoom*time;
   incxx=incxx+1;
   Canvas->MoveTo(incxx,yy-L);
   Canvas->LineTo(incxx,yy);
};


