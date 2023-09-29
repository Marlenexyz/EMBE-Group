#include <state.h>

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

    void event_go();

    void event_stop();

    void event_timeout();

};

#endif