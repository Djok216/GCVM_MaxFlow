#include <cassert>
#include <iostream>
#include "pushrelabel.h"

int main() {
  PushRelabel<int> alg(4);
  alg.addEdge(0, 1, 3);
  alg.addEdge(0, 2, 5);
  alg.addEdge(2, 1, 3);
  alg.addEdge(1, 3, 6);
  alg.addEdge(2, 3, 4);
  assert(alg.getMaxFlow(0, 3) == 8);
  assert(alg.getMaxFlow(0, 3) == 8);
  alg.clearFlow();
  assert(alg.getMaxFlow(0, 3) == 8);
  return 0;
}