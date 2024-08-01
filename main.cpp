#include <cstdio>
#include <ctime>
#define usertag {id}LL

int main() 
{
    time_t seconds = time(NULL);	
	
	setenv("TZ", "Europe/Amsterdam", 1); // Set the timezone environment variable to Amsterdam
    tzset(); // Apply the timezone change
	
    int daysSinceEpoch = seconds / (60 * 60 * 24);
    unsigned long long randomseed = usertag + daysSinceEpoch; // ensure user's only get 1 a day
    
	srand(randomseed);
    int p = rand() % 35 + 1; // Range of 1 to 35 
	
	
	char* dt = ctime(&seconds);  // Convert time_t to a human-readable string
	printf("The updated local date and time is: %s", dt);  // Print the string
	
	printf("Number: %d", p);
}
