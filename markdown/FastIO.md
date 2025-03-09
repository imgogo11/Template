### FastIO

只能读写整数

```c++
const int SIZE=1<<23;
char buf[SIZE],*p_1=buf,*p_2=buf,pbuf[SIZE],*p_p=pbuf;
#define getchar() (p_1==p_2&&(p_2=(p_1=buf)+fread(buf,1,SIZE,stdin),p_1==p_2)?EOF:*p_1++)
#define putchar(c) (p_p-pbuf==SIZE?(fwrite(pbuf,1,SIZE,stdout),p_p=pbuf,*p_p++=c):*p_p++=c)
inline int read()
{
	int x=0,f=1;char c=getchar();
	while (c<'0'||c>'9') f=(c=='-'?-1:f),c=getchar();
	while (c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
inline void write(long long x)
{
	if (x<0) putchar('-'),x=-x;
	int out[22],cnt=0;
	do out[++cnt]=(int)(x%10),x/=10;while (x);
	for (int i=cnt;i>=1;i--) putchar((char)(out[i]^48));
	return;
}
int main()
{
    int n;
    n=read();
    write(n);
    fwrite(pbuf,1,p_p-pbuf,stdout);
}
```

