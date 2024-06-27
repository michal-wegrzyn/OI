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

struct lect
{
    int st;
    int en;
    int id;
};

lect lectures[500007];
vector<int> res1;
vector<pair<int, int>> res2;

bool sort_lect(lect l1, lect l2)
{
    if (l1.en != l2.en)
        return l1.en < l2.en;
    if (l1.st != l2.st)
        return l1.st > l2.st;
    return l1.id < l2.id;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, a, b, min_st;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a >> b;
        lectures[i] = {a, b, i};
    }

    sort(lectures + 1, lectures + n + 1, sort_lect);
    res1.push_back(1);
    min_st = lectures[1].en;
    for (int i = 2; i <= n; i++)
    {
        if (lectures[i].st < min_st)
            continue;
        res1.push_back(i);
        min_st = lectures[i].en;
    }

    res2.push_back({1, 2});
    while (true)
    {
        min_st = max(lectures[res2.back().first].en, lectures[res2.back().second].en);
        a = -1;
        for (int i = max(res2.back().first, res2.back().second) + 1; i <= n; i++)
        {
            if (lectures[i].st < min_st)
                continue;
            a = i;
            break;
        }
        if (a == -1)
            break;

        min_st = lectures[res2.back().first].en;
        b = -1;
        for (int i = res2.back().first + 1; i <= n; i++)
        {
            if (i == res2.back().second)
                continue;
            if (i == a)
                continue;
            if (lectures[i].st < min_st)
                continue;
            b = i;
            break;
        }
        if (b == -1)
            break;
        res2.push_back({a, b});
    }

    if (ssize(res1) - 1 >= ssize(res2))
    {
        a = lectures[res1.back()].id;
        res1.pop_back();
        cout << ssize(res1) << '\n';
        for (int i : res1)
            cout << lectures[i].id << ' ' << a << '\n';
    }
    else
    {
        cout << ssize(res2) << '\n';
        for (auto i : res2)
            cout << lectures[i.first].id << ' ' << lectures[i.second].id << '\n';
    }

    return 0;
}
