#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#pragma warning(disable:4996);
struct pig{
	int hp=4;       //生命值
	int nc=4;       //n of cards
	bool k=0;       //是否装备武器
	char c[10000]="\0";  //手牌
	char id[5]="\0";     //身份
	int s=0;        //观测到的阵营，1代表主公阵营，2代表反贼阵营，3代表类反贼阵营，0代表未跳
	int ss=0;         //实际的阵营，1代表主公阵营，2代表反贼阵营，0代表主公
}p[25];
int n,m,q=0;
char ca[100000];    //牌堆
void dp(int i,int k){     //真·打牌
	for(int j=k;j<p[i].nc;j++){
		p[i].c[j]=p[i].c[j+1];
	}
	p[i].nc--;
}
bool gg(){          //判断游戏是否结束，以及进行回血
	for(int i=1;i<=n;i++){
	    if(p[i].hp<=0){
		    for(int j=0;j<p[i].nc;j++){
			    if(p[i].c[j]=='P'){
				    dp(i,j);p[i].hp++;
				}
			}
		}
	}
	if(p[1].hp<=0)return 0;
	bool flag=0;
	for(int i=1;i<=n;i++){
	    if(p[i].id[0]=='F'&&p[i].hp>0)flag=1;
	}
	return flag;
}
void tc(int q,int i){   //摸牌
    p[i].c[p[i].nc++]=ca[q++];
}
void js(int i,int r){     //角色死亡结算
	if(!p[i].ss&&p[r].ss==1){
		for(int j=0;j<p[i].nc;j++)p[i].c[j]='\0';
		p[i].nc=0;p[i].k=0;
	}
	if(p[r].ss==2){
	    tc(q++,i);tc(q++,i);tc(q++,i);
	}
}
void t1(int i,int r){     //i对r表敌意跳身份
	if(i==1)return;
	if(p[r].s==2){p[i].s=1;}
	if(p[r].s==1){p[i].s=2;}
}
void t2(int i,int r){     //i对r献殷勤跳身份
	if(p[r].s==1){p[i].s=1;}
	if(p[r].s==2){p[i].s=2;}
}
bool J(int i,int r,bool flag){      //从i开始为r呼吁无懈可击
	int k=i+1;
	while(k!=i){
	    if(k>n)k-=n;
		if(k==i)break;
	    if(p[k].ss==p[r].s&&!flag){
		    for(int j=0;j<p[k].nc;j++){
			    if(p[k].c[j]=='J'){dp(k,j);flag=J(k,r,1);t2(k,r);}
			}
		}
		else if(p[k].ss+p[r].s==3&&flag){
		    for(int j=0;j<p[k].nc;j++){
				if(p[k].c[j]=='J'){dp(k,j);flag=J(k,r,0);t1(k,r);}
			}
		}
		else if(!p[k].ss&&p[r].ss==1){
			for(int j=0;j<p[k].nc;j++){
				if(p[k].c[j]=='J'){dp(k,j);flag=J(k,r,1);t2(k,r);}
			}		
		}
		k++;
	}
	return flag;
}
void P(int i,int j){
	dp(i,j);p[i].hp++;
}
void K(int i,int r,int j){
	dp(i,j);t1(i,r);
	for(int m=0;m<p[r].nc;m++){
		if(p[r].c[m]=='D'){dp(r,m);return;}
	}
	p[r].hp--;if(!gg())return;
	if(p[r].hp<=0)js(i,r);
}
void F(int i,int r,int j){
	dp(i,j);t1(i,r);
	if(J(i,r,0))return;
	if(!p[i].ss&&p[r].ss==1){p[r].hp--;if(!gg())return;if(p[r].hp<=0)js(i,r);return;}
	else while(1){
		bool flag1=0,flag2=0;
	    for(int i1=0;i1<p[r].nc;i1++){if(p[r].c[i1]=='K'){flag1=1;dp(r,i1);}}
		if(!flag1){p[r].hp--;if(!gg())return;if(p[r].hp<=0)js(i,r);break;}
		for(int i1=0;i1<p[i].nc;i1++){if(p[i].c[i1]=='K'){flag2=1;dp(i,i1);}}
		if(!flag2){p[i].hp--;if(!gg())return;if(p[i].hp<=0)js(r,i);break;}
	}
}
void N(int i,int j){
	dp(i,j);int r=i+1;bool flag=0;
	while(r!=i){
	    if(r>n)r-=n;
		if(r==i)break;
		if(J(i,r,0)){r++;continue;}
		for(int m=0;m<p[r].nc;m++){
			if(p[r].c[m]=='K'){dp(r,m);flag=1;break;}
		}
		if(flag){r++;flag=0;continue;}
		p[r].hp--;if(!gg())return;if(p[r].hp<=0)js(i,r);
		if(r==1)p[i].s=3;
		r++;
	}
}
void W(int i,int j){
	dp(i,j);int r=i+1;bool flag=0;
	while(r!=i){
		if(r>n)r-=n;
		if(r==i)break;
		if(J(i,r,0)){r++;continue;}
		for(int m=0;m<p[r].nc;m++){
			if(p[r].c[m]=='D'){dp(r,m);flag=1;break;}
		}
		if(flag){r++;flag=0;continue;}
		p[r].hp--;if(!gg())return;if(p[r].hp<=0)js(i,r);
		if(r==1)p[i].s=3;
		r++;
	}
}
void Z(int i,int j){
    dp(i,j);p[i].k=1;
}
void play(int i){
	bool flag=0;
	int j=0;
	while(j<p[i].nc){
		if(p[i].c[j]=='P'&&p[i].hp<4&&p[i].hp>0){P(i,j);j--;}
		else if(p[i].c[j]=='K'&&((!flag)||p[i].k)){
            int r=i+1;
			while(p[r].hp<=0){
			    r++;if(r>n)r-=n;
			}
			if(r>n)r-=n;
			if(p[i].ss+p[r].s==3){K(i,r,j);j--;flag=1;}
			else if(!p[i].ss&&p[r].s==2){K(i,r,j);j--;flag=1;}
		}
		else if(p[i].c[j]=='F'){
			int r=i+1;
			if(p[i].ss==2){F(i,1,j);j--;}
			while(p[r].hp<=0){
			    if(r>n)r-=n;
				if(r==i)break;
				if(p[i].ss+p[r].s!=3||(!p[i].ss&&p[r].s==2)){r++;continue;}
				r++;
			}
			if(r!=i){
				if(p[i].ss+p[r].s==3){F(i,r,j);j--;}
				else if(!p[i].ss&&p[r].s==2){F(i,r,j);j--;}			    
			}
		}
		else if(p[i].c[j]=='N'){N(i,j);j--;}
		else if(p[i].c[j]=='W'){W(i,j);j--;}
		else if(p[i].c[j]=='Z'){Z(i,j);j=-1;}
		j++;
		if(!gg())return;
	}
}
int main(){
	//游戏初始化
	p[1].s=1;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",p[i].id);getchar();
		if(p[i].id[0]=='Z')p[i].ss=1;
		if(p[i].id[0]=='F')p[i].ss=2;
		int k=0;while(k<4){p[i].c[k++]=getchar();getchar();}
	}
	for(int i=0;i<m;i++){ca[i]=getchar();getchar();}
	for(int i=m;i<=99990;i++)ca[i]=ca[m-1];
	//开始游戏
	int pi=1;
	while(gg()){
		while(p[pi].hp<=0)pi++;
		if(pi>n)pi-=n;
		for(int i=1;i<=n;i++){
			if(p[i].hp>0)printf("身份%s 手牌%s 血量%d 武器%d 牌数%d 观测阵营%d\n",p[i].id,p[i].c,p[i].hp,p[i].k,p[i].nc,p[i].s);
			else printf("身份%s DEAD 血量%d 武器%d 牌数%d 观测阵营%d\n",p[i].id,p[i].hp,p[i].k,p[i].nc,p[i].s);
		}
		printf("%c %c %d\n",ca[q],ca[q+1],pi);
		printf("\n\n");
		tc(q++,pi);tc(q++,pi);
		play(pi);
		pi++;
	}
	if(!p[1].hp){
		printf("FP\n");
		for(int i=1;i<=n;i++){
			if(p[i].hp>0){
				for(int j=0;j<p[i].nc;j++)printf("%c ",p[i].c[j]);
				printf("\n");
			}
			else printf("DEAD\n");
		}
		return 0;
	}
	else{
		printf("MP\n"); 
	    for(int i=1;i<=n;i++){
		    if(p[i].hp>0){
			    for(int j=0;j<p[i].nc;j++)printf("%c ",p[i].c[j]);
			    printf("\n");
		    }
		    else printf("DEAD\n");
		}
	}
}