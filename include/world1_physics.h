/* vim: set filetype=cpp.doxygen : */

// 
// File:   world1_physics.h
// Author: kyle2
//
// Created on June 9, 2007, 12:38 PM
//

#ifndef _world1_physics_H
#define	_world1_physics_H

/** Gravity vector to apply (y cord only for most levels) */
#define GRAVITY_VECTOR  1
/** Terminal Velocity */
#define TERMINAL_VELOCITY  5
/** The floor y cordinate */
#define FLOOR_POSITION  160


void applyGravity(int* velocity_vector_x, int* velocity_vector_y);
void applyFriction(int* velocity_vector_x, int* velocity_vector_y, int position_x, int position_y);

#endif	/* _world1_physics_H */

