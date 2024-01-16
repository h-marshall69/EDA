#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "BKtree.h"

HINSTANCE hInst;

BKtree tree;

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
            case BOTONA: {
                //MessageBox(hwndDlg, "Botón presionado", "Información", MB_OK | MB_ICONINFORMATION);
                char buffer[256];
                GetDlgItemText(hwndDlg, EDITA, buffer, sizeof(buffer));
                std::string texto = buffer;
                tree.insertar(texto);
                HDC hdc = GetDC(hwndDrawingArea);
                //TextOut(hdc, 300, 300, texto.c_str(), texto.length());
                tree.mostrar(hdc, 650, 150);
                tree.xmostrar();
                std::cout << std::endl;
                ReleaseDC(hwndDrawingArea, hdc);
            }
            return TRUE;
            case BOTONB: {
                char buffer[256];
                int tolerancia = GetDlgItemInt(hwndDlg, TOL, nullptr, TRUE);
                GetDlgItemText(hwndDlg, EDITB, buffer, sizeof(buffer));
                std::string texto = buffer;
                std::vector<std::string> matc = tree.similares(texto, tolerancia);
                std::string tm = "";
                for(const auto& m : matc)
                    tm += m + ", ";
                SetDlgItemText(hwndDlg, EDITD, tm.c_str());
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
