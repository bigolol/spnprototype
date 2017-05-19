#ifndef NORMALYDISTRIBUTETRANDOMVAR_H
#define NORMALYDISTRIBUTETRANDOMVAR_H
#include <boost/math/distributions/binomial.hpp>
#include <cmath>
#include <vector>
#include "randomvariable.h"

namespace myspn {
class BinomialDistributionRandomVar : public RandomVariable {
 private:
  size_t n_;
  double p_;

 public:
  BinomialDistributionRandomVar(size_t n, double p, RandomVarId id)
      : RandomVariable(id), n_{n}, p_{p} {}
  virtual double getProbabilityOfValue(size_t value) override {
    return boost::math::pdf(boost::math::binomial_distribution<double>(n_, p_),
                            value);
  }
};
}
#endif  // NORMALYDISTRIBUTETRANDOMVAR_H
