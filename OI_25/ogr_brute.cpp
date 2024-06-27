#include <bits/stdc++.h>
using namespace std;

struct p{
    long long x;
    long long y;
    long long w;
};

long long cross_product(p p0, p p1, p p2){
    return (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);
}

p points[20];
int is_inside[1<<20];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    long long x, y, w;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> x >> y >> w;
        points[i] = {x,y,w};
    }
    int mask;
    long long curr_res, best_res = LONG_LONG_MIN/2;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            for(int k=j+1; k<n; k++){
                mask = (1<<i)+(1<<j)+(1<<k);
                is_inside[mask] |= (1<<i);
                is_inside[mask] |= (1<<j);
                is_inside[mask] |= (1<<k);
                for(int l=0; l<n; l++){
                    if(l==i || l==j || l==k) continue;
                    if(cross_product(points[i], points[j], points[l])>0 && cross_product(points[j], points[k], points[l])>0 && cross_product(points[k], points[i], points[l])>0){
                        is_inside[mask] |= (1<<l);
                    }
                    if(cross_product(points[i], points[j], points[l])<0 && cross_product(points[j], points[k], points[l])<0 && cross_product(points[k], points[i], points[l])<0){
                        is_inside[mask] |= (1<<l);
                    }
                }
                if(is_inside[mask] != mask) continue;
                curr_res = 0;
                for(int j=0; j<n; j++) if(mask&(1<<j)) curr_res += points[j].w;
                if(curr_res > best_res) best_res = curr_res;
            }
        }
    }
    for(int i=0; i<(1<<n); i++){
        if(__builtin_popcount(i)<4) continue;
        for(int j=0; j<n; j++){
            if(i&(1<<j)) is_inside[i] |= is_inside[i^(1<<j)];
        }
        if(is_inside[i] != i) continue;
        curr_res = 0;
        for(int j=0; j<n; j++) if(i&(1<<j)) curr_res += points[j].w;
        if(curr_res > best_res) best_res = curr_res;
    }

    cout << best_res << '\n';
}