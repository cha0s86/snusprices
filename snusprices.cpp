#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "snus.h"

struct SnusItem {
	int id;
	std::wstring merkki;
	std::wstring malli;
	std::wstring vahvuus;
	std::wstring hinta;
};

void loadDatabase(std::wstring filename, std::vector<SnusItem> database) {

	std::wcout << L"Loading database: " << filename << std::endl;
	std::wfstream file(filename);

	if (!file.is_open()) {
		std::wcerr << L"Error: Could not open file " << filename.c_str();
	}

	std::wstring line;
	std::getline(file, line); // Read the header line (first line);
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

	std::wcout << "Enter snus database: " << std::endl;
	
	std::wstring filename;
	std::wcin >> filename;

	// Print all databases (e.g kmarket.csv, sale.csv, prisma.csv)
	// Comment: for now just do one, load "snus.csv"...

	loadDatabase(filename, database);

	std::wcout << L"Database loaded successfully..." << std::endl;

	std::wcout << L"Welcome to nicotine pouch prices app!" << std::endl;
	
	Snus denssi_bf(L"Denssi", L"Brain freeze", L"6,50€", L"16mg/ps");
	Snus skruf_white(L"Skruf", L"White", L"6,50€", L"10mg/ps");
	Snus velo_freeze_max(L"VELO", L"Freeze Max", L"6,50€", L"16mg/ps");
	Snus zonex_cold_blast(L"ZoneX", L"Cold Blast", L"6,50€", L"16mg/ps");
	Snus greatest_cold_dry(L"Greatest", L"Cold Dry", L"6,50€", L"16mg/ps");
	Snus lundgrens_rimfrost(L"Lundgrens", L"Rimfrost", L"6,50€", L"10mg/ps");


	// todo: Find snus product using nicotine pouches search query
	
	std::wcout << "Do you want to list the available products? (yes/no): ";
	std::wstring answer;
	std::wcin >> answer;

	std::wcout << "-----------------------------------------------------" << std::endl;

	if (answer == L"yes") {
		// List all items
		std::wcout << L"Item 1 | " << denssi_bf.brand 		<< L" " << denssi_bf.label << std::endl;
		std::wcout << L"Item 2 | " << skruf_white.brand 	<< L" " << skruf_white.label << std::endl;
		std::wcout << L"Item 3 | " << velo_freeze_max.brand 	<< L" " << velo_freeze_max.label << std::endl;
		std::wcout << L"Item 4 | " << zonex_cold_blast.brand 	<< L" " << zonex_cold_blast.label << std::endl;
		std::wcout << L"Item 5 | " << greatest_cold_dry.brand 	<< L" " << greatest_cold_dry.label << std::endl;
		std::wcout << L"Item 6 | " << lundgrens_rimfrost.brand	<< L" " << lundgrens_rimfrost.label << std::endl;
	} else if (answer == L"no") {
		std::wcout << L"Exiting program..." << std::endl;
		return 0;
	} else {
		std::wcout << L"Wrong input, exiting..." << std::endl;
		return -1;
	}

	std::wcout << L"-----------------------------------------------------" << std::endl;
	
	// Print product information according to the index
	std::wcout << "Enter item ID to see the product information: ";
	int itemSelection;
	std::wcin >> itemSelection;

	std::wcout << "-----------------------------------------------------" << std::endl;

	switch (itemSelection) {
		case 1:
			std::wcout << "Brand: "     << denssi_bf.brand << std::endl;
			std::wcout << "Label: "     << denssi_bf.label << std::endl;
			std::wcout << "Price: "     << denssi_bf.price << std::endl;
			std::wcout << "Strength: "  << denssi_bf.strength << std::endl;
			break;
		case 2:
			std::wcout << "Brand: "     << skruf_white.brand << std::endl;
			std::wcout << "Label: "     << skruf_white.label << std::endl;
			std::wcout << "Price: "     << skruf_white.price << std::endl;
			std::wcout << "Strength: "  << skruf_white.strength << std::endl;
			break;
		case 3:
			std::wcout << "Brand: "     << velo_freeze_max.brand << std::endl;
			std::wcout << "Label: "     << velo_freeze_max.label << std::endl;
			std::wcout << "Price: "     << velo_freeze_max.price << std::endl;
			std::wcout << "Strength: "  << velo_freeze_max.strength << std::endl;
			break;
		case 4:
			std::wcout << "Brand: "     << zonex_cold_blast.brand << std::endl;
			std::wcout << "Label: "     << zonex_cold_blast.label << std::endl;
			std::wcout << "Price: "     << zonex_cold_blast.price << std::endl;
			std::wcout << "Strength: "  << zonex_cold_blast.strength << std::endl;
			break;
		case 5:
			std::wcout << "Brand: "     << greatest_cold_dry.brand << std::endl;
			std::wcout << "Label: "     << greatest_cold_dry.label << std::endl;
			std::wcout << "Price: "     << greatest_cold_dry.price << std::endl;
			std::wcout << "Strength: "  << greatest_cold_dry.strength << std::endl;
			break;
		case 6:
			std::wcout << "Brand: "     << lundgrens_rimfrost.brand << std::endl;
			std::wcout << "Label: "     << lundgrens_rimfrost.label << std::endl;
			std::wcout << "Price: "     << lundgrens_rimfrost.price << std::endl;
			std::wcout << "Strength: "  << lundgrens_rimfrost.strength << std::endl;
			break;
		default:
			break;
	}

	return 0;
}
