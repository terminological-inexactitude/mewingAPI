#include <cstdio>
#include <cstdlib>
#include <ctime>

#define usertag {id}LL // THANKS WARDEN

int main() 
{
    time_t seconds = time(NULL);
    int daysSinceEpoch = seconds / (60 * 60 * 24);

    unsigned long long randomseed = usertag + daysSinceEpoch; // ensure user's only get 1 a day
    srand(randomseed);

    int p = rand() % 35 + 1; // Range of 1 to 35 

    const char* s;

    switch (p) {
        case 1:
            s = "😄";
            break;
        case 2:
            s = "🍆🥚🥚";
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
            s = "🇵🇹";
            break;
        case 8:
            s = "🤡";
            break;
        case 9:
            s = "🇲🇿"; // inside joke, you wouldn't get it,,,,,,, 
            break;
        case 10:
            s = "<:skibid:1207635444909481984>";
            break;
        case 11:
            s = "🎮🕹️🖥️"; // geeked up 
            break;
        case 12:
            s = "😈";
            break;
        case 13:
            s = "🦄"; // le friendship est magique 
            break;
        case 14:
            s = "🍀";
            break;
        case 15:
            s = "😛";
            break;
        case 16:
            s = "🤮";
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
        case 21:
            s = "👅💦";
            break;
        case 22:
            s = "👨🏾‍🦽";
            break;
        case 23:
            s = "🇫🇷";
            break;
        case 24:
            s = "🗿";
            break;
        case 25:
            s = "👩‍❤️‍💋‍👩";
            break;
        case 26:
            s = "👨‍❤️‍💋‍👨";
            break;
        case 27:
            s = "🚽 💩💩💩💩"; // haha stinkie 
            break;
        case 28:
            s = "✈️🏢🏢";
            break;
        case 29:
            s = "🍍🍕";
            break;
        case 30:
            s = "😺🐟🤢🤮";
            break;
	case 31:
            s = "🤼‍♀️";
            break;
        case 32:
            s = "🖕";
            break;
        case 33:
            s = "<:sinister_kleiner:1121893499458027571>";
            break;
        case 34:
            s = "<:kleiner_happy:363444088965431298>";
            break;
        case 35:
            s = "🤫🧏🏻‍♂️";
            break;
        default:
            s = "❓"; // Just in case p is out of expected range
    }

    printf("Your emoji of today is: \n# %s", s);

    return 0;
}
