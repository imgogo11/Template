vector<int> zFunction(string &s) {
    int n=s.size();
    vector<int> z(n);
    z[0]=n;
    for (int i=1,j=1;i<n;i++)
    {
        z[i]=max(0,min(j+z[j]-i,z[i-j]));
        while(i+z[i]<n && s[z[i]]==s[i+z[i]])
            z[i]++;
        if(i+z[i]>j+z[j])
            j=i;
    }
    return z;
}
vector<int> zFunction(string &s,string &p,vector<int>& z) {
    int n=s.size(),m=p.size();
    vector<int> Z(n);
    Z[0]=0;
    for(int i=0,j=0;i<n;i++)
    {
        Z[i]=max(0,min(j+Z[j]-i,z[i-j]));
        while(i+Z[i]<n && Z[i]<m && p[Z[i]]==s[i+Z[i]])
            Z[i]++;
        if(i+Z[i]>j+Z[j])
            j=i;
    }
    return Z;
}


string a,b;
cin>>a>>b;
vector<int> z=zFunction(b);
vector<int> Z=zFunction(a,b,z);
for(int i=0;i<b.size();i++)
    cout<<z[i]<<" \n"[i+1==b.size()];
for(int i=0;i<a.size();i++)
    cout<<Z[i]<<" \n"[i+1==a.size()];
return 0;