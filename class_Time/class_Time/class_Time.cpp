#include <iostream>
#include <Windows.h>
using namespace std;

class Time
{
	int hour;
	int min;
	int sec;
public:
	void SetTime(int hour, int min, int sec)
	{
		if (hour < 24 && hour >= 0 && min < 60 && min >= 0 && sec < 60 && sec >= 0)
		{
			this->hour = hour;
			this->min = min;
			this->sec = sec;
		}
		else
		{
			cout << "Incorrect Time!\n";
			this->hour = 0;
			this->min = 0;
			this->sec = 0;
		}
			//this->hour = (hour >= 0) && (hour< 24) ? hour : 0;
			//this->min = (min >= 0) && (min < 60) ? min : 0;
			//this->sec = (sec >= 0) && (sec < 60) ? sec : 0;
	}
	int GetHour()const{ return hour; }
	int GetMin()const{ return min; }
	int GetSec()const{ return sec; }
	Time() //:Time(0, 0, 0){} 
	{
		//сделал по умолчанию локальное время
		SYSTEMTIME lt;
		GetLocalTime(&lt);
		hour = lt.wHour;
		min = lt.wMinute;
		sec = lt.wSecond;
	}
	Time(int hour, int min, int sec)
	{
		SetTime(hour, min, sec);
	}
	Time operator=(const Time &other)
	{
		this->hour = other.hour;
		this->min = other.min;
		this->sec = other.sec;
		return *this;
	}
	Time operator+=(const Time &other)
	{
		int h = 0;
		int m = 0;
		int s = 0;
		s = sec + other.sec;
		if (s > 59)
		{
			s -= 60; m++;
		}
		m +=( min + other.min);
		if (m>59)
		{
			m -= 60; h++;
		}
		h += (hour + other.hour);
		if (h>23)
		{
			h -= 24;
		}
		this->hour =h;
		this->min=m;
		this->sec=s;
		return  *this;
	}
	Time operator-=(const Time &other)
	{
		int h = 0;
		int m = 0;
		int s = 0;
		s = sec - other.sec;
		if (s < 0)
		{
			s += 60; m--;
		}
		m += (min - other.min);
		if (m<0)
		{
			m += 60; h--;
		}
		h += (hour - other.hour);
		if (h<0)
		{
			h += 24;
		}
		this->hour = h;
		this->min = m;
		this->sec = s;
		return  *this;
	}
	Time operator+(const Time &other)
	{
		int h = 0;
		int m = 0;
		int s = 0;
		s = sec + other.sec;
		if (s > 59)
		{
			s -= 60; m++;
		}
		m += (min + other.min);
		if (m>59)
		{
			m -= 60; h++;
		}
		h += (hour + other.hour);
		if (h>23)
		{
			h -= 24;
		}
		this->hour = h;
		this->min = m;
		this->sec = s;
		return Time(h, m, s);
	}
	Time operator-(const Time &other)
	{
		int h = 0;
		int m = 0;
		int s = 0;
		s = sec - other.sec;
		if (s < 0)
		{
			s += 60; m--;
		}
		m += (min - other.min);
		if (m<0)
		{
			m += 60; h--;
		}
		h += (hour - other.hour);
		if (h<0)
		{
			h += 24;
		}
		this->hour = h;
		this->min = m;
		this->sec = s;
		return Time(h, m, s);
	}
	bool operator==(const Time & other) const
	{
		if (hour == other.hour && min == other.min && sec == other.sec)	return true;
		return false;
	}
	bool operator!=(const Time & other) const
	{
		if (hour != other.hour || min != other.min || sec != other.sec)	return true;
		return false;
	}
	bool operator<(const Time & other) const
	{
		if (hour < other.hour || hour <= other.hour && min < other.min || hour <= other.hour && min <= other.min && sec < other.sec)return true;
		return false;
	}
	bool operator>(const Time & other) const
	{
		if (hour > other.hour || hour >= other.hour && min > other.min || hour >= other.hour && min >= other.min && sec > other.sec)return true;
		return false;
	}
	Time operator++()//префиксный инкремент
	{
		this->sec++;
		if (sec > 59)
		{
			sec -= 60; min++;
		}
		if (min>59)
		{
			min -= 60; hour++;
		}
		if (hour>23)
		{
			hour -= 24;
		}
		return *this;
	}
	Time operator--()//префиксный декремент
    {
		this->sec--;
		if (sec <0)
		{
			sec += 60; min--;
		}
		if (min<0)
		{
			min += 60; hour--;
		}
		if (hour<0)
		{
			hour += 24;
		}
		return *this;
	}
	Time operator++(int)//постфиксный инкремент
	{
		Time temp = *this;
		this->sec++;
		if (sec > 59)
		{
			sec -= 60; min++;
		}
		if (min>59)
		{
			min -= 60; hour++;
		}
		if (hour>23)
		{
			hour -= 24;
		}
		return temp;
	}
	Time operator--(int)//постфиксный декремент
	{
		Time temp = *this;
		this->sec--;
		if (sec <0)
		{
			sec += 60; min--;
		}
		if (min<0)
		{
			min += 60; hour--;
		}
		if (hour<0)
		{
			hour += 24;
		}
		return temp;
	}
	int TimeToSec()
	{
		return hour * 3600 + min * 60 + sec;
	}
};

void PrintTime(Time t)
{
	cout << t.GetHour() << " hour " << t.GetMin() << " min " << t.GetSec() << " sec " << endl;
}

void main()
{
	Time a;
	PrintTime(a);
	Time b(23, 6, 58);
	PrintTime(b);
	b -= a;
	PrintTime(b);
	Time c(23,59,59);
	PrintTime(c);
	c++;
	PrintTime(c);
	cout<<c.TimeToSec()<<endl;
	c--;
	PrintTime(c);
	cout<<c.TimeToSec()<<endl;
    c = a + b;
	PrintTime(c);
	if (a > b)
		cout << "Yes";
	else
		cout << "No";
	cout<<c.TimeToSec()<<endl;
}