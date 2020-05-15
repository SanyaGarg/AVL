#include<bits\stdc++.h>

using namespace std;

struct Node{

    Node* left,*right;
    int data,height;
    int lcnt,rcnt;

    Node(int x){
        data = x;
        left = NULL;
        right = NULL;
        height =1;
        lcnt =0;
        rcnt =0;
    }
};

int height(Node* root){

    if(root==NULL)return 0;

    return root->height;
}

int balance(Node* node){

    if(node==NULL)return 0;

    return height(node->right)-height(node->left);
}

Node* rightRotate(Node* root){

    if(root==NULL)return NULL;

    Node* l = root->left;
    Node* r = l->right;

    l->right = root;
    root->left = r;

    root->height = max(height(root->right),height(root->right))+1;
    l->height = max(height(l->left),height(l->right))+1;
    return l;
}

Node* leftRotate(Node* root){

    if(root==NULL)return NULL;

    Node* r = root->right;
    Node* l = r->left;

    root->right = l;
    r->left = root;

   root->height = max(height(root->right),height(root->right))+1;
    r->height = max(height(r->left),height(r->right))+1;

    return r;
}

Node* insert(Node* node,int data){

    if(node==NULL){
        Node* root = new Node(data);
        return root;
    }

    if(data>node->data) {
        node->right = insert(node->right,data);
        node->rcnt++;
    }
    else if(data<node->data){
        node->left= insert(node->left,data);
        node->lcnt++;
    }
    else return node;

    node->height = 1 + max( height(node->left), height(node->right) );

    int b = balance(node);

    if(b>1 && node->right->data<data)return leftRotate(node);
    else if(b>1 && node->right->data>data){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }else if(b<-1 && node->left->data<data)return rightRotate(node);
    else if(b<-1 && node->left->data>data){
        node->left = leftRotate(node->left);
        return rightRotate(node);
     }
     
     return node;
}

Node* search(Node* node,int data){

    if(node==NULL)return NULL;

    if(data > node->data)search(node->right,data);
    else if(data < node->data)search(node->left,data);
    return node;
}

Node* FindMax(Node* root){

    if(root->right == NULL)return root;

    return FindMax(root->right);
}

Node* del(Node* root,int data){

    if(root==NULL)return root;

   // cout << root->data << endl;
       
    if ( data < root->data )  
        root->left = del(root->left, data);  
    else if( data > root->data )  
        root->right = del(root->right, data);  
    else
    {  
        if((root->right==NULL) && (root->left==NULL)){
            root = NULL;
        }else if((root->right==NULL) && (root->left!=NULL)){
            *root = *(root->left);
        }else if((root->right!=NULL) && (root->left==NULL)){
            *root = *(root->right);
        }else{
            Node* max = FindMax(root->left);
            root->data = max->data;
            root->left = del(root->left,max->data);
        }
    }

   // cout << root->data << endl;
   
    if(root==NULL)return root;

   root->height = 1 + max( height(root->left), height(root->right) );

   // cout << root->height <<endl;
   int b = balance(root);

   if(b>1 && balance(root->right)>=0)return leftRotate(root);
   if(b<-1 && balance(root->left)<=0)return rightRotate(root);
   if(b>1 && balance(root->right)<0){
       rightRotate(root->right);
       return leftRotate(root);
   }  
   if(b<-1 && balance(root->left)>0) 
   {
       leftRotate(root->left);
       return rightRotate(root);
   } 
     return root;
}

Node* ksmall(Node* node,int k){

    if(node==NULL)return NULL;

    int count = node->lcnt+1;
    if(count == k)return node; 

    if(count > k)return ksmall(node->left,k);

    return ksmall(node->right,k);
}

int gnodes(Node* node,int x){

    if(node==NULL)return 0;

    if(node->data==x)return node->rcnt;

    if(node->data>x){
        //cout << "Hi";
        node->rcnt++;
        return node->rcnt+gnodes(node->left,x);
    }

    return gnodes(node->right,x);
} 

void InOrder(Node* node){

    if(node==NULL)return;

    cout << node->data;
    InOrder(node->left);
    InOrder(node->right);
}

int main(){

    int n;
    cin >> n;

    int data;

    Node* root = NULL;  
    for(int i=0;i<n;i++){
        cin >> data;
        root = insert(root,data);
    }

    InOrder(root);
    cout << endl;
//     root = del(root,4);
//     InOrder(root);
//      cout << endl;
//    cout << root->right->data;
    //cout << root->left->rcnt;
    cout << gnodes(root,4);

}