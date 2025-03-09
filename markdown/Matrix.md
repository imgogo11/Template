### Matrix

```c++
using Matrix = vector<vector<ll>>;
Matrix trans(Matrix &A) {//矩阵转置。O(N²)
    int H=A.size();
    int W=A[0].size();
    Matrix ret(W,vector<ll>(H));
    for(int i=0;i<W;i++)
        for(int j=0;j<H;j++)
            ret[i][j]=A[j][i];
    return ret;
}
Matrix Add(Matrix &A,Matrix &B,bool minus=false) {// 矩阵加法。O(N²)
    assert(A.size()==B.size() && A[0].size()==B[0].size());
    int h=A.size(),w=A[0].size();
    Matrix C(h,vector<ll>(w));
    for(int i=0;i<h;i++) {
        for(int j=0;j<w;j++) {
            if(minus) {
                C[i][j]=A[i][j];
                C[i][j]=C[i][j]-B[i][j];
            }
            else {
                C[i][j]=A[i][j];
                C[i][j]=C[i][j]+B[i][j];
            }
        }
    }
    return C;
}
Matrix Sub(Matrix &A,Matrix &B)// 矩阵减法。O(N²)
{return Add(A, B, true);}
Matrix Mul(Matrix &A,Matrix &B) {// 矩阵乘法。O(N³)
    assert(A[0].size()==B.size());
    Matrix C(A.size(),vector<ll>(B[0].size()));
    for(int i=0;i<A.size();i++) {
        for(int k=0;k<B.size();k++) {
            for(int j=0;j<B[0].size();j++) {
                int a=A[i][k];
                C[i][j]+=a*B[k][j];
            }
        }
    }
    return C;
}
Matrix Pow(Matrix &A,ll K) {// 矩阵快速幂。O(N³logK)
    assert(A.size()==A[0].size());
    Matrix B(A.size(),vector<ll>(A.size()));
    for(int i=0;i<A.size();i++)
        B[i][i]=1;
    while(K) {
        if(K&1) B=Mul(B, A);
        A=Mul(A, A);
        K>>=1;
    }
    return B;
}
```

