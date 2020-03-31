#include <algorithm>
#include <set>
#include <stdio.h>
#include <vector>
 
using namespace std;
 
struct edge{
    int to;
    long long w;
};
 
bool operator < (edge x, edge y){
    if(x.w!=y.w) return x.w<y.w;
    else return x.to<y.to;
}
 
int main(){
    int n, m, u, v;
    long long w;
    scanf("%d %d", &n, &m);
    vector< vector<edge> > g(n);
    for(int i=0; i<m; i++){
        scanf("%d %d %lli", &u, &v, &w);
        g[u-1].push_back({v-1, w});
        g[v-1].push_back({u-1, w});
    }
    set<edge> edges;
    vector<int> used(n);
    used[0]=1;
    long long ans=0;
    for(int i=0; i<g[0].size(); i++) edges.insert(g[0][i]);
    while(!edges.empty()){
        edge e=*edges.begin();
        edges.erase(edges.begin());
        if(used[e.to]) continue;
        used[e.to]=1;
        ans+=e.w;
        for(int i=0; i<g[e.to].size(); i++) edges.insert(g[e.to][i]);
    }
    printf("%lli\n", ans);
}
