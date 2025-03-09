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
            mul(A, B);
            swap(A, tmp_mul);
        }
        mul(B, B);
        swap(B, tmp_mul);
        K>>=1;
    }
}
Matrix trans(Matrix &A)//矩阵转置。O(N²)
{
    int H=A.size();
    int W=A[0].size();
    Matrix ret(W,vector<ll>(H));
    for(int i=0;i<W;i++)
    {
        for(int j=0;j<H;j++)
            ret[i][j]=A[j][i];
    }
    return ret;
}
Matrix Add(Matrix &A,Matrix &B,bool minus=false)// 矩阵加法。O(N²)
{
    assert(A.size()==B.size() && A[0].size()==B[0].size());
    int h=A.size(),w=A[0].size();
    Matrix C(h,vector<ll>(w));
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            if(minus)
            {
                C[i][j]=A[i][j];
                C[i][j]=C[i][j]-B[i][j];
            }
            else
            {
                C[i][j]=A[i][j];
                C[i][j]=C[i][j]+B[i][j];
            }
        }
    }
    return C;
}
Matrix Sub(Matrix &A,Matrix &B)// 矩阵减法。O(N²)
{return Add(A, B, true);}
Matrix Mul(Matrix &A,Matrix &B)// 矩阵乘法。O(N³)
{
    assert(A[0].size()==B.size());
    Matrix C(A.size(),vector<ll>(B[0].size()));
    for(int i=0;i<A.size();i++)
    {
        for(int k=0;k<B.size();k++)
        {
            for(int j=0;j<B[0].size();j++)
            {
                int a=A[i][k];
                C[i][j]+=a*B[k][j];
            }
        }
    }
    return C;
}
Matrix Pow(Matrix &A,ll K)// 矩阵快速幂。O(N³logK)
{
    assert(A.size()==A[0].size());
    Matrix B(A.size(),vector<ll>(A.size()));
    for(int i=0;i<A.size();i++)
        B[i][i]=1;
    while(K)
    {
        if(K&1)
            B=Mul(B, A);
        A=Mul(A, A);
        K>>=1;
    }
    return B;
}