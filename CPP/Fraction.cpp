struct frac {
    ll x,y;
    frac(): x(0), y(1){}
    frac(ll x,ll y) {
        init(x,y);
    }
    void init(ll x,ll y) {
        ll g=abs(gcd(x,y));
        if(y<0) x*=-1,y*=-1;
        this->x=x/g;
        this->y=y/g;
    }
    long double val() {
        return 1.0L*x/y;
    }
    bool operator==(const frac &F) const {return x*F.y==F.x*y;}
    bool operator<(const frac &F) const {return x*F.y<F.x*y;}
    bool operator>(const frac &F) const {return x*F.y>F.x*y;}
    frac operator+(const frac &F) const {return frac(x*F.y+F.x*y,y*F.y);}
    frac operator-(const frac &F) const {return frac(x*F.y-F.x*y,y*F.y);}
    frac operator-() const {return frac(-1*x,y);}
    frac operator*(const frac &F) const {return frac(x*F.x,y*F.y);}
    frac operator/(const frac &F) const {return frac(x*F.y,y*F.x);}
    frac operator*=(frac F) {
        ll a=x*F.x,b=y*F.y,g=gcd(a,b);
        x=a/g,y=b/g;
        if(y<0) x*=-1,y*=-1;
        return *this;
    }
    frac operator/=(frac F) {
        ll a=x*F.y,b=y*F.x,g=gcd(a,b);
        x=a/g,y=b/g;
        if(y<0) x*=-1,y*=-1;
        return *this;
    }
    frac operator+=(frac F) {
        ll a=x*F.y+F.x*y,b=y*F.y,g=gcd(a,b);
        x=a/g,y=b/g;
        if(y<0) x*=-1,y*=-1;
        return *this;
    }
    frac operator-=(frac F) {
        ll a=x*F.y-F.x*y,b=y*F.y,g=gcd(a,b);
        x=a/g,y=b/g;
        if(y<0) x*=-1,y*=-1;
        return *this;
    }
};