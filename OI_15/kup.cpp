#include <iostream>
#include <vector>
#include <utility>
using namespace std;

long long K[2003][2003];
bool isOK[20003][20003];
long long prev_sums[2003][2003];

struct rrect{
    int u;
    int d;
    int l;
    int r;
};
vector<pair<int,int>> M;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n, k, num;
    cin >> k >> n;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin >> num;
            if(num>=k && num <= 2*k){
                cout << j << ' ' << i << ' ' << j << ' ' << i << '\n';
                return 0;
            }
            K[i][j] = num;
            if(num<k) isOK[i][j] = true;
            prev_sums[i][j] = prev_sums[i-1][j] + prev_sums[i][j-1] - prev_sums[i-1][j-1];
        }
    }
    int s = -1, curr_s, x, y;
    rrect best_rect;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n+1; j++){
            x = j;
            y = -1;
            for(int kk=0; kk<=i; kk++) if(!isOK[j][kk]) y = (j>y?j:y);
            while(!M.empty() && M.back().second < y+1){
                curr_s = prev_sums[M.back().first][M.back().second] - prev_sums[M.back().first][j-1] - prev_sums[i][M.back().second] + prev_sums[j-1][i];
                if(curr_s > s){
                    s = curr_s;
                    best_rect.u = M.back().second;
                    best_rect.d = i;
                    best_rect.l = M.back().first;
                    best_rect.r = j-1;
                }
                x = M.back().first;
                M.pop_back();
            }
            if((M.empty() && y<i) || M.back().second > y+1) M.push_back(make_pair(x, y+1));
        }
    }
    cout << best_rect.u << ' ' << best_rect.d << ' ' << best_rect.l << ' ' << best_rect.r << '\n';
}
