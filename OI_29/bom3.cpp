#include <bits/stdc++.h>
using namespace std;

string board[1007];
int dist_P[1007][1007];
int dist_K[1007][1007];

queue<pair<int,int>> q;
int dp_P[1007][1007][4];
char dir_P[1007][1007][4];
int dp_K[1007][1007][4];
char dir_K[1007][1007][4];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    string s;
    pair<int,int> P, K, bomb, curr;
    for(int i=0; i<=n+1; i++){
        board[0].push_back('X');
        board[n+1].push_back('X');
    }
    for(int i=1; i<=n; i++){
        cin >> s;
        board[i] = "X"+s+"X";
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(board[i][j]=='P'){
                P = {i,j};
                board[i][j] = '.';
            }
            if(board[i][j]=='K'){
                K = {i,j};
                board[i][j] = '.';
            }
        }
    }
    for(int i=0; i<=n+1; i++){
        for(int j=0; j<=n+1; j++){
            dist_P[i][j] = INT_MAX/4;
            dist_K[i][j] = INT_MAX/4;
            for(int k=0; k<4; k++) dp_P[i][j][k] = INT_MAX/4;
            for(int k=0; k<4; k++) dp_K[i][j][k] = INT_MAX/4;
        }
    }

    q.push(P);
    dist_P[P.first][P.second] = 0;
    while(!q.empty()){
        curr = q.front();
        q.pop();
        if(board[curr.first-1][curr.second]=='.' && dist_P[curr.first-1][curr.second] == INT_MAX/4){
            q.push({curr.first-1, curr.second});
            dist_P[curr.first-1][curr.second] = dist_P[curr.first][curr.second]+1;
        }
        if(board[curr.first+1][curr.second]=='.' && dist_P[curr.first+1][curr.second] == INT_MAX/4){
            q.push({curr.first+1, curr.second});
            dist_P[curr.first+1][curr.second] = dist_P[curr.first][curr.second]+1;
        }
        if(board[curr.first][curr.second-1]=='.' && dist_P[curr.first][curr.second-1] == INT_MAX/4){
            q.push({curr.first, curr.second-1});
            dist_P[curr.first][curr.second-1] = dist_P[curr.first][curr.second]+1;
        }
        if(board[curr.first][curr.second+1]=='.' && dist_P[curr.first][curr.second+1] == INT_MAX/4){
            q.push({curr.first, curr.second+1});
            dist_P[curr.first][curr.second+1] = dist_P[curr.first][curr.second]+1;
        }
    }

    q.push(K);
    dist_K[K.first][K.second] = 0;
    while(!q.empty()){
        curr = q.front();
        q.pop();
        if(board[curr.first-1][curr.second]=='.' && dist_K[curr.first-1][curr.second] == INT_MAX/4){
            q.push({curr.first-1, curr.second});
            dist_K[curr.first-1][curr.second] = dist_K[curr.first][curr.second]+1;
        }
        if(board[curr.first+1][curr.second]=='.' && dist_K[curr.first+1][curr.second] == INT_MAX/4){
            q.push({curr.first+1, curr.second});
            dist_K[curr.first+1][curr.second] = dist_K[curr.first][curr.second]+1;
        }
        if(board[curr.first][curr.second-1]=='.' && dist_K[curr.first][curr.second-1] == INT_MAX/4){
            q.push({curr.first, curr.second-1});
            dist_K[curr.first][curr.second-1] = dist_K[curr.first][curr.second]+1;
        }
        if(board[curr.first][curr.second+1]=='.' && dist_K[curr.first][curr.second+1] == INT_MAX/4){
            q.push({curr.first, curr.second+1});
            dist_K[curr.first][curr.second+1] = dist_K[curr.first][curr.second]+1;
        }
    }

    // 0 lewo  1 gora  2 prawo  3 dol

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(board[i][j]=='X') continue;
            dp_P[i][j][0] = min(dp_P[i][j-1][0], min(dist_P[i-1][j], dist_P[i+1][j]))+1;
            dp_K[i][j][0] = min(dp_K[i][j-1][0], min(dist_K[i-1][j], dist_K[i+1][j]))+1;
            dp_P[i][j][1] = min(dp_P[i-1][j][1], min(dist_P[i][j-1], dist_P[i][j+1]))+1;
            dp_K[i][j][1] = min(dp_K[i-1][j][1], min(dist_K[i][j-1], dist_K[i][j+1]))+1;
        }
    }

    for(int i=n; i>=1; i--){
        for(int j=n; j>=1; j--){
            if(board[i][j]=='X') continue;
            dp_P[i][j][2] = min(dp_P[i][j+1][2], min(dist_P[i-1][j], dist_P[i+1][j]))+1;
            dp_K[i][j][2] = min(dp_K[i][j+1][2], min(dist_K[i-1][j], dist_K[i+1][j]))+1;
            dp_P[i][j][3] = min(dp_P[i+1][j][3], min(dist_P[i][j-1], dist_P[i][j+1]))+1;
            dp_K[i][j][3] = min(dp_K[i+1][j][3], min(dist_K[i][j-1], dist_K[i][j+1]))+1;
        }
    }

    int res = dist_P[K.first][K.second];
    bomb = P;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=0; k<4; k++){
                for(int l=0; l<4; l++){
                    if(res > dp_P[i][j][k]+dp_K[i][j][l]){
                        res = dp_P[i][j][k]+dp_K[i][j][l];
                        bomb = {i,j};
                    }
                }
            }
        }
    }
    if(res == INT_MAX/4){
        cout << "NIE\n";
        return 0;
    }
    cout << res << '\n';
    cout << bomb.first << ' ' << bomb.second << '\n';
}