/*
 * system.c
 *
 *  Created on: 12 Oct 2023
 *      Author: maria
 */
#include "lm35_sensor.h"
#include"gpio.h"
#include"lcd.h"
#include "adc.h"
#include<util/delay.h>
#include<avr/interrupt.h>
#include "dc_motor.h"
#include<avr/io.h>
#include "std_types.h"
int main (){
	/*enable the ADC */
	ADC_ConfigType adc={INTERNAL_REF,F_CPU_8};
	ADC_init(&adc);


	/*enble the LCD and display welcome statement */
	LCD_init();
	LCD_displayString("  Welcome to Fan ");
	LCD_displayStringRowColumn(1,0,"Controlled Sys  ");
	_delay_ms(1000);
	LCD_clearScreen();

	/*enable the Ibit*/
	SREG |=(1<<7);



	/*enable the DC_motor */
	DcMotor_init();

	LCD_displayString("  Fan is ");
	LCD_displayStringRowColumn(1,3,"Temp =    C");


	uint8 temp_value=0;


	while(1)
	{
		/*sense the temp */
		temp_value=LM35_getTemperature();

		LCD_moveCursor(1,5);
		if(temp_value<30){
			LCD_displayStringRowColumn(0,10,"OFF");
			/*display temp value */
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp_value);
			LCD_displayCharacter( ' ');
			/*stop rotation */
			DcMotor_Rotate(STOP,0);

		}
		else if ((temp_value>=30)&&(temp_value<60)){
			LCD_displayStringRowColumn(0,10,"ON");
			LCD_displayCharacter(' ');
			/*display temp value */
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp_value);
			LCD_displayCharacter(' ');
//			/*stop rotation */
			DcMotor_Rotate(CW,(uint8)(64));

		}
		else if ((temp_value>=60)&&(temp_value<90)){
			LCD_displayStringRowColumn(0,10,"ON");
			LCD_displayCharacter(' ');
			/*display temp value */
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp_value);
			LCD_displayCharacter(' ');
			/*stop rotation */
			DcMotor_Rotate(CW,(uint8)(128));

		}
		else if ((temp_value>=90)&&(temp_value<120)){
			LCD_displayStringRowColumn(0,10,"ON");
			LCD_displayCharacter(' ');
			/*display temp value */
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp_value);
			if(temp_value<100)
				LCD_displayCharacter(' ');
			/*stop rotation */
			DcMotor_Rotate(CW,(uint8)(192));

		}
		else if (temp_value>=120){
			LCD_displayStringRowColumn(0,10,"ON");
			LCD_displayCharacter(' ');
			/*display temp value */
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp_value);
			/*stop rotation */
			DcMotor_Rotate(CW,(uint8)255);

		}

	}
}
