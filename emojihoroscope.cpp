#include <cstdio>
#include <cstdlib>
#include <ctime>
#define usertag {id}LL

int main() 
{
    time_t seconds;

    seconds = time(NULL);
    int daysSinceEpoch = seconds / (60 * 60 * 24);

    unsigned long long randomseed = usertag + daysSinceEpoch;
    srand(randomseed);

    int p = rand() % 20 + 1; // Range of 1 to 20 

    const char* s;

    switch (p) {
        case 1:
            s = "💀";
            break;
        case 2:
            s = "😂";
            break;
        case 3:
            s = "😭";
            break;
        case 4:
            s = "🤠";
            break;
        case 5:
            s = "😎";
            break;
        case 6:
            s = "🦩";
            break;
        case 7:
            s = "🫨";
            break;
        case 8:
            s = "🤡";
            break;
        case 9:
            s = "🇲🇿";
            break;
        case 10:
            s = "🫃";
            break;
        case 11:
            s = "💪";
            break;
        case 12:
            s = "😈";
            break;
        case 13:
            s = "🦄";
            break;
        case 14:
            s = "👽";
            break;
        case 15:
            s = "😎";
            break;
        case 16:
            s = "🤢";
            break;
        case 17:
            s = "🤤";
            break;
        case 18:
            s = "🥱";
            break;
        case 19:
            s = "👹";
            break;
        case 20:
            s = "🪨";
            break;
        default:
            s = "❓"; // Just in case p is out of expected range
    }

    const char* b = "Your emoji of today is: ";
    printf("%s%s\n", b, s);

    return 0;
}
