//Trie Matching algorithm O(Text*(lognest pattern in the trie))
//Problem is memory usage is high as we are creating extra nodes for each characters in the pattern
#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    bool is_end = 0;// instead of adding this we can also add a dollar sign(as 27th character after(index 26)) at the end of each pattern.
    vector<node*> alp = vector<node*>(26, nullptr);//Note inside a class we cannot initilize by :- vector<node*> alp(26, nullptr); instead we have to use {} or =; i.e vector<node*> alp = vector<node*>(26, nullptr) or using {}.
    // node(){//https://stackoverflow.com/questions/54590838/initializing-class-member-vector-with-size-fails
    //     alp = vector<node*>(26, nullptr);
    // }
};

class str_Trie{
    node* root = nullptr;
    public:
    str_Trie(){
        root = new node();
    }
    str_Trie(vector<string>& patterns){
        root = new node();
        for(int i = 0; i<patterns.size(); i++){
            add_string(patterns[i]);
        }
    }
    void add_string(string str){
        node* curr = root;
        for(int i = 0; i<str.size(); i++){
            if(curr->alp[str[i]-'a']){
                curr = curr->alp[str[i]-'a'];
            }else{
                node* temp = new node();
                curr->alp[str[i]-'a'] = temp;
                curr=temp;
            }
        }
        curr->is_end = 1;
    }
    vector<pair<int,int>> detect_matches(string& Text){
        vector<pair<int,int>> ans;
        for(int i = 0; i<Text.size(); i++){
            node* curr = root;
            int j = 0;
            while( i+j<Text.size() && curr->alp[Text[i+j]-'a'] ){
                curr = curr->alp[Text[i+j]-'a'];
                if(curr->is_end){
                    ans.push_back({i, j+1});
                }
                j++;
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
    str_Trie patternsTrie(patterns);
    vector<pair<int, int>> ans = patternsTrie.detect_matches(Text);
    cout<<"\nanswers \n";
    for(int i= 0; i<ans.size(); i++){
        cout<<ans[i].first<<" "<<ans[i].second<<"\n";
    }

    return 0;
}