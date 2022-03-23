#include "racenames.h"

map<int, string(*)()> raceName;

// vector of base dnd class names

// Dwarf
    //First Names
vector<string> dwarf_first = {"ad", "alb", "am", "bae", "bar", "bro", "brue", "dai", "dar", "de", "ebe", "ein", "far", "fli", "gar", "har", "kil", "mor", "or", "os", "ran", "ru", "tak", "thor", "tor", "trau", "tra", "ulf", "ve", "von", "ar", "aud", "bard", "oag", "eld", "falk", "fin", "gunn", "hel", "hli", "kath", "kris", "li", "lift", "mar", "ris", "san", "vis"};
vector<string> dwarf_last = {"ber", "rik", "rich", "rn", "endd", "ttor", "nor", "n", "rak", "lg", "erk", "kil", "grim", "nt", "dain", "bek", "gran", "sik", "kar", "linn", "din", "in", "dek", "bon", "vok", "gar", "it", "dal", "tin", "hild", "dryn", "nal", "eth", "runn", "ellen", "loda", "dis", "ja", "ra", "de", "rasa", "red", "wynn", "nl", "bera", "gga"};
    //Mountain Clan Names
vector<string> dwarf_mclanf = {"battle", "brawn", "fire", "frost", "iron", "stout", "stone", "war", "ice", "cave"};
vector<string> dwarf_mclanl = {"hammer", "forge", "beard", "fist", "axe", "mane", "crucible", "sheild", "beer", "mine"};
    //Hill Clan Names
vector<string> dwarf_hclanf = {"bal", "oan", "gor", "holder", "lod", "lut", "rumna", "strak", "tor", "un", "ult", "sman", "mord"};
vector<string> dwarf_hclanl = {"erk", "kil", "unn", "hek", "err", "gehr", "heim", "eln", "gart", "durch", "vidur", "urs", "dir"};

// FirstName of clan ClanName
string mdwarfName()
{
    int firstHalf = rand() % dwarf_first.size();
    int secondHalf = rand() % dwarf_last.size();
    string name = "";
    name = name + dwarf_first[firstHalf] + dwarf_last[secondHalf] + " of clan ";
    string lName = "";

    firstHalf = rand() % dwarf_mclanf.size();
    secondHalf = rand() % dwarf_mclanl.size();

    lName = lName + dwarf_mclanf[firstHalf];
    lName = lName + dwarf_mclanl[secondHalf];

    lName[0] = toupper(lName[0]);
    name[0] = toupper(name[0]);

    name = name + lName;
    return name;
}

string hdwarfName()
{
    int firstHalf = rand() % dwarf_first.size();
    int secondHalf = rand() % dwarf_last.size();
    string name = "";
    name = name + dwarf_first[firstHalf] + dwarf_last[secondHalf] + " of clan ";
    string lName = "";

    firstHalf = rand() % dwarf_hclanf.size();
    secondHalf = rand() % dwarf_hclanl.size();

    lName = lName + dwarf_hclanf[firstHalf];
    lName = lName + dwarf_hclanl[secondHalf];

    lName[0] = toupper(lName[0]);
    name[0] = toupper(name[0]);

    name = name + lName;
    return name;
}

// Elf
    //First Names
vector<string> elf_first = {"adr", "ael", "ara", "au", "bei", "ber", "car", "eni", "erd", "ere", "galinn", "had", "hei", "imm", "ivell", "lau", "mind", "pae", "per", "qua", "ria", "rol", "sov", "tham", "thar", "ther", "var", "alth", "anast", "and", "ant", "beth", "bir", "cae", "oru", "enn", "felo", "lel", "jel", "key", "lesh", "li", "meri", "mia", "nai", "quel", "quil", "sar", "shan", "sha", "sil", "their", "thi", "vad", "val", "xana"};
vector<string> elf_last = {"an", "ar", "mil", "st", "ro", "rian", "rie", "alis", "van", "dan", "rai", "o", "eral", "ios", "cian", "artis", "lias", "en", "rion", "don", "eliss", "ior", "ivol", "is", "ie", "aea", "rianna", "raste", "inua", "rynna", "el", "lynn", "silia", "a", "sial", "enia", "enneth", "leth", "anna", "ele", "lee", "vara", "enna", "lathe", "iel", "airaa", "va", "qui", "astra", "ania", "anthe", "phia"};
    //Family Names
