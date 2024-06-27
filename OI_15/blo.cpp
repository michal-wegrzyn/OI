#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[100003];
vector<int> graph2[100003];
bool visited[100003];
int dist[100003];
int low[100003];
bool isAP[100003];
long long sizes[100003];
long long sizes2[100003];
long long result[100003];
int ttime;

void AP(int v, int parent){
    //cout << v << ' ' << parent << '\n';
	int children = 0;
	visited[v] = true;
	dist[v] = low[v] = ++ttime;
	for (int u : graph[v]) {
		if (!visited[u]) {
            graph2[v].push_back(u);
			children++;
			AP(u, v);
            sizes[v] += sizes[u]+1;
			low[v] = min(low[v], low[u]);
			if (parent != -1 && low[u] >= dist[v]) isAP[v] = true;
		}
		else if (u != parent) low[v] = min(low[v], dist[u]);
	}

	if (parent == -1 && children > 1) isAP[v] = true;

    for(int u : graph2[v]) if(low[v] < low[u] || isAP[v] == false){
            sizes2[v] += sizes[u]+1;
            result[v] -= (sizes[u]+1)*(sizes[u]+1);
        }
}

long long nn;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	int n, m, num1, num2;
    cin >> n >> m;
    nn = (long long) n;
    for(int i=0; i<m; i++){
        cin >> num1 >> num2;
        graph[num1].push_back(num2);
        graph[num2].push_back(num1);
    }
    //cout << '\n';

    AP(1, -1);
    // cout << '\n';
	// for (int i = 1; i<=n; i++) if (isAP[i]) cout << i << " ";
    // cout << '\n';
    // for(int i=1; i<=n; i++) cout << low[i] << ' ';
    // cout << '\n';
    // for(int i=1; i<=n; i++) cout << sizes[i] << ' ';
    // cout << '\n';
    // for(int i=1; i<=n; i++) cout << sizes2[i] << ' ';
    for(int i=1; i<=n; i++) result[i] += (nn-1)*(nn-1) - (nn-sizes2[i]-1)*(nn-sizes2[i]-1) + 2*(nn-1);
    for(int i=1; i<=n; i++){
        if(isAP[i]) cout << result[i] << '\n';
        else cout << 2*n-2 << '\n';
    }
	return 0;
}
