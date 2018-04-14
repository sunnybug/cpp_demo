#include <iostream>
#include <future>
#include <chrono>
#include <unistd.h>
using namespace std;
bool loop_thread(int x)
{
    for (auto i = 0; i < x; i++)
    {
        usleep( 1000 * 1000);
    }

    cout << endl <<  "loop_thread done" << flush;
    return true;
}

int main()
{
    // launch::async:立即启动线程
    // launch::deferred:直到调用 wait 或 get时才启动线程
    future <bool> fut = async(launch::async, loop_thread, 3);

    cout << "wait,Checking";
    chrono::milliseconds span(10);

    while(fut.wait_for(span) == future_status::timeout)
        cout << '.' << flush;

// 阻塞
    bool x = fut.get();
    cout << endl << "fut.get() return" << flush;
    return 0;
}