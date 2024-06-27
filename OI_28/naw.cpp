#include <iostream>
#include <utility>
using namespace std;

constexpr int base = 1 << 20;  // 20
pair<int,int> tree[2*base+7];
bool odp[1000007];
int perm[1000007];

void add(int v){
    v = v+base;
    tree[v].first -= 1;
    tree[v].second = 0;
    v /= 2;
    while(v){
        tree[v].first -= 1;
        tree[v].second = max(tree[v<<1].second, tree[v<<1].first+tree[(v<<1)+1].second);
        v /= 2;
    }
}

int query(int end){
    if(end == -1) return -1;
    end = end + 1 + base;
    int result = tree[end-1].second;
    end /= 2;
    while(end/2){
        if(end&1) result = max(tree[end-1].second, tree[end-1].first+result);
        end /= 2;
    }
    return result;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, num, m = 0, open_brackets=0, closed_brackets=0;
    cin >> n;
    if(n % 2 == 1){ cout << "NIE\n"; return 0;}
    for(int i=base; i<base+n; i+=2) tree[i] = {1,1};
    for(int i=base-1; i>0; i--) tree[i] = {tree[i<<1].first+tree[(i<<1)+1].first, max(tree[i<<1].second, tree[i<<1].first+tree[(i<<1)+1].second)};
    //for(int i=1; i<2*base; i++) cout << tree[i].first << ' ' << tree[i].second << ' ';
    //cout << query(2) << ' ' << query(3) << ' ' << query(4) << '\n';
    for(int i=0; i<n; i++) cin >> perm[i];
    for(int i=0; i<n; i++){
        num = perm[i] - 1;
        //for(int i=1; i<2*base; i++) cout << tree[i].first << ' ' << tree[i].second << ' ';
        if(query(num-1) < n/2 - open_brackets && open_brackets < n/2){
            //cout << query(num-2) << '<' << n/2-open_brackets << '\n'; 
            open_brackets++; m++;
            odp[i] = true;
            add(num);
        }
        else if(m>0 && closed_brackets < n/2){
            closed_brackets++; m--;
        }
        else { cout << "NIE\n"; return 0;}
    }
    for(int i=0; i<n; i++) cout << (odp[i]?'(':')');
    
    return 0;
}