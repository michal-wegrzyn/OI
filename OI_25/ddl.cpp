#include <bits/stdc++.h>
using namespace std;

vector<pair<char, int>> ll1;
vector<pair<char, int>> ll2;

pair<int,int> pref_sum1[152];
pair<int,int> pref_sum2[152];

vector<pair<int,int>,int> v1;
vector<pair<int,int>,int> h1;
vector<pair<int,int>,int> v2;
vector<pair<int,int>,int> h2;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int m1, m2, n;
    char c;
    string s1, s2;
    cin >> m1;
    for(int i=0; i<m1; i++){
        cin >> c >> n;
        ll1.push_back({c,n});
    }
    cin >> m2;
    for(int i=0; i<m2; i++){
        cin >> c >> n;
        ll2.push_back({c,n});
    }
    for(int i=0; i<ll1.size(); i++){
        pref_sum1[i+1] = pref_sum1[i];
        if(ll1[i].first == 'T') pref_sum1[i+1].first += ll1[i].second;
        else pref_sum1[i+1].second += ll1[i].second;
    }

    for(int i=0; i<ll2.size(); i++){
        pref_sum2[i+1] = pref_sum2[i];
        if(ll2[i].first == 'T') pref_sum2[i+1].first += ll2[i].second;
        else pref_sum2[i+1].second += ll2[i].second;
    }

    for(int i=1; i<=ll1.size(); i++){
        for(int j=i; j<=ll1.size(); j++){}
    }
}

/*
bitset<3007> av1[3007];
bitset<3007> av2[3007];
bitset<3007> av;
pair<pair<int,int>, pair<int,int>> gr[4];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int m1, m2, n, n_sum1=0, n_sum2=0, t_count;
    string s1, s2;
    char c;
    cin >> m1;
    for(int i=0; i<m1; i++){
        cin >> c >> n;
        ll1.push_back({c,n});
        n_sum1 += n;
    }
    cin >> m2;
    for(int i=0; i<m2; i++){
        cin >> c >> n;
        ll2.push_back({c,n});
        n_sum2 += n;
    }

    if(n_sum1 <= 500000 && n_sum2 <= 500000){
        for(auto i : ll1){
            for(int j=0; j<i.second; j++) s1.push_back(i.first);
        }
        for(auto i : ll2){
            for(int j=0; j<i.second; j++) s2.push_back(i.first);
        }
        for(int i=0; i<s1.size(); i++){
            t_count = 0;
            for(int j=i; j<s1.size(); j++){
                if(s1[j]=='T') t_count++;
                av1[j-i+1][t_count] = 1;
            }
        }

        for(int i=0; i<s2.size(); i++){
            t_count = 0;
            for(int j=i; j<s2.size(); j++){
                if(s2[j]=='T') t_count++;
                av2[j-i+1][t_count] = 1;
            }
        }

        for(int i=3000; i>0; i--){
            av = (av1[i] & av2[i]);
            if(av.count()){
                cout << i << '\n';
                return 0;
            }
        }
        cout << 0 << '\n';
        return 0;
    }

    if(ll1[0].first=='T') pref_sum1[0] = {ll1[0].second, 0};
    else pref_sum1[0] = {0, ll1[0].second};

    for(int st1=0; st1<ll1.size(); st1++){
        for(int en1=st1; en1<ll1.size();en1++){
            if(st1 == en1){
                if(ll1[st1].first == 'T') gr[0] = {{0, ll1[st1].second}, {0,0}};
                else gr[0] = {{0,0},{0, ll1[st1].second}};
            }
            else{}
            for(int st2=0; st2<ll2.size(); st2++){
                for(int en2=st2; en2<ll2.size(); en2++){}
            }
        }
    }

}
*/