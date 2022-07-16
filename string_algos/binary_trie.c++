#include<bits/stdc++.h>
using namespace std;

class Node{
    Node* link[2];
    bool containsKey(int bit){
        return link[bit]!=nullptr;
    }
    Node* get(int bit){
        return link[bit];
    }
    void put(int bit, Node* node){
        link[bit] = node;
    }
};

class Trie{
    Node* root;
    public:
    Trie(){
        root = new Node();
    }
    void insert(int num){
        Node* node = root;
        for(int i = 31; i>=0; i--){
            int bit = (num>>i)&1;
            if(!node->containsKey(bit)){
                node->put(bit);
            }
            node = node->get(bit);
        }
    }
    int getMax_xor_Num(int num){
        Node* node = root;
        int Maxnum = 0;
        for(int i=31; i>=0; i--){
            int bit = (num>>i)&1;
            if(node->containsKey(1-bit)){
                Maxnum |=(1<<i);
                node = node->get(1-bit);
            }else{
                node = node->get(bit);
            }
        }
        return Maxnum;
    }
}

int main(){

    return 0;
}