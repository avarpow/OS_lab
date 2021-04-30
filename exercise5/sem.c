#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#define MAXLEN 3
void *consumer();
void *produce();
void Delay(int time)
{ 
    clock_t now = clock();
    while(clock()-now<time); 
} 
pthread_t Consumer,Produce;
struct buffer{
    pthread_mutex_t mutex;//互斥锁，防止consumer和produce同时进入
    pthread_mutex_t no_full_mutex;//缓冲未满，consumer可进入
    pthread_mutex_t no_empty_mutex;//缓冲不空，produce可进入
    int number;
}buf;
void *consumer(void * i){
    while(1){
        pthread_mutex_lock(&buf.no_empty_mutex);
        printf("buffer no empty consumer %ld enter\n",(long)i); //缓冲未空
        pthread_mutex_lock(&buf.mutex);//获取互斥锁
        buf.number--;
        printf("consumer buffer remain size %d\n",buf.number); 
        if(buf.number==0){
            pthread_mutex_unlock(&buf.mutex);//修改完毕，释放互斥锁
            printf("buffer empty consumer %ld blocked\n",(long)i); //队列已空
        }
        else{
            pthread_mutex_unlock(&buf.mutex);//修改完毕，释放互斥锁
            pthread_mutex_unlock(&buf.no_empty_mutex);//队列不空，consumer可再次进入
        }
        pthread_mutex_unlock(&buf.no_full_mutex);//队列不满，produce可再次进入
        Delay((rand()%5)*1000000+1000000);//随机暂停1-5秒
    }
}
void *produce(void * i){
    while(1){
        pthread_mutex_lock(&buf.no_full_mutex);
        printf("buffer no full produce %ld enter\n",(long)i);  //缓冲未满
        pthread_mutex_lock(&buf.mutex);//获取互斥锁
        printf("produce buffer size %d\n",buf.number+1); 
        buf.number++;
        if(buf.number==MAXLEN){
            pthread_mutex_unlock(&buf.mutex);//修改完毕，释放互斥锁
            printf("buffer full produce %ld blocked\n",(long)i);//队列已满
        }
        else{
            pthread_mutex_unlock(&buf.mutex);//修改完毕，释放互斥锁
            pthread_mutex_unlock(&buf.no_full_mutex);//队列不满，produce可再次进入
        }
        pthread_mutex_unlock(&buf.no_empty_mutex);//队列不空，consumer可再次进入
        Delay( (rand()%5)*1000000+1000000);//随机暂停1-5秒
    }
}
int main(){
    pthread_mutex_init(&buf.mutex,NULL);
    pthread_mutex_init(&buf.no_full_mutex,NULL);
    pthread_mutex_init(&buf.no_empty_mutex,NULL);
    pthread_mutex_lock(&buf.no_empty_mutex);
    buf.number=0;
    pthread_create(&Consumer,NULL,consumer,(void *)1);
    pthread_create(&Produce,NULL,produce,(void *)1);
    while (1);
}