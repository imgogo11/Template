int h[N],idx;
struct Chain{int to,w,ne;}e[M];
void add(int x,int y,int z)
{
    e[idx].to=y;//新边指向y点
    e[idx].w=z;//新边权值为z
    e[idx].ne=h[x];//新边指向x点之前的边
    h[x]=idx;//把新边给x点
    idx++;//创造下一条新边
}
for (int i=1;i<=n;i++)//遍历
{
    for(int j=h[i];~j;j=e[j].ne)
    {
        int to=e[j].to;//to为与i相连的点
        int val=e[j].w;//val为i与to的边权
    }
}