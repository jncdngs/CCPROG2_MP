#ifndef DONGUINES_ARROWS_H
#define DONGUINES_ARROWS_H

void cls();
void clearInputBuffer();
void printError();
void printTitle();
void printDivider();
void enterPassengerInfo();

typedef struct
{
    int priorityNo;
    char lastName[51];
    char firstName[51];
    int idNo;
    int dropOff[5];
} Card;

#endif
