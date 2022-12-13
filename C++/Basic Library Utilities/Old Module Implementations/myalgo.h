#ifndef MYALGOS
#define MYALGOS

#include<iosfwd>

template<typename InIter, typename OutIter>
OutIter Copy(InIter beg, InIter end, OutIter destbeg)
{
    while(beg != end)
        *destbeg++ = *beg++;
    
    return destbeg;
}


template<typename InIter, typename OutIter,  typename UnPred>
OutIter Copy_if(InIter beg, InIter end, OutIter obeg, UnPred f)
{
    while(beg != end){
        if(f(*beg))
            *obeg++ = *beg;
        beg++;
    }
    return obeg;
}

template<typename InIter, typename T>
std::size_t Count(InIter beg, InIter end, const T& t)
{
    std::size_t cnt{};

    while(beg != end){
        if(*beg == t)
            ++cnt;
        
        ++beg;
    }

    return cnt;
}


template<typename InIter, typename Pred>
std::size_t Count_if(InIter beg, InIter end, Pred F)
{
    std::size_t cnt{};

    while(beg != end){
        if(f(*beg))
            ++cnt,
        ++beg;
    }

    return cnt;
}

template<typename InIter, typename T>
InIter Find(InIter beg, InIter end, const T& tval)
{
    while(beg != end){
        if(*beg == tval)
            return beg;
        ++beg; 
    }

    return beg;
}

template<typename InIter, typename UnPred>
InIter Find_if(InIter beg, InIter end, UnPred f)
{
    while(beg != end) {
        if(f(*beg)
            return beg;
        ++beg;
    }

    return beg;
}

template<typename Iter, typename F>
F ForEach(Iter beg, Iter end, F f)
{
    while(beg != end)
        f(*beg++);
    
    return f;
}

template<typename InIter, typename OutIter, typename Func>
OutIter Transform(InIter beg, InIter end, OutIter destbeg, Func f)
{
    while(beg != end)
        *destbeg++ = f(*beg++);
        
    return destbeg;
}

template<typename InIter1, typename InIter2, typename OutIter, typename Func>
OutIter Transform(InIter1 beg1, InIter1 end1, InIter2 beg2, OutIter destbeg, Func f)
{
    while(beg1 != end1)
        *destbeg++ = f(*beg1++, *beg2++);

    return destbeg;
}

template<typename InIter, typename OutIter>
OutIter Reverse_Copy(InIter beg, InIter end, OutIter destbeg)
{
    while(beg != end)
        *destbeg++ = *--end;

    return destbeg;
}


#endif