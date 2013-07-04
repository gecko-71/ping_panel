//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//#include <sqlitedbu.hpp>
#include "PERFGRAP.h"
#include "CoolTrayIcon.hpp"
#include <Menus.hpp>
#include "trayicon.h"
#include <ImgList.hpp>
//#include "easythrd.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TButton *Button1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Show1;
        TMenuItem *Exit1;
        TTrayIcon *TrayIcon1;
        TImageList *ImageList1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
private:	// User declarations

public:		// User declarations
   //     TSQLiteDB *FDb;
  //      TSQLiteDB *FDb2;
        int incre;
        THostList *h;
        TList *grLista;
        TPerformanceGraph *gr1;                
        __fastcall TForm1(TComponent* Owner);
        TPerformanceGraph *Creategraph(int t);        

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
