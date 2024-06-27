// clang-format off
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ssize(x) int(x.size())
template<class A,class B>auto&operator<<(ostream&o,pair<A,B>p){return o<<'('<<p.first<<", "<<p.second<<')';}
template<typename T,typename = typename enable_if<!is_same<T,string>::value>::type>
auto operator<<(ostream&o,T x)->decltype(x.end(),o){o<<'{';int i=0;for(auto e:x)o<<(", ")+2*!i++<<e;return o<<'}';}
#ifdef DEBUG
#define debug(x...) cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...);}(x),cerr<<'\n'
#else
#define debug(...) {}
#endif
// clang-format on

vector<int> graph[500007];
vector<int> dag[500007];
vector<int> tdag[500007];
int deg_in[500007];
int toposort[500007];
bitset<500007> vis;
queue<int> q;

void dfs(int v)
{
    vis[v] = 1;
    for (int u : graph[v])
    {
        if (vis[u])
            continue;
        dfs(u);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, a, b;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1);
    if (!vis[2])
    {
        if (m)
            cout << "NIE\n";
        else
        {
            cout << "TAK\n";
            for (int i = 1; i <= n; i++)
                cout << i << ' ';
            cout << '\n';
        }
        return 0;
    }

    for (int i = 3; i <= n; i++)
    {
        if (vis[i])
            continue;
        if (!ssize(graph[i]))
        {
            graph[1].push_back(i);
            graph[2].push_back(i);
            graph[i].push_back(1);
            graph[i].push_back(2);
            continue;
        }
        cout << "NIE\n";
        return 0;
    }

    vis.reset();

    q.push(1);
    b = 0;
    while (!q.empty())
    {
        a = q.front();
        q.pop();
        b++;
        for (int u : tdag[a])
            vis[u] = 1;
        for (int u : graph[a])
        {
            if (vis[u])
                continue;
            debug(a, u);
            deg_in[u]++;
            dag[a].push_back(u);
            tdag[u].push_back(a);
            if (u == 2)
                continue;
            if (deg_in[u] * 2 == ssize(graph[u]))
                q.push(u);
            if (deg_in[u] * 2 > ssize(graph[u]))
            {
                cout << "NIE\n";
                return 0;
            }
        }
        for (int u : tdag[a])
            vis[u] = 0;
    }

    debug(b);

    if (b != n - 1)
    {
        cout << "NIE\n";
        return 0;
    }

    b = 0;
    q.push(1);
    while (!q.empty())
    {
        b++;
        a = q.front();
        q.pop();
        toposort[a] = b;
        for (int u : dag[a])
        {
            deg_in[u]--;
            if (deg_in[u])
                continue;
            q.push(u);
        }
    }

    cout << "TAK\n";
    for (int i = 1; i <= n; i++)
        cout << toposort[i] << ' ';
    cout << '\n';

    return 0;
}
