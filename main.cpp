#include <iostream>
#include <thread>
#include <mutex>

std::string name[3] = {"trainA", "trainB", "trainC"};
int travel_time[3];
std::mutex station;

void input_travel_time ()
{
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Input travel time " << name[i] << ": ";
        std::cin >> travel_time[i];
    }
}

void train_traffic(int i)
{
    std::this_thread::sleep_for(std::chrono::seconds(travel_time[i]));
    std::cout << "The train " << name[i] << " pulled up to the station" << std::endl;

    station.lock();
        std::cout << "Train <" << name[i] << "> arrived at the station!!!" << std::endl;

        std::string command;
        while (command != "depart")
        {
            std::cout << "Enter the departure command from the station (depart): " << std::endl;
            std::cin >> command;
        }

        if (command == "depart")
        {
            std::cout << "Train <" << name[i] << "> dropped from the station!!!" << std::endl;
        }
    station.unlock();
}

int main()
{
    input_travel_time();

    std::thread trafficA(train_traffic, 0);
    std::thread trafficB(train_traffic, 1);
    std::thread trafficC(train_traffic, 2);

    trafficA.join();
    trafficB.join();
    trafficC.join();

};
