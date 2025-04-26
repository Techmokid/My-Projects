#ifndef MULTITHREAD_TIMERS_H
#define MULTITHREAD_TIMERS_H

#include <Arduino.h>
#include <vector>

struct Timer {
    bool accuracy;
    unsigned long lastTrigger;
    unsigned long timerLength;
    bool restartWhenTriggered;
    bool isRunning;
    int ID;

    Timer(unsigned long length, bool accurate, bool restart, int _ID)
        : accuracy(accurate),
          lastTrigger(accurate ? micros() : millis()),
          timerLength(length),
          restartWhenTriggered(restart),
          isRunning(true),
          ID(_ID) {}
};

// Make this static if included in header, or move to a .cpp file
static std::vector<Timer> timersList;

// Forward declaration
int GetIndex(int ID);

int addTimer(unsigned long timerLength, bool accurate, bool restartWhenTriggered) {
    static int nextID = 0;
    int ID = nextID++;
    timersList.emplace_back(timerLength, accurate, restartWhenTriggered, ID);
    return ID;
}

bool hasTimerExpired(int ID) {
    int index = GetIndex(ID);
    if (index < 0 || index >= static_cast<int>(timersList.size())) return false;

    Timer& timer = timersList[index];
    if (!timer.isRunning) return false;

    unsigned long currentTime = timer.accuracy ? micros() : millis();
    if ((currentTime - timer.lastTrigger) >= timer.timerLength) {
        if (timer.restartWhenTriggered) {
            timer.lastTrigger = currentTime;
        } else {
            timer.isRunning = false;
        }
        return true;
    }
    return false;
}

void resetTimer(int ID) {
    int index = GetIndex(ID);
    if (index >= 0 && index < static_cast<int>(timersList.size())) {
        Timer& t = timersList[index];
        t.lastTrigger = t.accuracy ? micros() : millis();
        t.isRunning = true;
    }
}

void stopTimer(int ID) {
    int index = GetIndex(ID);
    if (index >= 0 && index < static_cast<int>(timersList.size()))
        timersList[index].isRunning = false;
}

int GetIndex(int ID) {
    for (int i = 0; i < timersList.size(); i++) {
        if (timersList[i].ID == ID) return i;
    }
    return -1;
}

#endif
