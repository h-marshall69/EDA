#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "BKtree.h"

HINSTANCE hInst;

BKTree* tree = new BKTree();

HWND hwndDrawingArea;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        hwndDrawingArea = GetDlgItem(hwndDlg, AREA_DE_DIBUJO);
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
            case BOTON: {
                //MessageBox(hwndDlg, "Botón presionado", "Información", MB_OK | MB_ICONINFORMATION);
                char buffer[256];
                GetDlgItemText(hwndDlg, EDITA, buffer, sizeof(buffer));
                std::string texto = buffer;
                tree->insertar(texto);
                HDC hdc = GetDC(hwndDrawingArea);
                //TextOut(hdc, 300, 300, texto.c_str(), texto.length());
                tree->inorden(hdc);
                ReleaseDC(hwndDrawingArea, hdc);
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
