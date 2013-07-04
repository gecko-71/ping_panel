// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AppBar2.pas' rev: 6.00

#ifndef AppBar2HPP
#define AppBar2HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Appbar2
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TAppBar;
class PASCALIMPLEMENTATION TAppBar : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	_AppBarData FAppBarData;
	unsigned FEdge;
	#pragma pack(push, 1)
	Types::TRect FRect;
	#pragma pack(pop)
	
	Forms::TForm* FAppForm;
	bool FRegistered;
	void __fastcall AppBarRegister(void);
	void __fastcall AppBarSetPos(void);
	void __fastcall AppBarPosChanged(void);
	
public:
	__fastcall TAppBar(Forms::TForm* AForm);
	__fastcall virtual ~TAppBar(void);
	void __fastcall RegisterAppBar(unsigned uEdge);
	void __fastcall AppBarCallback(HWND hwndAccessBar, unsigned uNotifyMsg, int lParam);
};


//-- var, const, procedure ---------------------------------------------------
static const Word APPBAR_CALLBACK = 0x1d26;

}	/* namespace Appbar2 */
using namespace Appbar2;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AppBar2
