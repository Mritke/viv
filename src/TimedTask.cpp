/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// 
// 
// 

#include <TimedTask.hpp>
#include <iostream>
#include <fstream>
#include <iostream>
uint8_t months[12] = {31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31};

DateTimePlus::DateTimePlus(
        int week, int hour, int min, int sec, int wday) :
m_week(week), m_hour(hour), m_minute(min), m_second(sec), m_weekday(wday) {
    normalizeThis();
}

DateTimePlus::DateTimePlus(
        int hour, int min, int sec, int wday) :
m_hour(hour), m_minute(min), m_second(sec), m_weekday(wday) {
    normalizeThis();
}

DateTimePlus::DateTimePlus(
        int hour, int min, int sec) :
m_hour(hour), m_minute(min), m_second(sec) {
    normalizeThis();
}

int DateTimePlus::hour() {
    return m_hour;
}

int DateTimePlus::minute() {
    return m_minute;
}

int DateTimePlus::second() {
    return m_second;
}

int DateTimePlus::weekday() {
    return m_weekday;
}

int DateTimePlus::week() {
    return m_week;
}

void DateTimePlus::normalizeThis() {

    if (m_second > 59) {
        m_minute += int((float) m_second / 60.0);
        m_second = m_second % 60;
    }

    if (m_minute > 59) {
        m_hour += int((float) m_minute / 60.0);
        m_minute = m_minute % 60;
    }

    if (m_hour > 23) {
        m_weekday += int((float) m_hour / 24.0);
        m_hour = m_hour % 24;
    }


    if (m_weekday > 6) {
        m_week += int((float) m_hour / 7);
        m_weekday = m_weekday % 7;
    }


}

DateTimePlus& DateTimePlus::operator=(const DateTimePlus& time) {
    this->m_second = time.m_second;
    this->m_minute = time.m_minute;
    this->m_hour = time.m_hour;
    this->m_week = time.m_week;
    this->m_weekday = time.m_weekday;

    return *this;
}

bool DateTimePlus::operator==(const DateTimePlus& time) {
    return this->m_second == time.m_second && this->m_minute == time.m_minute && this->m_hour == time.m_hour;
}

bool DateTimePlus::operator!=(const DateTimePlus& time) {
    return !this->operator==(time);
}

bool DateTimePlus::operator<(const DateTimePlus& time) {
    return this->timeToSeconds() < time.timeToSeconds();
    //!(this->m_second >= time.m_second) && !(this->m_minute >= time.m_minute) && !(this->m_hour >= time.m_hour);
}

bool DateTimePlus::operator>(const DateTimePlus& time) {
    return this->timeToSeconds() > time.timeToSeconds();
    //return !(this->m_second <= time.m_second) && !(this->m_minute <= time.m_minute) && !(this->m_hour <= time.m_hour);
}

bool DateTimePlus::operator<=(const DateTimePlus& time) {

    return this->timeToSeconds() <= time.timeToSeconds();
}

bool DateTimePlus::operator>=(const DateTimePlus& time) {
    return this->timeToSeconds() >= time.timeToSeconds();
}

DateTimePlus DateTimePlus::operator+(int sec) {
    DateTimePlus ret = *this;
    ret.m_second = this->m_second + sec;
    ret.normalizeThis();
    return ret;
}

DateTimePlus DateTimePlus::operator-(int sec) {
    DateTimePlus ret;
    int temp = toSeconds();
    ret.m_second = temp - sec;
    ret.normalizeThis();
    return ret;
}

DateTimePlus DateTimePlus::operator+(const DateTimePlus& time) {
    DateTimePlus ret;
    ret.m_second = this->m_second + time.m_second;
    ret.m_minute = this->m_minute + time.m_minute;
    ret.m_hour = this->m_hour + time.m_hour;
    ret.m_week = this->m_week + time.m_week;
    ret.m_weekday = this->m_weekday + time.m_weekday;
    ret.normalizeThis();
    return ret;
}

DateTimePlus DateTimePlus::operator-(const DateTimePlus& time) {
    DateTimePlus ret;
    ret.m_second = this->m_second - time.m_second;
    ret.m_minute = this->m_minute - time.m_minute;
    ret.m_hour = this->m_hour - time.m_hour;
    ret.m_week = this->m_week - time.m_week;
    ret.m_weekday = this->m_weekday - time.m_weekday;
    ret.normalizeThis();
    return ret;
}

