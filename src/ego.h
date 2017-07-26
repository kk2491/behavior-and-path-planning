//
// Created by jun on 7/25/17.
//

#ifndef PATH_PLANNING_EGO_H
#define PATH_PLANNING_EGO_H

#include <iostream>
#include <vector>

#include "vehicle.h"

class EgoState;
class Map;


class Ego : public Vehicle {

private:
  EgoState* state_;

  double time_step_;
  unsigned int prediction_pts_;

  std::vector<double> path_s_;
  std::vector<double> path_d_;

  double safe_distance_;  // safe distance to the car on the same lane

  double max_speed_;  // maximum speed (m/s)
  double max_acceleration_;  // maximum acceleration (m/s^2)
  double max_steering_;  // maximum steering angle (rad)

public:

  //
  // constructor
  //
  Ego();

  //
  // destructor
  //
  virtual ~Ego();

  //
  // Update the ego car's state
  //
  void update(const std::vector<double>& localization,
              const std::vector<std::vector<double>>& sensor_fusion,
              const Map& map);

  //
  // Remove the way points in the vehicle paths which have been processed.
  //
  void updateUnprocessedPath();

  //
  // Keep a given number of way points in the current path
  //
  void truncatePath(unsigned int n_keep);

  //
  //
  //
  void extendPath(std::vector<double> coeff_s, std::vector<double> coeff_d);

  std::pair<std::vector<double>, std::vector<double>> getPath() const;

  double getMaxSpeed() const;

  double getMaxAcceleration() const;

  double getMaxSteering() const;

  double getTimeStep() const;

  unsigned int getPredictionPts() const;

  double getSafeDistance() const;

};


#endif //PATH_PLANNING_EGO_H