vector<string> elf_famfirst = {"gem", "star", "moon", "diamond", "ruby", "silver", "gold", "night", "wind", "dark", "aqua", "river", "sapphire", "emerald", "obsidian", "oak", "spruce", "pine", "juniper", "birch"};
vector<string> elf_famlast = {"flower", "whisper", "dew", "blossom", "frond", "heel", "breeze", "brook", "petal"};

string elfName()
{
    // FirstName FamilyName
    int firstHalf = rand() % elf_first.size();
    int secondHalf = rand() % elf_last.size();
    string name = "";
    name = name + elf_first[firstHalf] + elf_last[secondHalf] + " ";
    string lName = "";

    //TODO: Change to account for different clans
    /*
    if(sub==2) //high
    {
        firstHalf = rand() % elf_famfirst.size();
        secondHalf = rand() % elf_famlast.size();

        lName = lName + elf_famfirst[firstHalf];
        lName = lName + elf_famlast[secondHalf];
    }
    else if(sub==3) //wood
    {
        firstHalf = rand() % elf_famfirst.size();
        secondHalf = rand() % elf_famlast.size();

        lName = lName + elf_famfirst[firstHalf];
        lName = lName + elf_famlast[secondHalf];
    }
    else //drow
    {
        firstHalf = rand() % elf_famfirst.size();
        secondHalf = rand() % elf_famlast.size();

        lName = lName + elf_famfirst[firstHalf];
        lName = lName + elf_famlast[secondHalf];
    }*/

    firstHalf = rand() % elf_famfirst.size();
    secondHalf = rand() % elf_famlast.size();

    lName = lName + elf_famfirst[firstHalf];
    lName = lName + elf_famlast[secondHalf];

    lName[0] = toupper(lName[0]);
    name[0] = toupper(name[0]);

    name = name + lName;
    return name;
}

// Halfling names
vector<string> half_first = {"alt", "and", "ca", "cor", "eld", "er", "fin", "gar", "lind", "ly", "mer", "mil", "os", "per", "ros", "wel", "br", "cal", "cor", "euph", "jill", "kith", "lavi", "lid", "merl", "nedd", "pae", "port", "sera", "shae", "van", "ver"};
vector<string> half_last = {"on", "er", "de", "rin", "rich", "nan", "ret", "al", "ric", "o", "born", "coe", "lby", "ry", "ee", "lie", "a", "emia", "ian", "ri", "via", "da", "la", "ia", "phina", "na", "i"};
vector<string> half_famf = {"brush", "good", "green", "high", "under", "toss", "tea", "lea", "thorn", "branch", "bright", "thicket"};
vector<string> half_faml = {"gather", "barrel", "bottle", "hill", "topple", "leaf", "gage", "cobble", "bough", "burow", "pond", "grass"};

string halflingName()
{
    // FirstName FamilyName
    int firstHalf = rand() % half_first.size();
    int secondHalf = rand() % half_last.size();
    string name = "";
    name = name + half_first[firstHalf] + half_last[secondHalf] + " ";

    firstHalf = rand() % half_famf.size();
    secondHalf = rand() % half_faml.size();
    string lName = "";
    lName = lName + half_famf[firstHalf];
    lName = lName + half_faml[secondHalf];

    name[0] = toupper(name[0]);
    lName[0] = toupper(lName[0]);

    name = name + lName;
    return name;
}

// Human names
// These are kind of complex, as there are different ethnicities with different naming conventions. I'll come back to this
vector<string> cali_first = {"as", "bar", "has", "khe", "meh", "sude", "zash", "ala", "ceid", "ham", "jas", "meil", "seip", "yash"};
vector<string> cali_last = {"eir", "deid", "med", "men", "iman", "la", "il", "a", "mal", "ora", "eira", "eida"};
vector<string> cali_famf = {"bash", "dum", "jas", "khal", "mos", "pash", "re"};
vector<string> cali_faml = {"a", "ein", "san", "id", "tana", "ar", "in"};
vector<vector<string>> cal_names = {cali_first, cali_last, cali_famf, cali_faml};

