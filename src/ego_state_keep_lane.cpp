//
// Created by jun on 7/24/17.
//
#include <iostream>
#include <vector>

#include "map.h"
#include "vehicle.h"
#include "ego.h"
#include "ego_state.h"
#include "ego_state_keep_lane.h"
#include "ego_state_prepare_change_lane.h"
#include "utilities.h"


EgoStateKeepLane::EgoStateKeepLane() {}

EgoStateKeepLane::~EgoStateKeepLane() {}

void EgoStateKeepLane::onEnter(Ego& ego) {
  std::cout << "Enter state: *** KEEP LANE ***" << std::endl;
}

EgoState* EgoStateKeepLane::onUpdate(Ego& ego,
                                     const std::vector<std::vector<double>>& sensor_fusion,
                                     const Map& map) {
  if ( checkFrontCollision(ego, sensor_fusion, map) ) {
    return new EgoStatePrepareChangeLane();
  } else {
    planPath(ego, map);
  }

}

void EgoStateKeepLane::onExit(Ego& ego) {
  std::cout << "Exit state: *** KEEP LANE ***" << std::endl;
}

void EgoStateKeepLane::planPath(Ego& ego, const Map& map) {
  double ps0, vs0, as0;
  double pd0, vd0, ad0;

  double ps1, vs1, as1;
  double pd1, vd1, ad1;

  if ( ego.getPath().first.empty() ) {
    ps0 = ego.getPs();
    pd0 = ego.getPd();
  } else {
    ps0 = *std::next(ego.getPath().first.end(), -1);
    pd0 = *std::next(ego.getPath().second.end(), -1);
  }

  vs0 = ego.getMaxSpeed();
  vd0 = 0;
  as0 = 0;
  ad0 = 0;
  vs1 = vs0;
  vd1 = 0;
  as1 = 0;
  ad1 = 0;

  double duration = ego.getTimeStep() * ego.getPredictionPts();
  ps1 = ps0 + vs0*duration;
  pd1 = (ego.getLaneID() - 0.5) * map.getLaneWidth();

  std::vector<double> state0_s = {ps0, vs0, as0};
  std::vector<double> state0_d = {pd0, vd0, ad0};
  std::vector<double> state1_s = {ps1, vs1, as1};
  std::vector<double> state1_d = {pd1, vd1, ad1};

  std::vector<double> coeff_s = jerkMinimizingTrajectory(state0_s, state1_s, duration);
  std::vector<double> coeff_d = jerkMinimizingTrajectory(state0_d, state1_d, duration);

  ego.extendPath(coeff_s, coeff_d);
}

bool EgoStateKeepLane::checkFrontCollision(const Ego& ego,
                                      const std::vector<std::vector<double>>& sensor_fusion,
                                      const Map&map) {
  double min_ds = 1000;
  for ( auto &v : sensor_fusion ) {
    double s = v[4];
    double d = v[5];
    if ( map.compute_lane_id(d) == ego.getLaneID() ) {
      double ds = s - ego.getPs();
      if ( ds > 0 && ds < min_ds ) { min_ds = ds; }
    }
  }
  return ( min_ds < ego.getSafeDistance() );
}