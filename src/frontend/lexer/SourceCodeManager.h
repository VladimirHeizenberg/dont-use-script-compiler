#pragma once

#include <algorithm>
#include <string_view>
#include <vector>

class SourceCodeManager {
public:
    SourceCodeManager(std::string_view source_code_)
    : source_code_(source_code_) {
        line_starts_.push_back(0);
        for (int i = 0; i < source_code_.size(); ++i) {
            if (source_code_[i] == '\n') {
                line_starts_.push_back(i + 1);
            }
        }
    }

    [[nodiscard]] std::string_view GetLineAt(size_t offset) const {
        if (offset >= source_code_.size()) return {};

        auto it = std::upper_bound(line_starts_.begin(), line_starts_.end(), offset);
        auto current_line_start_it = std::prev(it);
        
        size_t start_pos = *current_line_start_it;
        size_t end_pos;

        if (it == line_starts_.end()) {
            end_pos = source_code_.size();
        } else {
            end_pos = *it - 1;
        }

        if (end_pos > start_pos && source_code_[end_pos - 1] == '\r') {
            --end_pos;
        }

        return source_code_.substr(start_pos, end_pos - start_pos);
    }

    [[nodiscard]] size_t GetLineNumber(size_t offset) const {
        auto it = std::upper_bound(line_starts_.begin(), line_starts_.end(), offset);
        return std::distance(line_starts_.begin(), std::prev(it)) + 1;
    }

private:
    std::string_view source_code_;
    std::vector<size_t> line_starts_;
};