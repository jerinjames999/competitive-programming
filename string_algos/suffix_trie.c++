//Trie Matching algorithm where we make the try with all the suffixs of Text
//Time to make suffix Trie :- O(|Text|^2)
//Running time for pattern matching :- O(|Text|*|patterns|) due to the dfs needed for finding locations
//Memory usage :- O(|Text|^2);
//Problem is memory usage is high as we are creating extra nodes for each characters in the text and memory is O(Text*Text)
#include<bits/stdc++.h>
using namespace std;

class node{//We can also store the character in the trie node as a member.
    public://27 for dollar sign at the end of the text
    int* pos = nullptr;
    vector<node*> alp = vector<node*>(27, nullptr);//Note inside a class we cannot initilize by :- vector<node*> alp(26, nullptr); instead we have to use {} or =; i.e vector<node*> alp = vector<node*>(26, nullptr) or using {}.
};

vector<int> dfs(node* curr){
    // cout<<"dfs started";
    vector<int> ans;
    if(curr->alp[26]){
        ans.push_back(*(curr->alp[26]->pos));
        // return ans;
    }
    for(int i = 0; i<26; i++){
        if(!curr->alp[i])continue;
        vector<int> v;
        v = dfs(curr->alp[i]);
        ans.insert(ans.end(), v.begin(), v.end());
    }
    return ans;
}

class suffix_Trie{
    node* root = nullptr;
    string Text;
    public:
    suffix_Trie(){
        root = new node();
    }
    suffix_Trie(string& str){
        root = new node();
        Text = str+"{";//I am attaching this instead of $ is because ascii of "{" is one greater than "z"; so it gets matched to 27
        for(int i = 0; i<Text.size(); i++){
            add_string(i);
        }
    }
    void add_string(int from){
        // cout<<"addig string"<<endl;
        node* curr = root;
        for(int i = from; i<Text.size(); i++){
            if(curr->alp[Text[i]-'a']){
                curr = curr->alp[Text[i]-'a'];
            }else{
                node* temp = new node();
                curr->alp[Text[i]-'a'] = temp;
                curr=temp;
            }
        }
        curr->pos = new int;
        *curr->pos = from;
        // cout<<"done addig string"<<endl;
    }
    vector<pair<int,int>> detect_matches(vector<string>& patterns){
        // cout<<"starting the detection"<<endl;
        vector<pair<int,int>> ans;
        for(int k = 0; k<patterns.size(); k++){
            // cout<<"detecting "<<k<<"th pattern"<<endl;
            node* curr = root;
            int j = 0;
            bool isfound = 1;
            while(j<patterns[k].size()){
                if(!curr->alp[patterns[k][j]-'a']){
                    isfound = 0;break;
                }
                curr = curr->alp[patterns[k][j]-'a'];
                // cout<<j<<" ";
                j++;
            }
            // cout<<endl;
            if(!isfound){
                continue;
            }
            //dfs to find the indexes of the suffixes from curr node.
            vector<int> start_pos = dfs(curr);
            for(int l =0; l<start_pos.size(); l++){
                ans.push_back({start_pos[l], start_pos[l]+patterns[k].length()-1});
            }
        }
        
        return ans;
    }

};

string Text;
vector<string> patterns;

int main(){
    cin>>Text;
    int n;
    cin>>n;
    for(int i = 0; i<n; i++){
        string str;
        cin>>str;
        patterns.push_back(str);
    }
    suffix_Trie suffixTrie(Text);
    vector<pair<int, int>> ans = suffixTrie.detect_matches(patterns);
    cout<<"\nanswers \n"<<ans.size()<<endl;
    for(int i= 0; i<ans.size(); i++){
        cout<<ans[i].first<<" "<<ans[i].second<<"\n";
    }

    return 0;
}