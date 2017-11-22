#include <iostream>
#include <armadillo>
#include <algorithm>
#include <iostream>
#include <time.h> 
#include <cstdio>
#include <omp.h>
#include <stdio.h>

using namespace std;
using namespace arma;
int thread_count =8;

int count_frequency(vec a,int tam)
{
	int cont=0,i;
	//#pragma omp for
	for (i =0;i<tam;i++)
	{
		if((a(i))>0) cont++;
	}
	return cont;
}

vec conjunction2(vec a,vec b, int tam)
{
	vec ans=zeros(tam);
	int i;
	//#pragma omp for
	for ( i =0;i<tam;i++)
	{
		ans(i)=a(i)&&b(i);
	}
	return ans;
}

vec conjunction3(vec a,vec b,vec c, int tam)
{
	vec ans=zeros(tam);
	int i;
	//	#pragma omp for
	for ( i =0;i<tam;i++)
	{
		ans(i)=(a(i)&&b(i)&&c(i));
	}
	return ans;
}


int main()
{
	double start = omp_get_wtime() ;
	double exec_time;

clock_t t;

t = clock();

mat comb;
mat data;
mat asoc2;
comb.load("combn.csv",csv_ascii);
data.load("CleanData.csv",csv_ascii);
asoc2.load("assocFirst.csv",csv_ascii);
mat  cm = zeros<mat>(13203,163);

cout<<"Datos cargados"<<endl;
//cout<<data<<endl;
int cont=0;
vec pre;
int s1,j,k;
float conf;

#pragma omp parallel for schedule(dynamic) num_threads(thread_count) private(j,pre,s1,conf)
for( k=0;k<comb.n_cols;k++)
{	
	
	for(int j=0;j<163;j++)
	{
		if(j!=(comb(0,k)-1) && j!=(comb(1,k)-1))
		{
			//cout<<"Entro if"<<endl;
			conf=0;s1=0;
			pre=conjunction3(data.col(comb(0,k)-1),data.col(comb(1,k)-1),data.col(j),data.n_rows);
			s1=count_frequency(pre,pre.n_rows);
			//cout<<s1<<"-"<<asoc2(comb(0,k)-1,comb(1,k)-1)<<endl;
			//if(asoc2(comb(0,k)-1,comb(1,k)-1))
			conf=(s1*1.0)/(asoc2(comb(0,k)-1,comb(1,k)-1));
			//cout<<conf<<endl;
			//cout<<cont<<"-"<<j<<endl;
			cm(k,j)=conf;
		}		
	}


	if(k%100==0)
	{
		cout<<k<<endl;
	}
}
cout<<"end\n";
 t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);



cm.save("Confidence49159(2).csv",csv_ascii);
// cm.save("Conf",raw_ascii);
// cm.save("Confwf");

  double end = omp_get_wtime();
  exec_time=end-start;
printf("the time difference is %15.15f", exec_time);
  return 0;
}

//g++ code3omp.cpp -std=c++11 -o la -DARMA_DONT_USE_WRAPPER -lopenblas -llapack
