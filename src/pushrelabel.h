#ifndef PUSHRELABEL_H__
#define PUSHRELABEL_H__

#include <vector>
#include <limits>
#include "maxflowalg.h"

template<typename T>
class PushRelabel : public MaxFlowAlg<T> {
public:
  PushRelabel(int n = 0);
  virtual T getMaxFlow(int source, int sink);
  virtual void clearNetwork();
  virtual void addEdge(int from, int to, int cap);

private:
  std::vector<std::vector<T>> flow;
  std::vector<std::vector<T>> cap;
  std::vector<T> exc;
  std::vector<T> h;
  
  static constexpr T INF = std::numeric_limits<T>::max() / 2;

  void push(int x, int y);
  void relabel(int x);
};
#endif
