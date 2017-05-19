#ifndef SPNTEST_H
#define SPNTEST_H
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "../SpnImplementation/binaryrandomvar.h"
#include "../SpnImplementation/spn.h"

class SPNTest : public testing::Test {
 protected:
  virtual void SetUp() {}
  void ctorTester() {}
};

TEST_F(SPNTest, generatingSimpleSPN) { myspn::SPN spn; }

TEST_F(SPNTest, evalMarginals) {
  myspn::SPN spn;
  spn.getRandomVarLayer().addRandomVariable(
      std::make_unique<myspn::BinaryRandomVar>(.3, 0));

  spn.getRandomVarLayer().addRandomVariable(
      std::make_unique<myspn::BinaryRandomVar>(.6, 1));

  spn.getRandomVarLayer().addRandomVariable(
      std::make_unique<myspn::BinaryRandomVar>(.6, 0));

  spn.getRandomVarLayer().addRandomVariable(
      std::make_unique<myspn::BinaryRandomVar>(.1, 1));

  auto summationLayer = std::make_unique<myspn::SummationLayer>(
      spn.getRandomVarLayer().getNodePotentials());
  auto multiplicationLayer = std::make_unique<myspn::MultiplicationLayer>(
      summationLayer->getNodePotentials());
  summationLayer->addNode();
  summationLayer->addNode();
  multiplicationLayer->addNode();

  summationLayer->connectNodeToChild(0, 0, .5);
  summationLayer->connectNodeToChild(0, 1, .5);

  summationLayer->connectNodeToChild(1, 2, .2);
  summationLayer->connectNodeToChild(1, 3, .8);

  multiplicationLayer->connectNodeToChild(0, 0);
  multiplicationLayer->connectNodeToChild(0, 1);

  spn.getSumAndProductNodes().push_back(std::move(summationLayer));
  spn.getSumAndProductNodes().push_back(std::move(multiplicationLayer));

  myspn::DataForMarginalEval data;
  data.addGivenVar(0, 1);
  spn.evaluateForMarginals(data);

  spn.printValues();
}

TEST_F(SPNTest, generatingSimpleSPNWithTwoBinaryVars) {
  myspn::SPN spn;
  spn.getRandomVarLayer().addRandomVariable(
      std::make_unique<myspn::BinaryRandomVar>(.3, 0));

  spn.getRandomVarLayer().addRandomVariable(
      std::make_unique<myspn::BinaryRandomVar>(.6, 1));

  spn.getRandomVarLayer().addRandomVariable(
      std::make_unique<myspn::BinaryRandomVar>(.6, 0));

  spn.getRandomVarLayer().addRandomVariable(
      std::make_unique<myspn::BinaryRandomVar>(.1, 1));

  /*
    creates the following:

    *
    |\
    + +
    |X|  .5 .5 .2 .8
    X X
    */
  auto summationLayer = std::make_unique<myspn::SummationLayer>(
      spn.getRandomVarLayer().getNodePotentials());
  auto multiplicationLayer = std::make_unique<myspn::MultiplicationLayer>(
      summationLayer->getNodePotentials());
  summationLayer->addNode();
  summationLayer->addNode();
  multiplicationLayer->addNode();

  summationLayer->connectNodeToChild(0, 0, .5);
  summationLayer->connectNodeToChild(0, 1, .5);

  summationLayer->connectNodeToChild(1, 2, .2);
  summationLayer->connectNodeToChild(1, 3, .8);

  multiplicationLayer->connectNodeToChild(0, 0);
  multiplicationLayer->connectNodeToChild(0, 1);

  spn.getSumAndProductNodes().push_back(std::move(summationLayer));
  spn.getSumAndProductNodes().push_back(std::move(multiplicationLayer));

  spn.evaluateForStateOfWorld(std::vector<size_t>{1, 1, 0, 1});
  spn.printValues();
}

#endif  // SPNTEST_H
