//O(Text size* pattern size)
#include<bits/stdc++.h>
using namespace std;

string Text, pattern;

int main(){
    cin>>Text;
    cin>>pattern;
    vector<int> matched_pos;
    for(int i= 0; i<Text.size(); i++){
        bool isMatched = 1;
        for(int j = 0; j<pattern.size(); j++){
            if(Text[i+j]!=pattern[j]){
                isMatched = 0;break;
            }
        }
        if(isMatched)matched_pos.push_back(i);
    }
    cout<<endl;
    for(int i = 0; i<matched_pos.size(); i++){
        cout<<matched_pos[i]<<" ";
    }
    
    return 0;
}