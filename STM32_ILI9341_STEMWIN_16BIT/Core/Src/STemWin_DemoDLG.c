/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "stm32f4xx_hal.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0    (GUI_ID_USER + 0x00)
#define ID_GRAPH_0    (GUI_ID_USER + 0x01)
#define ID_TEXT_0    (GUI_ID_USER + 0x02)
#define ID_TEXT_1    (GUI_ID_USER + 0x03)
#define ID_PROGBAR_0    (GUI_ID_USER + 0x04)
#define ID_TEXT_2    (GUI_ID_USER + 0x05)


// USER START (Optionally insert additional defines)
// USER END

extern ADC_HandleTypeDef hadc1;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "STemWin_Demo", ID_FRAMEWIN_0, 0, 0, 320, 240, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 1, 26, 309, 159, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "ADC Value:", ID_TEXT_0, 7, 4, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 65, 2, 65, 20, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 6, 191, 258, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 275, 193, 34, 20, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'ADC Value:'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_13_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_20_ASCII);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateSTemWin_Demo
*/
WM_HWIN MainLCDTask(void) {
  char i=0,x=0;
  int ADC_Value;
  char str[15];
  int StartTime,StopTime;
  WM_HWIN hWin;
  WM_HWIN hGraph;
  PROGBAR_Handle   	hPbar;
  TEXT_Handle	   	hText1,hText2;
  GRAPH_DATA_Handle hData;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);

  hPbar = WM_GetDialogItem(hWin, ID_PROGBAR_0);

  hText1 = WM_GetDialogItem(hWin, ID_TEXT_1);

  hText2 = WM_GetDialogItem(hWin, ID_TEXT_2);

  hGraph = WM_GetDialogItem(hWin, ID_GRAPH_0);


  hData = GRAPH_DATA_YT_Create(GUI_RED, 200, NULL, 0);
  GRAPH_DATA_YT_SetAlign(hData, GRAPH_ALIGN_LEFT);
  GRAPH_AttachData(hGraph, hData);

  GRAPH_SetGridVis(hGraph, 1);
  GRAPH_SetBorder(hGraph, 30, 0, 0, 0);

  while(1)
  {
	 PROGBAR_SetValue(hPbar, i++);
     if(i>100) i = 0;

     HAL_ADC_Start(&hadc1);
     HAL_ADC_PollForConversion(&hadc1, 50);
     ADC_Value = HAL_ADC_GetValue(&hadc1);
     HAL_ADC_Stop(&hadc1);
     itoa(ADC_Value,str,10);
     TEXT_SetText(hText1, str);

     itoa(StopTime,str,10);
     TEXT_SetText(hText2, str);

     x++;
     if(x>200)
     {
    	 x=0;
    	 GRAPH_DATA_YT_Clear(hData);
     }

     GRAPH_DATA_YT_AddValue(hData, ADC_Value/20);


	 HAL_Delay(100);

	 StartTime = HAL_GetTick();
	 GUI_Exec();
	 StopTime = HAL_GetTick() - StartTime;
  }

  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
