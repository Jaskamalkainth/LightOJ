/*
 *
 *    J1K7_7
 * 
 */
//Algo : Bellman Ford
//O(VE)
//http://lightoj.com/volume_showproblem.php?problem=1074
//1074 - Extended Traffic
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
#define pr(n)              printf("%d",n)
#define s(n)               scanf("%d",&n)
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))
#define snuke(c,itr)       for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
const int mod=1e9+7;

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);

inline bool ispow2(int x){return (x!=0 && (x&(x-1))==0);} //0 or 1

int msb(unsigned x){ union { double a; int b[2]; }; a = x; return (b[1] >> 20) - 1023; }

template<class T>
inline void cinarr(T a, int n){ for (int i=0;i<n;++i) cin >> a[i];}

inline ll powmod(ll a,ll b) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}

inline ll gcd(ll a,ll b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
inline ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%lld",&x); return x; }


vector<int> d ;
struct edge
{
	int a , b ,cost;  
};
vector<edge> e; 
void bellman_ford(int source , int n , int m ) 
{
	d.resize(n,mx_int);
	d[source] = 0;

	vector<int> p (n, -1);
	int x;
	for (int i=0; i<n; ++i) {
		x = -1;
		for (int j=0; j<m; ++j)
			if (d[e[j].a] < mx_int)
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = max (-mx_int, d[e[j].a] + e[j].cost);
					p[e[j].b] = e[j].a;
					x = e[j].b;
				}
	}
}

vi val;
int main()
{

	int t; cin >> t;
	for(int i = 1; i <= t; i++)
	{
		cout <<"Case " << i << ":" << "\n";
		int n ; cin >> n;
		for(int i = 0; i < n; i++)
		{
			int v; cin >> v;
			val.pb(v);
		}
		int m ; cin >> m;
		e.resize(m);
		for(int i = 0; i < m; i++)
		{
			int u , v; cin >> u >> v;
			e[i].a = u - 1;
			e[i].b = v - 1;
			int x  = (val[v-1]  - val[u-1]);
			e[i].cost = x*x*x;

		}
		bellman_ford(0,n,m);

		int q; cin >> q;
		while(q--)
		{
			int dest;
			cin >> dest;
			if ( d[dest-1] < 3  || d[dest-1] == mx_int) 
			{
				cout << "?" << "\n";
			}
			else
			{
				cout << d[dest-1] << "\n";
			}

		}
		e.clear();
		d.clear();
		val.clear();
	}
	return 0;
}

