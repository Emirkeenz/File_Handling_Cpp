#include <iostream>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

struct Car {
	string brand;
	int age;
	double price;
	double mileage;

	json toJson() const {
		return {
			{"brand", brand},
			{"age", age},
			{"price", price},
			{"mileage", mileage}
		};
	}

	void fromJson(const json& jsonData) {
		brand = jsonData["brand"];
		age = jsonData["age"];
		price = jsonData["price"];
		mileage = jsonData["mileage"];
	}
};

string runLengthEncoding(const string& input) {
	string compressed;
	int count = 1;
	char current = input[0];

	for (size_t i = 1; i < input.size(); ++i) {
		if (input[i] == current) {
			++count;
		} else {
			compressed += to_string(count) + current;
			count = 1;
			current = input[i];
		}
	}
	// Add the last character sequence
	compressed += to_string(count) + current;

	return compressed;
}

int main() {
	ifstream fin("input.txt");
	if (!fin) {
		cerr << "Error: Unable to open input file." << endl;
		return 1;
	}
	json carJson;
	fin >> carJson;
	fin.close();

	// Compress the JSON string using Run-Length Encoding
	string compressedContent = runLengthEncoding(carJson.dump());

	// Write the compressed content to "compressed.txt"
	ofstream compressedFout("compressed_car.txt");
	if (!compressedFout) {
		cerr << "Error: Unable to open output file for compressed data." << endl;
		return 1;
	}
	compressedFout << compressedContent;
	compressedFout.close();

	cout << "Compression successful. Compressed data written to 'compressed_car.txt'." << endl;

	return 0;
}
