#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "Vptree.h"
Vptree tree;

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
        tree.insert(P(xPos, yPos));
        InvalidateRect(hwndDlg, NULL, TRUE);
    }
    return TRUE;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwndDlg, &ps);
        for(auto d: tree.data_set) {
            Ellipse(hdc, d.x - 5, d.y - 5, d.x + 5, d.y + 5);
            char Cad[20];
            itoa(d.x, Cad, 10);
            int len = strlen(Cad);
            TextOut(hdc, d.x - 30, d.y + 10, Cad, len);

            char Cad1[20];
            itoa(d.y, Cad1, 10);
            int len1 = strlen(Cad1);
            TextOut(hdc, d.x + 5, d.y + 10, Cad1, len1);
        }
        tree.buil_tree();
        tree.preorden();
        tree.xpreorden(hdc,730,70,730,70,100);
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
                int x = GetDlgItemInt(hwndDlg, EDITX, nullptr, TRUE);
                int y = GetDlgItemInt(hwndDlg, EDITY, nullptr, TRUE);
                tree.eliminar(P(x, y));
                tree.buil_tree();
                InvalidateRect(hwndDlg, NULL, TRUE);
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
