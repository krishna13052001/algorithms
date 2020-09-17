#include<stdio.h>
#include<stdlib.h>
typedef struct node {
   int data;
   int priority;
   int lpast;
   struct node* next;
}Node;
int arr[40],count=0;
Node* newNode(int d, int p,int past) {
   Node* temp = (Node*)malloc(sizeof(Node));
   temp->data = d;          
   temp->priority = p;
   temp->lpast=past;
   temp->next = NULL;
   return temp;
}

int peek(Node** head) {
   return (*head)->data;
}
int peekPriority(Node** head){
    return (*head)->priority;
}

int peekPath(Node** head) {
   return (*head)->lpast;
}

void push(Node** head, int d, int p,int past) {
   Node* start = (*head);
   Node* temp = newNode(d, p,past);
   if ((*head)->priority > p) {
      temp->next = *head;
      (*head) = temp;
   } else {
      while (start->next != NULL &&
      start->next->priority < p) {
         start = start->next;
      }
      temp->next = start->next;
      start->next = temp;
   }
}

void pop(Node** head) {
   Node* temp = *head;
   (*head) = (*head)->next;
   free(temp);
}

int isEmpty(Node** head) {
   return (*head) == NULL;
}

int isPreset(Node** head,int d,int p,int ch){
    Node* start =(*head);
    while (start->next != NULL)
    {
        if(start->data==d){
            if(start->priority>p){
                start->priority=p;
                start->lpast=ch;
                return 1;
            }
        }
        start=start->next;
    }
    return 0;
}

void finalPath(Node** head,int d){
    int d1=d;
    int flag=0;
    for(;;){
        Node* start =(*head);
        while(start!=NULL){
            // printf("%d hi hi\n",start->data);
            if(start->data==d1){
                // printf("%d ",start->data);
                arr[count]=start->data;
                count++;
                d1=start->lpast;
                break;
            }
            if(d1==-1){
                flag=1;
            }
            start=start->next;
            // printf("the second value %d\n",start->data);
        }
        if(flag==1){
            break;
        }
    }
}

int verify(Node** head){
    Node* start=*head;
    //printf("%d",start->data);
    if(start==NULL){
        return 1;
    }
    else{
        return 0;
    }
    
}

int main(){
    int n,m,i,j;
    //printf("Enter no of node:\t");
    scanf("%d %d",&m,&n);
    int a[m][m],goal;
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            a[i][j]=0;
        }
    }
    //printf("Enter no of edges:\t");
    // scanf("%d",&n);
    int sn,dn,ev;
    for(i=0;i<n;i++){
        //printf("Enter the start node  desitation node and value of the edge:\t");
        scanf("%d %d %d",&sn,&dn,&ev);
        a[sn][dn]=ev;
    }
    //printf("Zero will be my start state\n");
    //printf("Enter the Goal state\t");
    scanf("%d",&goal);

    Node* fringe=newNode(0,0,-1);
    Node* closed=newNode(0,0,-1);
    int prev=0,flag=0;
    for(;;)
    {
        int data=peek(&fringe);
        int pr=peekPriority(&fringe);
        if(isPreset(&closed,data,pr,peekPath(&fringe))==0){
            push(&closed,data,pr,peekPath(&fringe));
        }
        //printf("\nThe closed list when the data is %d %d\n",peek(&closed),peekPriority(&closed));
        if (data==goal){
            break;
        }
        for(i=0;i<m;i++){
            if(a[data][i]!=0){
                int p=pr+a[data][i];
                if(isPreset(&fringe,i,p,data)==0){
                    push(&fringe,i,p,data);
                }
                //push(&fringe,i,p);
            }
        }
        //prev=data;
        pop(&fringe);
        //printf("the data is %d\n",data);
        // printf("Verify %d\n\n",verify(&fringe));
        //printf("Peek value is %d\n\n",peek(&fringe));
        if(verify(&fringe)==1){
            //printf("hey whatshkfsdjbvh\n");
            flag=1;
            break;
        }
    }
    
    pop(&closed);

    if(flag==0){
        pop(&fringe);    
        finalPath(&closed,goal);
    }    
    

    // printf("\nThe closed list at the end of the program: \n");
    int cost;
    while (!isEmpty(&closed)) {
        if(peek(&closed)==goal){
            cost=peekPriority(&closed);
        }
        printf("%d(%d)  ", peek(&closed),peekPriority(&closed));
        pop(&closed);
    }
    printf("\n");
    if(flag==0){
    
        // printf("\nThe path of the graph:");
        for(i=count-1;i>=0;i--){
            printf("%d ",arr[i]);
        }

        // printf("\nThe minimum path cost to : %d\n",cost);
        printf("\n%d\n",cost);        
        
        // printf("The fringe list at the end of the program: \n");
        while (!isEmpty(&fringe)) {
        printf("%d(%d) ", peek(&fringe),peekPriority(&fringe));
        pop(&fringe);
        }
    }
    return 0;
}