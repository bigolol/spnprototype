#ifndef NODELAYER_H
#define NODELAYER_H
#include <iostream>
#include <vector>
class NodeLayer {
 protected:
  std::vector<double> nodePotentials_;
  std::vector<std::vector<size_t>> connectedIndices_;
  std::vector<double>* childPotentials_;

 public:
  NodeLayer(std::vector<double>* childPotentials)
      : childPotentials_{childPotentials} {}

  std::vector<double>* getNodePotentials() { return &nodePotentials_; }
  void printValues() {
    for (auto v : nodePotentials_) {
      std::cout << v << ' ';
    }
    std::cout << '\n';
  }

  virtual void eval() = 0;
};

#endif  // NODELAYER_H
