#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

std::time_t getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    //std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
    return timestamp;
}

int main()
{
    cout << getTimeStamp() << endl;
    std::this_thread::sleep_for(50ms);
    cout << getTimeStamp() << endl;

    return 0;
}