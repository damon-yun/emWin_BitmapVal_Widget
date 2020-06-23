/*********************************************************************
----------------------------- MIT License ----------------------------
*  MIT License
*
*  Copyright (c) 2020 damonzhang
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
File        : MainTask.c
Purpose     : a simple test code for BitMapMovie WIDGET.
Requirements: WIDGET_BitMapMovie - (x)

---------------------------END-OF-HEADER------------------------------
*/
#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include "GUI.h"
#include "WM.h"            // MemoryDevices

#include "WIDGET_BitMapVal.h"
/*********************************************************************
*
*       Defines
*
*********************************************************************/

static int        _Play;

extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_0;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_1;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_2;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_3;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_4;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_5;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_6;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_7;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_8;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_9;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_sign;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigit_brand_temp;

const GUI_BITMAP* bitmapval_table[] = { 
    & bmdigit_brand_0, 
    & bmdigit_brand_1,
    & bmdigit_brand_2,
    & bmdigit_brand_3,
    & bmdigit_brand_4,
    & bmdigit_brand_5, 
    & bmdigit_brand_6, 
    & bmdigit_brand_7, 
    & bmdigit_brand_8, 
    & bmdigit_brand_9,
};

BITMAPVAL_Font LightBlueImageVal = {
    .pImageNumTable = bitmapval_table,
    .pImageSign     = &bmdigit_brand_sign,
    .pImageUnits    = &bmdigit_brand_temp,
    .rangMax        = 100,
    .rangMin        = -99,
};



/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
    BITMAPVAL_Handle hMyWidget;
  GUI_Init();
  GUI_SetColor(GUI_BLACK);
  GUI_FillRect(0,0,239,319);

  hMyWidget = BITMAPVAL_Create(0,0,240,320, WM_CF_SHOW, &LightBlueImageVal);

  int i  = - 99;
  while (1) {
      BITMAPVAL_SetVal(hMyWidget, i);
      i++;
      if (i > 101) {
          i = -101;
      }
      GUI_Delay(50);
    
  }
}

/*************************** End of file ****************************/
