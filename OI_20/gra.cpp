#include <iostream>
#include <vector>
#include <deque>
using namespace std;

deque<int> dq;
vector<int> graph[500003];
vector<int> result;
int odl[500003];

void BFS(int start){
    dq.push_back(start);
    odl[start] = 0;
    result.push_back(start);
    int curr_v;
    while(dq.size()){
        curr_v = dq.front();
        dq.pop_front();
        for(int i:graph[curr_v]){
            if(odl[i]==-1){
                odl[i] = odl[curr_v]+1;
                if(odl[i]==3){
                    odl[i] = 0;
                    result.push_back(i);
                    for(int j:graph[i]){
                        if(odl[j]==2) odl[j] = 1;
                        if(odl[j]==-1){
                            odl[j] = 1;
                            dq.push_front(j);
                        }
                    }
                }
                else dq.push_back(i);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(int i=0; i<500002; i++) odl[i] = -1;
    int n, m, k, num1, num2;
    cin >> n >> m >> k;
    for(int i=0; i<m; i++){
        cin >> num1 >> num2;
        graph[num1].push_back(num2);
        graph[num2].push_back(num1);
    }
    for(int i=1; i<=n; i++){
        if(odl[i]==-1){
            if(graph[i].size()==1) BFS(graph[i][0]);
            else BFS(i);
        }
    }
    cout << result.size() << '\n';
    for(int i:result) cout << i << ' ';
    return 0;
}