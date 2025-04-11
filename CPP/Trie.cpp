int t[N][65],cnt[N],idx;
int getnum(char x) {
    if(x>='A'&&x<='Z')
        return x-'A';
    else if(x>='a'&&x<='z')
        return x-'a'+26;
    else
        return x-'0'+52;
} 
void insert(string &str) {
    int p=0,len=str.size();
    for(int i=0;i<len;i++)
    {
        int c=getnum(str[i]);
        if(!t[p][c])
            t[p][c]=++idx;
        p=t[p][c];
        cnt[p]++;
    }
}
int find(string &str) {
    int p=0,len=str.size();
    for(int i=0;i<len;i++)
    {
        int c=getnum(str[i]);
        if(!t[p][c])
            return 0;
        p=t[p][c];
    }
    return cnt[p];
}