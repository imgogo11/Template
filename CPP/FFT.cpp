using cp=complex<double>;
int rev[N],bit,tot,res[N];//N要开多项式最高项和的两倍，即2(n+m)
cp a[N],b[N];
void fft(cp a[],int inv) {
    for(int i=0;i<tot;i++) if (i<rev[i]) swap(a[i],a[rev[i]]);
    for(int k=1;k<tot;k*=2) {
        auto w1=cp(cos(PI/k),inv*sin(PI/k));
        for(int i=0;i<tot;i+=k*2) {
            auto wk=cp(1,0);
            for(int j=0;j<k;j++,wk=wk*w1) {
                auto x=a[i+j],y=wk*a[i+j+k];
                a[i+j]=x+y,a[i+j+k]=x-y;
            }
        }
    }
}
void mul(int n,int m) {
    while((1<<bit)<n+m+1) bit++;
    tot=1<<bit;
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1) | ((i&1)<<(bit-1));
    fft(a,1),fft(b,1);
    for(int i=0;i<tot;i++) a[i]=a[i]*b[i];
    fft(a,-1);
    for(int i=0;i<=n+m;i++) res[i]=(int)(a[i].real()/tot+0.5);
}