#include <cstdio>
#include <cstdlib>
#include <ctime>
#define usertag {id}LL

int main() 
{
    time_t seconds;
    
    seconds = time(NULL);
    int daysSinceEpoch = seconds / (60 * 60 * 24);

    unsigned long long randomseed = usertag + daysSinceEpoch; // ensure user's only get 1 a day
    srand(randomseed);

    int p = rand() % 35 + 1; // Range of 1 to 35 
	
	printf("Number: %d", p);
}
