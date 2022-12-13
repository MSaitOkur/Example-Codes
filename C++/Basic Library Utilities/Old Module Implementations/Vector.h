#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <utility>

#define MAX_SIZE 9223372036854775807

template <typename VectorType>
class Vector;

template <typename T>
void swap(T &x, T &y);

template <typename T>
void swap(Vector<T> &x, Vector<T> &y);

template <typename T>
bool operator<(const Vector<T> &t1, const Vector<T> &t2);
template <typename T>
bool operator==(const Vector<T> &t1, const Vector<T> &t2);
template <typename T>
bool operator!=(const Vector<T> &t1, const Vector<T> &t2);
template <typename T>
bool operator<=(const Vector<T> &t1, const Vector<T> &t2);
template <typename T>
bool operator>(const Vector<T> &t1, const Vector<T> &t2);
template <typename T>
bool operator>=(const Vector<T> &t1, const Vector<T> &t2);

template <typename VectorType>
class Vector
{
public:
    using ValueType = VectorType;
    using constValueType = const VectorType;
    using PointerType = ValueType *;
    using constPointerType = const ValueType *;
    using ReferenceType = ValueType &;
    using constReferenceType = const ValueType &;
    using RReferenceType = ValueType &&;
    using SizeType = std::size_t;
    using DifferenceType = std::ptrdiff_t;

    class VectorIterator;
    class constVectorIterator;
    class VectorReverseIterator;
    class constVectorReverseIterator;

    //--------------------------------------------------
    Vector()
    {
        m_Parray = allocate(m_Capacity);
    }
    ~Vector()
    {
        if (m_Parray)
        {
            delete[] m_Parray;
            m_Parray = nullptr;
        }
    }
    Vector(const Vector &other) : m_Size{other.m_Size}, m_Capacity{other.m_Capacity}
    {
        m_Parray = allocate(m_Capacity);

        for (SizeType i = 0; i < m_Size; ++i)
            m_Parray[i] = other.m_Parray[i];
    }

