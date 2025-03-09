#include<bits/stdc++.h>
#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
#define uLL unsigned long long
using namespace std;
typedef vector<int> poly;
typedef vector<int> Vec;
typedef vector<Vec> Mat;
typedef tuple<poly,poly> Vec2;
typedef tuple<poly,poly,poly,poly> Mat2;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
const int Mod=998244353,G=3,img=86583718;
vector<uLL>Grt,iGrt;
poly Tr,grt,igrt,frc({1,1}),inv({0,1}),ivf({1,1});
inline int qpow(int x,int y,int z=1){
	for(;y;(y>>=1)&&(x=(LL)x*x%Mod))if(y&1)z=(LL)z*x%Mod;return z;
}
inline void Init(const int&n){
	for(int i=frc.size();i<=n;++i)
		frc.emplace_back((LL)frc.back()*i%Mod),
		inv.emplace_back(Mod-Mod/i*(LL)inv[Mod%i]%Mod),
		ivf.emplace_back((LL)ivf.back()*inv.back()%Mod);
}
inline int Binom(const int&n,const int&m){
	if(n<m||m<0)return 0;
	return Init(n),(LL)frc[n]*ivf[m]%Mod*ivf[n-m]%Mod;
}
inline int Sqrt(const int&x){
	if(qpow(x,(Mod-1)/2)!=1)return -1;
	int a=1;
	while(qpow(((LL)a*a+Mod-x)%Mod,(Mod-1)/2)==1)
		a=uniform_int_distribution<int>(0,Mod-1)(rng);
	const int b=((LL)a*a+Mod-x)%Mod;
	pair<int,int>z(1,0),r(a,1);
	const auto mul=[&](pair<int,int>x,pair<int,int>y){
		return make_pair(((LL)x.first*y.first+(LL)x.second*y.second%Mod*b)%Mod,((LL)x.first*y.second+(LL)x.second*y.first)%Mod);
	};
	for(int y=(Mod+1)/2;y;(y>>=1)&&(r=mul(r,r),1))if(y&1)z=mul(z,r);
	if(z.first<0)z.first+=Mod;
	return min(z.first,Mod-z.first);
}
inline bool Empty(poly&P){
	for(;!P.empty()&&!P.back();P.pop_back());
	return P.empty();
}
inline poly Add(poly P,poly Q){
    if(P.size()<Q.size())P.swap(Q);
    for(int i=Q.size();i--;)(P[i]+=Q[i])>=Mod&&(P[i]-=Mod);
    return P;
}
inline poly Add_Empty(poly P,poly Q){
    if(P.size()<Q.size())P.swap(Q);
    for(int i=Q.size();i--;)(P[i]+=Q[i])>=Mod&&(P[i]-=Mod);
    return Empty(P),P;
}
inline poly Sub(poly P,poly Q){
    if(P.size()<Q.size())P.resize(Q.size());
    for(int i=Q.size();i--;)(P[i]-=Q[i])<0&&(P[i]+=Mod);
    return P;
}
inline poly Sub_Empty(poly P,poly Q){
    if(P.size()<Q.size())P.resize(Q.size());
    for(int i=Q.size();i--;)(P[i]-=Q[i])<0&&(P[i]+=Mod);
    return Empty(P),P;
}
inline poly Mulx(poly P,int x){
	for(int&i:P)i=(LL)i*x%Mod;
	return P;
}
inline poly Neg(poly P){
	for(int i=P.size();i--;)P[i]&&(P[i]=Mod-P[i]);
	return P;
}
inline int Eval(poly&P,int x){
	int z=0;
	for(int i=P.size();i--;)z=((LL)z*x+P[i])%Mod;
	return z;
}
inline poly invLinear(poly P){
	const int n=P.size();
	poly Q(n+1,1);
	for(int i=0;i<n;++i)Q[i+1]=(LL)Q[i]*P[i]%Mod;
	int t=qpow(Q[n],Mod-2);Q.pop_back();
	for(int i=n;i--;)Q[i]=(LL)Q[i]*t%Mod,t=(LL)t*P[i]%Mod;
	return Q;
}
inline Mat operator*(const Mat&x,const Mat&y){
	const int n=x.size(),m=y.size(),q=y[0].size();
	Mat z(n,Vec(q));
	for(int i=0;i<n;++i)for(int j=0;j<m;++j)if(x[i][j])
		for(int k=0;k<q;++k)z[i][k]=(z[i][k]+(LL)x[i][j]*y[j][k])%Mod;
	return z;
}
inline uLL trans(const uLL&x){
    constexpr uLL A=-(uLL)Mod/Mod+1;
    constexpr uLL Q=(((__uint128_t)(-(uLL)Mod%Mod)<<64)+Mod-1)/Mod;
    return x*A+(uLL)((__uint128_t)x*Q>>64)+1;
}
inline uLL mul(const uLL&x,const uLL&y){
    return x*y*(__uint128_t)Mod>>64;
}
inline uLL add(uLL x,const uLL&y){
    return (LL)((x+=y)-Mod)>=0?x-Mod:x;
}
inline uLL sub(uLL x,const uLL&y){
    return (LL)(x-=y)<0?x+Mod:x;
}
inline void extend(const int&n){
    if(grt.empty())
		grt.emplace_back(1),igrt.emplace_back(1),
		Grt.emplace_back(trans(1)),iGrt.emplace_back(trans(1));
    if(grt.size()<n){
        int L=grt.size();
        grt.resize(n),igrt.resize(n),Grt.resize(n),iGrt.resize(n);
        for(;L<n;L*=2){
            const int w=qpow(G,Mod/(L*4)),iw=qpow(w,Mod-2);
            for(int i=0;i<L;++i)
				grt[i+L]=(LL)grt[i]*w%Mod,igrt[i+L]=(LL)igrt[i]*iw%Mod,
				Grt[i+L]=trans(grt[i+L]),iGrt[i+L]=trans(igrt[i+L]);
        }
    }
}
template<int A,int B,int C=0,class fun>inline void Butterrep(int i,int j,int k,fun F){
    if(A!=C)F(i,j+C/B,k+C*2-C%B),Butterrep<A,B,C+(C<A)>(i,j,k,F);
}
template<class fun>inline void ButterX(int i,int n,fun F){
    for(int j=0;2*i*j<n;++j)for(int k=0;k<i;k+=32)Butterrep<32,32>(i,j,k+2*i*j,F);
}
template<int i,class fun>inline void ButterY(int n,fun F){
    if(n>32)for(int j=0;2*i*j<n;j+=32/i)Butterrep<32,i>(i,j,2*i*j,F);
    else if(i<n)for(int j=0;2*i*j<n;++j)for(int k=0;k<i;++k)F(i,j,k+2*i*j);
}
template<class T>inline void DFT(T P,int n){
    extend(n);
    const auto F=[&](int x,int y,int z){
        const uLL a=P[z],b=mul(P[z+x],Grt[y]);
        P[z]=add(a,b),P[z+x]=sub(a,b);
    };
    for(int i=n>>1;i>16;i>>=1)ButterX(i,n,F);
    ButterY<16>(n,F),ButterY<8>(n,F),ButterY<4>(n,F),ButterY<2>(n,F),ButterY<1>(n,F);
}
template<class T>inline void IDFT(T P,int n){
    const uLL ni=trans(qpow(n,Mod-2));
	for(int i=0;i<n;++i)P[i]=mul(P[i],ni);
    extend(n);
    const auto F=[&](int x,int y,int z){
        const uLL a=P[z],b=P[z+x];
        P[z]=add(a,b),P[z+x]=mul(a-b+Mod,iGrt[y]);
    };
    ButterY<1>(n,F),ButterY<2>(n,F),ButterY<4>(n,F),ButterY<8>(n,F),ButterY<16>(n,F);
    for(int i=32;i<n;i<<=1)ButterX(i,n,F);
}
inline void DFT(poly&P){
	DFT(P.begin(),P.size());
}
inline void IDFT(poly&P){
	IDFT(P.begin(),P.size());
}
inline poly Mul(poly P,poly Q){
    if(P.empty()||Q.empty())return poly();
	const int pn=P.size(),qn=Q.size(),rn=pn+qn-1;
	const int m=2<<__lg(max(1,rn-1));
	P.resize(m),Q.resize(m);
	DFT(P),DFT(Q);
	for(int i=m;i--;)P[i]=(LL)P[i]*Q[i]%Mod;
	IDFT(P);
	return P.resize(rn),P;
}
inline poly MulT(poly P,poly Q){
	const int m=Q.size();
	reverse(Q.begin(),Q.end()),Q=Mul(P,Q);
	return poly(Q.begin()+m-1,Q.end());
}
inline poly Inv(poly P){
	const int pn=P.size();
	const int m=2<<__lg(max(1,pn-1));
	P.resize(m);
	poly Q({qpow(P[0],Mod-2)});
	for(int n=2;n<=m;n*=2){
		poly F(P.begin(),P.begin()+n),dQ(Q);
		dQ.resize(n),DFT(dQ),DFT(F);
		poly nQ(n);
		for(int i=0;i<n;++i)nQ[i]=(LL)(Mod-F[i])*dQ[i]%Mod;
		IDFT(nQ),fill_n(nQ.begin(),n/2,0),DFT(nQ);
		for(int i=0;i<n;++i)dQ[i]=(LL)nQ[i]*dQ[i]%Mod;
		IDFT(dQ),Q.insert(Q.end(),dQ.begin()+n/2,dQ.end());
	}
	return Q.resize(pn),Q;
}
inline pair<poly,poly>Sqrt_InvSqrt(poly P){
	const int pn=P.size();
	const int m=2<<__lg(max(1,pn-1));
	P.resize(m);
	poly Q({1}),H({1}),dQ({Q[0]});
	for(int n=2;n<=m;n*=2){
		poly dH(H);
		for(int i=0;i<n/2;++i)dQ[i]=(LL)dQ[i]*dQ[i]%Mod;
		IDFT(dQ),dQ=Sub(Sub(dQ,poly(P.begin(),P.begin()+n/2)),poly(P.begin()+n/2,P.begin()+n));
		dQ.insert(dQ.begin(),n/2,0),dH.resize(n),DFT(dH),DFT(dQ);
		for(int i=0;i<n;++i)
			if((dQ[i]=(LL)(Mod-dQ[i])*dH[i]%Mod)&1)dQ[i]+=Mod,dQ[i]>>=1;
			else dQ[i]>>=1;
		IDFT(dQ);
		Q.insert(Q.end(),dQ.begin()+n/2,dQ.end());
		dQ=Q,DFT(dQ);
		poly nH(n);
		for(int i=0;i<n;++i)nH[i]=(LL)(Mod-dQ[i])*dH[i]%Mod;
		IDFT(nH),fill_n(nH.begin(),n/2,0),DFT(nH);
		for(int i=0;i<n;++i)dH[i]=(LL)nH[i]*dH[i]%Mod;
		IDFT(dH),H.insert(H.end(),dH.begin()+n/2,dH.end());
	}
    return Q.resize(pn),H.resize(pn),make_pair(Q,H);
}
inline poly Sqrt(poly P){
	const int n=P.size();
	int p=0;while(p<n&&!P[p])++p;
	if(p>=n)return P;
	if(p&1)return poly({-1});
	const int v=Sqrt(P[p]);
	if(v==-1)return poly({-1});
	P.erase(P.begin(),P.begin()+p),P.resize(n-p/2);
	P=Mulx(Sqrt_InvSqrt(Mulx(P,qpow(P[0],Mod-2))).first,v);
	return P.insert(P.begin(),p/2,0),P;
}
inline poly InvSqrt(poly P){
	const int v=Sqrt(P[0]);
	if(v==-1)return poly({-1});
	return Mulx(Sqrt_InvSqrt(Mulx(P,qpow(P[0],Mod-2))).second,v);
}
inline poly Direv(poly P){
    const int n=P.size();
	for(int i=1;i<n;++i)P[i-1]=(LL)P[i]*i%Mod;
	return P.pop_back(),P;
}
inline poly Inter(poly P){
    P.emplace_back(0);
	const int n=P.size();Init(n);
	for(int i=n;--i;)P[i]=(LL)P[i-1]*inv[i]%Mod;
	return P[0]=0,P;
}
inline poly Ln(poly P){
	const int n=P.size();
	P=Mul(Direv(P),Inv(P));
	return P.resize(n-1),Inter(P);
}
inline vector<poly>Mul(vector<poly>P,vector<poly>Q){
    const int mP=P.size(),nP=P[0].size(),mQ=Q.size(),nQ=Q[0].size();
    poly _P(nP*(mP+mQ-1)),_Q(nQ*(mP+mQ-1));
    for(int i=0;i<mP;++i)for(int j=0;j<nP;++j)_P[i+j*(mP+mQ-1)]=P[i][j];
    for(int i=0;i<mQ;++i)for(int j=0;j<nQ;++j)_Q[i+j*(mP+mQ-1)]=Q[i][j];
    _P=Mul(_P,_Q),P.resize(mP+mQ-1);
    for(int i=0;i<mP+mQ-1;++i){
        P[i].resize(nP+nQ-1);
        for(int j=0;j<nP+nQ-1;++j)
            P[i][j]=_P[i+j*(mP+mQ-1)];
    }
    return P;
}
inline poly Exp(poly P){
	const int pn=P.size();
	const int m=2<<__lg(max(1,pn-1));
	P.resize(m),Init(m),extend(m);
	poly Q({1}),H({1}),dQ({1});
	for(int n=2;n<=m;n*=2){
		poly ddQ(Q);
		const int t=grt[n/4];
		for(int i=0,w=1;i<n/2;++i)ddQ[i]=(LL)ddQ[i]*w%Mod,w=(LL)w*t%Mod;
		DFT(ddQ),dQ.insert(dQ.end(),ddQ.begin(),ddQ.end());
		poly nF(Direv(poly(P.begin(),P.begin()+n/2))),nQ(Direv(Q)),dH(H),dnF(nF);
		dnF.resize(n),DFT(dnF);
		nQ.resize(n),DFT(nQ);
		dH.resize(n),DFT(dH);
		for(int i=0;i<n;++i)nQ[i]=(nQ[i]+Mod-(LL)dnF[i]*dQ[i]%Mod)*dH[i]%Mod;
		IDFT(nQ),copy(nF.begin(),nF.end(),nQ.begin());
		nQ=Sub(poly(P.begin(),P.begin()+n),Inter(nQ));
		nQ.resize(n),DFT(nQ);
		for(int i=0;i<n;++i)dQ[i]=(LL)dQ[i]*nQ[i]%Mod;
		IDFT(dQ),Q.insert(Q.end(),dQ.begin()+n/2,dQ.end());
		if(n==m)break;
		dQ=Q,DFT(dQ);
		poly nH(n);
		for(int i=0;i<n;++i)nH[i]=(LL)(Mod-dQ[i])*dH[i]%Mod;
		IDFT(nH),fill_n(nH.begin(),n/2,0),DFT(nH);
		for(int i=0;i<n;++i)dH[i]=(LL)nH[i]*dH[i]%Mod;
		IDFT(dH),H.insert(H.end(),dH.begin()+n/2,dH.end());
	}
	return Q.resize(pn),Q;
}
inline poly Qpow(poly P,int k){
	return Exp(Mulx(Ln(P),k));
}
inline poly Shift(poly P,int k){
	if(!k)return P;
	const int n=P.size();
	Init(n);
	for(int i=0;i<n;++i)P[i]=(LL)frc[i]*P[i]%Mod;
	poly Q(n,1);
	for(int i=1;i<n;++i)Q[i]=(LL)Q[i-1]*k%Mod*inv[i]%Mod;
	Q=MulT(P,Q);
	for(int i=0;i<n;++i)Q[i]=(LL)Q[i]*ivf[i]%Mod;
	return Q;
}
inline poly Multi(poly P,int k){
	const int n=P.size();
	for(int i=0,w=1;i<n;++i,w=(LL)w*k%Mod)P[i]=(LL)P[i]*w%Mod;
	return P;
}
inline poly ModPow(poly X,LL k,poly P){
	const int m=P.size();
	poly nP=P;reverse(nP.begin(),nP.end()),nP=Inv(nP);
	const int L=2<<__lg(m*2-1);
	P.resize(L),nP.resize(L),DFT(P),DFT(nP);
	int Xn=X.size();
	X.resize(L),DFT(X);
	const auto MoD=[&](poly F){
		poly nF=F;
		IDFT(nF);
		nF.resize(m*2-3),reverse(nF.begin(),nF.end()),nF.resize(m-2);
		nF.resize(L),DFT(nF);
		for(int i=0;i<L;++i)nF[i]=(LL)nF[i]*nP[i]%Mod;
		IDFT(nF),nF.resize(m-2),reverse(nF.begin(),nF.end());
		nF.resize(L),DFT(nF);
		for(int i=0;i<L;++i)nF[i]=(LL)nF[i]*P[i]%Mod;
		return Sub(F,nF);
	};
	poly Q({1});
	int Qn=Q.size();
	Q.resize(L),DFT(Q);
	while(k){
		if(k&1){
			for(int i=0;i<L;++i)Q[i]=(LL)Q[i]*X[i]%Mod;
			Qn+=Xn-1;
			if(Qn>=m)Q=MoD(Q),Qn=m-1;
		}
		if(k>>=1){
			for(int i=0;i<L;++i)X[i]=(LL)X[i]*X[i]%Mod;
			Xn+=Xn-1;
			if(Xn>=m)X=MoD(X),Xn=m-1;
		}
	}
	return IDFT(Q),Q.resize(m-1),Q;
}
inline poly Comp_solve(poly&P,poly&Q,int d,int n,int v){
    if(n==1){
        poly H(d+1);
		Init(d+d);
		for(int i=0,w=1;i<=d;++i)
			H[i]=(LL)Binom(d+i-1,d-1)*w%Mod,w=(LL)w*v%Mod;
        H=MulT(P,H);
		return H;
    }
	poly nQ(d*n*4);
	for(int i=0;i<d;++i)for(int j=0;j<n;++j)nQ[i*n*2+j]=Q[i*n+j];
	nQ[d*n*2]=1,DFT(nQ);
	poly H(d*n*2);
	for(int i=0;i<d*n*4;i+=2)H[i/2]=(LL)nQ[i]*nQ[i+1]%Mod;
	IDFT(H),--H[0];
	for(int i=1;i<d*2;++i)for(int j=0;j<n/2;++j)H[i*(n/2)+j]=H[i*n+j];
	H.resize(d*n);
	H=Comp_solve(P,H,d*2,n/2,v);
	poly nH(d*n*2);
	for(int i=0;i<d*2;++i)for(int j=0;j<n/2;++j)nH[i*n+j]=H[i*(n/2)+j];
	DFT(nH);
	poly F(d*n*4);
	for(int i=0;i<d*n*4;i+=2)F[i]=(LL)nH[i/2]*nQ[i+1]%Mod,F[i+1]=(LL)nH[i/2]*nQ[i]%Mod;
	IDFT(F);
	for(int i=0;i<d;++i)for(int j=0;j<n;++j)F[i*n+j]=F[(i+d)*n*2+j];
	return F.resize(d*n),F;
}
inline poly Comp(poly P,poly Q){
	if(P.empty()||Q.empty())return poly();
	const int pn=P.size(),m=2<<__lg(max(1,pn-1)),v=Q[0];
	P.resize(m),Q=Neg(Q),Q.resize(m);
	Q=Comp_solve(P,Q,1,m,v);
	return Q.resize(pn),Q;
}
inline poly Compinv(poly P){
    const int n=P.size(),t=qpow(P[1],Mod-2);Init(n);
	for(int i=1,w=t;i<n;++i)P[i]=(LL)P[i]*w%Mod,w=(LL)w*t%Mod;
	const int m=2<<__lg(n-1);
	poly Q(m);Q[0]=1,P=Neg(P),P.resize(m);
	P.swap(Q);
	int d=1;
	for(int k=n-1;k;d*=2,k/=2){
		const int L=2<<__lg(d*(k+1)*4-1);
		poly nP(L),nQ(L);
		for(int i=0;i<d;++i)for(int j=0;j<=k;++j)
			nP[i*(k+1)*2+j]=P[i*(k+1)+j],nQ[i*(k+1)*2+j]=Q[i*(k+1)+j];
		nQ[d*(k+1)*2]=1,DFT(nP),DFT(nQ);
		P.resize(L/2),Q.resize(L/2);
		if(k&1){
			for(int i=0;i<L;i+=2){
				if((P[i/2]=((LL)nP[i]*nQ[i+1]-(LL)nP[i+1]*nQ[i])%Mod*igrt[i/2]%Mod)<0)P[i/2]+=Mod;
				if(P[i/2]&1)P[i/2]+=Mod;
				P[i/2]>>=1,Q[i/2]=(LL)nQ[i]*nQ[i+1]%Mod;
			}
		}
		else{
			for(int i=0;i<L;i+=2){
				if((P[i/2]=((LL)nP[i]*nQ[i+1]+(LL)nP[i+1]*nQ[i])%Mod)&1)P[i/2]+=Mod;
				P[i/2]>>=1,Q[i/2]=(LL)nQ[i]*nQ[i+1]%Mod;
			}
		}
		IDFT(P),IDFT(Q);
		if(d*(k+1)*4>=L)--Q[d*(k+1)*4%L];
		for(int i=1;i<d*2;++i)for(int j=0;j<=k/2;++j)
			P[i*(k/2+1)+j]=P[i*(k+1)+j],Q[i*(k/2+1)+j]=Q[i*(k+1)+j];
		P.resize(d*2*(k/2+1)),Q.resize(d*2*(k/2+1));
	}
	Init(n);
	Q=P,reverse(Q.begin(),Q.end()),Q.resize(n);
    for(int i=1;i<n;++i)Q[i]=Q[i]*(n-1ll)%Mod*inv[i]%Mod;
    reverse(Q.begin(),Q.end()),Q=Mulx(Qpow(Q,Mod-qpow(n-1,Mod-2)),t);
    Q.insert(Q.begin(),0);
    return Q.resize(n),Q;
}
inline poly Div(poly P,poly Q){
    const int n=P.size(),m=Q.size();
    if(n<m)return poly();
	reverse(P.begin(),P.end());
	reverse(Q.begin(),Q.end()),Q.resize(n-m+1);
    P=Mul(P,Inv(Q)),P.resize(n-m+1);
	reverse(P.begin(),P.end());
	return P;
}
inline poly MOD(poly P,poly Q){
    if(P.size()<Q.size())return P;
	const int m=Q.size();
	return Q=Mul(Q,Div(P,Q)),P.resize(m-1),Q.resize(m-1),Sub(P,Q);
}
inline poly Fpow(poly P,int k,int ki){
	const int n=P.size();int tn=0;
	for(tn=0;tn<n&&!P[tn];++tn);
	if((LL)tn*k>=n)return poly(n);
	const int x=qpow(P[tn],Mod-2),y=qpow(P[tn],ki);
	poly Q(n-(tn*k));
	for(int i=n-tn*k-1;~i;--i)Q[i]=(LL)P[i+tn]*x%Mod;
	Q=Mulx(Ln(Q),k),tn*=k;
	Q=Exp(Q),fill_n(P.begin(),tn,0);
	for(int i=tn;i<n;++i)P[i]=(LL)Q[i-tn]*y%Mod;
	return P;
}
inline poly _MultiBuild(poly Q){
	const int n=Q.size(),lgm=__lg(max(1,n-1))+1,m=1<<lgm;
	Tr.assign((lgm+1)*m*2,1);
	for(int i=0;i<n;++i)Tr[lgm*m*2+i*2]=Mod+1-Q[i],Tr[lgm*m*2+i*2+1]=Mod-1-Q[i];
	for(int k=lgm-1,L=2;~k;--k,L*=2)
		for(int i=0;i<(1<<k);++i){
			auto p=Tr.begin()+(k*m*2+i*L*2);
			auto ls=Tr.begin()+((k+1)*m*2+i*L*2),rs=ls+L;
			for(int j=0;j<L;++j)p[j]=(LL)ls[j]*rs[j]%Mod;
			poly A(p,p+L);
			IDFT(A);
			if((i+1)*L<=n)(A[0]-=2)<0&&(A[0]+=Mod);
			if(k){
				const int t=grt[L/2];
				for(int j=0,w=1;j<L;++j)A[j]=(LL)A[j]*w%Mod,w=(LL)w*t%Mod;
				DFT(A);
			}
			copy(A.begin(),A.end(),p+L);
		}
	Q.assign(Tr.begin()+m,Tr.begin()+m*2);
	if(n==m)++Q[0],Q.emplace_back(1);
	return Q.resize(n+1),Q;
}
inline poly _MultiEval(poly P,poly Q){
	const int n=Q.size()-1,lgm=__lg(max(1,n-1))+1,m=1<<lgm;
	reverse(Q.begin(),Q.end());
	const int pn=P.size();
	reverse(P.begin(),P.end());
	Q.resize(pn),P=Mul(P,Inv(Q)),P.resize(pn);
	if(pn>n)P.erase(P.begin(),P.end()-n);
	reverse(P.begin(),P.end());
	P.resize(m);
	for(int k=0,L=m;(1<<k)<m;++k,L/=2){
		poly X(L),Y(L);
		for(int i=0;i<(1<<k);++i){
			auto W=P.begin()+i*L;
			auto ls=Tr.begin()+((k+1)*m*2+i*L*2),rs=ls+L;
			DFT(P.begin()+i*L,L);
			for(int j=0;j<L;++j)X[j]=(LL)W[j]*rs[j]%Mod,Y[j]=(LL)W[j]*ls[j]%Mod;
			IDFT(X),IDFT(Y);
			const int nl=max(min(i*L+L/2,n)-i*L,0);
			const int nr=max(min((i+1)*L,n)-i*L-L/2,0);
			copy_n(X.begin()+nr,L/2,P.begin()+i*L);
			copy_n(Y.begin()+nl,L/2,P.begin()+i*L+L/2);
		}
	}
	return P.resize(n),P;
}
inline poly MultiEval(poly P,poly Q){
	return _MultiEval(P,_MultiBuild(Q));
}
inline poly Interpolation(poly P,poly Q){
	P=_MultiBuild(P),P=_MultiEval(Direv(P),P);
	const int n=Q.size(),lgm=__lg(max(1,n-1))+1,m=1<<lgm;
	Q.resize(m*2);
	for(int i=n;i--;)Q[i*2]=Q[i*2+1]=qpow(P[i],Mod-2,Q[i]);
	for(int k=lgm-1,L=2;~k;--k,L*=2)
		for(int i=0;i<(1<<k);++i){
			auto p=Q.begin()+i*L*2;
			auto ls=Tr.begin()+((k+1)*m*2+i*L*2),rs=ls+L;
			for(int j=0;j<L;++j)p[j]=p[j+L]=((LL)p[j]*rs[j]+(LL)p[j+L]*ls[j])%Mod;
			if(k){
				IDFT(p+L,L);
				const int t=grt[L/2];
				for(int j=0,w=1;j<L;++j)p[L+j]=(LL)p[L+j]*w%Mod,w=(LL)w*t%Mod;
				DFT(p+L,L);
			}
		}
	return Q.resize(m),IDFT(Q),Q.resize(n),Q;
}
inline poly ChirpZ(poly P,int X,int m){
	if(!X){
		poly Q(m,Eval(P,0));
		return Q[0]=Eval(P,1),Q;
	}
	const int n=P.size(),iX=qpow(X,Mod-2);
	poly pwX(n+m-1,1),ipwX(n+m-1,1),pwXX(n+m-1,1),ipwXX(n+m-1,1);
	for(int i=0;i+1<n+m;++i)
		pwX[i+1]=(LL)pwX[i]*X%Mod,ipwX[i+1]=(LL)ipwX[i]*iX%Mod,
		pwXX[i+1]=(LL)pwXX[i]*pwX[i]%Mod,ipwXX[i+1]=(LL)ipwXX[i]*ipwX[i]%Mod;
	for(int i=0;i<n;++i)P[i]=(LL)P[i]*ipwXX[i]%Mod;
	poly Q=MulT(pwXX,P);
	Q.resize(m);
	for(int i=0;i<m;++i)Q[i]=(LL)Q[i]*ipwXX[i]%Mod;
	return Q;
}
inline poly ChirpZrev(poly P,int X){
	const int n=P.size();
	if(n<2)return P;
	const int iX=qpow(X,Mod-2);
	poly pwX(n+n-1,1),ipwX(n+n-1,1),pwXX(n+n-1,1),ipwXX(n+n-1,1);
	for(int i=0;i+1<n+n;++i)
		pwX[i+1]=(LL)pwX[i]*X%Mod,ipwX[i+1]=(LL)ipwX[i]*iX%Mod,
		pwXX[i+1]=(LL)pwXX[i]*pwX[i]%Mod,ipwXX[i+1]=(LL)ipwXX[i]*ipwX[i]%Mod;
	poly Q(n,1);
	for(int i=1;i<n;++i)Q[i]=(LL)(Mod+1-pwX[i])*Q[i-1]%Mod;
	const int t=(LL)(Mod+1-pwX[n])*Q[n-1]%Mod;
	Q=invLinear(Q);
	for(int i=0;i<n;++i)
		P[i]=(LL)(i&1?Mod-P[i]:P[i])*pwXX[n-1-i]%Mod*ipwXX[n-1]%Mod*Q[i]%Mod*Q[n-1-i]%Mod*ipwXX[i]%Mod;
	P=MulT(pwXX,P),P.resize(n);
	for(int i=0;i<n;++i)P[i]=(LL)P[i]*ipwXX[i]%Mod;
	poly H(n,1);
	for(int i=1;i<n;++i)
		H[i]=(LL)(i&1?Mod-t:t)*pwXX[i]%Mod*Q[i]%Mod*Q[n-i]%Mod;
	P=Mul(P,H),P.resize(n),reverse(P.begin(),P.end());
	return P;
}
inline poly Sin(poly P){
	P=Mulx(P,img);
	const poly Q=Exp(P);
	for(int i=(P=Inv(Q)).size();i--;)
		((P[i]-=Q[i])&1)&&(P[i]+=Mod),(P[i]=(LL)(P[i]>>1)*img%Mod)<0&&(P[i]+=Mod);
	return P;
}
inline poly Cos(poly P){
	P=Mulx(P,img);
	const poly Q=Exp(P);
	for(int i=(P=Inv(Q)).size();i--;)
        ((P[i]+=Q[i])&1)&&(P[i]-=Mod),((P[i]>>=1)<0)&&(P[i]+=Mod);
	return P;
}
inline poly Tan(poly P){
	const int n=P.size();
	return P=Mul(Sin(P),Inv(Cos(P))),P.resize(n),P;
}
inline poly Asin(poly P){
	const int n=P.size();
	poly Q=Neg(Mul(P,P));
	Q[0]=1,Q=Sqrt(Q),Q.resize(n);
	for(int i=n;i--;)P[i]=((LL)img*P[i]+Q[i])%Mod;
	P=Ln(P);
	for(int i=n;i--;)P[i]=(LL)(Mod-img)*P[i]%Mod;
	return P;
}
inline poly Atan(poly P){
	const int n=P.size();
	P=Mulx(P,img);
	P[0]=1;
	poly Q=Neg(Ln(P));
	P[0]=1,P=Ln(P);
	for(int i=n;i--;)
        ((P[i]-=Q[i])&1)&&(P[i]+=Mod),(P[i]=(LL)(P[i]>>1)*img%Mod)<0&&(P[i]+=Mod);
	return P;
}
inline poly Acos(poly P){
	const int n=P.size();
	poly Q=Mul(P,P);
	Q[0]=1,Q=Sqrt(Q);
	for(int i=n;i--;)P[i]=(LL)img*(P[i]+Q[i])%Mod;
	P=Ln(P);
	for(int i=n;i--;)P[i]=(LL)(Mod-img)*P[i]%Mod;
	return P;
}
inline int ConstHomogeneousLinear(poly P,poly A,LL k){
	const int n=P.size();
	P=Neg(P),P.insert(P.begin(),1);
	A=Mul(P,A),A.resize(n);
	const int m=2<<__lg(n);
	P.resize(m*2),A.resize(m*2);
	DFT(P),DFT(A);
	for(;k>=m;k>>=1){
		if(k&1){
			for(int i=0;i<m*2;i+=2){
				if((A[i/2]=((LL)A[i]*P[i+1]-(LL)A[i+1]*P[i])%Mod*igrt[i/2]%Mod)<0)A[i/2]+=Mod;
				if(A[i/2]&1)A[i/2]+=Mod;
				A[i/2]>>=1,P[i/2]=(LL)P[i]*P[i+1]%Mod;
			}
		}
		else{
			for(int i=0;i<m*2;i+=2){
				if((A[i/2]=((LL)A[i]*P[i+1]+(LL)A[i+1]*P[i])%Mod)&1)A[i/2]+=Mod;
				A[i/2]>>=1,P[i/2]=(LL)P[i]*P[i+1]%Mod;
			}
		}
		const int t=grt[m/2];
		copy_n(A.begin(),m,A.begin()+m),IDFT(A.begin()+m,m);
		copy_n(P.begin(),m,P.begin()+m),IDFT(P.begin()+m,m);
		for(int i=m,w=1;i<m*2;++i)A[i]=(LL)A[i]*w%Mod,P[i]=(LL)P[i]*w%Mod,w=(LL)w*t%Mod;
		DFT(A.begin()+m,m);
		DFT(P.begin()+m,m);
	}
	IDFT(P),P.resize(m),P=Inv(P),P.resize(m*2),DFT(P);
	for(int i=0;i<m*2;++i)A[i]=(LL)A[i]*P[i]%Mod;
	return IDFT(A),A[k];
}
inline int ConstNonHomogeneousLinear(poly P,poly Q,poly A,LL k){
	const int m=A.size(),n=Q.size();
	P.insert(P.begin(),0);
	poly C(n);iota(C.begin(),C.end(),m);
	C=MultiEval(Q,C);
	poly B=Mul(P,A);B.resize(m);
	for(int i=0;i<m;++i)(B[i]=A[i]-B[i])<0&&(B[i]+=Mod);
	B.insert(B.end(),C.begin(),C.end());
	P[0]=Mod-1,P=Neg(P);
	A=P,A.resize(n+m+1),A=Mul(B,Inv(A)),A.resize(n+m);
	C.resize(n+1);
	for(int i=0;i<=n;++i)C[i]=(n-i)&1?Binom(n,i):Mod-Binom(n,i);
	return ConstHomogeneousLinear(Mul(P,C),A,k);
}
inline vector<poly>ODEAM(vector<poly>P){
	const int n=P.size()-1;
	vector<poly>F;
	for(int i=0;i<(int)P.size();++i)
		for(int j=0;j<(int)P[i].size();++j){
			poly R({P[i][j]});
			for(int k=-j+1;k<=i-j;++k)R=Mul(R,{k<0?k+Mod:k,1});
			if(j-i+n>=F.size())F.resize(j-i+n+1);
			F[j-i+n]=Add(F[j-i+n],R);
		}
	while(Empty(F.back()))F.pop_back();
	const int m=F.size()-1-n;
	for(poly&i:F)i=Comp(i,{m>0?Mod-m:-m,1});
	reverse(F.begin(),F.end());
	while(Empty(F.back()))F.pop_back();
	return F;
}
inline int InterRecursive(vector<poly>P,poly A,int n){
	const int m=A.size();int D=0;
	if(n<m)return A[n];
	n-=m-1;
	for(poly&i:P)D=max(D,(int)i.size());
	for(poly&i:P)i.resize(D);
	--D;
	const int B=ceil(sqrtl(1.L*n/D))+1,C=(n-B)/B,iB=qpow(B,Mod-2);
	const auto MatP=[&](const int&x){
		Mat z(m,Vec(m));
		int v=Eval(P[0],x+m);
		for(int i=0;i+1<m;++i)z[i+1][i]=v;
		for(int i=0;i<m;++i)z[i][m-1]=Mod-Eval(P[m-i],x+m);
		return z;
	};
	const auto solve=[&](vector<Mat>f,vector<int>g,int X,bool op){
		const int n=f.size()-1,k=n+1;
		Init(n);
		poly frcm(n+1,1),ivfm(n+1);
		for(int i=0;i<=n;++i)
			frcm[0]=(LL)frcm[0]*(X-n+i+Mod)%Mod,
			ivfm[i]=(LL)ivf[i]*ivf[n-i]%Mod;
		poly pre(k+2,1),suf(k+2,1),qinv(k+1);
		for(int i=1;i<=k;++i)pre[i]=(LL)pre[i-1]*(X-n+i-1+Mod)%Mod;
		for(int i=k;i>=1;--i)suf[i]=(LL)suf[i+1]*(X-n+i-1+Mod)%Mod;
		const int s=qpow(pre[k],Mod-2);
		for(int i=1;i<=k;++i)qinv[i]=(LL)s*pre[i-1]%Mod*suf[i+1]%Mod;
		for(int i=1;i<=n;++i)frcm[i]=(LL)frcm[i-1]*(X+i)%Mod*qinv[i]%Mod;
		poly F=qinv;F.erase(F.begin());
		poly Q(n+1);
		for(int i=0;i<=n;++i)Q[i]=(LL)ivfm[i]*((n-i)&1?Mod-g[i]:g[i])%Mod;
		Q=Mul(F,Q);
		for(int i=0;i<=n;++i)g[i]=(LL)Q[i+n]*frcm[i]%Mod;
		if(op)for(int i=0;i<m;++i)for(int j=0;j<m;++j){
			Q.resize(n+1);
			for(int t=0;t<=n;++t)Q[t]=(LL)ivfm[t]*((n-t)&1?Mod-f[t][i][j]:f[t][i][j])%Mod;
			Q=Mul(F,Q);
			for(int t=0;t<=n;++t)f[t][i][j]=(LL)Q[t+n]*frcm[t]%Mod;
		}
		return make_pair(f,g);
	};
	vector<Mat>f(D+1);vector<int>g(D+1);
	for(int i=0;i<=D;++i)f[i]=MatP(i*B),g[i]=Eval(P[0],i*B);
	for(int _=__lg(B),R=1;_--;){
		auto [nf,ng]=solve(f,g,D*R+1,1);
		f.insert(f.end(),nf.begin(),nf.end()),f.pop_back();
		g.insert(g.end(),ng.begin(),ng.end()),g.pop_back();
		tie(nf,ng)=solve(f,g,(LL)R*iB%Mod,1);
		for(int i=0;i<=D*R*2;++i)f[i]=f[i]*nf[i],g[i]=(LL)g[i]*ng[i]%Mod;
		R*=2;
		if(B>>_&1){
			for(int i=D*R+1;i<=D*(R+1);++i){
				f.emplace_back(MatP(i*B)),g.emplace_back(Eval(P[0],i*B));
				for(int j=1;j<R;++j)f[i]=f[i]*MatP(i*B+j),g[i]=(LL)g[i]*Eval(P[0],i*B+j)%Mod;
			}
			for(int i=0;i<=D*(R+1);++i)
				f[i]=f[i]*MatP(i*B+R),g[i]=(LL)g[i]*Eval(P[0],i*B+R)%Mod;
			++R;
		}
	}
	tie(f,g)=solve(f,g,(LL)m*iB%Mod,0);
	Mat X=f[0];int Y=g[0];
	for(int i=1;i<=C;++i)X=X*f[i],Y=(LL)Y*g[i]%Mod;
	for(int i=(n/B)*B;i<n;++i)X=X*MatP(i),Y=(LL)Y*Eval(P[0],i+m)%Mod;
	int ans=0;
	for(int i=0;i<m;++i)ans=(ans+(LL)A[i]*X[i][m-1])%Mod;
	return qpow(Y,Mod-2,ans);
}
inline Mat2 operator*(const Mat2&x,const Mat2&y){
	return Mat2(
		Add_Empty(Mul(get<0>(x),get<0>(y)),Mul(get<1>(x),get<2>(y))),
		Add_Empty(Mul(get<0>(x),get<1>(y)),Mul(get<1>(x),get<3>(y))),
		Add_Empty(Mul(get<2>(x),get<0>(y)),Mul(get<3>(x),get<2>(y))),
		Add_Empty(Mul(get<2>(x),get<1>(y)),Mul(get<3>(x),get<3>(y)))
	);
}
inline Vec2 operator*(const Mat2&x,const Vec2&y){
	return Vec2(
		Add_Empty(Mul(get<0>(x),get<0>(y)),Mul(get<1>(x),get<1>(y))),
		Add_Empty(Mul(get<2>(x),get<0>(y)),Mul(get<3>(x),get<1>(y)))
	);
}
inline Mat2 Halfgcd(Vec2 P){
	const int m=get<0>(P).size()/2;
	if((int)get<1>(P).size()<=m)return Mat2(poly({1}),poly(),poly(),poly({1}));
	Mat2 Q=Halfgcd(Vec2(poly(get<0>(P).begin()+m,get<0>(P).end()),poly(get<1>(P).begin()+m,get<1>(P).end())));
	P=Q*P;
	if((int)get<1>(P).size()<=m)return Q;
	poly W=Div(get<0>(P),get<1>(P));
	Mat2 A(poly(),poly({1}),poly({1}),Neg(W));
	Q=A*Q,P=A*P;
	if((int)get<1>(P).size()<=m)return Q;
	const int k=m+m+1-get<0>(P).size();
	return Halfgcd(Vec2(poly(get<0>(P).begin()+k,get<0>(P).end()),poly(get<1>(P).begin()+k,get<1>(P).end())))*Q;
}
inline Mat2 Cogcd(Vec2 P){
	Mat2 Q=Halfgcd(P);
	P=Q*P;
	if(get<1>(P).empty())return Q;
	poly W=Div(get<0>(P),get<1>(P));
	Mat2 A(poly(),poly({1}),poly({1}),Neg(W));
	Q=A*Q,P=A*P;
	if(get<1>(P).empty())return Q;
	return Cogcd(P)*Q;
}
inline tuple<poly,poly,poly>Exgcd(poly P,poly Q){
	Empty(P),Empty(Q);
	poly W=Div(P,Q);
	Mat2 A(poly(),poly({1}),poly({1}),Neg(W));
	Vec2 C=A*Vec2(P,Q);
	if(!get<1>(C).empty())A=Cogcd(C)*A;
	poly D=Add_Empty(Mul(P,get<0>(A)),Mul(Q,get<1>(A)));
	const int v=qpow(D.back(),Mod-2);
	return make_tuple(Mulx(D,v),Mulx(get<0>(A),v),Mulx(get<1>(A),v));
}
inline poly Gcd(poly P,poly Q){
	Empty(P),Empty(Q);
	if(P.empty())return Q;
	if(Q.empty())return P;
	return get<0>(Exgcd(P,Q));
}
inline pair<poly,poly>BerlekampMassey(poly P){
	const int n=P.size(),m=(n+1)/2+1;
	poly M(n+1);M.back()=1;
	Mat2 Q=Halfgcd(Vec2(M,P));
	Vec2 A=Q*Vec2(M,P);
	while((int)max(get<3>(Q).size(),get<1>(A).size()+1)>m){
		poly W=Div(get<0>(A),get<1>(A));
		Mat2 B(poly(),poly({1}),poly({1}),Neg(W));
		Q=B*Q,A=B*A;
	}
	poly X=get<3>(Q),Y=get<1>(A);
	const int v=qpow(X[0],Mod-2);
	X=Mulx(X,v),Y=Mulx(Y,v);
	X.erase(X.begin()),X=Neg(X);
	if(X.size()>Y.size())Y.resize(X.size());
	if(X.size()<Y.size())X.resize(Y.size());
	P.resize(Y.size());
	return make_pair(P,X);
}
inline poly Modinv(poly P,poly Q){
	Empty(P),Empty(Q);
	auto [D,W,_]=Exgcd(P,Q);
	if(D.size()>1)return poly({-1});
	return W;
}
inline void FindingRoot_solve(poly P,poly&W){
	if(P.size()==1)return;
	if(P.size()==2){
		W.emplace_back(qpow(P[1],Mod-2,Mod-P[0]));
		return;
	}
	poly Q({uniform_int_distribution<int>(0,Mod-1)(rng),1});
	Q=ModPow(Q,Mod>>1,P);
	if(Empty(Q))return FindingRoot_solve(P,W);
	(--Q[0])<0&&(Q[0]+=Mod);
	Q=Gcd(P,Q),P=Div(P,Q);
	FindingRoot_solve(P,W),FindingRoot_solve(Q,W);
}
inline poly FindingRoot(poly P){
	Empty(P);
	poly Q=ModPow(poly({0,1}),Mod,P);
	if(Q.size()<2)Q.resize(2);
	(--Q[1])<0&&(Q[1]+=Mod);
	P=Gcd(P,Q);
	poly W;
	FindingRoot_solve(P,W);
	sort(W.begin(),W.end());
	return W;
}
inline poly FirstStirLingLine(int n){
	if(!n)return poly({1});
	poly P({0,1});
	for(int i=__lg(n);i--;){
		P=Mul(P,Shift(P,Mod-(n>>(i+1))));
		if(n>>i&1)P=Mul(P,poly({Mod-((n>>i)-1),1}));
	}
	return P;
}
inline poly FirstStirLingRow(int n,int k){
	Init(n);
	poly P(n-k+1);
	for(int i=0;i<=n-k;++i)P[i]=inv[i+1];
	P=Qpow(P,k);
	for(int i=0;i<=n-k;++i)
		P[i]=(LL)(i&1?Mod-P[i]:P[i])*ivf[k]%Mod*frc[i+k]%Mod;
	return P;
}
inline poly SecondStirLingLine(int n){
	Init(n);
	poly P(n+1),Q(n+1);
	for(int i=0;i<=n;++i)P[i]=qpow(i,n,ivf[i]),Q[i]=(i&1?Mod-ivf[i]:ivf[i]);
	P=Mul(P,Q);
	return P.resize(n+1),P;
}
inline poly SecondStirLingRow(int n,int k){
	if(!k){
		poly P(n+1);
		return P[0]=1,P;
	}
	poly P({Mod-1,1});
	for(int i=__lg(k);i--;){
		P=Mul(P,Shift(P,Mod-(k>>(i+1))));
		if(k>>i&1)P=Mul(P,poly({Mod-(k>>i),1}));
	}
	reverse(P.begin(),P.end()),P.resize(n-k+1),P=Inv(P);
	return P;
}
inline poly Bell(int n){
	Init(n);
	poly P(n+1);
	for(int i=1;i<=n;++i)P[i]=ivf[i];
	P=Exp(P);
	for(int i=1;i<=n;++i)P[i]=(LL)P[i]*frc[i]%Mod;
	return P;
}
inline poly Bernoulli(int n){
	Init(n+1);
	poly P(n+1);
	for(int i=0;i<=n;++i)P[i]=ivf[i+1];
	P=Inv(P);
	for(int i=1;i<=n;++i)P[i]=(LL)P[i]*frc[i]%Mod;
	return P;
}
inline poly Partition(int n){
	poly P(n+1);
	P[0]=1;
	for(int i=1;;++i){
		int j=i*(3*i-1)/2;
		if(j>n)break;
		if(i&1)(--P[j])<0&&(P[j]+=Mod);else ++P[j];
		if(i+j<=n)if(i&1)(--P[i+j])<0&&(P[i+j]+=Mod);else ++P[i+j];
	}
	P=Inv(P);
	return P.resize(n+1),P;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
	int d;LL k;cin>>d>>k;
	poly A(d);for(auto&i:A)cin>>i;
	poly P(d);for(auto&i:P)cin>>i;
	cout<<ConstHomogeneousLinear(P,A,k)<<'\n';
    return 0;
}