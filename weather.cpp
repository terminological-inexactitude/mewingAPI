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
    printf("cool weather app\n\n");

	
    std::string apiKey = "41fd771949d80645893f3abaea9cca15";
    std::string location = "London"; // You can change this to any location
    std::string command = "wget -qO- \"http://api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=" + apiKey + "&units=metric\" > weather.json";

    // Execute the command to fetch weather data
    system(command.c_str());

    // Read the JSON data from the file
    std::ifstream file("weather.json");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonData = buffer.str();

    // Parse and display the weather data
    std::string cityName = findValue(jsonData, "name");
    std::string temperature = findValue(jsonData, "temp");
    std::string weatherDescription = findValue(jsonData, "description");

    std::cout << "Location: " << cityName << std::endl;
    std::cout << "Temperature: " << temperature << " °C" << std::endl;
    std::cout << "Weather: " << weatherDescription << std::endl;

    return 0;
}
