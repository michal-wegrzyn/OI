#include <bits/stdc++.h>
using namespace std;

string board[1007];
vector<pair<pair<int,int>,pair<int,int>>> graph[1007][1007][6];

deque<pair<pair<int,int>,int>> dq;
int dist[1007][1007][6];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    string s;
    pair<int,int> P, K;
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
            for(int k=0; k<6; k++) dist[i][j][k] = INT_MAX/4;
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(board[i][j]=='X') continue;

            // 0 & 5
            if(board[i][j]=='.'){
                if(board[i][j+1]=='.'){
                    graph[i][j][0].push_back({{i,j+1},{0,1}});
                    graph[i][j+1][0].push_back({{i,j},{0,1}});
                }
                if(board[i][j+1]=='#'){
                    graph[i][j][0].push_back({{i,j+1},{3,1}});
                }
                if(board[i][j+1]!='X'){
                    graph[i][j+1][5].push_back({{i,j},{5,1}});
                }

                if(board[i+1][j]=='.'){
                    graph[i][j][0].push_back({{i+1,j},{0,1}});
                    graph[i+1][j][0].push_back({{i,j},{0,1}});
                    graph[i][j][5].push_back({{i+1,j},{5,1}});
                    graph[i+1][j][5].push_back({{i,j},{5,1}});
                }
                if(board[i+1][j]=='#'){
                    graph[i][j][0].push_back({{i+1,j},{1,1}});
                }
                if(board[i+1][j]!='X'){
                    graph[i+1][j][5].push_back({{i,j},{5,1}});
                }
            }
            else{
                if(board[i][j+1]=='.'){
                    graph[i][j+1][0].push_back({{i,j},{3,1}});
                }
                if(board[i+1][j]=='.'){
                    graph[i+1][j][0].push_back({{i,j},{1,1}});
                }
            }

            if(board[i][j+1]=='.'){
                graph[i][j][5].push_back({{i,j+1},{5,1}});
            }
            if(board[i+1][j]=='.'){
                graph[i][j][5].push_back({{i+1,j},{5,1}});
            }

            // 1 & 4
            if((board[i][j]=='.' || board[i][j]=='#') && (board[i][j+1]=='.' || board[i][j+1]=='#')){
                graph[i][j][1].push_back({{i,j+1},{1,1}});
                graph[i][j+1][1].push_back({{i,j},{1,1}});
                graph[i][j][4].push_back({{i,j+1},{4,1}});
                graph[i][j+1][4].push_back({{i,j},{4,1}});
            }

            // 2 & 3
            if((board[i][j]=='.' || board[i][j]=='#') && (board[i+1][j]=='.' || board[i+1][j]=='#')){
                graph[i][j][2].push_back({{i+1,j},{2,1}});
                graph[i+1][j][2].push_back({{i,j},{2,1}});
                graph[i][j][3].push_back({{i+1,j},{3,1}});
                graph[i+1][j][3].push_back({{i,j},{3,1}});
            }

            // change layer
            graph[i][j][0].push_back({{i,j}, {1,0}});
            graph[i][j][0].push_back({{i,j}, {3,0}});
            graph[i][j][1].push_back({{i,j}, {2,0}});
            graph[i][j][3].push_back({{i,j}, {4,0}});
            graph[i][j][2].push_back({{i,j}, {5,0}});
            graph[i][j][4].push_back({{i,j}, {5,0}});
        }
    }
    dq.push_back({P,0});
    dist[P.first][P.second][0] = 0;
    pair<pair<int,int>,int> curr;
    while(!dq.empty()){
        curr = dq.front();
        dq.pop_front();
        for(auto i:graph[curr.first.first][curr.first.second][curr.second]){
            if(dist[i.first.first][i.first.second][i.second.first] != INT_MAX/4) continue;
            if(i.second.second){
                dist[i.first.first][i.first.second][i.second.first] = dist[curr.first.first][curr.first.second][curr.second] + 1;
                dq.push_back({i.first, i.second.first});
            }
            else{
                dist[i.first.first][i.first.second][i.second.first] = dist[curr.first.first][curr.first.second][curr.second];
                dq.push_front({i.first, i.second.first});
            }
        }
    }

    int min_dist = dist[K.first][K.second][0];
    for(int i=1; i<6; i++) min_dist = min(min_dist, dist[K.first][K.second][i]);
    cout << min_dist << '\n';
}