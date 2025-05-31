#include <algorithm>
#include <iostream>
#include <codecvt>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <locale>
#include <map>

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

// Structure to represent a product in the Alko database
struct SnusItem {
    int id; // Product ID
    std::wstring merkki; // Product name
    std::wstring malli; // Manufacturer
    std::wstring vahvuus; // Bottle size
    std::wstring hinta; // Price
};

void loadDatabase(const std::string filename, std::vector<SnusItem> &database); // Forward declaration of loadDatabase function

// Funtion to load the database from a CSV file
void loadDatabase(const std::string filename, std::vector<SnusItem> &database) {
    std::wfstream file(filename);
    
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
    
    if (!file.is_open()) {
        std::wcerr << L"Error: Could not open file " << utf8_to_wstring(filename) << std::endl;
        return;
    }
    
    std::wstring line;

    std::getline(file, line); // Read the header line (first line)
    
    while (std::getline(file, line)) {
        std::wstringstream ss(line);
        SnusItem item;
        std::wstring token;

        std::getline(ss, token, L',');
        item.id = std::stoi(token);
        std::getline(ss, token, L',');
        item.merkki = token;
        std::getline(ss, token, L',');
        item.malli = token;
        std::getline(ss, token, L',');
        item.vahvuus = token;
        std::getline(ss, token, L',');
        item.hinta = token;
        database.push_back(item);
    }
    file.close();
}

// Function to print a separator line
void printSeparator() {
    std::wcout << L"------------------------------------------------------" << std::endl;
}

