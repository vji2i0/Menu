/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"

/* USER CODE BEGIN 0 */
#include <stdio.h>
#include <stdbool.h>
#include "LCD.h"
#include "MenuLibrary.h"

extern volatile unsigned int Lines;
extern volatile unsigned int MenuLayers;
extern volatile unsigned int CurrentLayer;
extern volatile int CurrentMenuPosition[MENU_LAYERS];
extern volatile int portAPin15Counter;
extern volatile _Bool SetLCD;
extern volatile unsigned int PeriodsToGo;
extern volatile _Bool UpdateLCD;
extern volatile unsigned int PhaseLCD;
extern volatile const int TotalPhasesLCDSetup;
extern volatile const int TotalPhasesLCDUpdate;
extern volatile char Text[4][16];
extern volatile unsigned int colomn;
extern volatile unsigned int row;

/*For timer debouncing*/
extern volatile int jTimer;
extern volatile int jOnDOWN; //PC10
extern volatile int jOnUP; //PA15
extern volatile int jOnOK; //PB4
extern volatile int jOnBACK; //PB5
extern volatile const int CheckCircles;
extern volatile const int jOnThreshold;


/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Prefetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
  jTimer+=1;
  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) & GPIO_PIN_SET){//DOWN is pressed
    jOnDOWN+=1;
  }
  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) & GPIO_PIN_SET){//UP is pressed
    jOnUP+=1;
  }
  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) & GPIO_PIN_SET){//OK is pressed
    jOnOK+=1;
  }
  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) & GPIO_PIN_SET){//BACK is pressed
    jOnBACK+=1;
  }
  if (jTimer == CheckCircles){
    if (jOnDOWN > jOnThreshold)
    {/*Button DOWN is pressed*/
      if (CurrentMenuPosition[CurrentLayer]==1)
      {
        Text[1][0] = ' ';
        Text[2][0] = '>';
        CurrentMenuPosition[CurrentLayer]+=1;
        UpdateLCD = true;
      }else{
        volatile int bufPosition = CurrentMenuPosition[CurrentLayer];
        CurrentMenuPosition[CurrentLayer]+=1;
        if (MenuOption(CurrentMenuPosition)[1]==' ')
        {
          CurrentMenuPosition[CurrentLayer]=bufPosition;
        }else{
          CurrentMenuPosition[CurrentLayer]+=1;
          if (MenuOption(CurrentMenuPosition)[1]==' ')
          {
            Text[2][0] = ' ';
            Text[3][0] = '>';
            CurrentMenuPosition[CurrentLayer]=bufPosition;
            CurrentMenuPosition[CurrentLayer]+=1;
            UpdateLCD = true;
          }else{
            volatile int i;
            CurrentMenuPosition[CurrentLayer]=bufPosition;
            for (i=1; i<Lines+1; i++)
            {
              sprintf(Text[i],MenuOption(CurrentMenuPosition));
              CurrentMenuPosition[CurrentLayer]+=1;
            };
            CurrentMenuPosition[CurrentLayer]=bufPosition;
            CurrentMenuPosition[CurrentLayer]+=1;
            Text[2][0] = '>';
            UpdateLCD = true;
          }
        }
      }
    };/*That is all for the button DOWN*/
    if (jOnUP > jOnThreshold)
    {/*Button UP is pressed*/
      if (CurrentMenuPosition[CurrentLayer]==1)
      {}else if(CurrentMenuPosition[CurrentLayer]==2){
        Text[1][0] = '>';
        Text[2][0] = ' ';
        CurrentMenuPosition[CurrentLayer]-=1;
        UpdateLCD = true;
      }else{
        volatile int bufPosition = CurrentMenuPosition[CurrentLayer];
        CurrentMenuPosition[CurrentLayer]+=1;
        if (MenuOption(CurrentMenuPosition)[1]==' ')
        {
          Text[2][0] = '>';
          Text[3][0] = ' ';
          CurrentMenuPosition[CurrentLayer]=bufPosition;
          CurrentMenuPosition[CurrentLayer]-=1;
          UpdateLCD = true;
        }else{
          CurrentMenuPosition[CurrentLayer]=bufPosition;
          CurrentMenuPosition[CurrentLayer]-=2;
          volatile int i;
          for (i=1; i<Lines+1; i++)
          {
            sprintf(Text[i],MenuOption(CurrentMenuPosition));
            CurrentMenuPosition[CurrentLayer]+=1;
          };
          CurrentMenuPosition[CurrentLayer]=bufPosition;
          CurrentMenuPosition[CurrentLayer]-=1;
          Text[2][0] = '>';
          UpdateLCD = true;
        }
      }
    };/*That is all for the button UP*/
    if (jOnOK > jOnThreshold)
    {/*Button OK is pressed*/
      CurrentLayer+=1;
      CurrentMenuPosition[CurrentLayer]=1;
      if (MenuOption(CurrentMenuPosition)[1]==' ')
      {
        CurrentMenuPosition[CurrentLayer]=0;
        CurrentLayer-=1;
      }else{
        volatile int bufPosition=CurrentMenuPosition[CurrentLayer];
        sprintf(Text[0],MenuTitle(CurrentMenuPosition));
        volatile int i;
        for (i=1; i<Lines+1; i++)
        {
          sprintf(Text[i],MenuOption(CurrentMenuPosition));
          CurrentMenuPosition[CurrentLayer]+=1;
        };
        CurrentMenuPosition[CurrentLayer]=bufPosition;
        Text[1][0] = '>';
        UpdateLCD = true;
      }
    };/*That is all for the button OK*/
    if (jOnBACK > jOnThreshold)
    {/*Button BACK is pressed*/
      if (CurrentLayer > 0)
      {
        CurrentMenuPosition[CurrentLayer]=0;
        CurrentLayer-=1;
        volatile int bufPosition=CurrentMenuPosition[CurrentLayer];
        sprintf(Text[0],MenuTitle(CurrentMenuPosition));



        if (CurrentMenuPosition[CurrentLayer]==1)
        {
          volatile int i;
          for (i=1; i<Lines+1; i++)
          {
            sprintf(Text[i],MenuOption(CurrentMenuPosition));
            CurrentMenuPosition[CurrentLayer]+=1;
          };
          CurrentMenuPosition[CurrentLayer]=bufPosition;
          Text[1][0] = '>';
          Text[2][0] = ' ';
          Text[3][0] = ' ';
          UpdateLCD = true;
        }else if (CurrentMenuPosition[CurrentLayer]==2){
          volatile int i;
          CurrentMenuPosition[CurrentLayer]-=1;
          for (i=1; i<Lines+1; i++)
          {
            sprintf(Text[i],MenuOption(CurrentMenuPosition));
            CurrentMenuPosition[CurrentLayer]+=1;
          };
          CurrentMenuPosition[CurrentLayer]=bufPosition;
          Text[1][0] = ' ';
          Text[2][0] = '>';
          Text[3][0] = ' ';
          UpdateLCD = true;
        }else{
          CurrentMenuPosition[CurrentLayer]+=1;
          if (MenuOption(CurrentMenuPosition)[1]==' ')
          {
            volatile int i;
            CurrentMenuPosition[CurrentLayer]-=3;
            for (i=1; i<Lines+1; i++)
            {
              sprintf(Text[i],MenuOption(CurrentMenuPosition));
              CurrentMenuPosition[CurrentLayer]+=1;
            };
            CurrentMenuPosition[CurrentLayer]=bufPosition;
            Text[1][0] = ' ';
            Text[2][0] = ' ';
            Text[3][0] = '>';
            UpdateLCD = true;
          }else{
            volatile int i;
            CurrentMenuPosition[CurrentLayer]-=2;
            for (i=1; i<Lines+1; i++)
            {
              sprintf(Text[i],MenuOption(CurrentMenuPosition));
              CurrentMenuPosition[CurrentLayer]+=1;
            };
            CurrentMenuPosition[CurrentLayer]=bufPosition;
            Text[1][0] = ' ';
            Text[2][0] = '>';
            Text[3][0] = ' ';
            UpdateLCD = true;
          }
        }
      }
    };/*That is all for the button BACK*/
    jTimer=0;
    jOnUP=0;
    jOnDOWN=0;
    jOnOK=0;
    jOnBACK=0;
  }

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles TIM3 global interrupt.
*/
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
  if (PeriodsToGo == 0)
  {
    if (SetLCD)
    {
      if (UpdateLCD)
      {
        LCDUpdate(PhaseLCD,Text[row-1][colomn-1],row,colomn);
        PeriodsToGo = LCDUpdatePeriodsToGo(PhaseLCD);
        if (PhaseLCD == TotalPhasesLCDSetup)
        {
          PhaseLCD=1;
          colomn+=1;
          if (colomn>16)
          {
           colomn=1;
           row+=1;
          }
          if (row>4)
          {
            row=1;
            UpdateLCD=false;
          }
        }else{
          PhaseLCD+=1;
        }
      }
      //LCDUpdate(PhaseLCD, text[colomn][row])
      //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
    }else{
      LCDSet(PhaseLCD);
      PeriodsToGo = LCDSetPeriodsToGo(PhaseLCD);
      if (PhaseLCD == TotalPhasesLCDSetup)
      {
        PhaseLCD=1;
        SetLCD=true;
        colomn=1;
        row=1;
        //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
      }else{
        PhaseLCD+=1;
      }
    }
  }else{PeriodsToGo-=1;}

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
