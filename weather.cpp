#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#define input "{args}"

// Function to find a value in JSON by key
std::string findValue(const std::string& json, const std::string& key) {
    std::string keyWithQuotes = "\"" + key + "\":";
    size_t start = json.find(keyWithQuotes);
    if (start == std::string::npos) return "";

    start += keyWithQuotes.length();
    while (start < json.length() && (json[start] == ' ' || json[start] == '\"' || json[start] == ':')) start++;

    size_t end = start;
    while (end < json.length() && json[end] != ',' && json[end] != '}' && json[end] != '\"') end++;

    return json.substr(start, end - start);
}

int main() {
    printf("cool weather app");
	
	
	
    return 0;
}
