/* set sinifinin insert fonksiyonunun geri donus degeri asagidaki turdendir.
 *  
 *    std::pair<std::set<T>::iterator, bool>
 * 
 * Burada pair'in 2. elemani ekleme isleminin basari durumudur.
 *  - eklenmek istenen oge sette yoksa ekleme basarili olur ve true deger alir.
 *  - eklenmek istenen oge sette varsa ekleme basarisiz olur ve false deger alir.
 * 
 * pairin ilk elemani ise:
 *  - Eklenmek istenen oge sette varsa o ogenin setteki konumu
 *  - Eklenmek istenen oge sette yoksa o ogenin sete yerlestirildigi konum.
 *  - Yani kisacasi ogenin setteki konumudur.
 */

#include <iostream>
#include <set>
#include "nutility.hpp"
#include "date.hpp"

template <typename Container, typename Func>
void fill_set(Container &c, std::size_t n, Func f)
{
    while (c.size() < n)
        c.insert(f());
}

int main()
{
    std::set<Date> dset;
    fill_set(dset, 10, Date::random_date);

    Date dval = Date::random_date();
    std::cout << "eklenmek istenen oge : " << dval << "\n";
    
    // std::pair<std::set<Date>::iterator, bool> res = dset.insert(dval);
    auto res = dset.insert(dval);
    
    if (res.second)
        std::cout << "ekleme basarili, eklenen ogenin konumu: " << std::distance(dset.begin(),res.first) << "\n";
    else
        std::cout << "ekleme basarisiz, setteki ogenin konumu: " << std::distance(dset.begin(),res.first) << "\n";

} 

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* set'in iterator parametreli insert fonksiyonu bulunmaktadir. 
 *  iterator insert( const_iterator pos, const value_type& value );
 * - Bu fonksiyonda 1. parametredeki asil amac eklenecek degerin aranmaya baslanacagi konumdur.
 * - Yani dogrudan bu konuma ekle denilmemektedir.
 */