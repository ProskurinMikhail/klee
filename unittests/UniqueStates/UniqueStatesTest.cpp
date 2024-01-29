#define KLEE_UNITTEST
#include "Core/ExecutionState.h"
#include "Core/Searcher.h"
#include "gtest/gtest.h"

#include <cstring>
#include <vector>

using namespace klee;

TEST(UniqueStatesTest, DFS3) {
  ExecutionState es1,es2,es3;
  int n = 3;
  SelectNSearcher sns(new DFSSearcher(),n);
  EXPECT_TRUE(sns.empty());
  sns.update(nullptr,{&es1,&es2,&es3},{});
  ExecutionState *t1 = &sns.selectState();
  ExecutionState *t2 = &sns.selectState();
  ExecutionState *t3 = &sns.selectState();
  EXPECT_FALSE((t1->getID()==t2->getID()));
  EXPECT_FALSE((t1->getID()==t2->getID()));
  EXPECT_FALSE((t2->getID()==t3->getID()));
}

TEST(UniqueStatesTest, DFSn) {
  int n = 5;
  std::vector <ExecutionState> es(n);
  std::vector <ExecutionState*> testVector(n);
  SelectNSearcher sns(new DFSSearcher(),n);
  EXPECT_TRUE(sns.empty());
  for (int i=0; i<n; ++i){
    sns.update(nullptr,{&es[i]},{});
  }
  for (int i=0; i<n; ++i){
    testVector[i] = &sns.selectState();
  }
  for (int i=0; i<n; ++i){
    for (int j=i+1; j<n; ++j){
      EXPECT_FALSE((testVector[i]->getID()==testVector[j]->getID()));
    }
  }
}