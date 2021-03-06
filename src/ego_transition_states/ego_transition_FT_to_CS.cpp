//
// Created by jun on 7/28/17.
//
#include "ego_transition_FT_to_CS.h"
#include "../ego.h"
#include "../ego_states/ego_state.h"


EgoTransitionFTToCS::EgoTransitionFTToCS() {}

EgoTransitionFTToCS::~EgoTransitionFTToCS() {}

EgoState* EgoTransitionFTToCS::getNextState(Ego& ego) const {
  return EgoStateFactory::createState(CS);
}

bool EgoTransitionFTToCS::isValid(Ego &ego) const {

  auto front_vehicle = ego.getClosestVehicle(ego.getLaneID(), 1);
  if ( !front_vehicle.empty() ) { ;
    double ps_front = front_vehicle[0];
    double vs_front = front_vehicle[1];

    if ( vs_front < ego.getTargetSpeed() ||
         (ps_front - ego.getPs()) < 2*ego.getMinSafeDistance() ) {
      return false;
    }
  }

  return true;
}