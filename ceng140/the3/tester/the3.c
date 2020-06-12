#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"

Node* createNode(){
    Node* temp;
    temp = malloc(sizeof(Node)); 
    temp->next = NULL;
    return temp;
}

void add_meal(Node **meals_head, char *name, int count){
    Node *temp,*m_next=NULL, **m_cur = meals_head;
    Meal *bellek;
    int k =1;
    
    temp = createNode();
    bellek = malloc(sizeof(Meal));
    while(k){
        if(*m_cur == NULL){
            *m_cur = temp;
            temp -> node = bellek;
            bellek -> name = name;
            bellek -> count = count;
            temp -> next = m_next;
            k=0;
        }
        else{m_cur = &((*m_cur)->next);}
    }
}

void add_philosopher(Node **philosophers_head, char *name, char *favorite_meal, int age){
    Node *temp,*p_next=NULL,**p_cur = philosophers_head;
    Philosopher *bellek;
    int k =1;
    
    temp = createNode();
    bellek = malloc(sizeof(Philosopher));
    while(k){
        if(*p_cur == NULL){
            *p_cur = temp;
            temp -> node = bellek;
            bellek -> name = name;
            bellek -> favorite_meal = favorite_meal;
            bellek -> age = age;
            temp -> next = p_next;
            k=0;
        }
        else{p_cur = &((*p_cur)->next);}
    }
}

void place_philosophers(Node **table_head, Node *philosophers){
   Node *iter=*table_head,*t_prev = *table_head,*p_cur = philosophers->next,*cre=NULL;
   int i,k,size;
   
   size = get_length(philosophers);
   *table_head = createNode();
   (*table_head)->node = philosophers->node;
   iter = *table_head;
   
   for(i=1;i<size;i++){
       for(k=0;k<i;k++){
           if((iter==*table_head)&&(((Philosopher*)(p_cur->node))->age < ((Philosopher *)(iter->node))->age)){
               cre = createNode();
               cre -> next = *table_head;
               cre->node = p_cur->node;
               (*table_head) = cre;
               break;
           }
           if((((Philosopher*)(p_cur->node))->age > ((Philosopher *)(iter->node))->age)&&(iter->next==NULL)){
              cre = createNode();
              cre -> node = p_cur->node;
              iter -> next = cre;
           }
           else if(((Philosopher*)(p_cur->node))->age > ((Philosopher *)(iter->node))->age){
               t_prev = iter;
               iter = iter -> next;
           }
           else{
               cre = iter;
               cre = createNode();
               t_prev -> next = cre;
               cre -> node = p_cur->node;
               cre -> next = iter;
               break;
           }
       }
       iter = *table_head;
       p_cur = p_cur -> next;
   }
   
   iter = (*table_head);
   while(iter->next!=NULL){
       iter = iter -> next;
   }
   iter -> next = *table_head;
}

void remove_philosopher(Node **table_head, int index, int size_of_table){
    Node *prev=*table_head,*cur = *table_head;
    int i=0, k=1;
    
    prev = prev->next;
    while(prev->next!=*table_head){
        prev = prev -> next;
    }
    while(k){
        if(i==index){
            prev -> next = cur->next;
            k=0; 
        }
        cur = cur ->next;
        prev = prev ->next;
        i++;
    }
    if(index==0){*table_head=(*table_head)->next;}
}

void serve_meals(Node *table, Node *meals){
    Node *iter = table,*m_check = meals,*cur=table;
    int size=1,i,k=1;
    
    cur = cur -> next;
    while(cur!=table){cur=cur->next;size++;}
    
    for(i=0;i<size;i++,k=1){
        while(k){
            if(!(strcmp(((Meal*)(m_check->node))->name,((Philosopher*)(iter->node))->favorite_meal))){
                ((Meal*)(m_check->node))->count = (((Meal*)(m_check->node))->count)-1;
                k=0;
            }
            m_check = m_check -> next ;
        }
        m_check = meals;
        iter = iter -> next;
    }
}

void print_list(Node *list, void (*helper_print)(void *)){
    Node *temp;
    for(temp=list;temp;temp = temp->next){
        (*helper_print)(temp -> node); 
    }
}

void print_meal_node(void *meal){
    Meal *temp = (Meal *)meal;
    printf("Name: %s, count: %d\n",(temp -> name),(temp -> count));
}

void print_philosopher_node(void *philosopher){
    Philosopher *temp = (Philosopher *)philosopher;
    printf("Name: %s, favorite meal: %s, age: %d\n",(temp -> name),(temp -> favorite_meal),(temp -> age));
}

void print_table(Node *table){
    Node *prev=table,*cur=table,*occ=table->next;
    
    prev = prev -> next;
    while(prev->next!=table){
        prev = prev -> next;
    }
    while((occ -> next) != (table -> next)){
        printf("%s -> %s -> %s\n",((Philosopher*)(prev->node))->name,((Philosopher*)(cur->node))->name,((Philosopher*)(occ->node))->name);
        prev = prev -> next;
        cur = cur -> next;
        occ = occ -> next;
    }
    printf("%s -> %s -> %s\n",((Philosopher*)(prev->node))->name,((Philosopher*)(cur->node))->name,((Philosopher*)(occ->node))->name);
}

int get_length(Node *list){ 
    Node *temp =list;
    int k=0;
    while(temp!=NULL){k +=1;temp=temp->next;}
    return k; 
}

Philosopher *get_philosopher(Node *philosophers, int index){ 
    Node *pp=philosophers;
    int i;
    for(i=0;i<index;i++){pp = pp -> next;}
    return (Philosopher *)(pp->node);
}
