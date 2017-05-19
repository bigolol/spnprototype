#ifndef SUMMATIONLAYER_H
#define SUMMATIONLAYER_H
#include <vector>
#include "nodelayer.h"
namespace myspn {
class SummationLayer : public NodeLayer {
 private:
  std::vector<std::vector<double>> weights_;

 public:
  SummationLayer(std::vector<double>* childValues) : NodeLayer(childValues) {}
  ~SummationLayer() {}

  void addNode() {
    nodePotentials_.push_back(0.0);
    connectedIndices_.push_back(std::vector<size_t>{});
    weights_.push_back(std::vector<double>{});
  }

  void connectNodeToChild(size_t nodeIndex, size_t childIndex, double weight) {
    connectedIndices_[nodeIndex].push_back(childIndex);
    weights_[nodeIndex].push_back(weight);
  }

  virtual void eval() override {
    auto rawNodePotentials = nodePotentials_.data();
    auto amountNodes = nodePotentials_.size();
    auto rawWeights = weights_.data();
    auto rawConnectedIndices = connectedIndices_.data();
#pragma omp parallel for
    for (size_t nodeIndex = 0; nodeIndex < amountNodes; ++nodeIndex) {
      double calculatedValue = 0.0;
      auto currentChildIndicesVector = rawConnectedIndices[nodeIndex];
      auto weightsToChildrenVector = rawWeights[nodeIndex];

      for (size_t posInChildIndexVec = 0;
           posInChildIndexVec < currentChildIndicesVector.size();
           ++posInChildIndexVec) {
        auto childIndex = currentChildIndicesVector[posInChildIndexVec];
        calculatedValue += weightsToChildrenVector[posInChildIndexVec] *
                           childPotentials_->at(childIndex);
      }
      rawNodePotentials[nodeIndex] = calculatedValue;
    }
  }
};
}
#endif  // SUMMATIONLAYER_H
