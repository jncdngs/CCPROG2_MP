/*******************************************************************************

    Acknowledgement/s:

    ASCII art generated using patorjk.com

*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include "donguinesArrows.h"

/**
 * Clears the screen by using ANSI escape codes.
 * 
 * \033[H   Moves cursor to top-left (home)
 * \033[J   Erases everything below the cursor
 * \033[3J  Erases everything, including scrolled-up text
 */
void
cls()
{
    printf("\033[H\033[J\033[3J");
}

/**
 * Discards characters in the input buffer until a '\n' is encountered.
 */
void
clearInputBuffer()
{
    while(getchar() != '\n');
}

/**
 * Displays a message and waits for a key press before continuing
 */
 void
pressAnyKey()
{
    printf("Press any key to return to the main menu...");
    getch();
}

/**
 * Displays error message for invalid input
 */
void
printError()
{
    printf("\033[0;31mERROR: \033[0m");
    printf("Invalid entry. Please try again.\n\n");
}

/**
 * Displays ASCII art for main menu
 */
void
printTitle()
{
    printf(" ______          _                                     _____                                  __\n");
    printf(" \\ \\ \\ \\        / \\   _ __ _ __ _____      _____      | ____|_  ___ __  _ __ ___  ___ ___     \\ \\\n");
    printf("  \\ \\ \\ \\_____ / _ \\ | '__| '__/ _ \\ \\ /\\ / / __|_____|  _| \\ \\/ / '_ \\| '__/ _ \\/ __/ __|_____\\ \\\n");
    printf("  / / / /_____/ ___ \\| |  | | | (_) \\ V  V /\\__ \\_____| |___ >  <| |_) | | |  __/\\__ \\__ \\_____/ /\n");
    printf(" /_/_/_/     /_/   \\_\\_|  |_|  \\___/ \\_/\\_/ |___/     |_____/_/\\_\\ .__/|_|  \\___||___/___/    /_/\n");
    printf("                                                                 |_|\n\n");
}

/**
 * Displays ASCII art for passenger menu
 */
void
printPassengerTitle()
{
    printf(" ______        ____                                             __\n");
    printf(" \\ \\ \\ \\      |  _ \\ __ _ ___ ___  ___ _ __   __ _  ___ _ __    \\ \\\n");
    printf("  \\ \\ \\ \\_____| |_) / _` / __/ __|/ _ \\ '_ \\ / _` |/ _ \\ '__|____\\ \\\n");
    printf("  / / / /_____|  __/ (_| \\__ \\__ \\  __/ | | | (_| |  __/ | |_____/ /\n");
    printf(" /_/_/_/      |_|   \\__,_|___/___/\\___|_| |_|\\__, |\\___|_|      /_/\n");
    printf("                                             |___/\n\n");
}

/**
 * Displays ASCII art for passenger information menu
 */
void
printPassengerInfoTitle()
{
    printf(" ______        ____                                              ___        __           __\n");
    printf(" \\ \\ \\ \\      |  _ \\ __ _ ___ ___  ___ _ __   __ _  ___ _ __    |_ _|_ __  / _| ___      \\ \\\n");
    printf("  \\ \\ \\ \\_____| |_) / _` / __/ __|/ _ \\ '_ \\ / _` |/ _ \\ '__|____| || '_ \\| |_ / _ \\ _____\\ \\\n");
    printf("  / / / /_____|  __/ (_| \\__ \\__ \\  __/ | | | (_| |  __/ | |_____| || | | |  _| (_) |_____/ /\n");
    printf(" /_/_/_/      |_|   \\__,_|___/___/\\___|_| |_|\\__, |\\___|_|      |___|_| |_|_|  \\___/     /_/\n");
    printf("                                             |___/\n\n");
}

/**
 * Displays ASCII art for personnel menu
 */
void
printPersonnelTitle()
{
    printf(" ______        ____                                      _     __\n");
    printf(" \\ \\ \\ \\      |  _ \\ ___ _ __ ___  ___  _ __  _ __   ___| |    \\ \\\n");
    printf("  \\ \\ \\ \\_____| |_) / _ \\ '__/ __|/ _ \\| '_ \\| '_ \\ / _ \\ |_____\\ \\\n");
    printf("  / / / /_____|  __/  __/ |  \\__ \\ (_) | | | | | | |  __/ |_____/ /\n");
    printf(" /_/_/_/      |_|   \\___|_|  |___/\\___/|_| |_|_| |_|\\___|_|    /_/\n\n\n");
}

/**
 * Displays ASCII art for passenger count menu
 */
