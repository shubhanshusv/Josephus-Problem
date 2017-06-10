// Shubhanshu Verma

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct node{

   long int id;
   int color;

   struct node* left;
   struct node* right;
   struct node* parent;

};

struct node* make_node(long int id, int color, struct node* left, struct node* right, struct node* parent);
struct node* left_rotate(struct node* root, struct node* x);
struct node* right_rotate(struct node* root, struct node* x);
struct node* insert_node(struct node* root, long int id);

int main(){

   int n,k;
   cin >> n >> k;

   long int i;
   struct node* root = make_node(1,1,NULL,NULL,NULL);

   for(i=2;i<=n;i++){

        root = insert_node(root,i);

   }



   return 0;

}

struct node* make_node(long int id, int color, struct node* left, struct node* right, struct node* parent){

   struct node* new_node;
   new_node = (struct node*)malloc(sizeof(struct node));

   new_node->id = id;
   new_node->color = color;
   new_node->left = left;
   new_node->right = right;
   new_node->parent = parent;

   return new_node;

}

struct node* left_rotate(struct node* root, struct node* x){

   //Assuming x->right is not NULL
   struct node* y = x->right;

   //if(y != NULL){

      x->right = y->left;

      if(y->left != NULL){

         y->left->parent = x;

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

   //}

   return root;

}


struct node* right_rotate(struct node* root, struct node* x){

   //Assuming x->left is not NULL
   struct node* y = x->left;

   //if(y != NULL){

      x->left = y->right;

      if(y->right != NULL){

         y->right->parent = x;

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

   //}

   return root;


}

struct node* insert_node(struct node* root, long int id){

   struct node* y = root;
   struct node* x = make_node(id,0,NULL,NULL,NULL);
   struct node* p;

   while(y != NULL){

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

   int color;

   while(x != root && x->parent->color == 0){

         p = x->parent;

         if(p == p->parent->left ){

               y = p->parent->right;

               if(y == NULL){

                  color = 1;

               }else{

                  color = y->color;

               }

               if(color == 0){

                  p->color = 1;
                  y->color = 1;
                  p->parent->color = 0;
                  x = p->parent;

               }else{

                  if(x == p->right){

                     x = p;
                     root = left_rotate(root,x);

                  }

                  p = x->parent;

                  if(p != NULL){

                     p->color = 1;
                     p->parent->color = 0;
                     root = right_rotate(root,p->parent);

                  }

               }



         }else{

               y = p->parent->left;

               if(y == NULL){

                  color = 1;

               }else{

                  color = y->color;

               }

               if(color == 0){

                  p->color = 1;
                  y->color = 1;
                  p->parent->color = 0;
                  x = p->parent;

               }else{

                    if(x == p->left){

                        x = p;
                        root = right_rotate(root,x);

                    }

                    p = x->parent;

                    if(p != NULL){

                        p->color = 1;
                        p->parent->color = 0;
                        root = left_rotate(root,p->parent);

                     }

               }


         }

   }

   root->color = 1;
   return root;

}

