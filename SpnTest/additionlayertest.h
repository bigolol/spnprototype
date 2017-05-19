#ifndef MULITPLICATIONLAYERTEST_H
#define MULITPLICATIONLAYERTEST_H
#include <gtest/gtest.h>
#include "../SpnImplementation/binaminaldistributionrandomvar.h"
#include "../SpnImplementation/randomvariablelayer.h"
#include "../SpnImplementation/summationlayer.h"
class AdditionLayerTest : public testing::Test {
 protected:
  myspn::RandomVariableLayer randomVarLayer;

  virtual void SetUp() {
    randomVarLayer.addRandomVariable(
        std::make_unique<myspn::BinomialDistributionRandomVar>(15, .4));
    randomVarLayer.addRandomVariable(
        std::make_unique<myspn::BinomialDistributionRandomVar>(15, .4));
    randomVarLayer.addRandomVariable(
        std::make_unique<myspn::BinomialDistributionRandomVar>(15, .4));
    randomVarLayer.eval(std::vector<size_t>{1, 1, 1});
  }
};

TEST_F(AdditionLayerTest, testAdditionLayerEvalWithOneNode) {
  myspn::SummationLayer summationLayer{randomVarLayer.getCurrentValues()};
  summationLayer.addNode();
  summationLayer.connectNodeToChild(0, 0, .4);
  summationLayer.connectNodeToChild(0, 1, .3);
  summationLayer.connectNodeToChild(0, 2, .2);
  summationLayer.eval();
  double expected = randomVarLayer.getCurrentValues()->at(0) * .4 +
                    randomVarLayer.getCurrentValues()->at(1) * .3 +
                    randomVarLayer.getCurrentValues()->at(2) * .2;
  EXPECT_DOUBLE_EQ(summationLayer.getNodePotentials()->at(0), expected);
}

#endif  // MULITPLICATIONLAYERTEST_H
