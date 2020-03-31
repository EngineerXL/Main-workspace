#include <algorithm>
#include <set>
#include <stdio.h>
#include <vector>
  
using namespace std;
  
struct dsu{
    vector<int> leader;
    vector<int> size;
  
    int find(int x){
        if(leader[x]==x) return x;
        leader[x]=find(leader[x]);
        return leader[x];
    }
  
    bool join(int x, int y){
        int xp=find(x);
        int yp=find(y);
        if(xp==yp) return false;
        if(size[xp]>size[yp]){
            leader[yp]=xp;
            size[xp]=size[xp]+size[yp];
        }else{
            leader[xp]=yp;
            size[yp]=size[xp]+size[yp];
        }
        return true;
    }
  
    dsu(int n){
        leader.resize(n);
        size.resize(n);
        for(int i=0; i<n; i++){
            leader[i]=i;
            size[i]=1;
        }
    }
};
  
struct edge{
    int u, v;
    long long w;
};
  
bool operator < (edge x, edge y){
    return x.w<y.w;
}
  
int main(){
    int n, m, u, v;
    long long w, ans=0;
    scanf("%d %d", &n, &m);
    vector<edge> g;
    for(int i=0; i<m; i++){
        scanf("%d %d %lli", &u, &v, &w);
        g.push_back({u, v, w});
    }
    dsu d(n);
    sort(g.begin(), g.end());
    for(int i=0; i<m; i++){
        if(d.join(g[i].u-1, g[i].v-1)) ans+=g[i].w;
    }
    printf("%lli\n", ans);
}