    Vector(Vector &&other) : m_Size{other.m_Size}, m_Capacity{other.m_Capacity}, m_Parray{other.m_Parray}
    {
        other.m_Parray = nullptr;
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            delete[] m_Parray;

            m_Size = other.m_Size;
            m_Capacity = other.m_Capacity;
            m_Parray = allocate(m_Capacity);

            for (SizeType i = 0; i < m_Size; ++i)
                m_Parray[i] = other.m_Parray[i];
        }
        return *this;
    }
    Vector &operator=(Vector &&other)
    {
        if (this != &other)
        {
            delete[] m_Parray;
            m_Size = other.m_Size;
            m_Capacity = other.m_Capacity;
            m_Parray = other.m_Parray;

            other.m_Parray = nullptr;
        }
        return *this;
    }
    //--------------------------------------------------

    //--------------------------------------------------
    explicit Vector(SizeType size, ValueType val = 0) : m_Size{size}, m_Capacity{size + size / 2}
    {
        m_Parray = allocate(m_Capacity);

        for (SizeType i = 0; i < m_Size; ++i)
            m_Parray[i] = val;
    }
    Vector(std::initializer_list<ValueType> ilist) : m_Size{ilist.size()}, m_Capacity{m_Size + m_Size / 2}
    {
        m_Parray = allocate(m_Capacity);

        SizeType idx = 0;
        for (auto iter : ilist)
            m_Parray[idx++] = iter;
    }
    Vector(constPointerType pbegin, constPointerType pend) : m_Size{static_cast<SizeType>(pend - pbegin)}, m_Capacity{m_Size + m_Size / 2}
    {
        m_Parray = allocate(m_Capacity);

        for (SizeType i = 0; i < m_Size; ++i)
            m_Parray[i] = pbegin[i];
    }
    Vector(constVectorIterator beg, constVectorIterator end) : m_Size{static_cast<SizeType>(end - beg)}, m_Capacity{m_Size + m_Size / 2}
    {
        m_Parray = allocate(m_Capacity);

        SizeType i = 0;
        while (beg != end)
            m_Parray[i++] = *beg++;
    }
    //--------------------------------------------------

    //--------------------------------------------------
    void reserve(SizeType new_cap)
    {
        m_Capacity = new_cap;
        reallocate(m_Capacity);
    }
    void shrink_to_fit()
    {
        m_Capacity = m_Size + m_Size / 2;
    }

    VectorIterator begin()
    {
        return VectorIterator{m_Parray};
    }
    constVectorIterator begin()const
    {
        return constVectorIterator{m_Parray};
    }
    constVectorIterator cbegin() const
    {
        return constVectorIterator{m_Parray};
    }
    VectorIterator end()
    {
        return VectorIterator{m_Parray + m_Size};
    }
    constVectorIterator end() const
    {
        return constVectorIterator{m_Parray + m_Size};
    }
    constVectorIterator cend() const
    {
        return constVectorIterator{m_Parray + m_Size};
    }

    VectorReverseIterator rbegin()
    {
        return static_cast<VectorReverseIterator>(VectorIterator{m_Parray + m_Size});
    }
    constVectorReverseIterator rbegin() const
    {
        return static_cast<constVectorReverseIterator>(constVectorIterator{m_Parray + m_Size});
    }
    constVectorReverseIterator crbegin() const
    {
        return static_cast<constVectorReverseIterator>(constVectorIterator{m_Parray + m_Size});
    }
    VectorReverseIterator rend()
    {
        return static_cast<VectorReverseIterator>(VectorIterator{m_Parray});
    }
    constVectorReverseIterator rend() const
    {
        return static_cast<constVectorReverseIterator>(constVectorIterator{m_Parray});
    }
    constVectorReverseIterator crend() const
    {
        return static_cast<constVectorReverseIterator>(constVectorIterator{m_Parray});
    }

    //--------------------------------------------------

    //--------------------------------------------------
    Vector &operator=(std::initializer_list<ValueType> ilist)
    {
        m_Size = ilist.size();

        SizeType idx = 0;
        for (auto iter : ilist)
            m_Parray[idx++] = iter;

        return *this;
    }
    void resize(SizeType newSize, constReferenceType val = 0)
    {
        if (newSize < m_Size)
        {
            m_Size = newSize;
        }
        else if (newSize > m_Size && newSize <= m_Capacity)
        {
            for (SizeType i = m_Size; i < newSize; ++i)
                m_Parray[i] = val;

            m_Size = newSize;
        }
        else if (newSize > m_Capacity)
        {
            while (newSize > m_Capacity)
                reallocate(m_Capacity + m_Capacity / 2);

            for (SizeType i = m_Size; i < newSize; ++i)
                m_Parray[i] = val;

            m_Size = newSize;
        }
    }

    void assign(SizeType n, constReferenceType val)
    {
        delete[] m_Parray;

        m_Size = n;
        m_Capacity = m_Size + m_Size / 2;
        m_Parray = allocate(m_Capacity);

        for (SizeType i = 0; i < m_Size; ++i)
            m_Parray[i] = val;
    }
    void assign(const std::initializer_list<ValueType> ilist)
    {
        delete[] m_Parray;

        m_Size = ilist.size();
        m_Capacity = m_Size + m_Size / 2;
        m_Parray = allocate(m_Capacity);

        SizeType idx = 0;
        for (auto iter : ilist)
            m_Parray[idx++] = iter;
    }
    void assign(constPointerType pbeg, constPointerType pend)
    {
        delete[] m_Parray;

        m_Size = static_cast<SizeType>(pend - pbeg);
        m_Capacity = m_Size + m_Size / 2;
        m_Parray = allocate(m_Capacity);

        for (SizeType idx = 0; idx < m_Size; ++idx)
            m_Parray[idx] = pbeg[idx];
    }

    VectorIterator insert(constVectorIterator where, constReferenceType value)
    {
        if (m_Size == m_Capacity)
            reallocate(m_Capacity + m_Capacity / 2);

        if (where == this->cend())
        {
            this->push_back(value);
            return static_cast<VectorIterator>(where);
        }

        ++m_Size;

        for (auto iter = this->end() - 2; iter != static_cast<VectorIterator>(where - 1); --iter)
            *(iter + 1) = *iter;
        *(static_cast<VectorIterator>(where)) = value;

        return static_cast<VectorIterator>(where);
    }
    VectorIterator insert(constVectorIterator where, RReferenceType value)
    {
        if (m_Size == m_Capacity)
            reallocate(m_Capacity + m_Capacity / 2);

        if (where == this->cend())
        {
            this->push_back(std::move(value));
            return static_cast<VectorIterator>(where);
        }

        ++m_Size;

        for (auto iter = this->end() - 2; iter != static_cast<VectorIterator>(where - 1); --iter)
            *(iter + 1) = *iter;
        *(static_cast<VectorIterator>(where)) = std::move(value);

        return static_cast<VectorIterator>(where);
    }
    VectorIterator insert(constVectorIterator where, SizeType count, constReferenceType value)
    {
        std::ptrdiff_t diff = where - this->cbegin();

        if (m_Size + count > m_Capacity)
        {
            while (m_Size + count > m_Capacity)
                reallocate(m_Capacity + m_Capacity / 2);
            where = constVectorIterator{this->cbegin() + diff};
        }

        if (where == this->cend())
        {
            while (count--)
                this->push_back(value);
            return static_cast<VectorIterator>(where);
        }

        m_Size += count;

        for (auto iter = this->end() - 1 - count; iter != static_cast<VectorIterator>(where - 1); --iter)
            *(iter + count) = *iter;

        for (SizeType n = 0; n < count; ++n)
            *static_cast<VectorIterator>(where + n) = value;

        return static_cast<VectorIterator>(where);
    }
    VectorIterator insert(constVectorIterator where, VectorIterator source_beg, VectorIterator source_end)
    {
        std::ptrdiff_t diff = where - this->cbegin();
        std::ptrdiff_t count = source_end - source_beg;

        if (m_Size + count > m_Capacity)
        {
            while (m_Size + count > m_Capacity)
                reallocate(m_Capacity + m_Capacity / 2);
            where = constVectorIterator{this->cbegin() + diff};
        }

        if (where == this->cend())
        {
            while (source_beg != source_end)
                this->push_back(*source_beg++);
            return static_cast<VectorIterator>(where);
        }

        m_Size += count;

        for (auto iter = this->end() - 1 - count; iter != static_cast<VectorIterator>(where - 1); --iter)
            *(iter + count) = *iter;

        for (SizeType n = 0; n < count; ++n)
            *static_cast<VectorIterator>(where + n) = *source_beg++;

        return static_cast<VectorIterator>(where);
    }
    VectorIterator insert(constVectorIterator where, std::initializer_list<ValueType> ilist)
    {
        std::ptrdiff_t diff = where - this->cbegin();
        std::ptrdiff_t count = ilist.size();

        if (m_Size + count > m_Capacity)
        {
            while (m_Size + count > m_Capacity)
                reallocate(m_Capacity + m_Capacity / 2);
            where = constVectorIterator{this->cbegin() + diff};
        }

        if (where == this->cend())
        {
            for (auto iter : ilist)
                this->push_back(iter);
            return static_cast<VectorIterator>(where);
        }

        m_Size += count;

        for (auto iter = this->end() - 1 - count; iter != static_cast<VectorIterator>(where - 1); --iter)
            *(iter + count) = *iter;

        SizeType n = 0;
        for (auto iter : ilist)
            *static_cast<VectorIterator>(where + n++) = iter;

        return static_cast<VectorIterator>(where);
    }

    VectorIterator erase(VectorIterator where)
    {
        VectorIterator temp_where = where;
        if (where == this->end())
            return this->end();

        for (VectorIterator iter = temp_where + 1; iter != this->end(); ++iter)
            *temp_where++ = *iter;

        --m_Size;
        return where;
    }
    VectorIterator erase(VectorIterator beg, VectorIterator end)
    {
        if (beg == end)
            return end;

        if (end == this->end())
        {
            m_Size = beg - this->begin();
            return beg;
        }

        VectorIterator temp_beg = beg;
        for (auto iter = end; iter != this->end(); ++iter)
            *temp_beg++ = *iter;

        m_Size = temp_beg - this->begin();

        return beg;
    }

    template <class... Args>
    VectorIterator emplace(constVectorIterator where, Args &&...args)
    {
        if (m_Size == m_Capacity)
            reallocate(m_Capacity + m_Capacity / 2);

        if (where == this->cend())
        {
            emplace_back(ValueType{std::forward<Args>(args)...});
            return static_cast<VectorIterator>(where);
        }

        ++m_Size;

        for (auto iter = this->end() - 2; iter != static_cast<VectorIterator>(where - 1); --iter)
            *(iter + 1) = *iter;
        *(static_cast<VectorIterator>(where)) = ValueType{std::forward<Args>(args)...};

        return static_cast<VectorIterator>(where);
    }

    template <class... Args>
    ReferenceType emplace_back(Args &&...args)
    {
        if (m_Size == m_Capacity)
            reallocate(m_Capacity + m_Capacity / 2);
        m_Parray[m_Size++] = ValueType{std::forward<Args>(args)...};

        return *(m_Parray + m_Size);
    }

    void push_back(constReferenceType val)
    {
        if (m_Size == m_Capacity)
            reallocate(m_Capacity + m_Capacity / 2);
        m_Parray[m_Size++] = val;
    }
    void push_back(RReferenceType val)
    {
        if (m_Size == m_Capacity)
            reallocate(m_Capacity + m_Capacity / 2);
        m_Parray[m_Size++] = std::move(val);
    }
    void pop_pack()
    {
        if (m_Size != 0)
            --m_Size;
    }

    void swap(Vector &other)
    {
        ::swap(m_Size, other.m_Size);
        ::swap(m_Capacity, other.m_Capacity);
        ::swap(m_Parray, other.m_Parray);
    }
    void clear()
    {
        m_Size = 0;
    }
    //--------------------------------------------------

    //--------------------------------------------------
    ReferenceType front()
    {
        return *m_Parray;
    }
    constReferenceType front() const
    {
        return *m_Parray;
    }
    ReferenceType back()
    {
        return *(m_Parray + m_Size - 1);
    }
    constReferenceType back() const
    {
        return *(m_Parray + m_Size - 1);
    }
    ReferenceType operator[](SizeType idx)
    {
        return *(m_Parray + idx);
    }
    constReferenceType operator[](SizeType idx) const
    {
        return *(m_Parray + idx);
    }
    PointerType data()
    {
        return m_Parray;
    }
    constPointerType data() const
    {
        return m_Parray;
    }

    ReferenceType at(SizeType idx)
    {
        if (idx > m_Size)
            throw std::out_of_range{"Gecersiz index\n"};

        return *(m_Parray + idx);
    }
    constReferenceType at(SizeType idx) const
    {
        if (idx > m_Size)
            throw std::out_of_range{"Gecersiz index\n"};

        return *(m_Parray + idx);
    }
    //--------------------------------------------------

    //--------------------------------------------------
    SizeType max_size() const noexcept
    {
        return MAX_SIZE;
    }
    SizeType capacity() const
    {
        return m_Capacity;
    }
    SizeType size() const
    {
        return m_Size;
    }
    bool empty() const
    {
        return m_Size == 0;
    }
    //--------------------------------------------------

    //--------------------------------------------------
    friend std::ostream &operator<<(std::ostream &os, const Vector &vec)
    {
        for (SizeType i = 0; i < vec.m_Size; ++i)
            os << vec.m_Parray[i] << "  ";
        os << "\n=======================================\n";
        return os;
    }

    class VectorIterator
    {
        PointerType m_Ptr = nullptr;

    public:
        VectorIterator() = default;
        VectorIterator(PointerType ptr) : m_Ptr{ptr} {}

        ReferenceType operator*()
        {
            return *m_Ptr;
        }
        ReferenceType operator[](int n)
        {
            return *(m_Ptr + n);
        }
        PointerType operator->()
        {
            return m_Ptr;
        }

        VectorIterator &operator++()
        {
            ++m_Ptr;
            return *this;
        }
        VectorIterator operator++(int)
        {
            VectorIterator temp = *this;
            ++(*this);
            return temp;
        }
        VectorIterator &operator--()
        {
            --m_Ptr;
            return *this;
        }
        VectorIterator operator--(int)
        {
            VectorIterator temp = *this;
            --(*this);
            return temp;
        }
        std::ptrdiff_t operator-(VectorIterator other) const
        {
            return m_Ptr - other.m_Ptr;
        }
        VectorIterator operator+(int n)
        {
            VectorIterator temp = *this;
            temp.m_Ptr += n;
            return temp;
        }
        VectorIterator operator-(int n)
        {
            VectorIterator temp = *this;
            temp.m_Ptr -= n;
            return temp;
        }
        VectorIterator &operator+=(int n)
        {
            m_Ptr += n;
            return *this;
        }
        VectorIterator &operator-=(int n)
        {
            m_Ptr -= n;
            return *this;
        }

        bool operator<(VectorIterator other) const
        {
            return m_Ptr < other.m_Ptr;
        }
        bool operator==(VectorIterator other) const
        {
            return !(*this < other || other < *this);
        }
        bool operator<=(VectorIterator other) const
        {
            return *this < other || *this == other;
        }
        bool operator>(VectorIterator other) const
        {
            return other < *this;
        }
        bool operator>=(VectorIterator other) const
        {
            return other < *this || other == *this;
        }
        bool operator!=(VectorIterator other) const
        {
            return *this < other || other < *this;
        }
        operator constVectorIterator() const
        {
            return m_Ptr;
        }
    };

    class constVectorIterator
    {
        constPointerType m_Ptr = nullptr;

    public:
        constVectorIterator() = default;
        constVectorIterator(PointerType ptr) : m_Ptr{ptr} {}

        constVectorIterator &operator++()
        {
            ++m_Ptr;
            return *this;
        }
        constVectorIterator operator++(int)
        {
            constVectorIterator temp = *this;
            ++(*this);
            return temp;
        }
        constVectorIterator &operator--()
        {
            --m_Ptr;
            return *this;
        }
        constVectorIterator operator--(int)
        {
            constVectorIterator temp = *this;
            --(*this);
            return temp;
        }
        constReferenceType operator*()
        {
            return *m_Ptr;
        }
        constReferenceType operator[](int n)
        {
            return *(m_Ptr + n);
        }
        constPointerType operator->()
        {
            return m_Ptr;
        }

        std::ptrdiff_t operator-(constVectorIterator other) const
        {
            return m_Ptr - other.m_Ptr;
        }
        constVectorIterator operator+(int n)
        {
            constVectorIterator temp = *this;
            temp.m_Ptr += n;
            return temp;
        }
        constVectorIterator operator-(int n)
        {
            constVectorIterator temp = *this;
            temp.m_Ptr -= n;
            return temp;
        }
        constVectorIterator &operator+=(int n)
        {
            m_Ptr += n;
            return *this;
        }
        constVectorIterator &operator-=(int n)
        {
            m_Ptr -= n;
            return *this;
        }

        bool operator<(constVectorIterator other) const
        {
            return m_Ptr < other.m_Ptr;
        }
        bool operator==(constVectorIterator other) const
        {
            return !(*this < other || other < *this);
        }
        bool operator<=(constVectorIterator other) const
        {
            return *this < other || *this == other;
        }
        bool operator>(constVectorIterator other) const
        {
            return other < *this;
        }
        bool operator>=(constVectorIterator other) const
        {
            return other < *this || other == *this;
        }
        bool operator!=(constVectorIterator other) const
        {
            return *this < other || other < *this;
        }
        explicit operator VectorIterator() const
        {
            return const_cast<PointerType>(m_Ptr);
        }
    };

    class VectorReverseIterator
    {
    protected:
        VectorIterator current;

    public:
        VectorReverseIterator() = default;
        explicit VectorReverseIterator(VectorIterator Iter) : current{Iter} {}
        VectorReverseIterator(const VectorReverseIterator &RIter) : current{RIter.current} {}

        VectorIterator base() const
        {
            return current;
        }
        ReferenceType operator*() const
        {
            VectorIterator temp{current};
            return *--temp;
        }
        PointerType operator->() const
        {
            VectorIterator temp{current};
            --temp;
            return temp.operator->();
        }
        VectorReverseIterator operator[](DifferenceType idx) const
        {
            return *(current - idx);
        }

        VectorReverseIterator &operator++()
        {
            --current;
            return *this;
        }
        VectorReverseIterator operator++(int)
        {
            VectorReverseIterator temp{*this};
            --current;
            return temp;
        }

        VectorReverseIterator &operator--()
        {
            ++current;
            return *this;
        }

        VectorReverseIterator operator--(int)
        {
            VectorReverseIterator temp{*this};
            ++current;
            return temp;
        }

        VectorReverseIterator operator+(DifferenceType n) const
        {
            return VectorReverseIterator{current - n};
        }
        VectorReverseIterator operator-(DifferenceType n) const
        {
            return VectorReverseIterator{current + n};
        }

        VectorReverseIterator &operator+=(DifferenceType n)
        {
            current -= n;
            return *this;
        }

        VectorReverseIterator &operator-=(DifferenceType n)
        {
            current += n;
            return *this;
        }
        bool operator<(VectorReverseIterator other) const
        {
            return current < other.current;
        }
        bool operator==(VectorReverseIterator other) const
        {
            return !(*this < other || other < *this);
        }
        bool operator<=(VectorReverseIterator other) const
        {
            return *this < other || *this == other;
        }
        bool operator>(VectorReverseIterator other) const
        {
            return other < *this;
        }
        bool operator>=(VectorReverseIterator other) const
        {
            return other < *this || other == *this;
        }
        bool operator!=(VectorReverseIterator other) const
        {
            return *this < other || other < *this;
        }
        operator constVectorReverseIterator() const
        {
            return current;
        }
    };

    class constVectorReverseIterator
    {
    protected:
        constVectorIterator current;

    public:
        constVectorReverseIterator() = default;
        explicit constVectorReverseIterator(constVectorIterator Iter) : current{Iter} {}
        constVectorReverseIterator(const constVectorReverseIterator &RIter) : current{RIter.current} {}

        constVectorIterator base() const
        {
            return current;
        }
        constReferenceType operator*() const
        {
            constVectorIterator temp{current};
            return *--temp;
        }
        constPointerType operator->() const
        {
            constVectorIterator temp{current};
            --temp;
            return temp.operator->();
        }
        constVectorReverseIterator operator[](DifferenceType idx) const
        {
            return *(current - idx);
        }

        constVectorReverseIterator &operator++()
        {
            --current;
            return *this;
        }
        constVectorReverseIterator operator++(int)
        {
            constVectorReverseIterator temp{*this};
            --current;
            return temp;
        }

        constVectorReverseIterator &operator--()
        {
            ++current;
            return *this;
        }

        constVectorReverseIterator operator--(int)
        {
            constVectorReverseIterator temp{*this};
            ++current;
            return temp;
        }

        constVectorReverseIterator operator+(DifferenceType n) const
        {
            return constVectorReverseIterator{current - n};
        }
        constVectorReverseIterator operator-(DifferenceType n) const
        {
            return constVectorReverseIterator{current + n};
        }

        constVectorReverseIterator &operator+=(DifferenceType n)
        {
            current -= n;
            return *this;
        }

        constVectorReverseIterator &operator-=(DifferenceType n)
        {
            current += n;
            return *this;
        }
        bool operator<(constVectorReverseIterator other) const
        {
            return current < other.current;
        }
        bool operator==(constVectorReverseIterator other) const
        {
            return !(*this < other || other < *this);
        }
        bool operator<=(constVectorReverseIterator other) const
        {
            return *this < other || *this == other;
        }
        bool operator>(constVectorReverseIterator other) const
        {
            return other < *this;
        }
        bool operator>=(constVectorReverseIterator other) const
        {
            return other < *this || other == *this;
        }
        bool operator!=(constVectorReverseIterator other) const
        {
            return *this < other || other < *this;
        }
        explicit operator VectorReverseIterator() const
        {
            return static_cast<VectorIterator>(current);
        }
    };

