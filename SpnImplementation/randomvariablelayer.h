#ifndef RANDOMVARIABLELAYER_H
#define RANDOMVARIABLELAYER_H
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include <memory>
#include <vector>
#include "randomvariable.h"
#include "spnlayer.h"
namespace myspn {

struct RandVarIdAndState {
  RandomVarId id_;
  size_t state_;
  RandVarIdAndState(RandomVarId id, size_t state) : id_{id}, state_{state} {}
};

struct DataForMarginalEval {
 private:
  std::vector<RandVarIdAndState> givenVarsId_;

 public:
  void addGivenVar(RandomVarId id, size_t variableState) {
    givenVarsId_.push_back(RandVarIdAndState(id, variableState));
  }

  void readyForApplication() {
    std::sort(
        givenVarsId_.begin(), givenVarsId_.end(),
        [](const RandVarIdAndState& lhs, const RandVarIdAndState& rhs) -> bool {
          return lhs.id_ > rhs.id_;
        });
  }

  bool isStateForValGivenGetStateIfTrue(RandomVarId id, size_t* state) {
    auto first = std::lower_bound(
        givenVarsId_.begin(), givenVarsId_.end(), RandVarIdAndState(id, 0),
        [](const RandVarIdAndState& lhs, const RandVarIdAndState& rhs) -> bool {
          return lhs.id_ > rhs.id_;
        });
    if ((first == givenVarsId_.end()) || (id != first->id_)) {
      return false;
    } else {
      *state = first->state_;
      return true;
    }
  }
};

class RandomVariableLayer {
 private:
  std::vector<double> nodePotentials_;
  std::vector<std::unique_ptr<RandomVariable>> randomVariables_;

 public:
  RandomVariableLayer() {}
  ~RandomVariableLayer() {}
  std::vector<double>* getNodePotentials() { return &nodePotentials_; }
  void eval(const std::vector<size_t>& stateOfTheWorld) {
    auto rawNodePotentials = nodePotentials_.data();
    auto rawRandomVars = randomVariables_.data();
    auto rawStateOfTheWorld = stateOfTheWorld.data();
    size_t amountRandomVariables = randomVariables_.size();
#pragma omp parallel for
    for (int currentStateVarPos = 0; currentStateVarPos < amountRandomVariables;
         ++currentStateVarPos) {
      rawNodePotentials[currentStateVarPos] =
          rawRandomVars[currentStateVarPos]->getProbabilityOfValue(
              rawStateOfTheWorld[currentStateVarPos]);
    }
  }

  void evalForMarginals(DataForMarginalEval& data) {
    data.readyForApplication();
    for (size_t i = 0; i < randomVariables_.size(); ++i) {
      size_t currentState;
      bool stateIsGiven = data.isStateForValGivenGetStateIfTrue(
          randomVariables_[i]->id_, &currentState);
      if (stateIsGiven) {
        nodePotentials_[i] =
            randomVariables_[i]->getProbabilityOfValue(currentState);
      } else {
        nodePotentials_[i] = 1.0;
      }
    }
  }

  void addRandomVariable(std::unique_ptr<RandomVariable> randomVariable) {
    nodePotentials_.push_back(0.0);
    randomVariables_.push_back(std::move(randomVariable));
  }
  void printValues() {
    for (auto val : nodePotentials_) {
      std::cout << val << ' ';
    }
    std::cout << '\n';
  }
};
}
#endif  // RANDOMVARIABLELAYER_H
