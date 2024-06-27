#include <bits/stdc++.h>
using namespace std;

#define frac pair<long long, long long>

long long trucks_x[100007];
long long trucks_d[100007];
frac trucks_v[100007];
long long pref_d[100007];

frac subtr(frac f1, frac f2){
    return {f1.first*f2.second - f2.first*f1.second, f1.second*f2.second};
}

frac calc_time(long long dist, frac v){
    return {dist*v.second, v.first};
}

bool compare_frac(frac f1, frac f2){
    if(f1.first/f1.second > f2.first/f2.second) return true;
    if(f1.first/f1.second < f2.first/f2.second) return false;
    f1.first %= f1.second; f2.first%=f2.second;
    return (f1.first*f2.second > f2.first*f1.second);
}

bool compare_greq_frac(frac f1, frac f2){
    if(f1.first/f1.second > f2.first/f2.second) return true;
    if(f1.first/f1.second < f2.first/f2.second) return false;
    f1.first %= f1.second; f2.first%=f2.second;
    return (f1.first*f2.second >= f2.first*f1.second);
}

bool pq_comparator(pair<int,frac> q1, pair<int,frac> q2){
    return compare_frac(q1.second, q2.second);
}

priority_queue<pair<int,frac>, vector<pair<int,frac>>, function<bool(pair<int,frac>, pair<int,frac>)>> pq(pq_comparator);

int repr[100007];
int sizes[100007];
pair<int,int> pm_truck[100007];

int F(int a){
    if(repr[a] == a) return a;
    repr[a] = F(repr[a]);
    return repr[a];
}

void U(int a, int b){
    a = F(a);
    b = F(b);
    if(a == b) return;
    if(sizes[a] > sizes[b]) swap(a, b);
    sizes[b] += sizes[a];
    repr[a] = b;
    pm_truck[b] = {min(pm_truck[a].first, pm_truck[b].first), max(pm_truck[a].second, pm_truck[b].second)};
}

long long getPos(int a){
    int b = pm_truck[F(a)].second;
    return trucks_x[b] - (pref_d[b] - pref_d[a]);
}

frac getV(int a){
    return trucks_v[pm_truck[F(a)].second];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    long long D, W, M, x, d, w, m;
    int num, res = 1;
    cin >> n >> D >> W >> M;

    for(int i=1; i<=n; i++){
        repr[i] = i;
        sizes[i] = 1;
        pm_truck[i] = {i-1, i};
    }

    for(int i=1; i<=n; i++){
        cin >> x >> d >> w >> m;
        trucks_x[i] = x;
        trucks_d[i] = d;
        pref_d[i] = pref_d[i-1] + d;
        trucks_v[i] = {w, m};
        if(i!=n) pq.push({-i, calc_time(x+D, subtr({W,M}, {w,m}))});
    }

    for(int i=n-1; i>0; i--){
        if(compare_greq_frac(trucks_v[i], getV(i+1)) && trucks_x[i+1]-trucks_d[i+1] == trucks_x[i]) U(i,i+1);
        if(compare_frac(getV(i), getV(i+1))){
            pq.push({i, calc_time(trucks_x[i+1]-trucks_d[i+1]-trucks_x[i], subtr(getV(i), getV(i+1)))});
        }
    }

    frac v_diff, final_dist, ttime;
    long long d_diff;
    pair<int, frac> query;
    while(!pq.empty()){
        query = pq.top();
        pq.pop();

        if(query.first < 0){
            num = -query.first;
            if(F(num) == F(num+1)) continue;
            v_diff = subtr(getV(num+1), getV(num));
            d_diff = getPos(num+1) - getPos(num) - trucks_d[num+1];
            if(v_diff.first == 0LL){
                if(d_diff >= D) res++;
                continue;
            }
            if(v_diff.first>0 && compare_greq_frac(query.second, {(D-d_diff)*v_diff.second,v_diff.first})) res++;
            if(v_diff.first<0 && compare_greq_frac({(d_diff-D)*v_diff.second,-v_diff.first}, query.second)) res++;
        }
        else{
            num = query.first;
            v_diff = subtr(getV(num), getV(num+1));
            d_diff = getPos(num+1) - getPos(num) - trucks_d[num+1];
            if(v_diff.first == 0LL) continue;
            ttime = calc_time(d_diff, v_diff);
            if(compare_frac(ttime, query.second) || compare_frac(query.second, ttime)){
                continue;
            }
            U(num, num+1);
            num = pm_truck[F(num)].first;
            if(num == 0) continue;
            v_diff = subtr(getV(num), getV(num+1));
            if(v_diff.first <= 0) continue;
            d_diff = getPos(num+1) - getPos(num) - trucks_d[num+1];
            pq.push({num, calc_time(d_diff, v_diff)});
        }
    }
    cout << res << '\n';
}