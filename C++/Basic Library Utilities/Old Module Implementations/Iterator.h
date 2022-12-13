#include <iostream>

struct Input_iterator_tag { };
struct Output_iterator_tag { };
struct Forward_iterator_tag : public Input_iterator_tag { };
struct Bidirectional_iterator_tag : public Forward_iterator_tag { };
struct Random_access_iterator_tag : public Bidirectional_iterator_tag { };

namespace std
{
    template <typename Category, typename T, typename Distance = ptrdiff_t, 
                                typename Pointer = T *, typename Reference = T &>
    struct iterator
    {
        typedef Category iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
    };
}

template <typename Container>
class Back_insert_iterator
{
protected:
    Container *container = nullptr;

public:
    using Iterator_category = Output_iterator_tag;
    using Value_type = void;
    using Difference_type = std::ptrdiff_t;
    using Pointer = void;
    using Reference = void;
    using Container_type = Container;

    Back_insert_iterator() noexcept = default;
    explicit Back_insert_iterator(Container &x) : container{&x} {}
    Back_insert_iterator &operator=(const typename Container::Value_type &value)
    {
        container->push_back(value);
        return *this;
    }
    Back_insert_iterator &operator=(typename Container::Value_type &&value)
    {
        container->push_back(std::move(value));
        return *this;
    }

    Back_insert_iterator &operator*()
    {
        return *this;
    }
    Back_insert_iterator &operator++()
    {
        return *this;
    }
    Back_insert_iterator operator++(int)
    {
        return *this;
    }
};

template <typename Container>
inline Back_insert_iterator<Container> Back_inserter(Container &x)
{
    return Back_insert_iterator<Container>{x};
}

template <class Container>
class Front_insert_iterator
{
protected:
    Container *container = nullptr;

public:
    using Iterator_category = Output_iterator_tag;
    using Value_type = void;
    using Difference_type = std::ptrdiff_t;
    using Pointer = void;
    using Reference = void;
    using Container_type = Container;

    Front_insert_iterator(Container &x) noexcept = default;
    explicit Front_insert_iterator(Container &x) : container{&x} {}

    Front_insert_iterator &operator=(const typename Container::Value_type &value)
    {
        container->push_front(value);
        return *this;
    }
    Front_insert_iterator &operator=(typename Container::Value_type &&value)
    {
        container->push_front(std::move(value));
        return *this;
    }
    Front_insert_iterator &operator*()
    {
        return *this;
    }
    Front_insert_iterator &operator++()
    {
        return *this;
    }
    Front_insert_iterator operator++(int)
    {
        return *this;
    }
};

template <typename Container>
inline Front_insert_iterator<Container> Front_inserter(Container &x)
{
    return Front_insert_iterator<Container>{x};
}

template <class Value>
class Istream_iterator
{
public:
    using Iterator_category = Input_iterator_tag;
    using Value_type = Value;
    using Difference_type = std::ptrdiff_t;
    using Pointer = const Value *;
    using Reference = const Value &;
    using char_type = char;

    Istream_iterator() = default;
    Istream_iterator(std::istream &is) : isptr{&is}
    {
        *isptr >> value;
    }
    Istream_iterator(const Istream_iterator &s) : isptr{s.isptr}, value{s.value} {}
    ~Istream_iterator() = default;
    Istream_iterator &operator=(const Istream_iterator &) = default;

    const Value_type &operator*() const
    {
        return value;
    }
    const Value_type *operator->() const
    {
        return &value;
    }
    Istream_iterator &operator++()
    {
        *isptr >> value;
        return *this;
    }
    Istream_iterator operator++(int)
    {
        Istream_iterator temp = *this;
        *isptr >> value;
        return temp;
    }

private:
    Value_type value = 0;
    std::istream *isptr = nullptr;
};

template <typename T>
inline bool operator==(const Istream_iterator<T> &x, const Istream_iterator<T> &y)
{
    return x.value == y.value && *(x.isptr) == *(y.isptr);
}

template <typename T>
inline bool operator!=(const Istream_iterator<T> &x, const Istream_iterator<T> &y)
{
    return !(x == y);
}

template <typename Type>
class Ostream_iterator
{
public:
    using Iterator_category = Output_iterator_tag;
    using Value_type = void;
    using Difference_type = std::ptrdiff_t;
    using Pointer = void;
    using Reference = void;
    using char_type = char;
    using ostream_type = std::ostream;

    ostreambuf_iterator() noexcept = default;
    Ostream_iterator(std::ostream &s) : optr{&s} {}
    Ostream_iterator(std::ostream &s, const char *delimiter) : optr{&s}, delim{delimiter} {}
    Ostream_iterator(const Ostream_iterator &os) : optr{os.optr}, delim{os.delim} {}
    ~Ostream_iterator() = default;
    Ostream_iterator &operator=(const Ostream_iterator &) = default;
    Ostream_iterator &operator=(const Type &value)
    {
        *optr << value;
        return *this;
    }
    Ostream_iterator &operator*()
    {
        return *this;
    }
    Ostream_iterator &operator++()
    {
        return *this;
    }
    Ostream_iterator &operator++(int)
    {
        return *this;
    }

private:
    std::ostream *optr = nullptr;
    const char *delim = nullptr;
};

