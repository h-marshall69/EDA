#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "marshall.h"
std::vector<P> pt;


HINSTANCE hInst;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
    }
    return TRUE;
    case WM_LBUTTONDOWN: {
        long xPos = GET_X_LPARAM(lParam);
        long yPos = GET_Y_LPARAM(lParam);
        pt.push_back(P(xPos, yPos));
        InvalidateRect(hwndDlg, NULL, TRUE);
    }
    return TRUE;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwndDlg, &ps);
        for(auto it: pt) {
            Ellipse(hdc, it.x - 5, it.y - 5, it.x + 5, it.y + 5);
        }
        if(pt.size() > 1) {
            std::vector<std::pair<double, P>> sp;
            for(int i = 0; i < pt.size(); i++) {
                int j = 0;
                while(j < i) {
                    sp.push_back(std::make_pair(distancia(pt[i], pt[j]), pt[j]));
                    j++;
                }
            }
            quickSort(sp, 0, sp.size() - 1);
            P v = sp[int(sp.size()/2)].second;
            double c = sp[int(sp.size()/2)].first;

            Arc(hdc, v.x - c, v.y - c, v.x + c, v.y + c, 0, 0, 0, 0);
        }
        EndPaint(hwndDlg, &ps);
    }
    return TRUE;
    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
            case BOTONA: {

                /*PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwndDlg, &ps);
                for(int i = 0; i < pt.size(); i++) {
                    int j = 0;
                    while(j < i) {
                        sp.push_back(std::make_pair(distancia(pt[i], pt[j]), pt[j]));
                        j++;
                    }
                }
                quickSort(sp, 0, sp.size() - 1);
                for(auto i : sp) {
                    std::cout << i.first << " ";
                }
                std::cout << std::endl;
                P v = sp[int(sp.size()/2)].second;
                double c = sp[int(sp.size()/2)].first;
                //std::cout << c << std::endl;

                Arc(hdc, v.x - 10, v.y - 10, v.x + 10, v.y + 10, 0, 0, 0, 0);

                InvalidateRect(hwndDlg, NULL, TRUE);*/
            }
            return TRUE;
        }
    }
    return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
