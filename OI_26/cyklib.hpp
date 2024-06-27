#include <iostream>
#include <vector>
using namespace std;

vector<long long> nums;
int pos;

void init(vector<long long> nm)
{
    nums = nm;
    pos = 0;
}

long long circular_shift(int n)
{
    pos = (pos + n) % nums.size();
    cout << "shift " << n << ' ' << pos << ' ' << nums[pos] << '\n';
    return nums[pos];
}

void give_answer(int n)
{
    cout << "!ans -> " << n << ' ' << (n == (int)nums.size()) << '\n';
    return;
}