/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_VECTOR_H_
#define ARA_CORE_VECTOR_H_

#include "ara/core/allocator.h"
#include <initializer_list>
#include <vector>

namespace ara::core {
/**
 * @brief Sequence container that encapsulates dynamic size arrays.
 *
 * @tparam T - the type of the elements.
 * @tparam Allocator - An allocator that is used to acquire/release memory and
 * to construct/destroy the elements in that memory.
 *
 * @req {SWS_CORE_01301}
 */
template<class T, class Allocator = Allocator<T>> class Vector
{

    static_assert(
      std::is_same<typename std::remove_cv<T>::type, T>::value,
      "ara::core::Vector must have a non-const, non-volatile value_type");

    std::vector<T, Allocator> _impl;

 public:
    using value_type       = T;
    using allocator_type   = Allocator;
    using size_type        = std::size_t;
    using difference_type  = std::ptrdiff_t;
    using reference        = value_type&;
    using const_reference  = const value_type&;
    using pointer          = typename AllocatorTraits<Allocator>::pointer;
    using const_pointer    = typename AllocatorTraits<Allocator>::const_pointer;
    using iterator         = typename std::vector<T>::iterator;
    using const_iterator   = typename std::vector<T>::const_iterator;
    using reverse_iterator = typename std::reverse_iterator<iterator>;
    using const_reverse_iterator =
      typename std::reverse_iterator<const_iterator>;

    /**
     * @brief Default destructor.
     */
    ~Vector() = default;

    /**
     * @brief Constructs an empty vector, using the specified allocator.
     *
     * @param[in] alloc - allocator.
     */
    explicit Vector(const Allocator& alloc = Allocator()) : _impl(alloc) {}

    /**
     * @brief Constructs a vector with @c count value-initialized elements
     *
     * @param[in] count - size of the container.
     */
    explicit Vector(size_type count) : _impl(count) {}

    /**
     * @brief Constructs a vector with @c count copies of @c value, using the
     * specified allocator @c alloc.
     *
     * @param[in] count - size of the container.
     * @param[in] value - initial value of single element.
     * @param[in] alloc - allocator.
     */
    Vector(size_type        count,
           const T&         value,
           const Allocator& alloc = Allocator())
      : _impl(count, value, alloc)
    {}

    /**
     * @brief Constructs a vector equal to the range @c [first,last), using the
     * specified allocator @c alloc.
     *
     * @param[in] first - specifies the begining of the range.
     * @param[in] last - specifies end of the range.
     * @param[in] alloc - allocator.
     */
    template<class InputIterator> Vector(InputIterator    first,
                                         InputIterator    last,
                                         const Allocator& alloc = Allocator())
      : _impl(first, last, alloc)
    {}

    /**
     * @brief Copy constructor.
     *
     * @param[in] other - content to be copied.
     */
    Vector(const Vector& other) : _impl(other._impl) {}

    /**
     * @brief Move constructor. Constructs the container with the contents of @c
     * other using move semantics.
     *
     * @param[in] other - content used to construct a container.
     */
    Vector(Vector&& other) : _impl(std::move(other._impl)) {}

    /**
     * @brief Allocator-extended copy constructor.
     * Constructs the container with the copy of the contents of @c other using
     * the specified allocator @c alloc.
     *
     * @param[in] other - content to be copied.
     * @param[in] alloc - allocator.
     */
    Vector(const Vector& other, const Allocator& alloc)
      : _impl(other._impl, alloc)
    {}

    /**
     * @brief Allocator-extended move constructor.
     * Constructs the container using move semantics with the contents of @c
     * other using the specified allocator @c alloc.
     *
     * @param[in] other - content used to construct a container.
     * @param[in] alloc - allocator.
     */
    Vector(Vector&& other, const Allocator& alloc)
      : _impl(std::move(other._impl), alloc)
    {}

    /**
     * @brief Constructs the container with the contents of the initializer list
     * @c init.
     *
     * @param[in] ilist - list of elements.
     * @param[in] alloc - allocator.
     */
    Vector(std::initializer_list<T> ilist, const Allocator& alloc = Allocator())
      : _impl(ilist, alloc)
    {}

    /**
     * @brief Copy assignment operator. Replaces the contents with a copy of the
     * contents of @c other.
     *
     * @param[in] other - content to be copied.
     */
    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            _impl = std::move(other._impl);
        }
        return *this;
    }

    /**
     * @brief Move assignment operator. Replaces the contents with those of @c
     * other using move semantics.
     *
     * @param[in] other - content used to construct a container.
     */
    Vector& operator=(Vector&& other)
    {
        _impl = std::move(other._impl);
        return *this;
    }

    /**
     * @brief Assignment operator. Replaces the contents with those identified
     * by initializer list @c ilist.
     *
     * @param[in] ilist - list of elements.
     */
    Vector& operator=(std::initializer_list<T> ilist)
    {
        _impl = ilist;
        return *this;
    }

    /**
     * @brief Replaces the contents with copies of those in the range @c
     * [first,last).
     *
     * @param[in] first - specifies the begining of the range.
     * @param[in] last - specifies end of the range.
     */
    template<class InputIterator> void
    assign(InputIterator first, InputIterator last)
    {
        _impl.assign(first, last);
    }

    /**
     * @brief Replaces the contents with @c count copies of value @c value.
     *
     * @param[in] count - new size of the container.
     * @param[in] value - initial value of single element.
     */
    void assign(size_type count, const T& value) { _impl.assign(count, value); }

    /**
     * @brief Replaces the contents with the elements from the initializer list
     * @c ilist.
     *
     * @param[in] ilist - list of elements.
     */
    void assign(std::initializer_list<T> ilist) { _impl.assign(ilist); }

    /**
     * @brief Returns the allocator associated with the container.
     *
     * @return The associated allocator.
     */
    allocator_type get_allocator() const noexcept
    {
        return _impl.get_allocator();
    }

    /**
     * @brief Returns an iterator to the first element of the vector.
     *
     * @return Iterator to the first element.
     */
    iterator begin() noexcept { return _impl.begin(); }

    /**
     * @brief Returns a const iterator to the first element of the vector.
     *
     * @return Iterator to the first element.
     */
    const_iterator begin() const noexcept { return _impl.begin(); }

    /**
     * @brief Returns an iterator to the element following the last element of
     * the vector.
     *
     * @return Iterator to the element following the last element.
     */
    iterator end() noexcept { return _impl.end(); }

    /**
     * @brief Returns a const iterator to the element following the last element
     * of the vector.
     *
     * @return Iterator to the element following the last element.
     */
    const_iterator end() const noexcept { return _impl.end(); }

    /**
     * @brief Returns a reverse iterator to the first element of the reversed
     * vector.
     *
     * @return Reverse iterator to the first element.
     */
    reverse_iterator rbegin() noexcept { return _impl.rbegin(); }

    /**
     * @brief Returns a const reverse iterator to the first element of the
     * reversed vector.
     *
     * @return Reverse iterator to the first element.
     */
    const_reverse_iterator rbegin() const noexcept { return _impl.rbegin(); }

    /**
     * @brief Returns a reverse iterator to the element following the last
     * element of the reversed vector.
     *
     * @return Reverse iterator to the element following the last element.
     */
    reverse_iterator rend() noexcept { return _impl.rend(); }

    /**
     * @brief Returns a const reverse iterator to the element following the last
     * element of the reversed vector.
     *
     * @return Reverse iterator to the element following the last element.
     */
    const_reverse_iterator rend() const noexcept { return _impl.rend(); }

    /**
     * @brief Returns a const iterator to the first element of the vector.
     *
     * @return Iterator to the first element.
     */
    const_iterator cbegin() const noexcept { return _impl.cbegin(); }

    /**
     * @brief Returns a const iterator to the element following the last element
     * of the vector.
     *
     * @return Iterator to the element following the last element.
     */
    const_iterator cend() const noexcept { return _impl.cend(); }

    /**
     * @brief Returns a reverse iterator to the first element of the reversed
     * vector.
     *
     * @return Reverse iterator to the first element.
     */
    const_reverse_iterator crbegin() const noexcept { return _impl.crbegin(); }

    /**
     * @brief Returns a reverse iterator to the element following the last
     * element of the reversed vector.
     *
     * @return Reverse iterator to the element following the last element.
     */
    const_reverse_iterator crend() const noexcept { return _impl.crend(); }

    /**
     * @brief Returns the number of elements in the container.
     *
     * @return The number of elements in the container.
     */
    size_type size() const noexcept { return _impl.size(); }

    /**
     * @brief Returns the maximum number of elements the container is able to
     * hold due to system or library implementation limitations.
     *
     * @return Maximum number of elements.
     */
    size_type max_size() const noexcept { return _impl.max_size(); }

    /**
     * @brief Resizes the container to contain count elements.
     *
     * @param[in] count - new size of the container.
     */
    void resize(size_type count) { _impl.resize(count); }

    /**
     * @brief Resizes the container to contain count elements.
     *
     * @param[in] count - new size of the container.
     * @param[in] value - the value to initialize the new elements with in case
     * when current size is less than @c count.
     */
    void resize(size_type count, const T& value) { _impl.resize(count, value); }

    /**
     * @brief Returns the number of elements that the container has currently
     * allocated space for.
     *
     * @return Capacity of the currently allocated storage.
     */
    size_type capacity() const noexcept { return _impl.capacity(); }

    /**
     * @brief Checks if the container has no elements.
     *
     * @return @c true if the container is empty, @c false otherwise.
     */
    bool empty() const noexcept { return _impl.empty(); }

    /**
     * @brief Increase the capacity of the vector to a value that's greater or
     * equal to @c new_cap.
     *
     * @param[in] new_cap - new capacity of the vector.
     */
    void reserve(size_type new_cap) { _impl.resize(new_cap); }

    /**
     * @brief Requests the removal of unused capacity.
     */
    void shrink_to_fit() { _impl.shrink_to_fit(); }

    /**
     * @brief Returns a reference to the element at specified location @c pos.
     * No bounds checking is performed.
     *
     * @param[in] pos - position of the element to return.
     *
     * @return Reference to the requested element.
     */
    reference operator[](size_type pos) { return _impl[pos]; }

    /**
     * @brief Returns a const reference to the element at specified location @c
     * pos. No bounds checking is performed.
     *
     * @param[in] pos - position of the element to return.
     *
     * @return Reference to the requested element.
     */
    const_reference operator[](size_type pos) const { return _impl[pos]; }

    /**
     * @brief Returns a reference to the element at specified location pos, with
     * bounds checking.
     *
     * @param[in] pos - position of the element to return.
     *
     * @return Reference to the requested element.
     */
    reference at(size_type pos) { return _impl.at(pos); }

    /**
     * @brief Returns a const reference to the element at specified location
     * pos, with bounds checking.
     *
     * @param[in] pos - position of the element to return.
     *
     * @return Reference to the requested element.
     */
    const_reference at(size_type pos) const { return _impl.at(pos); }

    /**
     * @brief Returns a reference to the first element in the container.
     *
     * @return Reference to the first element.
     */
    reference front() { return _impl.front(); }

    /**
     * @brief Returns a const reference to the first element in the container.
     *
     * @return Reference to the first element.
     */
    const_reference front() const { return _impl.front(); }

    /**
     * @brief Returns a reference to the last element in the container.
     *
     * @return Reference to the last element.
     */
    reference back() { return _impl.back(); }

    /**
     * @brief Returns a const reference to the last element in the container.
     *
     * @return Reference to the last element.
     */
    const_reference back() const { return _impl.back(); }

    /**
     * @brief Returns a pointer to the underlying array serving as element
     * storage.
     *
     * @return Pointer to the underlying element storage.
     */
    T* data() noexcept { return _impl.data(); }

    /**
     * @brief Returns a const pointer to the underlying array serving as element
     * storage.
     *
     * @return Pointer to the underlying element storage.
     */
    const T* data() const noexcept { return _impl.data(); }

    /**
     * @brief Appends a new element to the end of the container.
     *
     * @param[in] args - arguments to forward to the constructor of the element
     */
    template<class... Args> void emplace_back(Args&&... args)
    {
        _impl.emplace_back(std::forward<Args>(args)...);
    }

    /**
     * @brief Appends the given element @c value to the end of the container.
     * The new element is initialized as a copy of value.
     *
     * @param[in] value - the value of the element to append.
     */
    void push_back(const T& value) { _impl.push_back(value); }

    /**
     * @brief Appends the given element @c value to the end of the container.
     * Value is moved into the new element.
     *
     * @param[in] value - the value of the element to append.
     */
    void push_back(T&& value) { _impl.push_back(std::move(value)); }

    /**
     * @brief Removes the last element of the container.
     */
    void pop_back() { _impl.pop_back(); }

    /**
     * @brief Inserts a new element into the container directly before @c pos.
     *
     * @param[in] pos - iterator before which the new element will be
     * constructed.
     * @param[in] args - arguments to forward to the constructor of the element.
     *
     * @return Iterator pointing to the emplaced element.
     */
    template<class... Args> iterator emplace(const_iterator pos, Args&&... args)
    {
        return _impl.emplace(pos, std::forward<Args>(args)...);
    }

    /**
     * @brief Inserts an element @c value into the container before @c pos.
     *
     * @param[in] pos - iterator before which the content will be inserted.
     * @param[in] value - element value to insert.
     *
     * @return Iterator pointing to the.
     */
    iterator insert(const_iterator pos, const T& value)
    {
        return _impl.insert(pos, value);
    }

    /**
     * @brief Inserts an element @c value into the container before @c pos.
     *
     * @param[in] pos - iterator before which the content will be inserted.
     * @param[in] value - element value to insert.
     *
     * @return Iterator pointing to the.
     */
    iterator insert(const_iterator pos, T&& value)
    {
        return _impl.insert(pos, std::move(value));
    }

    /**
     * @brief Inserts @c count copies of the @c value into the container before
     * @c pos
     *
     * @param[in] pos - iterator before which the content will be inserted.
     * @param[in] count - number of copies.
     * @param[in] value - element value to insert.
     *
     * @return Iterator pointing to the.
     */
    iterator insert(const_iterator pos, size_type count, const T& value)
    {
        return _impl.insert(pos, count, value);
    }

    /**
     * @brief Inserts elements from range @c [first,last) into the container
     * before @c pos.
     *
     * @param[in] pos - iterator before which the content will be inserted.
     * @param[in] first - start the range of elements to insert.
     * @param[in] last - end the range of elements to insert.
     *
     * @return Iterator pointing to the.
     */
    template<class InputIterator> iterator
    insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        return _impl.insert(pos, first, last);
    }

    /**
     * @brief Inserts elements from initializer list @c ilist into the container
     * before @c pos.
     *
     * @param[in] pos - iterator before which the content will be inserted.
     * @param[in] ilist - initializer list to insert the values from.
     *
     * @return Iterator pointing to the.
     */
    iterator insert(const_iterator pos, std::initializer_list<T> ilist)
    {
        return _impl.insert(pos, ilist);
    }

    /**
     * @brief Erases the element at @c pos.
     *
     * @param[in] pos - iterator to the element to remove.
     *
     * @return Iterator following the last removed element.
     */
    iterator erase(const_iterator pos) { return _impl.erase(pos); }

    /**
     * @brief Erases the element in the range @c [first,last).
     *
     * @param[in] first - start the range of elements to erase.
     * @param[in] last - end the range of elements to erase.
     *
     * @return Iterator following the last removed element.
     */
    iterator erase(const_iterator first, const_iterator last)
    {
        return _impl.erase(first, last);
    }

    /**
     * @brief Exchanges the contents of the container with those of @c other.
     *
     * @param[in] other - container to exchange the contents with.
     */
    void swap(Vector& other) { _impl.swap(other._impl); }

    /**
     * @brief Erases all elements from the container.
     */
    void clear() noexcept { _impl.clear(); }
};

