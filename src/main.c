/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 6.0.0   2016-09-27

The MIT License (MIT)
Copyright (c) 2009-2016 Atollic AB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************
*/

/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"


/* Private typedef */
/* Private define  */
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */


/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	//u1
	//LED3 init
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	GPIOA->MODER |= (uint32_t)(0b01) << (5*2);
	GPIOA->OTYPER &= ~(uint16_t)(0b1) << 5;
	GPIOA->PUPDR |= (uint32_t)(0b01) << (5*2);
	GPIOA->OSPEEDR |= (uint32_t)(0b11) << (5*2);

	//LED3 ODR toggle
	GPIOA->ODR |= (uint16_t)(0b1) << 5;
	GPIOA->ODR &= ~(uint16_t)(0b1) << 5;

	//LED3 set/reset toggle
	GPIOA->BSRRL |= (uint16_t)(0b1) << 5;
	GPIOA->BSRRL &= ~(uint16_t)(0b1)<< 5;
	GPIOA->BSRRH |= (uint16_t)(0b1) << 5;
	GPIOA->BSRRH &= ~(uint16_t)(0b1) << 5;


	GPIOA->ODR ^= (uint16_t)(0b1) << 5; //toggle LED3
	GPIOA->ODR ^= (uint16_t)(0b1) << 5; //toggle LED3
	GPIOA->ODR ^= (uint16_t)(0b1) << 5; //toggle LED3
	GPIOA->ODR ^= (uint16_t)(0b1) << 5; //toggle LED3

	//u2
	//But1 init
	GPIOC->MODER &= ~(uint32_t)(0b11) << 26;
	GPIOC->OTYPER &= ~(uint16_t)(0b1) << 13;
	GPIOC->PUPDR &= ~(uint32_t)(0b11) << 26;

	int Button = 0;
	uint16_t ButtonIDR = 0;
	ButtonIDR = GPIOC->IDR;
	ButtonIDR &= (uint16_t)(0b1) << 13;
	Button = !(ButtonIDR >> 13);

	//u3
	long pocitadlo = 0;
	int ButtonPressed = 0;
	int Filter = 0;

  /* TODO - Add your application code here */


  /* Infinite loop */
  while (1)
  {
	  //blikac
	  /*pocitadlo++;
	  if (pocitadlo > 1000000)
	  {
		  GPIOA->ODR ^= (uint16_t)(0b1) << 5; //toggle LED3
		  pocitadlo = 0;
	  }*/

	  /*//LED sledovac vstupu
	  ButtonIDR = GPIOC->IDR;
	  ButtonIDR &= (uint16_t)(0b1) << 13;
	  Button = (int)!(ButtonIDR >> 13);
	  if (Button == 0)
	  {
		  GPIOA->ODR &= ~(uint16_t)(0b1) << 5; //switch off LED
	  }
	  else
	  {
		  GPIOA->ODR |= (uint16_t)(0b1) << 5; //switch on LED
	  }*/
	  //LED prepinanie tlacidlom
	  	  ButtonIDR = GPIOC->IDR;
	  	  ButtonIDR &= (uint16_t)(0b1) << 13;
	  	  Button = !(ButtonIDR >> 13);
	  	  Filter++;
	  	  if(ButtonPressed == 0)
	  	  {
	  		  if(Button == 0)
	  		  {
	  			  Filter = 0;
	  		  }
	  		  if(Filter > 100)
	  		  {
	  			  ButtonPressed = 1;
	  			  GPIOA->ODR ^= (uint16_t)(0b1) << 5; //toggle LED3
	  		  }
	  	  }
	  	  else if(ButtonPressed == 1)
	  	  {
	  		  if(Button == 1)
	  		  {
	  			  Filter = 0;
	  		  }
	  		  if(Filter > 100)
	  		  {
	  			  ButtonPressed = 0;
	  		  }
	  	  }

  }
  return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
