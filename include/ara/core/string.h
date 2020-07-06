/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_STRING_H_
#define ARA_CORE_STRING_H_

#include <string> // std::basic_string

#include "ara/core/allocator.h"

#include "ara/core/string_view.h"

namespace ara::core
{

    // [SWS_CORE_03000] String type
    /*
    The namespace ara::core shall provide a template type BasicString.
    All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined. The character type is fixed
    to char, and the traits type is fixed to std::char_traits<char>. All supporting
    symbols shall be contained within namespace ara::core.
    */
    template <class AllocatorT=ara::core::Allocator<char> >
    class BasicString
    {
        std::basic_string<char> __data;

        public:

        typedef std::allocator_traits<AllocatorT>::size_type size_type;
        typedef std::basic_string<char>::const_iterator const_iterator;
        static const size_type npos = std::basic_string<char>::npos;

        // [SWS_CORE_03301] Implicit conversion to StringView
        /*
        An operator shall be defined for BasicString that provides implicit conversion to StringView:
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        operator StringView() const noexcept { return static_cast<std::basic_string_view<char> >(this->__data); }

        // [SWS_CORE_03302] Constructor from StringView
        /*
        A constructor shall be defined for BasicString that accepts a StringView argument by value.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        explicit BasicString(StringView sv) : __data(sv.data) {}

        // [SWS_CORE_03303] Constructor from implicit StringView
        /*
        A constructor shall be defined for BasicString that accepts any type that is implicitly convertible to StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        template <typename T>
        BasicString(T const& t, size_type pos, size_type n) : __data(t, pos, n) {}

        // [SWS_CORE_03304] operator= from StringView
        /*
        An operator= member function shall be defined for BasicString that accepts a StringView argument by value.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        BasicString& operator=(StringView sv)
        {
            this->__data = sv.data;
            return *this;
        }

        // [SWS_CORE_03305] Assignment from StringView
        /*
        A member function shall be defined for BasicString that allows assignment from StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        BasicString& assign(StringView sv)
        {
            this->__data.assign(sv.data);
            return *this;
        }

        // [SWS_CORE_03306] Assignment from implicit StringView
        /*
        A member function shall be defined for BasicString that allows assignment from any type that is implicitly convertible to StringView:
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        template <typename T>
        BasicString& assign(T const& t, size_type pos, size_type n = npos)
        {
            this->__data.assign(t, pos, n);
            return *this;
        }

        // [SWS_CORE_03307] operator+= from StringView
        /*
        An operator+= member function shall be defined for BasicString that accepts a StringView argument by value.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        BasicString& operator+=(StringView sv)
        {
            this->__data += sv.data;
            return *this;
        }

        // [SWS_CORE_03308] Concatenation of StringView
        /*
        A member function shall be defined for BasicString that allows concatenation of a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        BasicString& append(StringView sv)
        {
            this->__data.append(sv.data);
            return *this;
        }

        // [SWS_CORE_03309] Concatenation of implicit StringView
        /*
        A member function shall be defined for BasicString that allows concatenation of any type that is implicitly convertible to StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        template<typename T>
        BasicString& append(T const& t, size_type pos, size_type n = npos)
        {
            this->__data.append(t, pos, n);
            return *this;
        }

        // [SWS_CORE_03310] Insertion of StringView
        /*
        A member function shall be defined for BasicString that allows insertion of a StringView:
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        BasicString& insert(size_type pos, StringView sv)
        {
            this->__data.insert(pos, sv.data);
            return *this;
        }

        // [SWS_CORE_03311] Insertion of implicit StringView
        /*
        A member function shall be defined for BasicString that allows insertion of any type that is implicitly convertible to StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        template <typename T>
        BasicString& insert(size_type pos1, T const& t, size_type pos2, size_type n = npos)
        {
            this->__data.insert(pos1, t, pos2, n);
            return *this;
        }

        // [SWS_CORE_03312] Replacement with StringView
        /*
        A member function shall be defined for BasicString that allows replacement of a subsequence of *this with the contents of a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        BasicString& replace(size_type pos1, size_type n1, StringView sv)
        {
            this->__data.replace(pos1, n1, sv.data);
            return *this;
        }

        // [SWS_CORE_03313] Replacement with implicit StringView
        /*
        A member function shall be defined for BasicString that allows replacement of a subsequence
        of *this with the contents of any type that is implicitly convertible to StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        template<typename T>
        BasicString& replace(size_type pos1, size_type n1, T const& t, size_type pos2, size_type n2 = npos)
        {
            this->__data.replace(pos1, n1, t, pos2, n2);
            return *this;
        }

        // [SWS_CORE_03314] Replacement of iterator range with StringView
        /*
        A member function shall be defined for BasicString that allows replacement of an
        iterator-bounded subsequence of *this with the contents of a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        BasicString& replace(const_iterator i1, const_iterator i2, StringView sv)
        {
            this->__data.replace(i1, i2, sv.data);
            return *this;
        }

        // [SWS_CORE_03315] Forward-find a StringView
        /*
        A member function shall be defined for BasicString that allows forward-searching for the contents of a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        size_type find(StringView sv, size_type pos = 0) const noexcept
        {
            return this->__data.find(sv.data, pos);
        }

        // [SWS_CORE_03316] Reverse-find a StringView
        /*
        A member function shall be defined for BasicString that allows reverse-searching for the contents of a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        size_type rfind(StringView sv, size_type pos = npos) const noexcept
        {
            return this->__data.rfind(sv.data, pos);
        }

        // [SWS_CORE_03317] Forward-find of character set within a StringView
        /*
        A member function shall be defined for BasicString that allows forward-searching for any of the characters within a StringView:
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        size_type find_first_of(StringView sv, size_type pos = 0) const noexcept
        {
            return this->__data.find_first_of(sv.data, pos);
        }

        // [SWS_CORE_03318] Reverse-find of character set within a StringView
        /*
        A member function shall be defined for BasicString that allows reverse-searching for any of the characters within a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        size_type find_last_of(StringView sv, size_type pos = npos) const noexcept
        {
            return this->__data.find_last_of(sv.data, pos);
        }

        // [SWS_CORE_03319] Forward-find of character set not within a StringView
        /*
        A member function shall be defined for BasicString that allows forward-searching for any of the characters not contained in a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        size_type find_first_not_of(StringView sv, size_type pos = 0) const noexcept
        {
            return this->__data.find_first_not_of(sv.data, pos);
        }

        // [SWS_CORE_03320] Reverse-find of character set not within a StringView
        /*
        A member function shall be defined for BasicString that allows reverse-searching for any of the characters not contained in a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        size_type find_last_not_of(StringView sv, size_type pos = npos) const noexcept
        {
            return this->__data.find_last_not_of(sv.data, pos);
        }

        // [SWS_CORE_03321] Comparison with a StringView
        /*
        A member function shall be defined for BasicString that allows comparison with the contents of a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        int compare(StringView sv) const noexcept
        {
            return this->__data.compare(sv.data);
        }

        // [SWS_CORE_03322] Comparison of subsequence with a StringView
        /*
        A member function shall be defined for BasicString that allows comparison of a subsequence of *this with the contents of a StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        int compare(size_type pos1, size_type n1, StringView sv) const
        {
            return this->__data.compare(pos1, n1, sv.data);
        }

        // [SWS_CORE_03323] Comparison of subsequence with a subsequence of a StringView
        /*
        A member function shall be defined for BasicString that allows
        comparison of a subsequence of *this with the contents of a subsequence of any type
        that is implicitly convertible to StringView.
        This function shall behave the same as the corresponding std::basic_string function from [6, the C++17 standard].
        */
        template<typename T>
        int compare(size_type pos1, size_type n1, T const& t, size_type pos2, size_type n2 = npos) const
        {
            return this->__data.compare(pos1, n1, t, pos2, n2);
        }
    };

    // [SWS_CORE_03001] String type
    /*
    The namespace ara::core shall provide a type alias String.
    */
    using String = BasicString<>;

    // [SWS_CORE_03296] swap overload for BasicString
    /*
    There shall be an overload of the swap function within the namespace ara::core for arguments of type BasicString.
    This function shall exchange the state of lhs with that of rhs.
    */
    template<typename Allocator>
    void swap(BasicString<Allocator>& lhs, BasicString<Allocator>& rhs)
    {
        std::swap(lhs.__data, rhs.__data);
    }
}

#endif // ARA_CORE_STRING_H_
