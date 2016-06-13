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

const int maxN = 5e5+7;
map<int,int> compress;
vector<pair<int,int> >points(maxN);
vector<int> qq(maxN);
int cnt[maxN];
int main()
{
	int t; 
	scanf("%d",&t);
	for(int i = 1; i <= t; i++)
	{
		compress.clear();
		qq.clear();
		points.clear();
		for(int i = 0; i < maxN; i++)
			cnt[i] = 0;
		printf("Case %d:\n",i);
		int n, q;
		scanf("%d%d",&n,&q);
		for(int i = 0; i < n; i++)
		{
			int l , r;
			scanf("%d%d",&l,&r);
			compress[l]= 1;
			compress[r]= 1;
			points[i].ff = l;
			points[i].ss = r;
		}
		for(int i = 0; i < q; i++)
		{
			int pt;
			scanf("%d",&pt);
			compress[pt] = 1;
			qq[i] = pt;
		}
		int a = 0;
		for(map<int,int>::iterator it = compress.begin(); it!= compress.end(); it++)
			(*it).second = a++;
		for(int i = 0; i < n; i++)
		{
			int l = compress[points[i].ff];
			int r = compress[points[i].ss];
			cnt[l]++;
			cnt[r+1]--;
		}
		for(int i = 1; i < maxN; i++)
			cnt[i] += cnt[i-1];

		for(int i = 0; i < q; i++)
			printf("%d\n", cnt[compress[qq[i]]]);
	}
	return 0;
}

