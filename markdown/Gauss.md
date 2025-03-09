# 高斯消元

对于n元线性方程组$AX=\beta$解的情况：
若$R(A,\beta)=R(A)=r$,且$r=n$时,原方程有唯一解
若$R(A,\beta)=R(A)=r$,且$r<n$时,原方程有无穷多解
若$R(A,\beta) \neq R(A)$,原方程无解

```c++
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
```

矩阵的逆(高斯消元法)

```c++
using Matrix = vector<vector<Z>>;
Matrix tmp_mul,tmp_inv;
bool inv(Matrix &A) {
    // assert(A.size() && A.size()==A[0].size());
    int n=A.size(),cur_row=0;
    tmp_inv.assign(n,vector<Z>(n));
    for(int i=0;i<n;i++)
        tmp_inv[i][i]=1;
    for(int col=0;col<n;col++) {
        int row;
        for(row=cur_row;row<n;row++)
            if(A[row][col]!=0)
                break;
        if(row>=n || A[row][col]==0) {
            return false;
        }
        swap(A[row],A[cur_row]);
        swap(tmp_inv[row],tmp_inv[cur_row]);
        for(int k=n-1;k>=0;k--)
            tmp_inv[cur_row][k]/=A[cur_row][col];
        for(int k=n-1;k>=col;k--)// 注意循环顺序
            A[cur_row][k]/=A[cur_row][col];
        for(int i=0;i<n;i++) {
            if(i!=cur_row) {
                for(int k=n-1;k>=0;k--)
                    tmp_inv[i][k]-=tmp_inv[cur_row][k]*A[i][col];
                for(int k=n-1;k>=col;k--)// 注意循环顺序
                    A[i][k]-=A[cur_row][k]*A[i][col];
            }
        }
        cur_row++;
    }
    return true;
}
void mul(const Matrix &A,const Matrix &B) {// 矩阵乘法。O(N³)
    // assert(A.size() && A[0].size()==B.size() && B.size());
    tmp_mul.assign(A.size(),vector<Z>(B[0].size()));
    for(int i=0;i<A.size();i++) {
        for(int k=0;k<B.size();k++) {
            Z a=A[i][k];
            for(int j=0;j<B[0].size();j++)
                tmp_mul[i][j]+=a*B[k][j];
        }
    }
}
void power(Matrix &A,ll K) {// 矩阵快速幂。O(N³logK)
    // assert(A.size() && A.size()==A[0].size());
    Matrix B(A.size(),vector<Z>(A.size()));
    swap(A,B);
    for(int i=0;i<A.size();i++)
        A[i][i]=1;
    while(K) {
        if(K&1) {
            mul(A,B);
            swap(A,tmp_mul);
        }
        mul(B,B);
        swap(B,tmp_mul);
        K>>=1;
    }
}
```

