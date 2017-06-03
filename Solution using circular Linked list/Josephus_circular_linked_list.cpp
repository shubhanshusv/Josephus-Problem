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

	int key;
	struct node* next; 

};

struct node* make_node(int key);
void delete_entry(struct node* prev_entry);

int main(){

   int n,k;
   cin >> n >> k;

   int i;
   int count = 0;

   // Making the start node of the list;

   struct node* root;
   root = make_node(1);

   struct node* p;
   p = root;


   // Making the circular link list for entries

   for(i=1;i<n;i++){

   		p->next = make_node(i+1);
   		p = p->next;

   }

   p->next = root;  // linking last entry to 1st entry, hence making the linked list circular

   // Start deleting entries

   p = root;

   while(n != 1){

   		count = 0;

   		while(count != k-2){

   			p = p->next;
   			count++;

   		}

   		delete_entry(p);
   		p = p->next;
   		n--;

   }

   cout << p->key << endl;

   return 0;

}

struct node* make_node(int key){

	struct node* new_node;
	new_node = (struct node*)malloc(sizeof(struct node));

	new_node->key = key;
	new_node->next = NULL;

	return new_node;

}


void delete_entry(struct node* prev_entry){

	struct node* p;
	p = prev_entry->next;

	prev_entry->next = p->next;
	p->next = NULL;

	p = NULL;

}
