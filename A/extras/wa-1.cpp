#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    if(n==0)printf("Austin\n");
    else
    {
        for(int i=3;i<=1000001;i+=2)
            if(n==1LL*i*k-1)
                return 0*printf("Austin\n");
        printf("Adrien\n");
    }
    return 0;
}