vector<string> chon_first = {"dar", "dor", "even", "gor", "gri", "hel", "mal", "mor", "ran", "ste", "arv", "esv", "jhes", "ker", "lur", "mir", "row", "shan", "tess"};
vector<string> chon_last = {"vin", "n", "dur", "stag", "m", "ark", "dal", "dd", "eene", "ele", "sail", "ri", "i", "an", "dri"};
vector<string> chon_famf = {"amble", "buck", "dun", "even", "grey", "tall", "black", "white", "dunder"};
vector<string> chon_faml = {"crown", "man", "dragon", "wood", "castle", "stag", "lord", "hill"};
vector<vector<string>> chon_names = {chon_first, chon_last, chon_famf, chon_faml};

vector<string> dam_first = {"ba", "fad", "gla", "gri", "i", "ko", "miv", "or", "pav", "ser", "aleth", "ka", "kater", "ma", "nata", "ol", "ta", "zo"};
vector<string> dam_last = {"r", "ei", "gor", "gan", "vor", "sef", "al", "el", "ra", "nin", "li", "ma", "na"};
vector<string> dam_famf = {"ber", "cher", "dot", "kulen", "mar", "nemet", "shem", "star"};
vector<string> dam_faml = {"sk", "nin", "ov", "ag"};
vector<vector<string>> dam_names = {dam_first, dam_last, dam_famf, dam_faml};

vector<string> ill_first = {"and", "bla", "bra", "fra", "ge", "land", "lu", "mal", "sto", "tam", "ur", "ama", "beth", "ce", "keth", "ma", "olg", "sili", "west"};
vector<string> ill_last = {"er", "th", "n", "cer", "r", "an", "frey", "a", "ra"};
vector<string> ill_famf = {"bright", "horn", "lack", "storm", "wind", "dark", "skull", "thunder"};
vector<string> ill_faml = {"wood", "raven", "man", "terror", "rivver", "crow", "root", "sea"};
vector<vector<string>> ill_names = {ill_first, ill_last, ill_famf, ill_faml};

vector<string> mul_first = {"ao", "bare", "ehput", "ketho", "mum", "ram", "so", "thazar", "ur", "ariz", "cha", "neph", "nul", "Muri", "sef", "tho", "um", "zol"};
vector<string> mul_last = {"th", "ris", "-ki", "ed", "as", "-kehur", "-de", "hur", "ima", "thi", "is", "ara", "la"};
vector<string> mul_famf = {"ank", "ansk", "fe", "hah", "nath", "sep", "uuth"};
vector<string> mul_faml = {"halab", "uld", "zim", "pet", "andem", "ret", "rakt"};
vector<vector<string>> mul_names = {mul_first, mul_last, mul_famf, mul_faml};

vector<string> rash_first = {"bori", "faur", "jan", "kani", "madi", "ralme", "shau", "vladi", "fyev", "hul", "im", "nev", "shev", "tamm", "yul"};
vector<string> rash_last = {"vik", "gar", "dar", "thar", "slak", "mar", "arra", "mith", "zel", "dra"};
vector<string> rash_famf = {"cher", "dyer", "iltaz", "murnyet", "staya", "ulmo"};
vector<string> rash_faml = {"goba", "nina", "yara", "hara", "noga", "kina"};
vector<vector<string>> rash_names = {rash_first, rash_last, rash_famf, rash_faml};

vector<string> shou_first = {"a", "che", "ch", "fa", "ji", "ju", "li", "lo", "me", "o", "shu", "w", "ba", "ch", "le", "me", "qi", "ta"};
vector<string> shou_last = {"n", "i", "ang", "an", "ng", "en", "ao"};
vector<string> shou_famf = {"chi", "hu", "ka", "ku", "la", "li", "me", "pi", "shi", "su", "ta", "wa"};
vector<string> shou_faml = {"en", "ang", "o", "ng", "i", "n", "m"};
vector<vector<string>> shou_names = {shou_first, shou_last, shou_famf, shou_faml};

//Agosto, Astorio, Calabra, Domine, Falone, Marivaldi, Pisacar, Ramondo
vector<string> tur_first = {"an", "di", "marc", "pier", "rim", "rom", "sala", "umb", "bal", "do", "fai", "jal", "lu", "mar", "qua", "se", "von"};
vector<string> tur_last = {"ton", "ero", "on", "ardo", "zar", "ama", "na", "la", "isa", "ana", "ta", "ra", "lise", "da"};
vector<string> tur_famf = {"ago", "asto", "cala", "do", "fal", "mari", "pis", "ram"};
vector<string> tur_faml = {"sto", "rio", "bra", "mine", "one", "valdi", "car", "ondo"};
vector<vector<string>> tur_names = {tur_first, tur_last, tur_famf, tur_faml};

