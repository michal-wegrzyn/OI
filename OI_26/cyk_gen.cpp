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

#define MAX_N 2000

bitset<MAX_N + 7> occ;
vector<int> ans;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, cnt = 0, best_i, best_cnt;

    while (occ.count() != MAX_N)
    {
        best_i = -1;
        best_cnt = -1;
        for (int i = 1; i <= 100; i += i / 10 + 1)
        {
            a = i;
            cnt = (occ[a] == 0);
            for (int j = ssize(ans) - 1; j >= 0; j--)
            {
                a += ans[j];
                if (a <= 2000)
                    cnt += (occ[a] == 0);
            }
            if (cnt > best_cnt)
            {
                best_cnt = cnt;
                best_i = i;
            }
        }
        a = best_i;
        occ[a] = 1;
        for (int j = ssize(ans) - 1; j >= 0; j--)
        {
            a += ans[j];
            if (a <= 2000)
                occ[a] = 1;
        }
        ans.push_back(best_i);
    }

    cout << ans << '\n';
    cout << ssize(ans) << '\n';

    return 0;
}
