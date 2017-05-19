#include <gtest/gtest.h>
#include <iostream>
#include "../SpnImplementation/binaminaldistributionrandomvar.h"
#include "../SpnImplementation/binaryrandomvar.h"
#include "randomvarlayertest.h"
#include "spntest.h"
using namespace std;

TEST(binaryRandomVar, trueAndFalse) {
  myspn::BinaryRandomVar binaryRandomVar{.5, 0};
  double probTrue = binaryRandomVar.getProbabilityOfValue(1);
  double probFalse = binaryRandomVar.getProbabilityOfValue(0);
  ASSERT_EQ(.5, probTrue);
  ASSERT_EQ(.5, probFalse);
  ;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
