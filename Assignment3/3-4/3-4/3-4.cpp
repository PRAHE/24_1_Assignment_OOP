#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Time {
private:
    int hour;
    int minute;
    int second;

public:
    Time(int hour, int min, int sec);
    ~Time() {}

    void setTime(int hour, int min, int sec);
    void addTime(int sec);
    void printTime();
};

Time::Time(int hour, int min, int sec) {
    setTime(hour, min, sec);
}

void Time::setTime(int hour, int min, int sec) {
    this->hour = hour;
    this->minute = min;
    this->second = sec;
}

void Time::addTime(int sec) {
    int h;
    int m;
    int s;
    int rem;

    if (sec >= 3600) { //시간단위확인
        h = sec / 3600;
        this->hour += h;

        rem = sec % 3600;
        if (rem >= 60) { //분단위 확인
            m = rem / 60;
            s = rem % 60;
            this->minute += m;
            if (this->minute >= 60) {
                this->minute -= 60;
                this->hour += 1;
            }
            this->second += s;
            if (this->second >= 60) {
                this->second -= 60;
                this->minute += 1;
                this->hour += 1;
            }
        }
        else {
            this->second += rem;
            if (this->second >= 60) {
                this->second -= 60;
                this->minute += 1;
                this->hour += 1;
            }
        }
    }
    else if (sec >= 60) {
        m = sec / 60;
        rem = sec % 60;
        this->minute += m;
        if (this->minute >= 60) {
            this->minute -= 60;
            this->hour += 1;
        }
        this->second += rem;
        if (this->second >= 60) {
            this->second -= 60;
            this->minute += 1;
            this->hour += 1;
        }
    }
    else {
        this->second += sec;
        if (this->second >= 60) {
            this->second -= 60;
            this->minute += 1;
            this->hour += 1;
        }
    }
}

void Time::printTime() {
    cout << hour << ":" << minute << ":" << second << endl;
}

class Korea : public Time {
public:
    Korea(int hour, int min, int sec) : Time(hour, min, sec) {
        setTime(hour, min, sec);
    }
    ~Korea() {}
};

class WashingtonDC : public Time {
public:
    WashingtonDC(int hour, int min, int sec) : Time(hour, min, sec) {}
    ~WashingtonDC() {}
    void setTime(int hour, int min, int sec) {
        if (hour < 13) {
            hour += 24;
        }
        Time::setTime(hour - 13, min, sec);
    }
};

class Paris : public Time {
public:
    Paris(int hour, int min, int sec) : Time(hour, min, sec) {}
    ~Paris() {}
    void setTime(int hour, int min, int sec) {
        if (hour < 7) {
            hour += 24;
        }
        Time::setTime(hour - 7, min, sec);
    }
};

class GreenwichObservatory : public Time {
public:
    GreenwichObservatory(int hour, int min, int sec) : Time(hour, min, sec) {}
    ~GreenwichObservatory() {}
    void setTime(int hour, int min, int sec) {
        if (hour < 8) {
            hour += 24;
        }
        Time::setTime(hour - 8, min, sec);
    }
};

int main() {
    string tmp;
    int pos;
    int cur_pos = 0;

    time_t tim = time(nullptr);
    struct tm* now = localtime(&tim);

    int hour = now->tm_hour;
    int min = now->tm_min;
    int sec = now->tm_sec;

    Korea korea(hour, min, sec);
    WashingtonDC washingtonDC(hour, min, sec);
    Paris paris(hour, min, sec);
    GreenwichObservatory greenwichObservatory(hour, min, sec);

    while (1) {
        cout << "Command: ";
        getline(cin, tmp);

        pos = tmp.find(' ');
        if (pos == string::npos) {
            if (tmp == "setting") {
                korea.setTime(hour, min, sec);
                washingtonDC.setTime(hour, min, sec);
                paris.setTime(hour, min, sec);
                greenwichObservatory.setTime(hour, min, sec);
            }
            else if (tmp == "print") {
                cout << "Korea \t\t\t = ";
                korea.printTime();
                cout << "WashingtonDC\t\t = ";
                washingtonDC.printTime();
                cout << "Paris\t\t\t = ";
                paris.printTime();
                cout << "GreenwichObservatory\t = ";
                greenwichObservatory.printTime();
                cout << endl;
            }
            else if (tmp == "exit") {
                return 0;
            }
        }
        else {
            int len = pos - cur_pos;
            string result = tmp.substr(cur_pos, len);
            if (result == "add") {
                len = tmp.size() - pos - 1;
                int add = stoi(tmp.substr(pos + 1, len));
                korea.addTime(add);
                washingtonDC.addTime(add);
                paris.addTime(add);
                greenwichObservatory.addTime(add);
            }
        }
        cout << endl;
    }
    return 0;
}
