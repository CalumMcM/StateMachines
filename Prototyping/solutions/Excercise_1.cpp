#include <iostream>
#include <thread>



int count; //The global variabel that will be accessed by the threads

std::mutex mtx;

void increment(int numIncrementsPerThread, int curThread){ //This thread that is multiplied
    mtx.lock(); //Locks the global variable count
    std::cout << "Thread " << curThread + 1 << " read count" << std::endl; //Output message
    count += numIncrementsPerThread; //Increments the global variable
    std::cout << "Thread " << curThread + 1 << " incremented count" << std::endl; //Output message
    mtx.unlock(); //unlocks the global variable count
}


int main(){
    int numThreads, numIncrementsPerThread;
    int curThread;
    std::cout << "Input numThreads: ";
    std::cin >> numThreads; //Gets input for the number of threads to be made
    std::cout << "Input numIncrementsPerThread: ";
    std::cin >> numIncrementsPerThread; //Gets the number to increments each thread by

    std::thread allThreads[numThreads]; //Generatees the thread that
    
    if (numThreads>2){ //Adds the output message, but only if num threads >2 otherwise it doesn't make sense
        std::cout << "Threads 1 and 2 and 3 .etc. operating independently" << std::endl;
    } //Creates the specified number of threads
    for(curThread =0; curThread < numThreads; ++curThread){
        allThreads[curThread] = std::thread(increment, numIncrementsPerThread, curThread); //spawn new thread
    }

    for (curThread = 0; curThread< numThreads; ++curThread){ //Waits for the specified number of threads to join
        allThreads[curThread].join();
    }
    
    std::cout << "count = " << count << std::endl; //Gives the final message
    return 0;
}
