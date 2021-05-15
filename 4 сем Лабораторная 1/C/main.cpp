#include <bits/stdc++.h>

using namespace std;

vector <bool> used;

bool dfs(long long v, vector <vector <long long> > &matrix, vector <long long> &mt){
    if (!used[v]){
        used[v]=true;
        for (long long i=0; i<matrix[v].size(); i++){
            if ((mt[matrix[v][i]]==-1) || (dfs(mt[matrix[v][i]], matrix, mt))){
                mt[matrix[v][i]]=v;
                return true;
            }
        }
        return false;
    }
    return false;
}

int main(){
    vector <pair <long long, long long> > ans, numEdge;
    long long n, m, e;
    cin>>n>>m>>e;
    vector <pair <long long, long long> > left(n), right(m);
    vector <vector <long long> > matrixL(n), matrixR(m);
    vector <long long> mtL, mtR, weightL(n), weightR(m);
    for (long long i=0; i<n; i++){
        cin>>left[i].first;
        left[i].second=i;
        weightL[i]=left[i].first;
    }
    for (long long i=0; i<m; i++){
        cin>>right[i].first;
        right[i].second=i;
        weightR[i]=right[i].first;
    }
    sort(left.rbegin(), left.rend());
    sort(right.rbegin(), right.rend());
    for (long long i=0; i<e; i++){
        long long x, y;
        cin>>x>>y; x--; y--;
        matrixL[x].push_back(y);
        matrixR[y].push_back(x);
        numEdge.push_back(make_pair(x, y));
    }
    mtL.resize(m, -1);
    for (long long i=0; i<n; i++){
        used.resize(0);
        used.resize(n, false);
        dfs(left[i].second, matrixL, mtL);
    }
    mtR.resize(n, -1);
    for (long long i=0; i<m; i++){
        used.resize(0);
        used.resize(m, false);
        dfs(right[i].second, matrixR, mtR);
    }
    vector <bool> leftWas(n, false), rightWas(m,false);
    vector <vector <long long> > matrixMTL(n), matrixMTR(m);
    for (long long i=0; i<m; i++){
        if (mtL[i]!=-1) {
            leftWas[mtL[i]]=true;
            matrixMTL[mtL[i]].push_back(i);
            matrixMTR[i].push_back(mtL[i]);
        }
    }
    for (long long i=0; i<n; i++){
        if (mtR[i]!=-1) {
            rightWas[mtR[i]]=true;
            matrixMTR[mtR[i]].push_back(i);
            matrixMTL[i].push_back(mtR[i]);
        }
    }

    used.resize(0);
    used.resize(n, false);
    vector <bool> usedR(m, false);
    vector <long long> que;
    for (long long i=0; i<n; i++){
        if(matrixMTL[i].size()==1){
            if (used[i]) continue;
            que.resize(0);
            long long v=i;
            while(true){
                used[v]=true;
                que.push_back(v);
                if (!usedR[matrixMTL[v][0]]){
                    usedR[matrixMTL[v][0]]=true;
                    que.push_back(matrixMTL[v][0]);
                } else{
                    if (matrixMTL[v].size()==2){
                        usedR[matrixMTL[v][1]]=true;
                        que.push_back(matrixMTL[v][1]);
                    } else{
                        break;
                    }
                }
                v=que[que.size()-1];
                if (!used[matrixMTR[v][0]]){
                    v=matrixMTR[v][0];
                    //used[matrixMTR[v][0]]=true;
                    //que.push_back(matrixMTR[v][0]);
                } else{
                    if (matrixMTR[v].size()==2){
                        v=matrixMTR[v][1];
                        //used[matrixMTR[v][1]]=true;
                        //que.push_back(matrixMTR[v][1]);
                    } else{
                        break;
                    }
                }
            }
            if (que.size()%2==0){
                for (long long i=0; i<que.size()-1; i+=2){
                    ans.push_back(make_pair(que[i], que[i+1]));
                }
            } else{
                if (leftWas[que[0]]){
                    for (long long i=0; i<que.size()-1; i+=2){
                        ans.push_back(make_pair(que[i], que[i+1]));
                    }
                } else{
                    for (long long i=1; i<que.size()-1; i+=2){
                        ans.push_back(make_pair(que[i+1], que[i]));
                    }
                }
            }
        }
    }
    for (long long i=0; i<m; i++){
        if(matrixMTR[i].size()==1){
            if (usedR[i]) continue;
            que.resize(0);
            long long v=i;
            while(true){
                usedR[v]=true;
                que.push_back(v);
                if (!used[matrixMTR[v][0]]){
                    used[matrixMTR[v][0]]=true;
                    que.push_back(matrixMTR[v][0]);
                } else{
                    if (matrixMTR[v].size()==2){
                        used[matrixMTR[v][1]]=true;
                        que.push_back(matrixMTR[v][1]);
                    } else{
                        break;
                    }
                }
                v=que[que.size()-1];
                if (!usedR[matrixMTL[v][0]]){
                    v=matrixMTL[v][0];
                    //usedR[matrixMTL[v][0]]=true;
                    //que.push_back(matrixMTL[v][0]);
                } else{
                    if (matrixMTL[v].size()==2){
                        v=matrixMTL[v][1];
                        //usedR[matrixMTL[v][1]]=true;
                        //que.push_back(matrixMTL[v][1]);
                    } else{
                        break;
                    }
                }
            }
            if (que.size()%2==0){
                for (long long i=0; i<que.size()-1; i+=2){
                    ans.push_back(make_pair(que[i+1], que[i]));
                }
            } else{
                if (rightWas[que[0]]){
                    for (long long i=0; i<que.size()-1; i+=2){
                        ans.push_back(make_pair(que[i+1], que[i]));
                    }
                } else{
                    for (long long i=1; i<que.size()-1; i+=2){
                        ans.push_back(make_pair(que[i], que[i+1]));
                    }
                }
            }
        }
    }
    for (long long i=0; i<n; i++){
        if (matrixMTL[i].size()==2){
            if (used[i]) continue;
            que.resize(0);
            long long from=-1, v=i;
            while (true){
                used[v]=true;
                que.push_back(v);
                if (!usedR[matrixMTL[v][0]]){
                    usedR[matrixMTL[v][0]]=true;
                    que.push_back(matrixMTL[v][0]);
                } else{
                    usedR[matrixMTL[v][1]]=true;
                    que.push_back(matrixMTL[v][1]);
                }
                v=que[que.size()-1];
                if (!used[matrixMTR[v][0]]){
                    v=matrixMTR[v][0];
                    //used[matrixMTR[v][0]]=true;
                    //que.push_back(matrixMTR[v][0]);
                } else{
                    v=matrixMTR[v][1];
                    //used[matrixMTR[v][1]]=true;
                    //que.push_back(matrixMTR[v][1]);
                }
                //v=que[que.size()-1];
                if (v==i) break;
            }
            for (long long i=0; i<que.size()-1; i+=2){
                ans.push_back(make_pair(que[i],que[i+1]));
            }
        }
    }
    long long ansWeight=0;
    for (long long i=0; i<ans.size(); i++){
        ansWeight+=weightL[ans[i].first];
        ansWeight+=weightR[ans[i].second];
    }
    cout<<ansWeight<<endl;
    cout<<ans.size()<<endl;
    for (long long i=0; i<ans.size(); i++){
        for (long long j=0; j<e; j++){
            if (numEdge[j].first==ans[i].first){
                if (numEdge[j].second==ans[i].second){
                    cout<<j+1<<" ";
                    break;
                }
            }
        }
    }
    return 0;
}
