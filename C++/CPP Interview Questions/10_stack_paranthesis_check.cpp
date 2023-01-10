#include <iostream>
#include <stack>
#include <string>

bool is_match(const std::string &s);
// Parametreye gelen arguman icerisinde parantezlerin uyumlu olup olmadigini test ediniz.
// Her acilan parantez "({[<" uyumlu bir sekilde kapanan parantez ile denk geliyorsa
// geri donus deger true, degilse false donecek.

// Algoritma basit, her acilan parantez ile karsilasildiginda stack'e push edilir.
// Karsilasilan ilk kapanan parantez stack'e en son push edilen parantez olmalidir.
// Bu kosul saglaniyorsa en ustteki eleman pop edilir. Saglanmiyorsa false dondurulur.
// Yazinin sonuna gelindiginde stack'in bos olmasi gerekmektedir.
// Bos degilse uyumsuzluk vardir.

int main()
{
    std::string sline;
    getline(std::cin, sline);

    if (is_match(sline))
        std::cout << "Evet parantezler uyumludur.\n";
    else
        std::cout << "Hayir parantezler uyumlu degildir.\n";
}