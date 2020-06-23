/*********************************************************************
*  Author : Damon Zhang
*  E-mail : damonzhang92@gmail.com
----------------------------- MIT License ----------------------------
*  MIT License
*
*  Copyright (c) 2020 Damon Zhang
*  All rights reserved.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
----------------------------------------------------------------------
File        : WIDGET_BitMapMovie.c
Purpose     : A Custom emWin Widget Type to achieve Bitmap format picture movie play.
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              Bitmap        - ( )
---------------------------END-OF-HEADER------------------------------
*/
#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include "GUI.h"
#include "GUI_Type.h"
#include "WM.h"            // MemoryDevices

#include "WIDGET_BitMapVal.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define BITMMAPVAL_CF_HCENTER      0
#define BITMMAPVAL_CF_LEFT         1
#define BITMMAPVAL_CF_RIGHT        2

#ifndef MYGUI_BITMAPVAL_SUPPORT_DECIMAL
    #define MYGUI_BITMAPVAL_SUPPORT_DECIMAL 0
#endif
/*********************************************************************
*
*       BitMapMovie widget data (global)
*
**********************************************************************
*/
/*********************************************************************
*
*       Typedef
*/
typedef struct _bitmap_val_userdata {
    BITMAPVAL_Font* pFont;
    int align;
    int val;
} BITMAPVAL_UserData;

#define BITMAPVAL_USERDATA_SIZE  (sizeof(BITMAPVAL_UserData))

/*********************************************************************
*
*       BitMapMovie widget function prototypes (global)
*
**********************************************************************
*/

/*********************************************************************
*
*       BitMapMovie widget functions (global)
*
**********************************************************************
*/
static int __val_get_len(int val)
{
    int n = 0;

    while (val != 0) {
        n++;
        val /= 10;
    }

    return n;
}

/*********************************************************************
*
*       MYWIDGET_Callback
*/
static void __BITMAPVAL_DefalutCallBack(WM_MESSAGE * pMsg) 
{
    WM_HWIN hWin;
    BITMAPVAL_UserData UserData;
    GUI_BITMAP** pImageNumTable;
    GUI_BITMAP* pImageSign;
    GUI_BITMAP* pImageUnits;
    char valBuffer[10];
    int x0 = 0;
    int y0 = 0;
    int xSize = 0;
    int ySize = 0;
    int valLen = 0;
    int n = 0;
    int val = 0;

    memset(valBuffer, 0x0, 10);

    hWin = pMsg->hWin;

    switch (pMsg->MsgId) {

    case WM_USER + 1:
        WM_GetUserData(hWin, &UserData, BITMAPVAL_USERDATA_SIZE);
        if ((pMsg->Data.v < (UserData.pFont)->rangMin) || (pMsg->Data.v > (UserData.pFont)->rangMax)) {
            break;
        }
        UserData.val = pMsg->Data.v;
        WM_SetUserData(hWin, &UserData, BITMAPVAL_USERDATA_SIZE);
        WM_Invalidate(hWin);
        break;

    case WM_PAINT:
        WM_GetUserData(hWin, &UserData, BITMAPVAL_USERDATA_SIZE);
        pImageNumTable = UserData.pFont->pImageNumTable;
        pImageSign = UserData.pFont->pImageSign;
        pImageUnits = UserData.pFont->pImageUnits;

        valLen = sprintf(valBuffer, "%d", UserData.val);
        if (UserData.val < 0) {
            valLen -= 1;
            n += 1;
        }

        xSize = WM_GetWindowSizeX(hWin);
        ySize = WM_GetWindowSizeY(hWin);
        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(0, 0, xSize-1, ySize-1);
        x0 = (xSize - (pImageNumTable[0]->XSize * valLen)) / 2;

        //Draw Sign
        if (UserData.val < 0) {
            x0 -= (pImageSign->XSize);
            y0 = (ySize - pImageSign->YSize) / 2;
            GUI_DrawBitmap(pImageSign, x0, y0);
            x0 += pImageSign->XSize;
        }
        //Draw Digit
        val = UserData.val;
        y0 = (ySize - pImageNumTable[0]->YSize) / 2;
        while (valLen != 0) {
            GUI_DrawBitmap(pImageNumTable[valBuffer[n]-'0'], x0, y0);
            x0 += pImageNumTable[0]->XSize;
            valLen--;
            n++;
        }
        //Draw Units
        y0 = (ySize - pImageUnits->YSize) / 2;
        GUI_DrawBitmap(pImageUnits, x0, y0);
    break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}

int BITMAPVAL_SetVal(BITMAPVAL_Handle handle, int val)
{
    WM_MESSAGE msg = {
      .hWin = handle,
      .MsgId = WM_USER + 1,
      .Data.v = val,
    };

    WM_SendMessage(handle, &msg);

    return 0;
}
/*********************************************************************
*
*       MYWIDGET_Create
*/
BITMAPVAL_Handle BITMAPVAL_CreateAsChild(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int Flags, BITMAPVAL_Font* pFont) 
{
    BITMAPVAL_Handle   hWin;
    BITMAPVAL_UserData UserData;

    if (pFont == NULL || pFont->pImageNumTable == NULL) {
    
    }

    hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent, Flags, __BITMAPVAL_DefalutCallBack, BITMAPVAL_USERDATA_SIZE);
    UserData.pFont = pFont;
    UserData.align = BITMMAPVAL_CF_HCENTER;
    UserData.val = 0;

    WM_SetUserData(hWin, &UserData, BITMAPVAL_USERDATA_SIZE);

    return hWin;
}

BITMAPVAL_Handle BITMAPVAL_Create(int x0, int y0, int xSize, int ySize, int Flags, BITMAPVAL_Font *pFont)
{
    BITMAPVAL_Handle   hWin;

    hWin = BITMAPVAL_CreateAsChild(x0, y0, xSize, ySize, WM_HBKWIN, Flags, pFont);

    return hWin;
}

/*********************************************************************
*
*       GUI_BITMAP_MOVIE_Delete
*/
//void GUI_BITMAP_MOVIE_Delete(GUI_BITMAP_MOVIE_Handle hWin)
//{
//    GUI_BitMap_Movie_UserData MovieUserData;
//    WM_GetUserData(hWin, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));
//    WM_DeleteTimer(MovieUserData.hTimer);
//    WM_DeleteWindow(hWin);
//}


/*************************** End of file ****************************/

