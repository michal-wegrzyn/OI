int max(int a, int b){
    return (a>b?a:b);
}

int N, K;

constexpr int base = 1 << 19;
int tree[(base<<1)+7];
int info_for_children[(base<<1)+7];
int tree2[(base<<1)+7];

int qstart, qend, value=1;

void add(int v, int v_start, int v_end){
    if(v_end<qstart || qend<v_start) return;
    else if(qstart <= v_start && v_end <= qend){
        tree[v] += value;
        info_for_children[v] += value;
    }
    else{
        tree[v<<1] += info_for_children[v];
        tree[(v<<1)+1] += info_for_children[v];
        info_for_children[v<<1] += info_for_children[v];
        info_for_children[(v<<1)+1] += info_for_children[v];
        info_for_children[v] = 0;
        add(v<<1, v_start, (v_start+v_end)>>1);
        add((v<<1)+1, ((v_start+v_end)>>1)+1, v_end);
        tree[v] = max(tree[v<<1], tree[(v<<1)+1]);
    }
}

int query(int v, int v_start, int v_end){
    if(v_end<qstart || qend<v_start) return 0;
    else if(qstart <= v_start && v_end <= qend) return tree[v];
    else{
        tree[v<<1] += info_for_children[v];
        tree[(v<<1)+1] += info_for_children[v];
        info_for_children[v<<1] += info_for_children[v];
        info_for_children[(v<<1)+1] += info_for_children[v];
        info_for_children[v] = 0;
        return max(query(v<<1, v_start, (v_start+v_end)>>1), query((v<<1)+1, ((v_start+v_end)>>1)+1, v_end));
    }
}

void add2(int v){
    v = v+base;
    tree2[v] += 1;
    v /= 2;
    while(v){
        tree2[v] = tree2[2*v]+tree2[2*v+1];
        v /= 2;
    }
}

int query2(){
    int result = 0;
    qstart = qstart - 1 + base;
    qend = qend + 1 + base;
    while(qstart/2 != qend/2){
        if(!(qstart&1)) result += tree2[qstart+1];
        if(qend&1) result += tree2[qend-1];
        qstart /= 2;
        qend /= 2;
    }
    return result;
}

void update_tree2(int v){
    if(tree[v]>=K){
        if(v>=base){
            add2(v-base);
            qstart = v-base;
            qend = v-base;
            add(1, 0, base-1);
        }
        else{
            tree[v<<1] += info_for_children[v];
            tree[(v<<1)+1] += info_for_children[v];
            info_for_children[v<<1] += info_for_children[v];
            info_for_children[(v<<1)+1] += info_for_children[v];
            info_for_children[v] = 0;
            if(tree[v<<1]>=K) update_tree2(v<<1);
            if(tree[(v<<1)+1]>=K) update_tree2((v<<1)+1);
        }
    }
}

void inicjuj(int n, int k, int *D){
    N = n;
    K = k;
    for(int i=0; i<n; i++){
        if(D[i] < K) tree[i+base] = D[i];
        else{
            tree[i+base] = -2000000000;
            tree2[i+base] = 1;
        }
    }
    for(int i=base-1; i>0; i--) tree[i] = max(tree[i<<1], tree[(i<<1)+1]);
    for(int i=base-1; i>0; i--) tree2[i] = tree2[i<<1]+tree2[(i<<1)+1];
}

void podlej(int a, int b){
    qstart = a;
    qend = b;
    add(1, 0, base-1);
}

int dojrzale(int a, int b){
    value = -2000000000;
    update_tree2(1);
    value = 1;
    qstart = a;
    qend = b;
    return query2();
}

/*#include <iostream>
using namespace std;

int T[6] = {5, 4, 5, 7, 3, 2};

int main(){
    inicjuj(6, 6, T);
    cout << dojrzale(2, 5) << '\n';
    podlej(1,2);
    cout << dojrzale(1,3) << '\n';
    podlej(0,3);
    podlej(1,1);
    cout << dojrzale(0,3) << '\n';
}*/