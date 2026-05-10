#include "servo.h"
#include "config.h"

#define SERVO_MIN_US 1000U
#define SERVO_MAX_US 2000U

static uint16_t servo_limit(uint16_t value)
{
    if (value < SERVO_MIN_US)
    {
        return SERVO_MIN_US;
    }

    if (value > SERVO_MAX_US)
    {
        return SERVO_MAX_US;
    }

    return value;
}

void pwm_output_init(
    servo_output_t *servo,
    TIM_HandleTypeDef *htim,
    uint32_t channel)
{
    servo->htim = htim;
    servo->channel = channel;

    HAL_TIM_PWM_Start(
        servo->htim,
        servo->channel
    );
}

void pwm_write_us(
    servo_output_t *servo,
    uint16_t pulse_us)
{
    pulse_us =
        servo_limit(pulse_us);

    __HAL_TIM_SET_COMPARE(
        servo->htim,
        servo->channel,
        pulse_us
    );
}
