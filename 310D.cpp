#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<pair<int,int> > vp;
#define pb push_back
#define mp make_pair
#define ll long long
#define rep(i,n) for(int i=0;i<n;i++)
#define MOD 1000000007
#define N 200010
pair<ll,ll> A[N],B[N];
pair<ll,pair<ll,ll> >C[N];
vector<ll> st[4*N];
vector<ll> pts;
ll rev[4*N],ans[N],tree[20*N];
map<ll,ll>  mpit;
void update(int low,int high,int ind,int val,int node){
	if(low == high){
		tree[node] += val;
		tree[node] = max(tree[node],(ll)0);
		return;
	}
	int mid = (low + high)/2;
	if(ind <= mid)update(low,mid,ind,val,2*node);
	else update(mid+1,high,ind,val,2*node+1);
	tree[node] = tree[2*node] + tree[2*node+1];
}
ll query(int low,int high,int begin,int end,int node){
	if(low >  end || high < begin || begin > end)return 0;
	if(low >= begin && high <= end)return tree[node];
	int mid = (low + high)/2;
	return query(low,mid,begin,end,2*node) + query(mid+1,high,begin,end,2*node+1);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>A[i].first>>A[i].second;
	for(int i=0;i<m;i++){
		ll x;
		cin>>x;
		B[i] = mp(x,i);
	}
	for(int i=1;i<n;i++){
		C[i] = mp(A[i].first-A[i-1].second,mp(A[i].second-A[i-1].first,i-1));
	}
	for(int i=1;i<n;i++){
		pts.pb(C[i].first);
		pts.pb(C[i].second.first);
	}
	for(int i=0;i<m;i++){
		pts.pb(B[i].first);
	}
	vector<ll> df = pts;
	sort(df.begin(),df.end());
	for(int i=0;i<pts.size();i++){
		mpit[pts[i]] = lower_bound(df.begin(),df.end(),pts[i]) - df.begin();
		rev[mpit[pts[i]]] = pts[i];
	}
	int g = pts.size();
	sort(B,B+m);
	sort(C+1,C+n);
	int cur = 1;
	for(int i=0;i<m;i++){
		int low = mpit[B[i].first],d = mpit[B[i].first],high = g;
		while(cur < n && mpit[C[cur].first] <= low){
			update(0,g,mpit[C[cur].second.first],1,1);
			st[mpit[C[cur].second.first]].pb(C[cur].second.second);
			cur++;
		}
		while(low < high){
			int mid = (high + low)/2;
			if(query(0,g,d,mid,1) > 0)high = mid;
			else low = mid + 1;
		}
		if(low != g){
			ans[st[low].back()] = B[i].second;
			st[low].pop_back();
			update(0,g,low,-1,1);
		}
	}
	if(!tree[1] && cur == n){
		cout<<"Yes\n";
		for(int i=0;i<n-1;i++)
			cout<<ans[i]+1<<" ";
		cout<<'\n';
	}
	else
		cout<<"No\n";
}
