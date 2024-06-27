#include<bits/stdc++.h>
using namespace std;

vector<long long>v;
int last[1000007];
bool cb[1000007];
bool odp[1000007];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	long long kl=0;
	int n,m,a,used;
	cin>>m;
	
	for(int i=1; i<=m; i++){
		cin>>a;
		cb[a]=1;
	}
	
	cin>>n;
	
	for(int i=1; i<=n; i++){
		cin >> a;
		used=0;
		
		for(int j=last[a]+a; j<=1000000; j+=a){
			if(used==a) break;
			if(odp[j]) continue;
			last[a]=j;
			odp[j]=1;
			used++;
			kl++;
			if(cb[j]) v.push_back(kl);
		}
		kl += a-used;
	}
	
	cout << v.size() << '\n';
	for(auto i:v) cout << i << '\n';
	
	return 0;
}