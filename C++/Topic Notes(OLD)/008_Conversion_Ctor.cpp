/*
 *  Sinifin ozel uye fonksiyonu degildir.

        struct A { };

        int main()
        {
            int ival = 2;
            A ax = ival; // Gecersiz
        }

        //=============================================================
        //=============================================================

        #include<iostream>

        class Myclass{
        public:
            Myclass(){std::cout << "Myclass() called for this : " << this << "\n";}
            Myclass(int x){std::cout << "Myclass(int x ) called  x = " << x << " for this : " << this << "\n";}
            Myclass(const Myclass &other){std::cout << "Myclass(const Myclass&) called for this : " << this << " &other : " << &other << "\n";}
            Myclass& operator=(const Myclass &other){std::cout << "Myclass& operator=(const Myclass&) called for this: " << this << " &other : " << &other << "\n"; return *this;}
            // Myclass(Myclass&& other){std::cout << "Myclass(Myclass&&) for this : " << this << " &other : " << &other << "\n";}
            // Myclass& operator=(Myclass &&other){std::cout << "Myclass& operator=(Myclass&&)called for this : " << this << " &other : " << &other << "\n"; return *this;};
            ~Myclass(){std::cout << "~Myclass() called for this : " << this << "\n";}
        private:
            
        };


        int main()
        {
            std::cout << "main basliyor\n";
            
            int ival = 2;
            Myclass m = ival; // Gecerli

            std::getchar();
            m = 23;
            std::getchar();

            std::cout << "main devam ediyor.\n";
        }



 *  s
 * 
 * 
 * 
 * 
 */

//=============================================================
//=============================================================

#include<iostream>

class Myclass{
public:
    Myclass(){
        std::cout << "Myclass() called for this : " << this << "\n";
    }
    Myclass(int x){
        std::cout << "Myclass(int x) called  x = " << x << " for this : " << this << "\n";
    }
    Myclass(const Myclass &other){
        std::cout << "Myclass(const Myclass&) called for this : " << this << " &other : " << &other << "\n";
    }
    Myclass& operator=(
        const Myclass &other){std::cout << "Myclass& operator=(const Myclass&) called for this: " << this << " &other : " << &other << "\n"; return *this;
    }
    Myclass(Myclass&& other){
        std::cout << "Myclass(Myclass&&) for this : " << this << " &other : " << &other << "\n";
    }
    Myclass& operator=(Myclass &&other){
        std::cout << "Myclass& operator=(Myclass&&)called for this : " << this << " &other : " << &other << "\n"; return *this;
    }
    ~Myclass(){
        std::cout << "~Myclass() called for this : " << this << "\n";
    }
 private:
    
};


int main()
{
    std::cout << "main basliyor\n";
    
    int ival = 2;
    Myclass m = ival; // Gecerli

    std::getchar();
    m = 23;
    std::getchar();

    std::cout << "main devam ediyor.\n";
}
