 #include <context.h>

Context::Context(State *state) : state_(nullptr)
{
    this->transition_to(state);
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

void Context::event_go()
  {
    this->state_->on_event_go();
  }

void Context::event_stop()
  {
    this->state_->on_event_stop();
  }

void Context::event_timeout()
  {
    this->state_->on_event_timeout();
  }

