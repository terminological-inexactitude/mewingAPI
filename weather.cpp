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
		printf("Please specify a city!");
		return 1;
	}
	
	std::string apiKey = "41fd771949d80645893f3abaea9cca15";
	std::string location = input;
	
	// Construct the command to fetch weather data
    std::string command = "wget -qO- \"http://api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=" + apiKey + "&units=metric\" > weather.json";

    // Execute the command
    int result = system(command.c_str());
    if (result != 0) {
        //std::cerr << "Error: Failed to fetch weather data." << std::endl;
		std::cerr << "Error: the city '" << input << "' was not found. Womp womp" << std::endl;
        return 1;
    }

    // Read the JSON data from the file
    std::ifstream file("weather.json");
    if (!file) {
        std::cerr << "Error: Failed to open the file for reading." << std::endl;
        return 1;
    }
	
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonData = buffer.str();

    // Parse and display the weather data
    std::string cityName = findValue(jsonData, "name");
    std::string weatherDescription = findValue(jsonData, "description");
    std::string temperature = findValue(jsonData, "temp");
    std::string humidity = findValue(jsonData, "humidity");
    std::string pressure = findValue(jsonData, "pressure");
    std::string windSpeed = findValue(jsonData, "speed");

    // Print weather data with formatting
    std::cout << "🌆 Location:    \t\t\t" << cityName << "\n";
    std::cout << "☀️ Description:  \t\t" << weatherDescription << "\n";
    std::cout << "🌡️ Temperature:\t\t" << temperature << " °C\n";
    std::cout << "💧 Humidity:   \t\t\t" << humidity << " %\n";
    std::cout << "🌫 Pressure:\t\t\t\t" << pressure << " hPa\n";
    std::cout << "🌬️ Wind Speed:  \t\t" << windSpeed << " m/s\n";
	
    return 0;
}
