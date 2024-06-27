#include <bits/stdc++.h>
using namespace std;

vector<int> graph[500007];
int dp[500007];
int dp_up[500007];
int dp_down[500007];
bitset<500007> agent;

int D;
int dp_u, dp_d, dp_ud;
int pref_dp_u, pref_dp_d, pref_dp_ud;
void dfs(int v, int p){
    for(int i:graph[v]){
        if(i != p){
            dfs(i, v);
        }
    }
    D = 0;
    for(int i:graph[v]){
        if(i != p){
            D += dp[i];
        }
    }
    if(agent[v]){
        dp_up[v] = D;
        dp_down[v] = INT_MIN/8;
        dp[v] = D;
        for(int i:graph[v]){
            if(i != p){
                dp[v] = max(dp[v], D - dp[i] + 1 + dp_down[i]);
            }
        }
    }
    else{
        dp_up[v] = INT_MIN/8;
        for(int i:graph[v]){
            if(i != p){
                dp_up[v] = max(dp_up[v], D - dp[i] + 1 + dp_up[i]);
            }
        }

        dp_down[v] = D;
        for(int i:graph[v]){
            if(i != p){
                dp_down[v] = max(dp_down[v], D - dp[i] + 1 + dp_down[i]);
            }
        }

        dp[v] = D;
        for(int i:graph[v]){
            if(i != p){
                dp[v] = max(dp[v], D - dp[i] + 1 + dp_up[i]);
            }
        }

        pref_dp_u = INT_MIN/8;
        pref_dp_d = INT_MIN/8;
        pref_dp_ud = INT_MIN/8;
        for(int i:graph[v]){
            if(i != p){
                dp_d = max(pref_dp_d, dp_down[i]-dp[i]);
                dp_u = max(pref_dp_u, dp_up[i]-dp[i]);
                dp_ud = max(pref_dp_ud, max(pref_dp_d+dp_up[i]-dp[i], pref_dp_u+dp_down[i]-dp[i]));
                pref_dp_d = dp_d;
                pref_dp_u = dp_u;
                pref_dp_ud = dp_ud;
            }
        }

        dp[v] = max(dp[v], D+2+pref_dp_ud);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, k, a, b;
    cin >> n >> k;
    for(int i=0; i<k; i++){
        cin >> a; agent[a] = 1;
    }
    for(int i=1; i<n; i++){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1, -1);
    cout << 2*(n-k) - dp[1] << '\n';
    return 0;
}