#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

extern const std::string TXT_EXTENSION;
extern const std::string BIN_EXTENSION;
extern const std::string JSON_EXTENSION;
extern const std::string CSV_EXTENSION;
extern const std::string INI_EXTENSION;

class FormatProcessor {
public:
    FormatProcessor(const std::string& filename) : filename_(filename) {}
    virtual ~FormatProcessor() = default;
    virtual std::string Read() = 0;
    virtual void Write(const std::string&) = 0;
    virtual void Write(int) = 0;
protected:
    std::ifstream in_;
    std::ofstream out_;
    std::string value_;
    std::string filename_;
};

class ASCIIProcessor : public FormatProcessor {
public:
    using FormatProcessor::FormatProcessor;
    std::string Read() override;
    void Write(const std::string& msg) override;
    void Write(int value) override;
};

class BinaryProcessor : public FormatProcessor {
public:
    using FormatProcessor::FormatProcessor;
    std::string Read() override;
    void Write(const std::string& msg) override;
    void Write(int value) override;
};

class JSONProcessor : public FormatProcessor {
public:
    using FormatProcessor::FormatProcessor;
    std::string Read() override;
    void Write(const std::string& msg) override;
    void Write(int value) override;
};

class CSVProcessor : public FormatProcessor {
public:
    using FormatProcessor::FormatProcessor;
    std::string Read() override;
    void Write(const std::string& msg) override;
    void Write(int value) override;
};

class INIConfigProcessor : public FormatProcessor {
public:
    using FormatProcessor::FormatProcessor;
    std::string Read() override;
    void Write(const std::string& msg) override;
    void Write(int value) override;
};

enum class FormatType {
    ASCII,
    BINARY,
    JSON,
    CSV,
    INI
};

FormatType define_type(const fs::path& filename);
FormatProcessor* create_processor(FormatType type, const std::string& filename);

class ProcessorFacade {
public:
    void Create(const std::vector<fs::path>& filenames);
    ~ProcessorFacade();
    void Write(int value);
    void Write(const std::string& msg);
    std::vector<std::string> ReadAll();
private:
    std::vector<FormatProcessor*> processors_;
};

#endif // FUNCTIONS_H
