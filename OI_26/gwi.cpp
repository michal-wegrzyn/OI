#include <bits/stdc++.h>
using namespace std;

vector<int> result;
vector<pair<int,bool>> operations;
bool is_in_result[500003];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, s, l, r;
    cin >> n >> s;
    cin >> l >> r;
    long long cost = min(l, r);
    int min_diff = abs(l-r);
    int diff_index = 1;
    if(l < r) operations.push_back({1,1});
    else operations.push_back({1,0});
    for(int i=2; i<n; i++){
        cin >> l >> r;
        cost += min(l, r);
        if((l<r) == operations.back().second) operations.back().first++;
        else operations.push_back({1, !operations.back().second});
        if(operations.size() == 1 && s+i<=n+1){
            if(abs(l-r) < min_diff){
                min_diff = abs(l-r);
                diff_index = i;
            }
        }
    }
    int start_del = 0, end_del = n+1;
    if(operations[0].second && operations[0].first >= s){
        cost += min_diff;
        operations[0].first -= diff_index;
        for(int i=diff_index-1; i>0; i--) result.push_back(i);
        start_del = diff_index-1;
        if(diff_index != operations[0].first){
            result.push_back(n);
            end_del = n;
        }
        else{
            result.push_back(diff_index);
            start_del = diff_index;
        }
    }
    else if(!operations[0].second && operations[0].first + s > n){
        operations[0].first -= diff_index;
        cost += min_diff;
        for(int i=n-diff_index+1; i<=n; i++) result.push_back(i);
        end_del = n-diff_index+1;
        if(diff_index != operations[0].first){
            result.push_back(1);
            start_del = 1;
        }
        else{
            result.push_back(n-diff_index);
            end_del = n-diff_index;
        }
    }
    // for(auto i : operations) cout << i.first << ' ' << i.second << '\n';
    for(auto i : operations){
        if(!i.first) continue;
        if(i.second){
            for(int j = start_del+i.first; j>start_del; j--) result.push_back(j);
            start_del += i.first;
        }
        else{
            for(int j=end_del-i.first; j<end_del; j++) result.push_back(j);
            end_del -= i.first;
        }
    }
    cout << cost << '\n' << s << ' ';
    int not_in_result;
    for(int i:result) is_in_result[i] = true;
    for(not_in_result=1; is_in_result[not_in_result]; not_in_result++);
    if(not_in_result == s) for(int i:result) cout << i << ' ';
    else if(not_in_result>s) for(int i:result) cout << (i>=s && i<not_in_result?i+1:i) << ' ';
    else for(int i:result) cout << (i>not_in_result && i <= s?i-1:i) << ' ';
    cout << '\n';
}