#ifndef SOLUTION_H
#define SOLUTION_H

#include <QMainWindow>

#include <vector>
#include <set>

// Comment

using namespace std;

QString solve(int n, vector< vector<int> > &g){
    QString ans;
    vector<int> g_mask(n);
    for(int i=0; i<n; i++){
        int mask=1<<i;
        for(int j=0; j<n; j++){
            mask=mask|((1*g[j][i])<<j);
        }
        g_mask[i]=mask;
    }
    set<int> sub;
    sub.insert((1<<n)-1);
    for(int mask=1; mask<(1<<n); mask++){
        int mask_sub=mask;
        int mask_cov=0;
        int j=n-1;
        while(mask_sub>0){
            if(mask_sub&1) mask_cov|=g_mask[j];
            j--;
            mask_sub=mask_sub>>1;
        }
        if(mask_cov==(1<<n)-1) sub.insert(mask);
    }

    for(set<int>::iterator i=sub.begin(); i!=sub.end(); i++){
        for(set<int>::iterator j=i; j!=sub.end(); j++){
            if(i==j) continue;
            int mask1=*i;
            int mask2=*j;
            if((mask1|mask2)==mask2){
                j--;
                sub.erase(mask2);
            }
        }
    }

    for(set<int>::iterator i=sub.begin(); i!=sub.end(); i++){
        int mask=*i;
        int j=n;
        while(mask>0){
            if(mask&1){
                if(j>9) ans+='0'+j/10;
                ans+='0'+j%10;
                ans+=' ';
            }
            j--;
            mask=mask>>1;
        }
        ans+='\n';
    }
    return ans;
}

#endif // SOLUTION_H
