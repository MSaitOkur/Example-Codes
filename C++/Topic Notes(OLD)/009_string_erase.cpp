#include <iostream>
#include <string>
#include<cstdlib>
#include<cctype>


int main()
{
	std::string s;
	std::cout << "bir yazi giriniz: ";
	std::getline(std::cin, s);

	std::cout << "[" << s.length() << "] [" << s.capacity() << "] [" << s << "]\n";

//	Yazının ilk karakterini silin.
	// s.erase(0,1);
	// s.erase(s.begin());
	// s.erase(s.begin(), s.begin() + 1);

//	Yazının son karakterini silin.
	// s.erase(s.size()-1);
	// s.erase(s.size()-1 , 1);
	// s.erase(s.end() - 1);
	// s.erase(s.end() - 1, s.end());
	// s.pop_back();
	
//	Yazının ilk ve son karakterleri dışında tüm karakterlerini silin.
	// s.erase(1,s.size() - 2);
	// s.erase(s.begin() + 1, s.end() - 1);

//	Yazının ikinci karakterini silin.
	// s.erase(1, 1);
	// s.erase(s.begin() + 1);
	// s.erase(s.begin() + 1, s.begin() + 2);

	
//	Yazının sondan ikinci karakterini silin.
	// s.erase(s.size() - 2, 1);
	// s.erase(s.end()-2, s.end()-1);

//	idx yazının geçerli bir indeksi olmak üzere yazının *idx* indisli karakterini silin.
	// std::size_t idx = 3;
	// s.erase(idx, 1);

//	Yazıdaki ilk a karakterini silin.
	// s.erase(s.find('a'), 1);

//	Yazıdaki son a karakterini silin.
	// s.erase(s.rfind('a'), 1);

//	Yazıdaki tüm a karakterlerini silin.
	// std::size_t c{};
	// while(( c = s.find('a')) != std::string::npos)
	// 	s.erase(c, 1);

//	Yazıdaki ilk a karakteri ile başlayan ve son a karakteri ile biten yazıyı silin.
	// std::size_t c = s.find('a');
	// s.erase(c, s.rfind('a') - c + 1);

//	Yazıdaki ilk a karakterinden önce gelen ve sonra gelen 2 karakteri silin.
	// std::size_t c = s.find('a');
	// s.erase(c - 1, 1);
	// s.erase(c, 1);

	// s.erase(s.find('a') - 1, 1);
	// s.erase(s.find('a') + 1, 1);

//	Yazıda bulunan ilk "kan" yazısını silin
	// s.erase(s.find("kan"), 3);

//	Yazıda bulunan son "kan" yazısını silin
	// s.erase(s.rfind("kan"), 3);

//	Yazıda bulunan tüm "kan" yazılarını silin
	// std::size_t idx{};
	// while((idx = s.find("kan")) != std::string::npos)
	// 	s.erase(idx, 3);

//	Yazıda bulunan ilk rakam karakterini silin
	// s.erase(s.find_first_of("0123456789"), 1);

//	Yazıda bulunan son rakam karakterini silin
	// s.erase(s.find_last_of("0123456789"), 1);

//	Yazıdaki tüm rakam karakterlerini silin.
	// std::size_t c{};
	// while((c = s.find_first_of("0123456789")) != std::string::npos)
	// 	s.erase(c, 1);

//	Yazının ilk karakteri ile son karakteri aynı ise bunları silin.
	// if(s.at(0) == s.at(s.size() - 1)){
	// 	s.erase(0,1);
	// 	s.pop_back();
	// }

//	Yazının ilk 3 karakteri ile son 3 karakteri aynı ise bunları silin.
	// if(s.substr(0,3) == s.substr(s.size() - 3)){
	// 	s.erase(0,3);
	// 	s.erase(s.size() - 3, 3);
	// }	

//	Yazıdaki ardışık eşit karakterlerden sadece bir tane kalacak şekilde silme işlemi yapın. (unique)
	// for(std::size_t i = 0; i < s.size();)
	// 	if(s[i] == s[i+1])
	// 		s.erase(i,1);
	// 	else
	// 		++i;

//	Yazıdaki tüm boşluk (whitespace) karakterlerini silin.
	// while(std::size_t c = s.find(' ')){
	// 	if(c != std::string::npos)
	// 		s.erase(c,1);
	// 	else
	// 		break;
	// }	

	std::cout << "[" << s.length() << "] [" << s.capacity() << "] [" << s << "]\n";

}

