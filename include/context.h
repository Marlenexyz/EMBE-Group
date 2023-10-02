#include <state.h>

#include <defines.h>
#include <digital_in.h>
#include <digital_out.h>
#include <analog_out.h>
#include <encoder.h>
#include <p_controller.h>

#ifndef CONTEXT_H
#define CONTEXT_H

/**
 * The Context defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Context.
 */

class Context
{
    /**
     * @var State A reference to the current state of the Context.
     */

private:
    State *state_;

public:
    Context(State *state) : 
        state_(nullptr),
        c1(PIN_C1, PORT_C1),
        c2(PIN_C2, PORT_C2),
        m1(PIN_M1, PORT_M1),
        m2(PIN_M2, PORT_M2),
        button(PIN_BUTTON, PORT_BUTTON),
        sleep(PIN_SLEEP, PORT_SLEEP),
        led(PIN_LED, PORT_LED),
        encoder(c1, c2),
        controller(m1, m2, button, sleep),
        tau(0),
        omega(0.0f),
        omegaRef(OMEGA_REF)
    {
        this->transition_to(state);
    }

    ~Context()
    {
        delete state_;
    }

    /**
     * The Context allows changing the State object at runtime.
     */

    void transition_to(State *state)
    {
        if (this->state_ != nullptr)
        {
            this->state_->on_exit();
            delete this->state_;
        }

        this->state_ = state;

        this->state_->set_context(this);

        this->state_->on_entry();
    }

    /**
     * The Context delegates part of its behavior to the current State object.
     */

    void do_work()
    {
        this->state_->on_do();
    }

    void event_reset()
    {
        this->state_->on_event_reset();
    }

    void event_set_operational()
    {
        this->state_->on_event_set_operational();
    }

    /**
     * The Context holds globaly used objects and variables.
     */

    Digital_in c1;
    Digital_in c2;
    Analog_out m1;
    Analog_out m2;
    Digital_in button;
    Digital_out sleep;
    Digital_out led;
    Encoder encoder;
    P_controller controller;

    unsigned long tau;
    float omega;
    float omegaRef;

};

#endif
