/*
 * adc.c
 *
 *  Created on: 6 Oct 2023
 *      Author: maria
 */
/* includes */
#include "adc.h"
#include"common_macros.h"
#include <avr/io.h>


/*function Definitions */
/*description :initialize the ADC:
 * 1.choose the mood of vref
 * 2. initially choose channel 0 (pin0)
 * 3.ADC enable
 * 4.disable the interrupt as we are working with powlling
 * 5.set the prescaler of the clk */

void ADC_init(const ADC_ConfigType * Config_ptr){
	/* pick the mood of Vref*/
	ADMUX =(ADMUX &0X3F)|(Config_ptr->ref_volt);


	/* choose channel 0 initially */
	ADMUX &=0XE0;

	/*enable the ADC */
	SET_BIT(ADCSRA,ADEN);

	/* disable the interrupt */
	CLEAR_BIT(ADCSRA,ADIE);

	/* set clk prescaler  */

	ADCSRA =(ADCSRA&0XF8)|(Config_ptr->prescaler);

}

/*description: a fn that read take the channel number as input and return the
 * value detected input is 8_bit as there is 8_pins(8 channels) to read from and 16_bit output
 * as the ADC perform the reading in 10 bits */
uint16 ADC_readChannel(uint8 channel_num){


	/* insert the channel in ADMUX */
	ADMUX =(ADMUX&0XE0)|(channel_num&0x07);


	/* start conversion by setting ADSC bit in ADCSRA reg */
	SET_BIT(ADCSRA,ADSC);

	/* polling until flag =1*/
	while(GET_BIT(ADCSRA,ADIF )!=1){

	}
	/* clear flag */
	SET_BIT(ADCSRA,ADIF);
	/*return the data output by ADC -> defined of avr library */
	return ADC;
}

