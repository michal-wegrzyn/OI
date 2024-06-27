#include <bits/stdc++.h>
using namespace std;

int board[2007][2007];
int time_info[2007][2007];
vector<int> snake;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int m, p, n, w, k, c, t=1;
    cin >> m >> p >> n;
    for(int i=0; i<=m+1; i++){
        for(int j=0; j<=m+1; j++) board[i][j] = -1;
    }
    for(int i=0; i<p; i++){
        cin >> w >> k >> c;
        board[w][k] = c;
    }

    pair<int,int> head_pos = {1,1};
    char op;
    snake.push_back(0);
    time_info[1][1] = 1;
    for(int i=0; i<n; i++){
        cin >> op;
        if(op == 'Z'){
            cin >> w >> k;
            if(time_info[w][k] == 0){
                cout << -1 << '\n';
                continue;
            }
            if(t-time_info[w][k] >= snake.size()){
                cout << -1 << '\n';
                continue;
            }
            cout << snake[snake.size()-1-t+time_info[w][k]] << '\n';
            continue;
        }
        t++;
        if(op=='G') head_pos.first--;
        if(op=='D') head_pos.first++;
        if(op=='P') head_pos.second++;
        if(op=='L') head_pos.second--;
        time_info[head_pos.first][head_pos.second] = t;
        if(board[head_pos.first][head_pos.second] != -1){
            snake.push_back(board[head_pos.first][head_pos.second]);
            board[head_pos.first][head_pos.second] = -1;
        }
    }
}