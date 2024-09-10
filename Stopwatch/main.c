/*
 * main.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Ibrahim Refaey
 */

/******************LIB*******************/
#include "LIB/STD_Types.h"
#include "LIB/BIT_MATH.h"

/*****************MCAL*******************/
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/EXI/EXTI_Interface.h"
#include "MCAL/TIMERS/TIMERS_Interface.h"
#include "MCAL/DIO/DIO_Interface.h"

/*****************HAL*******************/

/****************Delay******************/
#include "avr/delay.h"

/************Global Variables***********/
/***************Handlers****************/
#define OVERFLOW		30
u8 counter = 0;
u8 SEC=0;
u8 MIN=0;
u8 HR=0;

void func(void)
{
	counter++;
	if(counter == OVERFLOW)
	{
		counter=0;
		SEC++;
		if(SEC == 60)
		{
			SEC=0;
			MIN++;
			if(MIN == 60)
			{
				HR++;
				MIN=0;
			}
		}

	}

}
void RESET_Fun(void)
{
	SEC=0;
	MIN=0;
	HR=0;
	counter = 0;
	TIMER0_voidSetPreload(0);
}
void Pause_Fun(void)
{
	TIMER0_u8SetPrescalar(TIMER_NO_CLOCK_SOURCE);
}
void RESUME_Fun(void)
{
	TIMER0_u8SetPrescalar(TIMER_DIVISION_FACTOR_1024);

}

int main(void)
{
	/******************Initialize******************/
	GIE_voidEnable();
	EXTI_voidInit();
	TIMER0_voidInit();

	/*Reset Button*/
	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);
	/*Pause Button*/
	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_INPUT);
	/*RESUME Button*/
	DIO_u8SetPinDirection(DIO_PORTB,DIO_PIN2,DIO_PIN_INPUT);
	/*Port value of 7 segment */
	DIO_u8SetPortDirection(DIO_PORTC,DIO_PORT_OUTPUT);
	/*7 Segment Selection Pins*/
	DIO_u8SetPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTA,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTA,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTA,DIO_PIN4,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTA,DIO_PIN5,DIO_PIN_OUTPUT);

	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_LOW);
	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN1,DIO_PIN_LOW);
	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_LOW);
	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_LOW);
	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);

	TIMER_u8SetCallBack(func,TIMER0_OVF_VECTOR_ID);
	EXTI_u8Int0SetCallBack(RESET_Fun);
	EXTI_u8Int1SetCallBack(Pause_Fun);
	EXTI_u8Int2SetCallBack(RESUME_Fun);


	while(1)
	{

		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_HIGH);
		DIO_u8SetPortValue(DIO_PORTC,SEC%10);
		_delay_ms(5);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_LOW);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN1,DIO_PIN_HIGH);
		DIO_u8SetPortValue(DIO_PORTC,SEC/10);
		_delay_ms(5);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN1,DIO_PIN_LOW);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_HIGH);
		DIO_u8SetPortValue(DIO_PORTC,MIN%10);
		_delay_ms(5);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_LOW);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_HIGH);
		DIO_u8SetPortValue(DIO_PORTC,MIN/10);
		_delay_ms(5);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_LOW);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
		DIO_u8SetPortValue(DIO_PORTC,HR%10);
		_delay_ms(5);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_HIGH);
		DIO_u8SetPortValue(DIO_PORTC,HR/10);
		_delay_ms(5);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);

	}
	return 0;
}

