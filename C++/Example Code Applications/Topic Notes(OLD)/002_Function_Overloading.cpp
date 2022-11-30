//=============================================================
//=======Function Overload Resolution==========================

/*
 1- İlk olarak candidate(aday, overload edilmis fonk.lar) listelenir. Hic yoksa error.

 2- Aday fonk.lardan asagidaki soruya cevap uygun cevap verenler yani viable(uygun) olanlar ayrilir. 
    Bu asamada bir tane viable fonk. olması arama surecini bitirir. Birden fazla ise 3. adıma
    gecilir.
    - Eger bu fonk. tek basina olsaydi fonk. cagrisi legal olur muydu?

 3- Bu asamada viable fonk.lardan best match bulunmaya calisilir. Arama kriteri 3 kategoridedir.
    Secilebilirlik onceligine gore yukaridan asagiya siralanmistir.

    3_1 - Standart Conversion: Veri Kaybı olması onemli bir kriter degildir. 
          En iyi eslesmeden en kotuye dogru sıralama asagideki gibidir.
            # Exact Match(Tam Uyum)
                * Ayni Tur
                * Lvalue to PRvalue Transformation
                * Const Conversion(T to const T)
                * Array to Pointer Conversion
                * Function to Pointer Conversion
            # Promotion(Yukseltme)
                * Integral Promotion(char to int)
                * float to double
            # Conversion(Donusum)
                * Kalan uygun fonksiyonlar arasinda tercih sirasi yukaridan asagiya onceliklidir.
                * Ancak kalan uygun fonksiyonlarin hepsi conversion statusunde ise ambiguity olur.
    
    3_2 - User Defined Conversion: Standart conversion statusunde viable fonk. yoksa bu kategoriye bakilir.
          Variyadik'in bir ust seviyesidir.
            -- Conversion Constructor
            -- Typecast Operator Functions
            -- Eger 3. asamada kalan viable fonk.larin hepsi user defined conv. statusunde ise ambiguity olur.
    
    3_3 - Secilebilirligi en dusuk olan kategori variyadik donusumlerdir. Bu kategoriye en son bakilir.
*/

/*
 * Parametreleri const overload edilmiş olan 2 fonksiyon arasında,
   seçim önceliği için gönderilen adresin const nesne adresi olmasına bakılır. 
   Eğer gönderilen argüman adresi const ise çağrılma önceliği const parametreli fonksiyondadır.
 * Sag taraf referansi const sol taraf referansina gore onceliklidir.(C++11)
    
    void func(int&);       //1
    void func(const int&); //2
    void func(int&&);      //3

    int main() {
        int x = 5623;
        const int y = x; 

        func(y);     // gecerli 2
        func(x);     // gecerli 1
        func(4356);  // gecerli 3
        func(x + 2); // gecerli 3
    }

 */

/*
    Eğer overload edilmiş fonksiyonlar birden fazla parametreye sahipse 
    argümanlardan en az biri için ilgili parametre değişkenine dönüşümün kalitesi daha iyi olacak,
    ancak kalan argümanlar için ilgili parametre değişkenlerine dönüşümün kalitesi 
    daha kötü olmayacak yani argümanlardaki dönüşümlerde en az bir tane dönüşümde üstün olup 
    diğerlerinde de en az eşit olmalıdır. Bu koşul sağlanmazsa sentaks hatasıdır.
*/