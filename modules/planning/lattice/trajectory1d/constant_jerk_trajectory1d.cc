/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 **/


#include "modules/planning/lattice/trajectory1d/constant_jerk_trajectory1d.h"

#include "glog/logging.h"

#include "modules/planning/common/planning_gflags.h"

namespace apollo {
namespace planning {

ConstantJerkTrajectory1d::ConstantJerkTrajectory1d(
    const double p0, const double v0, const double a0,
    const double p1, const double v1, const double a1,
    const double param) : p0_(p0), v0_(v0), a0_(a0) {
  CHECK_GT(param, FLAGS_lattice_epsilon);
  jerk_ = (a1 - a0) / param;
}

double ConstantJerkTrajectory1d::Evaluate(
    const std::uint32_t order, const double param) const {
  switch (order) {
    case 0: {
      return p0_ + v0_ * param + 0.5 * a0_ * param * param +
             jerk_ * param * param * param / 6.0;
    }
    case 1: {
      return v0_ + a0_ * param + 0.5 * jerk_ * param * param;
    }
    case 2: {
      return a0_ + jerk_ * param;
    }
    case 3: {
      return jerk_;
    }
    default:
      return 0.0;
  }
}

}  // namespace planning
}  // namespace apollo
