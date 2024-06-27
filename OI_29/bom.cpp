// Michał Węgrzyn
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

char grid[1003][1003];
int usuniete[2003][2];
int it_usuniete;
int n, px, py, kx, ky, bx, by;

int odl[1003][1003];
queue <pair<int,int>> q;
pair<int,int> curr_peak;
int curr_x, curr_y;

int BFS(){
    for(int i=0; i<=n+1; i++) for(int j=0; j<=n+1; j++) odl[i][j] = -1;
    odl[px][py] = 0;
    q.push(make_pair(px, py));
    while(!q.empty()){
        curr_x = q.front().first;
        curr_y = q.front().second;
        q.pop();
        if(grid[curr_x][curr_y-1]=='.' && odl[curr_x][curr_y-1] == -1){
            odl[curr_x][curr_y-1] = odl[curr_x][curr_y] + 1;
            q.push(make_pair(curr_x, curr_y-1));
        }
        if(grid[curr_x][curr_y+1]=='.' && odl[curr_x][curr_y+1] == -1){
            odl[curr_x][curr_y+1] = odl[curr_x][curr_y] + 1;
            q.push(make_pair(curr_x, curr_y+1));
        }
        if(grid[curr_x-1][curr_y]=='.' && odl[curr_x-1][curr_y] == -1){
            odl[curr_x-1][curr_y] = odl[curr_x][curr_y] + 1;
            q.push(make_pair(curr_x-1, curr_y));
        }
        if(grid[curr_x+1][curr_y]=='.' && odl[curr_x+1][curr_y] == -1){
            odl[curr_x+1][curr_y] = odl[curr_x][curr_y] + 1;
            q.push(make_pair(curr_x+1, curr_y));
        }
    }
    return odl[kx][ky];
}

vector<char> ppath;
void vpath(int x, int y){
    if(odl[x][y]==0) return;
    if(odl[x-1][y] == odl[x][y] - 1){
        ppath.push_back('D');
        vpath(x-1, y);
    }
    else if(odl[x+1][y] == odl[x][y] - 1){
        ppath.push_back('G');
        vpath(x+1, y);
    }
    else if(odl[x][y-1] == odl[x][y] - 1){
        ppath.push_back('P');
        vpath(x, y-1);
    }
    else if(odl[x][y+1] == odl[x][y] - 1){
        ppath.push_back('L');
        vpath(x, y+1);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    char c, curr_c;
    int result = 10000000;
    int curr_res;
    cin >> n;
    for(int i=0; i<=n+1; i++){
        grid[0][i] = 'X';
        grid[n+1][i] = 'X';
        grid[i][0] = 'X';
        grid[i][n+1] = 'X';
    }
    int mury = 0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin >> c;
            grid[i][j] = c;
            if(c=='P'){
                px = i;
                py = j;
                grid[i][j] = '.';
            }
            if(c=='K'){
                kx = i;
                ky = j;
                grid[i][j] = '.';
            }
            if(c=='#') mury++;
        }
    }
    if(!mury){
        curr_res = BFS();
        if(BFS()==-1){
            cout << "NIE\n";
            return 0;
        }
        cout << BFS() << '\n' << kx << ' ' << ky << '\n';
        vpath(kx,ky);
        for(int i=ppath.size()-1; i>=0; i--) cout << ppath[i];
        return 0;
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            curr_c = grid[i][j];
            if(curr_c=='X') continue;
            for(int k=i-1; grid[k][j]!='X'; k--) if(grid[k][j] == '#'){
                grid[k][j] = '.';
                usuniete[it_usuniete][0] = k;
                usuniete[it_usuniete][1] = j;
                it_usuniete++;
            }
            for(int k=i; grid[k][j]!='X'; k++) if(grid[k][j] == '#'){
                grid[k][j] = '.';
                usuniete[it_usuniete][0] = k;
                usuniete[it_usuniete][1] = j;
                it_usuniete++;
            }
            for(int k=j-1; grid[i][k]!='X'; k--) if(grid[i][k] == '#'){
                grid[i][k] = '.';
                usuniete[it_usuniete][0] = i;
                usuniete[it_usuniete][1] = k;
                it_usuniete++;
            }
            for(int k=j+1; grid[i][k]!='X'; k++) if(grid[i][k] == '#'){
                grid[i][k] = '.';
                usuniete[it_usuniete][0] = i;
                usuniete[it_usuniete][1] = k;
                it_usuniete++;
            }
            curr_res = BFS();
            if(result > curr_res && curr_res!=-1){
                result = curr_res;
                bx = i;
                by = j;
            }
            for(int k=0; k<it_usuniete; k++) grid[usuniete[k][0]][usuniete[k][1]] = '#';
            it_usuniete = 0;
        }
    }
    cout << result << '\n' << bx << ' ' << by << '\n';
    for(int k=bx-1; grid[k][by]!='X'; k--) if(grid[k][by] == '#'){
        grid[k][by] = '.';
        usuniete[it_usuniete][0] = k;
        usuniete[it_usuniete][1] = by;
        it_usuniete++;
    }
    for(int k=bx; grid[k][by]!='X'; k++) if(grid[k][by] == '#'){
        grid[k][by] = '.';
        usuniete[it_usuniete][0] = k;
        usuniete[it_usuniete][1] = by;
        it_usuniete++;
    }
    for(int k=by-1; grid[bx][k]!='X'; k--) if(grid[bx][k] == '#'){
        grid[bx][k] = '.';
        usuniete[it_usuniete][0] = bx;
        usuniete[it_usuniete][1] = k;
        it_usuniete++;
    }
    for(int k=by+1; grid[bx][k]!='X'; k++) if(grid[bx][k] == '#'){
        grid[bx][k] = '.';
        usuniete[it_usuniete][0] = bx;
        usuniete[it_usuniete][1] = k;
        it_usuniete++;
    }
    curr_res = BFS();
    vpath(kx,ky);
    for(int i=ppath.size()-1; i>=0; i--) cout << ppath[i];
    return 0;
}