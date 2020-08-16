#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

#define max 15

using namespace std;


typedef struct
 {
  node *next;
  int key;
  string id;
  string lastname;
  string firstname;
 } pdata;

class node
{
 public:
 int noofkeys;
 pdata data[max];
 node *father;
 node *first;
 node();
 int leafnode();
 void insertinanode(pdata x);
 pdata splitanode(pdata x);
 node *nextindex(int x);
 void display();
};

void node::display()
{
 cout<<"("<<"\n";
 for(int i=0;i<noofkeys;i++)
 cout<<data[i].id<<"  "<<data[i].lastname<<"  "<<data[i].firstname<<"\n";
 cout<<")"<<"\n";
}

node *node::nextindex(int x)
{
	int i2;

 if(x<data[0].key)
 return(first);
 for(i2=0;i2<noofkeys;i2++)
 {
 	if(x<=data[i2].key)
 		return data[i2-1].next;
 }
 return data[i2-1].next;
}

int node::leafnode()
{
 if(data[0].next==NULL)
 	return 1;
 return 0;
}

void node::insertinanode(pdata x)
{
	int i1;

 for(i1=noofkeys-1;i1>=0&&data[i1].key>x.key;i1--)
 {
 	data[i1+1]=data[i1];
 }
 data[i1+1]=x;
 noofkeys++;
}

pdata node::splitanode(pdata x)
{
 node *t;
 pdata mypdata;
 int i,j,centre;
 centre=(noofkeys-1)/2;
 t=new node;
 if(x.key>data[centre].key)
 {
  for(i=centre+1,j=0;i<=noofkeys;i++,j++)
  t->data[j]=data[i];
  t->noofkeys=noofkeys-centre-1;
  noofkeys=noofkeys-t->noofkeys;
  t->insertinanode(x);
  t->first=t->data[0].next;
  t->father=father;
  mypdata.key=t->data[0].key;
  mypdata.next=t;
  for(i=1;i<t->noofkeys;i++)
  t->data[i-1]=t->data[i];
  t->noofkeys--;
 }
 else
 {
  for(i=centre,j=0;i<noofkeys;i++,j++)
  t->data[j]=data[i];
  t->noofkeys=noofkeys-centre;
  noofkeys=noofkeys-t->noofkeys;
  insertinanode(x);
  t->father=father;
  mypdata.key=t->data[0].key;
  mypdata.next=t;
  for(i=1;i<t->noofkeys;i++)
  t->data[i-1]=t->data[i];
  t->noofkeys--;
 }
 return(mypdata);
}

node::node()
{
 for(int i=0;i<=max;i++)
 data[i].next=NULL;
 noofkeys=0;
 father=NULL;
 first=NULL;
}

class q
{
 node *data[60];
 int r,f;
 public:
 q()
 {
  r=f=0;
 }
 int empty()
 {
  if(r==f)
  return 1;
  else
  return 0;
 }
 node *deque()
 {
  return data[f++];
 }
 void enque(node *x)
 {
  data[r++]=x;
 }
 void makeempty()
 {
  r=f=0;
 }
};

class btree
{
 int mkeys;
 node *root;
 public:
 btree(int n)
 {
  mkeys=n;
  root=NULL;
 }
 int size();
 void insert(int x, string id, string ls, string fs);
 void displaytree();
 node *search(int x);
 void delet(int x);
};

int btree::size()
{
	return mkeys;
}

node *btree::search(int x)
{
 node *p;
 int i;
 p=root;
 while(p!=NULL)
 {
  for(i=0;i<p->noofkeys;i++)
  if(x==p->data[i].key)
  return(p);
  p=p->nextindex(x);
 }
 return NULL;
}

void btree::displaytree()
{
 q q1,q2;
 node *p;
 q1.enque(root);
 while(!q1.empty())
 {
  q2.makeempty();
  cout<<"\n";
  while(!q1.empty())
  {
   p=q1.deque();
   p->display();
   cout<<" ";
   if(!p->leafnode())
   {
    q2.enque(p->first);
    for(int i=0;i<p->noofkeys;i++)
    q2.enque(p->data[i].next);
   }
  }
  q1=q2;
 }
}

