/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_STRING_VIEW_H
#define ARA_CORE_STRING_VIEW_H

#include <string_view> // std::string_view

namespace ara::core
{
    struct StringView
    {
        std::basic_string_view<char> data;
        StringView(const std::basic_string_view<char>& init) : data(init) {}
        // TODO: To be implemented
    };
} // ara::core

#endif // ARA_CORE_STRING_VIEW_H
