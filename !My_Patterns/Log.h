#pragma once
/*������� 1. ��������� ������� Singleton, ������������ ������� ���������������� �������
� �������. ������� ������:
- ������������ 3 ������ �������� ������� (����������, ���������, ������);
- ���������� �������� ������� (� �������� ����������� �����, ��������,
��������� ���������);
- �������� �� ������ 10 ��������� �������.
������ �������������:
#include �log.h�
void main(void)
{
 Log *log = Log::Instance();
 log->message(LOG_NORMAL, �program loaded�);
�
 log->message(LOG_ERROR, �error happens! help me!�);
 log->print();*/
#include <iostream>
#include <memory>
#include <ctime>
#include <list>
#include <string>

enum type{LOG_ERROR, LOG_WARNING, LOG_NORMAL};

class Log {
	
public:
	class Message {
		std::string Mes;
		std::time_t Time;
		type Level;
	public:
		Message(type t, const std::string& m) :Level(t), Mes(m), Time(time(NULL)) {}
		friend std::ostream& operator<<(std::ostream& os, const Log::Message&);
	};
private:
	static std::unique_ptr<Log> ptr;
	int Level_info=0;
	Log() {}
	Log(int L):Level_info(L) {}
	Log(const Log&) = delete;
	std::list<Message> queue;
public:
	
	static std::unique_ptr<Log> getInstance() { return move(ptr); }
	void message(type t, const std::string& mes);
	void print()const;
};

std::ostream& operator<<(std::ostream& os, const Log::Message& obj)
{
	std::string Level[] = { "Error","Warning","Normal" };
	os << obj.Time << ":(" << Level[obj.Level] << "):" << obj.Mes << std::endl;
	return os;
}
void Log::message(type t, const std::string& mes)
{
	if(Level_info>=t)
		queue.emplace_back(t, mes);
	while (queue.size() > 10)
		queue.pop_front();
}

void Log::print() const
{
	for (auto& x : queue)
		std::cout << x;
}