/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_STRING_H_
#define ARA_CORE_STRING_H_

#include <string>   // std::basic_string
#include <utility>  // std::forward, std::move, std::swap

#include "ara/core/allocator.h"

#include "ara/core/string_view.h"

namespace ara::core {

// [SWS_CORE_03000] String type
/*
The namespace ara::core shall provide a template type BasicString.
All members of this class and supporting constructs (such as global relational
operators) shall behave identical to those of std::basic_string in header
<string> from [5, the C++11 standard] section 21.3, except that the default
value for the Allocator template argument is implementation-defined. The
character type is fixed to char, and the traits type is fixed to
std::char_traits<char>. All supporting symbols shall be contained within
namespace ara::core.
*/
template<class AllocatorT = ara::core::Allocator<char>> class BasicString
{
    using string_t =
      std::basic_string<char, std::char_traits<char>, AllocatorT>;
    string_t __data;

 public:
    // types from STL
    using traits_type    = typename string_t::traits_type;
    using value_type     = typename traits_type::char_type;
    using allocator_type = AllocatorT;
    using size_type = typename std::allocator_traits<AllocatorT>::size_type;
    using difference_type =
      typename std::allocator_traits<AllocatorT>::difference_type;

    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename std::allocator_traits<AllocatorT>::pointer;
    using const_pointer =
      typename std::allocator_traits<AllocatorT>::const_pointer;

    using iterator               = typename string_t::iterator;
    using const_iterator         = typename string_t::const_iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr size_type npos = string_t::npos;

    // constructors from STL
    explicit BasicString(const AllocatorT& a = AllocatorT()) noexcept(
      std::is_nothrow_constructible<string_t, const AllocatorT&>::value)
      : __data(a)
    {}
    BasicString(const BasicString& bs) noexcept(
      std::is_nothrow_copy_constructible<string_t>::value)
      : __data(bs.__data)
    {}
    BasicString(BasicString&& bs) noexcept : __data(std::move(bs.__data)){};
    BasicString(
      const BasicString& str,
      size_type          pos,
      size_type          n = npos,
      const AllocatorT&  a =
        AllocatorT()) noexcept(std::is_nothrow_constructible<string_t,
                                                             const string_t&,
                                                             size_type,
                                                             size_type,
                                                             const AllocatorT&>::
                                 value)
      : __data(str.__data, pos, n, a)
    {}
    BasicString(
      const char*       s,
      size_type         n,
      const AllocatorT& a =
        AllocatorT()) noexcept(std::is_nothrow_constructible<string_t,
                                                             const char*,
                                                             size_type,
                                                             const AllocatorT&>::
                                 value)
      : __data(s, n, a)
    {}
    BasicString(const char* s, const AllocatorT& a = AllocatorT()) noexcept(
      std::is_nothrow_constructible<string_t, const char*, const AllocatorT&>::
        value)
      : __data(s, a)
    {}
    BasicString(size_type n, char c, const AllocatorT& a = AllocatorT()) noexcept(
      std::is_nothrow_constructible<string_t,
                                    size_type,
                                    char,
                                    const AllocatorT&>::value)
      : __data(n, c, a)
    {}
    template<class InputIterator> BasicString(
      InputIterator     begin,
      InputIterator     end,
      const AllocatorT& a =
        AllocatorT()) noexcept(std::is_nothrow_constructible<string_t,
                                                             InputIterator,
                                                             InputIterator,
                                                             const AllocatorT&>::
                                 value)
      : __data(begin, end, a)
    {}
    BasicString(std::initializer_list<char> i,
                const AllocatorT&           a =
                  AllocatorT()) noexcept(std::
                                           is_nothrow_constructible<
                                             string_t,
                                             std::initializer_list<char>,
                                             const AllocatorT&>::value)
      : __data(i, a)
    {}
    BasicString(const BasicString& bs, const AllocatorT& a) noexcept(
      std::is_nothrow_constructible<string_t,
                                    const string_t&,
                                    const AllocatorT&>::value)
      : __data(bs.__data, a)
    {}
    BasicString(BasicString&& bs, const AllocatorT& a) noexcept(
      std::is_nothrow_constructible<string_t, string_t&&, const AllocatorT&>::
        value)
      : __data(std::move(bs.__data), a)
    {}

    // assignment operator= from STL
    BasicString& operator=(const BasicString& str) noexcept(
      std::is_nothrow_assignable<string_t, const string_t&>::value)
    {
        __data = str.__data;
        return *this;
    }
    BasicString& operator=(BasicString&& str) noexcept
    {
        __data = std::move(str.__data);
        return *this;
    }
    BasicString& operator=(const char* s) noexcept(
      std::is_nothrow_assignable<string_t, const char*&>::value)
    {
        __data = s;
        return *this;
    }
    BasicString&
    operator=(char c) noexcept(std::is_nothrow_assignable<string_t, char>::value)
    {
        __data = c;
        return *this;
    }
    BasicString& operator=(std::initializer_list<char> i) noexcept(
      std::is_nothrow_assignable<string_t, std::initializer_list<char>>::value)
    {
        __data = i;
        return *this;
    }

    // iterator methods from STL
    iterator       begin() noexcept { return __data.begin(); }
    const_iterator begin() const noexcept { return __data.begin(); }
    iterator       end() noexcept { return __data.end(); }
    const_iterator end() const noexcept { return __data.end(); }

    reverse_iterator       rbegin() noexcept { return __data.rbegin(); }
    const_reverse_iterator rbegin() const noexcept { return __data.rbegin(); }
    reverse_iterator       rend() noexcept { return __data.rend(); }
    const_reverse_iterator rend() const noexcept { return __data.rend(); }

    const_iterator         cbegin() const noexcept { return __data.cbegin(); }
    const_iterator         cend() const noexcept { return __data.cend(); }
    const_reverse_iterator crbegin() const noexcept { return __data.crbegin(); }
    const_reverse_iterator crend() const noexcept { return __data.crend(); }

    // capacity methods from STL
    size_type size() const noexcept { return __data.size(); }
    size_type length() const noexcept { return __data.length(); }
    size_type max_size() const noexcept { return __data.max_size(); }
    void      resize(size_type n, char c) { __data.resize(n, c); }
    void      resize(size_type n) { __data.resize(n); }
    size_type capacity() const noexcept { return __data.capacity(); }
    void      reserve(size_type res_arg = 0) { __data.reserve(res_arg); }
    void      shrink_to_fit() { __data.shrink_to_fit(); }
    void      clear() noexcept { __data.clear(); }
    bool      empty() const noexcept { return __data.empty(); }

    // element access methods from STL
    const_reference operator[](size_type pos) const { return __data[pos]; }
    reference       operator[](size_type pos) { return __data[pos]; }
    const_reference at(size_type n) const { return __data.at(n); }
    reference       at(size_type n) { return __data.at(n); }

    const char& front() const { return __data.front(); }
    char&       front() { return __data.front(); }
    const char& back() const { return __data.back(); }
    char&       back() { return __data.back(); }

    // modifier methods from STL
    BasicString& operator+=(const BasicString& str)
    {
        __data += str.__data;
        return *this;
    }
    BasicString& operator+=(const char* s)
    {
        __data += s;
        return *this;
    }
    BasicString& operator+=(char c)
    {
        __data += c;
        return *this;
    }
    BasicString& operator+=(std::initializer_list<char> i)
    {
        __data += i;
        return *this;
    }
    BasicString& append(const BasicString& str)
    {
        __data.append(str.__data);
        return *this;
    }
    BasicString& append(const BasicString& str, size_type pos, size_type n)
    {
        __data.append(str.__data, pos, n);
        return *this;
    }
    BasicString& append(const char* s, size_type n)
    {
        __data.append(s, n);
        return *this;
    }
    BasicString& append(const char* s)
    {
        __data.append(s);
        return *this;
    }
    BasicString& append(size_type n, char c)
    {
        __data.append(n, c);
        return *this;
    }
    void push_back(char c) { __data.push_back(c); }

    BasicString& assign(const BasicString& str)
    {
        __data.assign(str.__data);
        return *this;
    }
    BasicString& assign(BasicString&& str) noexcept
    {
        __data.assign(std::move(str.__data));
        return *this;
    }
    BasicString& assign(const BasicString& str, size_type pos, size_type n)
    {
        __data.assign(str.__data, pos, n);
        return *this;
    }
    BasicString& assign(const char* s, size_type n)
    {
        __data.assign(s, n);
        return *this;
    }
    BasicString& assign(const char* s)
    {
        __data.assign(s);
        return *this;
    }
    template<class InputIterator> BasicString&
    assign(InputIterator first, InputIterator last)
    {
        __data.assign(first, last);
        return *this;
    }
    BasicString& assign(std::initializer_list<char> i)
    {
        __data.assign(i);
        return *this;
    }

    BasicString& insert(size_type pos1, const BasicString& str)
    {
        __data.insert(pos1, str.__data);
        return *this;
    }
    BasicString&
    insert(size_type pos1, const BasicString& str, size_type pos2, size_type n)
    {
        __data.insert(pos1, str.__data, pos2, n);
        return *this;
    }
    BasicString& insert(size_type pos, const char* str, size_type n)
    {
        __data.insert(pos, str, n);
        return *this;
    }
    BasicString& insert(size_type pos, const char* str)
    {
        __data.insert(pos, str);
        return *this;
    }
    BasicString& insert(size_type pos, size_type n, char c)
    {
        __data.insert(pos, n, c);
        return *this;
    }
    iterator insert(const_iterator p, char c) { return __data.insert(p, c); }
    iterator insert(const_iterator p, size_type n, char c)
    {
        return __data.insert(p, n, c);
    }
    template<class InputIterator> iterator
    insert(const_iterator p, InputIterator first, InputIterator last)
    {
        return __data.insert(p, first, last);
    }
    iterator insert(const_iterator p, std::initializer_list<char> i)
    {
        return __data.insert(p, i);
    }

    BasicString& erase(size_type pos = 0, size_type n = npos)
    {
        __data.erase(pos, n);
        return *this;
    }
    BasicString& erase(const_iterator p)
    {
        __data.erase(p);
        return *this;
    }
    BasicString& erase(const_iterator first, const_iterator last)
    {
        __data.erase(first, last);
        return *this;
    }

    void pop_back() { __data.pop_back(); }

    BasicString& replace(size_type pos1, size_type n1, const BasicString& str)
    {
        __data.replace(pos1, n1, str.__data);
        return *this;
    }
    BasicString& replace(size_type          pos1,
                         size_type          n1,
                         const BasicString& str,
                         size_type          pos2,
                         size_type          n2)
    {
        __data.replace(pos1, n1, str.__data, pos2, n2);
        return *this;
    }
    BasicString&
    replace(size_type pos, size_type n1, const char* s, size_type n2)
    {
        __data.replace(pos, n1, s, n2);
        return *this;
    }
    BasicString& replace(size_type pos, size_type n1, const char* s)
    {
        __data.replace(pos, n1, s);
        return *this;
    }
    BasicString& replace(size_type pos, size_type n1, size_type n2, char c)
    {
        __data.replace(pos, n1, n2, c);
        return *this;
    }

    BasicString&
    replace(const_iterator i1, const_iterator i2, const BasicString& str)
    {
        __data.replace(i1, i2, str.__data);
        return *this;
    }
    BasicString&
    replace(const_iterator i1, const_iterator i2, const char* s, size_type n)
    {
        __data.replace(i1, i2, s, n);
        return *this;
    }
    BasicString& replace(const_iterator i1, const_iterator i2, const char* s)
    {
        __data.replace(i1, i2, s);
        return *this;
    }
    BasicString&
    replace(const_iterator i1, const_iterator i2, size_type n, char c)
    {
        __data.replace(i1, i2, n, c);
        return *this;
    }
    template<class InputIterator> BasicString& replace(const_iterator i1,
                                                       const_iterator i2,
                                                       InputIterator  j1,
                                                       InputIterator  j2)
    {
        __data.replace(i1, i2, j1, j2);
        return *this;
    }
    BasicString&
    replace(const_iterator i1, const_iterator i2, std::initializer_list<char> i)
    {
        __data.replace(i1, i2, i);
        return *this;
    }

    size_type copy(char* s, size_type n, size_type pos = 0) const
    {
        return __data.copy(s, n, pos);
    }
    void swap(BasicString& str) { __data.swap(str.__data); }

    // comparision operators from STL
    bool operator==(const BasicString& other) const
    {
        return __data == other.__data;
    }
    bool operator==(const char* s) const { return __data == s; }
    bool operator!=(const BasicString& other) const
    {
        return __data != other.__data;
    }
    bool operator!=(const char* s) const { return __data != s; }

    bool operator<(const BasicString& other) const
    {
        return __data < other.__data;
    }
    bool operator<(const char* s) const { return __data < s; }

    bool operator>(const BasicString& other) const
    {
        return __data > other.__data;
    }
    bool operator>(const char* s) const { return __data > s; }

    bool operator<=(const BasicString& other) const
    {
        return __data <= other.__data;
    }
    bool operator<=(const char* s) const { return __data <= s; }

    bool operator>=(const BasicString& other) const
    {
        return __data >= other.__data;
    }
    bool operator>=(const char* s) const { return __data >= s; }

    // string operations methods from STL

    const char*    c_str() const noexcept { return __data.c_str(); }
    const char*    data() const noexcept { return __data.data(); }
    allocator_type get_allocator() const noexcept
    {
        return __data.get_allocator();
    }

    size_type find(const BasicString& str, size_type pos = 0) const noexcept
    {
        return __data.find(str.__data, pos);
    }
    size_type find(const char* s, size_type pos, size_type n) const
    {
        return __data.find(s, pos, n);
    }
    size_type find(const char* s, size_type pos = 0) const
    {
        return __data.find(s, pos);
    }
    size_type find(char c, size_type pos = 0) const noexcept
    {
        return __data.find(c, pos);
    }
    size_type rfind(const BasicString& str, size_type pos = npos) const noexcept
    {
        return __data.rfind(str.__data, pos);
    }
    size_type rfind(const char* s, size_type pos, size_type n) const
    {
        return __data.rfind(s, pos, n);
    }
    size_type rfind(const char* s, size_type pos = npos) const
    {
        return __data.rfind(s, pos);
    }
    size_type rfind(char c, size_type pos = npos) const noexcept
    {
        return __data.rfind(c, pos);
    }

    size_type
    find_first_of(const BasicString& str, size_type pos = 0) const noexcept
    {
        return __data.find_first_of(str.__data, pos);
    }
    size_type find_first_of(const char* s, size_type pos, size_type n) const
    {
        return __data.find_first_of(s, pos, n);
    }
    size_type find_first_of(const char* s, size_type pos = 0) const
    {
        return __data.find_first_of(s, pos);
    }
    size_type find_first_of(char c, size_type pos = 0) const noexcept
    {
        return __data.find_first_of(c, pos);
    }
    size_type
    find_last_of(const BasicString& str, size_type pos = npos) const noexcept
    {
        return __data.find_last_of(str.__data, pos);
    }
    size_type find_last_of(const char* s, size_type pos, size_type n) const
    {
        return __data.find_last_of(s, pos, n);
    }
    size_type find_last_of(const char* s, size_type pos = npos) const
    {
        return __data.find_last_of(s, pos);
    }
    size_type find_last_of(char c, size_type pos = npos) const noexcept
    {
        return __data.find_last_of(c, pos);
    }

    size_type
    find_first_not_of(const BasicString& str, size_type pos = 0) const noexcept
    {
        return __data.find_first_not_of(str.__data, pos);
    }
    size_type find_first_not_of(const char* s, size_type pos, size_type n) const
    {
        return __data.find_first_not_of(s, pos, n);
    }
    size_type find_first_not_of(const char* s, size_type pos = 0) const
    {
        return __data.find_first_not_of(s, pos);
    }
    size_type find_first_not_of(char c, size_type pos = 0) const noexcept
    {
        return __data.find_first_not_of(c, pos);
    }
    size_type find_last_not_of(const BasicString& str,
                               size_type          pos = npos) const noexcept
    {
        return __data.find_last_not_of(str.__data, pos);
    }
    size_type find_last_not_of(const char* s, size_type pos, size_type n) const
    {
        return __data.find_last_not_of(s, pos, n);
    }
    size_type find_last_not_of(const char* s, size_type pos = npos) const
    {
        return __data.find_last_not_of(s, pos);
    }
    size_type find_last_not_of(char c, size_type pos = npos) const noexcept
    {
        return __data.find_last_not_of(c, pos);
    }

    BasicString substr(size_type pos = 0, size_type n = npos) const
    {
        BasicString retval(__data.get_allocator());
        retval.__data = __data.substr(pos, n);
        return retval;
    }

    int compare(const BasicString& str) const noexcept
    {
        return __data.compare(str.__data);
    }
    int compare(size_type pos1, size_type n1, const BasicString& str) const
    {
        return __data.compare(pos1, n1, str.__data);
    }
    int compare(size_type          pos1,
                size_type          n1,
                const BasicString& str,
                size_type          pos2,
                size_type          n2) const
    {
        return __data.compare(pos1, n1, str.__data, pos2, n2);
    }
    int compare(const char* s) const { return __data.compare(s); }
    int compare(size_type pos1, size_type n1, const char* s) const
    {
        return __data.compare(pos1, n1, s);
    }
    int compare(size_type pos1, size_type n1, const char* s, size_type n2) const
    {
        return __data.compare(pos1, n1, s, n2);
    }

    // [SWS_CORE_03301] Implicit conversion to StringView
    /*
    An operator shall be defined for BasicString that provides implicit
    conversion to StringView: This function shall behave the same as the
    corresponding std::basic_string function from [6, the C++17 standard].
    */
    operator StringView() const noexcept
    {
        return static_cast<std::basic_string_view<char>>(__data);
    }

    // [SWS_CORE_03302] Constructor from StringView
    /*
    A constructor shall be defined for BasicString that accepts a StringView
    argument by value. This function shall behave the same as the corresponding
    std::basic_string function from [6, the C++17 standard].
    */
    explicit BasicString(StringView sv) : __data(sv) {}

    // [SWS_CORE_03303] Constructor from implicit StringView
    /*
    A constructor shall be defined for BasicString that accepts any type that is
    implicitly convertible to StringView. This function shall behave the same as
    the corresponding std::basic_string function from [6, the C++17 standard].
    */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    BasicString(T const& t, size_type pos, size_type n) : __data(t, pos, n)
    {}

    // [SWS_CORE_03304] operator= from StringView
    /*
    An operator= member function shall be defined for BasicString that accepts a
    StringView argument by value. This function shall behave the same as the
    corresponding std::basic_string function from [6, the C++17 standard].
    */
    BasicString& operator=(StringView sv)
    {
        __data = sv;
        return *this;
    }

    // [SWS_CORE_03305] Assignment from StringView
    /*
    A member function shall be defined for BasicString that allows assignment
    from StringView. This function shall behave the same as the corresponding
    std::basic_string function from [6, the C++17 standard].
    */
    BasicString& assign(StringView sv)
    {
        __data.assign(sv);
        return *this;
    }

    // [SWS_CORE_03306] Assignment from implicit StringView
    /*
    A member function shall be defined for BasicString that allows assignment
    from any type that is implicitly convertible to StringView: This function
    shall behave the same as the corresponding std::basic_string function from
    [6, the C++17 standard].
    */
    template<typename T> BasicString&
    assign(T const& t, size_type pos, size_type n = npos)
    {
        __data.assign(t, pos, n);
        return *this;
    }

    // [SWS_CORE_03307] operator+= from StringView
    /*
    An operator+= member function shall be defined for BasicString that accepts
    a StringView argument by value. This function shall behave the same as the
    corresponding std::basic_string function from [6, the C++17 standard].
    */
    BasicString& operator+=(StringView sv)
    {
        __data += sv;
        return *this;
    }

    // [SWS_CORE_03308] Concatenation of StringView
    /*
    A member function shall be defined for BasicString that allows concatenation
    of a StringView. This function shall behave the same as the corresponding
    std::basic_string function from [6, the C++17 standard].
    */
    BasicString& append(StringView sv)
    {
        __data.append(sv);
        return *this;
    }

    // [SWS_CORE_03309] Concatenation of implicit StringView
    /*
    A member function shall be defined for BasicString that allows concatenation
    of any type that is implicitly convertible to StringView. This function
    shall behave the same as the corresponding std::basic_string function from
    [6, the C++17 standard].
    */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    BasicString& append(T const& t, size_type pos, size_type n = npos)
    {
        __data.append(t, pos, n);
        return *this;
    }

    // [SWS_CORE_03310] Insertion of StringView
    /*
    A member function shall be defined for BasicString that allows insertion of
    a StringView: This function shall behave the same as the corresponding
    std::basic_string function from [6, the C++17 standard].
    */
    BasicString& insert(size_type pos, StringView sv)
    {
        __data.insert(pos, sv);
        return *this;
    }

    // [SWS_CORE_03311] Insertion of implicit StringView
    /*
    A member function shall be defined for BasicString that allows insertion of
    any type that is implicitly convertible to StringView. This function shall
    behave the same as the corresponding std::basic_string function from
    [6, the C++17 standard].
    */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    BasicString&
    insert(size_type pos1, T const& t, size_type pos2, size_type n = npos)
    {
        __data.insert(pos1, t, pos2, n);
        return *this;
    }

    // [SWS_CORE_03312] Replacement with StringView
    /*
    A member function shall be defined for BasicString that allows replacement
    of a subsequence of *this with the contents of a StringView. This function
    shall behave the same as the corresponding std::basic_string function from
    [6, the C++17 standard].
    */
    BasicString& replace(size_type pos1, size_type n1, StringView sv)
    {
        __data.replace(pos1, n1, sv);
        return *this;
    }

    // [SWS_CORE_03313] Replacement with implicit StringView
    /*
    A member function shall be defined for BasicString that allows replacement
    of a subsequence of *this with the contents of any type that is implicitly
    convertible to StringView. This function shall behave the same as the
    corresponding std::basic_string function from [6, the C++17 standard].
    */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    BasicString& replace(size_type pos1,
                         size_type n1,
                         T const&  t,
                         size_type pos2,
                         size_type n2 = npos)
    {
        __data.replace(pos1, n1, t, pos2, n2);
        return *this;
    }

    // [SWS_CORE_03314] Replacement of iterator range with StringView
    /*
    A member function shall be defined for BasicString that allows replacement
    of an iterator-bounded subsequence of *this with the contents of a
    StringView. This function shall behave the same as the corresponding
    std::basic_string function from [6, the C++17 standard].
    */
    BasicString& replace(const_iterator i1, const_iterator i2, StringView sv)
    {
        __data.replace(i1, i2, sv);
        return *this;
    }

    // [SWS_CORE_03315] Forward-find a StringView
    /*
    A member function shall be defined for BasicString that allows
    forward-searching for the contents of a StringView. This function shall
    behave the same as the corresponding std::basic_string function from
    [6, the C++17 standard].
    */
    size_type find(StringView sv, size_type pos = 0) const noexcept
    {
        return __data.find(sv, pos);
    }

    // [SWS_CORE_03316] Reverse-find a StringView
    /*
    A member function shall be defined for BasicString that allows
    reverse-searching for the contents of a StringView. This function shall
    behave the same as the corresponding std::basic_string function from
    [6, the C++17 standard].
    */
    size_type rfind(StringView sv, size_type pos = npos) const noexcept
    {
        return __data.rfind(sv, pos);
    }

    // [SWS_CORE_03317] Forward-find of character set within a StringView
    /*
    A member function shall be defined for BasicString that allows
    forward-searching for any of the characters within a StringView: This
    function shall behave the same as the corresponding std::basic_string
    function from [6, the C++17 standard].
    */
    size_type find_first_of(StringView sv, size_type pos = 0) const noexcept
    {
        return __data.find_first_of(sv, pos);
    }

    // [SWS_CORE_03318] Reverse-find of character set within a StringView
    /*
    A member function shall be defined for BasicString that allows
    reverse-searching for any of the characters within a StringView. This
    function shall behave the same as the corresponding std::basic_string
    function from [6, the C++17 standard].
    */
    size_type find_last_of(StringView sv, size_type pos = npos) const noexcept
    {
        return __data.find_last_of(sv, pos);
    }

    // [SWS_CORE_03319] Forward-find of character set not within a StringView
    /*
    A member function shall be defined for BasicString that allows
    forward-searching for any of the characters not contained in a StringView.
    This function shall behave the same as the corresponding std::basic_string
    function from [6, the C++17 standard].
    */
    size_type find_first_not_of(StringView sv, size_type pos = 0) const noexcept
    {
        return __data.find_first_not_of(sv, pos);
    }

    // [SWS_CORE_03320] Reverse-find of character set not within a StringView
    /*
    A member function shall be defined for BasicString that allows
    reverse-searching for any of the characters not contained in a StringView.
    This function shall behave the same as the corresponding std::basic_string
    function from [6, the C++17 standard].
    */
    size_type
    find_last_not_of(StringView sv, size_type pos = npos) const noexcept
    {
        return __data.find_last_not_of(sv, pos);
    }

    // [SWS_CORE_03321] Comparison with a StringView
    /*
    A member function shall be defined for BasicString that allows comparison
    with the contents of a StringView. This function shall behave the same as
    the corresponding std::basic_string function from [6, the C++17 standard].
    */
    int compare(StringView sv) const noexcept { return __data.compare(sv); }

    // [SWS_CORE_03322] Comparison of subsequence with a StringView
    /*
    A member function shall be defined for BasicString that allows comparison of
    a subsequence of *this with the contents of a StringView. This function
    shall behave the same as the corresponding std::basic_string function from
    [6, the C++17 standard].
    */
    int compare(size_type pos1, size_type n1, StringView sv) const
    {
        return __data.compare(pos1, n1, sv);
    }

    // [SWS_CORE_03323] Comparison of subsequence with a subsequence of a
    // StringView
    /*
    A member function shall be defined for BasicString that allows
    comparison of a subsequence of *this with the contents of a subsequence of
    any type that is implicitly convertible to StringView. This function shall
    behave the same as the corresponding std::basic_string function from
    [6, the C++17 standard].
    */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    int compare(size_type pos1,
                size_type n1,
                T const&  t,
                size_type pos2,
                size_type n2 = npos) const
    {
        return __data.compare(pos1, n1, t, pos2, n2);
    }

    // comparision operators from STL
    friend bool operator==(const char* s, const BasicString& bs)
    {
        return bs == s;
    }

    friend bool operator!=(const char* s, const BasicString& bs)
    {
        return bs != s;
    }
};

// [SWS_CORE_03001] String type
/*
The namespace ara::core shall provide a type alias String.
*/
using String = BasicString<>;

// [SWS_CORE_03296] swap overload for BasicString
/*
There shall be an overload of the swap function within the namespace ara::core
for arguments of type BasicString. This function shall exchange the state of lhs
with that of rhs.
*/
template<typename Allocator> void
swap(BasicString<Allocator>& lhs, BasicString<Allocator>& rhs)
{
    lhs.swap(rhs);
}

template<class AllocatorT> bool
operator<(const char* s, const BasicString<AllocatorT>& bs)
{
    return bs.compare(s) > 0;
}

template<class AllocatorT> bool
operator>(const char* s, const BasicString<AllocatorT>& bs)
{
    return bs.compare(s) < 0;
}

template<class AllocatorT> bool
operator<=(const char* s, const BasicString<AllocatorT>& bs)
{
    return bs.compare(s) >= 0;
}

template<class AllocatorT> bool
operator>=(const char* s, const BasicString<AllocatorT>& bs)
{
    return bs.compare(s) <= 0;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(const BasicString<AllocatorT>& lhs,
          const BasicString<AllocatorT>& rhs)
{
    BasicString<AllocatorT> ret(lhs);
    return ret += rhs;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(BasicString<AllocatorT>&& lhs, const BasicString<AllocatorT>& rhs)
{
    BasicString<AllocatorT> ret{std::forward<BasicString<AllocatorT>>(lhs)};
    return ret += rhs;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(const BasicString<AllocatorT>& lhs, BasicString<AllocatorT>&& rhs)
{
    BasicString<AllocatorT> ret(lhs);
    return ret += std::forward<BasicString<AllocatorT>>(rhs);
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(BasicString<AllocatorT>&& lhs, BasicString<AllocatorT>&& rhs)
{
    BasicString<AllocatorT> ret{std::forward<BasicString<AllocatorT>>(lhs)};
    return ret += std::forward<BasicString<AllocatorT>>(rhs);
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(const char* lhs, const BasicString<AllocatorT>& rhs)
{
    BasicString<AllocatorT> ret(lhs, rhs.get_allocator());
    return ret += rhs;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(const char* lhs, BasicString<AllocatorT>&& rhs)
{
    BasicString<AllocatorT> ret(lhs, rhs.get_allocator());
    return ret += rhs;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(char lhs, const BasicString<AllocatorT>& rhs)
{
    using size_type = typename BasicString<AllocatorT>::size_type;
    BasicString<AllocatorT> ret(size_type(1), lhs, rhs.get_allocator());
    return ret += rhs;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(char lhs, BasicString<AllocatorT>&& rhs)
{
    using size_type = typename BasicString<AllocatorT>::size_type;
    BasicString<AllocatorT> ret(size_type(1), lhs, rhs.get_allocator());
    return ret += rhs;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(const BasicString<AllocatorT>& lhs, const char* rhs)
{
    BasicString<AllocatorT> ret(lhs);
    return ret += rhs;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(BasicString<AllocatorT>&& lhs, const char* rhs)
{
    BasicString<AllocatorT> ret{std::forward<BasicString<AllocatorT>>(lhs)};
    return ret += rhs;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(const BasicString<AllocatorT>& lhs, char rhs)
{
    BasicString<AllocatorT> ret(lhs);
    return ret += rhs;
}

template<class AllocatorT> BasicString<AllocatorT>
operator+(BasicString<AllocatorT>&& lhs, char rhs)
{
    BasicString<AllocatorT> ret{std::forward<BasicString<AllocatorT>>(lhs)};
    return ret += rhs;
}

}  // namespace ara::core

#endif  // ARA_CORE_STRING_H_
