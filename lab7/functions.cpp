#include "functions.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

const std::string TXT_EXTENSION = ".txt";
const std::string BIN_EXTENSION = ".bin";
const std::string JSON_EXTENSION = ".json";
const std::string CSV_EXTENSION = ".csv";
const std::string INI_EXTENSION = ".ini";

std::string ASCIIProcessor::Read() {
    in_.open(filename_);
    if (!in_.is_open()) throw std::runtime_error("[ASCII Read]: file not opened");
    std::getline(in_, value_);
    in_.close();
    return value_;
}
void ASCIIProcessor::Write(const std::string& msg) {
    out_.open(filename_);
    if (!out_.is_open()) throw std::runtime_error("[ASCII Write]: file not opened");
    out_ << msg;
    out_.close();
}
void ASCIIProcessor::Write(int value) {
    out_.open(filename_);
    if (!out_.is_open()) throw std::runtime_error("[ASCII Write]: file not opened");
    out_ << value;
    out_.close();
}

std::string BinaryProcessor::Read() {
    in_.open(filename_, std::ios::binary);
    if (!in_.is_open()) throw std::runtime_error("[Binary Read]: file not opened");
    int x = 0;
    in_.read(reinterpret_cast<char*>(&x), sizeof(int));
    in_.close();
    return std::to_string(x);
}
void BinaryProcessor::Write(const std::string& msg) {
    out_.open(filename_, std::ios::binary);
    if (!out_.is_open()) throw std::runtime_error("[Binary Write]: file not opened");
    out_ << msg;
    out_.close();
}
void BinaryProcessor::Write(int value) {
    out_.open(filename_, std::ios::binary);
    if (!out_.is_open()) throw std::runtime_error("[Binary Write]: file not opened");
    out_.write(reinterpret_cast<const char*>(&value), sizeof(int));
    out_.close();
}

std::string JSONProcessor::Read() {
    in_.open(filename_);
    if (!in_.is_open()) throw std::runtime_error("[JSON Read]: file not opened");
    std::string line;
    value_.clear();
    while (std::getline(in_, line)) {
        value_ += line;
    }
    in_.close();
    return value_;
}
void JSONProcessor::Write(const std::string& msg) {
    out_.open(filename_);
    if (!out_.is_open()) throw std::runtime_error("[JSON Write]: file not opened");
    out_ << "{\n  \"data\": \"" << msg << "\"\n}";
    out_.close();
}
void JSONProcessor::Write(int value) {
    out_.open(filename_);
    if (!out_.is_open()) throw std::runtime_error("[JSON Write]: file not opened");
    out_ << "{\n  \"value\": " << value << "\n}";
    out_.close();
}

std::string CSVProcessor::Read() {
    in_.open(filename_);
    if (!in_.is_open()) throw std::runtime_error("[CSV Read]: file not opened");
    std::string line;
    std::vector<std::string> rows;
    while (std::getline(in_, line)) {
        rows.push_back(line);
    }
    in_.close();
    value_.clear();
    for (size_t i = 0; i < rows.size(); ++i) {
        value_ += rows[i];
        if (i != rows.size() - 1) value_ += "\n";
    }
    return value_;
}
void CSVProcessor::Write(const std::string& msg) {
    out_.open(filename_);
    if (!out_.is_open()) throw std::runtime_error("[CSV Write]: file not opened");
    out_ << msg;
    out_.close();
}
void CSVProcessor::Write(int value) {
    out_.open(filename_);
    if (!out_.is_open()) throw std::runtime_error("[CSV Write]: file not opened");
    out_ << value;
    out_.close();
}

std::string INIConfigProcessor::Read() {
    in_.open(filename_);
    if (!in_.is_open()) throw std::runtime_error("[INI Read]: file not opened");
    std::string line;
    std::map<std::string, std::string> config;
    std::string current_section;
    while (std::getline(in_, line)) {
        if (line.empty()) continue;
        if (line[0] == '[' && line[line.length() - 1] == ']') {
            current_section = line.substr(1, line.length() - 2);
        } else {
            size_t eq_pos = line.find('=');
            if (eq_pos != std::string::npos) {
                std::string key = line.substr(0, eq_pos);
                std::string val = line.substr(eq_pos + 1);
                std::string full_key = current_section.empty() ? key : current_section + "." + key;
                config[full_key] = val;
            }
        }
    }
    in_.close();
    value_.clear();
    for (const auto& pair : config) {
        value_ += pair.first + "=" + pair.second + "\n";
    }
    return value_;
}
void INIConfigProcessor::Write(const std::string& msg) {
    out_.open(filename_);
    if (!out_.is_open()) throw std::runtime_error("[INI Write]: file not opened");
    out_ << msg;
    out_.close();
}
void INIConfigProcessor::Write(int value) {
    out_.open(filename_);
    if (!out_.is_open()) throw std::runtime_error("[INI Write]: file not opened");
    out_ << "value=" << value << std::endl;
    out_.close();
}

FormatType define_type(const fs::path& filename) {
    std::string ext = filename.extension().string();
    if (ext == TXT_EXTENSION) return FormatType::ASCII;
    if (ext == BIN_EXTENSION) return FormatType::BINARY;
    if (ext == JSON_EXTENSION) return FormatType::JSON;
    if (ext == CSV_EXTENSION) return FormatType::CSV;
    if (ext == INI_EXTENSION) return FormatType::INI;
    throw std::invalid_argument("[define_type]: unsupported file extension");
}

FormatProcessor* create_processor(FormatType type, const std::string& filename) {
    if (type == FormatType::ASCII) return new ASCIIProcessor(filename);
    if (type == FormatType::BINARY) return new BinaryProcessor(filename);
    if (type == FormatType::JSON) return new JSONProcessor(filename);
    if (type == FormatType::CSV) return new CSVProcessor(filename);
    if (type == FormatType::INI) return new INIConfigProcessor(filename);
    throw std::invalid_argument("[create_processor]: not supported type");
}

void ProcessorFacade::Create(const std::vector<fs::path>& filenames) {
    for (size_t i = 0; i < filenames.size(); ++i) {
        FormatType type = define_type(filenames[i]);
        processors_.emplace_back(create_processor(type, filenames[i].string()));
    }
}
ProcessorFacade::~ProcessorFacade() {
    for (size_t i = 0; i < processors_.size(); ++i) {
        delete processors_[i];
    }
}
void ProcessorFacade::Write(int value) {
    for (size_t i = 0; i < processors_.size(); ++i) {
        processors_[i]->Write(value);
    }
}
void ProcessorFacade::Write(const std::string& msg) {
    for (size_t i = 0; i < processors_.size(); ++i) {
        processors_[i]->Write(msg);
    }
}
std::vector<std::string> ProcessorFacade::ReadAll() {
    std::vector<std::string> results;
    for (size_t i = 0; i < processors_.size(); ++i) {
        results.push_back(processors_[i]->Read());
    }
    return results;
}