void btree::insert(int x, string id, string ls, string fs)
{
 pdata mypdata;
 node *p,*q;
 mypdata.key=x;
 mypdata.id = id;
 mypdata.lastname = ls;
 mypdata.firstname=fs;
 mypdata.next=NULL;
 if(root==NULL)
 {
  root=new node;
  root->insertinanode(mypdata);
 }
 else
 {
  p=root;
  while(!(p->leafnode()))
  p=p->nextindex(x);
  if(p->noofkeys<mkeys)
  p->insertinanode(mypdata);
  else
  {
   mypdata=p->splitanode(mypdata);
   while(1)
   {
    if(p==root)
    {
     q=new node;
     q->data[0]=mypdata;
     q->first=root;
     q->father=NULL;
     q->noofkeys=1;
     root=q;
     q->first->father=q;
     q->data[0].next->father=q;
     return;
    }
    else
    {
     p=p->father;
     if(p->noofkeys<mkeys)
     {
      p->insertinanode(mypdata);
      return;
     }
     else
     mypdata=p->splitanode(mypdata);
    }
   }
  }
 }
}

void btree::delet(int x)
{
 node *left,*right;
 pdata *centre;
 node *p,*q;
 int i,j,centreindex;
 p=search(x);
 for(i=0;p->data[i].key!=x;i++)
 if(!p->leafnode())
 {
  q=p->data[i].next;
  while(!q->leafnode())
  q=q->first;
  p->data[i].key=q->data[0].key;
  p->data[i].id=q->data[0].id;
  p->data[i].lastname=q->data[0].lastname;
  p->data[i].firstname=q->data[0].firstname;
  p=q;
  x=q->data[0].key;
  i=0;
 }
 for(i=i+1;i<p->noofkeys;i++)
 p->data[i-1]=p->data[i];
 p->noofkeys--;
 while(1)
 {
  if(p->noofkeys>=mkeys/2)
  return;
  if(p==root)
  if(p->noofkeys>0)
  return;
  else
  {
   root=p->first;
   return;
  }
  q=p->father;
  if(q->first==p||q->data[0].next==p)
  {
   left=q->first;
   right=q->data[0].next;
   centre=&(q->data[0]);
   centreindex=0;
  }
  else
  {
   for(i=1;i<q->noofkeys;i++)
   if(q->data[i].next==p)
   break;
   left=q->data[i-1].next;
   right=q->data[i].next;
   centre=&(q->data[i]);
   centreindex=i;
  }
  if(left->noofkeys>mkeys/2)
 {
  right->data[i+1]=right->data[i];
  right->noofkeys++;
  right->data[0].key=centre->key;
  right->data[0].id=centre->id;
  right->data[0].lastname=centre->lastname;
  right->data[0].firstname=centre->firstname;
  centre->key=left->data[left->noofkeys-1].key;
  centre->id=left->data[left->noofkeys-1].id;
  centre->lastname=left->data[left->noofkeys-1].lastname;
  centre->firstname=left->data[left->noofkeys-1].firstname;
  left->noofkeys--;
  return;
 }
 else
 if(right->noofkeys>mkeys/2)
 {
  left->data[left->noofkeys].key=centre->key;
  left->data[left->noofkeys].id=centre->id;
  left->data[left->noofkeys].lastname=centre->lastname;
  left->data[left->noofkeys].firstname=centre->firstname;
  left->noofkeys++;
  centre->key=right->data[0].key;
  centre->id=right->data[0].id;
  centre->lastname=right->data[0].lastname;
  centre->firstname=right->data[0].firstname;
  for(i=1;i<right->noofkeys;i++)
  right->data[i-1]=right->data[i];
  right->noofkeys--;
  return;
 }
 else
 {
  left->data[left->noofkeys].key=centre->key;
  left->data[left->noofkeys].id=centre->id;
  left->data[left->noofkeys].lastname=centre->lastname;
  left->data[left->noofkeys].firstname=centre->firstname;
  left->noofkeys++;
  for(j=0;j<right->noofkeys;j++)
  left->data[left->noofkeys+j]=right->data[j];
  left->noofkeys+=right->noofkeys;
  for(i=centreindex+1;i<q->noofkeys;i++)
  q->data[i-1]=q->data[i];
  q->noofkeys--;
  p=q;
 }
}
}