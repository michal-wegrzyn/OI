#include <iostream>
using namespace std;

long long mod(long long num, long long m){
    return num - num/m*m;
}

int main(){
    long long n, m, result=0, a=0, b=1;
    cin >> n >> m;
    n--;
    long long suma = n * (n+1) / 2;

    if(n==1){ cout << 1; return 0;}

    for(long long i=0; i<n-1; i++){
        suma -= i;
        a = a*(n-i) + b*mod(suma, m);
        a = mod(a, m);
        b *= n-i;
        b = mod(b, m);
        result += a;
    }

    for(long long i=0; i<n; i++){
        a += n*b;
        a = mod(a, m);
        result += a;
    }

    a = mod(n*(n+1), m);
    b = 1;

    suma = n * (n+1) / 2;

    for(long long i=0; i< n-2; i++){
        result -= a;
        suma -= i;
        a = a*(n-i) + b*mod(suma, m);
        a = mod(a, m);
        b *= n-i;
        b = mod(b, m);
    }
    result -= a;
    result = mod(result, m);
    if(result<0) result += m;
    cout << result;
    return 0;
}