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
#define heyA                printf("%s\n","heyA");
#define heyB                printf("%s\n","heyB");

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
const int maxn = 1e5+7;
int tree[4*maxn];
int lazy[4*maxn];
int a[maxn];

void build(int node,int left , int right)
{
	if(left == right)
	{
		tree[node] = a[left];
		return ;
	}
	int mid = mid(left,right);
	build(2*node,left,mid);
	build(2*node+1,mid+1,right);
	tree[node] = tree[2*node] + tree[2*node+1];
}

void range_update(int node ,int left , int right ,int lq ,int rq)
{
	if( lazy[node] )
	{
		tree[node] += (right-left+1)*lazy[node];  
		if(left != right)
		{
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		lazy[node] = 0;
	}
	if(left > rq || right < lq) 
		return ;
	if(left >= lq && right <= rq)
	{
		tree[node] += (right - left + 1);
		if(left != right)
		{
			lazy[2*node] += 1;
			lazy[2*node+1] += 1;
		}
		lazy[node] = 0;
		return ;
	}
	int mid = mid(left,right);
	range_update(2*node,left,mid,lq,rq);
	range_update(2*node+1,mid+1,right,lq,rq);
	tree[node] = tree[2*node] + tree[2*node+1];
}
int point_query(int node ,int left ,int right ,int id)
{
	if( lazy[node] )
	{
		tree[node] += (right-left+1)*lazy[node];  
		if(left != right)
		{
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		lazy[node] = 0;
	}
	if(id > right || id < left)
		return 0;
	if( left >= id && right <= id)
		return tree[node];
	int mid = mid(left,right);
	return point_query(2*node ,left ,mid ,id)+point_query(2*node+1,mid+1,right ,id);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	int t = nextint();
	for(int ii = 1; ii <= t; ii++)
	{
		for(int i = 0; i < 4*maxn; i++)
			tree[i] = lazy[i] = 0;
		printf("Case %d:\n",ii);
		char s[maxn];
		scanf("%s",s);
		int len = strlen(s);
		for(int i = 0; i < len; i++)
			a[i] = s[i] - '0';
		build(1,0,len-1);
		int q = nextint();
		while(q--)
		{
			char ch;
			scanf(" %c",&ch);
			if(ch == 'I')
			{
				int l = nextint();
				int r = nextint();
				range_update(1,0,len-1,l-1,r-1);
				// range update invert [l,r]
			}
			if(ch == 'Q')
			{
					int id = nextint();
				printf("%d\n",point_query(1,0,len-1,id-1)%2);
				//query ith bit  
			}
		}
	}
	return 0;
}

