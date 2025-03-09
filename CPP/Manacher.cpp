vector<int> manacher(const string &s)
{
    string t="#";
    for(char c : s)
        t+=c,t+='#';
    int n=t.size();
    vector<int> r(n);
    for(int i=0,j=0;i<n;i++)
    {
        if(2*j-i>=0 && j+r[j]>i)
            r[i]=min(r[2*j-i],j+r[j]-i);
        while (i-r[i]>=0 && i+r[i]<n && t[i-r[i]]==t[i+r[i]])
            r[i]+=1;
        if(i+r[i]>j+r[j])
            j=i;
    }
    return r;//不论i为奇偶,以该为中心的最长回文子串长度均为r[i]-1
}