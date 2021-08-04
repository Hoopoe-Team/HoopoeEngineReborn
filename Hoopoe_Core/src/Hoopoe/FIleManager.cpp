#include "Hoopoe/FileManager.hpp"
#include "Hoopoe/Log.hpp"

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

std::string FileManager::read(const std::string& filename) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream file_stream;
    try {
        file.open(filename.c_str());
        file_stream << file.rdbuf();
        file.close();
    }
    catch (std::ifstream::failure e) {
        LOG_ERROR("Error reading shader file");
    }
    return file_stream.str();
}
