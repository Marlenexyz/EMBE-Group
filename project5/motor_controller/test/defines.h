
#ifndef DEFINES_H
#define DEFINES_H

/**
 * This file holds all the global defines which are needed
 * to control the behavior of the motor control
 */

#define PORT_C1             'D'
#define PIN_C1              2

#define PORT_C2             'D'
#define PIN_C2              3

#define PORT_M1             'D'
#define PIN_M1              4

#define PORT_M2             'D'
#define PIN_M2              5

#define PORT_BUTTON         'D'
#define PIN_BUTTON          6

#define PORT_FAULT          'D'
#define PIN_FAULT           7

#define PORT_SLEEP          'B'
#define PIN_SLEEP           0

#define PORT_LED            'B'
#define PIN_LED             5



#define UPDATE_RATE         2

#define OMEGA_MAX           12.48f
#define OMEGA_REF           8.0f

// #define P_CTRL_KP           20.0f  // 7.0f for w_ref = 8

// #define PI_CTRL_KP          0.0f
// #define PI_CTRL_TI          0.0f



#endif
