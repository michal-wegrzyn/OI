// Michał Węgrzyn
#include <iostream>
#include <vector>
using namespace std;

int group[1000003];
int sizes[2];
vector<int> graph[1000003];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q, x, w;
    char c;
    cin >> q;
    int curr_num = 2;
    if(q<=5000){
        graph[1].push_back(2);
        graph[2].push_back(1);
        for(int i=0; i<q; i++){
            cin >> c >> x;
            if(c=='W'){
                curr_num++;
                graph[curr_num].push_back(x);
                graph[x].push_back(curr_num);
            }
            if(c=='Z'){
                curr_num++;
                for(int j:graph[x]){
                    graph[curr_num].push_back(j);
                    graph[j].push_back(curr_num);
                }
            }
            if(c=='?') cout << graph[x].size() << '\n';
        }
        return 0;
    }
    group[1] = 0;
    group[2] = 1;
    sizes[0] = 1;
    sizes[1] = 1;
    for(int i=1; i<=q; i++){
        cin >> c >> x;
        if(c=='W') return 0;
        if(c=='Z'){
            curr_num++;
            group[curr_num] = group[x];
            sizes[group[curr_num]]++;
        } 
        if(c=='?'){
            if(group[x]==0) cout << sizes[1] << '\n';
            else cout << sizes[0] << '\n';
        }
    }
}