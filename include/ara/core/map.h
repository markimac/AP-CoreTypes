/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_MAP_H_
#define ARA_CORE_MAP_H_

#include "ara/core/allocator.h"
#include <map>

namespace ara::core {
/**
 * @brief Sorted associative container that contains key-value pairs with unique
 * keys.
 *
 * @tparam K vey type.
 * @tparam V value type.
 * @tparam C key_compare function.
 * @tparam Allocator allocator type.
 *
 * @req {SWS_CORE_01400}
 */
template<typename K,
         typename V,
         typename C         = std::less<K>,
         typename Allocator = Allocator<std::pair<const K, V>>>
class Map
{
 public:
    // Draft only
    // todo: write our own iterators
    using iterator = typename std::map<K, V, C, Allocator>::iterator;
    using const_iterator =
      typename std::map<K, V, C, Allocator>::const_iterator;
    using reverse_iterator =
      typename std::map<K, V, C, Allocator>::reverse_iterator;
    using const_reverse_iterator =
      typename std::map<K, V, C, Allocator>::const_reverse_iterator;
    using value_compare = typename std::map<K, V, C, Allocator>::value_compare;

    typedef K                                                  key_type;
    typedef V                                                  mapped_type;
    typedef std::pair<const K, V>                              value_type;
    typedef std::size_t                                        size_type;
    typedef std::ptrdiff_t                                     difference_type;
    typedef C                                                  key_compare;
    typedef Allocator                                          allocator_type;
    typedef value_type&                                        reference;
    typedef const value_type&                                  const_reference;
    typedef typename AllocatorTraits<Allocator>::pointer       pointer;
    typedef typename AllocatorTraits<Allocator>::const_pointer const_pointer;

    /**
     * @brief Constructs an empty container.
     *
     */
    Map() = default;

    /**
     * @brief Constructs an empty container.
     *
     * @param comp comparison function object to use for all comparisons of
     * keys.
     * @param alloc allocator to use for all memory allocations of this
     * container.
     */
    explicit Map(const C& comp, const Allocator& alloc = Allocator())
    {
        m_ = std::map<K, V, C, Allocator>(comp, alloc);
    }

    /**
     * @brief Constructs an empty container.
     *
     * @param alloc allocator to use for all memory allocations of this
     * container.
     */
    explicit Map(const Allocator& alloc)
    {
        m_ = std::map<K, V, C, Allocator>(alloc);
    }

    /**
     * @brief Copy constructor. Constructs the container with the copy of the
     * contents of other.
     *
     * @param other another container to be used as source to initialize the
     * elements of the container with.
     */
    Map(const Map& other) { m_ = std::map<K, V, C, Allocator>(other.m_); }

    /**
     * @brief Copy constructor. Constructs the container with the copy of the
     * contents of other.
     *
     * @param other another container to be used as source to initialize the
     * elements of the container with.
     * @param alloc allocator to use for all memory allocations of this
     * container.
     */
    Map(const Map& other, const Allocator& alloc)
    {
        m_ = std::map<K, V, C, Allocator>(other.m_, alloc);
    }

    /**
     * @brief Move constructor. Constructs the container with the contents of
     * other using move semantics.
     *
     * @param other another container to be used as source to initialize the
     * elements of the container with.
     */
    Map(const Map&& other)
    {
        m_ = std::map<K, V, C, Allocator>(std::move(other.m_));
    }

    /**
     * @brief Move constructor. Constructs the container with the contents of
     * other using move semantics.
     *
     * @param other another container to be used as source to initialize the
     * elements of the container with.
     * @param alloc allocator to use for all memory allocations of this
     * container.
     */
    Map(const Map&& other, const Allocator& alloc)
    {
        m_ = std::map<K, V, C, Allocator>(std::move(other.m_), alloc);
    }

    /**
     * @brief Constructs the container with the contents of the initializer list
     * init.
     *
     * @param init initializer list to initialize the elements of the container
     * with.
     * @param comp comparison function object to use for all comparisons of
     * keys.
     * @param alloc allocator to use for all memory allocations of this
     * container.
     */
    Map(std::initializer_list<value_type> init,
        const C&                          comp  = C(),
        const Allocator&                  alloc = Allocator())
    {
        m_ = std::map<K, V, C, Allocator>(init, comp, alloc);
    }

    /**
     * @brief Replaces the contents of the container.
     *
     * @param other another container to use as data source.
     *
     * @return reference to Map instance.
     */
    Map& operator=(const Map& other)
    {
        m_ = other.m_;

        return *this;
    }

    /**
     * @brief Replaces the contents of the container.
     *
     * @param ilist initializer list to use as data source.
     *
     * @return reference to Map instance.
     */
    Map& operator=(std::initializer_list<value_type> ilist)
    {
        m_ = ilist;

        return *this;
    }

