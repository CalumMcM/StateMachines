#include <iostream>
#include <thread>
#include <mutex>


using namespace std;

mutex aMutex1;//, aMutex2;      for deadlocking two mutexes

int count=0;
int numThreads, numIncrementsPerThread;


void increment_even(int threadNo){
   lock_guard<mutex> g1(aMutex1);
    //lock_guard<mutex> g2(aMutex2);
    cout << "Thread " << threadNo << " read count" << endl;
  //  this_thread::sleep_for(std::chrono::seconds(1)); // make it sleep 
    count = count +numIncrementsPerThread;
    cout << "Thread " << threadNo << " incremented count"<< endl;       
}

void increment_odd(int threadNo){
    //lock_guard<mutex> g2(aMutex2);
    lock_guard<mutex> g1(aMutex1);
    cout << "Thread " << threadNo << " read count" << endl;
    //this_thread::sleep_for(std::chrono::seconds(4));
    count = count +numIncrementsPerThread;
    cout << "Thread " << threadNo << " incremented count"<< endl;       
}

int main(){
        
    
    cout << "Input numThreads: ";
    cin >> numThreads;
    cout << "Input numIncrementsPerThread: ";
    cin >> numIncrementsPerThread;

    thread allThreads[numThreads];

    for(int i =0; i < numThreads; i++){
        cout << "Thread " << i<< " spawning...\n";
        if (i%2 ==0){
            allThreads[i] = thread(increment_even, i); //spawn new thread
        }else{
            allThreads[i] = thread(increment_odd, i); 
        }
        cout << "Thread " << i<< " joined\n";
    }

    for(int i =0; i< numThreads; i++){
        allThreads[i].join(); 
    }

    cout << "count = " << count << endl;

    return 0;
}
