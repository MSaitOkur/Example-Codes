#include "nutility.hpp"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iterator>

namespace
{
	std::mt19937 &urng()
	{
		static std::mt19937 eng{std::random_device{}()};

		return eng;
	};
}
//--------------------------------------------------
//--------------------------------------------------
int Irand::operator()()
{
	return m_dist(urng());
}
//--------------------------------------------------
//--------------------------------------------------
double Drand::operator()()
{
	return m_dist(urng());
}
//--------------------------------------------------
//--------------------------------------------------
std::string rname()
{
	const char *const pnames[] = {
		"abdi",
		"abdullah",
		"abdulmuttalip",
		"adem",
		"adnan",
		"afacan",
		"agah",
		"ahmet",
		"akin",
		"alev",
		"ali",
		"alican",
		"alparslan",
		"anil",
		"arda",
		"asim",
		"askin",
		"aslican",
		"aslihan",
		"ata",
		"atakan",
		"atalay",
		"atif",
		"atil",
		"aycan",
		"aydan",
		"aykut",
		"ayla",
		"aylin",
		"aynur",
		"ayse",
		"aytac",
		"aziz",
		"azize",
		"azmi",
		"baran",
		"bekir",
		"belgin",
		"bennur",
		"beril",
		"berivan",
		"berk",
		"beste",
		"beyhan",
		"bilal",
		"bilge",
		"bilgin",
		"billur",
		"binnaz",
		"binnur",
		"birhan",
		"bora",
		"bulent",
		"burak",
		"burhan",
		"busra",
		"cahide",
		"cahit",
		"can",
		"canan",
		"candan",
		"caner",
		"cansu",
		"cebrail",
		"celal",
		"celik",
		"cem",
		"cemal",
		"cemil",
		"cemile",
		"cemre",
		"cengiz",
		"cesim",
		"cetin",
		"ceyda",
		"ceyhan",
		"ceyhun",
		"ceylan",
		"cezmi",
		"cihan",
		"cihat",
		"ciler",
		"cumhur",
		"cuneyt",
		"demet",
		"demir",
		"deniz",
		"derin",
		"derya",
		"devlet",
		"devrim",
		"diana",
		"dilber",
		"dilek",
		"dogan",
		"dost",
		"durmus",
		"durriye",
		"ece",
		"eda",
		"edip",
		"ediz",
		"efe",
		"efecan",
		"ege",
		"egemen",
		"emine",
		"emirhan",
		"emre",
		"emrecan",
		"enes",
		"engin",
		"erkan",
		"ercument",
		"erdem",
		"esen",
		"esin",
		"esra",
		"eylul",
		"fadime",
		"fahri",
		"fazilet",
		"feramuz",
		"feraye",
		"ferhat",
		"ferhunde",
		"figen",
		"fikret",
		"fuat",
		"fugen",
		"furkan",
		"galip",
		"garo",
		"gazi",
		"gizem",
		"gul",
		"gulden",
		"gulsah",
		"gulsen",
		"gunay",
		"gurbuz",
		"gursel",
		"hakan",
		"hakki",
		"haldun",
		"halime",
		"haluk",
		"handan",
		"hande",
		"handesu",
		"hasan",
		"helin",
		"hikmet",
		"hilal",
		"hilmi",
		"hulki",
		"hulusi",
		"hulya",
		"huseyin",
		"iffet",
		"irmak",
		"ismail",
		"izzet",
		"jade",
		"julide",
		"kaan",
		"kamil",
		"kamile",
		"kasim",
		"kaya",
		"kayahan",
		"kayhan",
		"kazim",
		"kelami",
		"kenan",
		"kerem",
		"kerim",
		"keriman",
		"kezban",
		"korhan",
		"kunter",
		"kurthan",
		"lale",
		"lamia",
		"leyla",
		"mahir",
		"malik",
		"mehmet",
		"melek",
		"melih",
		"melike",
		"melisa",
		"menekse",
		"mert",
		"metin",
		"mucahit",
		"muhammed",
		"muhsin",
		"mukerrem",
		"murat",
		"murathan",
		"muruvvet",
		"muslum",
		"mustafa",
		"muzaffer",
		"naci",
		"naciye",
		"nagehan",
		"nahit",
		"nalan",
		"nasrullah",
		"naz",
		"nazif",
		"nazife",
		"nazli",
		"necmettin",
		"necmi",
		"necmiye",
		"nedim",
		"nefes",
		"nevsin",
		"nihal",
		"nihat",
		"nisan",
		"niyazi",
		"nurdan",
		"nuri",
		"nuriye",
		"nurullah",
		"nusret",
		"okan",
		"olcay",
		"onat",
		"orkun",
		"osman",
		"pakize",
		"papatya",
		"pelin",
		"pelinsu",
		"perihan",
		"petek",
		"pinat",
		"polat",
		"polathan",
		"poyraz",
		"recep",
		"refik",
		"refika",
		"rumeysa",
		"rupen",
		"saadet",
		"sabriye",
		"sade",
		"sadegul",
		"sadettin",
		"sadi",
		"sadiye",
		"sadri",
		"sadullah",
		"samet",
		"sami",
		"saniye",
		"sarp",
		"sefa",
		"sefer",
		"selenay",
		"selin",
		"semsit",
		"sevda",
		"sevilay",
		"sevim",
		"seyhan",
		"sezai",
		"sezen",
		"sezer",
		"sidre",
		"sinem",
		"soner",
		"su",
		"suheyla",
		"suleyman",
		"sumeyye",
		"suphi",
		"taci",
		"taner",
		"tanju",
		"tansel",
		"tansu",
		"tarcan",
		"tarik",
		"tarkan",
		"tayfun",
		"tayyar",
		"tayyip",
		"tekin",
		"temel",
		"teoman",
		"teslime",
		"tevfik",
		"tijen",
		"tonguc",
		"tufan",
		"tugay",
		"tugra",
		"tunc",
		"tuncer",
		"turgut",
		"turhan",
		"ufuk",
		"ugur",
		"umit",
		"utku",
		"yalcin",
		"yasar",
		"yasemin",
		"yasin",
		"yavuz",
		"yelda",
		"yeliz",
		"yesim",
		"yilmaz",
		"yunus",
		"yurdagul",
		"yurdakul",
		"yurdanur",
		"yusuf",
		"zahide",
		"zahit",
		"zarife",
		"zekai",
		"zeliha",
		"zerrin",
		"ziya",
		"zubeyde"};

	return pnames[Irand(0, std::size(pnames) - 1)()];
}
//--------------------------------------------------
//--------------------------------------------------
std::string rfname()
{
	static const char *const pfnames[] = {
		"acar", "acgoze", "acuka", "ademoglu", "adiguzel", "agaoglu", "akarsu", "akcalar", "akgunes", "akkay",
		"akkuyu", "aklikit", "aksakal", "akyildiz", "akyoldas", "alemdar", "alniacik", "altindag", "altinisik", "altinorak",
		"arcan", "aslan", "avci", "aybeyaz", "aylak", "azmak", "bahceli", "bakirci", "baklavaci", "barutcu",
		"baturalp", "bayraktar", "bekar", "belgeli", "beyaz", "bilgic", "bozkaya", "boztas", "canbay", "candamar",
		"cangoz", "cankoc", "canlikaya", "cansever", "cansiz", "celik", "celiker", "cengaver", "cevikkol", "cilingir",
		"comakci", "corbaci", "cubukay", "cuhadar", "daglarca", "damar", "degirmenci", "demirdogen", "demirel", "derin",
		"dingin", "dokmeci", "dokuzcan", "dosteli", "dumbuk", "dunyalik", "ecevit", "edepli", "edepsiz", "efelik",
		"elebasi", "eliagir", "elibol", "elitemiz", "elkizi", "elmali", "eloglu", "emirkulu", "engerek", "engereke",
		"erdogan", "erdogan", "ergin", "erim", "ersoy", "ertakan", "esbereli", "esnedur", "esteberli", "etci", "ezergecer",
		"fakir", "fedai", "fincan", "firatonu", "fitrat", "gamsiz", "gedik", "geldik", "gilgamis", "girik",
		"girit", "gucsuz", "gultekin", "gumus", "gurkas", "hamsikoylu", "harmanci", "haselici", "hepguler", "hurmaci",
		"iliksiz", "issiz", "jilet", "kabasakal", "kadersiz", "kahraman", "kalemsiz", "kalinkas", "kalpsiz", "kalpten",
		"kapan", "kapici", "kaplan", "kara", "karabatur", "karaduman", "karaelmas", "karakis", "karakoyun", "karakuzu",
		"karamuk", "karaorman", "karasaban", "karataban", "karayel", "kayabasi", "kazanci", "kecisakal", "kelepce", "kelleci",
		"keskin", "kesman", "kilicdar", "kilimci", "kilinc", "kirboga", "kirci", "kocyigit", "kolcak", "komcu",
		"komurcu", "konak", "konca", "koralp", "korukcu", "kosnuk", "kotek", "koylu", "kucukkaya", "kulaksiz",
		"kurban", "kurtulus", "kusmen", "lalezar", "lokmaci", "lombak", "lufer", "maganda", "malazgirt", "malkaciran",
		"mazgirt", "merdane", "mertek", "merzifon", "mirza", "miskin", "miskinoglu", "muglali", "nazik", "nurtopu", "okur",
		"olmez", "oltu", "onaran", "ongun", "ordulu", "orhancan", "ormanci", "ortaca", "osmaneli", "otaci",
		"ovacik", "oztoklu", "ozvezneci", "pakdamar", "pirlanta", "polatkan", "portakal", "poturgeli", "reis", "renacan",
		"resimci", "saferikli", "safkan", "salca", "saldiray", "sallabas", "samanci", "saricakir", "sarikafa", "sarpdemir",
		"savaskan", "sefiloglu", "selercan", "semiz", "sener", "serce", "serinsun", "sessiz", "silahdar", "silifkeli",
		"simsek", "sivri", "sofuoglu", "sonmez", "sonuzun", "soylu", "soysalan", "soyubozuk", "sucu", "sulugoz",
		"supuren", "takes", "tamgun", "tamirci", "tantana", "tarumar", "tekinalp", "tekkaya", "tekkilic", "telek",
		"temiz", "temizel", "temizkalp", "tepecik", "tepsici", "tercan", "terlemez", "tertemiz", "tilki", "tokatci", "sonmez",
		"tombeki", "topatan", "topkapi", "tozkoporan", "tufancan", "tunali", "tuzcu", "tuztas", "ufurukcu", "ugursuz",
		"ulakci", "uluocak", "umutsuz", "unalan", "unalmis", "unkapani", "uraz", "uslu", "uyar", "uzay",
		"uzunadam", "yagizeli", "yanardag", "yanardoner", "yangin", "yaracan", "yaradan", "yarma", "yasayavas", "yasli",
		"yasmak", "yavas", "yavasakan", "yaygara", "yelden", "yeldirme", "yeldirmen", "yersiz", "yikilmaz", "yildirim",
		"yilgin", "yilmaz", "yolyapan", "yorganci", "yorgun", "yosun", "yurdakul", "yurekli", "yurekyakan", "yurtsuz",
		"zaimoglu", "zalim", "zengin", "zebani"};

	return pfnames[Irand(0, std::size(pfnames) - 1)()];
}
//--------------------------------------------------
//--------------------------------------------------
std::string rtown()
{
	static const char *const ptowns[] = {
		"izmir",
		"afyonkarahisar",
		"kilis",
		"bolu",
		"yalova",
		"giresun",
		"tunceli",
		"manisa",
		"cankiri",
		"canakkale",
		"mugla",
		"isparta",
		"ankara",
		"kahramanmaras",
		"nigde",
		"kirklareli",
		"artvin",
		"kirikkale",
		"bursa",
		"bingol",
		"sirnak",
		"erzincan",
		"gaziantep",
		"bayburt",
		"tekirdag",
		"kocaeli",
		"trabzon",
		"ardahan",
		"elazig",
		"karabuk",
		"samsun",
		"malatya",
		"aksaray",
		"van",
		"kars",
		"amasya",
		"kirsehir",
		"balikesir",
		"eskisehir",
		"sanliurfa",
		"adiyaman",
		"mardin",
		"bilecik",
		"hakkari",
		"mus",
		"kayseri",
		"agri",
		"sinop",
		"istanbul",
		"mersin",
		"aydin",
		"sivas",
		"yozgat",
		"igdir",
		"sakarya",
		"burdur",
		"antalya",
		"osmaniye",
		"konya",
		"tokat",
		"zonguldak",
		"corum",
		"batman",
		"adana",
		"usak",
		"denizli",
		"edirne",
		"karaman",
		"ordu",
		"diyarbakir",
		"siirt",
		"kutahya",
		"bitlis",
		"bartin",
		"nevsehir",
		"rize",
		"kastamonu",
		"duzce",
		"erzurum",
		"gumushane",
		"hatay",
	};
	return ptowns[Irand(0, std::size(ptowns) - 1)()];
	// return ptowns[Irand(0, 20)()];
}
//--------------------------------------------------
//--------------------------------------------------
std::string rperson()
{
	std::ostringstream oss;
	oss << std::left;

	oss << std::setw(8) << Irand{0, 999999}() << std::setw(16) << rname() << std::setw(20) << rfname() << rtown();

	return oss.str();
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
bool isprime(int val)
{
	if (val < 2)
		return false;

	if (val % 2 == 0)
		return val == 2;

	if (val % 3 == 0)
		return val == 3;

	if (val % 5 == 0)
		return val == 5;

	for (int k = 7; k * k <= val; k += 2)
		if (val % k == 0)
			return false;

	return true;
}
//--------------------------------------------------
//--------------------------------------------------
std::ostream &sl(std::ostream &os)
{
	return os << "\n-----------------------------------------------------------------------------\n";
}
//--------------------------------------------------
//--------------------------------------------------
void my_terminate()
{
	std::cout << "std::terminate cagrildi....\n";
	std::cout << "myabort cagrildi....\n";
	std::cout << "std::abort() cagrildi\n";
	abort();
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
std::vector<std::string> get_dictionary(const std::string &fname)
{
	using namespace std;

	ifstream ifs{fname};
	if (!ifs)
	{
		cerr << "dosya acilamadi\n";
		exit(EXIT_FAILURE);
	}
	return {std::istream_iterator<string>{ifs}, {}};
}
std::string get_str_from_file(const std::string &fname)
{
	using namespace std;

	ifstream ifs{fname};
	if (!ifs)
	{
		cerr << "dosya acilamadi\n";
		exit(EXIT_FAILURE);
	}
	ostringstream oss;
	oss << ifs.rdbuf();

	return oss.str();
}

//========================
//========================
std::string &remove_duplicates(std::string &str)
{
	for (auto c : str)
	{
		auto pos = str.find_first_of(c);

		for (std::size_t res; (res = str.find_first_of(c, pos + 1)) != std::string::npos;)
			str.erase(res, 1);
	}

	return str;
}

std::string opposite_case(const std::string &s)
{
	std::string temp{s};

	for (auto &c : temp)
		c = std::isupper(c) ? std::tolower(c) : std::toupper(c);

	return temp;
}

std::string remove_chars(const std::string &source, const std::string &scars)
{
	std::string temp{source};

	for (std::size_t pos; (pos = temp.find_first_of(scars)) != std::string::npos;)
		temp.erase(pos, 1);

	return temp;
}

// std::string trim(const std::string &source)
// {
// 	std::string s{source};

// 	while (s.front() == ' ')
// 		s.erase(s.begin());
// 	while (s.back() == ' ')
// 		s.erase(s.end() - 1);

// 	return s;
// }

std::string trim(const std::string &source)
{
	std::string temp{source};

	std::size_t pos1 = temp.find_first_not_of(" ");
	temp.erase(0, pos1);

	std::size_t pos2 = temp.find_last_not_of(" ");
	temp.erase(pos2 + 1);

	return temp;
}

//========================
//========================

void print_time(const time_t &timer)
{
	using namespace std;

	static const char *const pmons[] = {
		"Ocak",
		"Subat",
		"Mart",
		"Nisan",
		"Mayis",
		"Haziran",
		"Temmuz",
		"Agustos",
		"Eylul",
		"Ekim",
		"Kasim",
		"Aralik"};

	static const char *const pdays[] = {
		"Pazar",
		"Pazartesi",
		"Sali",
		"Carsamba",
		"Persembe",
		"Cuma",
		"Cumartesi",
	};

	auto p = localtime(&timer);
	cout.fill('0');
	cout << setw(2) << p->tm_mday << " " << pmons[p->tm_mon] << " " << p->tm_year + 1900 << " "
		 << pdays[p->tm_wday] << " " << setw(2) << p->tm_hour << ":" << setw(2) << p->tm_min << ":"
		 << setw(2) << p->tm_sec << "\n";
}