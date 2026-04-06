#include "core/parser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <windows.h>
#include <vector>


namespace fs = std::filesystem;

namespace core {

Document Parser::parse(const fs::path& path) {
    if (!fs::exists(path)) {
        throw std::runtime_error("File does not exist: " + path.string());
    }

    Document doc;
    doc.title = path.filename().string();

    std::stringstream buffer;

    // Normalize extension
    std::string ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext == ".pdf") {
        if (ext == ".pdf") {
    fs::path exeDir = fs::current_path();  // works in your setup

    fs::path xpdfPath = exeDir / "core" / "bin_external" / "xpdf" / "pdftotext.exe";


    if (!fs::exists(xpdfPath)) {
    fs::path xpdfPath2 = fs::current_path() / "xpdf_tools" / "pdftotext.exe";

    if (fs::exists(xpdfPath2)) {
        std::cerr << "Warning: pdftotext not found in expected location. Using fallback: " 
                  << xpdfPath2 << std::endl;
        xpdfPath = xpdfPath2; // ← Actually update xpdfPath so CreateProcess uses it
    } else {
        throw std::runtime_error("pdftotext not found at: " + xpdfPath.string());
        }
    }
// Now xpdfPath is valid in both the primary and fallback case

    // Unique temp file
    fs::path outputPath = fs::temp_directory_path() / fs::path("parsed-%%%%%%.txt");

    // Build command line (IMPORTANT: mutable char buffer required)
    std::string cmd =
        "\"" + xpdfPath.string() + "\" \"" +
        path.string() + "\" \"" +
        outputPath.string() + "\"";

    std::vector<char> cmdBuffer(cmd.begin(), cmd.end());
    cmdBuffer.push_back('\0');  // null-terminate


    // Set working directory to where the exe is (fixes DLL issues)
    std::string workingDir = xpdfPath.parent_path().string();

    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;  // ← add STARTF_USESTDHANDLES
    si.wShowWindow = SW_HIDE;
    si.hStdInput  = NULL;
    si.hStdOutput = NULL;
    si.hStdError  = NULL;
    
    BOOL success = CreateProcessA(
        NULL,
        cmdBuffer.data(),
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW | DETACHED_PROCESS,  // ← add DETACHED_PROCESS
        NULL,
        workingDir.c_str(),
        &si,
        &pi
    );

    if (!success) {
        DWORD err = GetLastError();
        throw std::runtime_error("CreateProcess failed with error: " + std::to_string(err));
    }

    // Wait for process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get exit code
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // Cleanup handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode != 0) {
        throw std::runtime_error("pdftotext failed with exit code: " + std::to_string(exitCode));
    }

    // Read output file
    std::ifstream outFile(outputPath);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open extracted text file");
    }

    buffer << outFile.rdbuf();
    outFile.close();

    fs::remove(outputPath);
}
    } else {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + path.string());
        }

        buffer << file.rdbuf();
        file.close();
    }

    doc.content = buffer.str();

    if (doc.content.empty()) {
        doc.content = "(Empty file)";
    }

    return doc;
}

}