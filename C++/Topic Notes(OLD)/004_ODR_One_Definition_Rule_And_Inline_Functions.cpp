/* 
 *  C++'ta degiskenlerin, fonklarin, siniflarin bildirimi birden fazla kez yapilabilir. 
    Ancak tanimlarinin birden fazla kez yapilmasi ya sentaks hatasidir yada ub'dir. 
        - Ub durumunda derleyici sentaks hatasi verebilir yada vermeyebilir. 
 
 *  ODR'nin bazi istisnalari vardir.  
    -   User defined turlerin tanimi soz konusu oldugunda, eger farklı kaynak dosyalarda birden fazla tanim varsa ve bu tanimlar
        token-by-token aynı ise ODR ihlal edilmemis olur. Aynı kaynak dosyada birden fazla olursa sentaks hatasidir.
        Token-by-token demek bosluk karakterleri disinda hicbir karakter farkli olmamalidir demektir. 
        Bu yuzden siniflarin tanimi baslik dosyalarina konulur ki ODR ihlal edilmesin.
            
            // Header.cpp
            class A {
                int mx, my;
                void func(int);
            };

            // main.cpp
            #include<iostream>

            class A {

                int mx,    my;
                void func(int);
            };

            int main()
            {
                
            }
    -   Diger istisna ise tamplates konusu ile ilgilidir. Asagidaki sablonlarin tanimi token-by-token aynı ise
        ODR ihlal edilmemis olur.
        --  Fonksiyon sablonlari
        --  Sinif sablonlari
        --  Degisken sablonlari
        --  Typedef(Tur Es-isim) sablonlari
    
    -   Eger bir fonksiyon inline fonksiyon ise bu fonksiyonun tanımında kod token-by-token ayni ise ODR ihlal edilmemis olur.
        Asagideki kod hangi dosyada include edilirse edilsin ODR ihlal edilmemis olur. Inline degiskenler(C++17) icin de ayni durum gecerlidir.

            // Header.h
            inline int foo(int){
                //...
            }
            inline int x = 10; // C++17 ile dile eklenmistir.
 
 *  Derleyiciler bazen fonksiyon cagrilarinda optimizasyon yapmak ve daha verimli kod uretmek icin:
    -   Bir fonksiyon cagrisinda eger o fonksiyonun tanimini goruyorsa ve fonksiyona giris-cikis kodlarini uretmek yerine fonk.un kodunu aynen yerine koymak 
        daha verimli ise kodu aynen yerine yapistirir. Buna inline expansion denir. Ancak bunu yapabilmesi icin belirli kriterler vardir.
        --  Derleyicinin fonkun tanimini cagrinin yapildigi noktada gormesi gerekiyor.
        --  Derleyici analiz yapar. Eger kodu inline expand etmesi verimli degilse bu durumda bunu yapabilme sansi olmasina ragmen yapmaz.
        --  Fonksiyonun kodu kucuk olsa bile karmasik bir kod ise mesela recursive bir yapi yada nested loops varsa bu durumda derleyici zaten inline expand edemez.
 
 *  C++'ta bir fonksiyonun geri donus degeri turunun onune inline anahtar sozcugu getirilerek fonksiyonun tanımı yapilirsa buna inline fonksiyon denir.

        inline int foo(int x){
            return x * x + 10;
        }
 
 *  Bir fonksiyon inline olarak tanimlansa dahi cagri yapildiginda kodu inline olarak acma zorunlulugu yoktur. 
    Eger bir fonksiyon inline olarak tanımlanmasa dahi inline olarak acmamak sorunda degildir. Yani karar mercii derleyicidir.
    Inline fonksiyonlarin amaci inline olarak acilma olanagini vermektir. Ancak buna zorlanamaz. Bununla birlikte ODR ihlalini ortadan kaldirmaktir.
 
 *  Bir baslik dosyasinda tanimlanan class icinde, bir fonksiyon dogrudan tanimi ile yazilirsa bu fonksiyon inline'dir. inline keyword'u kullanılmasa bile.
    Yada ayni baslik dosyasi icinde class disinda inline olarak tanimlanabilir. Bu durumda bu baslik dosyasi kac tane dosya tarafindan include edilirse edilsin
    ODR ihlali ortadan kalkar. Non-static ve static uye fonksiyonlar sinifin icinde inline olarak tanimlanabilir. Yaygin convensiyon inline keywordunu kullanmamadir.

 */