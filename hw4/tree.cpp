#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

using std::string;

#define MAX_FEATURE (1024+1)

int global = 1;

double compute(double c, double d, double e, double f)
{
double a = 1 - (c / (c + d)) * (c / (c + d)) - (d / (c + d)) * (d / (c + d));
double b = 1 - (e / (e + f)) * (e / (e + f)) - (f / (e + f)) * (f / (e + f));
return (c + d) / (c + d + e + f) * a + (e + f) / (c + d + e + f) * b;
}

void printdata(std::vector<double *> data, int total)
{
for(int i = 0; i < total; i++){
	for(int j = 0; j < 5; j++)
		cout<<data[i][j]<<" ";
	cout<<endl;
	}

return ;
}

bool compare(double* a, double* b)
{
return a[global] < b[global];
}

void buildtree(std::vector<double *> &data, int total, double epsilon, int level)
{
if(total == 1){
	for(int i = 0; i < level; i++)     //!!!
	cout<<"\t";
	if(data[0][0] == 1)
		cout<<"return 1;\n";   //stop by only one
	else
		cout<<"return -1;\n";   //stop by only one 
	for(int i = 0; i < level - 1; i++)    //!!!
		cout<<"\t";
	cout<<"} \n";
	return ;
	}
int ter = 1;
for(int i = 0; i < total - 1; i++) {    //termination condition 1 - label same
	if(data[i][0] != data[i+1][0]) {
		ter = 0;
		break;
		}
	else 
		ter = 1;
	}
if(ter == 1){   //stop!!!
	for(int i = 0; i < level; i++)    //!!!
		cout<<"\t";
	if(data[0][0] == 1)
		cout<<"return 1;\n";   //stop by label same
	else
		cout<<"return -1;\n";   //stop by label same
	for(int i = 0; i < level - 1; i++)     //!!!
		cout<<"\t";
	cout<< "}\n";
	return ;
	}
int secondter = 0;
for(int i = 0; i < total ; i++) {  //termination condition 2  features same
	for(int j = 1; j < MAX_FEATURE; j++) {
		if(data[0][j] != data[i][j]) {
			ter = 0;
			secondter = 1;
			break;
			}
		else
			ter = 1;
		}
	if(secondter == 1)
		break;
	}
if(ter == 1) {    //stop!!!
	int yes = 0, no = 0;
	for(int i = 0; i < total; i++) {
		if(data[i][0] == 1)
			yes++;
		else
			no++;
		}
	for(int i = 0; i < level; i++)   //!!!
		cout<<"\t";
	if(yes > no)
		cout<<"return 1;\n";   // stop by features same
	else 
		cout<<"return -1;\n";   // stop by features same
	for(int i = 0; i < level - 1; i++)         //!!!
		cout<<"\t";
	cout<<"}\n";
	return ;
	}
double allcon[MAX_FEATURE] = {0};
for(int x = 0; x < MAX_FEATURE; x++)
	allcon[x] = 1;
double allthreshold[MAX_FEATURE] = {0};
for(int t = 1; t < MAX_FEATURE; t++) {
	global = t;
	sort(data.begin(),data.end(), compare);
	double a = 0, b = 0;
	double threshold = data[0][t] - 1;
	for(int j = 0; j < total; j++){
		if(data[j][0] == 1)
			a++;
		else
			b++;
		}
	double minconfusion = 1;
	for(int i = 0; i < total - 1; i++){
		double yesup = 0, yesdown = 0, noup = 0, nodown = 0;
		if(data[i][global] != data[i+1][global]){
			for(int j = 0; j <= i; j++) {
				if(data[j][0] == 1)
					yesup++;
				else 
					noup++;
				}
			for(int l = i + 1; l < total; l++){
				if(data[l][0] == 1)
					yesdown++;
				else
					nodown++;
				}
			double con = compute(yesup, noup, yesdown, nodown);
			if(con < minconfusion){
				minconfusion = con;
				threshold = (data[i][global] + data[i+1][global]) / 2;
				}
			}
		}
	allthreshold[t] = threshold;
	allcon[t] = minconfusion;
	}
int min = 1;
int check[MAX_FEATURE] = {0};
for(int i = 0; i < MAX_FEATURE; i++)
	check[i] = 1;
for(int i = 1; i < MAX_FEATURE; i++) {
	for(int k = 0; k < total; k++) {
		if(data[0][i] != data[k][i]){
			check[i] = 0;
			break;
			}
		}
	}
double allmincon = allcon[1];
double allminthre = allthreshold[1];
for(int i = 1; i < MAX_FEATURE; i++) {
	if(allcon[i] < allmincon && check[i] != 1){
		allmincon = allcon[i];
		allminthre = allthreshold[i];
		min = i;
		}
	}
//cout<< "min confusion : " << allmincon <<" min features : " << min << " threshold : " << allminthre <<endl; 

if(allmincon <= epsilon && allmincon != 0){    //stop by epsilon
	int yes = 0, no = 0;
	for(int i = 0; i < total; i++)
		if(data[i][0] == 1)
			yes++;
		else
			no++;
	for(int i = 0; i < level; i++)  //!!!
		cout<<"\t";
	if(yes > no)
		cout<<"return 1;\n";    //stop by epsilon 
	else 
		cout<<"return -1;\n";    //stop by epsilon 
	for(int i = 0; i < level - 1; i++)        //!!!
		cout<<"\t";
	cout<< "}\n";
	return ;
	}

std::vector<double*> dataup;
std::vector<double*> datadown;

int count = 0;
for(int i = 0; i < total; i++) {
	if(data[i][min] < allminthre) {
		dataup.push_back(data[i]);
		count++;
		}
	else
		datadown.push_back(data[i]);
	}
for(int i = 0; i < level; i++)     //!!!
	cout<<"\t";
cout<< "if(attr[" << min << "] < "<< allminthre << ") {" << endl;
level++;
buildtree(dataup, count, epsilon, level);
for(int i = 0; i < level - 1; i++)   //!!!
	cout<<"\t";
cout<<"else {\n";
buildtree(datadown, (total - count), epsilon, level);
level--;
for(int i = 0; i < level - 1; i++)   //!!!
	cout<<"\t";
cout<<"}"<<endl;
return ;
}

int main(int argc,char** argv) {

cout<<fixed;
cout.precision(6);
int total = 0;
std::ifstream fin;
string istring;
fin.open(argv[1]);
double epsilon = atof(argv[2]);
std::vector<double*> data;
while (std::getline(fin, istring)) {
	double* features = new double[MAX_FEATURE];
	total++;
	char *cstring, *tmp;
	int label;
	memset(features, 0, sizeof(double) * MAX_FEATURE);

	cstring = new char[istring.size() + 1];
	strncpy(cstring, istring.c_str(), istring.size()+1);

	tmp =  strtok(cstring, ": ");
	label = atoi(tmp);
	features[0] = (double)label;
	tmp = strtok(NULL, ": ");

	while(tmp != NULL) {
		int id = atoi(tmp);
		tmp = strtok(NULL, ": ");
		features[id] = atof(tmp);
		tmp = strtok(NULL, ": ");
		}
	double *ptr = features;
	data.push_back(ptr);
	delete[] cstring;
	}
int level = 1;
cout<< "int tree_predict(double *attr) {"<<endl;
buildtree(data, total, epsilon, level);

return 0;
}

