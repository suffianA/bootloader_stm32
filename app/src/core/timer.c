#include "core/timer.h"

#include <libopencm3/cm3/common.h> 
#include <libopencm3/stm32/f4/timer.h>
#include <libopencm3/stm32/f4/rcc.h>

// cpu freq 84_000_000

#define PRESCALER   (84)
#define ARR_VALUE   (1000)

void timer_setup(){
    rcc_periph_clock_enable(RCC_TIM2);

    // timer 2 configuration
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    
    // setup PWM mode   
    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);    

    // enable PWM output
    timer_enable_counter(TIM2);
    timer_enable_oc_output(TIM2, TIM_OC1);

    // set frequency and resolution
    timer_set_prescaler(TIM2, PRESCALER - 1);
    timer_set_period(TIM2, ARR_VALUE - 1);
}

void timer_pwm_set_duty_cycle(float duty_cycle){
    // duty cycle = (ccr / arr) * 100
    // crr = arr * (duty cycle / 100)

    const float raw_value = (float)ARR_VALUE * (duty_cycle / 100.0f);
    timer_set_oc_value(TIM2, TIM_OC1, (uint32_t)raw_value);
}