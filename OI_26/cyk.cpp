// clang-format off
#include<bits/stdc++.h>
#include <climits>
#include "cyklib.hpp"
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

ll st;
ll get_value(int x)
{
    ll v = circular_shift(x);
    if (v < st)
        return v + LONG_LONG_MAX / 4;
    return v;
}

map<ll, ll> q;
// vector<ll> test;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    ll t = 0, a, p, step = 1;
    // cin >> n;
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> a;
    //     test.push_back(a);
    //     init(test);
    // }
    st = circular_shift(0);
    p = 0;
    a = get_value(1);
    t++;
    q[a] = t;
    if (a == st)
    {
        give_answer(1);
        return 0;
    }
    while (p < a)
    {
        p = a;
        t += step;
        a = get_value(step);
        q[a] = t;
        step *= 2;
    }

    debug(t, a);

    if (a == st)
    {
        give_answer(t);
        return 0;
    }

    step /= 2;

    int mn = step, mx = step * 2, x, cnt;
    ll A, B, C = a;
    while (mx - mn > 2)
    {
        step /= 2;
        x = mn + step;
        debug(step, mn, x, mx);
        A = C;
        B = get_value(x / 2);
        C = get_value(x / 2);
        if (A == C)
        {
            give_answer(x);
            return 0;
        }
        cnt = (int)(A > B) + (B > C) + (A > C);
        debug(A, B, C, cnt);
        if (cnt % 2)
            mx = x;
        else
            mn = x;
    }

    give_answer(mn + 1);

    return 0;
}
