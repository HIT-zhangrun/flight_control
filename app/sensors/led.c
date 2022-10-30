#include "led.h"

void LED_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;                                            //推挽输出
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;                                            //推挽输出
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStruct);

    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    GPIO_ResetBits(GPIOB,GPIO_Pin_13);
    GPIO_ResetBits(GPIOB,GPIO_Pin_14);

    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

static const led_list_t led_list[] =
{
    {0},
};

LED_STATUS_E led_scan(led_list_t led_list[])
{
    uint32_t list_num = sizeof(*led_list) / sizeof(led_list_t);
    led_list_t *led_list_p = NULL;
    uint8_t ret;
    uint16_t cur_priority = 0xFF;
    LED_STATUS_E led_status = NORMAL;

    for(uint32_t num = 0; num < list_num; num++)
    {
        led_list_p = (led_list_t *)&led_list[num];
        ret = led_list_p->func;
        if(ret == TRUE)
        {
            continue;
        }
        if(led_list_p->priority < cur_priority)
        {
            cur_priority = led_list_p->priority;
            led_status = led_list_p->status;
        }
    }
    return led_status;
}

void led_task()
{
    while(1)
    {
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));

        LED_STATUS_E led_status = led_scan(led_list);

        switch(led_status)
        {
            case NORMAL:


        }


    }
}

void led_test()
{
    static uint32_t clock = 0;
    while (1)
    {
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
        if(clock % 2 == 0)
        {
            LEDR_H;
            LEDG_H;
            LEDB_H;
        }
        else
        {
            LEDR_L;
            LEDG_L;
            LEDB_L;
        }
        clock++;
        printf("led heart beat \n\r");
    }
}
