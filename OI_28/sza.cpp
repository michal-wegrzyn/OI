#include <bits/stdc++.h>
using namespace std;

int n;

vector<pair<int,char>> graph[2003];
int deg[2003];
bool is_on_pattern[2003][2003];

struct trie_node{
    int parent;
    vector<int> children;
};

vector<trie_node> trie;
trie_node empty_node;

void dfs_trie(int v, int parent, int curr_node){
    // cout << '#' << v << ' ' << parent << ' ' << curr_node << '\n';
    for(auto i:graph[v]){
        if(i.first != parent){
            if(trie[curr_node].children[i.second-'A'] == -1){
                trie.push_back(empty_node);
                
                // cout << empty_node.parent << ' ' << '!' << ' ';
                // for(int j:empty_node.children) cout << j << ' ';
                // cout << '\n';
                trie[curr_node].children[i.second-'A'] = trie.size() - 1;
                trie[trie.size()-1].parent = curr_node;
            }
            dfs_trie(i.first, v, trie[curr_node].children[i.second-'A']);
        }
    }
}

int depth[2003];
void dfs_depth(int v, int parent){
    for(auto i:graph[v]){
        if(i.first != parent){
            depth[i.first] = depth[v]+1;
            dfs_depth(i.first, v);
        }
    }
}

vector<int> dfs_route;
void dfs_patterns(int v, int parent, int curr_node){
    dfs_route.push_back(v);
    if(curr_node>0){
        for(int i=1; i<dfs_route.size(); i++){
            is_on_pattern[curr_node][(depth[dfs_route[i-1]] > depth[dfs_route[i]] ? dfs_route[i-1] : dfs_route[i])] = true;
        }
    }
    for(auto i:graph[v]){
        if(i.first != parent){
            if(trie[curr_node].children[i.second-'A'] != -1) dfs_patterns(i.first, v, trie[curr_node].children[i.second-'A']);
        }
    }
    dfs_route.pop_back();
}

string reverse_str(string s){
    reverse(s.begin(), s.end());
    return s;
}

set<string> result;
string curr_pattern;
bool is_ok;
void dfs_result(int curr_node){
    if(curr_node>0){
        is_ok = true;
        for(int i=2; i<=n; i++){
            is_ok = is_ok && is_on_pattern[curr_node][i];
        }
        if(is_ok){
            result.insert(curr_pattern);
            result.insert(reverse_str(curr_pattern));
        }
    }
    for(int i=0; i<26; i++) if(trie[curr_node].children[i] != -1){
        curr_pattern += (char)('A'+i);
        dfs_result(trie[curr_node].children[i]);
        curr_pattern.pop_back();
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int a, b, leaf=0, curr_node = 0;
    char c;
    cin >> n;
    for(int i=1; i<n; i++){
        cin >> a >> b >> c;
        graph[a].push_back({b,c});
        graph[b].push_back({a,c});
        deg[a]++; deg[b]++;
    }
    for(int i=1; i<=n; i++) if(deg[i] == 1){
        leaf = i; break;
    }
    empty_node.parent = -1;
    empty_node.children = vector<int>(26,-1);
    trie.push_back(empty_node);
    dfs_trie(leaf, -1, 0);
    // for(auto i:trie){
    //     cout << i.parent << ' ' << '!' << ' ';
    //     for(int j:i.children) cout << j << ' ';
    //     cout << '\n';
    // }
    dfs_depth(1, -1);
    for(int i=1; i<=n; i++) dfs_patterns(i, -1, 0);
    dfs_result(0);
    cout << result.size() << '\n';
    for(auto it = result.begin(); it != result.end(); it++) cout << *it << '\n';
    return 0;
}