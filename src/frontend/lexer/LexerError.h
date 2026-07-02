#include <stdexcept>
#include <string>


class LexerError : public std::runtime_error {
public:
    explicit LexerError(const std::string& message, size_t offset)
    : std::runtime_error(message)
    , offset_(offset) {}

    explicit LexerError(const char* message, size_t offset)
    : std::runtime_error(message)
    , offset_(offset) {}
private:
    size_t offset_;
};