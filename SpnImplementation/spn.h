#ifndef SPN_H
#define SPN_H
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include "multiplicationlayer.h"
#include "randomvariablelayer.h"
#include "summationlayer.h"
namespace myspn {
class SPN {
 private:
  RandomVariableLayer randomVariableLayer_;
  std::vector<std::unique_ptr<NodeLayer>> sumAndProductNodeLayer_;

 public:
  RandomVariableLayer& getRandomVarLayer() { return randomVariableLayer_; }
  std::vector<std::unique_ptr<NodeLayer>>& getSumAndProductNodes() {
    return sumAndProductNodeLayer_;
  }

  double evaluateForStateOfWorld(std::vector<size_t> stateOfTheWorld) {
    randomVariableLayer_.eval(stateOfTheWorld);
    for (size_t i = 0; i < sumAndProductNodeLayer_.size(); ++i) {
      sumAndProductNodeLayer_[i]->eval();
    }
    return sumAndProductNodeLayer_.back()->getNodePotentials()->at(0);
  }

  double evaluateForMarginals(DataForMarginalEval& data) {
    randomVariableLayer_.evalForMarginals(data);
    for (size_t i = 0; i < sumAndProductNodeLayer_.size(); ++i) {
      sumAndProductNodeLayer_[i]->eval();
    }
    return sumAndProductNodeLayer_.back()->getNodePotentials()->at(0);
  }

  void printValues() {
    randomVariableLayer_.printValues();
    for (auto& layer : sumAndProductNodeLayer_) {
      layer->printValues();
    }
  }
};
}

#endif  // SPN_H
