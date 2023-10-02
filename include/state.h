#ifndef STATE_H
#define STATE_H

class Context; // Forward declaration to allow the definition of a pointer to Context without compile error

/**
 * The base State class declares methods that all concrete states should
 * implement and also provides a backreference to the Context object, associated
 * with the State. This backreference can be used by States to transition the
 * Context to another State.
 */

class State
{
    /**
     * @var Context
     */

protected:
    Context *context_;

public:
    virtual ~State()
    {
    }

    void set_context(Context *context)
    {
        this->context_ = context;
    }

    virtual void on_do() = 0;

    virtual void on_entry() = 0;

    virtual void on_exit() = 0;

    virtual void on_event_reset() = 0;

    virtual void on_event_set_pre_operational() = 0;

    virtual void on_event_set_operational() = 0;

    // ...
};

#endif
