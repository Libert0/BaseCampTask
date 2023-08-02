#include "FileSearch.h"
#include "FileSeeker.h"
#include <string>
#include <vector>

std::string inputFileName() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::getline(std::cin, filename);
    return filename;
}

int main()
{
    std:: string filename = inputFileName();
    FileSeeker fileSearch("C:\\", filename);
    fileSearch.start();
    std::this_thread::sleep_for(std::chrono::seconds(5)); 
    fileSearch.stop();

    return 0;
}
