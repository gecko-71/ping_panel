//---------------------------------------------------------------------------


#pragma hdrstop

#include "PingPing.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TPing::TPing()
{
}

TPing::~TPing()
{
  FreeLibrary(hIcmp);
  WSACleanup();
}


int TPing::Create()
{
  if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        return 0;
  }
  // Load the ICMP.DLL
  hIcmp = LoadLibrary("ICMP.DLL");
  if (hIcmp == 0) {
      return 0;
  }
    // Get handles to the functions inside ICMP.DLL that we'll need
    pIcmpCreateFile = (pfnHV)GetProcAddress(hIcmp,
            "IcmpCreateFile");
    pIcmpCloseHandle = (pfnBH)GetProcAddress(hIcmp,
            "IcmpCloseHandle");
    pIcmpSendEcho = (pfnDHDPWPipPDD)GetProcAddress(hIcmp,
            "IcmpSendEcho");
    if ((pIcmpCreateFile == 0) || (pIcmpCloseHandle == 0) ||
            (pIcmpSendEcho == 0)) {
        return 0;
    }


  return 1;
};



int TPing::Ping(AnsiString ip,int &ok,int &time)
{
    ok=0;
    struct hostent* phe ;
    if ((phe = gethostbyname(ip.c_str())) == 0)
      return 0;

    HANDLE hIP = pIcmpCreateFile();
    if (hIP == INVALID_HANDLE_VALUE) return 0;
    memset(acPingBuffer, '\xAA', sizeof(acPingBuffer));
    PIP_ECHO_REPLY pIpe = (PIP_ECHO_REPLY)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,sizeof(IP_ECHO_REPLY) + sizeof(acPingBuffer));
    if (pIpe == 0) {
       return 0;
    }

    pIpe->Data = acPingBuffer;
    pIpe->DataSize = sizeof(acPingBuffer);

    // Send the ping packet
    DWORD dwStatus = pIcmpSendEcho(hIP, *((DWORD*)phe->h_addr_list[0]),
            acPingBuffer, sizeof(acPingBuffer), NULL, pIpe,
            sizeof(IP_ECHO_REPLY) + sizeof(acPingBuffer), 2400);
    if (dwStatus != 0) {
       if (pIpe->Status>0) ok=0;
       else {
         time=int(pIpe->RoundTripTime);
         ok=1;
       };
    }
    else {
        ok=0;
    }
 //----------------------
 GlobalFree(pIpe);
 return 1;
} ;

//----------------------------




//----------------------------
TInsertList::TInsertList()
{

  index=new TList;

};


TInsertList::~TInsertList()
{
  TRecord *R;
  TInsertList *rr;

  for (int i = 0; i < index->Count; i++)

  {
    R = (TRecord *) index->Items[i];
    rr=(TInsertList *) R->index;;
    delete rr;
    delete R;
  };

  delete index;
};



TInsertList::Add(AnsiString A,int B)
{
  TRecord *R;
  TInsertList *Ins;
  Ins = new TInsertList;
  R= new TRecord;
  R->A=A;
  R->B=B;
  R->index=Ins;
  index->Insert(0,R);
  DeleteLast();
  return 0;
};

TInsertList::Add(AnsiString A,AnsiString C)
{
  TRecord *R;
  TInsertList *Ins;
  Ins = new TInsertList;
  R= new TRecord;
  R->A=A;
  R->B=0;
  R->C=C;
  R->index=Ins;
  index->Insert(0,R);
  DeleteLast();
  return 0;
};



TInsertList::DeleteLast()
{
    TRecord *R;
    TInsertList *rr;

    int i=20;
    if(index->Count==i )
    {
      R = (TRecord *) index->Items[i-1];
      rr=(TInsertList *) R->index;;
      delete rr;
      delete R;
      index->Delete(i-1);
    }
  return 0;
};


TRecord *TInsertList::Get(int inde)
{
  TRecord *R;
  R = (TRecord *) index->Items[inde];
  return R;
};

int TInsertList::Count()
{
  return index->Count ;
};


//----
THostList::THostList()
{

};

THostList::~THostList()
{

};


THostList::AddHost(AnsiString ip,AnsiString host)
{
  Add(ip,host);
  return 0;
};





int THostList::GetHostPingLast(int ii)
{

  TRecord *r;
  TInsertList * rr;
  r=(TRecord *) Get(ii);
  rr =(TInsertList *) r->index;
  if(rr->Count()!=0)
  {
     r=(TRecord *)rr->Get(0);
     return r->B;
  } else return 0;

};


TInsertList *THostList::GetHostPingList(AnsiString host)
{

  TRecord *r;
  TInsertList * rr;
  int ii =Count();
  for (int i = 0; i < ii; i++)
  {
     r=(TRecord *) Get(i);
     if (r->A==host)
     {
       rr =(TInsertList *) r->index;
       return rr;
     }
  };
  return NULL;
};


TInsertList *THostList::GetHostPingList(int ii)
{

  TRecord *r;
  TInsertList * rr;
  r=(TRecord *) Get(ii);
  rr =(TInsertList *) r->index;
  return rr;
};





THostList::AddHostPingTime(int ii,int time)
{
  TRecord *r;
  TInsertList *rr;
  r=(TRecord *) Get(ii);
  rr =(TInsertList *) r->index;
  rr->Add(r->A,time);
  return 0;
};

THostList::AddHostPingTime(AnsiString host,int time)
{

  TRecord *r;
  TInsertList *rr;
  int ii =Count();
  for (int i = 0; i < ii; i++)
  {
     r=(TRecord *) Get(i);
     if (r->A==host)
     {
       rr =(TInsertList *) r->index;
       rr->Add(host,time);
     };
  };
  return 0;
};


AnsiString THostList::GetHost(int i)
{
  TRecord *r;
  r=(TRecord *) Get(i);
  return r->A;
};

AnsiString THostList::GetHost2(int i)
{
  TRecord *r;
  r=(TRecord *) Get(i);
  return r->C;
};



bool THostList::AnyOutTime()
{
  TRecord *r;
  TInsertList *rr;
  int ii =Count();
  for (int i = 0; i < ii; i++)
  {
     r=(TRecord *) Get(i);
       rr =(TInsertList *) r->index;
       r=rr->Get(0);
       if(r->B==9999)
         return FALSE;
  };
  return TRUE;
}



