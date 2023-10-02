#include <state.h>

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
    Context(State *state) : state_(nullptr)
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

};

#endif
