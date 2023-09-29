#include <state.h>
#include <digital_in.h>
#include <digital_out.h>
#include <encoder.h>
#include <analog_in.h>
#include <analog_out.h>
#include <P_controller.h>

#ifndef CONTEXT_H
#define CONTEXT_H

class Context
{
private:

    State *state_;

public:

    Context(State *state);      //keine Definition sonst weint

    ~Context();
    void transition_to(State *state);

    void do_work();

    void event_reset();

    void event_set_operational();

    void isr_int0();
    
    void isr_timer1_compa();

    void isr_timer1_compb();
  
    void isr_timer2_compa();

    void isr_timer2_compb();

// private:
// protected:
  // static unsigned long tau = 0;
    float omega;         // = 0.0f;
    float refOmega;      // = 8.0f;

    Digital_in c1;              //(2, 'D');
    Digital_in c2;              //(3, 'D');
    Analog_out m1;              //(4, 'D');
    Analog_out m2;              //(5, 'D');

    Encoder encoder;            //(c1, c2);
    P_controller controller;    //(m1, m2);
};

#endif