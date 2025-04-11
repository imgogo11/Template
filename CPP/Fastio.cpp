#include<bits/stdc++.h>
using namespace std;
constexpr int SIZE=1<<23;
char buf[SIZE],*p_1=buf,*p_2=buf,pbuf[SIZE],*p_p=pbuf;
#define getchar() (p_1==p_2&&(p_2=(p_1=buf)+fread(buf,1,SIZE,stdin),p_1==p_2)?EOF:*p_1++)
#define putchar(c) (p_p-pbuf==SIZE?(fwrite(pbuf,1,SIZE,stdout),p_p=pbuf,*p_p++=c):*p_p++=c)
inline int read() {
	int x=0,f=1;char c=getchar();
	while (c<'0'||c>'9') f=(c=='-'?-1:f),c=getchar();
	while (c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
inline void write(long long x) {
	if (x<0) putchar('-'),x=-x;
	int out[22],cnt=0;
	do out[++cnt]=(int)(x%10),x/=10;while (x);
	for (int i=cnt;i>=1;i--) putchar((char)(out[i]^48));
	return;
}
int main() {
    int n;
    n=read();
    write(n);
    fwrite(pbuf,1,p_p-pbuf,stdout);
    return 0;
}
// class fastIO
// {
// private:
//     char ibuf[50007], *p1 = ibuf, *p2 = ibuf, obuf[50007], *p3 = obuf, sta[50];
//     bool file_end = false;
//     char get()
//     {
//         return p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 50007, stdin), p1 == p2) ? (file_end = true), char(EOF)
//                                                                                        : *p1++;
//     }
//     void put(const char x)
//     {
//         p3 - obuf < 50007 ? *p3++ = x : (fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf, *p3++ = x);
//     }
 
// public:
//     explicit operator bool() { return !file_end; }
//     size_t flush()
//     {
//         size_t f = fwrite(obuf, p3 - obuf, 1, stdout);
//         p3 = obuf;
//         *p3 = 0;
//         return f;
//     }
//     fastIO &operator>>(char &t)
//     {
//         for (t = get(); !isgraph(t); t = get())
//             ;
//         return *this;
//     }
//     template <typename any>
//     typename enable_if<is_same<any, char>::value, any>::type tpval()
//     {
//         char t;
//         for (t = get(); !isgraph(t); t = get())
//             ;
//         return t;
//     }
//     fastIO &operator>>(char *t)
//     {
//         char c;
//         for (c = get(); !isgraph(c); c = get())
//             ;
//         for (; isgraph(c); c = get())
//             *t = c, t++;
//         *t = 0;
//         return *this;
//     }
//     fastIO &operator>>(string &t)
//     {
//         t.clear();
//         char c;
//         for (c = get(); !isgraph(c); c = get())
//             ;
//         for (; isgraph(c); c = get())
//             t += c;
//         return *this;
//     }
//     template <typename any>
//     typename enable_if<is_same<any, string>::value, any>::type tpval()
//     {
//         string t;
//         char c;
//         for (c = get(); !isgraph(c); c = get())
//             ;
//         for (; isgraph(c); c = get())
//             t += c;
//         return t;
//     }
//     template <typename any>
//     typename enable_if<
//         (is_signed<any>::value && is_integral<any>::value && !is_same<any, char>::value) ||
//             is_same<any, __int128_t>::value,
//         fastIO>::type &
//     operator>>(any &t)
//     {
//         t = 0;
//         bool y = 0;
//         char c = get();
//         for (; !isdigit(c); c = get())
//             if (c == 45)
//                 y = true;
//         for (; isdigit(c); c = get())
//             t = t * 10 + c - 48;
//         if (y == 1)
//             t = -t;
//         return *this;
//     }
//     template <typename any>
//     typename enable_if<
//         (is_signed<any>::value && is_integral<any>::value && !is_same<any, char>::value) ||
//             is_same<any, __int128_t>::value,
//         any>::type
//     tpval()
//     {
//         any t = 0;
//         bool y = 0;
//         char c = get();
//         for (; !isdigit(c); c = get())
//             if (c == 45)
//                 y = true;
//         for (; isdigit(c); c = get())
//             t = t * 10 + c - 48;
//         if (y == 1)
//             t = -t;
//         return t;
//     }
//     template <typename any>
//     typename enable_if<
//         (is_unsigned<any>::value && is_integral<any>::value && !is_same<any, char>::value) ||
//             is_same<any, __uint128_t>::value,
//         fastIO>::type &
//     operator>>(any &t)
//     {
//         t = 0;
//         char c = get();
//         for (; !isdigit(c); c = get())
//             ;
//         for (; isdigit(c); c = get())
//             t = t * 10 + c - 48;
//         return *this;
//     }
//     template <typename any>
//     typename enable_if<
//         (is_unsigned<any>::value && is_integral<any>::value && !is_same<any, char>::value) ||
//             is_same<any, __uint128_t>::value,
//         any>::type
//     tpval()
//     {
//         any t = 0;
//         char c = get();
//         for (; !isdigit(c); c = get())
//             ;
//         for (; isdigit(c); c = get())
//             t = t * 10 + c - 48;
//         return t;
//     }
//     template <typename any1, typename any2>
//     fastIO &operator>>(pair<any1, any2> &t) { return *this >> t.first >> t.second; }
//     template <typename any1, typename any2>
//     pair<any1, any2> tpval() { return pair<any1, any2>(tpval<any1>(), tpval<any2>()); }
//     template <typename any>
//     fastIO &read(any &t) { return *this >> t; }
//     fastIO &read(char *t)
//     {
//         char c;
//         for (c = get(); !isgraph(c); c = get())
//             ;
//         for (; isgraph(c); c = get())
//             *t = c, t++;
//         *t = 0;
//         return *this;
//     }
//     template <typename any, typename... args>
//     fastIO &read(any &t1, args &...t2) { return (*this >> t1).read(t2...); }
//     fastIO &operator<<(const char t)
//     {
//         put(t);
//         return *this;
//     }
//     fastIO &operator<<(const char *t)
//     {
//         for (; *t; t++)
//             put(*t);
//         return *this;
//     }
//     fastIO &operator<<(const string &t)
//     {
//         for (const char it : t)
//             put(it);
//         return *this;
//     }
//     template <typename any>
//     typename enable_if<
//         (is_signed<any>::value && is_integral<any>::value && !is_same<any, char>::value) ||
//             is_same<any, __int128_t>::value,
//         fastIO>::type &
//     operator<<(any t)
//     {
//         if (!t)
//         {
//             put(48);
//             return *this;
//         }
//         int len = 0;
//         if (t < 0)
//             t = -t, put(45);
//         while (t)
//             sta[len++] = char(t % 10 + 48), t /= 10;
//         while (len--)
//             put(sta[len]);
//         return *this;
//     }
//     template <typename any>
//     typename enable_if<
//         (is_unsigned<any>::value && is_integral<any>::value && !is_same<any, char>::value) ||
//             is_same<any, __uint128_t>::value,
//         fastIO>::type &
//     operator<<(any t)
//     {
//         if (!t)
//         {
//             put(48);
//             return *this;
//         }
//         int len = 0;
//         while (t)
//             sta[len++] = char(t % 10 + 48), t /= 10;
//         while (len--)
//             put(sta[len]);
//         return *this;
//     }
//     template <typename any1, typename any2>
//     fastIO &operator<<(const pair<any1, any2> &t) { return *this << t.first << ' ' << t.second; }
//     template <typename any>
//     fastIO &write(const any &t) { return *this << t; }
//     template <typename any, typename... args>
//     fastIO &write(const any &t1, const args &...t2) { return (*this << t1).write(t2...); }
//     ~fastIO() { fwrite(obuf, p3 - obuf, 1, stdout); }
// } FastIO;
// // #ifdef ONLINE_JUDGE
// #define cin FastIO
// #define cout FastIO
// // #endif