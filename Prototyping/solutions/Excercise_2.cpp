//To use this makefile type: $make -f makefileEx2
//This time you should see all the ouputs are all over the place, this is a data race!
//You should also see that the final answer is not correct
#include <iostream>
#include <thread>



int count; //The global variabel that will be accessed by the threads

std::mutex mtx;

void increment(int numIncrementsPerThread, int curThread){ //The thread that iterates the global variable
    //Removed the locking of the global variable count
    std::cout << "Thread " << curThread + 1 << " read count" << std::endl;
    if (curThread % 2 == 0){//By cutting out the even files and making them sleep it oputs the system out of sync
        std::this_thread::sleep_for (std::chrono::seconds(1)); 
    }
    count += numIncrementsPerThread;
    std::cout << "Thread " << curThread + 1 << " incremented count" << std::endl;
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
    
    for (curThread = 0; curThread < numThreads; ++curThread){
        allThreads[curThread].join();
    }
    
    std::cout << "count = " << count << std::endl;
    return 0;
}

