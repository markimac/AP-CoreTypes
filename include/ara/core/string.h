/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_STRING_H_
#define ARA_CORE_STRING_H_

#include <initializer_list>  // std::initializer_list
#include <string>            // std::basic_string
#include <utility>           // std::forward, std::move, std::swap

#include "ara/core/allocator.h"
#include "ara/core/string_view.h"

namespace ara::core {

/**
 * @brief Template class implementing string type.
 *
 * @tparam AllocatorT allocator type.
 *
 * @req {SWS_CORE_03000}
 */
template<class AllocatorT = ara::core::Allocator<char>> class BasicString
{
    using string_t =
      std::basic_string<char, std::char_traits<char>, AllocatorT>;
    string_t _data;

 public:
    // types
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

    // TODO: replace STL iterators with their AUTOSAR equivalents
    using iterator               = typename string_t::iterator;
    using const_iterator         = typename string_t::const_iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr size_type npos = string_t::npos;

    // constructors

    /**
     * @brief Constructs an empty string with optionally given allocator.
     */
    explicit BasicString(const AllocatorT& a = AllocatorT()) : _data(a) {}

    /**
     * @brief Copy constructor. Constructs the string with the copy of the
     * contents of another.
     *
     * @param bs another string to be used as the source of the content.
     */
    BasicString(const BasicString& bs) : _data(bs._data) {}

    /**
     * @brief Move constructor. Constructs the string with the contents of
     * another using move semantics.
     *
     * @param bs another string to be used as the source of the content.
     */
    BasicString(BasicString&& bs) noexcept : _data(std::move(bs._data)){};

    /**
     * @brief Constructs using a substring from given string.
     *
     * @param str the original string.
     * @param pos the beginning position of the substring.
     * @param n the ending position of the substring.
     * @param a the allocator.
     */
    BasicString(const BasicString& str,
                size_type          pos,
                size_type          n = npos,
                const AllocatorT&  a = AllocatorT())
      : _data(str._data, pos, n, a)
    {}

    /**
     * @brief Constructs using const char* string.
     *
     * @param s the string.
     * @param n the length of the string.
     * @param a the allocator.
     */
    BasicString(const char* s, size_type n, const AllocatorT& a = AllocatorT())
      : _data(s, n, a)
    {}

    /**
     * @brief Constructs using zero-terminated const char* string.
     *
     * @param s the string.
     * @param a the allocator.
     */
    BasicString(const char* s, const AllocatorT& a = AllocatorT()) : _data(s, a)
    {}

    /**
     * @brief Constructs a string filled with specified character, with
     * specified length.
     *
     * @param n the length of the resulting string.
     * @param c the char to fill the string.
     * @param a the allocator.
     */
    BasicString(size_type n, char c, const AllocatorT& a = AllocatorT())
      : _data(n, c, a)
    {}

    /**
     * @brief Constructs a string using a substring defined by 2 iterators.
     *
     * @param begin the iterator pointing to the begin of the substring.
     * @param end the iterator pointing to the end of the substring.
     * @param a the allocator.
     */
    template<class InputIterator>
    BasicString(InputIterator     begin,
                InputIterator     end,
                const AllocatorT& a = AllocatorT())
      : _data(begin, end, a)
    {}

    /**
     * @brief Constructs the string using provided initialization list.
     *
     * @param i the initialization list.
     * @param a the allocator.
     */
    BasicString(std::initializer_list<char> i,
                const AllocatorT&           a = AllocatorT())
      : _data(i, a)
    {}

    /**
     * @brief Copy constructs a string with explicit allocator.
     *
     * @param bs a string to copy.
     * @param a the allocator.
     */
    BasicString(const BasicString& bs, const AllocatorT& a) : _data(bs._data, a)
    {}

    /**
     * @brief Move constructs a string with explicit allocator.
     *
     * @param bs a string to move.
     * @param a the allocator.
     */
    BasicString(BasicString&& bs, const AllocatorT& a)
      : _data(std::move(bs._data), a)
    {}

    /**
     * @brief Constructs a string using a StringView object as source of the
     * data.
     *
     * @param sv the StringView object used as source of the data.
     *
     * @req {SWS_CORE_03302}
     */
    explicit BasicString(StringView sv) : _data(sv.data(), sv.length()) {}

    /**
     * @brief Constructs a string using substring from an object, that is
     * implicitly convertible to StringView.
     *
     * @param t the object being the source of a data.
     * @param pos position of first character of the substring.
     * @param n the length of the substring.
     *
     * @req {SWS_CORE_03303}
     */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    BasicString(T const& t, size_type pos, size_type n)
      : _data(static_cast<StringView>(t).substr(pos, n).data(),
              static_cast<StringView>(t).substr(pos, n).length())
    {}

    ~BasicString() = default;

    // assignment operator=

    /**
     * @brief Copy assignment operator.
     *
     * @param str another string to use as data source.
     *
     * @return reference to string instance.
     */
    BasicString& operator=(const BasicString& str)
    {
        _data = str._data;

        return *this;
    }

    /**
     * @brief Move assignment operator.
     *
     * @param str another string to use as data source.
     *
     * @return reference to string instance.
     */
    BasicString& operator=(BasicString&& str) noexcept
    {
        _data = std::move(str._data);

        return *this;
    }

    /**
     * @brief Assignment operator from null-terminated const char* string.
     *
     * @param other zero-terminated const char* string to use as data source.
     *
     * @return reference to string instance.
     */
    BasicString& operator=(const char* s)
    {
        _data = s;

        return *this;
    }

    /**
     * @brief Assigns a single char.
     *
     * @param c a character to be assigned as content of the string.
     *
     * @return reference to string instance.
     */
    BasicString& operator=(char c)
    {
        _data = c;

        return *this;
    }

    /**
     * @brief Assigns an initializing list.
     *
     * @param i an initialization list to use as data source.
     *
     * @return reference to string instance.
     */
    BasicString& operator=(std::initializer_list<char> i)
    {
        _data = i;

        return *this;
    }

    /**
     * @brief Replaces the string with contents of the StringView.
     *
     * @param sv the StringView used as source of a data.
     *
     * @return the instance of the string.
     *
     * @req {SWS_CORE_03304}
     */
    BasicString& operator=(StringView sv)
    {
        _data.assign(sv.data(), sv.length());

        return *this;
    }

    // iterator methods

    /**
     * @brief Gets iterator pointing at begin of the string.
     *
     * @return iterator to the first character.
     */
    iterator begin() noexcept { return _data.begin(); }

    /**
     * @brief Gets constant iterator pointing at begin of the constant string.
     *
     * @return constant iterator to the first character.
     */
    const_iterator begin() const noexcept { return _data.begin(); }

    /**
     * @brief Gets iterator pointing at end of the string.
     *
     * @return iterator pointing to next position after the last character of
     * string.
     */
    iterator end() noexcept { return _data.end(); }

    /**
     * @brief Gets constant iterator pointing at end of the constant string.
     *
     * @return constant iterator pointing to next position after the last
     * character of string.
     */
    const_iterator end() const noexcept { return _data.end(); }

    /**
     * @brief Gets reverse iterator pointing at reversed begin of the string.
     *
     * @return reverse iterator pointing to the last character of the string.
     */
    reverse_iterator rbegin() noexcept { return _data.rbegin(); }

    /**
     * @brief Gets constant reverse iterator pointing at reversed begin of the
     * constant string.
     *
     * @return constant reverse iterator pointing to the last character of the
     * string.
     */
    const_reverse_iterator rbegin() const noexcept { return _data.rbegin(); }

    /**
     * @brief Gets reverse iterator pointing at reversed end of the string.
     *
     * @return reverse iterator pointing to the position before the first
     * character of the string.
     */
    reverse_iterator rend() noexcept { return _data.rend(); }

    /**
     * @brief Gets constant reverse iterator pointing at reversed end of the
     * constant string.
     *
     * @return constant reverse iterator pointing to the position before the
     * first character of the string.
     */
    const_reverse_iterator rend() const noexcept { return _data.rend(); }

    /**
     * @brief Gets constant iterator pointing at begin of the constant string.
     *
     * @return constant iterator to the first character.
     */
    const_iterator cbegin() const noexcept { return _data.cbegin(); }

    /**
     * @brief Gets constant iterator pointing at end of the constant string.
     *
     * @return constant iterator pointing to next position after the last
     * character of string.
     */
    const_iterator cend() const noexcept { return _data.cend(); }

    /**
     * @brief Gets constant reverse iterator pointing at begin of the constant
     * string.
     *
     * @return constant reverse iterator pointing to the last character of the
     * string.
     */
    const_reverse_iterator crbegin() const noexcept { return _data.crbegin(); }

    /**
     * @brief Gets constant reverse iterator pointing at end of the constant
     * string.
     *
     * @return constant reverse iterator pointing to the position before the
     * first character of the string.
     */
    const_reverse_iterator crend() const noexcept { return _data.crend(); }

    // capacity methods

    /**
     * @brief Gets length of the string.
     *
     * @return length of the string
     */
    size_type size() const noexcept { return _data.size(); }

    /**
     * @brief Gets length of the string.
     *
     * @return length of the string
     */
    size_type length() const noexcept { return _data.length(); }

    /**
     * @brief Gets maximal length of the string.
     *
     * @return maximal length of the string.
     */
    size_type max_size() const noexcept { return _data.max_size(); }

    /**
     * @brief Changes the length of the string: if new size is shorter, then the
     * string is cropped, if longer then the string is padded by given character.
     *
     * @param n the new size.
     * @param c the character used as padding.
     */
    void resize(size_type n, char c) { _data.resize(n, c); }

    /**
     * @brief Changes the length of the string: if new size is shorter, then the
     * string is cropped, otherwise the string is extended.
     *
     * @param n the new size.
     */
    void resize(size_type n) { _data.resize(n); }

    /**
     * @brief Gets size of the memory allocated by the string.
     *
     * @return size of allocated memory.
     */
    size_type capacity() const noexcept { return _data.capacity(); }

    /**
     * @brief Reserves a buffer of a given size.
     */
    void reserve(size_type res_arg = 0) { _data.reserve(res_arg); }

    /**
     * @brief Performs reallocation of memory to exactly match capacity and
     * length of the string.
     */
    void shrink_to_fit() { _data.shrink_to_fit(); }

    /**
     * @brief Empties the string.
     */
    void clear() noexcept { _data.clear(); }

    /**
     * @brief Returns if the string is empty.
     *
     * @return true if the string is empty.
     */
    bool empty() const noexcept { return _data.empty(); }

    // element access methods

    /**
     * @brief Access specified element.
     *
     * @param pos position of the element to return.
     *
     * @return constant reference to the element.
     */
    const_reference operator[](size_type pos) const noexcept
    {
        return _data[pos];
    }

    /**
     * @brief Access specified element.
     *
     * @param pos position of the element to return.
     *
     * @return reference to the element.
     */
    reference operator[](size_type pos) noexcept { return _data[pos]; }

    /**
     * @brief Access specified element with bounds checking.
     *
     * @param pos position of the element to return.
     *
     * @return reference to the element.
     */
    const_reference at(size_type n) const { return _data.at(n); }

    /**
     * @brief Access specified element with bounds checking.
     *
     * @param pos position of the element to return.
     *
     * @return reference to the element.
     */
    reference at(size_type n) { return _data.at(n); }

    /**
     * @brief Access first element.
     *
     * @return constant reference to the first character.
     */
    const char& front() const noexcept { return _data.front(); }

    /**
     * @brief Access first element.
     *
     * @return reference to the first character.
     */
    char& front() noexcept { return _data.front(); }

    /**
     * @brief Access last element.
     *
     * @return constant reference to the last character.
     */
    const char& back() const noexcept { return _data.back(); }

    /**
     * @brief Access last element.
     *
     * @return reference to the last character.
     */
    char& back() noexcept { return _data.back(); }

    // modifier methods

    /**
     * @brief Appends the string with given string as source of data.
     *
     * @param str the appending string.
     *
     * @return the instance of appended string.
     */
    BasicString& operator+=(const BasicString& str)
    {
        _data += str._data;

        return *this;
    }

    /**
     * @brief Appends the string with given null-terminated const char* string
     * as source of data.
     *
     * @param str the appending string.
     *
     * @return the instance of appended string.
     */
    BasicString& operator+=(const char* s)
    {
        _data += s;

        return *this;
    }

    /**
     * @brief Appends the string with given character.
     *
     * @param str the appending string.
     *
     * @return the instance of appended string.
     */
    BasicString& operator+=(char c)
    {
        _data += c;

        return *this;
    }

    /**
     * @brief Appends the string with initialization list as source of data.
     *
     * @param str the appending string.
     *
     * @return the instance of appended string.
     */
    BasicString& operator+=(std::initializer_list<char> i)
    {
        _data += i;

        return *this;
    }

    /**
     * @brief Appends the string with given StringView as data source.
     *
     * @param sv the StringView instance used as data source.
     *
     * @return the instance of string.
     *
     * @req {SWS_CORE_03307}
     */
    BasicString& operator+=(StringView sv)
    {
        _data.append(sv.data(), sv.length());

        return *this;
    }

    /**
     * @brief Appends the string with given string as source of data.
     *
     * @param str the appending string.
     *
     * @return the instance of appended string.
     */
    BasicString& append(const BasicString& str)
    {
        _data.append(str._data);

        return *this;
    }

    /**
     * @brief Appends the string with the substring as source of data.
     *
     * @param str the string being the source of a data.
     * @param pos position of the begin of the substring.
     * @param n the length of the substring.
     *
     * @return the instance of appended string.
     */
    BasicString& append(const BasicString& str, size_type pos, size_type n)
    {
        _data.append(str._data, pos, n);

        return *this;
    }

    /**
     * @brief Appends the string with a const char* string as source of data.
     *
     * @param str the appending string.
     * @param n length of the str string.
     *
     * @return the instance of appended string.
     */
    BasicString& append(const char* s, size_type n)
    {
        _data.append(s, n);

        return *this;
    }

    /**
     * @brief Appends the string with a null-terminated const char* as source of
     * data.
     *
     * @param str the appending null-terminated const char* string.
     *
     * @return the instance of appended string.
     */
    BasicString& append(const char* s)
    {
        _data.append(s);

        return *this;
    }

    /**
     * @brief Appends the given with repetitions of a specified character.
     *
     * @param n the amount of repetition.
     * @param c the repeated character.
     *
     * @return the instance of appended string.
     */
    BasicString& append(size_type n, char c)
    {
        _data.append(n, c);

        return *this;
    }

    /**
     * @brief Appends content of the string with a substring.
     *
     * @param first the iterator pointing to the first character of the
     * substring.
     * @param last the iterator pointing to the last character of the substring.
     *
     * @return the instance of the string.
     */
    template<typename InputIterator> BasicString&
    append(InputIterator first, InputIterator last)
    {
        _data.append(first, last);

        return *this;
    }

    /**
     * @brief Appends content of the string with a substring.
     *
     * @param i the initializer_list being the source of data.
     *
     * @return the instance of the string.
     */
    BasicString& append(std::initializer_list<char> i)
    {
        _data.append(i);

        return *this;
    }

    /**
     * @brief Appends the string with given StringView as data source.
     *
     * @param sv the StringView instance used as data source.
     *
     * @return the instance of string.
     *
     * @req {SWS_CORE_03308}
     */
    BasicString& append(StringView sv)
    {
        _data.append(sv.data(), sv.length());

        return *this;
    }

    /**
     * @brief Appends the string with object convertible to StringView as data
     * source.
     *
     * @param t the instance of object convertible to StringView used as data
     * source.
     * @param pos the begining of the substring to be appended.
     * @param n the length of the substring.
     *
     * @return the instance of string.
     *
     * @req {SWS_CORE_03309}
     */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    BasicString& append(T const& t, size_type pos, size_type n = npos)
    {
        return append(static_cast<StringView>(t).substr(pos, n));
    }

    /**
     * @brief Appends the given character to the end of the string.
     *
     * @param c the character to append.
     */
    void push_back(char c) { _data.push_back(c); }

    /**
     * @brief Replaces content of the string with the given string.
     *
     * @param str the string being the source of data.
     *
     * @return the instance of the string.
     */
    BasicString& assign(const BasicString& str)
    {
        _data.assign(str._data);

        return *this;
    }

    /**
     * @brief Replaces content of the string with the given string.
     *
     * @param str the string being the source of data.
     *
     * @return the instance of the string.
     */
    BasicString& assign(BasicString&& str) noexcept
    {
        _data.assign(std::move(str._data));

        return *this;
    }

    /**
     * @brief Replaces content of the string with the given substring.
     *
     * @param str the string being the source of data.
     * @param pos the position of the first character of the substring.
     * @param n the length of the substring.
     *
     * @return the instance of the string.
     */
    BasicString& assign(const BasicString& str, size_type pos, size_type n)
    {
        _data.assign(str._data, pos, n);

        return *this;
    }

    /**
     * @brief Replaces content of the string with the specified.
     *
     * @param s the null-terminated const char string.
     * @param n the length of the string.
     *
     * @return the instance of the string.
     */
    BasicString& assign(const char* s, size_type n)
    {
        _data.assign(s, n);

        return *this;
    }

    /**
     * @brief Replaces content of the string with the given.
     *
     * @param s the string being the source of a data.
     *
     * @return the instance of the string.
     */
    BasicString& assign(const char* s)
    {
        _data.assign(s);

        return *this;
    }

    /**
     * @brief Replaces content of the string with a substring.
     *
     * @param first the iterator pointing to the first character of the
     * substring.
     * @param last the iterator pointing to the last character of the substring.
     *
     * @return the instance of the string.
     */
    template<class InputIterator> BasicString&
    assign(InputIterator first, InputIterator last)
    {
        _data.assign(first, last);

        return *this;
    }

    /**
     * @brief Replaces content of the string with a substring.
     *
     * @param i the initializer_list being the source of data.
     *
     * @return the instance of the string.
     */
    BasicString& assign(std::initializer_list<char> i)
    {
        _data.assign(i);

        return *this;
    }

    /**
     * @brief Replaces the string with contents of the StringView.
     *
     * @param sv the StringView used as source of a data.
     *
     * @return the instance of the string.
     *
     * @req {SWS_CORE_03305}
     */
    BasicString& assign(StringView sv)
    {
        _data.assign(sv.data(), sv.length());

        return *this;
    }

    /**
     * @brief Replaces the string using substring from an object, that is
     * implicitly convertible to StringView.
     *
     * @param t the object being the source of a data.
     * @param pos position of first character of the substring.
     * @param n the length of the substring.
     *
     * @return the instance of the string.
     *
     * @req {SWS_CORE_03306}
     */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    BasicString& assign(T const& t, size_type pos, size_type n = npos)
    {
        return assign(static_cast<StringView>(t).substr(pos, n));
    }

    /**
     * @brief Inserts a given string in the specified place.
     *
     * @param str the string being the source of the data.
     * @param pos1 the position where to insert a string.
     *
     * @return the instance of string.
     */
    BasicString& insert(size_type pos1, const BasicString& str)
    {
        _data.insert(pos1, str._data);

        return *this;
    }

    /**
     * @brief Inserts a given substring in the specified place.
     *
     * @param pos1 the position where to insert a substring.
     * @param str the string being the source of the data.
     * @param pos2 the position of the first character of the inserted substring.
     * @param n the lenght of the inserted substring.
     *
     * @return the instance of string.
     */
    BasicString&
    insert(size_type pos1, const BasicString& str, size_type pos2, size_type n)
    {
        _data.insert(pos1, str._data, pos2, n);

        return *this;
    }

    /**
     * @brief Inserts a given substring in the specified place.
     *
     * @param pos the position where to insert a substring.
     * @param str the null-terminated const char string being the source of the
     * data.
     * @param n the lenght of the inserted substring.
     *
     * @return the instance of string.
     */
    BasicString& insert(size_type pos, const char* str, size_type n)
    {
        _data.insert(pos, str, n);

        return *this;
    }

    /**
     * @brief Inserts a given string in the specified place.
     *
     * @param pos the position where to insert a substring.
     * @param str the null-terminated const char string being the source of the
     * data.
     *
     * @return the instance of string.
     */
    BasicString& insert(size_type pos, const char* str)
    {
        _data.insert(pos, str);

        return *this;
    }

    /**
     * @brief Inserts a given character in the specified place.
     *
     * @param pos the position where to insert the characters.
     * @param n the number of repetition of the character.
     * @param c the character to insert.
     *
     * @return the instance of string.
     */
    BasicString& insert(size_type pos, size_type n, char c)
    {
        _data.insert(pos, n, c);

        return *this;
    }

    /**
     * @brief Inserts a given character in the specified place.
     *
     * @param p the iterator pointing to the place where to insert the character.
     * @param c the character to insert.
     *
     * @return the instance of string.
     */
    iterator insert(const_iterator p, char c) { return _data.insert(p, c); }

    /**
     * @brief Inserts a given character in the specified place.
     *
     * @param p the iterator pointing to the place where to insert the character.
     * @param n the number of character repetition.
     * @param c the character to insert.
     *
     * @return the instance of string.
     */
    iterator insert(const_iterator p, size_type n, char c)
    {
        return _data.insert(p, n, c);
    }

    /**
     * @brief Inserts a given string in the specified place.
     *
     * @param p the iterator pointing to the place where to insert the character.
     * @param first the iterator pointing to the first character of the inserted
     * string.
     * @param last the iterator pointing to the end of the inserted string.
     *
     * @return the instance of string.
     */
    template<class InputIterator> iterator
    insert(const_iterator p, InputIterator first, InputIterator last)
    {
        return _data.insert(p, first, last);
    }

    /**
     * @brief Inserts a given string in the specified place.
     *
     * @param p the iterator pointing to the place where to insert the character.
     * @param i the initializer_list serving as the source of data to insert.
     *
     * @return the instance of string.
     */
    iterator insert(const_iterator p, std::initializer_list<char> i)
    {
        return _data.insert(p, i);
    }

    /**
     * @brief Inserts the substring at specified place using the StringView as
     * data source.
     *
     * @param pos the position where to insert a StringView.
     * @param sv the StringView used as data source.
     *
     * @returns the instance of string.
     *
     * @req {SWS_CORE_03310}
     */
    BasicString& insert(size_type pos, StringView sv)
    {
        _data.insert(pos, sv.data(), sv.length());

        return *this;
    }

    /**
     * @brief Inserts at specified place a substring from an object convertible
     * to StringView as data source.
     *
     * @param pos1 the positon where to insert a StringView.
     * @param t the instance of object convertible to StringView used as data
     * source.
     * @param pos2 the begin of the substring to be inserted.
     * @param n the end of the substring to be inserted.
     *
     * @return the instance of string.
     *
     * @req {SWS_CORE_03311}
     */
    template<typename T,
             typename = typename std::
               enable_if<std::is_convertible<T, StringView>::value, void>::type>
    BasicString&
    insert(size_type pos1, T const& t, size_type pos2, size_type n = npos)
    {
        return insert(pos1, static_cast<StringView>(t).substr(pos2, n));
    }

    /**
     * @brief Removes part of the string.
     *
     * @param pos the first character of a removed substring.
     * @param n the length of the removed substring.
     *
     * @return the instance of string.
     */
    BasicString& erase(size_type pos = 0, size_type n = npos)
    {
        _data.erase(pos, n);

        return *this;
    }

    /**
     * @brief Removes part of the string.
     *
     * @param p the iterator pointing to the first character of a removed
     * substring.
     *
     * @return the instance of string.
     */
    BasicString& erase(const_iterator p)
    {
        _data.erase(p);

        return *this;
    }

    /**
     * @brief Removes part of the string.
     *
     * @param first the iterator pointing to the first character of a removed
     * substring.
     * @param last the iterator pointing to the first character of a removed
     * substring.
     *
     * @return the instance of string.
     */
    BasicString& erase(const_iterator first, const_iterator last)
    {
        _data.erase(first, last);

        return *this;
    }

    /**
     * @brief Removes the last character from the string.
     */
    void pop_back() noexcept { _data.pop_back(); }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param pos1 the position of the first character of the replaced substring.
     * @param n1 the length of the replaced substring.
     * @param str the replacement string.
     *
     * @return the instance of string.
     */
    BasicString& replace(size_type pos1, size_type n1, const BasicString& str)
    {
        _data.replace(pos1, n1, str._data);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param pos1 the position of the first character of the replaced substring.
     * @param n1 the length of the replaced substring.
     * @param str the replacement string.
     * @param pos2 the position of the first character of the replacement
     * substring.
     * @param n2 the length of the replacement substring.
     *
     * @return the instance of string.
     */
    BasicString& replace(size_type          pos1,
                         size_type          n1,
                         const BasicString& str,
                         size_type          pos2,
                         size_type          n2)
    {
        _data.replace(pos1, n1, str._data, pos2, n2);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param pos the position of the first character of the replaced substring.
     * @param n1 the length of the replaced substring.
     * @param s the replacement string.
     * @param n2 the length of the replacement string.
     *
     * @return the instance of string.
     */
    BasicString&
    replace(size_type pos, size_type n1, const char* s, size_type n2)
    {
        _data.replace(pos, n1, s, n2);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param pos the position of the first character of the replaced substring.
     * @param n1 the length of the replaced substring.
     * @param s the replacement string.
     *
     * @return the instance of string.
     */
    BasicString& replace(size_type pos, size_type n1, const char* s)
    {
        _data.replace(pos, n1, s);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param pos the position of the first character of the replaced
     * substring.
     * @param n1 the length of the replaced substring.
     * @param n2 the number of the repetitions.
     * @param c the replacement character.
     *
     * @return the instance of string.
     */
    BasicString& replace(size_type pos, size_type n1, size_type n2, char c)
    {
        _data.replace(pos, n1, n2, c);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param i1 the iterator pointing to the first character of the replaced
     * substring.
     * @param i2 the iterator pointing to the end of the replaced substring.
     * @param str the replacement string.
     *
     * @return the instance of string.
     */
    BasicString&
    replace(const_iterator i1, const_iterator i2, const BasicString& str)
    {
        _data.replace(i1, i2, str._data);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param i1 the iterator pointing to the first character of the replaced
     * part of a string.
     * @param i2 the iterator pointing to the end of the replaced part of a
     * string.
     * @param s the replacement string.
     * @param n the length of the replacement string.
     *
     * @return the instance of string.
     */
    BasicString&
    replace(const_iterator i1, const_iterator i2, const char* s, size_type n)
    {
        _data.replace(i1, i2, s, n);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param i1 the iterator pointing to the first character of the replaced
     * part of a string.
     * @param i2 the iterator pointing to the end of the replaced part of a
     * string.
     * @param s the replacement string.
     *
     * @return the instance of string.
     */
    BasicString& replace(const_iterator i1, const_iterator i2, const char* s)
    {
        _data.replace(i1, i2, s);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a repeated character.
     *
     * @param i1 the iterator pointing to the first character of the replaced
     * part of a string.
     * @param i2 the iterator pointing to the end of the replaced part of a
     * string.
     * @param n the number of repetitions.
     * @param c the replacement character.
     *
     * @return the instance of string.
     */
    BasicString&
    replace(const_iterator i1, const_iterator i2, size_type n, char c)
    {
        _data.replace(i1, i2, n, c);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param i1 the iterator pointing to the first character of the replaced
     * part of a string.
     * @param i2 the iterator pointing to the end of the replaced part of a
     * string.
     * @param j1 the iterator pointing to the first character of the replacement
     * string.
     * @param j2 the iterator pointing to the end of the replacement string.
     *
     * @return the instance of string.
     */
    template<class InputIterator> BasicString& replace(const_iterator i1,
                                                       const_iterator i2,
                                                       InputIterator  j1,
                                                       InputIterator  j2)
    {
        _data.replace(i1, i2, j1, j2);

        return *this;
    }

    /**
     * @brief Replaces part of the string with a specified one.
     *
     * @param i1 the iterator pointing at the first character of the replaced
     * part.
     * @param i2 the iterator pointing at the end of the replaced part.
     * @param i the initializer_list used as a source of the data.
     *
     * @return the instance of string.
     */
    BasicString&
    replace(const_iterator i1, const_iterator i2, std::initializer_list<char> i)
    {
        _data.replace(i1, i2, i);

        return *this;
    }

    /**
     * @brief Replaces a substring with the StringView as data source.
     *
     * @param pos1 start of the substring that is going to be replaced.
     * @param n length of the substring that is going to be replaced.
     * @param sv the StringView used as data source.
     *
     * @return the instance of string.
     *
     * @req {SWS_CORE_03312}
     */
    BasicString& replace(size_type pos1, size_type n1, StringView sv)
    {
        _data.replace(pos1, n1, sv.data(), sv.length());

        return *this;
    }

    /**
     * @brief Replaces at specified place a substring from an object convertible
     * to StringView as data source.
     *
     * @param pos1 the begin of the replaced substring.
     * @param n1 the length of the replaced substring.
     * @param t the instance of object convertible to StringView used as data
     * source.
     * @param pos2 the begin of the substring to be inserted.
     * @param n2 the length of the substring to be inserted.
     *
     * @return the instance of string.
     *
     * @req {SWS_CORE_03313}
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
        return replace(pos1, n1, static_cast<StringView>(t).substr(pos2, n2));
    }

    /**
     * @brief Replaces a substring using StringView instance as data source.
     *
     * @param i1 the iterator pointing to the begin of the substring.
     * @param i2 the iterator pointing to the end of the substring.
     * @param sv the StringView used as data source.
     *
     * @return the instance of string.
     *
     * @req {SWS_CORE_03314}
     */
    BasicString& replace(const_iterator i1, const_iterator i2, StringView sv)
    {
        _data.replace(i1, i2, sv.data(), sv.length());

        return *this;
    }

    /**
     * @brief Copies a substring into specified buffer.
     *
     * @param s the buffer.
     * @param n the substring length.
     * @param pos the position of the substring's first character.
     *
     * @return number of  characters copied.
     */
    size_type copy(char* s, size_type n, size_type pos = 0) const
    {
        return _data.copy(s, n, pos);
    }

    /**
     * @brief Exchanges string's contents with the specified one.
     *
     * @param str the string to swap.
     */
    void swap(BasicString& str) noexcept { _data.swap(str._data); }

    // string operations methods

    /**
     * @brief Returns a pointer to a null-terminated const char array with data
     * equivalent to those in the string.
     *
     * @return the pointer to the underlying character storage.
     */
    const char* c_str() const noexcept { return _data.c_str(); }

    /**
     * @brief Returns a pointer to the underlying character storage array.
     *
     * @return the pointer to the character storing array.
     */
    const char* data() const noexcept { return _data.data(); }

    /**
     * @brief Returns the allocator associated with the string.
     *
     * @return The associated allocator.
     */
    allocator_type get_allocator() const noexcept
    {
        return _data.get_allocator();
    }

    /**
     * @brief Finds the first substring equal to the given character sequence.
     *
     * @param str the string to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the first character of the substring being looked
     * for or BasicString::npos if not found.
     */
    size_type find(const BasicString& str, size_type pos = 0) const noexcept
    {
        return _data.find(str._data, pos);
    }

    /**
     * @brief Finds the first substring equal to the given character sequence.
     *
     * @param str the string to search for.
     * @param pos the position at which to start the search.
     * @param n the length of the string.
     *
     * @return a position of the first character of the substring being looked
     * for or BasicString::npos if not found.
     */
    size_type find(const char* s, size_type pos, size_type n) const noexcept
    {
        return _data.find(s, pos, n);
    }

    /**
     * @brief Finds the first substring equal to the given character sequence.
     *
     * @param str the null-terminated const char string to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the first character of the substring being looked
     * for or BasicString::npos if not found.
     */
    size_type find(const char* s, size_type pos = 0) const noexcept
    {
        return _data.find(s, pos);
    }

    /**
     * @brief Finds the first substring equal to the given character sequence.
     *
     * @param c the character to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the first character of the substring being looked
     * for or BasicString::npos if not found.
     */
    size_type find(char c, size_type pos = 0) const noexcept
    {
        return _data.find(c, pos);
    }

    /**
     * @brief Finds the first occurence of StringView in string.
     *
     * @param sv the StringView instance used as a substring being looked for.
     * @param pos the assumed begin of the string.
     *
     * @return the position of the first character of the found substring or
     * BasicString::npos if no such substring is found.
     *
     * @req {SWS_CORE_03315}
     */
    size_type find(StringView sv, size_type pos = 0) const noexcept
    {
        return static_cast<StringView>(_data).find(sv, pos);
    }

    /**
     * @brief Finds the last substring equal to the given character sequence.
     *
     * @param str the string to search for.
     * @param pos the position at which to end the search.
     *
     * @return a position of the first character of the substring being looked
     * for or BasicString::npos if not found.
     */
    size_type rfind(const BasicString& str, size_type pos = npos) const noexcept
    {
        return _data.rfind(str._data, pos);
    }

    /**
     * @brief Finds the last substring equal to the given character sequence.
     *
     * @param str the string to search for.
     * @param pos the position at which to start the search.
     * @param n the length of the string.
     *
     * @return a position of the first character of the substring being looked
     * for or BasicString::npos if not found.
     */
    size_type rfind(const char* s, size_type pos, size_type n) const noexcept
    {
        return _data.rfind(s, pos, n);
    }

    /**
     * @brief Finds the last substring equal to the given character sequence.
     *
     * @param str the null-terminated const char string to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the first character of the substring being looked
     * for or BasicString::npos if not found.
     */
    size_type rfind(const char* s, size_type pos = npos) const noexcept
    {
        return _data.rfind(s, pos);
    }

    /**
     * @brief Finds the last substring equal to the given character sequence.
     *
     * @param c the character to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the first character of the substring being looked
     * for or BasicString::npos if not found.
     */
    size_type rfind(char c, size_type pos = npos) const noexcept
    {
        return _data.rfind(c, pos);
    }

    /**
     * @brief Finds the last occurence of StringView in string.
     *
     * @param sv the StringView instance used as a substring being looked for.
     * @param pos the assumed end of the string.
     *
     * @return the position of the first character of the found substring or
     * BasicString::npos if no such substring is found.
     *
     * @req {SWS_CORE_03316}
     */
    size_type rfind(StringView sv, size_type pos = npos) const noexcept
    {
        return static_cast<StringView>(_data).rfind(sv, pos);
    }

    /**
     * @brief Finds the first character equal to one of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type
    find_first_of(const BasicString& str, size_type pos = 0) const noexcept
    {
        return _data.find_first_of(str._data, pos);
    }

    /**
     * @brief Finds the first character equal to one of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     * @param n the length of the string.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type
    find_first_of(const char* s, size_type pos, size_type n) const noexcept
    {
        return _data.find_first_of(s, pos, n);
    }

    /**
     * @brief Finds the first character equal to one of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type find_first_of(const char* s, size_type pos = 0) const noexcept
    {
        return _data.find_first_of(s, pos);
    }

    /**
     * @brief Finds the first character equal to one of the characters in given
     * character sequence.
     *
     * @param c the character to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type find_first_of(char c, size_type pos = 0) const noexcept
    {
        return _data.find_first_of(c, pos);
    }

    /**
     * @brief Finds the first character equal to one of the characters occurring
     * in the specified string.
     *
     * @param sv the StringView instance used as source of data.
     * @param pos the assumed begin of the string.
     *
     * @return the position of the found character or BasicString::npos if no
     * such character is found.
     *
     * @req {SWS_CORE_03317}
     */
    size_type find_first_of(StringView sv, size_type pos = 0) const noexcept
    {
        return static_cast<StringView>(_data).find_first_of(sv, pos);
    }

    /**
     * @brief Finds the last character equal to one of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type
    find_last_of(const BasicString& str, size_type pos = npos) const noexcept
    {
        return _data.find_last_of(str._data, pos);
    }

    /**
     * @brief Finds the last character equal to one of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     * @param n the length of the string.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type
    find_last_of(const char* s, size_type pos, size_type n) const noexcept
    {
        return _data.find_last_of(s, pos, n);
    }

    /**
     * @brief Finds the last character equal to one of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type find_last_of(const char* s, size_type pos = npos) const noexcept
    {
        return _data.find_last_of(s, pos);
    }

    /**
     * @brief Finds the last character equal to one of the characters in given
     * character sequence.
     *
     * @param c the character to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type find_last_of(char c, size_type pos = npos) const noexcept
    {
        return _data.find_last_of(c, pos);
    }

    /**
     * @brief Finds the last character equal to one of the characters occurring
     * in the specified string.
     *
     * @param sv the StringView instance used as source of data.
     * @param pos the assumed end of the string.
     *
     * @return the position of the found character or BasicString::npos if no
     * such character is found.
     *
     * @req {SWS_CORE_03318}
     */
    size_type find_last_of(StringView sv, size_type pos = npos) const noexcept
    {
        return static_cast<StringView>(_data).find_last_of(sv, pos);
    }

    /**
     * @brief Finds the first character equal to none of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type
    find_first_not_of(const BasicString& str, size_type pos = 0) const noexcept
    {
        return _data.find_first_not_of(str._data, pos);
    }

    /**
     * @brief Finds the first character equal to none of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     * @param n the length of the string.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type
    find_first_not_of(const char* s, size_type pos, size_type n) const noexcept
    {
        return _data.find_first_not_of(s, pos, n);
    }

    /**
     * @brief Finds the first character equal to none of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type find_first_not_of(const char* s, size_type pos = 0) const noexcept
    {
        return _data.find_first_not_of(s, pos);
    }

    /**
     * @brief Finds the first character equal to none of the characters in given
     * character sequence.
     *
     * @param c the character to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type find_first_not_of(char c, size_type pos = 0) const noexcept
    {
        return _data.find_first_not_of(c, pos);
    }

    /**
     * @brief Finds the first character not equal to any of the characters
     * occurring in the specified string.
     *
     * @param sv the StringView instance used as source of data.
     * @param pos the assumed begin of the string.
     *
     * @return the position of the found character or BasicString::npos if no
     * such character is found.
     *
     * @req {SWS_CORE_03319}
     */
    size_type find_first_not_of(StringView sv, size_type pos = 0) const noexcept
    {
        return static_cast<StringView>(_data).find_first_not_of(sv, pos);
    }

    /**
     * @brief Finds the last character equal to none of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type find_last_not_of(const BasicString& str,
                               size_type          pos = npos) const noexcept
    {
        return _data.find_last_not_of(str._data, pos);
    }

    /**
     * @brief Finds the last character equal to none of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     * @param n the length of the string.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type
    find_last_not_of(const char* s, size_type pos, size_type n) const noexcept
    {
        return _data.find_last_not_of(s, pos, n);
    }

    /**
     * @brief Finds the last character equal to none of the characters in given
     * character sequence.
     *
     * @param str a string containing characters to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type
    find_last_not_of(const char* s, size_type pos = npos) const noexcept
    {
        return _data.find_last_not_of(s, pos);
    }

    /**
     * @brief Finds the last character equal to none of the characters in given
     * character sequence.
     *
     * @param c the character to search for.
     * @param pos the position at which to start the search.
     *
     * @return a position of the found character or BasicString::npos if not
     * found.
     */
    size_type find_last_not_of(char c, size_type pos = npos) const noexcept
    {
        return _data.find_last_not_of(c, pos);
    }

    /**
     * @brief Finds the last character not equal to any of the characters
     * occurring in the specified string.
     *
     * @param sv the StringView instance used as source of data.
     * @param pos the assumed begin of the string.
     *
     * @return the position of the found character or BasicString::npos if no
     * such character is found.
     *
     * @req {SWS_CORE_03320}
     */
    size_type
    find_last_not_of(StringView sv, size_type pos = npos) const noexcept
    {
        return static_cast<StringView>(_data).find_last_not_of(sv, pos);
    }

    /**
     * @brief Creates a substring from the string.
     *
     * @param pos the position of the first substring's character.
     * @param n the length of the substring.
     *
     * @return an instance of the substring.
     */
    BasicString substr(size_type pos = 0, size_type n = npos) const
    {
        BasicString retval(_data.get_allocator());
        retval._data = std::move(_data.substr(pos, n));

        return retval;
    }

    /**
     * @brief Lexicographically compares the content of the string with the
     * specified one.
     *
     * @param str the string instance being compared with.
     *
     * @return negative value if the BasicString's value appears before the
     * character sequence in the specified string, zero when identical,
     * positive value if the BasicString's value appears after the character
     * sequence in the string.
     */
    int compare(const BasicString& str) const noexcept
    {
        return _data.compare(str._data);
    }

    /**
     * @brief Lexicographically compares the content of the string with the
     * specified substring.
     *
     * @param pos1 the position of the first character of the substring.
     * @param n1 the length of the substring.
     * @param str the string instance being compared with.
     *
     * @return negative value if the BasicString's value appears before the
     * character sequence in the specified substring, zero when identical,
     * positive value if the BasicString's value appears after the character
     * sequence in the substring.
     */
    int compare(size_type pos1, size_type n1, const BasicString& str) const
    {
        return _data.compare(pos1, n1, str._data);
    }

    /**
     * @brief Lexicographically compares the content of the string with the
     * specified substring.
     *
     * @param pos1 the position of the first character of the substring.
     * @param n1 the length of the substring.
     * @param str the string instance being compared with.
     *
     * @return negative value if the BasicString's value appears before the
     * character sequence in the specified substring, zero when identical,
     * positive value if the BasicString's value appears after the character
     * sequence in the substring.
     */
    int compare(size_type          pos1,
                size_type          n1,
                const BasicString& str,
                size_type          pos2,
                size_type          n2) const
    {
        return _data.compare(pos1, n1, str._data, pos2, n2);
    }

    /**
     * @brief Lexicographically compares the content of the string with the
     * specified null-terminated const char* string.
     *
     * @param s the null-terminated const char* string instance being compared
     * with.
     *
     * @return negative value if the BasicString's value appears before the
     * character sequence in the specified string, zero when identical,
     * positive value if the BasicString's value appears after the character
     * sequence in the string.
     */
    int compare(const char* s) const noexcept { return _data.compare(s); }

    /**
     * @brief Lexicographically compares the content of the string with the
     * specified substring.
     *
     * @param pos1 the position of the first character of the substring.
     * @param n1 the length of the substring.
     * @param str the string instance being compared with.
     *
     * @return negative value if the BasicString's value appears before the
     * character sequence in the specified substring, zero when identical,
     * positive value if the BasicString's value appears after the character
     * sequence in the substring.
     */
    int compare(size_type pos1, size_type n1, const char* s) const
    {
        return _data.compare(pos1, n1, s);
    }

    /**
     * @brief Lexicographically compares the content of the string with the
     * specified substring.
     *
     * @param pos1 the position of the first character of the substring.
     * @param n1 the length of the substring.
     * @param str the string instance being compared with.
     * @param n2 the length of the string being compared with.
     *
     * @return negative value if the BasicString's value appears before the
     * character sequence in the specified substring, zero when identical,
     * positive value if the BasicString's value appears after the character
     * sequence in the substring.
     */
    int compare(size_type pos1, size_type n1, const char* s, size_type n2) const
    {
        return _data.compare(pos1, n1, s, n2);
    }

    /**
     * @brief Lexicographically compares the content of the string with a
     * content of the StringView.
     *
     * @param sv the StringView instace being compared with.
     *
     * @return negative value if the BasicString's value appears before the
     * character sequence in the specified StringView, zero when identical,
     * positive value if the BasicString's value appears after the character
     * sequence in the StringView.
     *
     * @req {SWS_CORE_03321}
     */
    int compare(StringView sv) const noexcept
    {
        return static_cast<StringView>(_data).compare(sv);
    }

    /**
     * @brief Lexicographically compares a substring with a content of the
     * StringView instance.
     *
     * @param pos1 position of the first character of the substring.
     * @param n1 the length of the substring.
     * @param sv the StringView instance being compared with.
     *
     * @return negative value if the BasicString's value appears before the
     * character sequence in the specified StringView, zero when identical,
     * positive value if the BasicString's value appears after the character
     * sequence in the StringView.
     *
     * @req {SWS_CORE_03322}
     */
    int compare(size_type pos1, size_type n1, StringView sv) const
    {
        return static_cast<StringView>(_data).compare(pos1, n1, sv);
    }

    /**
     * @brief Lexicographically compares a substring with a content of an object
     * convertible to StringView.
     *
     * @param pos1 the begin the compared substring.
     * @param n1 the length of the compared substring.
     * @param t the instance of object convertible to StringView.
     * @param pos2 the begin of the substring made of a given object.
     * @param n2 the length of the substring made of a given object.
     *
     * @return negative value if the BasicString's value appears before the
     * character sequence in the specified StringView, zero when identical,
     * positive value if the BasicString's value appears after the character
     * sequence in the StringView.
     *
     * @req {SWS_CORE_03323}
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
        StringView sv = static_cast<StringView>(t);

        // FIXME: replace this after ara::core::StringView reimplementation
        return static_cast<StringView>(_data).substr(pos1, n1).compare(
          sv.substr(pos2, n2));
    }

    /**
     * @brief Converts the string to the StringView instance.
     *
     * @return the instance of StringView.
     *
     * @req {SWS_CORE_03301}
     */
    operator StringView() const noexcept { return StringView(data(), size()); }
};

/**
 * @brief A type alias for BasicString.
 *
 * @req {SWS_CORE_03001}
 */
using String = BasicString<>;

/**
 * @brief Exchanges contents of two BasicString's instances.
 *
 * @param lhs an instance of BasicString to swap.
 * @param rhs an instance of BasicString to swap.
 *
 * @tparam Allocator an allocator type.
 *
 * @req {SWS_CORE_03296}
 */
template<typename Allocator> void
swap(BasicString<Allocator>& lhs, BasicString<Allocator>& rhs) noexcept
{
    lhs.swap(rhs);
}

// comparision operators

/**
 * @brief Checks if two strings are identical.
 *
 * @param lhs the BasicString instance to compare.
 * @param rhs the BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if strings are identical, false otherwise.
 */
template<class AllocatorT> bool
operator==(const BasicString<AllocatorT>& lhs,
           const BasicString<AllocatorT>& rhs) noexcept
{
    return lhs.compare(rhs) == 0;
}

/**
 * @brief Checks if two strings are identical.
 *
 * @param bs the BasicString instance to compare.
 * @param s the plain null-terminated const char* string instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if strings are identical, false otherwise.
 */
template<class AllocatorT> bool
operator==(const BasicString<AllocatorT>& bs, const char* s) noexcept
{
    return bs.compare(s) == 0;
}

/**
 * @brief Checks if two strings are identical.
 *
 * @param s the plain null-terminated const char* string instance to compare.
 * @param bs the BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if strings are identical, false otherwise.
 */
template<class AllocatorT> bool
operator==(const char* s, const BasicString<AllocatorT>& bs) noexcept
{
    return bs.compare(s) == 0;
}

/**
 * @brief Checks if two strings are diffrent.
 *
 * @param lhs the BasicString instance to compare.
 * @param rhs the BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if strings are different, false otherwise.
 */
template<class AllocatorT> bool
operator!=(const BasicString<AllocatorT>& lhs,
           const BasicString<AllocatorT>& rhs) noexcept
{
    return lhs.compare(rhs) != 0;
}

/**
 * @brief Checks if two strings are diffrent.
 *
 * @param bs the BasicString instance to compare.
 * @param s the plain null-terminated const char* string instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if strings are different, false otherwise.
 */
template<class AllocatorT> bool
operator!=(const BasicString<AllocatorT>& bs, const char* s) noexcept
{
    return bs.compare(s) != 0;
}

/**
 * @brief Checks if two strings are diffrent.
 *
 * @param s the plain null-terminated const char* string instance to compare.
 * @param bs the BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if strings are different, false otherwise.
 */
template<class AllocatorT> bool
operator!=(const char* s, const BasicString<AllocatorT>& bs) noexcept
{
    return bs.compare(s) != 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param lhs BasicString instance to compare.
 * @param rhs BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if lhs is lexicographically lesser than rhs, false otherwise.
 */
template<class AllocatorT> bool
operator<(const BasicString<AllocatorT>& lhs,
          const BasicString<AllocatorT>& rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param bs the BasicString instance to compare.
 * @param s null-terminated const char string to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if bs is lexicographically lesser than s, false otherwise.
 */
template<class AllocatorT> bool
operator<(const BasicString<AllocatorT>& bs, const char* s) noexcept
{
    return bs.compare(s) < 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param s null-terminated const char string to compare.
 * @param bs BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if s is lexicographically lesser than bs, false otherwise.
 */
template<class AllocatorT> bool
operator<(const char* s, const BasicString<AllocatorT>& bs) noexcept
{
    return bs.compare(s) > 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param lhs BasicString instance to compare.
 * @param rhs BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if lhs is lexicographically greater than rhs, false otherwise.
 */
template<class AllocatorT> bool
operator>(const BasicString<AllocatorT>& lhs,
          const BasicString<AllocatorT>& rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param bs the BasicString instance to compare.
 * @param s null-terminated const char string to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if bs is lexicographically greater than s,
 * false otherwise.
 */
template<class AllocatorT> bool
operator>(const BasicString<AllocatorT>& bs, const char* s) noexcept
{
    return bs.compare(s) > 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param s null-terminated const char string to compare.
 * @param bs BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if s is lexicographically greater than bs, false otherwise.
 */
template<class AllocatorT> bool
operator>(const char* s, const BasicString<AllocatorT>& bs) noexcept
{
    return bs.compare(s) < 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param lhs BasicString instance to compare.
 * @param rhs BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if lhs is lexicographically not greater
 * than rhs, false otherwise.
 */
template<class AllocatorT> bool
operator<=(const BasicString<AllocatorT>& lhs,
           const BasicString<AllocatorT>& rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param bs BasicString instance to compare.
 * @param s null-terminated const char string to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if bs is lexicographically not greater
 * than s, false otherwise.
 */
template<class AllocatorT> bool
operator<=(const BasicString<AllocatorT>& bs, const char* s) noexcept
{
    return bs.compare(s) <= 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param s null-terminated const char string to compare.
 * @param bs BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if s is lexicographically not greater than bs, false otherwise.
 */
template<class AllocatorT> bool
operator<=(const char* s, const BasicString<AllocatorT>& bs) noexcept
{
    return bs.compare(s) >= 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param lhs BasicString instance to compare.
 * @param rhs BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if lhs is lexicographically not lesser than
 * rhs, false otherwise.
 */
template<class AllocatorT> bool
operator>=(const BasicString<AllocatorT>& lhs,
           const BasicString<AllocatorT>& rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param bs the BasicString instance to compare.
 * @param s null-terminated const char string to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if bs is lexicographically not lesser than
 * s, false otherwise.
 */
template<class AllocatorT> bool
operator>=(const BasicString<AllocatorT>& bs, const char* s) noexcept
{
    return bs.compare(s) >= 0;
}

/**
 * @brief Lexicographically compares two strings.
 *
 * @param s null-terminated const char string to compare.
 * @param bs BasicString instance to compare.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return True if s is lexicographically not lesser than bs, false otherwise.
 */
template<class AllocatorT> bool
operator>=(const char* s, const BasicString<AllocatorT>& bs) noexcept
{
    return bs.compare(s) <= 0;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the string to concatenate.
 * @param rhs the string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(const BasicString<AllocatorT>& lhs,
          const BasicString<AllocatorT>& rhs)
{
    BasicString<AllocatorT> ret(lhs);

    return ret += rhs;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the string to concatenate.
 * @param rhs the string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(BasicString<AllocatorT>&& lhs, const BasicString<AllocatorT>& rhs)
{
    BasicString<AllocatorT> ret{std::forward<BasicString<AllocatorT>>(lhs)};

    return ret += rhs;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the string to concatenate.
 * @param rhs the string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(const BasicString<AllocatorT>& lhs, BasicString<AllocatorT>&& rhs)
{
    BasicString<AllocatorT> ret(lhs);

    return ret += std::forward<BasicString<AllocatorT>>(rhs);
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the string to concatenate.
 * @param rhs the string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(BasicString<AllocatorT>&& lhs, BasicString<AllocatorT>&& rhs)
{
    BasicString<AllocatorT> ret{std::forward<BasicString<AllocatorT>>(lhs)};

    return ret += std::forward<BasicString<AllocatorT>>(rhs);
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the null-terminated const char* string to concatenate.
 * @param rhs the string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(const char* lhs, const BasicString<AllocatorT>& rhs)
{
    BasicString<AllocatorT> ret(lhs, rhs.get_allocator());

    return ret += rhs;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the null-terminated const char* string to concatenate.
 * @param rhs the string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(const char* lhs, BasicString<AllocatorT>&& rhs)
{
    BasicString<AllocatorT> ret(lhs, rhs.get_allocator());
    return ret += rhs;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the character to put at the beginning.
 * @param rhs the string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(char lhs, const BasicString<AllocatorT>& rhs)
{
    using size_type = typename BasicString<AllocatorT>::size_type;
    BasicString<AllocatorT> ret(size_type(1), lhs, rhs.get_allocator());

    return ret += rhs;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the character to put at the beginning.
 * @param rhs the string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(char lhs, BasicString<AllocatorT>&& rhs)
{
    using size_type = typename BasicString<AllocatorT>::size_type;
    BasicString<AllocatorT> ret(size_type(1), lhs, rhs.get_allocator());
    return ret += rhs;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the string to concatenate.
 * @param rhs the null-terminated const char* string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(const BasicString<AllocatorT>& lhs, const char* rhs)
{
    BasicString<AllocatorT> ret(lhs);

    return ret += rhs;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the string to concatenate.
 * @param rhs the null-terminated const char* string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(BasicString<AllocatorT>&& lhs, const char* rhs)
{
    BasicString<AllocatorT> ret{std::forward<BasicString<AllocatorT>>(lhs)};

    return ret += rhs;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the string to concatenate.
 * @param rhs the null-terminated const char* string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(const BasicString<AllocatorT>& lhs, char rhs)
{
    BasicString<AllocatorT> ret(lhs);

    return ret += rhs;
}

/**
 * @brief Concatenates two strings.
 *
 * @param lhs the string to concatenate.
 * @param rhs the null-terminated const char* string to concatenate.
 *
 * @tparam AllocatorT an allocator type.
 *
 * @return An instance of BasicString containing concatenated content of the
 * given strings.
 */
template<class AllocatorT> BasicString<AllocatorT>
operator+(BasicString<AllocatorT>&& lhs, char rhs)
{
    BasicString<AllocatorT> ret{std::forward<BasicString<AllocatorT>>(lhs)};

    return ret += rhs;
}

}  // namespace ara::core

#endif  // ARA_CORE_STRING_H_
