unit AppBar2;

interface

uses
  ShellAPI,
  Forms,
  Types,
  Windows,
  Messages;

const
  APPBAR_CALLBACK = WM_USER + 6438;

type
  TAppBar = class
  private
    FAppBarData: TAppBarData;
    FEdge:       UINT;
    FRect:       TRect;
    FAppForm:    TForm;
    FRegistered: Boolean;
    procedure AppBarRegister;
    procedure AppBarSetPos;
    procedure AppBarPosChanged;
  public
    constructor Create(AForm: TForm);
    destructor Destroy; override;

    procedure RegisterAppBar(uEdge: UINT);
    procedure AppBarCallback(hwndAccessBar: HWND; uNotifyMsg: UINT; lParam: 
      LPARAM);
  end;

implementation

{ TAppBar }

procedure TAppBar.AppBarCallback(hwndAccessBar: HWND; uNotifyMsg: UINT; lParam: LPARAM);
begin
  FAppBarData.hWnd := hwndAccessBar;
  case uNotifyMsg of
    {ABN_STATECHANGE:
    begin
      uState := SHAppBarMessage(ABM_GETSTATE, FAppBarData);

      SetWindowPos(hwndAccessBar,
        (ABS_ALWAYSONTOP and uState) or HWND_TOPMOST or HWND_BOTTOM,
        0, 0, 0, 0, SWP_NOMOVE or SWP_NOSIZE or SWP_NOACTIVATE);
    end;
    ABN_FULLSCREENAPP:
    begin
      if lParam > 0 then
        SetWindowPos(hwndAccessBar,
          (ABS_ALWAYSONTOP and uState) or HWND_TOPMOST or HWND_BOTTOM,
          0, 0, 0, 0, SWP_NOMOVE or SWP_NOSIZE or SWP_NOACTIVATE)
      else
      begin
        uState := SHAppBarMessage(ABM_GETSTATE, abd);
        if (uState <> 0 and ABS_ALWAYSONTOP) then
          SetWindowPos(hwndAccessBar, HWND_TOPMOST,
            0, 0, 0, 0,
            SWP_NOMOVE or SWP_NOSIZE or SWP_NOACTIVATE);
      end;
    end;     }
    ABN_POSCHANGED:
      AppBarPosChanged;
  end;
end;

procedure TAppBar.AppBarPosChanged;
var
  AppBArWidth, AppBarHeight: integer;
begin
  with FAppBarData do
  begin
    GetWindowRect(hWnd, FRect);
    AppBarWidth := rc.Right - rc.Left;
    AppBarHeight := rc.Bottom - rc.Top;

    FRect.Top := 0;
    FRect.Left := 0;
    FRect.Right := GetSystemMetrics(SM_CXSCREEN);
    FRect.Bottom := GetSystemMetrics(SM_CYSCREEN);

    case FEdge of
      ABE_LEFT: rc.Right := rc.Left + AppBarWidth;
      ABE_RIGHT: rc.Left := rc.Right - AppBarWidth;
      ABE_TOP: rc.Bottom := rc.Top + AppBarHeight;
      ABE_BOTTOM: rc.Top := rc.Bottom - AppBarHeight;
    end;

    AppBarSetPos;
  end;
end;

procedure TAppBar.AppBarRegister;
begin
  SHAppBarMessage(ABM_NEW, FAppBarData);
  FRegistered := True;
  AppBarSetPos;
end;

procedure TAppBar.AppBarSetPos;
var
  AppBArWidth, AppBarHeight: integer;
begin
  with FAppBarData do
  begin
    AppBArWidth  := 0;
    AppBarHeight := 0;

    rc.Top := 0;
    rc.Left := 0;
    rc.Right := GetSystemMetrics(SM_CXSCREEN);
    rc.Bottom := GetSystemMetrics(SM_CYSCREEN);

    uEdge := FEdge;

    if FEdge in [ABE_LEFT, ABE_RIGHT] then
    begin
      AppBarWidth := FRect.Right - FRect.Left;
      rc.Top := 0;
      rc.Bottom := GetSystemMetrics(SM_CYSCREEN);
    end
    else
    begin
      AppBarHeight := FRect.Bottom - FRect.Top;
      rc.Left  := 0;
      rc.Right := GetSystemMetrics(SM_CXSCREEN);
    end;

    SHAppBarMessage(ABM_QUERYPOS, FAppBarData);

    case FEdge of
      ABE_LEFT: rc.Right := rc.Left + AppBarWidth;
      ABE_RIGHT: rc.Left := rc.Right - AppBarWidth;
      ABE_TOP: rc.Bottom := rc.Top + AppBarHeight;
      ABE_BOTTOM: rc.Top := rc.Bottom - AppBarHeight;
    end;

    SHAppBarMessage(ABM_SETPOS, FAppBarData);

    MoveWindow(hWnd, rc.Left, rc.Top, rc.Right - rc.Left, rc.Bottom - rc.Top, True);

    FAppForm.BoundsRect := rc;
  end;
end;

constructor TAppBar.Create(AForm: TForm);
begin
  FAppForm := AForm;
  FRect := AForm.BoundsRect;
  FAppBarData.cbSize := SizeOf(APPBARDATA);
  FAppBarData.hWnd := FAppForm.Handle;
  FAppBarData.uCallbackMessage := APPBAR_CALLBACK;
  FRegistered := False;
end;

destructor TAppBar.Destroy;
begin
  if FRegistered then
    SHAppBarMessage(ABM_REMOVE, FAppBarData);
  inherited;
end;

procedure TAppBar.RegisterAppBar(uEdge: UINT);
begin
  FEdge := uEdge;
  AppBarRegister;
end;

end.