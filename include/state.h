#pragma once

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

  virtual void on_event_go() = 0;

  virtual void on_event_stop() = 0;

  virtual void on_event_timeout() = 0;

  // ...

};

#endif