#ifndef MULITPLICATIONLAYERTEST_H
#define MULITPLICATIONLAYERTEST_H
#include <gtest/gtest.h>
#include "../SpnImplementation/randomvariablelayer.h"
class RandomVarLayerTest : public testing::Test {
 protected:
  myspn::RandomVariableLayer randomVariableLayer;

  virtual void SetUp() {}
};

TEST_F(RandomVarLayerTest, dataForMarginals) {
  myspn::DataForMarginalEval data;

  data.addGivenVar(3, 1);
  data.addGivenVar(0, 1);
  data.addGivenVar(1, 1);
  data.addGivenVar(2, 1);
  data.readyForApplication();
  size_t state;
  bool stateIsGiven = data.isStateForValGivenGetStateIfTrue(3, &state);
  ASSERT_TRUE(stateIsGiven);
  ASSERT_EQ(1, state);
}

#endif  // MULITPLICATIONLAYERTEST_H
