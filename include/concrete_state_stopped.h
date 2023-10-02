#include <state.h>

#ifndef CONCRETE_STATE_STOPPED_H
#define CONCRETE_STATE_STOPPED_H

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class Concrete_state_stopped : public State
{
public:

    void on_do() override;
    void on_entry() override;
    void on_exit() override;
    void on_event_reset() override;
    void on_event_set_pre_operational() override;
    void on_event_set_operational() override;
    
};

#endif
