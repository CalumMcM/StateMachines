#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>

int COMMUNICATIONS;
int MOTORS;
int BATTERIES;
int NAVIGATION;

void Communications(){ //Communcations thread
    COMMUNICATIONS = rand() %20;
    switch (COMMUNICATIONS){
        case 3: std::cout << "Communcations: \033[1;31mCRITICAL ERROR \033[0m "; break;
        case 5: std::cout << "Communcations: \033[1;33mMINOR ERROR    \033[0m "; break;
        default: std::cout << "Communcations: \033[1;32mPERFECT        \033[0m "; break;
    }
}

void Motors(){ //Motors thread
    MOTORS = rand() % 20;
    switch (MOTORS) {
        case 3: std::cout << "Motors: \033[1;31mCRITICAL ERROR  \033[0m "; break;
        case 5: std::cout << "Motors: \033[1;33mMINOR ERROR     \033[0m "; break;
        default: std::cout << "Motors: \033[1;32mPERFECT         \033[0m "; break;
    }
}

void Batteries(){ //Batteries thread
    BATTERIES = rand() % 20;
    switch (BATTERIES){
        case 3:
            std::cout << "Batteries: \033[1;31mCRITICAL ERROR  \033[0m ";
            break;
        case 5:  std::cout << "Batteries: \033[1;33mMINOR ERROR     \033[0m "; break;
        default: std::cout << "Batteries: \033[1;32mPERFECT         \033[0m "; break;
    }
}

void Navigations(){ //Navigations thread
    NAVIGATION = rand() % 20;
    switch (NAVIGATION){
        case 3: std::cout << "Navigations: \033[1;31mCRITICAL ERROR  \033[0m" << std::endl; break;
        case 5: std::cout << "Navigations: \033[1;33mMINOR ERROR     \033[0m " <<std::endl; break;
        default: std::cout << "Navigations: \033[1;32mPERFECT        \033[0m" << std::endl; break;
    }
}

int check_status(){
    if (COMMUNICATIONS == 3){
        std::cout <<"\033[1;35m!!!!!!!!!!!!PAUSING SYSTEM WHILE COMMUNICATIONS TROUBLESHOOTS!!!!!!!!!!!!\n\033[0m" <<std::endl;
        return 0;
    }
    if (MOTORS == 3){
        std::cout <<"\033[1;35m!!!!!!!!!!!!!!!!PAUSING SYSTEM WHILE MOTORS TROUBLESHOOTS!!!!!!!!!!!!!!!!\n\033[0m" <<std::endl;
        return 1;
    }
    if (BATTERIES == 3){
        std::cout <<"\033[1;35m!!!!!!!!!!!!!!!PAUSING SYSTEM WHILE BATTERIES TROUBLESHOOTS!!!!!!!!!!!!!!\n\033[0m" <<std::endl;
        return 2;
    }
    if (NAVIGATION == 3) {
        std::cout <<"\033[1;35m!!!!!!!!!!!!!PAUSING SYSTEM WHILE NAVIGATION TROUBLESHOOTS!!!!!!!!!!!!!!!\n\033[0m" <<std::endl;
        return 3;
    }
    return 4;
}


int main() {
    srand(time(NULL));

    std::cout << "\n\n\n   ______________________________________CURRENT STATUS OF STATES______________________________________\nRun Time: 20 Seconds\n" << std::endl;
    time_t start = time (NULL);
    time_t end = start + 20;
    time_t loop_time = time (NULL);

    while (start != end){
        //allThreads[0] = std::thread(Communcations); //spawn new thread
        loop_time = time (NULL);
        std::thread communications (Communications);
        communications.join();
        std::thread motors (Motors);
        motors.join();
        std::thread batteries (Batteries);
        batteries.join();
        std::thread navigations (Navigations);
        navigations.join();

        int broken_state = check_status();
        if (broken_state != 4){
            bool safe = false;
            do{
                if (broken_state == 0){
                    std::thread communications (Communications);
                    communications.join();
                }
                if (broken_state == 1){
                    std::thread motors (Motors);
                    motors.join();
                }
                if (broken_state == 2){
                    std::thread batteries (Batteries);
                    batteries.join();
                }
                if (broken_state == 3) {
                    std::thread navigations(Navigations);
                    navigations.join();
                }
                broken_state = check_status();
                if (broken_state == 4){
                    safe = true;
                    std::cout <<"\033[1;36m\n\n!!!!!!!!!!!!!!!!!!!!!!!!RESUMING SYSTEM!!!!!!!!!!!!!!!!!!!!!!\033[0m" <<std::endl;
                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            } while (!safe);
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        start = time(NULL);
    }

    std::cout << "______________________________________FINISHED RECORDING STATES______________________________________" << std::endl;

    return 0;
}
