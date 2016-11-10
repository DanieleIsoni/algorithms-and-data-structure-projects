#include <fstream>
#include <vector>
#include <climits>
#include <map>
#include <iostream>
#include <queue>
using namespace std;

int main()
{

		int N,M,S,T;
		ifstream in("input.txt");
		ofstream out("output.txt");
		in>>N>>M>>S>>T;

		vector< vector<int> >adiacenti;
		adiacenti.resize(N);

    vector< int >distanzeS;
		distanzeS.resize(N);

		int da,a;
		for(int i=0;i<M;i++)
		{
			in>>da>>a;
			adiacenti[da].push_back(a);
			adiacenti[a].push_back(da);
		}
}
