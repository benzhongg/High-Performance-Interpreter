#pragma once
#include <memory>
#include <istream>
#include <string>
#include <stdexcept>

namespace utils {
    inline std::unique_ptr<std::istream> makeFileStream(const std::string& path) {
        auto file = std::make_unique<std::ifstream>(path, std::ios::binary);
        
        // Check if the file actually exists and opened
        if (!file->is_open()) {
            throw std::runtime_error("Could not open file: " + path);
        }
        return file;
    }
}