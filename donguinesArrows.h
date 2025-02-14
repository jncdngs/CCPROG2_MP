#ifndef DONGUINES_ARROWS_H
#define DONGUINES_ARROWS_H

void cls();
void clearInputBuffer();
void printError();
void printTitle();
void printPassengerTitle();
void printDivider();
void enterPassengerInfo();

typedef struct
{
    int priorityNo;
    char lastName[51];
    char firstName[51];
    int idNo;
    int dropOff;
} Card;

#endif
