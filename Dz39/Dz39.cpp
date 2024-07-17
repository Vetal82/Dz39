#include <iostream>
#include <map>
#include <vector>
#include <string>

struct Violation {
    std::string description;
    int fine;
    std::string date;
};

typedef std::map<std::string, std::vector<Violation>> Database;

void printDatabase(const Database& database) {
    for (const auto& entry : database) {
        std::cout << "Car number: " << entry.first << std::endl;
        for (const auto& violation : entry.second) {
            std::cout << "  Description: " << violation.description << ", Fine: " << violation.fine << ", Date: " << violation.date << std::endl;
        }
    }
}

void printCarViolations(const Database& database, const std::string& carNumber) {
    auto it = database.find(carNumber);
    if (it != database.end()) {
        std::cout << "Car number: " << carNumber << std::endl;
        for (const auto& violation : it->second) {
            std::cout << "  Description: " << violation.description << ", Fine: " << violation.fine << ", Date: " << violation.date << std::endl;
        }
    }
    else {
        std::cout << "Car not found." << std::endl;
    }
}

int calculateTotalFine(const Database& database, const std::string& carNumber) {
    auto it = database.find(carNumber);
    if (it != database.end()) {
        int totalFine = 0;
        for (const auto& violation : it->second) {
            totalFine += violation.fine;
        }
        return totalFine;
    }
    else {
        return 0;
    }
}

void payFine(Database& database, const std::string& carNumber, int fine) {
    auto it = database.find(carNumber);
    if (it != database.end()) {
        for (auto& violation : it->second) {
            if (violation.fine == fine) {
                violation.fine = 0;
                std::cout << "Fine paid." << std::endl;
                return;
            }
        }
        std::cout << "Fine not found." << std::endl;
    }
    else {
        std::cout << "Car not found." << std::endl;
    }
}

void searchViolations(const Database& database, const std::string& startDate, const std::string& endDate) {
    for (const auto& entry : database) {
        for (const auto& violation : entry.second) {
            if (violation.date >= startDate && violation.date <= endDate) {
                std::cout << "Car number: " << entry.first << std::endl;
                std::cout << "  Description: " << violation.description << ", Fine: " << violation.fine << ", Date: " << violation.date << std::endl;
            }
        }
    }
}

int main() {
    Database database;

    // Add some sample data
    database["ABC123"].push_back({ "Speeding", 100, "2022-01-01" });
    database["ABC123"].push_back({ "Parking", 50, "2022-01-15" });
    database["DEF456"].push_back({ "Running red light", 200, "2022-02-01" });
    database["GHI789"].push_back({ "Driving without license", 500, "2022-03-01" });

    // Print database
    std::cout << "Database:" << std::endl;
    printDatabase(database);

    // Print car violations
    std::cout << "Car violations for ABC123:" << std::endl;
    printCarViolations(database, "ABC123");

    // Calculate total fine
    std::cout << "Total fine for ABC123: " << calculateTotalFine(database, "ABC123") << std::endl;

    // Pay fine
    payFine(database, "ABC123", 100);

    // Search violations
    std::cout << "Violations between 2022-01-01 and 2022-02-01:" << std::endl;
    searchViolations(database, "2022-01-01", "2022-02-01");

    return 0;
}