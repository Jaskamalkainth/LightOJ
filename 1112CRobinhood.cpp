/*
 *    J1K7_7
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <list>
#include <map>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cassert>
#include <limits>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
typedef long double        ld;
typedef pair<int,int>      pii;
typedef pair<ll,ll>        pll;
typedef vector<int>        vi;
typedef vector<long long>  vll;
#define l(x) 		       (x << 1) + 1
#define r(x) 		       (x << 1) + 2
#define mid(l, r) 	       ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))
#define snuke(c,itr)       for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

template<class T>
inline bool ispow2(T x){return (x!=0 && (x&(x-1))==0);} //0 or 1

template<class T> inline T powmod(T a,T b,T mod) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}
template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%lld",&x); return x; }

const int mod=1e9+7;

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);

const int maxN = 1e5+7;
int a[maxN];
int tree[4*maxN];


void build(int node,int left, int right)
{
	if(left > right)
		return;
	if(left == right)
	{
		tree[node] = a[left];
		return;
	}
	int mid = mid(left,right);
	build(2*node,left,mid);
	build(2*node+1,mid+1,right);
	tree[node] = tree[2*node] + tree[2*node+1];
}

void update(int node,int left ,int right , int id , int val)
{
	if(left == right)
	{
		tree[node] = val;
		return ;
	}
	int mid = mid(left,right);
	if(id <= mid)
		update(2*node,left,mid,id,val);
	else
		update(2*node+1,mid+1,right,id,val);
	tree[node] = tree[2*node] + tree[2*node+1];
}
int query(int node , int left , int right ,int lq , int rq)
{
	if(left > rq || right < lq)
		return 0;
	if(left >= lq && right <= rq)
		return tree[node];
	int mid = mid(left,right);
	return query(2*node,left,mid,lq,rq) + query(2*node+1,mid+1,right,lq,rq);
}


int main()
{
	int t; cin >> t;
	for(int ii =1; ii <= t; ii++)
	{
		printf("Case %d:\n",ii);
		int n , q;
		n = nextint();
		q = nextint();
		assert( n <= 100000);
		for(int i = 0; i < n; i++)
			cin >> a[i];
		build(1,0,n-1);
		while(q--)
		{
			int tp = nextint(); 
			if(tp == 1)
			{
				int id = nextint(); 
				printf("%d\n",a[id]);
				a[id] = 0;
				update(1,0,n-1,id,0);

			}
			if(tp == 2)
			{
				int id = nextint(); 
				int v= nextint(); 
				a[id] += v;
				update(1,0,n-1,id,a[id]);

			}
			if(tp == 3)
			{
				int l = nextint(); 
				int r = nextint(); 
				printf("%d\n",query(1,0,n-1,l,r));
				// query sum[l,r]

			}
		}
	}


    return 0;
}

