#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

struct Color {
    int red;
    int green;
    int blue;

    Color(int r, int g, int b) : red(r), green(g), blue(b) {}
};

std::string getFileExtension(const std::string& filename) {
    size_t dotIndex = filename.find_last_of(".");
    if (dotIndex != std::string::npos) {
        return filename.substr(dotIndex + 1);
    }
    return "";
}

int main() {
    std::string response;

    do {
      
        std::string filename;
        std::cout << "Podaj nazwe pliku: ";
        std::cin >> filename;

     
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Nie mozna otworzyc pliku." << std::endl;
            continue;
        }

        
        std::string format = getFileExtension(filename);
        if (format != "ppm" && format != "pgm" && format != "pbm") {
            std::cerr << "Nieobslugiwany format pliku." << std::endl;
            continue;
        }

       
        std::string magicNumber;
        int width, height, maxColor;
        file >> magicNumber >> width >> height >> maxColor;

        
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

       
        std::unordered_map<std::string, int> colorCount;

        
        if (format == "ppm") {
            for (int i = 0; i < width * height; ++i) {
                int r, g, b;
                file >> r >> g >> b;
                Color color(r, g, b);
                colorCount[std::to_string(r) + "-" + std::to_string(g) + "-" + std::to_string(b)]++;
            }
        }
        else if (format == "pgm" || format == "pbm") {
            for (int i = 0; i < width * height; ++i) {
                int value;
                file >> value;
                colorCount[std::to_string(value)]++;
            }
        }

        
        std::string mostCommonColor;
        int maxCount = 0;
        for (const auto& pair : colorCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostCommonColor = pair.first;
            }
        }

        
        std::cout << "\nSzerokosc obrazu: " << width << std::endl;
        std::cout << "Wysokosc obrazu: " << height << std::endl;
        std::cout << "Najczesciej wystepujacy kolor: " << mostCommonColor << " i wystapil " << maxCount << " razy." << std::endl;
        std::cout << "Ilosc unikalnych kolorow: " << colorCount.size() << std::endl;

        std::cout << "\nCzy chcesz wczytac kolejny plik (tak/nie): ";
        std::cin >> response;
    } while (response == "tak");

    return 0;
}