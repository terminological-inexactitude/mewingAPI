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
	if(input == ""){
		printf("please specify a city!");
		return 1;
	}
	
	// Check if JSON data contains error message
    if (jsonData.find("city not found") != std::string::npos ||
        jsonData.find("404") != std::string::npos) {
        printf("%s was not found. womp womp", input);
        return 1;
    }
	
    std::string apiKey = "41fd771949d80645893f3abaea9cca15";
    //std::string location = "London"; // You can change this to any location
    std::string location = input;
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
    std::string humidity = findValue(jsonData, "humidity");
	std::string pressure = findValue(jsonData, "pressure");

    // Print weather data with formatting
    std::cout << "Weather Information:\n";
    std::cout << "Location:\t\t" << cityName << "\n";
    std::cout << "Temperature:\t\t" << temperature << " °C\n";
    std::cout << "Weather:\t\t" << weatherDescription << "\n";
    std::cout << "Humidity:\t\t" << humidity << " %\n";
    std::cout << "Pressure:\t\t" << pressure << " hPa\n";
	
    return 0;
}
