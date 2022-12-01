class myclass
{
    A ax;
    B bx;
    C cx;

public:
    myclass(myclass &r) : ax(r.ax), bx(r.bx), cx(r.cx) {}
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Date
{
public:
    Date() : md{1}, mm{1}, my{1900} {}
    Date(int day, int mon, int year) : md{day}, mm{mon}, my{year} {}

    Date(const Date &other) : md{other.md}, mm{other.mm}, my{other.my} {}
    //  This copy ctor will be implicitly declared defaulted if programmer doesn't write

    void print()
    {
        std::cout << md << "-" << mm << "-" << my << "\n";
    }

private:
    int md, mm, my;
};

int main()
{
    Date date1{6, 7, 2020};
    Date date2{date1};
    date1.print();
    date2.print();
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Date
{
public:
    Date() : md{1}, mm{1}, my{1900} {}

    Date(int day, int mon, int year) : md{day}, mm{mon}, my{year} {}

    Date(const Date &other) : md{other.md}, mm{other.mm}, my{other.my}
    {
        std::cout << "copy ctor called for the object at the address " << this << "\n";
        std::cout << "&other = " << &other << "\n";
    }

    void print()
    {
        std::cout << md << "-" << mm << "-" << my << "\n";
    }

private:
    int md, mm, my;
};

int main()
{
    Date date1{6, 7, 2020};
    Date date2{date1};

    std::cout << "&date1 = " << &date1 << "\n";
    std::cout << "&date2 = " << &date2 << "\n";

    date1.print();
    date2.print();
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <cstdlib>

class Sentence
{
public:
    Sentence(const char *p) : mlen{std::strlen(p)},
                              mptr{static_cast<char *>(std::malloc(mlen + 1))}
    {
        std::strcpy(mptr, p);
    }

    Sentence(Sentence &other) : mlen{other.mlen},
                                mptr{static_cast<char *>(std::malloc(mlen + 1))}
    {
        std::strcpy(mptr, other.mptr);
    }

    ~Sentence()
    {
        std::free(mptr);
    }

    size_t length() const
    {
        return mlen;
    }

    void print() const
    {
        std::cout << "(" << mptr << ")\n";
    }

private:
    size_t mlen; // yazının uzunluğu
    char *mptr;  // yazının tutulacağı dinamik ömürlü dizi adresi
};

void do_something(Sentence s)
{
    std::cout << "do_something called\n";
    s.print();
    std::cout << "do_something finished\n";
    getchar();
}

int main()
{

    Sentence s1{"bugun hava cok sicak"};

    std::cout << "uzunluk " << s1.length() << "\n";
    std::cout << "cumle : ";

    s1.print();

    do_something(s1);

    s1.print();
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/*  Bir sinif nesnesi hayata gelirken degerini, aynı türden başka bir sınıf nesnesinden alarak geldiginde Copy Ctor cagrilir.
        
        Myclass y;
        Myclass x1 = y; // copy ctor
        Myclass x2{y};  // copy ctor
        Myclass x3(y);  // copy ctor

 *  Fonksiyon parametreleri sinif nesnesi iken bu fonk.a yapilan cagrida parametre degiskeni icin Copy Ctor cagrilir.

        void func(Myclass);

        void foo(){
            Myclass m;
            func(m); // copy ctor
        }
 
 *  Fonksiyonlarda geri donus degeri turu sinif nesnesi ise bu durumda bir gecici nesne olusturulacak ve bu gecici nesne icin Copy Ctor cagrilir.

        Myclass f(){

            Myclass m;

            return m; // copy ctor
        }

 *  Eger Copy Ctoru derleyici yazarsa nonstatic, public, inline uye fonksiyon olarak yazar. Parametresi const T& tir. Eger ilgili
    sinifin sinif nesnesi elemanlari varsa o elemanlarinda copy ctor lari cagrilir.
        
        //=============================================================
        //=============================================================

        class A{};
        class B{};

        class Nec{
        public:
            Nec();
            ~Nec();
            Nec (const Nec &other): ax(other.ax), bx(other.bx), ival(other.ival) {}

        private:
            A ax;
            B bx;
            int ival;
        }

        //=============================================================
        //=============================================================

        #include<iostream>

        class Date {
        public:
            Date() : mday{1}, mmon{1}, myear {1990}{}
            Date(int d, int m, int y): mday{d}, mmon{m}, myear{y}{}
            void print()const 
            {
                std::cout << mday << "-" << mmon << "-" << myear << "\n";
            }
        private:
            int mday, mmon, myear;
            
        };


        int main()
        {
            Date d1{4, 10, 2020};
            d1.print(); 

            Date d2{d1};
            d2.print();
        }

        //=============================================================
        //=============================================================

        #include<iostream>

        class A {
        public:
            A()  { std::cout << "A default Ctor this : " << this << "\n"; }
            ~A() { std::cout << "A destructor this   : " << this << "\n"; }
            A(const A& other){ std::cout << "A copy ctor this : " << this << " &other : " << &other << "\n"; }

        private:
            
        };

        int main()
        {
            A a1{};
            A a2 = a1;

            std::cout << "&a1 = " << &a1 << "   &a2 = " << &a2 << "\n";

        }

        //=============================================================
        //=============================================================

 *  RAII : Resource Acqusition Is Initialization, Kaynak edinimi ilk deger verme yolu ile olur. Bu tur nesnelerde nesne hayata gelirken
    edinilen kaynak, nesnenin omru bitince geri verilmelidir.

 *  shallow copy (memberwise copy) : data memberlar karsilikli olarak kopyalanir.
 *  deep copy : Data memberlar karsilikli olarak degil. Pointer yada referans data memberlar varsa bunlarin gosterdikleri
               nesneler kopyalanir.
  
 *  Eger bir sinifta constructor ile kaynak edinimi varsa bu durumda copy ctor ile cagri durumu riskli olabilir.
    Cunku kaynaklar birbirine kopyalanmasi durumunda 2 nesne ayni kaynagi gosterir. Bu sebeple boyle durumlarda
    copy ctorun yaziliminda programcinin yazmasi daha uygundur. Shallow copy yerine deep copy yapilmalidir. 
 */
