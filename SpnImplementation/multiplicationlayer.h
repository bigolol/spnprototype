#ifndef MULTIPLICATIONLAYER_H
#define MULTIPLICATIONLAYER_H
#include "nodelayer.h"
#include "spnlayer.h"
namespace myspn {
class MultiplicationLayer : public NodeLayer {
 public:
  MultiplicationLayer(std::vector<double>* childPotentials)
      : NodeLayer(childPotentials) {}

  virtual void eval() override {
    auto rawNodePotentials = nodePotentials_.data();
    auto amtNodes = nodePotentials_.size();
    auto rawConnectedIndices = connectedIndices_.data();
    auto rawChildPotentials = childPotentials_->data();
#pragma omp parallel for
    for (size_t nodeIndex = 0; nodeIndex < amtNodes; ++nodeIndex) {
      auto currentChildIndexVector = rawConnectedIndices[nodeIndex];
      auto currentChildIndex = currentChildIndexVector[0];
      double calculatedPotential = rawChildPotentials[currentChildIndex];

      for (size_t posInChildIndexVector = 1;
           posInChildIndexVector < currentChildIndexVector.size();
           ++posInChildIndexVector) {
        currentChildIndex = currentChildIndexVector[posInChildIndexVector];
        calculatedPotential *= childPotentials_->at(currentChildIndex);
      }
      rawNodePotentials[nodeIndex] = calculatedPotential;
    }
  }

  void connectNodeToChild(size_t nodeIndex, size_t childIndex) {
    connectedIndices_[nodeIndex].push_back(childIndex);
  }

  void addNode() {
    nodePotentials_.push_back(0.0);
    connectedIndices_.push_back(std::vector<size_t>{});
  }
};
}

#endif  // MULTIPLICATIONLAYER_H
