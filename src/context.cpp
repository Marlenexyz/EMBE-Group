#include <context.h>


Context::Context(State *state) : state_(nullptr), c1(2, 'D'), c2(3, 'D'), m1(4, 'D'), m2(5, 'D'), encoder(c1, c2), controller(m1, m2)
{
    this->transition_to(state);
    // tau = 0;
    omega = 0.0f;
    refOmega = 8.0f;
}

Context::~Context()
{
    delete state_;
}

void Context::transition_to(State *state)
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

void Context::do_work()
{
    this->state_->on_do();
}

void Context::event_reset()
{
    this->state_->on_event_reset();
}

void Context::event_set_operational()
{
    this->state_->on_event_set_operational();
}

void Context::isr_int0(){
    this->state_->on_isr_int0();
}

void Context::isr_timer1_compa(){
    this->state_->on_isr_int0();
}

void Context::isr_timer1_compb(){
    this->state_->on_isr_int0();
}

void Context::isr_timer2_compa(){
    this->state_->on_isr_int0();
}

void Context::isr_timer2_compb(){
    this->state_->on_isr_int0();
}
