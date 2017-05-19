#ifndef SPNLAYER_H
#define SPNLAYER_H
#include <iostream>
#include <vector>
namespace myspn {
class SpnLayer {
  typedef size_t NodeIndex;

 protected:
  std::vector<double> nodePotentials_;
  std::vector<std::vector<size_t>> connectedIndices_;
  std::vector<double>* childLayer_;

 public:
  SpnLayer(std::vector<double>* childLayer) : childLayer_{childLayer} {}
  virtual void eval() = 0;
  void printLayerPotentials() {
    for (double pot : nodePotentials_) {
      std::cout << pot << " | ";
    }
    std::cout << '\n';
  }
};
}
#endif  // SPNLAYER_H
