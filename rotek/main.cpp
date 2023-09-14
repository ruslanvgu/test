/*
Написать код программы на С++ для ОС Linux. Результат разместить на github.
Программа должна считать данные из файла /proc/meminfo, удалить из текста все символы ":", 
нулевые значения заменить на прочерк. Результат записать в новый файл, отсортировав строки по объему памяти.

кулик руслан
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct MemInfo {
    std::string name;
    std::string value;

    bool operator<(const MemInfo& other) const {
        return std::stoi(value) > std::stoi(other.value);
    }
};

std::vector<MemInfo> parseMemInfo(const std::string& filename) {
    std::vector<MemInfo> entries;

    std::ifstream file(filename);
    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            line.erase(std::remove(line.begin(), line.end(), ':'), line.end());

            std::istringstream iss(line);
            std::string name;
            std::string value;

            if (iss >> name >> value) {
                MemInfo entry;
                entry.name = name;
                entry.value = value;

                entries.push_back(entry);
            }
        }

        file.close();
    }

    return entries;
}

void writeSortedMemInfo(const std::vector<MemInfo>& entries, const std::string& filename) {
    std::ofstream file(filename);
    if (file) {
        for (const auto& entry : entries) {
            file << entry.name << " " <<( (std::stoi(entry.value) == 0) ? "-" : entry.value )<< "\n";
        }

        file.close();
    }
}

int main() {
    std::string inputFilename = "d:\\programming\\MVS\\test\\rotek\\meminfo.txt";
    std::string outputFilename = "result_meminfo.txt";

    std::vector<MemInfo> entries = parseMemInfo(inputFilename);

    std::sort(entries.begin(), entries.end());

    writeSortedMemInfo(entries, outputFilename);

    std::cout << "Результат записан в " << outputFilename << std::endl;

    return 0;
}
