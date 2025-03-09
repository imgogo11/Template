int check=0;//0唯一解   1无穷解    2无解
void Gauss(Matrix &a) {//O(N^3)
    int n=a.size(),m=a[0].size(),cur_row=0;
    for(int col=0;col<min(n,m);col++) {
        int row;
        for(row=cur_row;row<n;row++) if(a[row][col]) break;
        if(row>=n || a[row][col]==0) {
            check=1;
            continue;
        }
        swap(a[row],a[cur_row]);
        for(int k=m-1;k>=col;k--)// 注意循环顺序
            a[cur_row][k]/=a[cur_row][col];
        for(int i=0;i<n;i++) {
            if(i!=cur_row) {
                for(int k=m-1;k>=col;k--)// 注意循环顺序
                    a[i][k]-=a[cur_row][k]*a[i][col];
            }
        }
        cur_row++;
    }
    for(int i=n-1;i>=cur_row;i--) {
        if(abs(a[i][m-1])>eps) {
            check=2;
            break;
        }
    }
}