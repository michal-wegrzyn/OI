// clang-format off
#include<bits/stdc++.h>
#include <vector>
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

char board[1503][1503];

typedef pair<int, pair<int, int>> hr;
typedef pair<pair<int, int>, int> vr;

vector<hr> h_runway;
vector<vr> v_runway;

bool compare_hr(hr hr1, hr hr2)
{
    return (hr1.second.second - hr1.second.first > hr2.second.second - hr2.second.first);
}

bool compare_vr(vr vr1, vr vr2)
{
    return (vr1.first.second - vr1.first.first > vr2.first.second - vr2.first.first);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, st;
    char ch;

    hr hr1, hr2, hr_curr;
    vr vr1, vr2, vr_curr;

    cin >> n >> m;
    for (int i = 0; i <= n + 1; i++)
        board[0][i] = 'X';
    for (int i = 1; i <= n; i++)
    {
        board[i][0] = 'X';
        for (int j = 1; j <= n; j++)
        {
            cin >> ch;
            board[i][j] = ch;
        }
        board[i][n + 1] = 'X';
    }
    for (int i = 0; i <= n + 1; i++)
        board[n + 1][i] = 'X';

    for (int r = 1; r <= n; r++)
    {
        st = -1;
        hr1 = {-1, {0, -1}};
        hr2 = {-1, {0, -1}};
        for (int c = 1; c <= n + 1; c++)
        {
            if (board[r][c] == '.')
            {
                if (st == -1)
                    st = c;
                continue;
            }
            if (board[r][c] == 'X' && st == -1)
                continue;
            hr_curr = {r, {st, c - 1}};
            if (compare_hr(hr_curr, hr2))
                hr2 = hr_curr;
            if (compare_hr(hr2, hr1))
                swap(hr1, hr2);
            st = -1;
        }
        if (hr1.first != -1)
            h_runway.push_back(hr1);
        if (hr2.first != -1)
            h_runway.push_back(hr2);
    }

    sort(h_runway.begin(), h_runway.end(), compare_hr);

    for (int c = 1; c <= n; c++)
    {
        st = -1;
        vr1 = {{0, -1}, -1};
        vr2 = {{0, -1}, -1};
        for (int r = 1; r <= n + 1; r++)
        {
            if (board[r][c] == '.')
            {
                if (st == -1)
                    st = r;
                continue;
            }
            if (board[r][c] == 'X' && st == -1)
                continue;
            vr_curr = {{st, r - 1}, c};
            if (compare_vr(vr_curr, vr2))
                vr2 = vr_curr;
            if (compare_vr(vr2, vr1))
                swap(vr1, vr2);
            st = -1;
        }
        if (vr1.second != -1)
            v_runway.push_back(vr1);
        if (vr2.second != -1)
            v_runway.push_back(vr2);
    }

    sort(v_runway.begin(), v_runway.end(), compare_vr);

    int h, v, res = 0;

    if (h_runway.size() == 0)
    {
        cout << 0 << '\n';
        return 0;
    }

    if (m == 1)
    {
        hr_curr = h_runway[0];
        h = hr_curr.second.second - hr_curr.second.first + 1;

        vr_curr = v_runway[0];
        v = vr_curr.first.second - vr_curr.first.first + 1;
        cout << max(h, v) << '\n';
        return 0;
    }

    if (h_runway.size() == 1 && v_runway.size() == 1)
    {
        cout << 0 << '\n';
        return 0;
    }

    hr_curr = h_runway[0];
    h = hr_curr.second.second - hr_curr.second.first + 1;
    res = max(res, h / 2);

    if (h_runway.size() > 1)
    {
        hr_curr = h_runway[1];
        h = hr_curr.second.second - hr_curr.second.first + 1;
        res = max(res, h);
    }

    vr_curr = v_runway[0];
    v = vr_curr.first.second - vr_curr.first.first + 1;
    res = max(res, v / 2);

    if (v_runway.size() > 1)
    {
        vr_curr = v_runway[1];
        v = vr_curr.first.second - vr_curr.first.first + 1;
        res = max(res, v);
    }

    for (hr chr : h_runway)
    {
        if (chr.second.second - chr.second.first + 1 <= res)
            break;
        for (vr cvr : v_runway)
        {
            if (cvr.first.second - cvr.first.first + 1 <= res)
                break;
            if (cvr.first.first <= chr.first && chr.first <= cvr.first.second && chr.second.first <= cvr.second &&
                cvr.second <= chr.second.second)
            {
                h = max(cvr.second - chr.second.first, chr.second.second - cvr.second);
                v = max(chr.first - cvr.first.first, cvr.first.second - chr.first);
                res = max(res, max(min(h, cvr.first.second - cvr.first.first + 1),
                                   min(v, chr.second.second - chr.second.first + 1)));
                continue;
            }

            res = max(res, min(cvr.first.second - cvr.first.first + 1, chr.second.second - chr.second.first + 1));
        }
    }

    cout << res << '\n';

    return 0;
}
