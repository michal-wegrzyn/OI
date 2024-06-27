#include <iostream>
using namespace std;

long long primes[45] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
37, 41, 43, 47, 53, 61, 73, 89, 107, 109, 113, 149,
199, 211, 233, 281, 307, 421, 521, 557, 1597, 2161,
2207, 2417, 2789, 3001, 3571, 19801, 28657, 59369,
135721, 141961, 514229, 433494437};

long long f[87]; // ciag fibonacciego
long long rf[45]; // dzielniki m bedace liczbami fibonacciego
int rfp[45][6][2]; // rozklad liczb z rf na liczby pierwsze
int prf_sizes[45];
int long prf[45][25]; // dla kazdej liczby pierwszej info dla ktorych liczb fibbonaciego sa dzielnikami
bool rf_isused[45];
int steps[45][2];

long long mod(long long n, long long d){
    return n - n/d*d;
}

int main(){
    long long m, p, p2, p3, result;
    bool pb;
    cin >> m;
    int rf_size = 0;
    p2 = m;
    f[0] = 1; f[1] = 1;

    // m <= 10^9
    for(int i=0; i<45; i++) while(mod(p2, primes[i]) == 0) p2 /= primes[i];
    for(int i=2; i<87; i++) f[i] = f[i-2] + f[i-1];
    if(p2 > (long long)1){
        for(int i=46; i<87; i++) if(mod(f[i], p2) == 0){
            result += i+1;
            p2 *= -1;
            if(mod(m, f[i]) != 0){cout << "NIE"; return 0;}
            break;
        }
        if(p2>0){cout << "NIE"; return 0;}
    }

    // tworzymy rf, rfp i prf
    for(int i=2; i<46; i++){
        if(mod(m,f[i])==0){
            rf[rf_size] = f[i];
            p = 0;
            for(int j=0; j<45; j++){
                if(mod(f[i], primes[j]) == 0){
                    p2 = f[i]; p3 = 0;
                    while(mod(p2, primes[j]) == 0){
                        p2 /= primes[j];
                        p3++;
                    }
                    rfp[rf_size][p][0] = j;
                    rfp[rf_size][p][1] = p3;
                    if(p<5) rfp[rf_size][p+1][0] = -1;
                    p++;
                    prf[j][prf_sizes[j]] = rf_size;
                    prf_sizes[j]++;
                }
            }
            rf_size++;
        }
    }

    // tworzymy steps
    p3 = 0;

    for(int i=rf_size-1; i>=0; i--){  // i -> rf
        /*for(int j=0; j<5; j++){
            cout << primes[j] << ' ';
            for(int k=0; k<prf_sizes[j]; k++) cout << prf[j][k] << ' ';
            cout << '\n';
        }
        for(int j=0; j<rf_size; j++) cout << (rf_isused[j]?1:0) << ' ';
        cout << '\n' << '\n';*/
        if(rf_isused[i]) continue;

        pb = false;
        for(int j=0; j<45; j++){    // j -> primes
            if(prf_sizes[j]==1){
                steps[p3][0] = prf[j][0];
                steps[p3][1] = j;
                rf_isused[prf[j][0]] = true;
                for(int k=0; k<6; k++){    // k -> rfp[prf[j][0]][k][0]
                    if(rfp[prf[j][0]][k][0] == -1) break;
                    for(int l=0; l<prf_sizes[rfp[prf[j][0]][k][0]]; l++){   
                        if(prf[rfp[prf[j][0]][k][0]][l] == prf[j][0]){
                            prf[rfp[prf[j][0]][k][0]][l] = prf[rfp[prf[j][0]][k][0]][prf_sizes[rfp[prf[j][0]][k][0]]-1];
                            break;
                        }
                    }
                    prf_sizes[rfp[prf[j][0]][k][0]]--;
                }
                p3++;
                pb = true;
            }
        }
        if(pb){i++; pb=false; continue;}
        if(rf_isused[i]) continue;
        rf_isused[i] = true;
        for(int j=0; j<6; j++){  // j -> rfp[i][j][0]
            if(rfp[i][j][0] == -1) break;
            for(int k=0; k<prf_sizes[rfp[i][j][0]]; k++){ // k -> prf[rfp[i][j][0]][k]
                if(prf[rfp[i][j][0]][k] == i){
                    prf[rfp[i][j][0]][k] = prf[rfp[i][j][0]][prf_sizes[rfp[i][j][0]]-1];
                    prf_sizes[rfp[i][j][0]]--;
                    break;
                }
            }
        }
        steps[p3][0] = i;
        steps[p3][1] = -1;
        p3++;
    }

    cout << rf_size << '\n';
    for(int i=0; i<rf_size; i++) cout << rf[i] << ' ';
    cout << '\n';

    cout << p3 << '\n';

    for(int i=0; i<p3; i++) cout << rf[steps[i][0]] << ' ' << (steps[i][1]!=-1?primes[steps[i][1]]:-1) << '\n';

    return 0;
}