//---------------------------------------------------------------------------

#ifndef PingPingH
#define PingPingH
//---------------------------------------------------------------------------
#include <winsock.h>
#include <windowsx.h>
#include <vcl.h>


// Structures required to use functions in ICMP.DLL

typedef struct {
    unsigned char Ttl;                         // Time To Live
    unsigned char Tos;                         // Type Of Service
    unsigned char Flags;                       // IP header flags
    unsigned char OptionsSize;                 // Size in bytes of options data
    unsigned char *OptionsData;                // Pointer to options data
} IP_OPTION_INFORMATION, * PIP_OPTION_INFORMATION;

typedef struct {
    DWORD Address;                             // Replying address
    unsigned long  Status;                     // Reply status
    unsigned long  RoundTripTime;              // RTT in milliseconds
    unsigned short DataSize;                   // Echo data size
    unsigned short Reserved;                   // Reserved for system use
    void *Data;                                // Pointer to the echo data
    IP_OPTION_INFORMATION Options;             // Reply options
} IP_ECHO_REPLY, * PIP_ECHO_REPLY;


    typedef HANDLE (WINAPI* pfnHV)(VOID);
    typedef BOOL (WINAPI* pfnBH)(HANDLE);
    typedef DWORD (WINAPI* pfnDHDPWPipPDD)(HANDLE, DWORD, LPVOID, WORD,PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD); 

class TPing
{
   WSAData wsaData;
   HINSTANCE hIcmp;
   PIP_ECHO_REPLY pIpe;
   pfnHV pIcmpCreateFile;
   pfnBH pIcmpCloseHandle;
   pfnDHDPWPipPDD pIcmpSendEcho;
   char acPingBuffer[64];
  public:
    TPing();
    ~TPing();
    int Create();
    int Ping(AnsiString ip,int &ok,int &time);
};



class TRecord
{
  public:
    void *index;  
    AnsiString A;
    int B;
    AnsiString C;    
};

class TInsertList
{
   TList *index;
 public:
    TInsertList();
    ~TInsertList();
    Add(AnsiString A,int B);
    Add(AnsiString A,AnsiString C);    
    TRecord *Get(int inde);
    int Count();
    DeleteLast();
};

class THostList : public TInsertList
{

  public :
    THostList();
    ~THostList();
    AddHost(AnsiString ip,AnsiString host);
    AnsiString GetHost(int i);
    AnsiString GetHost2(int i);
    TInsertList *GetHostPingList(AnsiString host);
    TInsertList *GetHostPingList(int ii);
    //AnsiString GetHostPingLast(int ii);
    int GetHostPingLast(int ii);         
    AddHostPingTime(AnsiString host,int time);
    AddHostPingTime(int ii,int time);
    bool AnyOutTime();        

};


#endif

