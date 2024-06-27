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

vector<int> desks[1003];
int dp1[3003][3003];
int dp2[3003][2];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q, d, l, w, k, p, nn, s = 0, a;
    cin >> n >> q >> d >> l >> w;
    for (int i = 0; i < n; i++)
    {
        cin >> k >> p;
        desks[k].push_back(p);
    }

    for (int i = 1; i <= l; i++)
    {
        sort(desks[i].begin(), desks[i].end());
        desks[i].push_back(w);
    }

    for (int desk = 1; desk <= l; desk++)
    {
        nn = desks[desk].size() - 1;
        for (int i = 0; i <= nn; i++)
            dp1[i][0] = desks[desk][i] / d - i;
        for (int i = 1; i <= nn; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                for (int ii = j - 1; ii < i; ii++)
                {
                    dp1[i][j] = max(dp1[i][j], dp1[ii][j - 1] + (desks[desk][i] - desks[desk][ii]) / d - i + ii);
                }
            }
        }
        for (int i = 0; i <= s; i++)
        {
            for (int j = 0; j <= nn; j++)
            {
                dp2[i + j][1] = max(dp2[i + j][1], dp2[i][0] + dp1[nn][j]);
            }
        }
        s += nn;
        for (int i = 0; i <= s; i++)
        {
            dp2[i][0] = dp2[i][1];
            dp2[i][1] = 0;
        }
    }

    int ans;

    while (q--)
    {
        cin >> a;
        if (dp2[0][0] < a)
        {
            cout << -1 << '\n';
            continue;
        }
        ans = 0;
        for (int i = (1 << 11); i > 0; i /= 2)
        {
            ans += i;
            if (ans > n)
            {
                ans -= i;
                continue;
            }
            if (dp2[ans][0] < a)
                ans -= i;
        }
        cout << n - ans << '\n';
    }

    return 0;
}
