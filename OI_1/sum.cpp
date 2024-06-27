#include <iostream>
using namespace std;

int squares[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};

int sum_of_squares(int num){
    int result = 0;
    while(num){
        result += squares[num%10];
        num /= 10;
    }
    return result;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t, result;
    string n;
    cin >> t;
    for(int z=0; z<t; z++){
        cin >> n;
        cout << n;
        if(n == "1" || n == "4"){ cout << '\n'; continue;}
        result = 0;
        for(char c:n) result += squares[c-'0'];
        cout << ' ' << result;
        while(result != 1 && result != 4){
            result = sum_of_squares(result);
            cout << ' ' << result;
        }
        cout << '\n';
    }
}