    /**
     * @brief Compares the contents of two maps.
     *
     * @param lhs first map.
     * @param rhs second map.
     *
     * @return true if the contents of the maps are equal, false otherwise.
     */
    friend bool operator==(const Map<K, V, C, Allocator>& lhs,
                           const Map<K, V, C, Allocator>& rhs)
    {
        return lhs.m_ == rhs.m_;
    }

    /**
     * @brief Compares the contents of two maps.
     *
     * @param lhs first map.
     * @param rhs second map.
     *
     * @return true if the contents of the maps are not equal, false otherwise.
     */
    friend bool operator!=(const Map<K, V, C, Allocator>& lhs,
                           const Map<K, V, C, Allocator>& rhs)
    {
        return lhs.m_ != rhs.m_;
    }

    /**
     * @brief Compares the contents of two maps.
     *
     * @param lhs first map.
     * @param rhs second map.
     *
     * @return true if the contents of the lhs are lexicographically less than
     * the contents of rhs, false otherwise.
     */
    friend bool operator<(const Map<K, V, C, Allocator>& lhs,
                          const Map<K, V, C, Allocator>& rhs)
    {
        return lhs.m_ < rhs.m_;
    }

    /**
     * @brief Compares the contents of two maps.
     *
     * @param lhs first map.
     * @param rhs second map.
     *
     * @return true if the contents of the lhs are lexicographically less than
     * or equal the contents of rhs, false otherwise.
     */
    friend bool operator<=(const Map<K, V, C, Allocator>& lhs,
                           const Map<K, V, C, Allocator>& rhs)
    {
        return lhs.m_ <= rhs.m_;
    }

    /**
     * @brief Compares the contents of two maps.
     *
     * @param lhs first map.
     * @param rhs second map.
     *
     * @return true if the contents of the lhs are lexicographically greater
     * than the contents of rhs, false otherwise.
     */
    friend bool operator>(const Map<K, V, C, Allocator>& lhs,
                          const Map<K, V, C, Allocator>& rhs)
    {
        return lhs.m_ > rhs.m_;
    }

    /**
     * @brief Compares the contents of two maps.
     *
     * @param lhs first map.
     * @param rhs second map.
     *
     * @return true if the contents of the lhs are lexicographically greater
     * than or equal the contents of rhs, false otherwise.
     */
    friend bool operator>=(const Map<K, V, C, Allocator>& lhs,
                           const Map<K, V, C, Allocator>& rhs)
    {
        return lhs.m_ >= rhs.m_;
    }

    /**
     * @brief Returns the allocator associated with the container.
     *
     * @return the associated allocator.
     */
    allocator_type get_allocator() const noexcept { return m_.get_allocator(); }

    /**
     * @brief Returns a reference to the mapped value of the element with key
     * equivalent to key.
     *
     * @param key the key of the element to find.
     *
     * @return reference to the mapped value of the requested element.
     */
    mapped_type& at(const K& key) { return m_.at(key); }

    /**
     * @brief Returns a const reference to the mapped value of the element with
     * key equivalent to key.
     *
     * @param key the key of the element to find.
     *
     * @return reference to the mapped value of the requested element.
     */
    const mapped_type& at(const K& key) const { return m_.at(key); }

    /**
     * @brief Returns a reference to the value.
     *
     * @param key the key of the element to find.
     *
     * @return reference to the mapped value of the new element if no element
     * with key key existed.
     */
    mapped_type& operator[](const K& key) { return m_[key]; }

    /**
     * @brief Returns a reference to the value.
     *
     * @param key the key of the element to find.
     *
     * @return reference to the mapped value of the new element if no element
     * with key key existed.
     */
    mapped_type& operator[](const K&& key) { return m_[key]; }

    /**
     * @brief Returns an iterator to the beginning.
     *
     * @return iterator to the first element.
     */
    iterator begin() noexcept { return m_.begin(); }

    /**
     * @brief Returns an iterator to the beginning.
     *
     * @return iterator to the first element.
     */
    const_iterator begin() const noexcept { return m_.begin(); }

    /**
     * @brief Returns an iterator to the beginning.
     *
     * @return iterator to the first element.
     */
    const_iterator cbegin() const noexcept { return m_.cbegin(); }

    /**
     * @brief Returns an iterator to the end.
     *
     * @return iterator to the last element.
     */
    iterator end() noexcept { return m_.end(); }

    /**
     * @brief Returns an iterator to the end.
     *
     * @return iterator to the last element.
     */
    const_iterator end() const noexcept { return m_.end(); }

    /**
     * @brief Returns an iterator to the end.
     *
     * @return iterator to the last element.
     */
    const_iterator cend() const noexcept { return m_.cend(); }

    /**
     * @brief Returns an reverse iterator to the beginning.
     *
     * @return reverse iterator to the first element.
     */
    reverse_iterator rbegin() noexcept { return m_.rbegin(); }

