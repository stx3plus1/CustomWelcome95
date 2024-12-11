/*
 * CustomWelcome95
 * by stx3plus1
 */

#include <windows.h>
#include <string>
#include <ctime>

#include "resource.h"

/*
 * Control element IDs
 */

#define IDC_NEXTTIP 16901
#define IDC_DIDYOUKNOW 16910
#define IDC_TEXTCONTROL 16908
#define IDC_TIP 16905
#define IDC_WHATSNEW 16898
#define IDC_ONLINEREGISTRATION 16899
#define IDC_WINDOWSTOUR 16897
#define IDC_CATALOG 16900
#define IDC_APPICON 16909
#define IDC_BITMAP 16906
#define IDC_CHECKBOX 16903

/*
 * Various strings
 */

const char* strings[] = {
    "Loneliness is an emotion.\nEmotions are weakness.\n\nUninstall them by going to the Control Panel and selecting Add/Remove Emotions.",
	"I need MS-DOS. Please give me MS-DOS.",
	"You have no importance here\nYou can now leave\nYou are allowed to exit",
	"You didn't know this.",
	"Notice: If you notice this notice you will notice that this notice is not worth noticing.",
	"Destroy System32",
	"where's the fucking soil",
	"the cake is a lie",
	"The longer the icon of sin stays on earth, the stronger he will become"
};
const int numStrings = sizeof(strings) / sizeof(strings[0]);

const char* msgtitle = "Microsoft Windows";
const char* errmsg = "Nothing's new. Windows 95 has been installed for quite a while.";
const char* warnmsg = "Windows 95 does not think so.\nYou have been revoked of your network access.\n\"Try again later\".";
const char* tourmsg = "The Windows 95 tour has been missing for a long time.";
const char* catalog = "You already installed it all.";
const char* tipwarning = "You weren't supposed to do that.";

/* 
 * Code
 */

int strIndex;
HBRUSH hBackgroundBrush;

BOOL CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
		case WM_INITDIALOG: {
			srand(time(NULL));
			strIndex = rand() % numStrings;

			SetDlgItemTextA(hDlg, IDC_TIP, strings[strIndex]);

			HWND hDidYouKnow = GetDlgItem(hDlg, IDC_DIDYOUKNOW);
			HWND hTip = GetDlgItem(hDlg, IDC_TIP);
			HWND hTextControl = GetDlgItem(hDlg, IDC_TEXTCONTROL);
			HWND hIcon = GetDlgItem(hDlg, IDC_APPICON);

			HFONT hFont, hOldFont;
			LOGFONT lf = { 0 };
			hFont = (HFONT)SendMessage(hTip, WM_GETFONT, 0, 0);
			if (hFont) GetObject(hFont, sizeof(LOGFONT), &lf);
			lf.lfWeight = FW_BOLD;
			hFont = CreateFontIndirect(&lf);
			hOldFont = (HFONT)SendMessage(hDidYouKnow, WM_SETFONT, (WPARAM)hFont, TRUE);
			if (hOldFont) DeleteObject(hOldFont);

			hBackgroundBrush = CreateSolidBrush(RGB(255, 255, 225));
			SendDlgItemMessage(hDlg, 16903, BM_SETCHECK, BST_CHECKED, 0);
			
			HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_WELCOME), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
			SendDlgItemMessage(hDlg, IDC_BITMAP, STM_SETIMAGE, 0, (LPARAM)hBitmap);
		}
			return (INT_PTR)TRUE;
		case WM_CTLCOLORSTATIC: {
			int id = GetWindowLong((HWND)lParam, GWL_ID);
				if (id != IDC_CHECKBOX) {
					SetBkMode((HDC)wParam, TRANSPARENT); 
					return (INT_PTR)hBackgroundBrush;
				}
			}
			break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			if (LOWORD(wParam) == IDC_NEXTTIP) {
				HWND hCheckbox = GetDlgItem(hDlg, IDC_CHECKBOX);
				int state = SendMessage(hCheckbox, BM_GETCHECK, 0, 0);
				if (state == BST_CHECKED) {
					strIndex++;
					if ((strIndex + 1) > numStrings) {
						strIndex = 0;
					}
					SetDlgItemTextA(hDlg, IDC_TIP, strings[strIndex]);
				} else
					SetDlgItemTextA(hDlg, IDC_TIP, tipwarning);
				return (INT_PTR)TRUE;
			}
			if (LOWORD(wParam) == IDC_WHATSNEW) {
				MessageBoxA(hDlg, errmsg, msgtitle, MB_ICONWARNING);
				return (INT_PTR)TRUE;
			}
			if (LOWORD(wParam) == IDC_ONLINEREGISTRATION) {
				MessageBoxA(hDlg, warnmsg, msgtitle, MB_ICONSTOP);
				return (INT_PTR)TRUE;
			}
			if (LOWORD(wParam) == IDC_WINDOWSTOUR) {
				MessageBoxA(hDlg, tourmsg, msgtitle, MB_ICONWARNING);
			}
			if(LOWORD(wParam) == IDC_CATALOG) {
				MessageBoxA(hDlg, catalog, msgtitle, MB_ICONSTOP);
			}
			if (LOWORD(wParam) == IDC_CHECKBOX) {
				HWND hCheckbox = GetDlgItem(hDlg, IDC_CHECKBOX);
				int state = SendMessage(hCheckbox, BM_GETCHECK, 0, 0);
				if (state == BST_CHECKED)
					SetDlgItemTextA(hDlg, IDC_TIP, strings[strIndex]);
				else
					SetDlgItemTextA(hDlg, IDC_TIP, tipwarning);
				return (INT_PTR)TRUE;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_WELCOMEBOX), NULL, MainDialogProc);
	return 0;
}