/**
 * @brief Checks if the contents of @c lhs and @c rhs are equal, that is,
 * they have the same number of elements and each element in @c lhs compares
 * equal with the element in @c rhs at the same position.
 *
 * @param[in] lhs - vector which content is compared.
 * @param[in] rhs - vector which content is compared.
 *
 * @return @c true if the contents of the vectors are equal, @c false otherwise.
 *
 * @req {SWS_CORE_01390}
 */
template<class T, class Allocator> bool
operator==(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
    return (lhs.size() == rhs.size()
            && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

/**
 * @brief Checks if the contents of @c lhs and @c rhs are equal, that is,
 * they have the same number of elements and each element in @c lhs compares
 * equal with the element in @c rhs at the same position.
 *
 * @param[in] lhs - vector which content is compared.
 * @param[in] rhs - vector which content is compared.
 *
 * @return @c true if the contents of the vectors are not equal, @c false
 * otherwise.
 *
 * @req {SWS_CORE_01391}
 */
template<class T, class Allocator> bool
operator!=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
    return ! (lhs == rhs);
}

/**
 * @brief Compares the contents of @c lhs and @c rhs lexicographically.
 *
 * @param[in] lhs - vector which content is compared.
 * @param[in] rhs - vector which content is compared.
 *
 * @return @c true if the contents of the @c lhs are lexicographically less than
 * the contents of @c rhs, @c false otherwise.
 *
 * @req {SWS_CORE_01392}
 */
template<class T, class Allocator> bool
operator<(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
    return std::lexicographical_compare(lhs.begin(),
                                        lhs.end(),
                                        rhs.begin(),
                                        rhs.end());
}

/**
 * @brief Compares the contents of @c lhs and @c rhs lexicographically.
 *
 * @param[in] lhs - vector which content is compared.
 * @param[in] rhs - vector which content is compared.
 *
 * @return @c true if the contents of the @c lhs are lexicographically less than
 * or equal the contents of @c rhs, @c false otherwise.
 *
 * @req {SWS_CORE_01393}
 */
template<class T, class Allocator> bool
operator<=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
    return ! (rhs < lhs);
}

