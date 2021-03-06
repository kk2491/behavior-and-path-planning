//
// Created by jun on 7/31/17.
//

#include "../vehicle.h"
#include "../ego.h"
#include "../map.h"
#include "ego_state_start.h"
#include "../ego_transition_states/ego_transition_state.h"
#include "../path_planner.h"


EgoStateStart::EgoStateStart() {
  transition_states_.push_back(EgoTransitionStateFactory::createState(ST_TO_FT));
}

EgoStateStart::~EgoStateStart() {}

void EgoStateStart::onEnter(Ego& ego) {
  ego.truncatePath(0);
  std::cout << "Enter state: *** START ***" << std::endl;
}

void EgoStateStart::onUpdate(Ego &ego) {
  planPath(ego);
}

void EgoStateStart::onExit(Ego& ego) {
  std::cout << "Exit state: *** START ***" << std::endl;
}

void EgoStateStart::planPath(Ego &ego) {
  ego.truncatePath(5);

  auto state0 = ego.getInitialState();

  double vs0 = state0.first[1];
  double as0 = state0.first[2];

  double prediction_time = 1.0;

  double as1 = as0 + ego.getMaxJerk()*prediction_time;
  if ( as1 > ego.getMaxAcceleration() ) { as1 = ego.getMaxAcceleration(); }
  double vs1 = vs0 + 0.5*(as0 + as1)*prediction_time;
  double ds1 = 0.5*(vs0 + vs1)*prediction_time;

  PathPlanner planner(ego.getTargetSpeed(), ego.getMaxAcceleration(), ego.getMaxJerk());

  planner.setDsBoundary(0.25*ds1, ds1);
  planner.setVsBoundary(0.25*vs1, vs1);
  planner.setAsBoundary(as0, as1);

  double pd0 = state0.second[0];
  planner.setPdBoundary(pd0, pd0);

  vehicle_trajectory new_path = planner.plan(state0, prediction_time);

  ego.extendPath(new_path);
}