void DateTimePlus::operator+=(const DateTimePlus& time) {
    this->m_second += time.m_second;
    this->m_minute += time.m_minute;
    this->m_hour += time.m_hour;
    this->m_week += time.m_week;
    this->m_weekday += time.m_weekday;
    this->normalizeThis();
}

void DateTimePlus::operator-=(const DateTimePlus& time) {
    this->m_second -= time.m_second;
    this->m_minute -= time.m_minute;
    this->m_hour -= time.m_hour;
    this->m_week -= time.m_week;
    this->m_weekday -= time.m_weekday;
    this->normalizeThis();
}

DateTimePlus DateTimePlus::operator*(int i) {
    DateTimePlus ret;
    ret.m_second = this->m_second *i;
    ret.m_minute = this->m_minute *i;
    ret.m_hour = this->m_hour *i;
    ret.m_week = this->m_week *i;
    ret.m_weekday = this->m_weekday *i;
    ret.normalizeThis();
    return ret;
}

DateTimePlus DateTimePlus::operator*(float i) {
    DateTimePlus ret;
    int temp = toSeconds();
    ret.m_second = temp*i;
    ret.normalizeThis();
    return ret;
}

void DateTimePlus::operator*=(int i) {
    this->m_second *= i;
    this->m_minute *= i;
    this->m_hour *= i;
    this->m_week *= i;
    this->m_weekday *= i;
    this->normalizeThis();
}

int DateTimePlus::toSeconds() {
    return this->m_second + this->m_minute * 60 + this->m_hour * 3600 + this->m_weekday * 86400 + m_week * 604800;
}

int DateTimePlus::timeToSeconds() const  {
    return this->m_second + this->m_minute * 60 + this->m_hour * 3600;
}

int DateTimePlus::zeroThis() {
    this->m_second = 0;
    this->m_minute = 0;
    this->m_hour = 0;
    this->m_week = 0;
    this->m_weekday = 0;
}

void DateTimePlus::operator*=(float i) {
    int temp = toSeconds();
    zeroThis();
    this->m_second = temp*i;
    this->normalizeThis();

}

DateTimePlus DateTimePlus::operator/(int i) {
    DateTimePlus ret;
    ret.m_second = this->m_second / i;
    ret.m_minute = this->m_minute / i;
    ret.m_hour = this->m_hour / i;
    ret.m_week = this->m_week / i;
    ret.m_weekday = this->m_weekday / i;
    ret.normalizeThis();
    return ret;
}

DateTimePlus DateTimePlus::operator/(float f) {
    DateTimePlus ret;
    ret.m_second = this->toSeconds() / f;
    ret.normalizeThis();
    return ret;
}

void DateTimePlus::operator/=(int i) {
    this->m_second /= i;
    this->m_minute /= i;
    this->m_hour /= i;
    this->m_week /= i;
    this->m_weekday /= i;
    this->normalizeThis();
}

void DateTimePlus::operator/=(float f) {
    int temp = toSeconds();
    zeroThis();
    this->m_second = temp / f;
    this->normalizeThis();
}
//////////////////////////////////////////////////////////////TaskTime//////////////////

Json::Value* TaskTime::saveToJson() {
    return new Json::Value();
}



//////////////////////////////////////////////////////////////TimedTask//////////////////////////////////////////////

TimedTask::TimedTask() {
}

TimedTask::~TimedTask() {
}

bool TimedTask::startWorking() {
    if (!m_taskPermamentOff && !m_skipDay) {
        if (!m_isOn) {
            m_isOn = true;
            digitalWrite(m_taskPin, m_taskOnState);
        }
        return true;
    }
}

bool TimedTask::stopWorking() {
    if (m_isOn) {
        m_isOn = false;
        digitalWrite(m_taskPin, !m_taskOnState);
    }

    return false;
}

void TimedTask::skipDay() {
    m_skipToday = true;
}

uint8_t TimedTask::getSkipDay() {
    return m_dayToSkip;
}

bool TimedTask::isTaskOn() {
    return m_isOn;
}

bool TimedTask::addTaskTime(TaskTime tasktime) {
    m_workTime.push_back(tasktime);
    return true;
}

bool TimedTask::removeTaskTime(uint8_t rem) {
    for (std::vector<TaskTime>::iterator iter = m_workTime.begin(); iter != m_workTime.end(); iter++) {
        if ((*iter).id == rem) {
            m_workTime.erase(iter);
            break;
        }
    }
    return true;
}

