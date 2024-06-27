#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[500003];
bool is_protected[500003];
vector<int> result;

void protect(int v){
    is_protected[v] = true;
    for(int i:graph[v]){
        is_protected[i] = true;
        for(int j:graph[i]) is_protected[j] = true;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, k, num1, num2;
    cin >> n >> m >> k;
    for(int i=0; i<m; i++){
        cin >> num1 >> num2;
        graph[num1].push_back(num2);
        graph[num2].push_back(num1);
    }
    for(int i=1; i<=n; i++){
        if(!is_protected[i]){
            protect(i);
            result.push_back(i);
        }
    }
    cout << result.size() << '\n';
    for(int i:result) cout << i << ' ';
    return 0;
}