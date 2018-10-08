#include<bits/stdc++.h>
using namespace std;

typedef double db;

const int MAXN=105;

int n;

db x[MAXN],y[MAXN],z[MAXN];

db cal(db tx,db ty,db tz)
{
    db res=0;
    for(int i=1;i<=n;i++)
        res=max(res,sqrt((x[i]-tx)*(x[i]-tx)+(y[i]-ty)*(y[i]-ty)+(z[i]-tz)*(z[i]-tz)));
    return res;
}

db solve_z(db x,db y)
{
    db l=-100000,r=100000;
    for(int _=0;_<40;_++)
    {
        db m1=(5*l+4*r)/9;
        db m2=(4*l+5*r)/9;
        if(cal(x,y,m1)<cal(x,y,m2))r=m2;
        else l=m1;
    }
    return cal(x,y,(l+r)/2);
}

db solve_y(db x)
{
    db l=-100000,r=100000;
    for(int _=0;_<40;_++)
    {
        db m1=(5*l+4*r)/9;
        db m2=(4*l+5*r)/9;
        if(solve_z(x,m1)<solve_z(x,m2))r=m2;
        else l=m1;
    }
    return solve_z(x,(l+r)/2);
}

db solve_x()
{
    db l=-100000,r=100000;
    for(int _=0;_<40;_++)
    {
        db m1=(5*l+4*r)/9;
        db m2=(4*l+5*r)/9;
        if(solve_y(m1)<solve_y(m2))r=m2;
        else l=m1;
    }
    return solve_y((l+r)/2);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf%lf",&x[i],&y[i],&z[i]);
    printf("%.15f\n",solve_x());
    return 0;
}

