/*
 *
 *    J1K7_7
 * 
 */
// Suffix Array
// http://lightoj.com/volume_showproblem.php?problem=1314
// 1314 - Names for Babies
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


#define MAXN 10004
int lcp[MAXN], cnt[256], cls[2][MAXN], sa[2][MAXN], st[MAXN], rnk[MAXN];
//sa[1][0] sa[1][1] ..... sa[1][n] where n=str.length() 
//sa[1][i] i=0->n gives the Suffix Array
//For LCP Array lcp[i] i=0-->n

void suffixArray(string s) {
    int i, j;
    int n = s.size();
    for (i = 0; i < n; i++) { cnt[s[i]] ++; cls[0][i] = s[i];}
    for (i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
    for (i = 0; i < n; i++) sa[0][--cnt[cls[0][i]]] = i;
    int cur = 0;
    for (i = 0; (1 << i) < n; i++) {
        int clen = (1 << i);
        for (j = 0; j < n; j++) {
            if (j > 0 && sa[cur][j - 1] + clen < n && cls[cur][sa[cur][j]] == cls[cur][sa[cur][j - 1]] &&
                    cls[cur][sa[cur][j] + clen / 2] == cls[cur][sa[cur][j - 1] + clen / 2]
               )
                cls[1 - cur][sa[cur][j]] = cls[1 - cur][sa[cur][j - 1]];
            else cls[1 - cur][sa[cur][j]] = j;
        }
        for (j = 0; j < n; j++) { st[j] = j; sa[1 - cur][j] = sa[cur][j]; }
        for (j = 0; j < n; j++) {
            int cele = sa[cur][j] - clen;
            if (cele >= 0) sa[1 - cur][st[cls[1 - cur][cele]]++] = cele;
        }
        cur = 1 - cur;
    }
    for (i = 0; i < n; i++) { sa[0][i] = sa[cur][i]; rnk[sa[cur][i]] = i;}
    int x = 0;
    for (i = 0; i < n; i++) {
        if (rnk[i] < n - 1) {
            for (j = sa[cur][rnk[i] + 1]; max(i, j) + x < n && s[i + x] == s[j + x]; x++);
            lcp[rnk[i] + 1] = x; if (x > 0) x--;
        }
    }
}

void init()
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j< MAXN; j++)
		cls[i][j] = sa[i][j] =0;
	}
	for(int i = 0; i < MAXN; i++)
	{
		lcp[i] = 0;
		st[i] = 0;
		if(i<256)
			cnt[i] = 0;
	}
}


int main()
{
	int t; cin >> t;
	for(int i = 1; i <= t; i++)
	{
		cout << "Case " << i << ": " ;
		init();
				
		string s; cin >> s;
		int p , q; cin >> p >> q;
		suffixArray(s);
		int n = s.size();

		ll t = (n-sa[1][0]);
		ll ans = 0;
		if ( p <= t ) 
		{
			if ( q <= t )
			{
				ans += (q-p+1);
			}
			else
			{
				ans += (t-p+1);  
			}
		}
		for(int i = 1; i < n; i++)
		{
			t = (n-sa[1][i]) - lcp[i]; 
			ll p1 = (p -lcp[i] <= 0 )? 1 : (p-lcp[i]);
			ll q1 = (q -lcp[i] < 0 )? 0 : (q-lcp[i]);
			if ( p1 <= t ) 
			{
				if ( q1 <= t )
				{
					ans += (q1-p1+1);
				}
				else
				{
					ans += (t-p1+1);  
				}
			}
		}
		cout << ans << "\n";
	}
	return 0;
}

