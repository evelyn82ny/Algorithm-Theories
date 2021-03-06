#include <cstdio>
#include <algorithm>
using namespace std;

using ll=long long;
const int MX=1e5+1;

ll h[MX], cost[MX];
struct LinearFunc{
    // f(x) = ax + b
    ll a, b;
    double s;
    LinearFunc():LinearFunc(1,0){}
    LinearFunc(ll a1, ll b1):a(a1), b(b1), s(0){}
};

// upper_bound
bool operator<(const double &a, const LinearFunc &b){
    return a<b.s;
}

inline double cross(const LinearFunc &f, const LinearFunc &g){
    return (g.b-f.b)/(f.a-g.a);
}
int main(){
    int n; scanf("%d", &n);
    for(int i=0;i<n;++i) scanf("%lld", h+i);
    for(int i=0;i<n;++i) scanf("%lld", cost+i);
    
    ll dp[MX]={0,};
    LinearFunc f[MX];
    int top=0;
    for(int i=1;i<n;++i){
        LinearFunc g(cost[i-1], dp[i-1]);
        while(top>0){
            g.s=cross(f[top-1], g);
            if(f[top-1].s<g.s) break;
            --top; // pop
        }
        f[top++]=g;
       
        ll x=h[i];
        int fpos=top-1;
        int low, high, mid;
        
        // O(N*logN)
        if(x<f[top-1].s){
            low=0, high=top-1;
            while(low+1<high){
                mid=(low+high)/2;
                (x<f[mid].s ? high : low)=mid;
            }fpos=low;
        }
        
        // 직접구현(line 47~53)한 것과 upper_bound 사용시, 처리시간 동일
        /*
        int fpos=upper_bound(f, f+top, h[i]) - f;
        fpos--;
        dp[i]=f[fpos].a*h[i] + f[fpos].b;
        */
        
        dp[i]=f[fpos].a*x + f[fpos].b;
    }
    printf("%lld\n", dp[n-1]);
}
