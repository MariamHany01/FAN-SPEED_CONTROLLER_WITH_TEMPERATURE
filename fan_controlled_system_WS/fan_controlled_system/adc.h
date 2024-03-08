/*
 * adc.h
 *
 *  Created on: 10 Oct 2023
 *      Author: maria
 */

/*
 * adc.h
 *
 *  Created on: 10 Oct 2023
 *      Author: maria
 */

#ifndef ADC_H_
#define ADC_H_

#include"std_types.h"
/************************************************************************************************
                                 important definitions
 ************************************************************************************************/
/*definitions for sensor driver and not for the ADC */
#define ADC_MAXIMUM_VALUE 1024   /* 2^(number of bits of ADC =10) */
#define ADC_REF_VOLT_VALUE   5

/* enum for VREF configuration */
typedef enum {

	AREF, /* AREF, internal Vref with 5v */
	AVCC, /*external capacitor at AREF pin */
	REVERSED ,/*no actiom */
	INTERNAL_REF /*internal 2.56v with external capacitor at AREF pin */
}ADC_RefrenceVoltage;

typedef enum {
	F_CPU_2 =1,
	F_CPU_4 =2,
	F_CPU_8,
	F_CPU_16,
	F_CPU_32,
	F_CPU_64,
	F_CPU_128
}ADC_Prescaler;

/* struct for ADC configurations */
typedef struct{
	ADC_RefrenceVoltage ref_volt ;
	/* set clk prescaler with 128 as the clk of ADC range 50-200 khz and clk of cpu=16MGHZ */
	ADC_Prescaler prescaler ;
}ADC_ConfigType;


/*************************************************************************************************
                             important fn prototypes
 *************************************************************************************************/
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_ptr);


/*
* Description :
* Function responsible for read analog data from a certain ADC channel
* and convert it to digital using the ADC driver. input is the number of read channel (0_7)->3bits
and return the digital converted by ADC */
uint16 ADC_readChannel(uint8 channel_num);





#endif /* ADC_H_ */
