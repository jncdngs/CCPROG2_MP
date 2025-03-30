// Include guards
#ifndef DONGUINES_ARROWS_H
#define DONGUINES_ARROWS_H

#define MAX_CHARS 21        // Maximum of 20 chars each for last name and first name
#define MAX_PASS 13         // Maximum of 13 passengers per regular shuttle
#define SPECIAL_PASS 16     // Maximum of 16 passengers per special shuttle
#define MAX_BUS 22          // Maximum of 22 shuttles
#define MAX_DROPOFFS 4      // Maximum of 4 drop-off points per shuttle

typedef char stringTrip[6];                     // "AE101", etc.
typedef char stringTime[5];                     // "0600", etc.
typedef char stringOrigin[21];                  // "DLSU Manila Campus"
typedef char stringDropOff[41];                 // Full drop-off point name
typedef char stringName[MAX_CHARS];             // Passenger name
typedef char stringFullName[MAX_CHARS * 2 + 2]; // Full name
typedef char stringFileName[20];                // "Trip-dd-mm-yyyy.txt"

struct TripInfo
{
    stringTrip tripNumber;
    stringTime tripTime;
    stringOrigin tripOrigin;
    int dropOffSet;
};

struct Card
{
    int priorityNo;
    stringName lastName;
    stringName firstName;
    int idNo;
    int dropOff;
};

struct FilePassenger
{
    stringTrip tripNumber;
    stringOrigin origin;
    stringFullName fullName;
    int idNo;
    int priorityNo;
    stringDropOff dropOff;
};

struct Date
{
    int dd;
    int mm;
    int yyyy;
};

// funcDisplay.c
void cls();
void clearInputBuffer();
void pressAnyKey();
void printError();
void printTitle();
void printPassengerTitle();
void printPassengerInfoTitle();
void printPersonnelTitle();
void printPassengerCountTitle();
void printDropOffTitle();
void printLoadPassengerTitle();
void printSearchPassengerTitle();
void printLoadRecentTripTitle();

// funcCommon.c
void initializePassengers(struct Card[][SPECIAL_PASS]);
int compareStrings(char*, char*);
int isValidTrip(struct TripInfo[], stringTrip);
int isValidID(struct Card[][SPECIAL_PASS], int);
int isFullTrip(int, struct Card[][SPECIAL_PASS], int);
int isSpecDeployed(struct Card[][SPECIAL_PASS]);
int convertDropOff(int, int, int);
void copyStruct(struct Card*, struct Card*);
void insertPassenger(struct Card[][SPECIAL_PASS], int, struct Card);
void movePassenger(struct TripInfo[], struct Card[][SPECIAL_PASS], int);
void displayTrips(struct TripInfo[], int);
void displayDropOffs(struct TripInfo[], int, stringDropOff[][MAX_DROPOFFS]);
void displayDropOffCount(struct TripInfo[], int, struct Card[][SPECIAL_PASS], stringDropOff[][MAX_DROPOFFS], int[]);
struct Date getDate();
void savePassengerInfo(struct TripInfo[], struct Card[][SPECIAL_PASS], stringDropOff[][MAX_DROPOFFS]);

// funcPassenger.c
void enterPassengerInfo(struct TripInfo[], struct Card[][SPECIAL_PASS], stringDropOff[][MAX_DROPOFFS], int*);

// funcPersonnel.c
void viewPassengerCount(struct TripInfo[], struct Card[][SPECIAL_PASS], int*);
void viewDropOffCount(struct TripInfo[], struct Card[][SPECIAL_PASS], stringDropOff[][MAX_DROPOFFS], int*);
void viewPassengerInfo(struct TripInfo[], struct Card[][SPECIAL_PASS], int*);
void loadPassenger(struct TripInfo[], struct Card[][SPECIAL_PASS], stringDropOff[][MAX_DROPOFFS]);
void searchPassenger(struct TripInfo[], struct Card[][SPECIAL_PASS], stringDropOff[][MAX_DROPOFFS]);
void displayRecentTrip();

#endif