private:
    SizeType m_Size = 0;
    SizeType m_Capacity = 5;
    PointerType m_Parray = nullptr;

    PointerType allocate(SizeType cap)
    {
        PointerType ptr;

        try
        {
            ptr = new ValueType[cap];
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Hata yakalandi : " << e.what() << '\n';
            std::terminate();
        }

        return ptr;
    }

    void reallocate(SizeType newCapacity)
    {
        PointerType newBlock = allocate(newCapacity);

        for (SizeType i = 0; i < m_Size; ++i)
            newBlock[i] = m_Parray[i];

        m_Capacity = newCapacity;
        m_Parray = newBlock;
        newBlock = nullptr;
    }
};

template <typename T>
bool operator<(const Vector<T> &t1, const Vector<T> &t2)
{
    if (t1.size() < t2.size())
    {
        std::size_t i = 0;
        while (i < t1.size())
        {
            if (t1[i] != t2[i])
                return t1[i] < t2[i];
            ++i;
        }
        return 0;
    }
    std::size_t i = 0;
    while (i < t2.size())
    {
        if (t1[i] != t2[i])
            return t1[i] < t2[i];
        ++i;
    }
    return 0;
}

template <typename T>
bool operator==(const Vector<T> &t1, const Vector<T> &t2)
{
    return !(t1 < t2 || t2 < t1);
}

template <typename T>
bool operator!=(const Vector<T> &t1, const Vector<T> &t2)
{
    return t1 < t2 || t2 < t1;
}

template <typename T>
bool operator<=(const Vector<T> &t1, const Vector<T> &t2)
{
    return !(t2 < t1);
}
template <typename T>
bool operator>(const Vector<T> &t1, const Vector<T> &t2)
{
    return t2 < t1;
}
template <typename T>
bool operator>=(const Vector<T> &t1, const Vector<T> &t2)
{
    return !(t1 < t2);
}

template <typename T>
void swap(T &x, T &y)
{
    T temp;
    temp = x;
    x = y;
    y = temp;
}

template <typename T>
void swap(Vector<T> &x, Vector<T> &y)
{
    swap(x.m_Size, y.m_Size);
    swap(x.m_Capacity, y.m_Capacity);
    swap(x.m_Parray, y.m_Parray);
}

#endif