#include <iostream>
#include <fstream>

void writeVar(const char array[]){
    std::ofstream file("./output/__internals__.json");
	file << R"({"storage":{"server":{},"user":{},"channel":{"gamestate":")" << array << R"("}}})";
}

int main() {
    printf("asf");
	
	writeVar("gamestate example");
	
    return 0;
}
