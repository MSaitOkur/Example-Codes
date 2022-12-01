/*
 *  Bir sinif nesnesine atama operatoru ile baska bir sinif nesnesi atanirsa bu durumda sinifin kopyalayan atama operator fonksiyonu cagrilir.

 *  Copy assignment bir sinifta mutlaka olmak zorundadir. Programci yazmazsa derleyici yazacaktir.
 
 *  Derleyicinin yazdigi copy assignment fonksiyonu public, non-static, inline uye fonksiyondur.

        class A{};
        class B{};

        class Nec{
        public:
            Nec& operator=(const Nec& other)
            {
                ax = other.ax;
                bx = other.bx;
                ival = other.ival;

                return *this;
            }
            
        private:
            A ax;
            B bx;
            int ival;
        };

*/
