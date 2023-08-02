#pragma once

#include <string>
#include <thread>
#include <vector>
#include <atomic>

class FileSeeker
{
public:
    FileSeeker(const std::string& root, const std::string& filename);
    void start();
    void stop();
    void searchDirectory(const std::string& directory);
private:
    std::string root_;
    std::string filename_;
    std::vector<std::thread> threads_;
    std::atomic<bool> stop_ = false;
};
