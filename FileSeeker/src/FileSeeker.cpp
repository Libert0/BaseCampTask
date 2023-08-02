#include "FileSeeker.h"
#include <filesystem>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <mutex>

// variable to synchronize the output
std::mutex print_mutex;

FileSeeker::FileSeeker(const std::string& root, const std::string& filename)
    : root_(root), filename_(filename)
{ }

void FileSeeker::start()
{
    std::vector<std::string> directories;
    for (const auto& entry : std::filesystem::directory_iterator(root_))
    {
        if (entry.is_directory())
        {
            directories.push_back(entry.path().string());
        }
    }

    // Limit the number of threads to 8 or the number of subdirectories
    int numThreads = std::min(8, static_cast<int>(directories.size()));

    // Create a thread for each subdirectory
    for (int i = 0; i < numThreads; ++i) {
        std::string directory = directories[i];
        threads_.emplace_back([this, directory] {
            searchDirectory(directory);
            if (stop_) {
                print_mutex.lock();
                std::cout << "File is found!!! Stop seeking" << "\n";
                print_mutex.unlock();
                return;
            }
        });
    }
}

void FileSeeker::stop()
{
    for (auto& t : threads_) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void FileSeeker::searchDirectory(const std::string& directory)
{
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().filename() == filename_) {
                stop_.store(true); // Use .store() to write to an std::atomic<bool>
                print_mutex.lock();
                std::cout << entry.path() << "\n";
                print_mutex.unlock();
                break;
            }
            if (stop_.load()) { // Use .load() to read from an std::atomic<bool>
                return;
            }
        }
    }
    catch (std::filesystem::filesystem_error& e) {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << "Access denied to directory: " << directory << "\n";
        std::cout << "Error details: " << e.what() << "\n";
    } 
}