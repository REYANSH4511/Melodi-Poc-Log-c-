#include <iostream>
#include <fstream>
#include <ctime>

#define LOG_LEVEL_INFO "INFO"
#define LOG_LEVEL_WARNING "WARNING"
#define LOG_LEVEL_ERROR "ERROR"

// Function to log messages to a file
void logToFile(const std::string& message, const std::string& logLevel, const std::string& filename, int lineNumber, std::ofstream& logFile) {
    // Get the current time
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    // Format the timestamp
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);

    // Write the log entry to the file
    logFile << "[" << timestamp << "] [" << logLevel << "] [" << filename << ":" << lineNumber << "] " << message << std::endl;
}

int main() {
    // Open the log file for writing
    std::ofstream logFile("logfile.txt", std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Error opening the log file." << std::endl;
        return 1;
    }

    // Log different types of messages
    logToFile("Program started", LOG_LEVEL_INFO, __FILE__, __LINE__, logFile);
    logToFile("This is a warning message", LOG_LEVEL_WARNING, __FILE__, __LINE__, logFile);

    // Introduce an error and log it
    try {
        throw std::runtime_error("This is a simulated error.");
    } catch (const std::exception& e) {
        logToFile(e.what(), LOG_LEVEL_ERROR, __FILE__, __LINE__, logFile);
    }

    // Close the log file
    logFile.close();

    return 0;
}
