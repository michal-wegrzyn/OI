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

map<int, int> av;
bitset<2500007> dp;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, a, s = 0, c, mx = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        av[a]++;
        s += a;
        mx = max(mx, a);
    }

    av[mx]--;
    s -= mx;

    for (int i = 1; i <= s; i++)
    {
        if (!av[i])
            continue;
        c = (av[i] - 1) / 2;
        av[i] -= c * 2;
        av[i * 2] += c;
    }

    dp[0] = 1;
    for (auto i : av)
    {
        for (int j = 0; j < i.second; j++)
            dp |= (dp << i.first);
    }

    for (int i = s / 2; i >= 0; i--)
    {
        if (!dp[i])
            continue;
        cout << i + mx << '\n';
        return 0;
    }

    return 0;
}