void
printPassengerCountTitle()
{
    printf(" ______        ____                                                ____                  _      __\n");
    printf(" \\ \\ \\ \\      |  _ \\ __ _ ___ ___  ___ _ __   __ _  ___ _ __      / ___|___  _   _ _ __ | |_    \\ \\\n");
    printf("  \\ \\ \\ \\_____| |_) / _` / __/ __|/ _ \\ '_ \\ / _` |/ _ \\ '__|____| |   / _ \\| | | | '_ \\| __|____\\ \\\n");
    printf("  / / / /_____|  __/ (_| \\__ \\__ \\  __/ | | | (_| |  __/ | |_____| |__| (_) | |_| | | | | ||_____/ /\n");
    printf(" /_/_/_/      |_|   \\__,_|___/___/\\___|_| |_|\\__, |\\___|_|        \\____\\___/ \\__,_|_| |_|\\__|   /_/\n");
    printf("                                             |___/\n\n");
}

/**
 * Displays ASCII art for drop-off menu
 */
void
printDropOffTitle()
{
    printf(" ______        ____                   ___   __  __        ____                  _      __\n");
    printf(" \\ \\ \\ \\      |  _ \\ _ __ ___  _ __  / _ \\ / _|/ _|      / ___|___  _   _ _ __ | |_    \\ \\\n");
    printf("  \\ \\ \\ \\_____| | | | '__/ _ \\| '_ \\| | | | |_| |_ _____| |   / _ \\| | | | '_ \\| __|____\\ \\\n");
    printf("  / / / /_____| |_| | | | (_) | |_) | |_| |  _|  _|_____| |__| (_) | |_| | | | | ||_____/ /\n");
    printf(" /_/_/_/      |____/|_|  \\___/| .__/ \\___/|_| |_|        \\____\\___/ \\__,_|_| |_|\\__|   /_/\n");
    printf("                              |_|\n\n");
}

/**
 * Displays ASCII art for load passenger menu
 */
void
printLoadPassengerTitle()
{
    printf(" ______        _                    _       ____                                             __\n");
    printf(" \\ \\ \\ \\      | |    ___   __ _  __| |     |  _ \\ __ _ ___ ___  ___ _ __   __ _  ___ _ __    \\ \\\n");
    printf("  \\ \\ \\ \\_____| |   / _ \\ / _` |/ _` |_____| |_) / _` / __/ __|/ _ \\ '_ \\ / _` |/ _ \\ '__|____\\ \\\n");
    printf("  / / / /_____| |__| (_) | (_| | (_| |_____|  __/ (_| \\__ \\__ \\  __/ | | | (_| |  __/ | |_____/ /\n");
    printf(" /_/_/_/      |_____\\___/ \\__,_|\\__,_|     |_|   \\__,_|___/___/\\___|_| |_|\\__, |\\___|_|      /_/\n");
    printf("                                                                          |___/\n\n");
}

/**
 * Displays ASCII art for search passenger menu
 */
void
printSearchPassengerTitle()
{
    printf(" ______       ____                      _           ____                                             __\n");
    printf(" \\ \\ \\ \\     / ___|  ___  __ _ _ __ ___| |__       |  _ \\ __ _ ___ ___  ___ _ __   __ _  ___ _ __    \\ \\\n");
    printf("  \\ \\ \\ \\____\\___ \\ / _ \\/ _` | '__/ __| '_ \\ _____| |_) / _` / __/ __|/ _ \\ '_ \\ / _` |/ _ \\ '__|____\\ \\\n");
    printf("  / / / /_____|__) |  __/ (_| | | | (__| | | |_____|  __/ (_| \\__ \\__ \\  __/ | | | (_| |  __/ | |_____/ /\n");
    printf(" /_/_/_/     |____/ \\___|\\__,_|_|  \\___|_| |_|     |_|   \\__,_|___/___/\\___|_| |_|\\__, |\\___|_|      /_/\n");
    printf("                                                                                  |___/\n\n");
}

/**
 * Displays ASCII art for view recent trip menu
 */
void
printLoadRecentTripTitle()
{
    printf(" ______        _                    _     _____     _           __\n");
    printf(" \\ \\ \\ \\      | |    ___   __ _  __| |   |_   _| __(_)_ __      \\ \\\n");
    printf("  \\ \\ \\ \\_____| |   / _ \\ / _` |/ _` |_____| || '__| | '_ \\ _____\\ \\\n");
    printf("  / / / /_____| |__| (_) | (_| | (_| |_____| || |  | | |_) |_____/ /\n");
    printf(" /_/_/_/      |_____\\___/ \\__,_|\\__,_|     |_||_|  |_| .__/     /_/\n");
    printf("                                                     |_|\n\n");
}
