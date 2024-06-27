#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int dane[1000003][2];
priority_queue<pair<int, int>> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, x, y, wynik, curr_wynik, mx, sstart=0;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> x >> y;
        dane[i][0] = x;
        dane[i][1] = y;
    }
    wynik = 1; curr_wynik = 1;
    pq.push(make_pair(dane[0][0], 0));
    for(int i = 1; i<n; i++){
        if(!pq.empty()) while(pq.top().second < sstart || dane[i][1]<pq.top().first){
            if(pq.top().second < sstart){
                pq.pop();
                if(pq.empty()) break;
                continue;
            }
            mx = pq.top().second;
            sstart = mx+1;
            curr_wynik = i - sstart;
            pq.pop();
            if(pq.empty()) break;
        }
        pq.push(make_pair(dane[i][0], i));
        curr_wynik++;
        if(curr_wynik > wynik) wynik = curr_wynik;
    }
    cout << wynik;
    return 0;
}