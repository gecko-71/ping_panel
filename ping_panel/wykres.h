//---------------------------------------------------------------------------

#ifndef wykresH
#define wykresH
//---------------------------------------------------------------------------
#include <graphics.hpp>

class TWykres
{
    int xx;
    int yy;
    int dxx;
    int dyy;
    int xtime;
    int zoom;
    int incxx;    
    TCanvas *Canvas;
  public:
     TWykres(TCanvas *can,int x,int y,int dx , int dy);
     ~TWykres();
     void Paint();
     void SetW(int x,int y,int dx , int dy);
     void SetBarZoom(int max_time);
     void PaintOneBar(int time);     
};

#endif