/**
 * @brief Compares the contents of @c lhs and @c rhs lexicographically.
 *
 * @param[in] lhs - vector which content is compared.
 * @param[in] rhs - vector which content is compared.
 *
 * @return @c true if the contents of the @c lhs are lexicographically greater
 * than the contents of @c rhs, @c false otherwise.
 *
 * @req {SWS_CORE_01394}
 */
template<class T, class Allocator> bool
operator>(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
    return rhs < lhs;
}

/**
 * @brief Compares the contents of @c lhs and @c rhs lexicographically.
 *
 * @param[in] lhs - vector which content is compared.
 * @param[in] rhs - vector which content is compared.
 *
 * @return @c true if the contents of the @c lhs are lexicographically greater
 * than or equal the contents of @c rhs, @c false otherwise.
 *
 * @req {SWS_CORE_01395}
 */
template<class T, class Allocator> bool
operator>=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
    return ! (lhs < rhs);
}

/**
 * @brief Swaps the contents of @c lhs and @c rhs.
 *
 * @param[in] lhs - vector which content is compared.
 * @param[in] rhs - vector which content is compared.
 *
 * @req {SWS_CORE_01396}
 */
template<class T, class Allocator> void
swap(Vector<T, Allocator>& lhs, Vector<T, Allocator>& rhs)
{
    lhs.swap(rhs);
}

}  // namespace ara::core

#endif  // ARA_CORE_VECTOR_H_