    /**
     * @brief Returns an reverse iterator to the beginning.
     *
     * @return reverse iterator to the first element.
     */
    const_reverse_iterator rbegin() const noexcept { return m_.rbegin(); }

    /**
     * @brief Returns an reverse iterator to the beginning.
     *
     * @return reverse iterator to the first element.
     */
    const_reverse_iterator crbegin() const noexcept { return m_.crbegin(); }

    /**
     * @brief Returns an reverse iterator to the end.
     *
     * @return reverse iterator to the last element.
     */
    reverse_iterator rend() noexcept { return m_.rend(); }

    /**
     * @brief Returns an reverse iterator to the end.
     *
     * @return reverse iterator to the last element.
     */
    const_reverse_iterator rend() const noexcept { return m_.rend(); }

    /**
     * @brief Returns an reverse iterator to the end.
     *
     * @return reverse iterator to the last element.
     */
    const_reverse_iterator crend() const noexcept { return m_.crend(); }

    /**
     * @brief Checks whether the container is empty.
     *
     * @return true if the container is empty, false otherwise.
     */
    bool empty() const noexcept { return m_.empty(); }

    /**
     * @brief Returns the number of elements.
     *
     * @return the number of elements in the container.
     */
    size_type size() const noexcept { return m_.size(); }

    /**
     * @brief Returns the maximum possible number of elements.
     *
     * @brief maximum number of elements.
     */
    size_type max_size() const noexcept { return m_.max_size(); }

    /**
     * @brief Erases all elements from the container.
     *
     */
    void clear() noexcept { m_.clear(); }

    /**
     * @brief Inserts element(s) into the container
     *
     * @param value element value to insert.
     *
     * @return a pair consisting of an iterator to the inserted element (or to
     * the element that prevented the insertion) and a bool denoting whether the
     * insertion took place.
     */
    std::pair<iterator, bool> insert(const value_type& value)
    {
        return m_.insert(value);
    }

    /**
     * @brief Inserts element(s) into the container
     *
     * @param value element value to insert.
     *
     * @tparam P value type.
     *
     * @return a pair consisting of an iterator to the inserted element (or to
     * the element that prevented the insertion) and a bool denoting whether the
     * insertion took place.
     */
    template<class P> std::pair<iterator, bool> insert(const P&& value)
    {
        return m_.insert(value);
    }

    /**
     * @brief Inserts value in the position as close as possible to hint.
     *
     * @param hint iterator to the position before which the new element will be
     * inserted.
     * @param value element value to insert.
     *
     * @return an iterator to the inserted element, or to the element that
     * prevented the insertion.
     */
    iterator insert(const_iterator hint, const value_type& value)
    {
        return m_.insert(hint, value);
    }

    /**
     * @brief Inserts value in the position as close as possible to hint.
     *
     * @param hint iterator to the position before which the new element will be
     * inserted.
     * @param value element value to insert.
     *
     * @tparam P value_type.
     *
     * @return an iterator to the inserted element, or to the element that
     * prevented the insertion.
     */
    template<class P> iterator insert(const_iterator hint, P&& value)
    {
        m_.insert(hint, value);
    }

    /**
     * @brief Inserts elements from range [first, last).
     *
     * @param first range of elements to insert.
     * @param last range of elements to insert.
     *
     * @tparam InputIt iterator type.
     */
    template<class InputIt> void insert(InputIt first, InputIt last)
    {
        m_.insert(first, last);
    }

    /**
     * @brief Inserts elements from initializer list ilist.
     *
     * @param ilist initializer list to insert the values from.
     */
    void insert(std::initializer_list<value_type> ilist) { m_.insert(ilist); }

    /**
     * @brief Inserts a new element into the container constructed in-place with
     * the given args if there is no element with the key in the container.
     *
     * @param args arguments to forward to the constructor of the element.
     *
     * @tparam Args arguments type.
     *
     * @return a pair consisting of an iterator to the inserted element, or the
     * already-existing element if no insertion happened, and a bool denoting
     * whether the insertion took place (true if insertion happened, false if it
     * did not).
     */
    template<class... Args> std::pair<iterator, bool> emplace(Args&&... args)
    {
        return m_.emplace(std::forward<Args>(args)...);
    }

    /**
     * @brief Inserts a new element to the container as close as possible to the
     * position just before hint.
     *
     * @param hint iterator to the position before which the new element will be
     * inserted.
     * @param args arguments to forward to the constructor of the element.
     *
     * @tparam Args arguments type.
     *
     * @return an iterator to the newly inserted element.
     */
    template<class... Args> iterator
    emplace_hint(const_iterator hint, Args&&... args)
    {
        return m_.emplace_hint(hint, std::forward<Args>(args)...);
    }

