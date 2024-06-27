// clang-format off
#include<bits/stdc++.h>
#include <type_traits>
using namespace std;
#define ll long long
#define ssize(x) int(x.size())
template<class A,class B>auto&operator<<(ostream&o,pair<A,B>p){return o<<'('<<p.first<<", "<<p.second<<')';}
template<class T>auto operator<<(ostream&o,T x)->decltype(x.end(),o){o<<'{';int i=0;for(auto e:x)o<<(", ")+2*!i++<<e;return o<<'}';}
#ifdef DEBUG
#define debug(x...) cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...);}(x),cerr<<'\n'
#else
#define debug(...) {}
#endif
// clang-format on

pair<int, int> buttons[500007];
vector<pair<int, int>> rows[100007];
vector<pair<int, int>> cols[100007];

vector<int> graph[500007];
vector<int> graph2[500007];
int v_deg[500007];
int cnt_row[100007];
int cnt_col[100007];
vector<int> vpath;
int pos_on_path[500007];
bitset<500007> is_deleted;
queue<int> q;

bitset<100007> parity_row;
bitset<100007> parity_col;

vector<int> res;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, a, b, v;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b;
        buttons[i] = {a, b};
        rows[a].push_back({b, i});
        cols[b].push_back({a, i});
    }

    for (int i = 1; i <= n; i++)
    {
        sort(rows[i].begin(), rows[i].end());
        for (int j = 0; j < ssize(rows[i]) - 1; j++)
        {
            graph[rows[i][j].second].push_back(rows[i][j + 1].second);
            graph[rows[i][j + 1].second].push_back(rows[i][j].second);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        sort(cols[i].begin(), cols[i].end());
        for (int j = 0; j < ssize(cols[i]) - 1; j++)
        {
            graph[cols[i][j].second].push_back(cols[i][j + 1].second);
            graph[cols[i][j + 1].second].push_back(cols[i][j].second);
        }
    }

    for (int i = 1; i <= m; i++)
    {
        v_deg[i] = ssize(graph[i]);
        if (v_deg[i] <= 1)
        {
            q.push(i);
            is_deleted[i] = 1;
        }
    }

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        if (v_deg[v] == 0)
            continue;
        v_deg[v] = 0;
        for (int u : graph[v])
        {
            if (is_deleted[u])
                continue;
            v_deg[u]--;
            if (v_deg[u] <= 1)
            {
                q.push(u);
                is_deleted[u] = 1;
            }
        }
    }

    v = -1;

    for (int i = 1; i <= m; i++)
    {
        if (is_deleted[i])
            continue;
        v = i;
        break;
    }

    if (v != -1)
    {
        for (int i = 1; i <= m; i++)
        {
            if (is_deleted[i])
                continue;
            for (int u : graph[i])
            {
                if (is_deleted[u])
                    continue;
                graph2[i].push_back(u);
            }
        }
        vpath.push_back(-1);
        vpath.push_back(v);
        pos_on_path[v] = 1;
        a = graph2[v][0];
        while (!pos_on_path[a])
        {
            pos_on_path[a] = ssize(vpath);
            vpath.push_back(a);
            b = v;
            v = a;
            a = graph2[v][0];
            if (a == b)
                a = graph2[v][1];
        }

        vpath[0] = vpath.back();
        vpath.push_back(a);
        for (int i = 1; i < ssize(vpath) - 1; i++)
        {
            if (buttons[vpath[i - 1]].first == buttons[vpath[i + 1]].first)
                continue;
            else if (buttons[vpath[i - 1]].second == buttons[vpath[i + 1]].second)
                continue;
            res.push_back(vpath[i]);
        }

        cout << "TAK\n";
        cout << ssize(res) << '\n';
        for (int i : res)
            cout << i << ' ';
        cout << '\n';
        return 0;
    }

    for (int i = 1; i <= n; i++)
    {
        cnt_row[i] = ssize(rows[i]);
        cnt_col[i] = ssize(cols[i]);
        if (cnt_row[i] == 0 || cnt_col[i] == 0)
        {
            cout << "NIE\n";
            return 0;
        }
        if (cnt_row[i] == 1)
        {
            q.push(i);
        }
        if (cnt_col[i] == 1)
        {
            q.push(i + n);
        }
    }

    is_deleted.reset();

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        if (v <= n)
        {
            if (!cnt_row[v])
                continue;
            for (auto u : rows[v])
            {
                if (is_deleted[u.second])
                    continue;
                is_deleted[u.second] = 1;
                if (!parity_row[v])
                {
                    parity_row[v] = 1;
                    parity_col[u.first] = !parity_col[u.first];
                    res.push_back(u.second);
                }
                cnt_col[u.first]--;
                cnt_row[v] = 0;
                if (cnt_col[u.first] == 1)
                    q.push(u.first + n);
                break;
            }
        }
        else
        {
            v -= n;
            if (!cnt_col[v])
                continue;
            for (auto u : cols[v])
            {
                if (is_deleted[u.second])
                    continue;
                is_deleted[u.second] = 1;
                if (!parity_col[v])
                {
                    parity_col[v] = 1;
                    parity_row[u.first] = !parity_row[u.first];
                    res.push_back(u.second);
                }
                cnt_row[u.first]--;
                cnt_col[v] = 0;
                if (cnt_row[u.first] == 1)
                    q.push(u.first);
                break;
            }
        }
    }

    if ((int)parity_row.count() != n || (int)parity_col.count() != n)
    {
        cout << "NIE\n";
        return 0;
    }

    cout << "TAK\n";
    cout << ssize(res) << '\n';
    for (int i : res)
        cout << i << ' ';
    cout << '\n';

    return 0;
}
