#include <iostream>
using namespace std;

struct dane{
    long long suma;
    long long max_prefix;
    long long max_sufix;
    long long max_podciag;
};

constexpr int base = 1 << 18;
dane tree[2*base+7];

void add(int v, int value){
    v = v+base;
    tree[v].suma += (long long)value;
    v /= 2;
    while(v){
        tree[v].suma += (long long) value;
        tree[v].max_prefix = max(tree[2*v].max_prefix, tree[2*v].suma+tree[2*v+1].max_prefix);
        tree[v].max_sufix = max(tree[2*v+1].max_sufix, tree[2*v+1].suma+tree[2*v].max_sufix);
        tree[v].max_podciag = max(max(tree[2*v].max_podciag, tree[2*v+1].max_podciag), tree[2*v].max_sufix+tree[2*v+1].max_prefix);
        v /= 2;
    }
}

/*int query(int start, int end){
    int result = 0;
    start = start - 1 + base;
    end = end + 1 + base;
    while(start/2 != end/2){
        if(!(start&1)) result += tree[start+1];
        if(end&1) result += tree[end-1];
        start /= 2;
        end /= 2;
    }
    return result;
}*/

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, k, d, num1, num2;
    cin >> n >> m >> k >> d;
    for(int i=base+1; i<=base+n; i++) tree[i].suma = -k;
    for(int i=base-1; i>0; i--) tree[i].suma = tree[i*2].suma+tree[i*2+1].suma;
    for(int i=0; i<m; i++){
        cin >> num1 >> num2;
        add(num1, num2);
        cout << (tree[1].max_podciag>(long long)d*(long long)k?"NIE\n":"TAK\n");
    }
    
    return 0;
}