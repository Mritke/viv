/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Mritke
 *
 * Created on 2 marca 2017, 00:39
 */

#include <cstdlib>
#include <json/json.h>
#include <TimedTask.hpp>
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    wiringPiSetup();


    Schedule schedule;
    schedule.defaultInit();
    schedule.save();
    int last_sec = 0;
    while (true) {

        using namespace std;
        using namespace std::chrono;
        typedef duration<int, ratio_multiply<hours::period, ratio<24> >::type> days;
        system_clock::time_point now = system_clock::now();
        system_clock::duration tp = now.time_since_epoch();
        days d = duration_cast<days>(tp);
        tp -= d;
        hours h = duration_cast<hours>(tp);
        tp -= h;
        minutes m = duration_cast<minutes>(tp);
        tp -= m;
        seconds s = duration_cast<seconds>(tp);
        tp -= s;
        /*std::cout << d.count() << "d " << h.count() << ':'
                << m.count() << ':' << s.count();
        std::cout << " " << tp.count() << "["
                << system_clock::duration::period::num << '/'
                << system_clock::duration::period::den << "]\n";*/

        time_t tt = system_clock::to_time_t(now);
        tm utc_tm = *gmtime(&tt);
        tm local_tm = *localtime(&tt);
        if (local_tm.tm_sec != last_sec) {
            std::cout << local_tm.tm_year + 1900 << '-';
            std::cout << local_tm.tm_mon + 1 << '-';
            std::cout << local_tm.tm_mday << ' ';
            std::cout << local_tm.tm_hour << ':';
            std::cout << local_tm.tm_min << ':';
            std::cout << local_tm.tm_sec << '\n';
            last_sec = local_tm.tm_sec;
        }
        DateTimePlus date = DateTimePlus(local_tm.tm_hour, local_tm.tm_min, local_tm.tm_sec, local_tm.tm_wday);

        schedule.update(date);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    };

    return 0;
}