void TimedTask::update(DateTimePlus actualTime) {

    if (m_skipToday || (!m_skipDay && m_dayToSkip == actualTime.weekday())) {
        stopWorking();
        m_skipDay = true;
        m_skipToday = false;
        m_dayToSkip = actualTime.weekday();
    } else if (m_skipDay && m_dayToSkip != actualTime.weekday()) {
        m_skipDay = false;
        m_dayToSkip = 8;
    }

    bool turnIt = m_isOn;
    for (size_t i = 0; i < m_workTime.size(); i++) {
        TaskTime& thisTask = m_workTime[i];

        std::cout << actualTime.hour() << " " << actualTime.minute() << " " << actualTime.second() << " " << "\n";
        std::cout << thisTask.startTime.hour() << " " << thisTask.startTime.minute() << " " << thisTask.startTime.second() << " " << "\n";
        std::cout << (actualTime > thisTask.startTime + thisTask.duration) << "\n";
        std::cout << (actualTime < thisTask.startTime + thisTask.duration) << "\n";

        if (thisTask.isActive && actualTime > thisTask.startTime + thisTask.duration &&
            thisTask.dayActive[actualTime.weekday()] && m_isOn) {
            thisTask.isActive = false;
            turnIt =  false;
            std::cout << "turnOFF " << turnIt << "\n";
        } else if (!thisTask.isActive && actualTime > thisTask.startTime &&
                actualTime < thisTask.startTime + thisTask.duration &&
                thisTask.dayActive[actualTime.weekday()] && !m_isOn) {
            thisTask.isActive = true;
            turnIt = true;
            std::cout << "turnON " << turnIt << "\n";
        }
    }

    if (turnIt) {
        startWorking();
    } else {
        stopWorking();
    }

}

Json::Value TimedTask::saveWorkTimeToJson() {
    Json::Value ret;
    for (size_t i = 0; i < m_workTime.size(); ++i) {
        Json::Value workTimejsn;
        TaskTimeToJsonObject(m_workTime[i], workTimejsn);
        ret[i] = workTimejsn;
    }
    return ret;
}
////////////////////////////////////////////////////JsonMakers////////////////////////////

void DateTimePlusToJsonObject(DateTimePlus& object, Json::Value& json) {
    //json
    json[" h"] = object.hour();
    json[ "m"] = object.minute();
    json[ "s"] = object.second();
}

void TaskTimeToJsonObject(TaskTime& object, Json::Value& json) {
    Json::Value id(int(object.id));
    Json::Value isActive(object.isActive);
    json["id"] = id;
    json["isActive"] = isActive;


    Json::Value startTime;
    DateTimePlusToJsonObject(object.startTime, startTime);
    json["startTime"] = startTime;

    Json::Value duration;
    DateTimePlusToJsonObject(object.duration, duration);
    json["duration"] = duration;

    Json::Value daysActive;

    for (size_t i = 0; i < 7; ++i) {
        daysActive[i] = object.dayActive[i];
    }

    json["daysActive"] = daysActive;


}

void TimedTaskToJsonObject(TimedTask& object, Json::Value& json) {
    Json::Value id(int(object.id));
    Json::Value m_isCritical(object.m_isCritical);
    Json::Value taskPermamentOff(object.m_taskPermamentOff);
    Json::Value pin(int(object.m_taskPin));
    Json::Value name(object.name.c_str());
    Json::Value dayToSkip(int(object.getSkipDay()));
    Json::Value taskOnState((object.m_taskOnState));
    json["name"] = name;
    json["id"] = id;
    json["isCritical"] = m_isCritical;
    json["taskPermamentOff"] = taskPermamentOff;
    json["pin"] = pin;
    json["dayToSkip"] = dayToSkip;
    json["workTime"] = object.saveWorkTimeToJson();
    json["taskOnState"] = object.saveWorkTimeToJson();

}

////////////////////////////////////////////////////JsonReaders////////////////////////////

DateTimePlus makeDateTimePlusFromJsonObject(Json::Value& object) {

    int h = object["h"].asInt();
    int m = object["m"].asInt();
    int s = object["s"].asInt();

    return DateTimePlus(h, m, s, 0);
}

