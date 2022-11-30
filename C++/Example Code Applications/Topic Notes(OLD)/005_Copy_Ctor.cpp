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


 * 
 * 
 * 
 * 
 * 
 *     
 */