std::map<std::wstring, std::wstring> strings;
// Function to set the strings for the selected language
void setLanguageStrings(const std::wstring& language) {
    if (language == L"fi") {
        strings[L"PRODUCT_ID"] = L"Tuotteen ID: ";
        strings[L"PRODUCT_BRAND"] = L"Tuotemerkki: ";
        strings[L"PRODUCT_LABEL"] = L"Malli: ";
	strings[L"PRODUCT_STRENGTH"] = L"Vahvuus: ";
        strings[L"PRICE"] = L"Hinta: ";
        strings[L"MENU_HEADER"] = L"Valitse toiminto:";
        strings[L"MENU_OPTION_1"] = L"1. Hae tuotteita merkin perusteella";
        strings[L"MENU_OPTION_2"] = L"2. Poistu";
        strings[L"MENU_PROMPT"] = L"Anna valintasi (1-2): ";
        strings[L"DETAIL_PROMPT"] = L"Haluatko tuotetiedot tulostettuna jokainen omalla rivillä, vai tuoteblockeina?\n tuoteblockit ovat helposti luettavampia, mutta saattavat tukkia terminaalia, jos tuotteita on liikaa.\nValitse vaihtoehto:";
        strings[L"DETAIL_OPTION_1"] = L"1. Tuoteblockit";
        strings[L"DETAIL_OPTION_2"] = L"2. Tuotetiedot yhdellä rivillä";
        strings[L"DETAIL_PROMPT_INPUT"] = L"Anna valintasi (1-2): ";
        strings[L"INVALID_CHOICE"] = L"Virheellinen valinta. Yritä uudelleen.";
        strings[L"DEFAULTING_TO_NICELY"] = L"Virheellinen valinta. Oletuksena tulostetaan siististi.";
        strings[L"ENTER_PRODUCT_NAME"] = L"Anna haettavan tuotteen nimi: ";
        strings[L"SEARCHING"] = L"Haetaan tuotteita nimellä: ";
        strings[L"ERROR_NO_ITEMS"] = L"Virhe: Tietokannasta ei löytynyt tuotteita.";
        strings[L"DATABASE_LOADED"] = L"Tietokanta ladattu. ";
        strings[L"ITEMS_FOUND"] = L" tuotetta löydetty.";
        strings[L"WELCOME"] = L"Tervetuloa SnusPrices hakuohjelmaan!";
        strings[L"COPYRIGHT"] = L"Tekijänoikeus (c) 2025 Pekka Kukonlehto";
        strings[L"AUTHOR"] = L"Tekijä: Pekka Kukonlehto";
        strings[L"VERSION"] = L"Versio: v1.2";
        strings[L"DATE"] = L"Päivämäärä: 2025";
        strings[L"UNSUPPORTED_LANGUAGE"] = L"Virhe: Valittu kieli ei ole tuettu.";
        strings[L"SEPARATOR"] = L"------------------------------------------------------";
        strings[L"CATEGORY_NUMBER_PROMPT"] = L"Syötä kategorian numero: ";
    } else if (language == L"en") {
        strings[L"PRODUCT_ID"] = L"Product ID: ";
        strings[L"PRODUCT_BRAND"] = L"Brand: ";
        strings[L"PRODUCT_LABEL"] = L"Label: ";
	strings[L"PRODUCT_STRENGTH"] = L"Strength: ";
        strings[L"PRICE"] = L"Price: ";
        strings[L"MENU_OPTION_1"] = L"1. Search products by name";
        strings[L"MENU_OPTION_2"] = L"2. Exit";
        strings[L"MENU_PROMPT"] = L"Enter your choice (1-2): ";
        strings[L"DETAIL_PROMPT"] = L"Do you want the product details printed as blocks or on single lines?\nChoose an option:";
        strings[L"DETAIL_OPTION_1"] = L"1. Product blocks";
        strings[L"DETAIL_OPTION_2"] = L"2. Product details on single lines";
        strings[L"DETAIL_PROMPT_INPUT"] = L"Enter your choice (1-2): ";
        strings[L"INVALID_CHOICE"] = L"Invalid choice. Please try again.";
        strings[L"DEFAULTING_TO_NICELY"] = L"Invalid choice. Defaulting to nicely printed.";
        strings[L"ENTER_PRODUCT_NAME"] = L"Enter the product name to search: ";
        strings[L"SEARCHING"] = L"Searching for products with name: ";
        strings[L"ERROR_NO_ITEMS"] = L"Error: No items found in the database.";
        strings[L"DATABASE_LOADED"] = L"Database loaded successfully. ";
        strings[L"ITEMS_FOUND"] = L" items found.";
        strings[L"WELCOME"] = L"Welcome to the SnusPrices Search Program!";
        strings[L"COPYRIGHT"] = L"Copyright (c) 2025 Pekka Kukonlehto";
        strings[L"AUTHOR"] = L"Author: Pekka Kukonlehto";
        strings[L"VERSION"] = L"Version: v1.2";
        strings[L"DATE"] = L"Date: 2025";
        strings[L"UNSUPPORTED_LANGUAGE"] = L"Error: Unsupported language selected.";
        strings[L"SEPARATOR"] = L"------------------------------------------------------";
        strings[L"CATEGORY_NUMBER_PROMPT"] = L"Enter the category number: ";
    } else {
        std::wcerr << strings[L"UNSUPPORTED_LANGUAGE"] << std::endl;
        return;
    }
}

// Function to search for products by name
void searchByName(const std::vector<SnusItem> &database, const std::wstring &name, bool singleLine) {
    std::wcout << strings[L"SEARCHING"] << name << std::endl;
    printSeparator();
    bool found = false;

    for (const auto& item : database) {
        if (toLower(item.merkki).find(toLower(name)) != std::wstring::npos) {
            found = true;
            if (singleLine) {
                std::wcout << strings[L"PRODUCT_ID"] << item.id
                            << L", " << strings[L"PRODUCT_BRAND"] << item.merkki
                            << L", " << strings[L"PRODUCT_LABEL"] << item.malli
                            << L", " << strings[L"PRODUCT_STRENGTH"] << item.vahvuus
                            << L", " << strings[L"PRICE"] << item.hinta << std::endl;
            } else {
                if (item.id) std::wcout << strings[L"PRODUCT_ID"] << item.id << std::endl;
                if (!item.merkki.empty()) std::wcout << strings[L"PRODUCT_BRAND"] << item.merkki << std::endl;
                if (!item.malli.empty()) std::wcout << strings[L"PRODUCT_LABEL"] << item.malli << std::endl;
                if (!item.vahvuus.empty()) std::wcout << strings[L"PRODUCT_STRENGTH"] << item.vahvuus << std::endl;
                if (!item.hinta.empty()) std::wcout << strings[L"PRICE"] << item.hinta << std::endl;
                std::wcout << std::endl;
            }
        }
    }

    if (!found) {
        std::wcout << L"No products found with the name: " << name << std::endl;
    }
}