    /**
     * @brief Removes specified elements from the container.
     *
     * @param pos iterator to the element to remove.
     *
     * @return iterator following the last removed element.
     */
    iterator erase(const_iterator pos) { return m_.erase(pos); }

    /**
     * @brief Removes specified elements from the container.
     *
     * @param first range of elements to remove.
     * @param last range of elements to remove.
     *
     * @return iterator following the last removed element.
     */
    iterator erase(const_iterator first, const_iterator last)
    {
        return m_.erase(first, last);
    }

    /**
     * @brief Removes specified elements from the container.
     *
     * @param key key value of the elements to remove.
     *
     * @return number of elements removed.
     */
    size_type erase(const key_type& key) { return m_.erase(key); }

    /**
     * @brief Exchanges the contents of the container with those of other.
     *
     * @param other container to exchange the contents with.
     */
    void swap(Map& other) { m_.swap(other.m_); }

    /**
     * @brief Returns the number of elements matching specific key.
     *
     * @param key key value of the elements to count.
     *
     * @return number of elements with key that compares equivalent to key or x,
     * which is either 1 or 0 for (1).
     */
    size_type count(const K& key) const { return m_.count(key); }

    /**
     * @brief Finds an element with key that compares equivalent to the value x.
     *
     * @param key key value of the element to search for.
     *
     * @return iterator to an element with key equivalent to key.
     */
    iterator find(const K& key) { return m_.find(key); }

    /**
     * @brief Finds an element with key that compares equivalent to the value x.
     *
     * @param key key value of the element to search for.
     *
     * @return iterator to an element with key equivalent to key.
     */
    const_iterator find(const K& key) const { return m_.find(key); }

    /**
     * @brief Returns a range containing all elements with the given key in the
     * container.
     *
     * @param key key value to compare the elements to.
     *
     * @return std::pair containing a pair of iterators defining the wanted
     * range: the first pointing to the first element that is not less than key
     * and the second pointing to the first element greater than key.
     */
    std::pair<iterator, iterator> equal_range(const K& key)
    {
        return m_.equal_range(key);
    }

    /**
     * @brief Returns a range containing all elements with the given key in the
     * container.
     *
     * @param key key value to compare the elements to.
     *
     * @return std::pair containing a pair of iterators defining the wanted
     * range: the first pointing to the first element that is not less than key
     * and the second pointing to the first element greater than key.
     */
    std::pair<const_iterator, const_iterator> equal_range(const K& key) const
    {
        return m_.equal_range(key);
    }

    /**
     * @brief Returns an iterator pointing to the first element that is not less
     * than (i.e. greater or equal to) key.
     *
     * @param key key value to compare the elements to.
     *
     * @return iterator pointing to the first element that is not less than key.
     */
    iterator lower_bound(const K& key) { return m_.lower_bound(key); }

    /**
     * @brief Returns an iterator pointing to the first element that is not less
     * than (i.e. greater or equal to) key.
     *
     * @param key key value to compare the elements to.
     *
     * @return iterator pointing to the first element that is not less than key.
     */
    const_iterator lower_bound(const K& key) const
    {
        return m_.lower_bound(key);
    }

    /**
     * @brief Returns an iterator pointing to the first element that is greater
     * than key.
     *
     * @param key key value to compare the elements to.
     *
     * @return iterator pointing to the first element that is greater than key.
     */
    iterator upper_bound(const K& key) { return m_.upper_bound(key); }

    /**
     * @brief Returns an iterator pointing to the first element that is greater
     * than key.
     *
     * @param key key value to compare the elements to.
     *
     * @return iterator pointing to the first element that is greater than key.
     */
    const_iterator upper_bound(const K& key) const
    {
        return m_.upper_bound(key);
    }

    /**
     * @brief Returns the function object that compares the keys, which is a
     * copy of this container's constructor argument comp.
     *
     * @return the key comparison function object.
     */
    key_compare key_comp() const { return m_.key_comp(); }

    /**
     * @brief Returns a function object that compares objects of type
     * std::map::value_type (key-value pairs) by using key_comp to compare the
     * first components of the pairs.
     *
     * @return the value comparison function object.
     */
    value_compare value_comp() const { return m_.value_comp(); }

 private:
    std::map<K, V, C, Allocator> m_;
};

/**
 * @brief Exchanges content between maps.
 *
 * @param lhs first argument of swap invocation.
 * @param rhs second argument of swap invocation.
 *
 * @tparam K vey type.
 * @tparam V value type.
 * @tparam C key_compare function.
 * @tparam Allocator allocator type.
 *
 * @req {SWS_CORE_01496}
 */
template<class K, class V, class C, class Allocator> void
swap(Map<K, V, C, Allocator>& lhs, Map<K, V, C, Allocator>& rhs) noexcept
{
    lhs.swap(rhs);
}

}  // namespace ara::core

#endif  // ARA_CORE_MAP_H_
