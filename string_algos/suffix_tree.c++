//pattern Matching algorithm where we make the suffix tree with all the suffixs of Text
//Time to make suffix Tree :- O(|Text|^2)
    //There exist an algorithm to construct suffix tree in O(n) time using Weiner algorithm later modified by Ukkonen.
    //We will study to construct suffix tree using suffix array(which itself will take O(nlogn)) in total of nlogn time.
    // suffix tree from suffix array is O(n) time.
//Running time for pattern matching :- O(|Text|*|patterns|) due to the dfs needed for finding locations
//Memory usage :- O(2*|Text|);
#include<bits/stdc++.h>
using namespace std;

class node{//We can also store the character in the trie node as a member.
    public://27 for dollar sign at the end of the text
    int* pos = nullptr;
    pair<int, int> str_loc=make_pair(-1, -1);
    vector<node*> alp = vector<node*>(27, nullptr);//Note inside a class we cannot initilize by :- vector<node*> alp(26, nullptr); instead we have to use {} or =; i.e vector<node*> alp = vector<node*>(26, nullptr) or using {}.
};

vector<int> dfs(node* curr){
    // cout<<"dfs started"<<endl;
    vector<int> ans;
    if(curr->pos){
        ans.push_back(*(curr->pos));
        // cout<<"Hi0"<<endl;
        // return ans;
    }
    // cout<<"Hi1"<<endl;
    for(int i = 0; i<27; i++){
        // cout<<"Hi2"<<endl;
        if(!curr->alp[i])continue;
        // cout<<"Hi3"<<endl;
        // cout<<(char)(i+'a')<<endl;
        vector<int> v;
        v = dfs(curr->alp[i]);
        ans.insert(ans.end(), v.begin(), v.end());
    }
    return ans;
}

class suffix_Tree{
    node* root = nullptr;
    string Text;
    public:
    suffix_Tree(){
        root = new node();
    }
    suffix_Tree(string& str){
        root = new node();
        Text = str+"{";//I am attaching this instead of $ is because ascii of "{" is one greater than "z"; so it gets matched to 27
        for(int i = 0; i<Text.size(); i++){
            add_string(i);
        }
    }
    void add_string(int from){
        // cout<<"adding string "<<Text[from]<<endl;
        node* curr = root, *prev_node;
        for(int i = from; i<Text.size(); ){
            
            if(curr->alp[Text[i]-'a']){
                prev_node = curr;
                curr = curr->alp[Text[i]-'a'];
                int l = curr->str_loc.first;
                int r = curr->str_loc.second;
                
                while(Text[l]==Text[i] && l<=r ){
                    l++;i++;
                }
                if(l>r){
                    continue;
                }
                else{
                    // cout<<"subdivision started"<<endl;
                    //subdivide and create a new node for rest of the text. and then return;
                    node* temp1 = new node();
                    temp1->alp[Text[l]-'a'] = curr;//prev_node->alp[Text[curr->str_loc.first]-'a'];  curr->alp[Text[curr->str_loc.first]-'a'];
                    prev_node->alp[Text[curr->str_loc.first]-'a'] = temp1;
                    temp1->str_loc = {curr->str_loc.first, l-1};
                    curr->str_loc = {l, r};
                    
                    node* temp2 = new node();
                    temp1->alp[Text[i]-'a'] = temp2;
                    temp2->str_loc = {i, Text.size()-1};
                    curr=temp2;
                    // cout<<"subdivision finished"<<endl;
                    break;
                }

            }else{
                //simply attach new node with range  form i to end of string.
                // cout<<"HHHH"<<endl;
                node* temp = new node();
                curr->alp[Text[i]-'a'] = temp;
                temp->str_loc = {i, Text.size()-1};
                curr=temp;
                break;
            }
        }
        curr->pos = new int;
        *(curr->pos) = from;
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
                    isfound = 0;
                    // cout<<"detection unsuccessfull at "<< j<<endl;
                    break;
                }

                curr = curr->alp[patterns[k][j]-'a'];

                

                int l = curr->str_loc.first;
                int r = curr->str_loc.second;
                // cout<<l<<" "<<r<<endl;
                // cout<<Text[l]<<" "<<patterns[k][j]<<endl;
                while(Text[l]==patterns[k][j] && l<=r && j<patterns[k].size()){
                    // cout<<j<<"th match successfull "<<endl;
                    l++;j++;
                }
                if(l>r && j<patterns[k].size()){
                    // curr = curr->alp[Text[l]-'a'];
                    continue;
                }else if(j== patterns[k].size()){
                    // cout<<"successfully!!"<<endl;
                    break;
                }else if(l<=r){
                    isfound = 0;
                    // cout<<"detection unsuccessfull somehow at "<< j<<endl;
                    break;
                }

                // curr = curr->alp[patterns[k][j]-'a'];
                // cout<<j<<" ";
                // j++;
            }
            // cout<<endl;
            if(!isfound){
                // cout<<"Not found"<<endl;
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
    suffix_Tree suffixTrie(Text);
    vector<pair<int, int>> ans = suffixTrie.detect_matches(patterns);
    cout<<"\nanswers \n"<<ans.size()<<endl;
    for(int i= 0; i<ans.size(); i++){
        cout<<ans[i].first<<" "<<ans[i].second<<"\n";
    }

    return 0;
}