vector<vector<vector<string>>> human_names = {cal_names, chon_names, dam_names, ill_names, mul_names, rash_names, shou_names, tur_names};

string humanName()
{
    int ethnicity = rand() % human_names.size();
    //cout << "Human ethnicity: " << ethnicity << "\n";
    string name = "";

    // FirstName FamilyName
    int firstHalf = rand() % human_names[ethnicity][0].size();
    int secondHalf = rand() % human_names[ethnicity][1].size();
    name = name + human_names[ethnicity][0][firstHalf] + human_names[ethnicity][1][secondHalf] + " ";

    firstHalf = rand() % human_names[ethnicity][2].size();
    secondHalf = rand() % human_names[ethnicity][3].size();
    string lName = "";
    lName = lName + human_names[ethnicity][2][firstHalf] + human_names[ethnicity][3][secondHalf];

    name[0] = toupper(name[0]);
    lName[0] = toupper(lName[0]);

    name = name + lName;
    return name;
}

// Dragonborn names
vector<string> drag_first = {"arj", "bal", "bhar", "don", "ghe", "hesk", "kr", "med", "meh", "nad", "pand", "pat", "rho", "sham", "shed", "tar", "tor", "ak", "bi", "fari", "har", "havi", "jhe", "ka", "kor", "mish", "na", "per", "rai", "so", "sur", "tha", "uad"};
vector<string> drag_last = {"han", "asar", "ash", "aar", "sh", "an", "iv", "rash", "en", "arr", "jed", "rin", "gar", "inn", "hun", "ra", "ri", "deh", "ann", "lar", "va", "la", "ina", "jit"};
vector<string>drag_famf = {"clethtin", "daarden", "delmi", "drache", "fenken", "kepesh", "kerr", "kimba", "linxaka", "myas", "nemmo", "norix", "ophinsh", "prexi", "shestende", "turnu", "verthi", "yar"};
vector<string>drag_faml = {"thiallor", "drian", "rev", "dandion", "kabradon", "molik", "hylon", "tuul", "sendalor", "tan", "nis", "ius", "talajiir", "jandilin", "liath", "roth", "sathurgiesh", "jerit"};

string dragonName()
{
    // FirstName FamilyName
    int firstHalf = rand() % drag_first.size();
    int secondHalf = rand() % drag_last.size();
    string name = "";
    name = name + drag_first[firstHalf] + drag_last[secondHalf] + " ";

    firstHalf = rand() % drag_famf.size();
    secondHalf = rand() % drag_faml.size();
    string lName = "";
    lName = lName + drag_famf[firstHalf];
    lName = lName + drag_faml[secondHalf];

    name[0] = toupper(name[0]);
    lName[0] = toupper(lName[0]);

    name = name + lName;
    return name;
}


// Gnome names
    // Gnomes should have a few names, and possibly a nickname or two.
vector<string> gn_first = {"als", "alv", "boddy", "bro", "burg", "dim", "eld", "er", "fon", "fr", "ger", "gim", "glim", "jeb", "kell", "nam", "orr", "roon", "see", "sin", "warr", "wr", "zoo", "bimp", "bre", "cara", "car", "don", "duv", "ella", "elly", "lil", "loop", "lor", "mard", "ni", "orl", "roy", "sha", "ta", "way", "za"};
vector<string> gn_last = {"ton", "yn", "nock", "cc", "ell", "ble", "on", "ky", "kin", "ug", "bo", "eddo", "en", "foodle", "dar", "dri", "enn", "nollin", "ena", "mip", "lin", "ella", "amil", "jobell", "wick", "li", "mottin", "illa", "nab", "ssa", "a", "wyn", "mil", "na", "wocket"};

string gnomeName()
{
    int firstHalf = rand() % gn_first.size();
    int secondHalf = rand() % gn_last.size();
    string name = "";
    name = name + gn_first[firstHalf] + gn_last[secondHalf] + " ";

    name[0] = toupper(name[0]);

    //TODO: Add extra gnome names

    return name;
}

