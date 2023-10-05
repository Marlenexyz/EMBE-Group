#include <util/delay.h>
#include <unity.h>
#include <context.h>
#include "concrete_state_pre_operational.h"
#include "context.h"
#include "concrete_state_initialization.h"
#include "concrete_state_operational.h"
#include <Arduino.h>
#include <pi_controller.h>
#include <state.h>
#include <p_controller.h>

Context *context;


void test_normal_flow(void){        
    context = new Context(new Concrete_state_initialization);

    TEST_ASSERT_EQUAL_INT(State::Name::PRE_OPERATIONAL, context->getState()->getStateName());
    context->event_set_operational();
    TEST_ASSERT_EQUAL_INT(State::Name::OPERATIONAL, context->getState()->getStateName());
}

void test_alternate_flow(void){
    context = new Context(new Concrete_state_initialization);

    TEST_ASSERT_EQUAL_INT(State::Name::PRE_OPERATIONAL, context->getState()->getStateName());
    context->event_set_operational();
    TEST_ASSERT_EQUAL_INT(State::Name::OPERATIONAL, context->getState()->getStateName());
    Serial.println("Press Emergency Button now!");
    delay(5000);    
    TEST_ASSERT_EQUAL_INT(State::Name::STOPPED, context->getState()->getStateName());
    context->event_set_operational();
    TEST_ASSERT_EQUAL_INT(State::Name::OPERATIONAL, context->getState()->getStateName());
    context->event_reset();
    TEST_ASSERT_EQUAL_INT(State::Name::PRE_OPERATIONAL, context->getState()->getStateName());
}


int main()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    _delay_ms(2000);
    Serial.begin(9600);

    UNITY_BEGIN(); // IMPORTANT LINE!

    RUN_TEST(test_normal_flow);
    RUN_TEST(test_alternate_flow);
 

    UNITY_END(); // stop unit testing
}