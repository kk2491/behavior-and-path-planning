//
// Created by jun on 8/13/17.
//

#ifndef PATH_PLANNING_PARAMETERS_H
#define PATH_PLANNING_PARAMETERS_H

#include <iostream>
#include <cmath>
#include <limits>
#include <string>


const double kTIME_STEP = 0.02; // time step (s)

const double kMAX_SPEED = 50.0*4.0/9.0; // maximum speed (MPH -> m/s)
const double kMAX_ACCELERATION = 10; // maximum acceleration (m/s^2)
const double kMAX_JERK = 10; // maximum jerk (m/s^3)

const double kINF_D = std::numeric_limits<double>::max();

const std::string kMAP_PATH = "../data/highway_map.csv";
// Maximum s in meter. s will restart from 0 after this point
const double kMAX_S = 6945.554;

#endif //PATH_PLANNING_PARAMETERS_H
