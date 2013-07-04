//---------------------------------------------------------------------------

#include <vcl.h>
#include <winsock.h>
#include <windowsx.h>
#include <classes.hpp>
#include "PingPing.h"


#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"

//#pragma link "CoolTrayIcon"
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  incre=0;
}
//---------------------------------------------------------------------------






void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 delete grLista;
 delete h;
}
///---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
 AnsiString ip;
 int ok;
 int time;
 TPing pi;
 pi.Create();
 // pobranie ip do pingowania
 ip=h->GetHost(incre);
 pi.Ping(ip,ok,time);
 gr1=(TPerformanceGraph *)grLista->Items[incre]; 
 if(ok==0)
 {
   time=9999;
   gr1->DataPoint(clRed,150);
 } else {
   if (time<200)
      gr1->DataPoint(clLime,time);
   else
      gr1->DataPoint(clYellow,200);
 };
 //---
 gr1->Update();

 h->AddHostPingTime(incre,time);

 ++incre;
 if(h->Count()==incre)
    incre=0;
 if(h->AnyOutTime())
   TrayIcon1->IconIndex=1;
 else
   TrayIcon1->IconIndex=0;
 //-----

 Update();
 Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
  int y;
  int w;
  y=15;
  int  time;
  AnsiString  ip;
  AnsiString host;

  for (int i = 0; i < h->Count(); i++)
  {
    ip=h->GetHost(i);
    host=h->GetHost2(i);
    time=h->GetHostPingLast(i);
    Canvas->TextOut(5,y,ip);
    w=Canvas->TextWidth(ip+"w");
    Canvas->TextOut(5+w,y,host);
    y=y+15;
    if (time!=9999)
       Canvas->TextOut(5,y,AnsiString(time)+" ms");
    else Canvas->TextOut(5,y,"#####");
    y=y+12+75;
    Canvas->TextOut(1,y,"-------------------------------------------");
    y=y+25;
  };

}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormCreate(TObject *Sender)
{
   AnsiString ip;
   AnsiString hostname;
   int ok;
   int time;
   TPing pi;
   int aa=50;
   grLista= new TList;
   int pos;

   h= new THostList();
   TStringList *TempList = new TStringList;
   TempList->LoadFromFile("pingowaniet.txt");
   for (int i = 0; i < TempList->Count; i++)
   {
     hostname="";
     pos=TempList->Strings[i].AnsiPos(";");
     if(pos>0)
     {
        ip=TempList->Strings[i].SubString(0,pos-1);
        hostname=TempList->Strings[i].SubString(pos+1,TempList->Strings[i].Length()-pos);
     } else
       ip=TempList->Strings[i];
     h->AddHost(ip,hostname);
     // kreowanie wykresu
     gr1=Creategraph(aa);
     grLista->Add(gr1);
     this->InsertControl(gr1);
     aa=aa+127;
   };
   delete TempList;
   incre=0;
   pi.Create();
   for (int i = 0; i < h->Count(); i++)
   {
     ip=h->GetHost(i);
     pi.Ping(ip,ok,time);
     gr1=(TPerformanceGraph *)grLista->Items[i];
     if(ok==0)
     {
       time=9999;
       gr1->DataPoint(clRed,150);
     } else  gr1->DataPoint(clLime,time);
     gr1->Update();
     h->AddHostPingTime(i,time);
   };
   if(h->AnyOutTime())
      TrayIcon1->IconIndex=1;
   else
     TrayIcon1->IconIndex=0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
  TrayIcon1->Minimize();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------







TPerformanceGraph * TForm1::Creategraph(int t)
{
   TPerformanceGraph *gr= new TPerformanceGraph(this);
   gr->Top=t;
   gr->Left =1;
   gr->Width=130;
   gr->Height=70;
   gr->Kind=pgBar;
   gr->Enabled=true ;
   gr->ForeColor = clGreen;
   gr->BackColor = clBlack;
   gr->GridSize = 5;
   gr->StepSize = 2;
   gr->Scale = 1000;
   gr->Gradient = 100;
   gr->Gridlines = true;
   gr->PenWidth = 1;
   gr->Visible=true ;
   gr->Gridlines=false;
   gr->Update();
   return gr;
}




