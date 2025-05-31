#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <vector>
#include <string>
#include <locale>
#include "snus.h"

struct SnusItem {
	int id;
	std::string merkki;
	std::string malli;
	std::string vahvuus;
	std::string hinta;
};

// Function to trim leading and trailing whitespace from a string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) return ""; // No non-whitespace characters
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

// Function to trim leading and trailing whitespace from a wstring
std::wstring trim(const std::wstring& str) {
    size_t first = str.find_first_not_of(L" \t\n\r\f\v");
    if (first == std::wstring::npos) return L""; // No non-whitespace characters
    size_t last = str.find_last_not_of(L" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

// Helper function to convert a string to lowercase
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Helper for UTF-8 to wstring conversion
std::wstring utf8_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.from_bytes(str);
}

// Helper function to convert a wstring to lowercase
std::wstring toLower(const std::wstring& str) {
    std::wstring lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::towlower);
    return lowerStr;
}

// Function to search for products by name
void searchByName(const std::vector<SnusItem> &database, std::string &merkki, bool singleLine) {
    
    bool found = false;

    for (const auto& item : database) {
        if (toLower(item.merkki).find(toLower(merkki)) != std::wstring::npos) {
            found = true;
            if (singleLine) {
                std::cout << "ID:" << item.id
                            << ", " << "Merkki: " << item.merkki
                            << ", " << "Malli: " << item.malli
                            << ", " << "Vahvuus: " << item.vahvuus
                            << ", " << "Hinta: " << item.hinta;
            } else {
                if (item.id) std::cout << "ID: " << item.id << std::endl;
                if (!item.merkki.empty()) std::cout << "Merkki: " << item.merkki << std::endl;
                if (!item.malli.empty()) std::cout << "Malli: " << item.malli << std::endl;
                if (!item.vahvuus.empty()) std::cout << "Vahvuus: " << item.vahvuus << std::endl;
                if (!item.hinta.empty()) std::cout << "Hinta: " << item.hinta << std::endl;
                std::cout << std::endl;
            }
        }
    }

    if (!found) {
        std::cout << L"No products found with the name: " << merkki << std::endl;
    }
}

void loadDatabase(std::string filename, std::vector<SnusItem> database) {

	std::cout << "Loading database: " << filename << std::endl;
	
	std::fstream file(filename.c_str());

	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file: " << filename << std::endl;
	}

	std::string line;
	std::getline(file, line); // Read the header line (first line);
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		SnusItem item;
		std::string token;

		std::getline(ss, token, ',');
		item.id = std::stoi(token);
		std::getline(ss, token, ',');
		item.merkki = token;
		std::getline(ss, token, ',');
		item.malli = token;
		std::getline(ss, token, ',');
		item.vahvuus = token;
		std::getline(ss, token, ',');
		item.hinta = token;
		
		database.push_back(item);
	}
	file.close();
}

int main() {

	std::vector<SnusItem> database;
	
	// Set the locale to support UTF-8 (Windows-specific)
    	#ifdef _WIN32
    	std::setlocale(LC_ALL, "");
    	system("chcp 65001 > nul");
    	#endif

    	// Set UTF-8 locale for C++ streams (Linux-specific)
    	#ifdef __linux__
    	std::setlocale(LC_ALL, "");
    	#endif

	std::cout << "Enter snus database: ";
	std::string dbname;
	std::cin >> dbname;

	// While searching
	// Print all databases (e.g kmarket.csv, sale.csv, prisma.csv)
	// Comment: for now just do one, load "snus.csv"...

	loadDatabase(dbname, database);

	std::cout << "Database loaded successfully..." << std::endl;

	std::cout << "Welcome to nicotine pouch prices app!" << std::endl;
	
	bool searching = true;

	while (searching) {
		std::string searchterm;
		std::cout << "Please enter the product name or leave empty to list all products: ";
		std::cin >> searchterm;

		bool singleLine;

		searchByName(database, searchterm, singleLine);

		std::cout << "--- 1. Search again / 2. Exit ---" << std::endl;
		std::cout << "Do you want to search again or exit?: ";
		
		int choice;
		std::cin >> choice;

		if (choice == 1) {
			// Do nothing
		} else if (choice == 2) {
			searching = false;
		} else {
			std::cout << "Invalid input" << std::endl;
		}
	}
	

	return 0;
}
