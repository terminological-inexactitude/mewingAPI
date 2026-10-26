#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

std::string findV(const std::string& j, const std::string& k, size_t pos = 0) {
    size_t s = j.find("\"" + k + "\":", pos);
    if (s == std::string::npos) return "";
    s = j.find_first_not_of(" \":", s + k.length() + 2);
    size_t e = j.find_first_of(",}", s);
    std::string v = j.substr(s, e - s);
    if (!v.empty() && v.front() == '"') v = v.substr(1, v.length() - 2);
    return v;
}

int main() {
    std::string key = MY_SECRET_KEY; 
    
    std::string cmd = "wget -qO- \"https://tankerkoenig.de" + key + "\" > f.json";

    if (system(cmd.c_str()) != 0) {
        std::cout << "❌ Failed to fetch price data.";
        return 1;
    }

    std::ifstream file("f.json");
    if (!file) return 1;
    std::stringstream buf;
    buf << file.rdbuf();
    std::string json = buf.str();

    if (json.find("\"ok\":true") == std::string::npos) {
        std::cout << "❌ API Error or no stations found.";
        return 1;
    }

    std::cout << "⛽ **Rütenbrock Border Fuel Prices** 🇩🇪\n```\nBrand      | Status | E5    | E10\n-----------------------------------\n";

    size_t pos = 0;
    while ((pos = json.find("\"id\":", pos)) != std::string::npos) {
        std::string brand = findV(json, "brand", pos);
        std::string open = findV(json, "isOpen", pos);
        std::string e5 = findV(json, "e5", pos);
        std::string e10 = findV(json, "e10", pos);

        if(brand.length() > 10) brand = brand.substr(0, 10);
        while(brand.length() < 10) brand += " ";

        std::string status = (open == "true") ? "OPEN  " : "CLOSED";

        std::cout << brand << " | " << status << " | €" << e5 << " | €" << e10 << "\n";
        pos += 5;
    }
    std::cout << "```\n";
    return 0;
}
