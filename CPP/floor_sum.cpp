ll floor_sum(ll a,ll b,ll c,ll n) {
	ll res=0;
	if(a>=c) {
		res+=n*(n+1)*(a/c)/2;
		a%=c;
	}
	if(b>=c) {
		res+=(n+1)*(b/c);
		b%=c;
	}
	ll m=(a*n+b)/c;
	if(m==0) return res;
	res+=n*m-floor_sum(c,c-b-1,a,m-1);
	return res;
}