#include "adc.h"

void Adc_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; // 配置结构体

	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOC, ENABLE); // 使能时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;    //模拟输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOC, &GPIO_InitStructure); // 初始化GPIO
	
	ADC_CommonInitTypeDef ADC_CommonInitStruct;

	ADC_DeInit();//ADC复位

	ADC_CommonInitStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;

	ADC_CommonInit(&ADC_CommonInitStruct);
	
	ADC_InitTypeDef ADC_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_NbrOfConversion=1;
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;

	ADC_Init(ADC1, &ADC_InitStruct);
	//ADC1使能
	ADC_Cmd(ADC1, ENABLE);
}

unsigned int Get_ADC_Value(void)
{
	unsigned int adc_value = 0;
	float volt = 0;
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_480Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

	adc_value = ADC_GetConversionValue(ADC1);
	volt = (adc_value + 1) * (3.3 / 4096 * 11);
	adc_value = volt * 100;
	return adc_value;
}

