// clang-format off
#include<bits/stdc++.h>
#include <iterator>
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

set<pair<pair<ll, ll>, ll>> distances;
vector<pair<ll, int>> queries;
ll res[100007];
pair<pair<ll, ll>, ll> curr;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ll mult = (1 << 3);
    ll mult = (1 << 30);
    ll n, X, z, x, p, k, g;
    cin >> n >> X >> z >> p;

    for (int i = 1; i < n; i++)
    {
        cin >> x;
        x *= mult;
        distances.insert({{p - x, p}, 1});
        p = x;
    }

    for (int i = 0; i < z; i++)
    {
        cin >> k;
        queries.push_back({k, i});
    }

    sort(queries.begin(), queries.end());
    reverse(queries.begin(), queries.end());
    debug(distances);

    ll ttime = 1;
    while (!queries.empty())
    {
        curr = *distances.begin();
        distances.erase(curr);
        curr.first.first = -curr.first.first;
        k = ttime + curr.second;
        debug(ttime, k, curr, queries);
        while (!queries.empty() && queries.back().first < k)
        {
            res[queries.back().second] =
                curr.first.second + curr.first.first / 2 + curr.first.first * (queries.back().first - ttime);
            debug(queries.back(), res[queries.back().second]);
            queries.pop_back();
        }
        ttime = k;
        distances.insert({{-curr.first.first / 2, curr.first.second}, curr.second * 2});
        debug(distances);
        debug();
    }

    for (int i = 0; i < z; i++)
    {
        g = __gcd(res[i], mult);
        cout << res[i] / g << '/' << mult / g << '\n';
    }

    return 0;
}