TaskTime makeTaskTimeFromJsonObject(Json::Value& object) {
    TaskTime ret;

    ret.id = object["id"].asInt();
    ret.isActive = object["isActive"].asBool();
    ret.startTime = makeDateTimePlusFromJsonObject(object["startTime"]);
    ret.duration = makeDateTimePlusFromJsonObject(object["duration"]);
    Json::Value daysActive = object["daysActive"];

    int tasksSize = daysActive.size();

    for (uint8_t i = 0; i < tasksSize; ++i) {

        ret.dayActive[i] = daysActive[i].asBool();
    }

    return ret;
}

TimedTask makeTimedTaskFromJsonObject(Json::Value& object) {
    TimedTask ret;

    ret.name = object["name"].asString();
    ret.id = object["id"].asInt();
    ret.m_isCritical = object["isCritical"].asBool();
    ret.m_taskPermamentOff = object["taskPermamentOff"].asBool();
    ret.m_taskPin = object["pin"].asInt();
    ret.m_taskOnState = object["taskOnState"].asBool();


    Json::Value worktime = object["workTime"];

    int worksSize = worktime.size();

    for (uint8_t i = 0; i < worksSize; ++i) {
        ret.addTaskTime(makeTaskTimeFromJsonObject(worktime[ i]));
    }

    return ret;
}

//////////////////////////////////////////////////////////////Schedule//////////////////////////////////////////////

Schedule::Schedule() {
}

Schedule::~Schedule() {
}

void Schedule::update(DateTimePlus actualTime) {


    for (size_t i = 0; i < m_tasks.size(); i++) {
        m_tasks[i].update(actualTime);
    }
}

bool Schedule::init() {
    //this->read();
    return true;
}

void Schedule::save() {


    Json::StyledWriter writer;

    std::ofstream file_id;
    file_id.open("./shld.jsn");

    if (file_id.is_open()) {

        Json::Value tasks;
        for (size_t i = 0; i < m_tasks.size(); ++i) {
            Json::Value task;
            TimedTaskToJsonObject(m_tasks[i], task);
            tasks[i] = task;
        }

        Json::Value root;
        root["tasks"] = tasks;
        file_id << root;
        file_id.close();
    }

}

void Schedule::read() {


    Json::Value root; // will contains the root value after parsing.
    Json::Reader reader;
    bool parsingSuccessful = reader.parse("./shld.jsn", root);

    if (parsingSuccessful) {

        if (!root.empty()) {
            Json::Value tasks = root["tasks"];
            if (!tasks.empty()) {
                int tasksSize = 0;
                if (tasks.isArray()) {
                    tasksSize = tasks.size();
                }

                for (uint8_t i = 0; i < tasksSize; ++i) {
                    Json::Value taskjson = tasks[i];
                    if (!taskjson.empty()) {
                        TimedTask task = makeTimedTaskFromJsonObject(taskjson);
                        m_tasks.push_back(task);
                    }
                }
            }
        }


    } else {
        // report to the user the failure and their locations in the document.
        std::cout << "Failed to parse configuration\n"
                << reader.getFormattedErrorMessages();
        return;
    }
}

void Schedule::skipTask(uint8_t id) {
    for (size_t i = 0; i < m_tasks.size(); i++) {
        if (m_tasks[i].id == id) {
            m_tasks[i].skipDay();
            break;
        }
    }
}

bool Schedule::isCritical() {
    for (size_t i = 0; i < m_tasks.size(); ++i) {
        if (m_tasks[i].isTaskOn() && m_tasks[i].m_isCritical) {
            return true;
        }
    }
    return false;
}

void Schedule::defaultInit() {
    TimedTask task;
    task.m_taskPin=22;
    TaskTime taskTime;
    taskTime.startTime = DateTimePlus(10, 0, 0);
    taskTime.duration = DateTimePlus(9, 30, 0);
    taskTime.id = 1;
    task.addTaskTime(taskTime);
    m_tasks.push_back(task);
    
    TimedTask task2;
    task2.m_taskPin=24;
    TaskTime taskTime2;
    taskTime2.startTime = DateTimePlus(17, 0, 0);
    taskTime2.duration = DateTimePlus(0, 0, 20);
    taskTime2.id = 2;
    task2.addTaskTime(taskTime2);
    m_tasks.push_back(task2);
    
    TimedTask task3;
    task3.m_taskPin=24;
    TaskTime taskTime3;
    taskTime3.startTime = DateTimePlus(9, 55, 0);
    taskTime3.duration = DateTimePlus(0, 0, 18);
    taskTime3.id = 3;
    task3.addTaskTime(taskTime3);
    m_tasks.push_back(task3);
    
}
