// clang-format off
#include<bits/stdc++.h>
#include <climits>
#include <queue>
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

#define LOG 3

vector<pair<ll, int>> graph[100003];
vector<pair<ll, int>> cgraph[100003];
vector<int> restaurants_t[100003];
set<int> interesting[100003];
vector<int> v_int;
int jumps[100003][LOG];
int lvl[100003];
ll dist[100003];
ll min_dist[100003];
ll mind[100003][LOG];
int preorder[100003];
int preorder_counter;
vector<pair<pair<int, int>, int>> queries[100003];
priority_queue<pair<ll, int>> pq;
ll answers[100003];

void init_lca(int v, int p)
{
    jumps[v][0] = p;
    lvl[v] = lvl[p] + 1;
    preorder_counter++;
    preorder[v] = preorder_counter;
    for (auto u : graph[v])
    {
        if (u.second == p)
            continue;
        dist[u.second] = dist[v] + u.first;
        init_lca(u.second, v);
    }
}

int lca(int a, int b)
{
    if (lvl[a] < lvl[b])
        swap(a, b);
    for (int j = LOG - 1; j >= 0; j--)
    {
        if (lvl[a] - (1 << j) >= lvl[b])
            a = jumps[a][j];
    }

    if (a == b)
        return a;

    for (int j = LOG - 1; j >= 0; j--)
    {
        if (jumps[a][j] != jumps[b][j])
        {
            a = jumps[a][j];
            b = jumps[b][j];
        }
    }
    return jumps[a][0];
}

ll get_mind(int a, int b)
{
    ll ans = min_dist[a];
    if (lvl[a] < lvl[b])
        swap(a, b);
    for (int j = LOG - 1; j >= 0; j--)
    {
        if (lvl[a] - (1 << j) >= lvl[b])
        {
            a = jumps[a][j];
            ans = min(ans, mind[a][j]);
        }
    }

    if (a == b)
        return ans;

    for (int j = LOG - 1; j >= 0; j--)
    {
        if (jumps[a][j] != jumps[b][j])
        {
            ans = min(ans, mind[a][j]);
            ans = min(ans, mind[b][j]);
            a = jumps[a][j];
            b = jumps[b][j];
        }
    }
    return min(ans, min_dist[jumps[a][0]]);
}

ll get_dist(int a, int b)
{
    return dist[a] + dist[b] - dist[lca(a, b)] * 2;
}

bool sort_by_preorder(int a, int b)
{
    return preorder[a] < preorder[b];
}

int main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    int n, r, a, b, q, t;
    ll l;
    pair<ll, int> tp;
    cin >> n >> r;
    for (int i = 1; i <= n; i++)
    {
        cin >> t;
        restaurants_t[t].push_back(i);
        interesting[t].insert(i);
    }

    for (int i = 1; i < n; i++)
    {
        cin >> a >> b >> l;
        graph[a].push_back({l, b});
        graph[b].push_back({l, a});
    }

    init_lca(1, 1);
    for (int j = 1; j < LOG; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            jumps[i][j] = jumps[jumps[i][j - 1]][j - 1];
        }
    }

    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> a >> b >> t;
        queries[t].push_back({{a, b}, i});
        interesting[t].insert(a);
        interesting[t].insert(b);
    }

    // for (int i = 1; i <= n; i++)
    //     cout << dist[i] << ' ';
    // cout << '\n';
    // for (int j = 0; j < LOG; j++)
    // {
    //     for (int i = 1; i <= n; i++)
    //         cout << jumps[i][j] << ' ';
    //     cout << '\n';
    // }

    for (t = 1; t <= r; t++)
    {
        if (ssize(queries[t]) == 0)
            continue;
        if (ssize(restaurants_t[t]) == 0)
        {
            for (auto i : queries[t])
                answers[i.second] = -1;
            continue;
        }
        interesting[t].insert(1);
        for (int i : interesting[t])
            v_int.push_back(i);
        sort(v_int.begin(), v_int.end(), sort_by_preorder);
        for (int i = 1; i < ssize(v_int); i++)
            interesting[t].insert(lca(v_int[i - 1], v_int[i]));
        v_int.clear();
        for (int i : interesting[t])
            v_int.push_back(i);
        sort(v_int.begin(), v_int.end(), sort_by_preorder);
        for (int i = 1; i < ssize(v_int); i++)
        {
            a = lca(v_int[i - 1], v_int[i]);
            cgraph[a].push_back({get_dist(a, v_int[i]), v_int[i]});
            cgraph[v_int[i]].push_back({get_dist(a, v_int[i]), a});
        }
        debug(t);
        for (int i : v_int)
            debug(i, cgraph[i]);
        for (int i : v_int)
            min_dist[i] = LONG_LONG_MAX / 4;
        for (int i : restaurants_t[t])
        {
            min_dist[i] = 0;
            pq.push({0, i});
        }

        while (!pq.empty())
        {
            tp = pq.top();
            pq.pop();
            tp.first *= -1;
            if (tp.first > min_dist[tp.second])
                continue;
            for (auto u : cgraph[tp.second])
            {
                if (min_dist[u.second] <= tp.first + u.first)
                    continue;
                min_dist[u.second] = tp.first + u.first;
                pq.push({-min_dist[u.second], u.second});
            }
        }

        debug(restaurants_t[t]);
        debug(queries[t]);
        debug(v_int);

        for (int i : v_int)
            mind[i][0] = min(min_dist[i], min_dist[jumps[i][0]]);

        for (int i : v_int)
            cout << mind[i][0] << ' ';
        cout << '\n';

        for (int i : v_int)
            cout << min_dist[i] << ' ';
        cout << '\n';

        for (int j = 1; j < LOG; j++)
        {
            for (int i = 1; i <= n; i++)
            {
                mind[i][j] = min(mind[i][j - 1], mind[jumps[i][j - 1]][j - 1]);
                cout << mind[i][j] << ' ';
            }
            cout << '\n';
        }

        for (auto i : queries[t])
        {
            answers[i.second] = get_dist(i.first.first, i.first.second) + get_mind(i.first.first, i.first.second) * 2;
        }

        for (int i : v_int)
            cgraph[i].clear();
        v_int.clear();
    }

    for (int i = 0; i < q; i++)
        cout << answers[i] << ' ';

    return 0;
}
