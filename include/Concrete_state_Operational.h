#include <state.h>

#ifndef CONCRETE_STATE_OPERATIONAL_H
#define CONCRETE_STATE_OPERATIONAL_H

class Concrete_state_Operational : public State
{
public:
  void on_do() override;

  void on_entry() override;

  void on_exit() override;

  void on_event_reset() override;

  void on_event_set_operational() override;

  void on_isr_int0() override;

  void on_isr_timer1_compa() override;

  void on_isr_timer1_compb() override;

  void on_isr_timer2_compa() override;

  void on_isr_timer2_compb() override;
};

#endif