#include <iostream>
#include <algorithm>
using namespace std;

constexpr int base = 1 << 19;
long long tree_max[(base<<1)+7];
long long info_for_children[(base<<1)+7];
long long tree[(base<<1)+7];

int qstart, qend;
long long value;
long long zero;

void add_max(int v, int v_start, int v_end){
    if(v_end<qstart || qend<v_start) return;
    else if(qstart <= v_start && v_end <= qend){
        tree_max[v] += value;
        info_for_children[v] += value;
    }
    else{
        tree_max[v<<1] += info_for_children[v];
        tree_max[(v<<1)+1] += info_for_children[v];
        info_for_children[v<<1] += info_for_children[v];
        info_for_children[(v<<1)+1] += info_for_children[v];
        info_for_children[v] = zero;
        add_max(v<<1, v_start, (v_start+v_end)>>1);
        add_max((v<<1)+1, ((v_start+v_end)>>1)+1, v_end);
        tree_max[v] = max(tree_max[v<<1], tree_max[(v<<1)+1]);
    }
}

void add(int start, int end){
    start = start - 1 + base;
    end = end + 1 + base;
    while(start/2 != end/2){
        if(!(start&1)) tree[start+1] += value;
        if(end&1) tree[end-1] += value;
        start /= 2;
        end /= 2;
    }
}

int query(int v){
    long long result = 0;
    v = v+base;
    while(v){
        result += tree[v];
        v /= 2;
    }
    return result;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q, p, start, end, middle, count;
    long long x, y;
    char c;
    cin >> n >> q;
    for(int i=0; i<n; i++){
        cin >> p;
        tree[i+base] = p;
    }
    sort(tree+base, tree+base+n);
    for(int i=0; i<n; i++) tree_max[base+i] = tree[base+i] + n-i;
    for(int i=base-1; i>0; i--) tree_max[i] = max(tree_max[i<<1], tree_max[(i<<1)+1]);
    for(int i=0; i<q; i++){
        cin >> c;
        if(c=='Z'){
            if(query(0)+n >= tree_max[1]){
                cout << n << '\n';
                continue;
            }
            start = 1;
            end = n;
            middle = (n+1)>>1;
            count = 0;
            while(start < end){
                if(query(middle-1)+n < tree_max[1] && query(middle)+n >= tree_max[1]) break;
                if(query(middle-1)+n >= tree_max[1]) end = middle;
                else start = middle+1;
                middle = (start+end)>>1;
                count++;
                if(count==25){cout << "!!!"; return 0;}
            }
            cout << n-middle << '\n';
        }
        else{
            cin >> x >> y;
            if(c=='B'){
                if(x<tree_max[1]-n) continue;
                if(query(0) >= x){
                    qstart = 0; qend = n-1; value = y;
                    add(0, n-1);
                    add_max(1, 0, base-1);
                    continue;
                }
                if(query(n-1) < x) continue;
                start = 1;
                end = n;
                middle = (n+1)>>1;
                count = 0;
                while(start < end){
                    if(query(middle-1) < x && query(middle) >= x) break;
                    if(query(middle-1) >= x) end = middle;
                    else start = middle+1;
                    middle = (start+end)>>1;
                    count++;
                    if(count==25){cout << "!!!"; return 0;}
                }
                qstart = middle; qend = n-1; value = y;
                add(middle, n-1);
                add_max(1, 0, base-1);
            }
            if(c=='K'){
                if(x<tree_max[1]-n) continue;
                if(query(n-1) <= x){
                    qstart = 0; qend = n-1; value = -y;
                    add(0, n-1);
                    add_max(1, 0, base-1);
                    continue;
                }
                if(query(0) > x) continue;
                x++;
                start = 1;
                end = n;
                middle = n>>1;
                count = 0;
                while(start < end){
                    if(query(middle-1) < x && query(middle) >= x) break;
                    if(query(middle-1) >= x) end = middle;
                    else start = middle+1;
                    middle = (start+end)>>1;
                    count++;
                    if(count==25){cout << "!!!"; return 0;}
                }
                qstart = 0; qend = middle-1; value = -y;
                add(0, middle-1);
                add_max(1, 0, base-1);
            }
        }
    }
    return 0;
}