// Function to print the program header
void printHeader() {
    printSeparator();
    std::wcout << strings[L"WELCOME"] << std::endl;
    printSeparator();
    std::wcout << strings[L"COPYRIGHT"] << std::endl;
    std::wcout << strings[L"AUTHOR"] << std::endl;
    std::wcout << strings[L"VERSION"] << std::endl;
    std::wcout << strings[L"DATE"] << std::endl;
    printSeparator();
}

// Function to display the main menu
void displayMenu() {
    std::wcout << strings[L"MENU_HEADER"] << std::endl;
    std::wcout << strings[L"MENU_OPTION_1"] << std::endl;
    std::wcout << strings[L"MENU_OPTION_2"] << std::endl;
    std::wcout << strings[L"MENU_PROMPT"];
}

// Function to get the user's choice for detail level
bool getDetailChoice() {
    std::wcout << strings[L"DETAIL_PROMPT"] << std::endl;
    std::wcout << strings[L"DETAIL_OPTION_1"] << std::endl;
    std::wcout << strings[L"DETAIL_OPTION_2"] << std::endl;
    std::wcout << strings[L"DETAIL_PROMPT_INPUT"];

    int detailChoice;
    std::wcin >> detailChoice;
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (detailChoice == 1) {
        return false; // Printed nicely
    } else if (detailChoice == 2) {
        return true; // Single line
    } else {
        std::wcout << strings[L"DEFAULTING_TO_NICELY"] << std::endl;
        return false; // Default to printed nicely
    }
}

int main() {

    // Set the locale to support UTF-8 (Windows-specific)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "");
    system("chcp 65001 > nul");
    #endif

    // Set UTF-8 locale for C++ streams (Linux-specific)
    #ifdef __linux__
    std::setlocale(LC_ALL, "");
    #endif

    // Prompt the user for language choice
    std::wcout << L"Select language (1: Finnish, 2: English): ";
    int languageChoice;
    std::wcin >> languageChoice;
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::wstring language = (languageChoice == 2) ? L"en" : L"fi";
    setLanguageStrings(language);
    
    // Print the program header
    printHeader();

    // Load the database from the CSV file
    std::vector<SnusItem> database;


    std::wcout << "Please select your market..." << std::endl;
    std::wcout << "1. K-Market" << std::endl;
    std::wcout << "2. Sale" << std::endl;
    std::wcout << "3. Shell" << std::endl;
    std::wcout << "4. Prisma" << std::endl;

    std::wcout << "Please select the market: ";

    int market = 0; 

    std::wcin >> market;
    std::wcin.ignore();

    if (market == 1) {
	loadDatabase("kmarket.csv", database);
    } else if (market == 2) {
	loadDatabase("sale.csv", database);
    } else if (market == 3) {
	loadDatabase("shell.csv", database);
    } else if (market == 4) {
    	loadDatabase("prisma.csv", database);
    } else {
	std::cerr << "Invalid input, exiting..." << std::endl;
    }

    if (database.empty()) {
        std::wcerr << strings[L"ERROR_NO_ITEMS"] << std::endl;
        return 1;
    }

    // Check if the database is empty
    if (database.empty()) {
        std::wcerr << strings[L"ERROR_NO_ITEMS"] << std::endl;
        return 1;
    }

    // Print the number of items loaded
    std::wcout << strings[L"DATABASE_LOADED"] << database.size() << strings[L"ITEMS_FOUND"] << std::endl;
    printSeparator();
    
    // Main program loop
    bool searching = true;

    while (searching) {
        // Display menu options
        displayMenu();

        // Get the user's choice
        int choice;
        std::wcin >> choice;
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printSeparator();

        switch (choice) {
            case 1: { // Search by name
                std::wstring productName;
                std::wcout << strings[L"ENTER_PRODUCT_NAME"];
                std::getline(std::wcin, productName);
                bool singleLine = getDetailChoice();
                searchByName(database, productName, singleLine);
                break;
            }
            case 2: { // Exit
                searching = false;
                break;
            }
            default:
                std::wcout << strings[L"INVALID_CHOICE"] << std::endl;
        }
    }

    return 0;
}
