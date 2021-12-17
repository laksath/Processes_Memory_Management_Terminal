#include <fstream>
#include <string>

int main()
{
    const char *path="/home/laksath/Desktop/file.txt";
    std::ofstream file(path); //open in constructor
    std::string data("data to write to file");
    file << data;
}