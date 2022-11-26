#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

// urand işlevi her çağrıldığında 0 - 100 arasında (100 dahil değil) rastgele bir sayi uretmeli:
// İşlev daha önce üettiği bir değeri tekrar üretmeyecek
// Bu durumda fonksiyon en cok URAND_MAX çağrılabilir.
// eger fonksiyon daha fazla kez cagrilirsa hata kodu olarak -1 döndürmeli

#define URAND_MAX 100

int urand(void)
{
    static int rand_flags[URAND_MAX] = {0};
    static int rand_cnt = 0;

    if (rand_cnt == URAND_MAX)
        return -1;

    int rand_val;
    // while (1)
    // {
    //     rand_val = rand() % URAND_MAX;

    //     if (rand_flags[rand_val] == 0)
    //     {
    //         rand_flags[rand_val] = 1;
    //         ++rand_cnt;
    //         break;
    //     }
    // }

    while (rand_flags[rand_val = rand() % URAND_MAX] != 0)
        ;
    rand_flags[rand_val] = 1;
    ++rand_cnt;

    return rand_val;
}

int main(void)
{
    randomize();

    int arr_rand[100];
    for (size_t i = 0; i < URAND_MAX; ++i)
        arr_rand[i] = urand();

    bubble_sort_int(arr_rand, 100);
    display_array_int(arr_rand, 100);
}