// Shubhanshu Verma

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct node{

   long int id;
   int color;
   long int size;
   struct node* left;
   struct node* right;
   struct node* parent;

};

struct node* make_node(long int id, int color, struct node* left, struct node* right, struct node* parent);
struct node* make_nil_node();
struct node* left_rotate(struct node* root, struct node* x);
struct node* right_rotate(struct node* root, struct node* x);
struct node* insert_node(struct node* root, long int id);
struct node* tree_minimum(struct node* x);
struct node* tree_successor(struct node* x);
struct node* delete_fixup(struct node* root, struct node* x);
struct node* delete_node(struct node* root, struct node* z);
void inorder(struct node* p);
void preorder(struct node* p);
void size_updator(struct node* x);
void size_updator_del(struct node* x);
struct node* node_search(struct node* x, long int key);
struct node* OS_select(struct node* x, long int i);
long int OS_rank(struct node* root, struct node* x);
int Josephus(long int n, long int m);

struct node* nil = make_nil_node();


int main(){

   int n,k,j;
   //cin >> n >> k;

   long int i;
   ofstream myfile1,myfile2;
   long int x;
   double y;

   myfile1.open("datafilex.csv");
   myfile2.open("datafiley.csv");

   for(i=10000;i<=12000;i++){

      y = 0;

      for(j=0;j<10;j++){

         auto start = std::chrono::high_resolution_clock::now();

         x = Josephus(i,2);

         auto end = std::chrono::high_resolution_clock::now();

         y += (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()/1000000000;

      }

      y = y/10;

      myfile1 << x << "\n";
      myfile2 << y << "\n";

   }

   return 0;

}

struct node* make_nil_node(){

    struct node* new_node;
   new_node = (struct node*)malloc(sizeof(struct node));

   new_node->id = 0;
   new_node->color = 1;
   new_node->size = 0;
   new_node->left = NULL;
   new_node->right = NULL;
   new_node->parent = NULL;

   return new_node;

}

struct node* make_node(long int id, int color, struct node* left, struct node* right, struct node* parent){

   struct node* new_node;
   new_node = (struct node*)malloc(sizeof(struct node));

   new_node->id = id;
   new_node->color = color;
   new_node->size = 1;
   new_node->left = left;
   new_node->right = right;
   new_node->parent = parent;

   return new_node;

}

struct node* left_rotate(struct node* root, struct node* x){

   //Assuming x->right is not NULL
   struct node* y = x->right;

      x->right = y->left;

      if(y->left->id != 0){

         y->left->parent = x;
         x->size = x->size - y->size + y->left->size;
         y->size = y->size - y->left->size + x->size;

      }else{

         x->size = x->size - y->size;
         y->size = y->size + x->size;

      }

      y->parent = x->parent;

      if(x->parent == NULL){

         root = y;

      }else if( x == x->parent->left){

         x->parent->left = y;

      }else{

         x->parent->right = y;

      }

      y->left = x;
      x->parent = y;

   return root;

}


struct node* right_rotate(struct node* root, struct node* x){

   //Assuming x->left is not NULL
   struct node* y = x->left;

      x->left = y->right;

      if(y->right->id != 0){

         y->right->parent = x;
         x->size = x->size - y->size + y->right->size;
         y->size = y->size - y->right->size + x->size;

      }else{

         x->size = x->size - y->size;
         y->size = y->size + x->size;

      }

      y->parent = x->parent;

      if(x->parent == NULL){

         root = y;

      }else if( x == x->parent->left){

         x->parent->left = y;

      }else{

         x->parent->right = y;

      }

      y->right = x;
      x->parent = y;

   return root;

}

void size_updator(struct node* x){

   struct node* p = x->parent;

   while(p!=NULL){

      p->size = p->size + 1;
      p = p->parent;

   }

}

void size_updator_del(struct node* x){

   struct node* p = x->parent;

   while(p!=NULL){

      p->size = p->size - 1;
      p = p->parent;

   }

}

void inorder(struct node* p){

    if(p->id != 0){

        inorder(p->left);
        cout << p->id << " ";
        inorder(p->right);

    }

}

void preorder(struct node* p){

    if(p->id != 0){

        cout << p->id << " " << p->size << " " << p->color << "   ";
        preorder(p->left);
        preorder(p->right);

    }

}

struct node* insert_node(struct node* root, long int id){

   struct node* y = root;
   struct node* x = make_node(id,0,nil,nil,NULL);
   struct node* p;

   while(y->id != 0){

      p = y;

      if(y->id > id){

         y = y->left;

      }else{

         y = y->right;

      }

   }

   x->parent = p;

   if(p == NULL){

      root = x;

   }else if(p->id > x->id){

      p->left = x;

   }else{

      p->right = x;

   }

   size_updator(x);

   int color;

   while(x != root && x->parent->color == 0){

         p = x->parent;

         if(p == p->parent->left ){

               y = p->parent->right;

               if(y->id != 0 && y->color == 0){

                  p->color = 1;
                  y->color = 1;
                  p->parent->color = 0;
                  x = p->parent;

               }else{

                  if(x == p->right){

                     x = p;
                     root = left_rotate(root,x);
                     p = x->parent;

                  }

                     p->color = 1;
                     p->parent->color = 0;
                     root = right_rotate(root,p->parent);

               }



         }else{

               y = p->parent->left;

               if(y->id != 0 && y->color == 0){

                  p->color = 1;
                  y->color = 1;
                  p->parent->color = 0;
                  x = p->parent;

               }else{

                    if(x == p->left){

                        x = p;
                        root = right_rotate(root,x);
                        p = x->parent;

                    }

                        p->color = 1;
                        p->parent->color = 0;
                        root = left_rotate(root,p->parent);

               }


         }

   }

   root->color = 1;
   return root;

}

struct node* tree_minimum(struct node* x){

   while(x->left->id != 0){

      x = x->left;

   }

   return x;

}

struct node* tree_successor(struct node* x){

   if(x->right->id != 0){

      return tree_minimum(x->right);

   }

   struct node* y = x->parent;

   while(y->id != 0 && x == y->right){

      x = y;
      y = x->parent;

   }

   return y;

}

struct node* node_search(struct node* x, long int key){

      while(x->id != 0 && key != x->id){

         if(key < x->id){

            x = x->left;

         }else{

            x = x->right;

         }

      }

      return x;

}

struct node* delete_node(struct node* root, struct node* z){

   struct node* x;
   struct node* y;

   if(z->left->id == 0 || z->right->id == 0){

      y = z;
      size_updator_del(z);

   }else{

      y = tree_successor(z);
      size_updator_del(y);

   }

   if(y->left->id != 0){

      x = y->left;
      x->parent = y->parent;

   }else if(y->right->id != 0){

      x = y->right;
      x->parent = y->parent;

   }else{

      x = nil;
      x->parent = y->parent;

   }

   if(y->parent == NULL){

      root = x;

   }else if(y == y->parent->left){

      y->parent->left = x;

   }else{

      y->parent->right = x;

   }

   if(y != z){

      z->id = y->id;

   }

   y->parent = NULL;
   y->left = NULL;
   y->right = NULL;

   if(y->color == 1){

      root = delete_fixup(root,x);

   }

   free(y);

   return root;

}

struct node* delete_fixup(struct node* root, struct node* x){

   struct node* p;
   struct node* w;

   while(x != root && x->color == 1){

      p = x->parent;

      if(x == p->left){

         w = p->right;

         if(w->color == 0){

            w->color = 1;
            p->color = 0;
            root = left_rotate(root,p);
            w = p->right;

         }

         if(w->id != 0 && w->left->color == 1 && w->right->color == 1){

            w->color = 0;
            x = p;
            p = x->parent;

         }else{

            if(w->id != 0 && w->right->color == 1){

               w->left->color = 1;
               w->color = 0;
               root = right_rotate(root,w);
               w = p->right;

            }

            if(w->id != 0){

               w->color = p->color;
               p->color = 1;
               w->right->color = 1;
               root = left_rotate(root,p);

            }

            x = root;

         }

      }else{

         w = p->left;

         if(w->color == 0){

            w->color = 1;
            p->color = 0;
            root = right_rotate(root,p);
            w = p->left;

         }

         if(w->id != 0 && w->left->color == 1 &&  w->right->color == 1){

            w->color = 0;
            x = p;
            p = x->parent;

         }else{

            if(w->id != 0 && w->left->color == 1){

               w->right->color = 1;
               w->color = 0;
               root = left_rotate(root,w);
               w = p->left;

            }

            if(w->id != 0){

               w->color = p->color;
               p->color = 1;
               w->left->color = 1;
               root = right_rotate(root,p);

            }

            x = root;

         }

      }

      nil->color = 1;

   }

   x->color = 1;
   return root;

}


struct node* OS_select(struct node* x, long int i){

   long int r = x->left->size + 1;

   if(i == r){

      return x;

   }else if(i < r){

      return OS_select(x->left,i);

   }else{

      return OS_select(x->right,i-r);

   }

}

long int OS_rank(struct node* root, struct node* x){

   long int r = x->left->size + 1;
   struct node* y = x;
   struct node* p;

   while(y != root){

      if(y == y->parent->right){

         p = y->parent;
         r = r + p->left->size + 1;

      }

      y = y->parent;

   }

   return r;

}

int Josephus(long int n, long int m){

   long int i;

   struct node* root = make_node(1,1,nil,nil,NULL);
   struct node* x;

   for(i=2;i<=n;i++){

        root = insert_node(root,i);

   }

   long int k,j;
   j = 1;

   for(k=n;k>1;k--){

      j = ((j+m-2)%k) + 1;

      x = OS_select(root,j);

      root = delete_node(root,x);
      //preorder(root);
      //cout << endl;

   }

   return root->id;

}
