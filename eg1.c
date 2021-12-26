#include<stdio.h>
#include<stdlib.h>

struct node
{
int num;
struct node *right,*left;
}; 
struct node *start;

struct stack
{
struct node *ptr;
struct stack *previous;
};

struct stack *stackStart=NULL;

void push(struct node *p)
{
struct stack *j;
j=(struct stack *)malloc(sizeof(struct stack));
j->ptr=p;

j->previous=stackStart;
stackStart=j;
}

struct node * pop()
{
struct node *t;
struct stack *j;
t=stackStart->ptr;
j=stackStart->previous;
free(stackStart);
stackStart=j;
return t;
}

int getHeightUsingRecursion(struct node *p)
{
int lch,rch;

if(p==NULL) return 0;
lch=getHeightUsingRecursion(p->left);
rch=getHeightUsingRecursion(p->right);

if(lch>rch) return lch+1;
else return rch+1;

}

struct node * elementAtTop()
{
return stackStart->ptr;
}

int isEmpty()
{
if(stackStart!=NULL) return 0;
else return 1;
}

void balanceTree()
{

struct node *parent,*rc,*rclc,*lc,*lcrc,*root;
struct node **p2p;
int rch,lch,diff;
while(stackStart!=NULL)
{


root=pop();

rch=getHeightUsingRecursion(root->right);
lch=getHeightUsingRecursion(root->left);
diff=rch-lch;


if(diff>=-1 && diff<=1)  continue;



if(root==start) p2p=&start;
else
{
parent=elementAtTop();
if(parent->right==root) p2p=&parent->right;
else p2p=&parent->left;
}

if(rch>lch)    //right is heavy
{

rc=root->right;
if(getHeightUsingRecursion(rc->left)>getHeightUsingRecursion(rc->right))    
{ 
rclc=rc->left;                                                  //right is left heavy
root->right=rclc;
rc->left=rclc->right;
rclc->right=rc;
rc=root->right;
}

// Now 100% right is right heavy


root->right=rc->left;
rc->left=root;
*p2p=rc;
}
else          //left is heavy
{


lc=root->left;
if(getHeightUsingRecursion(lc->right)>getHeightUsingRecursion(lc->left))   
{
lcrc=lc->right;                                        // left is right heavy
root->left=lcrc;
lc->right=lcrc->left;
lcrc->left=lc;
lc=root->left;
}

//now 100% left is left heavy
*p2p=lc;
root->left=lc->right;
lc->right=root;
}


}            //ending point of loop



}






int addToTree(int num)
{

struct node *j;
j=(struct node *)malloc(sizeof(struct node));
j->num=num;
j->right=j->left=NULL;
struct node *p,*t;

if(start==NULL)
{
start=j;

}
else
{
         
p=start;
while(p->num!=num)
{ 

push(p);
     
if(p->num<num)
{
if(p->right==NULL)
{
p->right=j;
break;
}
else p=p->right;

}
else
{
if(p->left==NULL)
{
p->left=j;
break;
}
else  p=p->left;

}


}

if(p->num==num)
{
return 0;
}


}

if(start!=j) balanceTree();

return 1;

}

struct queue
{
struct node *p;
struct queue *next;
};

struct queue *queueStart, *queueEnd;

void addToQueue(struct node *t)
{
struct queue *j,*m;
j=(struct queue *)malloc(sizeof(struct queue));
j->p=t;
j->next=NULL;
if(queueStart==NULL) 
{
queueStart=j;
queueEnd=j;
}
else
{
queueEnd->next=j;
queueEnd=j;
}
}


struct node * removeFromQueue()
{
struct queue *t;
struct node *p;
t=queueStart;
p=t->p;
if(t->next==NULL) queueStart=NULL;
else queueStart=t->next;
free(t);
return p;
}

