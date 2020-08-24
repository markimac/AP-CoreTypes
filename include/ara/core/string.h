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
    string_t _data;

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
      : _data(a)
    {}
    BasicString(const BasicString& bs) noexcept(
      std::is_nothrow_copy_constructible<string_t>::value)
      : _data(bs._data)
    {}

    BasicString(BasicString&& bs) noexcept : _data(std::move(bs._data)){};
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
      : _data(str._data, pos, n, a)
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
      : _data(s, n, a)
    {}
    BasicString(const char* s, const AllocatorT& a = AllocatorT()) noexcept(
      std::is_nothrow_constructible<string_t, const char*, const AllocatorT&>::
        value)
      : _data(s, a)
    {}
    BasicString(size_type n, char c, const AllocatorT& a = AllocatorT()) noexcept(
      std::is_nothrow_constructible<string_t,
                                    size_type,
                                    char,
                                    const AllocatorT&>::value)
      : _data(n, c, a)
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
      : _data(begin, end, a)
    {}
    BasicString(std::initializer_list<char> i,
                const AllocatorT&           a =
                  AllocatorT()) noexcept(std::
                                           is_nothrow_constructible<
                                             string_t,
                                             std::initializer_list<char>,
                                             const AllocatorT&>::value)
      : _data(i, a)
    {}
    BasicString(const BasicString& bs, const AllocatorT& a) noexcept(
      std::is_nothrow_constructible<string_t,
                                    const string_t&,
                                    const AllocatorT&>::value)
      : _data(bs._data, a)
    {}
    BasicString(BasicString&& bs, const AllocatorT& a) noexcept(
      std::is_nothrow_constructible<string_t, string_t&&, const AllocatorT&>::
        value)
      : _data(std::move(bs._data), a)
    {}

    // assignment operator= from STL
    BasicString& operator=(const BasicString& str) noexcept(
      std::is_nothrow_assignable<string_t, const string_t&>::value)
    {
        _data = str._data;
        return *this;
    }
    BasicString& operator=(BasicString&& str) noexcept
    {
        _data = std::move(str._data);
        return *this;
    }
    BasicString& operator=(const char* s) noexcept(
      std::is_nothrow_assignable<string_t, const char*&>::value)
    {
        _data = s;
        return *this;
    }
    BasicString&
    operator=(char c) noexcept(std::is_nothrow_assignable<string_t, char>::value)
    {
        _data = c;
        return *this;
    }
    BasicString& operator=(std::initializer_list<char> i) noexcept(
      std::is_nothrow_assignable<string_t, std::initializer_list<char>>::value)
    {
        _data = i;
        return *this;
    }

    // iterator methods from STL

    iterator       begin() noexcept { return _data.begin(); }

    // capacity methods from STL
    size_type size() const noexcept { return _data.size(); }

    size_type length() const noexcept { return _data.length(); }
    size_type max_size() const noexcept { return _data.max_size(); }
    void      resize(size_type n, char c) { _data.resize(n, c); }
    void      resize(size_type n) { _data.resize(n); }
    size_type capacity() const noexcept { return _data.capacity(); }
    void      reserve(size_type res_arg = 0) { _data.reserve(res_arg); }
    void      shrink_to_fit() { _data.shrink_to_fit(); }
    void      clear() noexcept { _data.clear(); }
    bool      empty() const noexcept { return _data.empty(); }
    // element access methods from STL
    const_reference operator[](size_type pos) const { return _data[pos]; }

    reference       operator[](size_type pos) { return _data[pos]; }

    const_reference at(size_type n) const { return _data.at(n); }
    reference       at(size_type n) { return _data.at(n); }
    const char& front() const { return _data.front(); }
    char&       front() { return _data.front(); }
    const char& back() const { return _data.back(); }
    char&       back() { return _data.back(); }
    // modifier methods from STL
    BasicString& operator+=(const BasicString& str)
    {
        _data += str._data;
        return *this;
    }
    BasicString& operator+=(const char* s)
    {
        _data += s;
        return *this;
    }
    BasicString& operator+=(char c)
    {
        _data += c;
        return *this;
    }
    BasicString& operator+=(std::initializer_list<char> i)
    {
        _data += i;
        return *this;
    }
    BasicString& append(const BasicString& str)
    {
        _data.append(str._data);
        return *this;
    }
    BasicString& append(const BasicString& str, size_type pos, size_type n)
    {
        _data.append(str._data, pos, n);
        return *this;
    }
    BasicString& append(const char* s, size_type n)
    {
        _data.append(s, n);
        return *this;
    }
    BasicString& append(const char* s)
    {
        _data.append(s);
        return *this;
    }
    BasicString& append(size_type n, char c)
    {
        _data.append(n, c);
        return *this;
    }

    void push_back(char c) { _data.push_back(c); }

    BasicString& assign(const BasicString& str)
    {
        _data.assign(str._data);
        return *this;
    }
    BasicString& assign(BasicString&& str) noexcept
    {
        _data.assign(std::move(str._data));
        return *this;
    }
    BasicString& assign(const BasicString& str, size_type pos, size_type n)
    {
        _data.assign(str._data, pos, n);
        return *this;
    }
    BasicString& assign(const char* s, size_type n)
    {
        _data.assign(s, n);
        return *this;
    }
    BasicString& assign(const char* s)
    {
        _data.assign(s);
        return *this;
    }
    template<class InputIterator> BasicString&
    assign(InputIterator first, InputIterator last)
    {
        _data.assign(first, last);
        return *this;
    }
    BasicString& assign(std::initializer_list<char> i)
    {
        _data.assign(i);
        return *this;
    }

    BasicString& insert(size_type pos1, const BasicString& str)
    {
        _data.insert(pos1, str._data);
        return *this;
    }
    BasicString&
    insert(size_type pos1, const BasicString& str, size_type pos2, size_type n)
    {
        _data.insert(pos1, str._data, pos2, n);
        return *this;
    }
    BasicString& insert(size_type pos, const char* str, size_type n)
    {
        _data.insert(pos, str, n);
        return *this;
    }
    BasicString& insert(size_type pos, const char* str)
    {
        _data.insert(pos, str);
        return *this;
    }
    BasicString& insert(size_type pos, size_type n, char c)
    {
        _data.insert(pos, n, c);
        return *this;
    }
    iterator insert(const_iterator p, char c) { return _data.insert(p, c); }
    iterator insert(const_iterator p, size_type n, char c)
    {
        return _data.insert(p, n, c);
    }
    template<class InputIterator> iterator
    insert(const_iterator p, InputIterator first, InputIterator last)
    {
        return _data.insert(p, first, last);
    }
    iterator insert(const_iterator p, std::initializer_list<char> i)
    {
        return _data.insert(p, i);
    }

    BasicString& erase(size_type pos = 0, size_type n = npos)
    {
        _data.erase(pos, n);
        return *this;
    }
    BasicString& erase(const_iterator p)
    {
        _data.erase(p);
        return *this;
    }
    BasicString& erase(const_iterator first, const_iterator last)
    {
        _data.erase(first, last);
        return *this;
    }

    void pop_back() { _data.pop_back(); }

    BasicString& replace(size_type pos1, size_type n1, const BasicString& str)
    {
        _data.replace(pos1, n1, str._data);
        return *this;
    }
    BasicString& replace(size_type          pos1,
                         size_type          n1,
                         const BasicString& str,
                         size_type          pos2,
                         size_type          n2)
    {
        _data.replace(pos1, n1, str._data, pos2, n2);
        return *this;
    }
    BasicString&
    replace(size_type pos, size_type n1, const char* s, size_type n2)
    {
        _data.replace(pos, n1, s, n2);
        return *this;
    }
    BasicString& replace(size_type pos, size_type n1, const char* s)
    {
        _data.replace(pos, n1, s);
        return *this;
    }
    BasicString& replace(size_type pos, size_type n1, size_type n2, char c)
    {
        _data.replace(pos, n1, n2, c);
        return *this;
    }

    BasicString&
    replace(const_iterator i1, const_iterator i2, const BasicString& str)
    {
        _data.replace(i1, i2, str._data);
        return *this;
    }
    BasicString&
    replace(const_iterator i1, const_iterator i2, const char* s, size_type n)
    {
        _data.replace(i1, i2, s, n);
        return *this;
    }
    BasicString& replace(const_iterator i1, const_iterator i2, const char* s)
    {
        _data.replace(i1, i2, s);
        return *this;
    }
    BasicString&
    replace(const_iterator i1, const_iterator i2, size_type n, char c)
    {
        _data.replace(i1, i2, n, c);
        return *this;
    }
    template<class InputIterator> BasicString& replace(const_iterator i1,
                                                       const_iterator i2,
                                                       InputIterator  j1,
                                                       InputIterator  j2)
    {
        _data.replace(i1, i2, j1, j2);
        return *this;
    }
    BasicString&
    replace(const_iterator i1, const_iterator i2, std::initializer_list<char> i)
    {
        _data.replace(i1, i2, i);
        return *this;
    }

    size_type copy(char* s, size_type n, size_type pos = 0) const
    {
        return _data.copy(s, n, pos);
    }
    void swap(BasicString& str) { _data.swap(str._data); }

    // comparision operators from STL
    bool operator==(const BasicString& other) const
    {
        return _data == other._data;
    }
    bool operator==(const char* s) const { return _data == s; }
    bool operator!=(const BasicString& other) const
    {
        return _data != other._data;
    }
    bool operator!=(const char* s) const { return _data != s; }

    bool operator<(const BasicString& other) const
    {
        return _data < other._data;
    }
    bool operator<(const char* s) const { return _data < s; }

    bool operator>(const BasicString& other) const
    {
        return _data > other._data;
    }
    bool operator>(const char* s) const { return _data > s; }

    bool operator<=(const BasicString& other) const
    {
        return _data <= other._data;
    }
    bool operator<=(const char* s) const { return _data <= s; }

    bool operator>=(const BasicString& other) const
    {
        return _data >= other._data;
    }
    bool operator>=(const char* s) const { return _data >= s; }

    // string operations methods from STL

    const char*    c_str() const noexcept { return _data.c_str(); }
    const char*    data() const noexcept { return _data.data(); }
    allocator_type get_allocator() const noexcept
    {
        return _data.get_allocator();
    }

    size_type find(const BasicString& str, size_type pos = 0) const noexcept
    {
        return _data.find(str._data, pos);
    }
    size_type find(const char* s, size_type pos, size_type n) const
    {
        return _data.find(s, pos, n);
    }
    size_type find(const char* s, size_type pos = 0) const
    {
        return _data.find(s, pos);
    }
    size_type find(char c, size_type pos = 0) const noexcept
    {
        return _data.find(c, pos);
    }
    size_type rfind(const BasicString& str, size_type pos = npos) const noexcept
    {
        return _data.rfind(str._data, pos);
    }
    size_type rfind(const char* s, size_type pos, size_type n) const
    {
        return _data.rfind(s, pos, n);
    }
    size_type rfind(const char* s, size_type pos = npos) const
    {
        return _data.rfind(s, pos);
    }
    size_type rfind(char c, size_type pos = npos) const noexcept
    {
        return _data.rfind(c, pos);
    }

    size_type
    find_first_of(const BasicString& str, size_type pos = 0) const noexcept
    {
        return _data.find_first_of(str._data, pos);
    }
    size_type find_first_of(const char* s, size_type pos, size_type n) const
    {
        return _data.find_first_of(s, pos, n);
    }
    size_type find_first_of(const char* s, size_type pos = 0) const
    {
        return _data.find_first_of(s, pos);
    }
    size_type find_first_of(char c, size_type pos = 0) const noexcept
    {
        return _data.find_first_of(c, pos);
    }
    size_type
    find_last_of(const BasicString& str, size_type pos = npos) const noexcept
    {
        return _data.find_last_of(str._data, pos);
    }
    size_type find_last_of(const char* s, size_type pos, size_type n) const
    {
        return _data.find_last_of(s, pos, n);
    }
    size_type find_last_of(const char* s, size_type pos = npos) const
    {
        return _data.find_last_of(s, pos);
    }
    size_type find_last_of(char c, size_type pos = npos) const noexcept
    {
        return _data.find_last_of(c, pos);
    }

    size_type
    find_first_not_of(const BasicString& str, size_type pos = 0) const noexcept
    {
        return _data.find_first_not_of(str._data, pos);
    }
    size_type find_first_not_of(const char* s, size_type pos, size_type n) const
    {
        return _data.find_first_not_of(s, pos, n);
    }
    size_type find_first_not_of(const char* s, size_type pos = 0) const
    {
        return _data.find_first_not_of(s, pos);
    }
    size_type find_first_not_of(char c, size_type pos = 0) const noexcept
    {
        return _data.find_first_not_of(c, pos);
    }
    size_type find_last_not_of(const BasicString& str,
                               size_type          pos = npos) const noexcept
    {
        return _data.find_last_not_of(str._data, pos);
    }
    size_type find_last_not_of(const char* s, size_type pos, size_type n) const
    {
        return _data.find_last_not_of(s, pos, n);
    }
    size_type find_last_not_of(const char* s, size_type pos = npos) const
    {
        return _data.find_last_not_of(s, pos);
    }
    size_type find_last_not_of(char c, size_type pos = npos) const noexcept
    {
        return _data.find_last_not_of(c, pos);
    }

    BasicString substr(size_type pos = 0, size_type n = npos) const
    {
        BasicString retval(_data.get_allocator());
        retval._data = _data.substr(pos, n);
        return retval;
    }

    int compare(const BasicString& str) const noexcept
    {
        return _data.compare(str._data);
    }
    int compare(size_type pos1, size_type n1, const BasicString& str) const
    {
        return _data.compare(pos1, n1, str._data);
    }
    int compare(size_type          pos1,
                size_type          n1,
                const BasicString& str,
                size_type          pos2,
                size_type          n2) const
    {
        return _data.compare(pos1, n1, str._data, pos2, n2);
    }
    int compare(const char* s) const { return _data.compare(s); }
    int compare(size_type pos1, size_type n1, const char* s) const
    {
        return _data.compare(pos1, n1, s);
    }
    int compare(size_type pos1, size_type n1, const char* s, size_type n2) const
    {
        return _data.compare(pos1, n1, s, n2);
    }

    // [SWS_CORE_03301] Implicit conversion to StringView
    /*
    An operator shall be defined for BasicString that provides implicit
    conversion to StringView: This function shall behave the same as the
    corresponding std::basic_string function from [6, the C++17 standard].
    */
    operator StringView() const noexcept
    {
        return static_cast<std::basic_string_view<char>>(_data);
    }

    // [SWS_CORE_03302] Constructor from StringView
    /*
    A constructor shall be defined for BasicString that accepts a StringView
    argument by value. This function shall behave the same as the corresponding
    std::basic_string function from [6, the C++17 standard].
    */
    explicit BasicString(StringView sv) : _data(sv) {}

    // [SWS_CORE_03303] Constructor from implicit StringView
    /*
    A constructor shall be defined for BasicString that accepts any type that is
    implicitly convertible to StringView. This function shall behave the same as
    the corresponding std::basic_string function from [6, the C++17 standard].
    */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    BasicString(T const& t, size_type pos, size_type n) : _data(t, pos, n)
    {}

    // [SWS_CORE_03304] operator= from StringView
    /*
    An operator= member function shall be defined for BasicString that accepts a
    StringView argument by value. This function shall behave the same as the
    corresponding std::basic_string function from [6, the C++17 standard].
    */
    BasicString& operator=(StringView sv)
    {
        _data = sv;
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
        _data.assign(sv);
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
        _data.assign(t, pos, n);
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
        _data += sv;
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
        _data.append(sv);
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
        _data.append(t, pos, n);
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
        _data.insert(pos, sv);
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
        _data.insert(pos1, t, pos2, n);
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
        _data.replace(pos1, n1, sv);
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
        _data.replace(pos1, n1, t, pos2, n2);
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
        _data.replace(i1, i2, sv);
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
        return _data.find(sv, pos);
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
        return _data.rfind(sv, pos);
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
        return _data.find_first_of(sv, pos);
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
        return _data.find_last_of(sv, pos);
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
        return _data.find_first_not_of(sv, pos);
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
        return _data.find_last_not_of(sv, pos);
    }

    // [SWS_CORE_03321] Comparison with a StringView
    /*
    A member function shall be defined for BasicString that allows comparison
    with the contents of a StringView. This function shall behave the same as
    the corresponding std::basic_string function from [6, the C++17 standard].
    */
    int compare(StringView sv) const noexcept { return _data.compare(sv); }

    // [SWS_CORE_03322] Comparison of subsequence with a StringView
    /*
    A member function shall be defined for BasicString that allows comparison of
    a subsequence of *this with the contents of a StringView. This function
    shall behave the same as the corresponding std::basic_string function from
    [6, the C++17 standard].
    */
    int compare(size_type pos1, size_type n1, StringView sv) const
    {
        return _data.compare(pos1, n1, sv);
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
        return _data.compare(pos1, n1, t, pos2, n2);
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
