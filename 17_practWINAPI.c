#include <windows.h>

LRESULT CALLBACK MainWinProc(HWND,UINT,WPARAM,LPARAM);
#define ID_MYBUTTON 1    

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int ss) {
    /* создаем и регистрируем класс главного окна */
    WNDCLASS wc;
    wc.style=0;
    wc.lpfnWndProc=MainWinProc;
    wc.cbClsExtra=wc.cbWndExtra=0;
    wc.hInstance=hInst;
    wc.hIcon=LoadIcon(hInst,"Ex4_Icon");
    wc.hCursor=NULL;
    wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName="Ex4_Menu";
    wc.lpszClassName="Meaw";
    if (!RegisterClass(&wc)) return FALSE;

    /* создаем главное окно и отображаем его */
    HWND hMainWnd=CreateWindow("Meaw","Kalmykova Pavel",WS_OVERLAPPEDWINDOW|ES_AUTOHSCROLL|ES_AUTOVSCROLL,
    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInst,NULL);
    if (!hMainWnd) return FALSE;
    ShowWindow(hMainWnd,ss);
    UpdateWindow(hMainWnd);

    MSG msg; 
    while (GetMessage(&msg,NULL,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK MainWinProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp) {
    char buf[256];
    switch (msg) {
        case WM_CREATE:
            CreateWindow("button","Don't press", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
                300,300,100,20,hw,(HMENU)ID_MYBUTTON,NULL,NULL);
            CreateWindow("button","Press",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
                 300,250,100,20,hw,(HMENU)2,NULL,NULL);
            CreateWindow("button","One",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
                 300,200,100,20,hw,(HMENU)5,NULL,NULL); 
            CreateWindow("button","two",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
                 300,225,100,20,hw,(HMENU)6,NULL,NULL);     

            return 0;
        case WM_COMMAND:
            if ((HIWORD(wp)==0) && (LOWORD(wp)==ID_MYBUTTON)) {
            
             MessageBox(NULL, "gai buuton(modal)", "DONT DO DIS gay", MB_OK | MB_ICONINFORMATION);
            }
            if ((HIWORD(wp)==0) && (LOWORD(wp)==2))
                MessageBox(
                    hw,
                    "Hello Friend, can you help me find the backpack",
                    "MessageBox",MB_OK
                );
            if ((HIWORD(wp)==0) && (LOWORD(wp)==5)){
                MessageBox(
                    hw,
                    "Hello world",
                    "MessageBox",MB_OK
                );  
                 MessageBox(
                    hw,
                    "one more message - hello world",
                    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",MB_OK
                ); 
                 MessageBox(
                    hw,
                    "again - hello world",
                    "MessageBox",MB_OK
                ); 
            } ;
            if ((HIWORD(wp)==0) && (LOWORD(wp)==6)){
                MessageBox(NULL, "gai buuton (non-modal)", "NO_INFO_PLS", MB_OK | MB_ICONINFORMATION);
            } ;
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hw,msg,wp,lp);
}