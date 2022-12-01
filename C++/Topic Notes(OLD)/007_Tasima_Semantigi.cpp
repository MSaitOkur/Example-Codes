/*
 *  Modern C++ oncesi en cok kullanilan terimlerden birisi "Big 3" idi. Bu ucluden birisi tanimlanirsa yuksek ihtimalle 
    diger ikiside tanimlanacak demektir.
    -   Destructor
    -   Copy Ctor
    -   Copy Assignment
 
 *  Modern C++ sonrasi bu terim "Big 5" oldu. Cunku dile tasima semantigi eklendi. 
    -   Destructor
    -   Copy Ctor
    -   Copy Assignment
    -   Move Ctor
    -   Move Assignment

 *  Hayati bitecek (baska bir kodun kullanma ihtimali olmayan) bir nesnenin kaynagini kopyalamak yerine onun kaynagi devralinir.
    Ancak kaynagi calinan nesnenin Dtor'u cagrildigina kaynagi geri veren kodun calismamasi saglanmalidir.
    -   Bir sinif nesnesi anlamina gelen ifade Rvalu bir ifade ise bu nesnenin kaynagi calinabilir. 
        Bu sekilde gereksiz kopyalamadan kacinilir.
    
 
 
 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 *
 */