#ifndef MAXFLOWALG_H__
#define MAXFLOWALG_H__

template<class T>
class MaxFlowAlg {
public:
  virtual T getMaxFlow(int source, int sink) = 0;
  virtual void clearNetwork() = 0;
  virtual void addEdge(int from, int to, int cap) = 0;
};
#endif