// Half-elf's use human or elf names
string halfelfName()
{
    //TODO: Human name function currently generates full human name, we need just first or last
    int name = rand() % 2;
    int ethnicity = rand() % human_names.size();

    int firstHalf;
    int secondHalf;
    string fullname = "";
    if( name )
    {
        // if 1, give elf first name
        firstHalf = rand() % elf_first.size();
        secondHalf = rand() % elf_last.size();
        fullname = fullname + elf_first[firstHalf] + elf_last[secondHalf] + " ";
    }
    else
    {
        // else give human first name
        firstHalf = rand() % human_names[ethnicity][0].size();
        secondHalf = rand() % human_names[ethnicity][1].size();
        fullname = fullname + human_names[ethnicity][0][firstHalf] + human_names[ethnicity][1][secondHalf] + " ";
    }

    // same for family name
    name = rand() % 2;
    string lName = "";
    if( name )
    {
        // if 1 give human name
        firstHalf = rand() % human_names[ethnicity][2].size();
        secondHalf = rand() % human_names[ethnicity][3].size();
        lName = lName + human_names[ethnicity][2][firstHalf] + human_names[ethnicity][3][secondHalf];
    }
    else
    {
        // else give elf name
        firstHalf = rand() % elf_famfirst.size();
        secondHalf = rand() % elf_famlast.size();
        lName = lName + elf_famfirst[firstHalf];
        lName = lName + elf_famlast[secondHalf];
    }

    fullname[0] = toupper(fullname[0]);
    lName[0] = toupper(lName[0]);

    fullname = fullname + lName;
    return fullname;
}

// Half-orc names
vector<string> orc_first = {"den", "fen", "ge", "hen", "hol", "im", "kel", "kru", "mhur", "ron", "shu", "tho", "bag", "eme", "eng", "kans", "my", "nee", "ova", "own", "shaul", "sul", "vol", "yeve"};
vector<string> orc_last = {"eh", "g", "ll", "k", "sh", "h", "sk", "ren", "t", "mp", "kk", "gi", "n", "ong", "if", "ev", "ga", "ka", "en", "lda", "a", "ha"};

string halforcName()
{

    int firstHalf = rand() % orc_first.size();
    int secondHalf = rand() % orc_last.size();
    string name = "";
    name = name + orc_first[firstHalf] + orc_last[secondHalf];

    name[0] = toupper(name[0]);

    return name;
}

// Tiefling names
vector<string> tief_first = {"akme", "am", "bara", "dama", "eke", "lad", "kai", "leu", "mel", "mor", "pel", "ska", "the", "ak", "ana", "bry", "cri", "dam", "kall", "ler", "mak", "nem", "ori", "phel", "rie"};
vector<string> tief_last = {"nos", "non", "kas", "kos", "mon", "os", "ron", "cis", "ech", "thos", "aios", "mos", "rai", "ta", "kis", "seis", "ella", "aia", "ista", "issa", "ria", "eia", "anna", "eta"};

string tieflingName()
{
    int firstHalf = rand() % tief_first.size();
    int secondHalf = rand() % tief_last.size();
    string name = "";
    name = name + tief_first[firstHalf] + tief_last[secondHalf];

    name[0] = toupper(name[0]);

    return name;
}


void createMap()
{
    raceName.insert(pair<int, string(*)()>(0, hdwarfName));
    raceName.insert(pair<int, string(*)()>(1, mdwarfName));
    raceName.insert(pair<int, string(*)()>(2, elfName));
    raceName.insert(pair<int, string(*)()>(3, elfName));
    raceName.insert(pair<int, string(*)()>(4, halflingName));
    raceName.insert(pair<int, string(*)()>(5, halflingName));
    raceName.insert(pair<int, string(*)()>(6, humanName));
    raceName.insert(pair<int, string(*)()>(7, dragonName));
    raceName.insert(pair<int, string(*)()>(8, gnomeName));
    raceName.insert(pair<int, string(*)()>(9, gnomeName));
    raceName.insert(pair<int, string(*)()>(10, halfelfName));
    raceName.insert(pair<int, string(*)()>(11, halforcName));
    raceName.insert(pair<int, string(*)()>(12, tieflingName));
    raceName.insert(pair<int, string(*)()>(13, elfName));
}

string createName(int race)
{
    string test;
    if( race < (int)raceName.size() )
    {
        return raceName[race]();
    }
    // Error Code 1107
    QString error = "Cannot find race to build: ";
    error.append(QString::number(race));
    logError(createErr, error);
    return "Error";
}
