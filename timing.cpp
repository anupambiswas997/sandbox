#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <thread>

void showCurrentTime()
{
    time_t now = time(nullptr);
    char *dt = ctime(&now);
    std::cout << "Local date/time: " << dt;
}

void showCurrentTime2()
{
    auto now = std::chrono::system_clock::now();
    time_t now2 = std::chrono::system_clock::to_time_t(now);
    std::cout << "Local date/time: " << ctime(&now2);
}

void someTimeTakingFunction(int msecs)
{
    std::chrono::milliseconds sometime(msecs);
    std::this_thread::sleep_for(sometime);
}

void showTimeDiff()
{
    time_t start, end;
    time(&start);
    someTimeTakingFunction(1000);
    time(&end);
    std::cout << "Start-time " << ctime(&start);
    std::cout << "End-time " << ctime(&end);
    std::cout << "Diff: " << difftime(end, start) << " seconds" << std::endl;
}

void showTimeDiff2()
{
    auto start = std::chrono::system_clock::now();
    someTimeTakingFunction(1020);
    auto end = std::chrono::system_clock::now();
    auto milsecs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    auto micsecs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    time_t s = std::chrono::system_clock::to_time_t(start);
    time_t e = std::chrono::system_clock::to_time_t(end);
    std::cout << "Start-time " << ctime(&s);
    std::cout << "End-time " << ctime(&e);
    std::cout << "Diff: " << milsecs << " milliseconds" << std::endl;
    std::cout << "Diff: " << micsecs << " microseconds" << std::endl;
}

int main(int argc, char *argv[])
{
    showCurrentTime();
    showCurrentTime2();
    showTimeDiff();
    showTimeDiff2();
    return 0;
}