/*
 * bsp_adc.c
 *
 *  Created on: 2024Äê8ÔÂ19ÈÕ
 *      Author: Mr. Chen
 */

#include "Mcal.h"
#include "Clock_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#include "Pit_Ip.h"
#include "bsp_adc.h"
#include "Adc_Sar_Ip.h"

#define ADC_BANDGAP             5980U /* Vbandgap ~ 1.2V on 14 bits resolution, 3.3V VrefH */
#define ADC_SAR_USED_CH         34U /* Internal Bandgap Channel */

#define ADC_TOLERANCE(x,y)              (((x > y) ? (x - y) : (y - x)) > 200U) /* Check that the data is within tolerated range */

volatile boolean notif_triggered = FALSE;
volatile uint16 data;
float adc_voltage;

extern void Adc_Sar_0_Isr(void);
extern void Adc_Sar_1_Isr(void);

void AdcEndOfChainNotif(void)
{
    notif_triggered = TRUE;
    data = Adc_Sar_Ip_GetConvData(ADCHWUNIT_0_INSTANCE, ADC_SAR_USED_CH);

    adc_voltage = data*5.0f/16384; //2^14=16384
    /* Checks the measured ADC data conversion */
//    while (ADC_TOLERANCE(data, ADC_BANDGAP));
}

void main_adc_init(void){

	/*ADC*/
	StatusType status;
	uint8 Index;

	status = (StatusType) Adc_Sar_Ip_Init(ADCHWUNIT_0_INSTANCE, &AdcHwUnit_0);
	while (status != E_OK);

	/* Install and enable interrupt handlers */
	IntCtrl_Ip_InstallHandler(ADC1_IRQn, Adc_Sar_1_Isr, NULL_PTR);
	IntCtrl_Ip_EnableIrq(ADC1_IRQn);

	/* Call Calibration function multiple times, to mitigate instability of board source */
	for(Index = 0; Index <= 5; Index++)
	{
		status = (StatusType) Adc_Sar_Ip_DoCalibration(ADCHWUNIT_0_INSTANCE);
		if(status == E_OK)
		{
			break;
		}
	}

	Adc_Sar_Ip_EnableNotifications(ADCHWUNIT_0_INSTANCE, ADC_SAR_IP_NOTIF_FLAG_NORMAL_ENDCHAIN | ADC_SAR_IP_NOTIF_FLAG_INJECTED_ENDCHAIN);

	/* Start a SW triggered normal conversion on ADC_SAR */
	Adc_Sar_Ip_StartConversion(ADCHWUNIT_0_INSTANCE, ADC_SAR_IP_CONV_CHAIN_NORMAL);

	/* Wait for the notification to be triggered and read the data */
	while (notif_triggered != TRUE);
	notif_triggered = FALSE;

//	/* Start a SW triggered injected conversion on ADC_SAR */
//	Adc_Sar_Ip_StartConversion(ADCHWUNIT_0_INSTANCE, ADC_SAR_IP_CONV_CHAIN_INJECTED);
//
//	/* Wait for the notification to be triggered and read the data */
//	while (notif_triggered != TRUE);
//	notif_triggered = FALSE;
}
