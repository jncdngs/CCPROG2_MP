#include <stdio.h>

int main()
{
    printf("Hello, World!\n");

    return 0;
}

/*

Arrows Shuttle Service System

Passenger Embarkation Card:
Priority number
Name
ID Number
Drop-off point (depending on route)

Shuttle can accommodate 13 passengers (excl. driver)
Can accomodate 16 passengers during worst case scenarios (special shuttle)

Priority levels are STRICTLY adhered to
    1 - Faculty and ASF with Inter-campus assignments
    2 - Students with Inter-campus enrolled subjects or enrolled in thesis 
        using Inter-campus facilities
    3 - Researchers
    4 - School Administrators (Academic Coordinators level and up for Faculty 
        and ASF, and Director level and up for APSP)
    5 - University Fellows
    6 - Employees and Students with official business

Create a program to keep track of the trips of the shuttles

The system will always check the priority level of each new passenger entry and 
adjust the seating accordingly. This means that it is possible for those with a 
lower priority level to be removed from a specific trip and moved to the next.

FEATURES:
Passenger Features
    - Encode Passenger Information
        - It will ask the user for the Trip Number.
        - This is where the user will encode the embarkation information that 
          was mentioned above.
        - The system will automatically assign the passenger to the selected 
          trip if that trip is not yet full. In the event that the trip is full 
          and a high priority passenger wants to board, the first lowest 
          priority passenger listed will be removed and moved to the next trip. 
          The removed passenger will be notified(display a message on screen).
          NOTE: Seat assignment will start at seat 1. Refer to figure.

Feature for both user types
    - Notify/Inform the user that a specific trip is full
        - When the user picks a specific trip, if the trip is full, he/she will 
          be notified via display message.

Arrows Express Personnel Features
    - Viewing the passenger count on a certain trip
        - It will ask the user for the Trip Number.
        - This will display the current count for a specific trip.
        - Display will be as seen above. All taken seats will be marked with a 
          “X” while open/available seats will be marked with an “O”.
    - View the drop-off count
        - It will ask the user for the Trip Number.
        - This will display a list of the stops that the passengers picked and 
          show how many will be getting off at those stops.
    - View passenger information
        - This feature will ask for the Trip Number.
        - It will then display a list of the names, ID Numbers and priority 
          numbers of the passengers of the specific trip sorted by priority 
          number(highest to lowest).
    - Load passenger
        - This will be an alternative to manually inputting passenger 
          information.
        - It will read the trip number as well as the passenger info from a 
          text file.
    - Search passenger
        - This feature will allow the user to search for passengers by their 
          last name.
    - Load Recent Trip File (for viewing only)
        - Using this feature will display all information of the loaded trip 
          file.
    - Exit Program
        - Automatically save current information to a text file then the 
          program is terminated

ASSUMPTIONS:
- All passengers that sign up for a trip WILL show up. Meaning there is no 
  chance for “no shows”.
- The special shuttle (16-seater) is limited to just one (1) shuttle. If it’s 
  out then there are no more special shuttles until it returns.

BONUS:
- Add "login" screen for personnel (username and password)

*/