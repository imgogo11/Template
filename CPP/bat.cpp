//A.cpp
freopen("input","r",stdin);
freopen("output","w",stdout);
//A__Good.cpp
freopen("input","r",stdin);
freopen("out","w",stdout);
//A__Generator.cpp
mt19937_64 rng{chrono::steady_clock::now().time_since_epoch().count()};
ll range(ll l,ll r)
{return rng()%(r+1-l)+l;}
freopen("input","w",stdout);
//A__Bat.cpp
int t=100;
while(t--) {
    system("T2__Generator.exe");
    system("T2.exe");
    system("T2__Good.exe");
    if(system("fc out output")) {
        puts("WA");
        return;
    }
}
puts("AC");


//bat.sh(linux)
g++ A.cc -o A
g++ naive.cc -o naive
g++ gen.cc -o gen
while true;do
    ./gen > 1.in
    ./naive <1.in >std.out
    ./A <1.in >1.out
    if diff 1.out std.out; then
        echo ac
    else
        echo wa
        break
    fi
done