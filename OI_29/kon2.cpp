#include <bits/stdc++.h>
using namespace std;

bitset<1000007> XY;
vector<pair<char,int>> queries;
pair<int,int> pointers[1000007]; // v
vector<int> graph[1000007]; // edge
pair<int,int> edges[1000007]; // v

constexpr int base = 1 << 21;
int tree[2*base+7];
pair<int,int> tree_e_pos[1000007];
int tree_v_pos[1000007];

void add(int v, int value){
    v += base;
    while(v){
        tree[v] += value;
        v >>= 1;
    }
}

int query(int a, int b){
    a += base-1;
    b += base+1;
    int res = 0;
    while(a/2 != b/2){
        if(!(a&1)) res += tree[a+1];
        if(b&1) res += tree[b-1];
        a >>= 1; b >>= 1;
    }
    return res;
}

int last_tree_pos;
void dfs(int v){
    tree_v_pos[v] = last_tree_pos;
    for(int i:graph[v]){
        last_tree_pos++;
        tree_e_pos[i].first = last_tree_pos;
        dfs(edges[i].second);
        last_tree_pos++;
        tree_e_pos[i].second = last_tree_pos;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int q, x, curr_dancer = 2, last_v_num = 3;
    char c;
    cin >> q;
    XY[1] = 0; // X
    XY[2] = 1; // Y
    graph[0].push_back(2);
    edges[2] = {0,2};
    pointers[1] = {0,2};

    graph[1].push_back(1);
    edges[1] = {1,3};
    pointers[2] = {1,3};
    
    for(int i=0; i<q; i++){
        cin >> c >> x;
        queries.push_back({c,x});
        if(c=='?') continue;

        curr_dancer++;
        if(c=='Z') XY[curr_dancer] = XY[x];
        else XY[curr_dancer] = !XY[x];

        if(c=='W'){// Wybredna osoba
            pointers[curr_dancer] = edges[x];

            last_v_num++;
            graph[pointers[x].second].push_back(curr_dancer);
            edges[curr_dancer] = {pointers[x].second, last_v_num};
            pointers[x].second = last_v_num;
        }
        else{ // Zazdrosna osoba
            pointers[curr_dancer] = pointers[x];

            last_v_num++;
            edges[curr_dancer] = {last_v_num, edges[x].second};
            edges[x].second = last_v_num;
            graph[last_v_num].push_back(curr_dancer);
        }
    }

    /*for(int i=0; i<=last_v_num; i++){
        cout << i << "   ";
        for(int j:graph[i]) cout << j << ' ';
        cout << '\n';
    }
    cout << '\n';
    for(int i=1; i<=curr_dancer; i++){
        cout << i << "   " << edges[i].first << ' ' << edges[i].second << '\n';
    }
    cout << '\n';
    for(int i=1; i<=curr_dancer; i++){
        cout << i << "   " << pointers[i].first << ' ' << pointers[i].second << '\n';
    }*/
    dfs(0); dfs(1);
    /*for(int i=0; i<=last_v_num; i++) cout << tree_v_pos[i] << ' ';
    cout << '\n';
    for(int i=1; i<=curr_dancer; i++){
        cout << tree_e_pos[i].first << ' ' << tree_e_pos[i].second << '\n';
    }*/

    add(tree_e_pos[1].first, 1);
    add(tree_e_pos[1].second, -1);
    add(tree_e_pos[2].first, 1);
    add(tree_e_pos[2].second, -1);
    curr_dancer = 2;

    for(auto i : queries){
        if(i.first == '?'){
            cout << query(tree_v_pos[pointers[i.second].first]+1, tree_v_pos[pointers[i.second].second]) << '\n';
        }
        else{
            curr_dancer++;
            add(tree_e_pos[curr_dancer].first, 1);
            add(tree_e_pos[curr_dancer].second, -1);
        }
    }
}