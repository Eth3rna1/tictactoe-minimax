/*
    Conditional selection
*/
/*#include <string>*/
#include <optional>
#include <vector>
#include <unordered_map>

class Options {
    std::unordered_map<std::string, std::string> __values;

public:
    Options(std::vector<std::string>& values) {
        for (int i=0; i < values.size(); ++i) {
            __values[std::to_string(i + 1)] = values[i];
        }
    }

    std::string display() const {
        std::string buffer = "";
        int size = __values.size();
        for (int i=0; i < size; ++i) {
            std::string str_index = std::to_string(i + 1);
            buffer += str_index + ".) " + __values.at(str_index);
            if (i < size - 1) {
                buffer += '\n';
            }
        }
        return buffer;
    }

    std::optional<std::string> eval(std::string v) {
        for (const auto& pair : __values) {
            if (pair.first == v) {
                return pair.second;
            } else if (pair.second == v) {
                return v;
            }
        }
        return std::nullopt;
    }
};

