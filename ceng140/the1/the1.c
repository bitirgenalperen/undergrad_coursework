#include <stdio.h>
#include <math.h>
#include "the1.h"


void initialize_the_tree(int binary_tree[MAX_LENGTH], int get_values_from_user) {
    int i,num,val,ind,hold[MAX_LENGTH];	

    for(i=0;i<MAX_LENGTH;i++){binary_tree[i]=-1;}
    for(i=0;i<MAX_LENGTH;i++){hold[i]=0;}
    
    if(get_values_from_user!=0){
        scanf("%d",&num);
        i=0;
        while(i<num){
            i++;
            scanf("%d %d",&ind,&val);
            if(ind<MAX_LENGTH && hold[ind]==0){hold[ind] = 1;binary_tree[ind]=val;}
            else{continue;}
        }
    }
}


void insert_node(int binary_tree[MAX_LENGTH], int node, char where, int value) {
    int ind = node + (where=='l')*(node + 1) + (where=='r')*(node+2);
    if(binary_tree[ind]==-1){binary_tree[ind]=value;}
}


void delete_node_rec(int binary_tree[MAX_LENGTH], int node) {
    int loc,left,right;
    left = 2*node+1;
    right = 2*node+2;
    loc = right<MAX_LENGTH;
    
    if(left<MAX_LENGTH && binary_tree[left]!=-1){
        delete_node_rec(binary_tree,left);
    }
    if(loc && binary_tree[right]!=-1){
        delete_node_rec(binary_tree,right);
    }
    if((right >= MAX_LENGTH||binary_tree[right]==-1) && (left >= MAX_LENGTH ||binary_tree[left]==-1)){
        binary_tree[node]=-1;
    }
}

void tabber(int dep){
    if(dep==0){return;}
    else{printf("\t");tabber(dep-1);}
}

void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth) {
    int left,right;
    left = 2*root+1;
    right = 2*root+2;
    if(left<MAX_LENGTH && binary_tree[left]!=-1){
        draw_binary_tree_rec(binary_tree,left,depth-1);
         tabber(depth);
        printf("%d\n",binary_tree[root]);
    }

    if((left>=MAX_LENGTH || binary_tree[left]==-1)&&binary_tree[root]!=-1){
      tabber(depth);
        printf("%d\n",binary_tree[root]);

    }
    
    
    if(right<MAX_LENGTH && binary_tree[right]!=-1){
        draw_binary_tree_rec(binary_tree,right,depth-1);
    }
}

int max(int a,int b){
    if(a<=b){return b;}
    else{return a;}
} 
int min(int a,int b){
    if(a<b && a!=-1){return a;}
    else{return b;}
} 
 
int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int left,right,loc;
    left = 2*root+1;
    right = 2*root+2;
    loc = right<MAX_LENGTH;
    
    if(loc && binary_tree[right]==-1 && binary_tree[left]==-1){
        return 0;
    }
    else if(loc && (binary_tree[right]!=-1 || binary_tree[left]!=-1)){
        return 1+max(find_height_of_tree_rec(binary_tree,left),find_height_of_tree_rec(binary_tree,right));
    }
    else{
        return 0;
    }
}

int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int left,right,loc;
    left = 2*root+1;
    right = 2*root+2;
    loc = right<MAX_LENGTH;
    
    if(loc && binary_tree[right]==-1 && binary_tree[left]==-1){
        return binary_tree[root];
    }
    else if(loc && (binary_tree[right]!=-1 || binary_tree[left]!=-1)){
        return min(binary_tree[root],min(find_min_of_tree_rec(binary_tree,left),find_min_of_tree_rec(binary_tree,right)));
    }
    else{
        return binary_tree[root];
    }
}

int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value) {
    int lm,rm,temp1=root,temp2=root,i,lim;
    
    if(binary_tree[root]==value){return root;}
    
    while(2*temp1+1<=MAX_LENGTH){
        lm=2*temp1+1;
        rm=2*temp2+2;
        lim = (rm<=MAX_LENGTH)*(rm) + (rm>MAX_LENGTH)*(MAX_LENGTH-1);
    	for(i=lm;i<=lim;i++){
            if(binary_tree[i]==value){return i;}
            }   
        temp1=lm;
        temp2=rm;
    }
    return -1;
}

int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value) {
    int loc = 2*root+2,x,y;
    
    
    if(loc <= MAX_LENGTH){
        x = depth_first_search_rec(binary_tree,2*root+1,value);
        if(x!=-1){return x;}
        y = depth_first_search_rec(binary_tree,2*root+2,value);
        if(y!=-1){return y;}
    }
    if(binary_tree[root]==value){return root;}
    return -1;
}

void print_binary_tree_values(int binary_tree[MAX_LENGTH]) {
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (binary_tree[i] != -1) {
            printf("%d - %d\n", i, binary_tree[i]);
        }
    }
}
