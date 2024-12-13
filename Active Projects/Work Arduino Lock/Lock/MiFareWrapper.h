// MiFareWrapper.h
#ifndef MIFAREWRAPPER_H
#define MIFAREWRAPPER_H

#include <Arduino.h>
#include "EasyMFRC522.h"

class MiFareWrapper {
private:
    EasyMFRC522 rfidReader;
    const int block = 1; // Default block for operations

public:
    MiFareWrapper(int ssPin, int rstPin);
    bool initialize();
    bool writeToCard(const String& data);
    String readFromCard();
    bool newCardDetected();
};

#endif
