#ifndef BINARYRANDOMVAR_H
#define BINARYRANDOMVAR_H
#include "randomvariable.h"
namespace myspn {
class BinaryRandomVar : public RandomVariable {
 private:
  double probOfTrue_;

 public:
  BinaryRandomVar(double probOfTrue, RandomVarId id)
      : RandomVariable(id), probOfTrue_{probOfTrue} {}

  virtual double getProbabilityOfValue(size_t value) override {
    if (value == 0)
      return 1 - probOfTrue_;
    else
      return probOfTrue_;
  }
};
}

#endif  // BINARYRANDOMVAR_H
