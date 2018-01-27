#include <iostream>
#include <string>
#include <math.h>

using namespace std;

string Cypher;
double alph_prob[26]={0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.02, 0.061, 0.07, 0.002, 0.008, 0.04,
0.024, 0.067, 0.075, 0.019, 0.001, 0.06, 0.063, 0.091, 0.028, 0.01, 0.023, 0.001, 0.02, 0.001};

unsigned int Friedman(){
	double dist_target=1;
	unsigned int m=1;
	for(unsigned int mtest=1;mtest<=20;mtest++){
		double freq[20][26]={0};
		unsigned int len[20]={0};
		for(unsigned int group=0;group<mtest;group++){
			for(unsigned int index=group;index<Cypher.length();index+=mtest){
				freq [group][ Cypher[index]-65 ] ++ ;
				len[group]++;
			}
		}
		double test[20]={0};
		for(unsigned int group=0;group<mtest;group++){
			for(unsigned int i=0;i<26;i++)
				test[group]+= (double)(freq[group][i]*(freq[group][i]-1)) / (double)(len[group]*(len[group]-1)) ;
		}
		double dist_now=0;
		for(unsigned int i=0;i<mtest;i++)
			dist_now+= test[i];
		dist_now/=mtest;
		if(abs(dist_now-0.065)<dist_target){
			dist_target=abs(dist_now-0.065);
			m=mtest;
		}
	}
	return m;
}

void decry(unsigned int m){
	unsigned int *key = new unsigned int[m];
	for(unsigned int group=0;group<m;group++){
		unsigned int freq[26]={0};	//should always initial?!
		unsigned int len=0;
		for(unsigned int pos=group;pos<Cypher.length();pos+=m){
			freq[ Cypher[pos]-65 ]++;
			len++;
		}
		double dist_target=0.065;
		for(unsigned int g=0;g<26;g++){
			double test=0;
			for(unsigned int i=0;i<26;i++){
				test += alph_prob[i]*freq[(i+g)%26]/len;
			}
			if(abs(0.065-test)<dist_target){
				dist_target=abs(0.065-test);
				key[group]=g;
			}
		}
	}
	//use key to decry
	for(unsigned int i=0;i<m;i++)
		cout<<(char)(key[i]+65);
	cout<<endl;
	for(unsigned int i=0,j=0;i<Cypher.length();i++,j++){
		if(j==m)j=0;
		cout<<(char)((Cypher[i]-13-key[j])%26+65);
	}
}

int main(){
	cin>>Cypher;
	decry(Friedman());
	return 0;
}