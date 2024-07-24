#include <iostream>
#include <fstream>

#define input "{args}"
#define usertag {id}LL

void writeVar(const char array[]){
    std::ofstream file("./output/__internals__.json");
	file << R"({"storage":{"server":{},"user":{},"channel":{"gamestate":")" << array << R"("}}})";
}

int main() {
    //printf("ja uhm");
	
	
	
	writeVar("id"); // save state of the game as an array
	
    return 0;
}
