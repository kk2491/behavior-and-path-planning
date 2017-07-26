//
// Created by jun on 7/24/17.
//

#ifndef PATH_PLANNING_EGO_STATE_KEEP_LANE_H
#define PATH_PLANNING_EGO_STATE_KEEP_LANE_H

#include <vector>

#include "ego_state.h"

class Ego;
class Map;


class EgoStateKeepLane : public EgoState {
private:

  void planPath(Ego& ego, const Map& map);

  bool checkFrontCollision(const Ego& ego,
                      const std::vector<std::vector<double>>& sensor_fusion,
                      const Map&map);

public:
  //
  // constructor
  //
  EgoStateKeepLane();

  //
  // destructor
  //
  ~EgoStateKeepLane();

  void onEnter(Ego& ego);

  EgoState* onUpdate(Ego& ego,
                     const std::vector<std::vector<double>>& sensor_fusion,
                     const Map& map);

  void onExit(Ego& ego);
};


#endif //PATH_PLANNING_EGO_STATE_KEEP_LANE_H