#include "core/parser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace core {

Document Parser::parse(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("File does not exist");
    }

    Document doc;
    doc.title = path.filename().string();

    // Open the file
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path.string());
    }

    // Read entire file content
    std::stringstream buffer;
    buffer << file.rdbuf();
    doc.content = buffer.str();

    file.close();

    if (doc.content.empty()) {
        doc.content = "(Empty file)";
    }

    return doc;
}

}