#include <iostream>
#include <thread>



int count;

std::mutex mtx;

void increment(int numIncrementsPerThread, int curThread){
    mtx.lock();
    std::cout << "Thread " << curThread + 1 << " read count" << std::endl;
    count += numIncrementsPerThread;
    std::cout << "Thread " << curThread + 1 << " incremented count" << std::endl;
    mtx.unlock();
}


int main(){
    int numThreads, numIncrementsPerThread;
    int curThread;
    std::cout << "Input numThreads: ";
    std::cin >> numThreads;
    std::cout << "Input numIncrementsPerThread: ";
    std::cin >> numIncrementsPerThread;

    std::thread allThreads[numThreads];
    
    if (numThreads>2){
        std::cout << "Threads 1 and 2 and 3 .etc. operating independently" << std::endl;
    }
    for(curThread =0; curThread < numThreads; ++curThread){
        allThreads[curThread] = std::thread(increment, numIncrementsPerThread, curThread); //spawn new thread
    }
    
    for (curThread = 0; curThread< numThreads; ++curThread){
        allThreads[curThread].join();
    }
    
    std::cout << "count = " << count << std::endl;
    return 0;
}
