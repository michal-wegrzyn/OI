#include <iostream>
#include <utility>
using namespace std;

constexpr int base = 1 << 3; // 19
long long tree[(base<<1)+7];
pair<long long,long long> info_for_children[(base<<1)+7];
pair<int, int> infos[300007];

int qstart, qend, value1, value2, x, s, a;

long long valueInPos(int pos){
    long long res = (long long)s-(long long)a*(long long)(abs(x-pos));
    //if(res<(long long)0) return (long long)0;
    return res;
}

void add(int v, int v_start, int v_end){
    if(v_end<qstart || qend<v_start) return;
    else if(qstart <= v_start && v_end <= qend){
        tree[v] += (long long)(v_end-v_start+1)*(valueInPos(v_start)+valueInPos(v_end))/2;
        info_for_children[v].first += valueInPos(v_start);
        info_for_children[v].second += a;
    }
    else{
        int mid = ((v_start+v_end)>>1)+1;
        info_for_children[v<<1].first += info_for_children[v].first;
        info_for_children[v<<1].second += info_for_children[v].second;
        info_for_children[(v<<1)+1].first += info_for_children[v].first+a*(v_end-v_start+1)/2;
        info_for_children[(v<<1)+1].second += a ;
        tree[v<<1] += (info_for_children[v].first*2+(mid-1-v_start)*info_for_children[v].second)*(mid-v_start)/2;
        tree[(v<<1)+1] += ((info_for_children[v].first+info_for_children[v].second*(mid-v_start)/2)*2+(v_end-v_start)*info_for_children[v].second)*(v_end-mid+1)/2;
        info_for_children[v] = {(long long)0, (long long)0};
        add(v<<1, v_start, mid-1);
        add((v<<1)+1, mid, v_end);
        tree[v] = tree[v<<1] + tree[(v<<1)+1];
    }
}

long long query(int v, int v_start, int v_end){
    if(v_end<qstart || qend<v_start) return (long long)0;
    else if(qstart <= v_start && v_end <= qend) return tree[v];
    else{
        int mid = ((v_start+v_end)>>1)+1;
        info_for_children[v<<1].first += info_for_children[v].first;
        info_for_children[v<<1].second += info_for_children[v].second;
        info_for_children[(v<<1)+1].first += info_for_children[v].first+a*(v_end-v_start+1)/2;
        info_for_children[(v<<1)+1].second += a ;
        tree[v<<1] += (info_for_children[v].first*2+(mid-1-v_start)*info_for_children[v].second)*(mid-v_start)/2;
        tree[(v<<1)+1] += ((info_for_children[v].first+info_for_children[v].second*(mid-v_start)/2)*2+(v_end-v_start)*info_for_children[v].second)*(v_end-mid+1)/2;
        info_for_children[v] = {(long long)0, (long long)0};
        return query(v<<1, v_start, mid-1) + query((v<<1)+1, mid, v_end);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    char c;
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> c;
        if(c == 'P'){
            cin >> x >> s >> a;
            infos[x] = {s,a};
            qstart = max(1, x-(s-1)/a);
            qend = x;
            add(1,0,base-1);
            /*qstart = x+1;
            s-=a;
            x+=1;
            a*=(-1);
            qend = min(n, x-(s-1)/a);
            if(s>0) add(1,0,base-1);*/
        }
        if(c == 'U'){
            cin >> x;
            s = -infos[x].first;
            a = -infos[x].second;
            qstart = max(1, x-(s+1)/a);
            qend = x;
            add(1, 0, base-1);
            qstart = x+1;
            s-=a;
            x+=1;
            a*=-1;
            qend = min(n,x+(s+1)/a);
            if(s<0) add(1, 0, base-1);
            infos[x] = {0, 0};
        }
        if(c == 'Z'){
            cin >> qstart >> qend;
            cout << query(1, 0, base-1)/(qend-qstart+1) << '\n';
        }
        for(int j=1; j<base*2; j++) cout << tree[j] << ' ';
        cout << '\n';
        for(int j=1; j<base*2; j++) cout << info_for_children[j].first << '_' << info_for_children[j].second << ' ' << ' ';
        cout << '\n';
    }
    return 0;
}