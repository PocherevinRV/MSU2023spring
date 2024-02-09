#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstring>
#include <math.h>
using namespace std;
#define N 5
#define eps 1e-50


class MyClass
{ 
public:   
double a[N];      
MyClass() {memset(a,0,sizeof(a));}
MyClass(double x) {for (size_t i=0; i < N; i++) a[i] = x;}
double &operator[](size_t i){return a[i];}
virtual void Show() = 0; //{for(int i=0; i < N; i++) {printf("\n! %d, %lf",i,a[i]);}}
virtual int cmp(double u, double v){if (u > v) return 1; if (u < v) return -1; return 0;}
void Sort() {double z; for(int i=0; i < N; i++) for(int j=i + 1; j < N; j++) {if (cmp(a[i],a[j]) == 1) {z = a[i]; a[i] = a[j]; a[j] = z;}}}
static int Input(const char *name, vector <MyClass*> &v);
//static int Input(const char *name);
};

//MyClass **a1; size_t M;
/*
int MyClass::Input(const char *name) 
{
	int i = 0; double z; M = 0;
	FILE *f = fopen(name, "r");  
	while (fscanf(f, "%lf", &z) == 1)
	{
		a1[M]->a[i] = z; i++;
//		a1[M] = &v;
//		a1[M]->Show();
//printf("\na[%d]=%lf z = %lf M=%d i=%d\n",i,a1[M]->a[i],z,(int)M,i);
		if (i == N) {i = 0; M++;}
	}
	fclose(f);
	return 0;  
}
*/               


class ChildClass1 : public MyClass
{
public:
//int j;
ChildClass1(): MyClass(){}
ChildClass1(double x): MyClass(x){}
void Show() {for(int i=0; i < N; i++) {printf("\n! a[%d] = %.1lf",i,a[i]);}}
int cmp(double u, double v){if (u > v) return -1; if (u < v) return 1; return 0;}
ChildClass1 &operator= (const MyClass&b) {if (this != &b) { for (int i=0; i < N; i++) {a[i] = b.a[i];}} return *this;} 
};

class ChildClass2 : public MyClass
{
public:
//int j;
ChildClass2(): MyClass(){}	
ChildClass2(double x): MyClass(x){}
void Show() {for(int i=0; i < N; i++) {printf("\n? a[%d] = %.1lf",i,a[i]);}}
int cmp(double u, double v){if (u > v) return -1; if (u < v) return 1; return 0;}
ChildClass2 &operator= (const MyClass&b) {if (this != &b) { for (int i=0; i < N; i++) {a[i] = b.a[i];}} return *this;} 
};


int MyClass::Input(const char *name, vector <MyClass*> &v)
{
	ifstream f(name); string str;
	while (getline(f, str))
	{
		stringstream ss(str); istream_iterator<string> it;
		it = ss; 		
		if (it != istream_iterator<string>())
		{
			if (fabs(stod(*it) - 1) < eps)
			{
				ChildClass1 *w = new ChildClass1; size_t i; ++it; //cout<<"\n|"<<*it<<"|\n"; it++;
				for (i = 0; i < N && it != istream_iterator<string>(); ++it) (*w)[i++] = stod(*it); 
				v.push_back(w);
			}
			else if (fabs(stod(*it) - 2) < eps)
			{
				ChildClass2 *w = new ChildClass2; size_t i; ++it; //cout<<"\n||"<<*it<<"||\n"; it++;
				for (i = 0; i < N && it != istream_iterator<string>(); ++it) (*w)[i++] = stod(*it);
				v.push_back(w);
			}
		}
	}
	return 0;
}


vector<MyClass*> v;	
                
int main(void)
{
//MyClass x(2.0); ChildClass y(1.0);
//a1 = (MyClass **) malloc (10*sizeof(MyClass *));
//for (int i=0; i < 10; i++) {a1[i] = (MyClass *) malloc (sizeof(MyClass));}
//x.a[0] = 2.3; x.a[1] = 2.1; x.a[2] = 1.9; x.a[3] = 1.7; x.a[4] = 1.5;
//a1[0] = &x;
//a1[0] -> Show();
//y.a[0] = 3.3; y.a[1] = 3.1; y.a[2] = 2.9; y.a[3] = 2.7; y.a[4] = 2.5;
//y = x;
//x.Show(); y.Show()o; 
/* x1 = &y;
//y1 = &x;
x1->Show();*/
//y1->Show();
//x.Show();   
//x.Sort(); x.Show(); y.Sort(); y.Show();  

MyClass::Input("data.txt", v);
//MyClass::Input("2.txt");
for (size_t i = 0; i < v.size(); ++i) {v[i]->Show(); cout<<endl;}
//for (size_t i = 0; i < M; ++i) {a1[i]->Show(); cout<<endl;}
//for (size_t i = 0; i < 10; ++i) free(a1[i]);  
//free(a1);  
return 0;      
}