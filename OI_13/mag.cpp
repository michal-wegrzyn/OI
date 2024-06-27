#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

pair<int, int> tx[100003];
pair<int, int> ty[100003];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n, x, y, t, it=1, t_sum = 0, curr_t_sum = 0, best_optn_x=0, best_optn_y=0;
    long long min_length_sum = 4000000000000000000;
    long long curr_length_sum = 0;
    cin >> n;
    cin >> x >> y >> t;
    tx[0] = make_pair(x+y, t);
    ty[0] = make_pair(y-x, t);
    t_sum += t;
    for(int i=1; i<n; i++){
        cin >> x >> y >> t;
        tx[it]  = make_pair(x+y, t);
        ty[it] = make_pair(y-x, t);
        t_sum += t;
        it++;
    }
    sort(tx, tx+it);
    sort(ty, ty+it);
    for(int i=1; i<it; i++) curr_length_sum += tx[i].first - tx[0].first;
    min_length_sum = curr_length_sum;
    curr_t_sum += tx[0].second;
    best_optn_x = tx[0].first;
    for(int i=1; i<it; i++){
        curr_length_sum -= (tx[i].first-tx[i-1].first) * (t_sum-2*curr_t_sum);
        if(curr_length_sum < min_length_sum){
            min_length_sum = curr_length_sum;
            best_optn_x = tx[i].first;
        }
        curr_t_sum += tx[i].second;
    }

    curr_t_sum = 0;
    min_length_sum = 4000000000000000000;
    curr_length_sum = (long long)0;

    for(int i=1; i<it; i++) curr_length_sum += ty[i].first - ty[0].first;
    min_length_sum = curr_length_sum;
    curr_t_sum += ty[0].second;
    best_optn_y = ty[0].first;
    for(int i=1; i<it; i++){
        curr_length_sum -= (ty[i].first-ty[i-1].first) * (t_sum-2*curr_t_sum);
        if(curr_length_sum < min_length_sum){
            min_length_sum = curr_length_sum;
            best_optn_y = ty[i].first;
        }
        curr_t_sum += ty[i].second;
    }

    cout << best_optn_x - (best_optn_x+best_optn_y)/2 << ' ' << (best_optn_x+best_optn_y)/2;

    return 0;
}