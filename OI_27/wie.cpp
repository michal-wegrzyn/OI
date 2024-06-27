#include <bits/stdc++.h>
using namespace std;

pair<long long, long long> dominos[200007];
vector<pair<long long, long long>> to_left_info;
vector<pair<long long, long long>> to_right_info;

constexpr int base = 1 << 20;

long long tree[2*base+7];
long long tree2[2*base+7];

void add(int v, long long value){
    v = v+base;
    tree[v] += value*(v-base);
    tree2[v] += value;
    v /= 2;
    while(v){
        tree[v] = tree[2*v]+tree[2*v+1];
        tree2[v] = tree2[2*v]+tree2[2*v+1];
        v /= 2;
    }
}

long long query(int start, int end){
    long long result = 0;
    start = start - 1 + base;
    end = end + 1 + base;
    while(start/2 != end/2){
        if(!(start&1)) result += tree[start+1];
        if(end&1) result += tree[end-1];
        start /= 2;
        end /= 2;
    }
    return result;
}

long long query2(int start, int end){
    long long result = 0;
    start = start - 1 + base;
    end = end + 1 + base;
    while(start/2 != end/2){
        if(!(start&1)) result += tree2[start+1];
        if(end&1) result += tree2[end-1];
        start /= 2;
        end /= 2;
    }
    return result;
}

long long N1, N2, H1, H2, count1, req, res, best_res;
int sstart, endd;

pair<int,long long> bsrch(){
    int v = 1;
    long long result = 0LL;
    while(v<base){
        if(result + tree[v*2] <= N2){
            result += tree[v*2];
            v = v*2+1;
        }
        else v *= 2;
    }
    return {v-base, N2-result};
}

bool is_possible(){
    if(sstart == endd) return true;
    if(count1>=N1) return (count1*H1+tree[1] <= N1*H1+N2);
    pair<int,long long> r = bsrch();
    if(r.first == base-1) return true;
    req = count1 + query2(r.first, base-1) - r.second/r.first;
    // cout << query2(r.first, base-1) << ' ' << r.second/r.first << '\n';
    return (req<=N1);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    long long x, h, mxx, mnx;
    
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> x >> h;
        dominos[i] =  {x, h};
    }
    cin >> N1 >> H1 >> N2 >> H2;
    H1 /= H2;
    to_left_info.push_back({1,0});
    mxx = dominos[0].first;

    for(int i=1; i<n; i++){
        mxx = max(mxx, dominos[i-1].first+dominos[i-1].second);
        if(mxx >= dominos[i].first) to_left_info.back().first++;
        else{
            to_left_info.back().second = (dominos[i].first - mxx+H2-1)/H2;
            to_left_info.push_back({1,0});

        }
    }

    mnx = dominos[n-1].first;
    to_right_info.push_back({1,0});
    for(int i=n-2; i>=0; i--){
        mnx = min(mnx, dominos[i+1].first-dominos[i+1].second);
        if(mnx <= dominos[i].first) to_right_info.back().first++;
        else{
            to_right_info.back().second =  (mnx - dominos[i].first+H2-1)/H2;
            to_right_info.push_back({1,0});
        }
    }

    sstart = 0;
    res = to_left_info[0].first;
    best_res = res;
    for(endd=1; endd<to_left_info.size(); endd++){
        count1 += to_left_info[endd-1].second/H1;
        add(to_left_info[endd-1].second % H1, 1);
        res += to_left_info[endd].first;
        while(!is_possible()){
            count1 -= to_left_info[sstart].second/H1;
            add(to_left_info[sstart].second % H1, -1);
            res -= to_left_info[sstart].first;
            sstart++;
        }
        best_res = max(best_res, res);
    }


    count1 = 0;
    for(int i=0; i<2*base; i++){ tree[i]=0LL; tree2[i]=0LL;}
    sstart = 0;
    res = to_right_info[0].first;
    best_res = max(best_res, res);
    for(endd=1; endd<to_right_info.size(); endd++){
        count1 += to_right_info[endd-1].second/H1;
        add(to_right_info[endd-1].second % H1, 1);
        res += to_right_info[endd].first;
        while(!is_possible()){
            count1 -= to_right_info[sstart].second/H1;
            add(to_right_info[sstart].second % H1, -1);
            res -= to_right_info[sstart].first;
            sstart++;
        }
        best_res = max(best_res, res);
    }

    cout << best_res + N1 + N2 << '\n';
}