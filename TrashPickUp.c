#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

int WinMain() 
{
    
    int day, month, year, day_of_week;
    time_t currentTime = time(NULL);
    struct tm date = *localtime(&currentTime);
    day = date.tm_mday;
    month = date.tm_mon + 1;
    year = date.tm_year + 1900;
    if (month < 3)
    {
        month += 12;
        year--;
    }

    FILE *log = fopen("log.txt", "a");

    day_of_week = (day + (13 * (month + 1) / 5) + (year % 100) +
        ((year % 100) / 4) + ((year / 100) / 4) + 5 * (year / 100)) % 7;

    switch (day_of_week) 
    {
        case 0:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Saturday", "It's Saturday.", NULL);
            break;
        case 1:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Sunday", "Klump, my dearly, \ndauntless Klump. Remind me if I ever were to kill myself, \nI could scale to the heights of your blind devotion \nAND LEAP DOWN TOWARDS YOUR IQ! that is one of the greatest insults i ever heard.", NULL);
            break;
        case 2:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Monday", "You wake up it's a Monday\n your friends have been taken by furries\n god must be killed. failboat", NULL);
            break;
        case 3:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tuesday", "Well it's a tuesday", NULL);
            break;
        case 4:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Wednesday", "BEWOOP!", NULL);
            break;
        case 5:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Thursday", "One Does Not Simply Take Out The Trash.", NULL);
            break;
        case 6:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Friday", "Put the trash cans back.", NULL);
            break;
    }
    
    fprintf(log, "%s", getenv("PATH"));
    fprintf(log, "\n");
    fclose(log);
    return 0;
}
