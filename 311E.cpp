#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<pair<int,int> > vp;
#define pb push_back
#define mp make_pair
#define ll long long
#define rep(i,n) for(int i=0;i<n;i++)
#define MOD 1000000007
#define N 5010
int dp[N][N],dp2[N][N];
struct node{
	node* A[2];
	int ct,sm;
} ;
node* getnode(){
	node *A = new node;
	A->ct = 0;
	A->sm = 0;
	A->A[0] = NULL;
	A->A[1] = NULL;
	return A;
}
void cal(node* cur){
	if(!cur)return;
	cur->sm = cur->ct;
	for(int i=0;i<2;i++){
		cal(cur->A[i]);
		if(cur->A[i])
			cur->sm += cur->A[i]->sm;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	string a;
	cin>>a;
	int n,k;
	cin>>k;
	int cr = 0;
	node* rt = getnode();
	n = a.length();
	for(int k=0;k<5;k++)
		for(int i=0;i<n-k;i++)
			if(a[i] == a[i+k])dp[i][i+k] = 1;
	for(int l = 5;l<=n;l++){
		for(int i=0;i<n;i++){
			int j = i + l - 1;
			if(j >= n)continue;
			if(a[i] == a[j])dp[i][j] = dp[i+2][j-2];
		}
	}
	for(int i=0;i<n;i++){
		node* cur = rt;
		for(int j=i;j<n;j++){
			int fg = 0;
			if(a[j] == 'b')fg = 1;
			if(cur->A[fg] == NULL)cur->A[fg] = getnode();
			cur = cur->A[fg];
			if(dp[i][j])cur->ct++;
		}
	}

	cal(rt);
	node* cur = rt;
	string ans = "";
	int val = 0;
	while(1){
		if(cur->A[0] && val + cur->A[0]->sm >= k){
			ans += "a";
			val += cur->A[0]->ct;
			cur = cur->A[0];
		}	
		else if(cur->A[1]){
			if(cur->A[0])
		 		val += cur->A[0]->sm;
		 	val += cur->A[1]->ct;
		 	ans+="b";
		 	cur = cur->A[1];
		}
		if(val >= k){
			cout<<ans<<'\n';
			break;
		}
	}
}	
