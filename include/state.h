#ifndef STATE_H
#define STATE_H

class Context; // Forward declaration to allow the definition of a pointer to Context without compile error

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

  virtual void on_event_set_operational() = 0;

  virtual void on_isr_int0() = 0;

  virtual void on_isr_timer1_compa() = 0;

  virtual void on_isr_timer1_compb() = 0;
  
  virtual void on_isr_timer2_compa() = 0;

  virtual void on_isr_timer2_compb() = 0;

  // ...

};

#endif