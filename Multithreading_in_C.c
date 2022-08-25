/* What the program does:
I've made a linked list of size num_of_nodes (you can edit in code) with all data fields containing the integer 2, 
Thread 1 (called writer here) (made first) writes 1 into all the data fields
Thread 2 (called reader here) (made second) reads data from linked list and prints it
Now, for smaller values of num_of_nodes we expect Thread 1 to be faster as it is created first so values printed are mostly 1
Therefore we see that "Writing Finished" is printed before "Reading Finished"
But for bigger size of linked list, this can change as one thread can run faster sometimes and overtake the other one and vice versa.
For example try num_of_nodes=1000000
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node{// declaring node structure
    int data;
    struct node * next;
};

pthread_mutex_t mutex;

struct node * create_linked_list(int num_of_nodes){//creates linked list with all data fields containing integer 2
    struct node *nnode, *temp;
    struct node * head = (struct node *)malloc(sizeof(struct node));
    if(head == NULL){
        printf("Unable to allocate memory \n");
        exit(0);
    }
    head->data=2;
    head->next = NULL;
    temp = head;
    for(int i=1; i<num_of_nodes; i++){
        nnode = (struct node *)malloc(sizeof(struct node));
        if(nnode == NULL){
            printf("Unable to allocate memory \n");
            break;
        }
        nnode->data=2;
        nnode->next = NULL;  
        temp->next = nnode;
        temp = temp->next;    
    }
    return head;
}
void * writer(void * head){ //writes 1 into the data field of the linked list
    head = (struct node *) head;
    struct node * temp=head;
    while(temp!=NULL){
        pthread_mutex_lock(&mutex);
        temp->data=1;
        temp=temp->next;
        pthread_mutex_unlock(&mutex);
    }
    printf("Writing Finished \n");
}

void * reader(void * head){// reads the data in linked list and prints it
    head = (struct node *) head;
    struct node * temp=head;
    while(temp!=NULL){
        pthread_mutex_lock(&mutex);
        printf("%d \n",temp->data);
        temp=temp->next;
        pthread_mutex_unlock(&mutex);
    }
    printf("Reading Finished \n");
}

int main(){
    int num_elements=1000;
    struct node * head = create_linked_list(num_elements);
    pthread_t write,read;
    pthread_mutex_init(&mutex, NULL);
    if(pthread_create(&write,NULL,writer,head)){//creates thread for writing into linked list
        printf("Error creating writer thread");
    }
    if(pthread_create(&read,NULL,reader,head)){//creates thread for reading from linked list
        printf("Error creating reader thread");
    }
    if(pthread_join(write,NULL)){
        printf("Error terminating writer thread");
    }
    if(pthread_join(read,NULL)){
        printf("Error terminating reader thread");
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}