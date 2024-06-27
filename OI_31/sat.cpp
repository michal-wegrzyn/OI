// clang-format off
#include<bits/stdc++.h>
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

#define P 54924024384186589LL

ll pow2_P[1007];
int ceil_log2[1007];

bitset<1007> graph1[1007];
bitset<1007> graph2[1007];
bitset<1007> res[2007];
ll hsh1[1007];
ll hsh2[1007];

bitset<1007> skip_row;
vector<vector<int>> v1;
vector<vector<int>> v2;
vector<int> same_rows;

vector<int> empty1;
vector<int> empty2;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ceil_log2[1] = 0;
    for (int i = 0; i < 10; i++)
        ceil_log2[(1 << i) + 1] = i + 1;

    for (int i = 2; i <= 1005; i++)
    {
        if (!ceil_log2[i])
            ceil_log2[i] = ceil_log2[i - 1];
    }

    pow2_P[0] = 1;
    for (int i = 1; i <= 1005; i++)
    {
        pow2_P[i] = pow2_P[i - 1] * 2;
        if (pow2_P[i] >= P)
            pow2_P[i] -= P;
    }

    int n, p, M, a, b, num;
    ll hsh;

    cin >> n >> p >> M;

    for (int i = 0; i < p; i++)
    {
        cin >> a >> b;
        b -= n + 1;
        a--;
        graph1[a][b] = 1;
        graph2[b][a] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        hsh = 0LL;
        for (int j = 0; j < n; j++)
            hsh = (hsh + pow2_P[j] * graph1[i][j]) % P;
        hsh1[i] = hsh;
    }

    for (int i = 0; i < n; i++)
    {
        if (skip_row[i])
            continue;
        if (graph1[i].count() == 0)
        {
            empty1.push_back(i);
            continue;
        }
        same_rows.clear();
        same_rows.push_back(i);
        for (int j = i + 1; j < n; j++)
        {
            if (hsh1[i] != hsh1[j])
                continue;
            if (graph1[i] != graph1[j])
                continue;
            same_rows.push_back(j);
            skip_row[j] = 1;
        }
        v1.push_back(same_rows);
    }

    skip_row.reset();

    for (int i = 0; i < n; i++)
    {
        hsh = 0LL;
        for (int j = 0; j < n; j++)
            hsh = (hsh + pow2_P[j] * graph2[i][j]) % P;
        hsh2[i] = hsh;
    }

    for (int i = 0; i < n; i++)
    {
        if (skip_row[i])
            continue;
        if (graph2[i].count() == 0)
        {
            empty2.push_back(i);
            continue;
        }
        same_rows.clear();
        same_rows.push_back(i);
        for (int j = i + 1; j < n; j++)
        {
            if (hsh2[i] != hsh2[j])
                continue;
            if (graph2[i] != graph2[j])
                continue;
            same_rows.push_back(j);
            skip_row[j] = 1;
        }
        v2.push_back(same_rows);
    }

    skip_row.reset();

    int c1 = n - ssize(v1);
    int c2 = n - ssize(v2);

    int m1 = ssize(empty1), m2 = ssize(empty2);
    for (auto i : v1)
        m1 = max(m1, ssize(i));
    for (auto i : v2)
        m2 = max(m2, ssize(i));

    int option = 1;
    a = n - c1 - empty1.size() + ceil_log2[m1] + ceil_log2[m2] + (m1 == 1 || m2 == 1);
    b = n - c2 - empty2.size() + ceil_log2[m1] + ceil_log2[m2] + (m1 == 1 || m2 == 1);
    if (b < a)
        option = 2;

    a = min(a, b);

    if (option == 1)
    {
        b = 0;
        for (auto i : v1)
        {
            for (int sat : i)
                res[sat][b] = 1;
            for (int sat = 0; sat < n; sat++)
            {
                if (graph1[i[0]][sat])
                    res[sat + n][b] = 1;
            }
            b++;
        }
    }

    else
    {
        b = 0;
        for (auto i : v2)
        {
            for (int sat : i)
                res[sat + n][b] = 1;
            for (int sat = 0; sat < n; sat++)
            {
                if (graph2[i[0]][sat])
                    res[sat][b] = 1;
            }
            b++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        hsh = 0LL;
        for (int j = 0; j < b; j++)
            hsh = (hsh + pow2_P[j] * res[i][j]) % P;
        hsh1[i] = hsh;
    }

    m1 = 0;
    v1.clear();

    for (int i = 0; i < n; i++)
    {
        if (skip_row[i])
            continue;
        same_rows.clear();
        same_rows.push_back(i);
        for (int j = i + 1; j < n; j++)
        {
            if (hsh1[i] != hsh1[j])
                continue;
            if (res[i] != res[j])
                continue;
            same_rows.push_back(j);
            skip_row[j] = 1;
        }
        m1 = max(m1, ssize(same_rows));
        v1.push_back(same_rows);
    }

    skip_row.reset();

    for (int i = 0; i < n; i++)
    {
        hsh = 0LL;
        for (int j = 0; j < b; j++)
            hsh = (hsh + pow2_P[j] * res[i + n][j]) % P;
        hsh2[i] = hsh;
    }

    m2 = 0;
    v2.clear();

    for (int i = 0; i < n; i++)
    {
        if (skip_row[i])
            continue;
        same_rows.clear();
        same_rows.push_back(i);
        for (int j = i + 1; j < n; j++)
        {
            if (hsh2[i] != hsh2[j])
                continue;
            if (res[i + n] != res[j + n])
                continue;
            same_rows.push_back(j);
            skip_row[j] = 1;
        }
        m2 = max(m2, ssize(same_rows));
        v2.push_back(same_rows);
    }

    skip_row.reset();

    m1 = ceil_log2[m1];
    m2 = ceil_log2[m2];

    for (auto i : v1)
    {
        for (int sat = 0; sat < ssize(i); sat++)
        {
            num = sat;
            for (int pos = 0; pos < m1; pos++)
            {
                res[i[sat]][b + pos] = (num & 1);
                num /= 2;
            }
        }
    }

    for (auto i : v2)
    {
        for (int sat = 0; sat < ssize(i); sat++)
        {
            num = sat;
            for (int pos = 0; pos < m2; pos++)
            {
                res[i[sat] + n][b + m1 + pos] = (num & 1);
                num /= 2;
            }
        }
    }

    a = b + m1 + m2 + (m1 == 0 || m2 == 0);
    cout << a << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < a; j++)
            cout << (res[i][j] ? 'C' : 'A');
        cout << '\n';
    }

    for (int i = n; i < n * 2; i++)
    {
        for (int j = 0; j < a; j++)
            cout << (res[i][j] ? 'C' : 'B');
        cout << '\n';
    }

    return 0;
}
