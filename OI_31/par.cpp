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

vector<int> graph[200007][3];
vector<int> d_graph[200007];
vector<int> td_graph[200007];
queue<int> q;
int deg_in[200007];
vector<int> toposort;
int max_path_v[200007];
int max_path;

pair<int, int> dp[200007];
bitset<200007> is_blocked;

bool dfs(int v, int p)
{
    pair<int, int> ans = {1, max_path};

    for (int i : graph[v][1])
    {
        if (i == p)
            continue;
        if (!dfs(i, v))
            return 0;
        ans.second = min(ans.second, dp[i].second - 1);
    }

    for (int i : graph[v][2])
    {
        if (i == p)
            continue;
        if (!dfs(i, v))
            return 0;
        ans.first = max(ans.first, dp[i].first + 1);
    }

    vector<int> blocked;

    for (int i : graph[v][0])
    {
        if (i == p)
            continue;
        if (!dfs(i, v))
            return 0;
        if (dp[i].first == dp[i].second)
        {
            blocked.push_back(dp[i].first);
        }
    }

    for (int i : blocked)
        is_blocked[i] = 1;

    for (int i = ans.first; i <= ans.second; i++)
    {
        if (is_blocked[i])
            ans.first++;
        else
            break;
    }

    for (int i = ans.second; i >= ans.first; i--)
    {
        if (is_blocked[i])
            ans.second--;
        else
            break;
    }

    for (int i : blocked)
        is_blocked[i] = 0;

    blocked.clear();

    dp[v] = ans;

    return (ans.first <= ans.second);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t, n, a, b, d;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i < n; i++)
        {
            cin >> a >> b >> d;
            if (d == 0)
            {
                graph[a][0].push_back(b);
                graph[b][0].push_back(a);
            }
            else
            {
                graph[a][1].push_back(b);
                graph[b][2].push_back(a);
                d_graph[a].push_back(b);
                td_graph[b].push_back(a);
                deg_in[b]++;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (deg_in[i] == 0)
                q.push(i);
        }

        while (!q.empty())
        {
            a = q.front();
            q.pop();
            toposort.push_back(a);
            for (int i : d_graph[a])
            {
                deg_in[i]--;
                if (deg_in[i] == 0)
                    q.push(i);
            }
        }

        for (int v : toposort)
        {
            d = 1;
            for (int u : td_graph[v])
                d = max(d, max_path_v[u] + 1);
            max_path_v[v] = d;
        }

        max_path = 1;
        for (int i = 1; i <= n; i++)
            max_path = max(d, max_path_v[i]);

        if (dfs(1, -1))
            cout << max_path << '\n';
        else
            cout << max_path + 1 << '\n';

        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < 3; j++)
                graph[i][j].clear();
            d_graph[i].clear();
            td_graph[i].clear();
            max_path_v[i] = 0;
        }

        toposort.clear();
    }

    return 0;
}
