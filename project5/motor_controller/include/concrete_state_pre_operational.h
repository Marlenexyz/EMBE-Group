#include <state.h>

#ifndef CONCRETE_STATE_PRE_OPERATIONAL_H
#define CONCRETE_STATE_PRE_OPERATIONAL_H

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class Concrete_state_pre_operational : public State
{
public:

    State::Name getStateName() override;
    void on_do() override;
    void on_entry() override;
    void on_exit() override;
    void on_event_reset() override;
    void on_event_set_pre_operational() override;
    void on_event_set_operational() override;
    void on_event_set_stopped() override;
    
};

#endif
