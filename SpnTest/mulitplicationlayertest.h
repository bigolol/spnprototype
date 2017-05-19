#ifndef MULITPLICATIONLAYERTEST_H
#define MULITPLICATIONLAYERTEST_H
#include <gtest/gtest.h>
#include "../SpnImplementation/binaminaldistributionrandomvar.h"
#include "../SpnImplementation/multiplicationlayer.h"
#include "../SpnImplementation/randomvariablelayer.h"
class MultiPlicationLayerTest : public testing::Test {
 protected:
  myspn::RandomVariableLayer randomVarLayer;

  virtual void SetUp() {
    randomVarLayer.addRandomVariable(
        std::make_unique<myspn::BinomialDistributionRandomVar>(.5, 10));
    randomVarLayer.addRandomVariable(
        std::make_unique<myspn::BinomialDistributionRandomVar>(.5, 10));
    randomVarLayer.addRandomVariable(
        std::make_unique<myspn::BinomialDistributionRandomVar>(.5, 10));
    randomVarLayer.eval(std::vector<size_t>{1, 1, 1});
  }
};

TEST_F(MultiPlicationLayerTest, testEvalWithOneNode) {
  myspn::MultiplicationLayer multiplicationLayer{
      randomVarLayer.getCurrentValues()};
  multiplicationLayer.addNode();
  multiplicationLayer.connectNodeToChild(0, 0);
  multiplicationLayer.connectNodeToChild(0, 1);
  multiplicationLayer.connectNodeToChild(0, 2);
  multiplicationLayer.eval();
  double expected = randomVarLayer.getCurrentValues()->at(0) *
                    randomVarLayer.getCurrentValues()->at(1) *
                    randomVarLayer.getCurrentValues()->at(2);
  EXPECT_DOUBLE_EQ(expected, multiplicationLayer.getNodePotentials()->at(0));
}

#endif  // MULITPLICATIONLAYERTEST_H
