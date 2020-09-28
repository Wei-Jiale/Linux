#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<queue>

using namespace std;

// 最大线程数
const size_t MAX_SIZE = 5;

class BlockQueue{
public:
    BlockQueue(size_t capacity = MAX_SIZE) : _capacity(capacity){
        pthread_mutex_init(&_mutex, NULL);
        pthread_cond_init(&_pro_cond, NULL);
        pthread_cond_init(&_cus_cond, NULL);                               
    }

    ~BlockQueue(){
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_pro_cond);
        pthread_cond_destroy(&_cus_cond);                            
    }
    
    // 入队
    // 只有生产者生产资源
    void Push(int data){
        pthread_mutex_lock(&_mutex);

        while (_queue.size() == _capacity){
            pthread_cond_wait(&_pro_cond, &_mutex);                                  
        }

        _queue.push(data);
        pthread_mutex_unlock(&_mutex);
        // 唤醒消费者线程
        pthread_cond_signal(&_cus_cond);                                            
    }
    
    // 出队
    // 只有消费者处理资源
    void Pop(int& data){
        pthread_mutex_lock(&_mutex);

        while (_queue.empty()){
            pthread_cond_wait(&_cus_cond, &_mutex);                                    
        }

        data = _queue.front();
        _queue.pop();
        pthread_mutex_unlock(&_mutex);
        // 唤醒生产者线程
        pthread_cond_signal(&_pro_cond);                                                    
    }

private:
    queue<int> _queue; // 队列
    size_t _capacity; // 队列中最大结点数

    pthread_mutex_t _mutex; // 互斥锁
    pthread_cond_t _pro_cond; // 生产者线程
    pthread_cond_t _cus_cond; // 消费者线程
};

// 生产者线程入口函数
void *productor(void *arg){
    BlockQueue *queue = (BlockQueue*)arg;
    int data = 0;
    while (1){
        queue->Push(data);
        cout << "生产者放入数据：" << data++ << endl;                            
    }
    return NULL;
}

// 消费者线程入口函数
void *customer(void *arg){
    BlockQueue *queue = (BlockQueue*)arg;
    while (1){
        int data;
        queue->Pop(data);
        cout << "消费者取出数据：" << data << endl;                                
    }
    return NULL;
}

int main(){
    BlockQueue queue;
    pthread_t pro_tid[5], cus_tid[5];

    // 创建线程
    for (size_t i = 0; i < 5; i++){
        int ret = pthread_create(&pro_tid[i], NULL, productor, (void*)&queue);
        if (ret){
            cout << "生产者线程创建失败" << endl;
            return -1;                                                
        }
        ret = pthread_create(&cus_tid[i], NULL, customer, (void*)&queue);
        if (ret){
            cout << "消费者线程创建失败" << endl;
            return -1;                                                        
        }
                                    
    }

    for (size_t i = 0; i < 4; i++){
        pthread_join(pro_tid[i], NULL);
        pthread_join(cus_tid[i], NULL);                            
    }

    return 0;
}
