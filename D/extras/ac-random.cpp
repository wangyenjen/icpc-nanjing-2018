#include<bits/stdc++.h>
using namespace std;
#define For(i,n) for(int i=1;i<=n;i++)
#define Fork(i,k,n) for(int i=k;i<=n;i++)
#define ForkD(i,k,n) for(int i=n;i>=k;i--)
#define Rep(i,n) for(int i=0;i<n;i++)
#define ForD(i,n) for(int i=n;i>0;i--)
#define RepD(i,n) for(int i=n;i>=0;i--)
#define Forp(x) for(int p=pre[x];p;p=next[p])
#define Forpiter(x) for(int &p=iter[x];p;p=next[p])
#define Lson (o<<1)
#define Rson ((o<<1)+1)
#define MEM(a) memset(a,0,sizeof(a));
#define MEMI(a) memset(a,0x3f,sizeof(a));
#define MEMi(a) memset(a,128,sizeof(a));
#define MEMx(a,b) memset(a,b,sizeof(a));
#define INF (0x3f3f3f3f)
#define F (1000000007)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define vi vector<int>
#define pi pair<int,int>
#define SI(a) ((a).size())
#define Pr(kcase,ans) printf("Case #%d: %lld\n",kcase,ans);
#define PRi(a,n) For(i,n-1) cout<<a[i]<<' '; cout<<a[n]<<endl;
#define PRi2D(a,n,m) For(i,n) { \
						For(j,m-1) cout<<a[i][j]<<' ';\
						cout<<a[i][m]<<endl; \
						}
#pragma comment(linker, "/STACK:102400000,102400000")
#define ALL(x) (x).begin(),(x).end()
#define gmax(a,b) a=max(a,b);
#define gmin(a,b) a=min(a,b);
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
ll mul(ll a,ll b){return (a*b)%F;}
ll add(ll a,ll b){return (a+b)%F;}
ll sub(ll a,ll b){return ((a-b)%F+F)%F;}
void upd(ll &a,ll b){a=(a%F+b%F)%F;}
inline int read()
{
	int x=0,f=1; char ch=getchar();
	while(!isdigit(ch)) {if (ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}
#define MAXN (1010)
int n;
double x[MAXN],y[MAXN],z[MAXN];
double sqr(double x){return x*x;}
double dis(double a,double b,double c,int i) {
	return sqrt(sqr(a-x[i])+sqr(b-y[i])+sqr(c-z[i]) );
}
double get(double a,double b,double c) {
	double ans=0;
	For(i,n) {
		gmax(ans,dis(a,b,c,i));
	}
	return ans;
}
double hillclimbing() {
	double t=100000,ans=0,ansx=0,ansy=0,ansz=0;
	For(i,n) {
		ansx+=x[i];ansy+=y[i];ansz+=z[i];
	}
	ansx/=n,ansy/=n,ansz/=n;
	ans=get(0,0,0);
	while(t>1e-5) {
		double t1=rand()%201-100,t2=rand()%201-100,t3=rand()%201-100;
		t1/=100,t2/=100,t3/=100;
		t1=t1*t,t2=t2*t,t3=t3*t;
		double c=get(ansx+t1,ansy+t2,ansz+t3);
		if(c<ans) {
			ans=c;
			ansx+=t1;
			ansy+=t2;
			ansz+=t3;
		}
		t*=0.96;
	}
	return ans;
//	cout<<get(ansx,ansy,ansz)<<endl;
//	For(i,n)cout<<dis(ansx,ansy,ansz,i)<<endl;
//	printf("%.5lf\n",ans);
}
int main()
{
//	freopen("A.in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n;
	For(i,n) {
		scanf("%lf%lf%lf",&x[i],&y[i],&z[i]);
	}
	srand(time(NULL));
	double p=1e9;
	For(i,1000)
		p=min(p,hillclimbing());
	printf("%.5f\n",p);


	return 0;
}

