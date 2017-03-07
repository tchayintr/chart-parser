#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "def.h"          

int intArray[BufSize];
int front = 0;
int rear = -1;
int itemCount = 0;

int peek(){
   return intArray[front];
}

bool isEmpty(){
   return itemCount == 0;
}

bool isFull(){
   return itemCount == BufSize;
}

int qsize(){
   return itemCount;
}  

void insert(int data){

   if(!isFull()){
      if(rear == BufSize-1){
         rear = -1;            
      }       
      intArray[++rear] = data;
      itemCount++;
   }
}

int removeData(){
   int data = intArray[front++];
   
   if(front == BufSize){
      front = 0;
   }
   
   itemCount--;
   return data;  
}

void copyData(int * array){  //copy to array
   int i;

   for(i=0;i<itemCount;i++){
      array[i] = intArray[i];
   }
}

void insertCopyData(int * array, int arraySize){   //insert array with arraySize to queue
   int i;
   for(i=0;i<arraySize;i++){
      insert(array[i]);
   }
}

void freequeue(){
   free(intArray);
 }