#include <iostream>

int main()
{
    //=======================auto x = expression;======================================
    /*
     * auto x = expr;
     *  - expr. const T ise constluk duser(Kendisi const nesnelerde constluk duser)
     *  - expr. T& ise referanslik duser
     *  - expr. const T& ise constluk ve referanslik duser
     *  - expr. dizi ismi array to pointer conv. olur. Array to pointer conv'da pointer dusmez.
     *  - expr. const dizi ismi array to pointer conv. olur. Array to pointer conv'da constluk ve pointer dusmez.
     *  - expr. yazi ise array to pointer conv. olur. Array to pointer conv'da constluk ve pointer dusmez.
     *  - expr. fonksiyon adresi ise function to pointer conv. olur. x ifadenin turunu alir.
     */

    int ival1 = 321;
    const int cival1 = 4;
    auto t1 = ival1;        // auto yerine gelen tür int, t1’in türü int
    auto t2 = cival1;       // auto yerine gelen tür int, t2’nin türü int, auto x = expr da constluk düşer
    const auto t3 = cival1; // auto yerine gelen tür int, t3’ün türü const int

    int ival2 = 24;
    int &rival2 = ival2;
    const int &crival2 = ival2;
    auto t4 = rival2;  // auto yerine gelen tür int, t4’ün türü int, auto x = expr da referanslık düşer
    auto t5 = crival2; // auto yerine gelen tür int, t5’in türü int

    int ar1[10]{};
    const int ar2[10]{};
    auto t6 = ar1; // auto yerine gelen tür int*, t6’nın türü int* (array to poiter conversion’da pointer düşmez)
    auto t7 = ar2; // auto yerine gelen tür const int*, t7’nin türü const int *(array to poiter conversion’da constluk düşmez)

    auto t8 = "Sait"; // auto yerine gelen tür const char*, t8’in türü const char *(array to poiter conversion’da constluk düşmez)

    int foo(int, int);
    auto t9 = foo; // auto yerine gelen tür int(*)(int, int), t9'un türü int(*)(int, int) (function to pointer conversion)

    //================================================================================
    //=======================autp& x = expression=====================================
    /*
     * auto & x = expr;
     *  - Tur cikarimindan sonra x her zaman Lvalue referanstir.
     *  - expr. T turu ise {auto:T), {x:T&}
     *  - expr. const T ise {auto:const T}, {x:const T&}
     *  - expr. const T ise {auto:const T}, {x:const T&}
     *  - expr. Rvalue expr. ise error.(auto'dan once const var ise gecerli)
     *  - expr. bir dizi ismi ise array to pointer conv. olmaz. x dizinin tamamina referans olur.
     *  - expr. yazi ise array to pointer conv. olmaz. x yaziya referans olur. constluk dusmez.
     *  - expr. fonksiyon adresi ise function to pointer conv. olmaz. x fonksiyona referans olur.
     */

    int ival3 = 5;
    auto &t10 = ival3; // auto yerine gelen tür int, t10’un türü int&

    const int ival4 = 15;
    auto &t11 = ival4; // auto yerine gelen tür const int, t11’in türü const int&

    auto &x1 = 10;       // Gecersiz. Ilk deger veren ifade Lvalue ifade olmali.
    const auto &x2 = 10; // Gecerli. auto yerine gelen tur int, x2'nin turu const int&

    int ar3[5]{1, 2, 3, 4, 5};
    auto &t12 = ar3; // auto yerine gelen tür int[5], t12’nin türü int(&)[5], ar3 kullanilabilen her yerde t12 kullanilabilir.
    // int (&t12)[5] = ar3;
    t12[2] = 25;  // gecerli
    int *a = t12; // gecerli

    auto &t13{"ali"}; // auto yerine gelen tür const char[4], t13’ün türü const char(&)[4]
    // const char (&t13)[4]{"ali"};

    int func(int, int);
    auto t14 = func;  // auto yerine gelen tür int(*)(int, int), t14’ün türü int (*)(int, int)
    auto &t15 = func; // auto yerine gelen tür int(&)(int, int), t15’in türü int (&)(int, int)

    //==========auto&& x = expression(Forwarding(Universal) Reference)================

    auto &&t16 = 214; // auto yerine gelen tür int , t16’nın türü int &&
    // int &&t16 = 214;

    int ival4 = 132643;
    auto &&t17 = ival4; // auto yerine gelen tür int& , t17’nın türü int & && ==> int &
    // int& &&t17 = ival4; ======> int &t17 = ival4;

    int &&r = 20;
    auto &&t18 = std::move(r); // auto yerine gelen tur int&&, t18'in turu int&& && ==> int&&

    //================decltype(expr): expr isim ise===================================
    /*
     * decltype(operand) x = expr; ile yapilan tur cikariminda operand bir isim ise:
     *  - operand turu const T ise x'in turu const T (constluk dusmez)
     *  - operand turu T& ise x'in turu T& (referanslik dusmez)
     *  - operand turu dizi ismi ise array to pointer conv. olmaz. x'in turu dizinin turudur.
     *  - operand turu string literali ise array to pointer conv. olmaz. x'in turu string literalinin turudur.
     */
    const int ival5 = 546;
    decltype(ival5) t19 = 4; // const int

    int ar4[10]{};
    decltype(ar4) t20; // int[10]

    decltype("Ali") t21; // const char[4], ilk değer verme mecburi

    int ival6 = 5;
    int &rival6 = ival6;
    decltype(rival6) t22; // int&, ilk deger verme mecburi

    //=======decltype(expr): expr isim olmayan bir ifade ise=======
    /*
     * decltype(operand) x = expr; ile yapilan tur cikariminda operand isim olmayan bir ifade ise:
     *  - operand olan ifadenin deger kategorisi PRvalue ise x operand olan ifadenin turudur.
     *  - operand olan ifadenin deger kategorisi Lvalue ise x operand olan ifadenin turunun LValue referansidir.
     *  - operand olan ifadenin deger kategorisi Xvalue ise x operand olan ifadenin turunun RValue referansidir.
     *
     *  - operand olan ifade sizeof operatorunde oldugu gibi unevaluated contex'tir.
     *    Yani ifadedeki islem yapilmaz. Sadece tur icin bakilir.
     */

    // Eger decltype(expr) icin: expr'nin deger kategorisi PRvalue ise cikarim yapilacak tur dogrudan ifadenin türüdür.
    int ival7 = 2;
    decltype(ival7 + 32) ival8; // int

    // Eger decltype(expr) icin: expr'nin deger kategorisi Lvalue ise cikarim yapilacak tur,
    // ifadenin turunun Lvalue referansıdır.
    std::size_t ival9 = 5356;
    decltype(++ival9) ival10 = ival9; // std::size_t &

    // Eger decltype(expr) icin: expr'nin deger kategorisi Xvalue ise cikarim yapilacak tur,
    // ifadenin && turunden yani Rvalue referansı turundendir.

    int &&bar();
    decltype(bar()) xbar = 34; // int&&

    /* decltype icerisindeki ifadeler sizeof operatorunde oldugu gibi unevaluated context'tir.
     * Yani sadece tur bilgisine bakilir. Ifade isleme konulmaz. */
    int ival11 = 43;
    decltype(ival11++) ival12 = 24;
    std::cout << " ival11 " << ival11 << '\n';
}
