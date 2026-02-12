#pragma once
#include <filesystem>
#include "document.hpp"

namespace core {

class Parser {
public:
    Document parse(const std::filesystem::path& path);
};

}


