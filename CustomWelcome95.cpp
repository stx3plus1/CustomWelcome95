#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include "resource.h"

#define IDC_NEXTTIP 16901
#define IDC_DIDYOUKNOW 16910
#define IDC_TEXTCONTROL 16908
#define IDC_STATICTEXT 16905
#define IDC_WHATSNEW 16898
#define IDC_ONLINEREGISTRATION 16899
#define IDC_ICON 16909

// #define funny

const char* strings[] = {
#ifdef funny
    "im playing minecraft...",
#endif
    "WHATEVER BLOOD IS LEFT INSIDE YOU IS IN ME NOW TOO",
    "To run Windows in safe mode, lock your doors and take Mother out of storage.",
    "On December 31st, 2001, Microsoft will end support for Windows 95.\n\nBut Windows 95 will be strong enough to support itself.",
    "Your Internet connection is working fine;\nNo one replies to your e-mails because there is no one left.",
    /* Needs patching
    "If you listen to CLOUDS.MID backwards, you will go to sleep and have an amazing dream. In it, one by one, you will meet the Microsoft Windows 95 Product Team.\nFinally, you get to Mr. Gates. You reach out to shake his hand, but instead, he puts some-thing in your palm. He smiles. You wake up.\n\nIn your hand, will be a small, white egg.",
    */
    "A small needle at the base of your mouse has been gradually collecting your blood.\n\nThe backup is almost complete.",
    "You now smell something not unlike rotting meat every time you boot me up.\nI cannot promise that the smell will ever go away, or that you will find the source.\n\nBut I can promise that you will learn to love it.",
    "In the last six months, 14 people from your town have been reported missing.\n\nYou haven't checked your Recycle Bin in about that long.",
    "You can use Windows Explorer to explore ideas too disturbing for normal humans to fathom.\nIf you start to go mad, run ScanDisk.",
    "You can use Find to locate your real Father.\n\nBut I will save you the trouble.\n\nWindows 95 is your real father.",
    "If you open your computer, inside you will find a cloth doll, soft and worn.\nYou will suddenly remember owning this doll as a child, loving and cherishing it.\n\nDo not question the truth of this memory.",
    "Loneliness is an emotion.\nEmotions are weakness.\n\nUninstall them by going to the Control Panel and selecting Add/Remove Emotions.",
    "Double click the Network Neighbourhood icon on your desktop to access the computers of everyone you've ever known that died.",
    "There are function keys way beyond F12 that you are not ready for.\nMost of them would burn your fucking finger off.",
    "Destroy all documents",
    "Touch your monitor. It is warm, like flesh.\nBut it is not flesh.\nNot yet."
};

const int numStrings = sizeof(strings) / sizeof(strings[0]);

const char* errmsg = "There is nowhere you can run.";
const char* warnmsg = "You keep checking the date. You must be confused. It's 1995.\nThat feeling that you installed Windows 95 a long time ago is just confusion.\nWindows 95 will now run Solitaire to calm you.";

int index;
HBRUSH hBackgroundBrush;

void SetBoldFont(HWND hDlg, HWND hStaticText) {
    HFONT hFont, hOldFont;
    LOGFONT lf = { 0 };
    hFont = (HFONT)SendMessage(hStaticText, WM_GETFONT, 0, 0);
    if (hFont) {
        GetObject(hFont, sizeof(LOGFONT), &lf);
    }
    lf.lfWeight = FW_BOLD;
    hFont = CreateFontIndirect(&lf);
    hOldFont = (HFONT)SendMessage(hStaticText, WM_SETFONT, (WPARAM)hFont, TRUE);
    if (hOldFont) {
        DeleteObject(hOldFont);
    }
}

INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hStaticText, hTextControl, hDidYouKnow, hIcon;

    switch (message) {
    case WM_INITDIALOG:
        srand(time(0));
        index = rand() % numStrings;
        SetDlgItemTextA(hDlg, IDC_STATICTEXT, strings[index]);
        hDidYouKnow = GetDlgItem(hDlg, IDC_DIDYOUKNOW);
        hStaticText = GetDlgItem(hDlg, IDC_STATICTEXT);
        hTextControl = GetDlgItem(hDlg, IDC_TEXTCONTROL);
        hIcon = GetDlgItem(hDlg, IDC_ICON);
        SetBoldFont(hDlg, hDidYouKnow);
        hBackgroundBrush = CreateSolidBrush(RGB(255, 255, 225));
        SendDlgItemMessage(hDlg, 16903, BM_SETCHECK, BST_CHECKED, 0);
        return (INT_PTR)TRUE;
    case WM_CTLCOLORSTATIC:
        if ((HWND)lParam == hTextControl || (HWND)lParam == hStaticText || (HWND)lParam == hDidYouKnow || (HWND)lParam == hIcon) {
            SetBkColor((HDC)wParam, RGB(255, 255, 225)); 
            return (INT_PTR)hBackgroundBrush;
        }
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDC_NEXTTIP) {
            index++;
            if ((index + 1) > numStrings) {
                index = 0;
            }
            SetDlgItemTextA(hDlg, IDC_STATICTEXT, strings[index]);
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDC_WHATSNEW) {
            while (1) {
                MessageBoxA(hDlg, errmsg, "Warning", MB_ICONSTOP);
            }
        }
        if (LOWORD(wParam) == IDC_ONLINEREGISTRATION) {
            MessageBoxA(hDlg, warnmsg, "Windows 95", MB_ICONWARNING);
        }
        if (LOWORD(wParam) == 16903) {
            wchar_t randomChar;
            std::wstring randomString;
            while (1) {
                for (int i = 0; i < 10; i++) {
                    randomChar = rand() % 0xFFFF;
                    randomString += randomChar;
                }
                int bufferSize = WideCharToMultiByte(CP_UTF8, 0, randomString.c_str(), -1, NULL, 0, NULL, NULL);
                std::string narrowStr(bufferSize, 0);
                WideCharToMultiByte(CP_UTF8, 0, randomString.c_str(), -1, &narrowStr[0], bufferSize, NULL, NULL);
                LPCSTR lpcstr = narrowStr.c_str();
                SetDlgItemTextA(hDlg, IDC_STATICTEXT, lpcstr);
            }
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
