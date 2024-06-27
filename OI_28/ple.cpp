// clang-format off
#include<bits/stdc++.h>
#include <climits>
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

constexpr int base = (1 << 19);
ll w[base + 7];
ll tree[base * 2 + 7];
ll lazy[base * 2 + 7];
ll ans[base];

inline void push(int v)
{
    tree[v * 2] += lazy[v];
    tree[v * 2 + 1] += lazy[v];
    lazy[v * 2] += lazy[v];
    lazy[v * 2 + 1] += lazy[v];
    lazy[v] = 0;
}

void add(int ql, int qr, ll value, int v, int l, int r)
{
    if (ql > r || qr < l)
        return;
    if (ql <= l && r <= qr)
    {
        tree[v] += value;
        lazy[v] += value;
        return;
    }
    push(v);
    int m = (l + r + 1) / 2;
    add(ql, qr, value, v * 2, l, m - 1);
    add(ql, qr, value, v * 2 + 1, m, r);
    tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
}

int find_positive()
{
    int v = 1;
    while (v < base)
    {
        push(v);
        if (tree[v * 2] > 0)
            v *= 2;
        else
            v = v * 2 + 1;
    }
    return v - base;
}

#ifdef DEBUG
void print_tree()
{
    int a;
    for (int i = base; i < base * 2; i++)
    {
        a = tree[i];
        for (int j = i / 2; j; j /= 2)
            a -= lazy[j];
        cout << a << ' ';
    }
    cout << '\n';
    for (int s = 1; s <= base; s *= 2)
    {
        for (int i = s; i < s * 2; i++)
            cout << tree[i] << ' ';
        cout << '\n';
    }

    for (int s = 1; s <= base; s *= 2)
    {
        for (int i = s; i < s * 2; i++)
            cout << lazy[i] << ' ';
        cout << '\n';
    }
}
#else
void print_tree()
{
}
#endif

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, p;
    long long s = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
        s += w[i];
    }

    ans[n] = s;
    for (int i = 0; i < n; i++)
    {
        s -= w[i];
        tree[base + i] = w[i] - s;
    }

    for (int i = base - 1; i; i--)
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);

    print_tree();

    for (int i = n - 1; i; i--)
    {
        p = find_positive();
        add(0, p - 1, w[p], 1, 0, base - 1);
        add(p, p, LONG_LONG_MIN / 64, 1, 0, base - 1);
        ans[i] = ans[i + 1] - w[p];
        debug(p);
        print_tree();
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';

    cout << '\n';

    return 0;
}
