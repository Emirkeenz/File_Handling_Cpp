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

string runLengthDecoding(const string& compressed) {
  string decompressed;
  for (size_t i = 0; i < compressed.size(); i += 2) {
    int count = compressed[i] - '0'; // Get the count
    char symbol = compressed[i + 1]; // Get the symbol
    decompressed.append(count, symbol); // Append count symbols to the decompressed string
  }
  return decompressed;
}

int main() {
  ifstream compressedFin("compressed_car.txt");
  if (!compressedFin) {
    cerr << "Error: Unable to open compressed file." << endl;
    return 1;
  }

  string compressedContent;
  getline(compressedFin, compressedContent);
  compressedFin.close();

  string decompressedJson = runLengthDecoding(compressedContent);

  json carJson = json::parse(decompressedJson);
  Car car;
  car.fromJson(carJson);

  ofstream decompressedFout("decompressed_car.txt");
  if (!decompressedFout) {
    cerr << "Error: Unable to open output file for decompressed data." << endl;
    return 1;
  }
  decompressedFout << carJson << endl;
  decompressedFout.close();

  cout << "Decompression successful. Decompressed Car data written to 'decompressed_car.txt'." << endl;

  return 0;
}