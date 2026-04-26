#include<iostream>


int main(){
    
    volatile int i = 0;
    while(true)i = 42;
    return 0;
}