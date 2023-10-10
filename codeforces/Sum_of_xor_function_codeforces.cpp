 


#include<bits/stdc++.h>
using namespace std;
 
//<------------------------------FOR USING PBDS------------------------------->
/*
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
#include <functional> // for less
#include <iostream>
using namespace __gnu_pbds;
 
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
//ordered_multiset<int> s;
 
//Declaring ordered_set
typedef tree<int, null_type, less<int>, rb_tree_tag,
      tree_order_statistics_node_update>
  ordered_set;
 
ordered_set s;
 
*/
//<-------------------------------PBDS ENDS HERE----------------------------->
 
 
//#pragma GCC optimize "trapv"
#define loop(i,j,k,in)              for(int i=j; i<k; i+=in)
#define rloop(i,j,k,in)             for(int i=j; i>=k; i-=in)
#define mem(a,b)                    memset(a, b, sizeof(a))
#define mod                         998244353
#define pub                         push_back
#define pob                         pop_back
#define endl                        "\n"
#define int                         long long int
 
 
typedef pair<int,int>               pii;
typedef vector<int>                 vi;
typedef vector<char>                vc;
typedef vector<string>              vs;
typedef vector<pii>                 vii;
typedef map<int,int>                mii;
typedef set<int>                    si;
// typedef long long int               ll;
// typedef unsigned long long int      ull;
 
 
//---------------------SEGMENT TREE IMPLEMENTATION(RANGE MIN QUERY)---------------------->
 
void buildtree(int s, int e, int idx, vector<int> &arr, vector<int> &tree){
  if(s == e){
    tree[idx] = arr[s];
    return;
  }
  int mid = (s + e)/2;
  buildtree(s, mid, 2*idx, arr, tree);
  buildtree(mid + 1, e, 2*idx + 1, arr, tree);
  tree[idx] = min(tree[2*idx] , tree[2*idx + 1]);
  return;
}
 
int query(int ss, int se, int qs ,int qe,int idx, vector<int> &tree){
  if(ss >= qs && se <= qe){
    return tree[idx];
  }
 
  if(se < qs || qe < ss){
    return INT_MAX;
  }
 
  int mid = (ss + se) /2;
  int la = query(ss, mid , qs, qe, 2*idx, tree);
  int ra = query(mid + 1, se, qs, qe, 2*idx + 1, tree);
  return min(la, ra);
}
 
void update(int ss, int se, int i, int idx,int increment, vector<int> &tree){
  if(i < ss || i > se) return;
  if(ss == se){
    tree[idx] += increment;
    return;
  }
  int mid = (ss + se) /2;
  update(ss, mid, i, 2*idx,increment, tree);
  update(mid + 1, se, i , 2*idx + 1, increment, tree);
  tree[idx] = min(tree[2*idx], tree[2*idx + 1]);
  return; 
}
 
//----------------------------SEGMENT TREE ENDS HERE-------------------------------
 
//--------------------------------CALCULATE POWER HERE------------------------
int fastpow(int a, int b, int m)
{
  long long res = 1;
  while (b)
  {
    if (b & 1)
      res = res * a;
    res %= m;
    a = (1ll * a * a) % m;
    b = b >> 1;
  }
  return res;
}
 
 
//------------------CALCULATE MODULO INVERSE USING FERMET'S LITTLE THEOREM-----
int inverse(int a, int m){
  return fastpow(a, m-2, m);
}
 
 
//-----------------DISJOINT SET UNION-------------------------------------
class DSU
{
public:
  vector<int> parent;
  vector<int> rank;
  vector<int> loop;
  int cc;
  DSU(int n)
  {
    parent.resize(n+1);
    rank.resize(n+1);
    loop.resize(n+1);
    cc = n;
    for (int i = 0; i <= n; i++)
    {
      parent[i] = i;
      rank[i] = 1;
      loop[i] = false;
    }
  }
  int get(int x)
  {
    return parent[x] = parent[x] == x ? x : get(parent[x]);
  }
  void merge(int l, int r)
  {
    l = get(l);
    r = get(r);
    if (l == r){
      loop[l] = true;
        return;
    }
    if(rank[l] > rank[r]){
      parent[r] = l;
      rank[l]+= rank[r];
    }else{
      parent[l] = r;
      rank[r] += rank[l];
    }
    return;
  }
};

//---------------------------Z-Array------------------------------- 
void zCompute(string &s, vector<int> &z){
  int l = 0, r = 0;
  int n = s.size();
  
  for(int i=1; i<n; i++){
    if(i<=r){
      z[i] = min(z[i-l], r - i + 1);
    }
    
    while(i+z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
    
    if(i+z[i] - 1 > r){
      l = i, r = i + z[i] - 1;
    }
  }
  return;
}

 
class point{
public:
  int x, y;
};
 
int dot(point &p, point &q, point &r){
  int x1= q.x - p.x;
  int y1 = q.y - p.y;
  int x2 = r.x - q.x;
  int y2 = r.y - q.y;
  return x1 * x2 + y1 * y2;
}
 
int cross(point &p, point &q, point &r){
  int x1= q.x - p.x;
  int y1 = q.y - p.y;
  int x2 = r.x - q.x;
  int y2 = r.y - q.y;
  return x1 * y2 - y1 * x2;
}
 
 
 


int32_t main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  // #ifndef ONLINE_JUDGE
   //  freopen("input.txt","r",stdin);
   //  freopen("output.txt","w",stdout);
  // #endif
  int tt = 1;
  // cin >> tt;
  while(tt--){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(auto &it: arr) cin >> it;
    vector<map<int,pair<int,int>>> vt(32);
    for(int i=0; i<32; i++){
      vt[i][0].first++;
      vt[i][0].second = 0;
    }
    vector<int> sum(32);
    int ans = 0;
    for(int i=1; i<=n; i++){
      for(int j=0; j<32; j++){
        // cout <<"j : " << j << endl;
        if((1 << j) & arr[i-1]){
          sum[j]++;
          sum[j] %= 2;
        }
        int cnt = (vt[j][1-sum[j]].first);
        int val1 = (1 << j);
        int len = (((i * cnt)%mod) - vt[j][1-sum[j]].second ) % mod;
        len += mod;
        len %= mod;
        
        int val2 = val1 * len;
        ans += val2;
        ans %= mod;
        vt[j][sum[j]].first++;
        vt[j][sum[j]].second += i;
      }
    }
    cout << ans << endl;
  }
 
  return 0;
}

    
