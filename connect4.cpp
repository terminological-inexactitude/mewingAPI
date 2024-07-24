#include <iostream>
#include <fstream>

#define getvar "{getchannel:game}"

void writeVar(const char array[]){
    std::ofstream file("./output/__internals__.json");
    file << R"({"storage":{"server":{},"user":{"game":")" << array << R"("},"channel":{}}})";
}

int main() {
    printf("asf");
	
	writeVar("gamestate example");
	
    return 0;
}
