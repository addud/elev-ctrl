/**
 * Program skeleton for the course "Programming embedded systems"
 *
 * Lab 1: the elevator control system
 */

/**
 * This file defines datastructures used for communication between
 * the various modules
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include "FreeRTOS.h"
#include "stm32f10x_type.h"
#include "queue.h"
#include "position_tracker.h"

#define TRACKER_FLOOR1_POS	0
#define TRACKER_FLOOR2_POS	400
#define TRACKER_FLOOR3_POS	800
#define SAFE_STOP_DISTANCE	50 //50 cm before target position

#define FLOOR_TIMEOUT 100  // 1 second


/**
 * Events that can occur during execution. Those events
 * are generated by the PinListener module, and are
 * in the end consumed by the Planner module
 */
typedef enum {
  UNASSIGNED = 0,

  // Elevator request, either from within the elevator
  // or at a floor
  TO_FLOOR_1 = 1, TO_FLOOR_2, TO_FLOOR_3,

  // The elevetor has arrived at a floor, or has just
  // left a floor
  // NB: this does not mean that the elevator
  //     has stopped! The elevator might just be passing by
  //     a floor
  ARRIVED_AT_FLOOR, LEFT_FLOOR,

  // The doors have been closed or opened
  DOORS_CLOSED, DOORS_OPENING,

  // The stop button has been pressed or released
  STOP_PRESSED, STOP_RELEASED
} PinEvent;



/**
 * Queue on which events are propagated
 */
extern xQueueHandle pinEventQueue;



/**
 * Query the current position of the elevator car. The
 * position is provided by the PositionTracker module;
 * the unit are "cm"
 */
s32 getCarPosition(void);

/**
 * Tell the elevator motor to move the car to a particular
 * place (unit are "cm")
 */
void setCarTargetPosition(s32 target);

/**
 * Emergency stop for the elevator motor
 */
void setCarMotorStopped(u8 stopped);

//returns the car's direction of movement (up, down, unknown)
Direction getCarDirection(void);

//returns the car's target position
s32 getCarTargetPosition(void);

//returns the next floor where the car should go from the planner
s32 getPlannerTargetPosition(void);

//checks if the GPIO inputs (except the postion) satisfy Safety env4 condition
bool checkInputsStabilized(void);

#endif
