#include <iostream>
#include <algorithm>
#include <vector>
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define MAX 1000000001
#define MIN 0
using namespace std;
using range = pair<int, int>;

class SegmentTree{
private:
  int size;
  vector<int> minTree, maxTree;

public:
  SegmentTree(int n){
    for (size = 1; size <= n; size *= 2);
    minTree.assign(size * 2, MAX);
    maxTree.assign(size * 2, MIN);
  }

  void update(int pos, int val){
    int idx = size + pos - 1;

    minTree[idx] = maxTree[idx] = val;
    idx /= 2;

    while (idx){
      minTree[idx] = min(minTree[idx * 2], minTree[idx * 2 + 1]);
      maxTree[idx] = max(maxTree[idx * 2], maxTree[idx * 2 + 1]);
      idx /= 2;
    }
  }

  // Check subtree at idx on which start and end depend.
  range getMinMax(int left, int right){
    return getMinMax(1, 1, size, left, right);
  }

  range getMinMax(int idx, int start, int end, int left, int right){
    if (end < left || start > right)
      return {MAX, MIN};
    if (left <= start && end <= right)
      return {minTree[idx], maxTree[idx]};

    int mid = (start + end) / 2;
    range a = getMinMax(2 * idx, start, mid, left, right);
    range b = getMinMax(2 * idx + 1, mid + 1, end, left, right);
    return {min(a.first, b.first), max(a.second, b.second)};
  }
};

int N, M;
SegmentTree st(100000);

void processQueries(){
  int a, b;
  while (M--){
    cin >> a >> b;
    range res = st.getMinMax(a, b);
    cout << res.first << ' ' << res.second << '\n';
  }
}

void init(){
  cin >> N >> M;
  int num;
  for (int i = 1; i <= N; ++i){
    cin >> num;
    st.update(i, num);
  }
}

int main(){
  fastio
  init();
  processQueries();
  return 0;
}