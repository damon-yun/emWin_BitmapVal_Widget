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

#ifndef _WIDGET_BITMAP_MOVIE_H_
#define _WIDGET_BITMAP_MOVIE_H_

#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include <stdint.h>        // int32_t uint32_t
#include "GUI.h"
#include "WM.h"            // MemoryDevices

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GUI_BITMMAP_MOVIE_NOTIFICATION_NULL         -1
#define GUI_BITMMAP_MOVIE_NOTIFICATION_PREDRAW       0
#define GUI_BITMMAP_MOVIE_NOTIFICATION_POSTDRAW      1
#define GUI_BITMMAP_MOVIE_NOTIFICATION_START         2
#define GUI_BITMMAP_MOVIE_NOTIFICATION_STOP          3
#define GUI_BITMMAP_MOVIE_NOTIFICATION_END           4
#define GUI_BITMMAP_MOVIE_NOTIFICATION_DELETE        5

/*********************************************************************
*
*       Custom widget data (global)
*
**********************************************************************
*/
/*********************************************************************
*
*       Typedef
*/
typedef struct __bitmap_val {
    const GUI_BITMAP** pImageNumTable;
    const GUI_BITMAP*  pImageSign;
    const GUI_BITMAP*  pImageUnits;
    int rangMax;
    int rangMin;
    int xSize;
    int ySize;
} BITMAPVAL_Font;

typedef WM_HWIN BITMAPVAL_Handle;

typedef void GUI_BITMAP_MOVIE_FUNC(BITMAPVAL_Handle hMovie, int Notification, uint32_t CurrentFrame);

/*********************************************************************
*
*       API
*/
#if defined(__cplusplus)
extern "C" {
#endif

/*********************************************************************
*
*       MYWIDGET_Create
*/
extern BITMAPVAL_Handle BITMAPVAL_Create(int x0, int y0, int xSize, int ySize, int Flags, BITMAPVAL_Font* pFont);

extern BITMAPVAL_Handle BITMAPVAL_CreateAsChild(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int Flags, BITMAPVAL_Font* pFont);

extern int BITMAPVAL_SetVal(BITMAPVAL_Handle handle, int val);

#if defined(__cplusplus)
}
#endif

#endif /* _WIDGET_BITMAP_MOVIE_H_ */

/*************************** End of file ****************************/