void levelOrderTraversal()
{
struct node *t;
int insertionCount,levelNumber=1;
int j,x;

if(start==NULL) return;
addToQueue(start);
insertionCount=1;

while(queueStart!=NULL)
{
x=0;
j=1;
printf("\n\n\t........................\n");
printf("\t%d\n",levelNumber);
printf("\t........................\n");
levelNumber++;
while(insertionCount>=j)
{

t=removeFromQueue();
printf("%d\n",t->num);
if(t->left!=NULL)
{
addToQueue(t->left);
x++;
}
if(t->right!=NULL)
{
addToQueue(t->right);
x++;
}
j++;
}
insertionCount=x;
}

}


int removeFromTree(int num)
{
struct node *t,*j,*e,*f;
int k;

t=start;
while(t!=NULL)
{
if(t->num!=num) 
{
push(t);            //push upto num(remove)
}
else break;
j=t;
if(t->num<num) t=t->right;
else t=t->left;
}

if(t==NULL) return 0;

if(t->left==NULL && t->right==NULL)     //num is leaf node
{
if(start==t)
{
start=NULL;
free(t);
return 1;
}
else
{
if(j->left==t) j->left=NULL;
else j->right=NULL;
free(t);
}



}
else
{
if(t->right!=NULL)   //successor 
{

for(e=t->right;  e->left!=NULL; e=e->left)
{
f=e;
addToQueue(e);      //add to queue
}

if(t->right==e)
{
e->left=t->left;
}
else
{
f->left=e->right;
e->left=t->left;
e->right=t->right;
}

if(start==t)
{
start=e;
}
else
{
if(j->right==t) j->right=e;
else j->left=e;
}

push(e);     //push successor
free(t);
}
else      //predecessor
{

for(e=t->left; e->right!=NULL; e=e->right)
{
f=e;
addToQueue(e);         //Add to queue
}

if(e==t->left)
{
e->right=t->right;
}
else
{
f->right=e->left;
e->right=t->right;
e->left=t->left;
}

if(start==t)
{
start=e;
}
else
{
if(j->left==t) j->left=e;
else  j->right=e;
}

push(e);        // push predecessor
free(t);

}
k=1;
}

while(0)
{
j=pop();
printf("j->num=(%d)\n",j->num);
}


while(queueStart!=NULL)     
{

j=removeFromQueue(); 
push(j);
}


balanceTree();

return 1;
}



void findHeight(int num)
{
struct node *p;
int h;
p=start;
while(p!=NULL)
{
if(p->num==num) break;
if(p->num<num) p=p->right;
else p=p->left;
}

h=getHeightUsingRecursion(p);
printf("height is ..... (%d) ...\n\n",h);
return;
}

void inorderTraversalUsingRecursion(struct node *p)
{
if(p==NULL) return;
inorderTraversalUsingRecursion(p->left);
printf("%d\n",p->num);
inorderTraversalUsingRecursion(p->right);

}

int main()
{
int ch,num;
start=NULL;
queueStart=queueEnd=NULL;
printf("\n...........................\n\n");
printf("\tAVL TREE\n\nAdd element, remove element, level order traversal, Inorder traversal using recursion\n");
printf("..........................\n\n");


while(1)
{
printf("1. Add Element\n");
printf("2. level order traversal\n");
printf("3. remove element\n");
printf("4. inorder traversal using recursion\n");
printf("5. height of tree \n");
printf("enter your choice:");
scanf("%d",&ch);  fflush(stdin);

if(ch==1)
{
printf("enter num: ");
scanf("%d",&num);   fflush(stdin);
if(addToTree(num))  printf("%d is added to node....\n",num);
else  printf("%d is not added to tree.....\n",num);
}

if(ch==2)
{
levelOrderTraversal();
}

if(ch==3)
{
printf("enter number to remove : ");
scanf("%d",&num);  fflush(stdin);
if(removeFromTree(num))  printf("%d is removd from tree...\n",num);
else  printf("%d is not found in tree...\n",num);

}

if(ch==4)
{

inorderTraversalUsingRecursion(start);

}

if(ch==5)
{
printf("enter num get height : ");
scanf("%d",&num); fflush(stdin);

findHeight(num);

}



}



return 0;
}
