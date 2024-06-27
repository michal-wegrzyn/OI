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

ll pow31_P[10000007];
map<pair<ll, char>, int> m_cnt;
map<ll, pair<char, int>> m_cnt2;
map<ll, int> m_occ;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    pow31_P[0] = 1;
    for (int i = 1; i <= 1000005; i++)
        pow31_P[i] = (pow31_P[i - 1] * 31) % P;

    ll n, k, a, b;
    cin >> n >> k >> a >> b;
    a--;
    b--;
    string s;
    cin >> s;

    ll hsh = 0LL;
    for (int i = 0; i < k; i++)
        hsh = (hsh * 31 + s[i] - 'a' + 1) % P;
    for (int i = k; i < n; i++)
    {
        m_cnt[{hsh, s[i]}] += 1;
        hsh = (hsh * 31 + s[i] - 'a' + 1 - (s[i - k] - 'a' + 1) * pow31_P[k]) % P;
        if (hsh < 0)
            hsh += P;
    }

    for (auto i : m_cnt)
    {
        if (m_cnt2[i.first.first].second < i.second + (m_cnt2[i.first.first].first > i.first.second))
            m_cnt2[i.first.first] = {i.first.second, i.second};
    }

    int st = -1;

    while (true)
    {
        if (m_occ[hsh])
        {
            st = m_occ[hsh];
            break;
        }
        if (ssize(s) > b)
            break;
        m_occ[hsh] = s.size();
        s.push_back(max(m_cnt2[hsh].first, 'a'));
        hsh = (hsh * 31 + s.back() - 'a' + 1 - (s[s.size() - 1 - k] - 'a' + 1) * pow31_P[k]) % P;
        if (hsh < 0)
            hsh += P;
    }

    for (ll i = a; i <= b; i++)
    {
        if (i < ssize(s))
            cout << s[i];
        else
            cout << s[(i - st) % (s.size() - st) + st];
    }

    return 0;
}
