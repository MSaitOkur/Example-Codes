#ifndef SENTENCE_HPP
#define SENTENCE_HPP

#include <cstddef>
#include <cstdlib>
#include <cstring>

class Sentence
{
public:
    Sentence(const char *);
    Sentence(const Sentence &);
    Sentence(Sentence &&);
    Sentence &operator=(const Sentence &);
    Sentence &operator=(Sentence &&);

    ~Sentence();

    size_t length() const;
    void print() const;

private:
    std::size_t mlen;
    char *mptr;
};

#endif