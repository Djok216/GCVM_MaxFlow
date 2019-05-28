#include <algorithm>
#include <vector>
#include <iostream>
#include "pushrelabel.h"

template<typename T>
PushRelabel<T>::PushRelabel(int n) {
  flow = std::vector<std::vector<T>>(n, std::vector<T>(n, 0));
  cap = std::vector<std::vector<T>>(n, std::vector<T>(n, 0));
  h = std::vector<T>(n, 0);
  exc = std::vector<T>(n, 0);
}

template<typename T>
void PushRelabel<T>::clearNetwork() {
  flow.clear();
  cap.clear();
  h.clear();
  exc.clear();
}

template<typename T>
void PushRelabel<T>::addEdge(int from, int to, int cap) {
  this->cap[from][to] += cap;
}

template<typename T>
void PushRelabel<T>::push(int x, int y) {
  T addFlow = std::min<T>(exc[x], cap[x][y] - flow[x][y]);
  flow[x][y] += addFlow;
  flow[y][x] -= addFlow;
  exc[x] -= addFlow;
  exc[y] += addFlow;
}

template<typename T>
void PushRelabel<T>::relabel(int x) {
  T newh = INF;
  int n = exc.size();
  for (int i = 0; i < n; ++i) {
    if (cap[x][i] - flow[x][i] > 0) {
      newh = std::min<T>(newh, h[i]);
    }
  }
  if (newh < INF) {
    h[x] = newh + 1;
  }
}

template<typename T>
T PushRelabel<T>::getMaxFlow(int source, int sink) {
  int n = exc.size();
  h[source] = n;
  exc[source] = INF;

  for (int i = 0; i < n; ++i) {
    if (i != source) {
      push(source, i);
    }
  }
  
  auto getMHV = [&]() {
    std::vector<int> mhv;
    for (int i = 0; i < n; ++i) {
      if (i == source || i == sink || exc[i] <= 0) {
        continue;
      }
      if (mhv.size() && h[i] > h[mhv[0]]) {
        mhv.clear();
      }
      if (!mhv.size() || h[mhv[0]] == h[i]) {
        mhv.push_back(i);
      }
    }
    return mhv;
  };

  for (std::vector<int> v = getMHV(); v.size(); v = getMHV()) {
    for (int from : v) {
      bool pushed = false;
      for (int to = 0; to < n && exc[from] > 0; ++to)
        if (cap[from][to] - flow[from][to] > 0 && h[from] == h[to] + 1) {
          push(from, to);
          pushed = true;
        }
      if (!pushed) {
        relabel(from);
        break;
      }
    }
  }
  T ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += flow[source][i];
  }
  return ans;
}

template class PushRelabel<float>;
template class PushRelabel<double>;
template class PushRelabel<short>;
template class PushRelabel<unsigned short>;
template class PushRelabel<long long>;
template class PushRelabel<unsigned long long>;
template class PushRelabel<int>;
template class PushRelabel<unsigned int>;
template class PushRelabel<char>;