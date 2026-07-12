#pragma once

enum class TokenType {
    kNumber,
    kIdentifier,

    kPlus,
    kMinus,
    kAsteriks,
    kSlash,
    kLeftParenthesis,
    kRightParenthesis,
    kAssign,
    kSemicolon,


    // keywords
    kInt,
    kFloat,

    kEof,
};