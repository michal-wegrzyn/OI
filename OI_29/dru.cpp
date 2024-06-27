#include <iostream>
#include <algorithm>
using namespace std;

char litery[1003][1003];
int liczba_liter[28];
int liczba_liter_spr[28];
int prawo[1003][1003];
int dol[1003][1003];
int dzielniki[140];
char min_fragment[1003];
int wydrukowane[1003][2003];
int w[1003];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, poczatek, wynik=0;
    char pchar;
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> pchar;
            liczba_liter[((int)pchar)-97]++;
            litery[i][j] = pchar;
        }
    }
    
    int curr_nwd = liczba_liter[((int)litery[0][0])-97];
    for(int i=0; i<26; i++) if(liczba_liter[i] != 0) curr_nwd = __gcd(curr_nwd, liczba_liter[i]);
    int k = n*m/curr_nwd;
    
    if(n/k*k != n && m/k*k != m){
        cout << 0;
        return 0;
    }
    
    int p2 = 1; int it_dzielniki = 0;
    if(k==1){
        while(p2*p2<n){
            if(n/p2*p2 == n){
                dzielniki[it_dzielniki] = p2;
                it_dzielniki++;
                dzielniki[it_dzielniki] = n/p2;
                it_dzielniki++;
            }
            p2++;
        }
        if(p2*p2==n){
            dzielniki[it_dzielniki] = p2;
            it_dzielniki++;
        }

        p2 = 1;
        while(p2*p2<m){
            if(m/p2*p2 == m){
                dzielniki[it_dzielniki] = p2;
                it_dzielniki++;
                dzielniki[it_dzielniki] = m/p2;
                it_dzielniki++;
            }
            p2++;
        }
        if(p2*p2==m){
            dzielniki[it_dzielniki] = p2;
            it_dzielniki++;
        }

        sort(dzielniki, dzielniki+it_dzielniki);
        p2 = -1;
        for(int i=0; i<it_dzielniki; i++){
            if(dzielniki[i] != p2) wynik++;
            p2 = dzielniki[i];
        }
        cout << wynik << '\n';
        for(int i=0; i<it_dzielniki; i++){
            if(dzielniki[i] != p2) cout << dzielniki[i] << ' ';
            p2 = dzielniki[i];
        }

        return 0;
    }

    pchar = litery[0][0];
    for(int i=n-1; i>=0; i--){
        for(int j=m-1; j>=0; j--){
            if(litery[i][j] == pchar){
                prawo[i][j] = prawo[i][j+1] + 1;
                dol[i][j] = dol[i+1][j] + 1;
            }
        }
    }
    
    if(prawo[0][0] == dol[0][0]){
        cout << 0;
        return 0;
    }

    int k2, curr_nwd2;
    
    int dlugosc = k, pominiete = 0;
    if((prawo[0][0] < dol[0][0] && prawo[0][0] != m) || dol[0][0] == n){ // idziemy w prawo
        poczatek = prawo[0][0];
        for(int i=k; i<m; i++){
            if((i-pominiete)/dlugosc*dlugosc == i-pominiete){
                if(i+prawo[0][i] == m){
                    pominiete += prawo[0][i];
                    break;
                }
                if(prawo[0][i]>=prawo[0][0]){
                    pominiete += prawo[0][i] - prawo[0][0];
                    i += prawo[0][i] - 1;
                    continue;
                }
                if(prawo[0][i] < prawo[0][0]){
                    if(dlugosc != i) dlugosc = (i-1)/k*k+k;
                    else dlugosc += k;
                    pominiete = 0;
                    i = dlugosc-1;
                }
            }
            else{
                if(litery[0][i-pominiete - (i-pominiete)/dlugosc*dlugosc] != litery[0][i]){
                    if(dlugosc != i) dlugosc = (i-1)/k*k+k;
                    else dlugosc += k;
                    pominiete = 0;
                    i = dlugosc-1;
                }
            }
        }
        if((m-pominiete)/dlugosc*dlugosc != m-pominiete){
            cout << 0;
            return 0;
        }

        for(int j=0; j<dlugosc; j++){
            min_fragment[j] = litery[0][j];
            liczba_liter_spr[((int)min_fragment[j])-97]++;
        }
        curr_nwd2 = liczba_liter_spr[((int)litery[0][0])-97];
        for(int j=0; j<26; j++) if(liczba_liter_spr[j] != 0) curr_nwd2 = __gcd(curr_nwd2, liczba_liter_spr[j]);
        k2 = dlugosc/curr_nwd2;
    }

    else{ // idziemy w dol
        poczatek = dol[0][0];
        for(int i=k; i<n; i++){
            if((i-pominiete)/dlugosc*dlugosc == i-pominiete){
                if(i+dol[i][0] == n){
                    pominiete += dol[i][0];
                    break;
                }
                if(dol[i][0]>=dol[0][0]){
                    pominiete += dol[i][0] - dol[0][0];
                    i += dol[i][0] - 1;
                    continue;
                }
                if(dol[i][0] < dol[0][0]){
                    if(dlugosc != i) dlugosc = (i-1)/k*k+k;
                    else dlugosc += k;
                    pominiete = 0;
                    i = dlugosc-1;
                }
            }
            else{
                if(litery[i-pominiete - (i-pominiete)/dlugosc*dlugosc][0] != litery[i][0]){
                    if(dlugosc != i) dlugosc = (i-1)/k*k+k;
                    else dlugosc += k;
                    pominiete = 0;
                    i = dlugosc-1;
                }
            }
        }
        if((n-pominiete)/dlugosc*dlugosc != n-pominiete){
            cout << 0;
            return 0;
        }

        for(int j=0; j<dlugosc; j++){
            min_fragment[j] = litery[j][0];
            liczba_liter_spr[((int)min_fragment[j])-97]++;
        }
        curr_nwd2 = liczba_liter_spr[((int)litery[0][0])-97];
        for(int j=0; j<26; j++) if(liczba_liter_spr[j] != 0) curr_nwd2 = __gcd(curr_nwd2, liczba_liter_spr[j]);
        k2 = dlugosc/curr_nwd2;
    }

    if(k2 != k){
        cout << 0; return 0;
    }

    if(m/dlugosc*dlugosc!=m && n/dlugosc*dlugosc!=n){
        cout << 0;
        return 0;
    }

    int p_wielokrotnosc;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(wydrukowane[i][j] == 0){
                if(prawo[i][j] != poczatek && dol[i][j] != poczatek){cout << 0; return 0;}
                if(prawo[i][j] == poczatek && wydrukowane[i][j+poczatek] == 0 && j+dlugosc <= m){ // idziemy w prawo
                    if(j==0) p_wielokrotnosc = 1;
                    else if(wydrukowane[i][j-1]>0) p_wielokrotnosc = wydrukowane[i][j-1] + 1;
                    else p_wielokrotnosc = 1;
                    w[p_wielokrotnosc]++;
                    w[p_wielokrotnosc-1]--;
                    for(int k=0; k<poczatek; k++){
                        if(wydrukowane[i][j+k] != 0){cout << 0; return 0;}
                        wydrukowane[i][j+k] = p_wielokrotnosc;
                    }
                    for(int k=poczatek; k<dlugosc; k++){
                        if(min_fragment[k] != litery[i][j+k]){cout << 0; return 0;}
                        if(wydrukowane[i][j+k] != 0){cout << 0; return 0;}
                        wydrukowane[i][j+k] = p_wielokrotnosc;
                    }
                }
                else{ // idziemy w dol
                    if(i+dlugosc>n){cout << 0; return 0;}
                    if(i==0) p_wielokrotnosc = -1;
                    else if(wydrukowane[i-1][j]<0) p_wielokrotnosc = wydrukowane[i-1][j] - 1;
                    else p_wielokrotnosc = -1;
                    w[-p_wielokrotnosc]++;
                    w[-p_wielokrotnosc-1]--;
                    for(int k=0; k<poczatek; k++){
                        if(wydrukowane[i+k][j] != 0){cout << 0; return 0;}
                        wydrukowane[i+k][j] = p_wielokrotnosc;
                    }
                    for(int k=poczatek; k<dlugosc; k++){
                        if(min_fragment[k] != litery[i+k][j]){cout << 0; return 0;}
                        if(wydrukowane[i+k][j] != 0){cout << 0; return 0;}
                        wydrukowane[i+k][j] = p_wielokrotnosc;
                    }
                }
            }
        }
    }

    curr_nwd2 = -1;
    for(int i=1; i<=1000; i++){
        if(w[i]!=0){
            if(curr_nwd2 == -1) curr_nwd2 = i;
            else curr_nwd2 = __gcd(curr_nwd2, i);
        }
    }

    p2 = 1; it_dzielniki = 0;
    while(p2*p2<curr_nwd2){
        if(curr_nwd2/p2*p2 == curr_nwd2){
            dzielniki[it_dzielniki] = p2;
            it_dzielniki++;
            dzielniki[it_dzielniki] = curr_nwd2/p2;
            it_dzielniki++;
        }
        p2++;
    }
    if(p2*p2==curr_nwd2){
        dzielniki[it_dzielniki] = p2;
        it_dzielniki++;
    }

    sort(dzielniki, dzielniki+it_dzielniki);

    cout << it_dzielniki << '\n';
    for(int i=0; i<it_dzielniki; i++){
        cout << dzielniki[i]*dlugosc << ' ';
        p2 = dzielniki[i];
    }
    
    return 0;
}