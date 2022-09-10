// See LICENSE for license details.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "hbird_sdk_hal.h"

void btn_irq_handler() {
    int i;
    int32_t mask;

    mask = gpio_clear_interrupt(GPIOA);

    switch (mask) {
        case SOC_BUTTON_R_GPIO_MASK:
            printf("Button R pressed\n");
            break;

        case SOC_BUTTON_L_GPIO_MASK:
            printf("Button L pressed\n");
            break;

        case SOC_BUTTON_D_GPIO_MASK:
            printf("Button D pressed\n");
            break;

        case SOC_BUTTON_U_GPIO_MASK:
            printf("Button U pressed\n");
            break;
        
        default:
            break;
    }
}

int main(void)
{
    gpio_enable_input(GPIOA, SOC_BUTTON_GPIO_MASK);

    /**
     * When press the buttons on Genesys2, the value is HIGH
     * Judge the GPIO_INT_FALL is the most precise control
    **/
    gpio_enable_interrupt(GPIOA, SOC_BUTTON_GPIO_MASK, GPIO_INT_FALL);
    PLIC_Register_IRQ(PLIC_GPIOA_IRQn, 1, btn_irq_handler);
    __enable_irq();

    return 0;
}

