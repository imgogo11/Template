vector<int> s(n);
for(int i=0;i<n;i++)
    cin>>s[i];
s.insert(s.end(),s.begin(),s.end());
int i=0,j=1;
while(j<n) {
    int k=0;
    while(k<n && s[i+k]==s[j+k])
        k++;
    if(s[i+k]>s[j+k]) i+=k+1;
    else j+=k+1;
    if(i==j) j++;
    if(i>j) swap(i,j);
}