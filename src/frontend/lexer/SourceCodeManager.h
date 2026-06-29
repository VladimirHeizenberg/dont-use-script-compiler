#pragma once

#include <algorithm>
#include <string_view>
#include <vector>

class SourceCodeManager {
public:
    SourceCodeManager(std::string_view source_code_)
    : source_code(source_code_) {
        line_starts.push_back(0);
        for (int i = 0; i < source_code.size(); ++i) {
            if (source_code[i] == '\n') {
                line_starts.push_back(i + 1);
            }
        }
    }

    size_t get_line_start(size_t index) {
        auto it = std::lower_bound(line_starts.begin(), line_starts.end(), index);
        if (*it == index) {
            return index;
        }
        return *(it - 1);
    }

    std::string_view get_line(std::vector<size_t>::iterator iterator) {
        
    }

private:
    std::string_view source_code;
    std::vector<size_t> line_starts;
};