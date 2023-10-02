#include <state.h>

#ifndef CONCRETE_STATE_INITIALIZATION_H
#define CONCRETE_STATE_INITIALIZATION_H

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class Concrete_state_initialization : public State
{
public:

    void on_do() override;
    void on_entry() override;
    void on_exit() override;
    void on_event_reset() override;
    void on_event_set_operational() override;
    
};

#endif
