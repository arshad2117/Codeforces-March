#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<pair<int,int> > vp;
#define pb push_back
#define mp make_pair
#define ll long long
#define rep(i,n) for(int i=0;i<n;i++)
#define MOD 1000000007
#define N 100010
vector<int> graph[N];
int par[N],ct = 0,cp[N],visited[N],l[2],cl[N];
bool cyc;
vector<pair<int,int> > cs;
void dfs(int s){
	if(cyc)return;
	visited[s] = 1;
	ct++;
	for(int i=0;i<graph[s].size();i++){
		if(!visited[graph[s][i]]){
			cl[graph[s][i]] = 1 - cl[s];
			l[cl[graph[s][i]]]++;
			dfs(graph[s][i]);
		}
		else{
			if(cl[graph[s][i]] == cl[s]){
				cyc = true;
				return;
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n,m,maxi = 0;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		graph[a-1].pb(b-1);
		graph[b-1].pb(a-1);
	}
	for(int i=0;i<n;i++){
		if(!visited[i]){
			ct = 0;
			l[0] = 1;
			l[1] = 0;
			dfs(i);
			maxi = max(maxi,ct);
			if(ct >= 3)
				cs.pb(mp(l[0],l[1]));
			cp[ct]++;
			if(cyc){
				cout<<0<<" "<<1<<'\n';
				return 0;
			}
		}
	}
	if(maxi == 1){
		cout<<3<<" "<<(ll)n*(n-1)*(n-2)/6<<'\n';
	}
	else if(maxi == 2){
		cout<<2<<" "<<((ll)cp[2]*(n-2))<<'\n';
	}
	else{
		ll ans = 0;
		for(int i=0;i<cs.size();i++){
			ans += ((ll)cs[i].first*(cs[i].first-1))/2 + ((ll)cs[i].second*(cs[i].second-1))/2  ;
		}
		cout<<1<<" "<<ans<<'\n';
	}
}
