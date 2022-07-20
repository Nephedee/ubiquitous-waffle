#include <iostream>
#include <thread>
#include <mutex>
#include <string>

std::mutex writeLock;

int station = 0;

void train(int travel, std::string name){
    writeLock.lock();
    std::string command;
    std::cout << "\nTrain " << name << " departing";
    writeLock.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(travel));
        writeLock.lock();
        std::cout << "Train " << name << " arrived" << std::endl;
        station++;
        while (command != "depart")
            std::cin >> command;
        writeLock.unlock();
}


int main() {
    int times[3];
    for(int i = 0; i < 3; i++){
        std::cout << "\nEnter train " << i + 1 << " travel time: ";
        std::cin >> times[i];
    }
    std::thread train1(train, times[0], "A");
    std::thread train2(train, times[1], "B");
    std::thread train3(train, times[2], "C");
    train1.join();
    train2.join();
    train3.join();
    std::cout << "\nAll trains arrived";
    return 0;
}
