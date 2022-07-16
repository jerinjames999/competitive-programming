//KMP algorithm for string pattern matching
// Time complexity : O(n+m)
#include<bits/stdc++.h>
using namespace std;

string Text, pattern;

int main(){
    cin>>Text;
    cin>>pattern;
    string temp = pattern+'$'+Text;
    vector<int> prefix_matches(temp.size(), 0);
    vector<int> ans;
    int i, j = 0;
    prefix_matches[0] = 0;
    for(i = 1; i<temp.size(); i++){
        cout<<"0Hi"<<endl;
        while(temp[j]!=temp[i] && j>0){
        cout<<"1Hi"<<endl;
            j = prefix_matches[prefix_matches[j-1]];
        }
        if(temp[i]!=temp[j]){
            cout<<"2Hi not same"<<endl;
            prefix_matches[i] = 0;
        }
        else{
            cout<<"2Hi same"<<endl;
            prefix_matches[i] = j+1;
            j++;
        }
    }
    for(i = pattern.size()+1; i<temp.size(); i++){
        if(prefix_matches[i]==pattern.size()){
            ans.push_back(i-pattern.size());
        }
    }
    for(i = 0; i<temp.size(); i++){
        cout<<prefix_matches[i]<<" ";
    }
    cout<<endl;
    for(i = 0; i< ans.size(); i++){
        cout<<ans[i]<<" ";
    }
    
    return 0;
}