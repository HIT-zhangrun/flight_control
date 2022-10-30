#ifndef   __LED_H__
#define   __LED_H__

#include "main.h"
#include "stdint.h"

#define LEDR_H GPIOB->BSRR |= GPIO_Pin_12 //配置LED引脚为 高电平
#define LEDR_L GPIOB->BRR  |= GPIO_Pin_12 //配置LED引脚为 低电平

#define LEDG_H GPIOB->BSRR |= GPIO_Pin_13 //配置LED引脚为 高电平
#define LEDG_L GPIOB->BRR  |= GPIO_Pin_13 //配置LED引脚为 低电平

#define LEDB_H GPIOB->BSRR |= GPIO_Pin_14 //配置LED引脚为 高电平
#define LEDB_L GPIOB->BRR  |= GPIO_Pin_14 //配置LED引脚为 低电平

typedef __packed struct
{
    uint8_t (* func)();
    uint16_t priority;
    LED_STATUS_E status;
} led_list_t;

typedef enum LED_STATUS
{
    NORMAL = 0,
    RED_SLOWLY,
    GREEN_SLOWLY,
    RED_QUICKLY,
    GREEN_QUICKLY,
} LED_STATUS_E;

void LED_Init(void);
void LEDR_1(void);
void LEDR_2(void);
void LEDR_3(void);

void LEDG_1(void);
void LEDG_2(void);
void LEDG_3(void);

void LEDB_1(void);
void LEDB_2(void);
void LEDB_3(void);

void led_task(void);
void led_test(void);

#endif
