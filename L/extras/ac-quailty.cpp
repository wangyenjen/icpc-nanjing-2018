#include<bits/stdc++.h>
using namespace std;
const int MAXN=5005;
const int INF=0x3f3f3f3f;
inline void upd(int &x,int y)
{
    (x>y) && (x=y);
}
int a[MAXN],dp[2][MAXN][3][4];
int main()
{
    int n,x,y;
    scanf("%d%d%d",&n,&x,&y);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int m=0,f=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]==x)a[i]=0,f|=1;
        else if(a[i]==y)a[i]=1,f|=2;
        else a[i]=2,m++;
    }
    if(f!=3)return 0*printf("0\n");
    if(m==0)return 0*printf("-1\n");
    int now=0,la=1;
    memset(dp[now],INF,sizeof(dp[now]));
    dp[now][0][2][0]=0;
    for(int i=1;i<=n;i++)
    {
        swap(now,la);
        memset(dp[now],INF,sizeof(dp[now]));
        for(int j=0;j<=m;j++)
            for(int k=0;k<3;k++)
                for(int l=0;l<4;l++)if(dp[la][j][k][l]<INF)
                {
                    ///insert a '2' between a[i-1] and a[i]
                    {
                        ///take away a[i]
                        if(k==2)upd(dp[now][j+1][2][l|1],dp[la][j][k][l]+1+(a[i]!=2)),upd(dp[now][j+1][2][l|2],dp[la][j][k][l]+1+(a[i]!=2));
                        else upd(dp[now][j+1][2][l],dp[la][j][k][l]+1+(a[i]!=2));
                        ///keep a[i]
                        if(k==2)upd(dp[now][j+1+(a[i]==2)][a[i]][3],dp[la][j][k][l]+1);
                        else
                        {
                            if(a[i]==2)upd(dp[now][j+2][2][l|1],dp[la][j][k][l]+1),upd(dp[now][j+2][2][l|1],dp[la][j][k][l]+1);
                            else upd(dp[now][j+1][a[i]][l|(1<<a[i])],dp[la][j][k][l]+1);
                        }
                    }
                    ///or not
                    {
                        ///take away a[i]
                        upd(dp[now][j][k][l],dp[la][j][k][l]+(a[i]!=2));
                        ///keep a[i]
                        if(k==2 && a[i]==2)upd(dp[now][j+1][2][l|1],dp[la][j][k][l]),upd(dp[now][j+1][2][l|2],dp[la][j][k][l]);
                        else if(k+a[i]!=1)upd(dp[now][j+(a[i]==2)][a[i]][l|(a[i]<2 ? 1<<a[i] : 0)],dp[la][j][k][l]);
                    }
                }
    }
    int res=dp[now][m][0][3];
    res=min(res,dp[now][m][1][3]);
    res=min(res,dp[now][m][2][3]);
    res=min(res,dp[now][m][2][1]);
    res=min(res,dp[now][m][2][2]);
    printf("%d\n",res);
    return 0;
}

