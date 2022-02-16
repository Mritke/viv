// TimedTask.h

#ifndef _TIMEDTASK_h
#define _TIMEDTASK_h

#include <vector>
#include <map>
#include <json/json.h>
#include <iterator>
#include <chrono>
#include <wiringPi.h>
#include <date/date.h>
#include <date/iso_week.h>

typedef std::chrono::milliseconds Milliseconds;
typedef std::chrono::seconds Seconds;
typedef std::chrono::minutes Minutes;
typedef std::chrono::hours Hours;
namespace D = date;
class DateTimePlus 
{
public:

	DateTimePlus(int week, int hour, int min, int sec, int wday);
	DateTimePlus(int hour, int min, int sec, int wday);
	DateTimePlus(int hour, int min, int sec);
	DateTimePlus(){}

	int hour();
	int minute();
	int second();
	int weekday();
	int week();
        int timeToSeconds() const;
	int toSeconds();
	int zeroThis();
	 
	DateTimePlus& operator= (const DateTimePlus& time);
	
	bool operator==(const DateTimePlus& time);
	bool operator!=(const DateTimePlus& time);
	bool operator<(const DateTimePlus& time);
	bool operator>(const DateTimePlus& time);
	bool operator<=(const DateTimePlus& time);
	bool operator>=(const DateTimePlus& time);
	DateTimePlus operator+(const DateTimePlus& time);
	DateTimePlus operator+(int sec);
	DateTimePlus operator-(const DateTimePlus& time);
	DateTimePlus operator-(int sec);
	void operator+=(const DateTimePlus& time);
	void operator-=(const DateTimePlus& time);
	DateTimePlus operator*(int i);
	DateTimePlus operator*(float f);
	void operator*=(int i);
	void operator*=(float f);
	DateTimePlus operator/(int i);
	DateTimePlus operator/(float f);
	void operator/=(int i);
	void operator/=(float f);

protected:
	void normalizeThis();
	int   m_week =0 , m_hour = 0, m_minute = 0, m_second = 0, m_weekday = 0;

};

DateTimePlus makeDateTimePlusFromJsonObject(Json::Value& object);
void  DateTimePlusToJsonObject(DateTimePlus& object, Json::Value& json);

struct TaskTime
{
	Json::Value* saveToJson();
	//values:
	uint8_t id = 255;
	bool isActive = false;
	DateTimePlus startTime;
	DateTimePlus duration;
	bool dayActive[7] = { true, true, true, true, true, true, true};

	
};

TaskTime makeTaskTimeFromJsonObject(Json::Value& object);
void TaskTimeToJsonObject(TaskTime& object, Json::Value& json);

class TimedTask
{
public:
	TimedTask();

	~TimedTask();
	bool startWorking();
	bool stopWorking();

	void skipDay();
    uint8_t getSkipDay();
	void update(DateTimePlus actualTime);
	bool isTaskOn();
	bool isTaskPermmamentOff();
	void setTaskPermmamentOff(bool isOn);
	bool addTaskTime(TaskTime tasktime);
	bool removeTaskTime(uint8_t id);
	Json::Value saveWorkTimeToJson();

	//values:
	bool m_taskPermamentOff = false;
	bool m_isCritical = false;
	uint8_t m_taskPin =22;
        bool m_taskOnState = true;
	uint8_t id = 255;
	std::string name= "defname";
private:
	//values:
	std::vector <TaskTime> m_workTime;
	bool m_isOn = false;
	bool m_skipDay = false;
	bool m_skipToday = false;
	uint8_t m_dayToSkip = 8;
	

};

TimedTask makeTimedTaskFromJsonObject(Json::Value& object);
void TimedTaskToJsonObject(TimedTask& object, Json::Value& json);

class Schedule
{
public:
	Schedule();
	~Schedule();

	bool init();
	void update(DateTimePlus actualTime);
	bool isCritical();
	void skipTask(uint8_t id);
	bool m_saveNeedUpdate = false;
	void save();
	void read();
        void defaultInit();
	//values:
private:

	bool readFromJson();



	//values:

	std::vector <TimedTask> m_tasks;

};



#endif

