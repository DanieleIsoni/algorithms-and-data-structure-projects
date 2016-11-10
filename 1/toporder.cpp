#include <fstream>
#include <vector>
#include <climits>
#include <map>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;


/**
topSort(GRAPH G, STACK S)
boolean[] visitato boolean[1 ...G.n]
foreach u 2 G.V() do visitato[u] false
foreach u 2 G.V() do
if not visitato[u] then
ts-dfs(G, u, visitato,S)



ts-dfs(GRAPH G, NODE u, boolean[] visitato, STACK S)
visitato[u] true
foreach v 2 G.adj(u) do
if not visitato[v] then
ts-dfs(G, v, visitato,S)
S.push(u)

*/

void topSort(vector< vector<int> > & Graph,int node, stack<int> &S, vector<bool> &visitato, int N)
{
    visitato[node]=true;
    for(auto &v : Graph[node])
        if(!visitato[v])
        {
          topSort(Graph,v,S,visitato,N);
        }
    S.push(node);

}





int main()
{

		int N,M;
		ifstream in("input.txt");
		ofstream out("output.txt");
		in>>N>>M;

		vector< vector<int> >adiacenti;
		adiacenti.resize(N);
    vector< bool> visitato;
		visitato.resize(N);


		int da,a;
		for(int i=0;i<M;i++)
		{
			in>>da>>a;
			adiacenti[da].push_back(a);
		}
    stack<int> S;


    for(int i=0;i<N;i++)
      visitato[i]=false;

    for(int i=0;i<N;i++)
    {
        if(!visitato[i])
          {
              topSort(adiacenti,i,S,visitato,N);
          }
    }
    while(!S.empty())
    {
        out<<S.top()<<endl;
        S.pop();
    }


}
