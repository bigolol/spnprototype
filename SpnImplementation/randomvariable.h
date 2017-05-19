#ifndef RANDOMVARIABLE_H
#define RANDOMVARIABLE_H
namespace myspn {
typedef size_t RandomVarId;
class RandomVariable {
 public:
  const RandomVarId id_;
  RandomVariable(RandomVarId id) : id_{id} {}
  virtual double getProbabilityOfValue(size_t value) = 0;
};
}
#endif  // RANDOMVARIABLE_H
