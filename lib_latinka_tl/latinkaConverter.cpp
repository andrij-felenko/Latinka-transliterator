#include "latinkaConverter.h"
#include <locale>
#include <iostream>

Latinka::Converter::Converter()
{
    addLetter(LType::DoubleLoud, true, L"ji", L"Ji", L"ї", L"Ї");
    addLetter(LType::DoubleLoud, true, L"je", L"Je", L"є", L"Є");
    addLetter(LType::DoubleLoud, true, L"ja", L"Ja", L"я", L"Я");
    addLetter(LType::DoubleLoud, true, L"ju", L"Ju", L"ю", L"Ю");

    addLetter(LType::Loud, true, L"i", L"I", L"і", L"І");
    addLetter(LType::Loud, true, L"e", L"E", L"е", L"Е");
    addLetter(LType::Loud, true, L"a", L"A", L"а", L"А");
    addLetter(LType::Loud, true, L"u", L"U", L"у", L"У");
    addLetter(LType::Loud, true, L"o", L"O", L"о", L"О");
    addLetter(LType::Loud, true, L"y", L"Y", L"и", L"И");

    addLetter(LType::Hissing, false, L"x",  L"X", L"х", L"Х");
    addLetter(LType::Hissing, false, L"ć",  L"", L"ч", L"Ч"); // TODO
    addLetter(LType::Hissing, false, L"ś",  L"", L"ш", L"Ш"); // TODO
    addLetter(LType::Hissing, false, L"ść", L"", L"щ", L"Щ"); // TODO

    addLetter(LType::Consonantal, true, L"j", L"J", L"й", L"Й");
    addLetter(LType::Consonantal, true, L"c", L"C", L"ц", L"Ц");
    addLetter(LType::Consonantal, true, L"k", L"K", L"к", L"К");
    addLetter(LType::Consonantal, true, L"n", L"N", L"н", L"Н");
    addLetter(LType::Consonantal, true, L"h", L"H", L"г", L"Г");
    addLetter(LType::Consonantal, true, L"z", L"Z", L"з", L"З");
    addLetter(LType::Consonantal, true, L"x", L"X", L"х", L"Х");
    addLetter(LType::Consonantal, true, L"f", L"F", L"ф", L"Ф");
    addLetter(LType::Consonantal, true, L"v", L"V", L"в", L"В");
    addLetter(LType::Consonantal, true, L"p", L"P", L"п", L"П");
    addLetter(LType::Consonantal, true, L"r", L"R", L"р", L"Р");
    addLetter(LType::Consonantal, true, L"l", L"L", L"л", L"Л");
    addLetter(LType::Consonantal, true, L"d", L"D", L"д", L"Д");
    addLetter(LType::Consonantal, true, L"ʒ", L"Ʒ", L"ж", L"Ж"); // TODO
    addLetter(LType::Consonantal, true, L"s", L"S", L"с", L"С");
    addLetter(LType::Consonantal, true, L"m", L"M", L"м", L"М");
    addLetter(LType::Consonantal, true, L"t", L"T", L"т", L"Т");
    addLetter(LType::Consonantal, true, L"b", L"B", L"б", L"Б");
    addLetter(LType::Consonantal, true, L"g", L"G", L"ґ", L"Ґ");
}

// send current alpabet, not destination
std::wstring Latinka::Converter::run(Alphabet type, std::wstring text)
{
    Converter ltl;
    std::wstring result = L"";
    std::wstring word = L"";
    for (auto it : text){
        if (ltl.isLetterCompareAlphabet(type, std::wstring(&it))){
            word += it;
            continue;
        }

        ltl.retranslate(type, word);
        result += word;
        word = L"";
        result += it;
    }
    ltl.retranslate(type, word);
    result += word;
    return result;
}

Latinka::Converter::LType Latinka::Converter::getLetterType(const std::wstring &str)
{
    for (auto it : m_list)
        if (it.latinLower == str || it.latinUpper == str)
            return it.type;
    return LType::None;
}

Latinka::Alphabet Latinka::Converter::getLetterAlphabet(const std::wstring &str)
{
    if (str == L"'" || str == L"ь")
        return Alphabet::SubLetter;

    for (auto it : m_list){
        if (it.latinLower == str || it.latinUpper == str)
            return Alphabet::Latin;
        else if (it.ukrajinskaLower == str || it.ukrajinskaUpper == str)
            return Alphabet::Cyrillic;
    }
    return Alphabet::Other;
}

bool Latinka::Converter::isLetterCompareAlphabet(const Alphabet &type, const std::wstring &str)
{
    auto alp = getLetterAlphabet(str);
    return alp == type || (alp == Alphabet::SubLetter && type == Alphabet::Cyrillic);
}

void Latinka::Converter::retranslate(const Alphabet& type, std::wstring &str)
{
    if (str.empty())
        return;

//     if only one letter
    if (str.size() == 1){
        str = translateLetter(str[0]);
        return;
    }

//    std::wstring copyStr = str;
//    std::wstring result = L"";
//    std::wstring second = L"";
//    second += copyStr[1];
//    if (second == L"\'" || second == L"ь" || (isDoubleLoud(copyStr[1]) && isConsonantal(copyStr[0]))){
//        result += translateLetter(copyStr[0], copyStr[1]);
//        copyStr.erase(0, 2);
//        retranslate(copyStr);
//        result += copyStr;
//    }
//    else {
//        result += translateLetter(copyStr[0]);
//        copyStr.erase(0, 1);
//        retranslate(copyStr);
//        result += copyStr;
//    }
//    str = result;
}

//bool Latinka::Converter::isLetter(const std::wstring &str)
//{
//    for (auto it : m_list)
//        if (it.compare(str))
//            return true;
//    return false;
//}

//Latinka::Converter::LType Latinka::Converter::getLetterType(const std::wstring &str)
//{
//    for (auto it : m_list)
//        if (it.compare(str))
//            return it.type;
//    return LType::None;
//}

//bool Latinka::Converter::isHissing(const wchar_t &c)
//{
//    if (c == m_consonantal[5] || c == m_consonantal[6] || c == m_consonantal[16])
//        return true;
//    return false;
//}

//std::wstring Latinka::Converter::translateLetter(wchar_t c)
//{
//    std::wstring c_;
//    bool isLower = std::iswlower(c);
//    c = wchar_t(std::towlower(c));
//         if (c == m_consonantal[ 0]) c_ = L"j";  // й
//    else if (c == m_consonantal[ 1]) c_ = L"c";  // ц
//    else if (c == m_consonantal[ 2]) c_ = L"k";  // к
//    else if (c == m_consonantal[ 3]) c_ = L"n";  // н
//    else if (c == m_consonantal[ 4]) c_ = L"h";  // г
//    else if (c == m_consonantal[ 5]) c_ = L"ś";  // ш
//    else if (c == m_consonantal[ 6]) c_ = L"ść"; // щ
//    else if (c == m_consonantal[ 7]) c_ = L"z";  // з
//    else if (c == m_consonantal[ 8]) c_ = L"x";  // х
//    else if (c == m_consonantal[ 9]) c_ = L"f";  // ф
//    else if (c == m_consonantal[10]) c_ = L"v";  // в
//    else if (c == m_consonantal[11]) c_ = L"p";  // п
//    else if (c == m_consonantal[12]) c_ = L"r";  // р
//    else if (c == m_consonantal[13]) c_ = L"l";  // л
//    else if (c == m_consonantal[14]) c_ = L"d";  // д
//    else if (c == m_consonantal[15]) c_ = L"ʒ";  // ж
//    else if (c == m_consonantal[16]) c_ = L"ć";  // ч
//    else if (c == m_consonantal[17]) c_ = L"s";  // с
//    else if (c == m_consonantal[18]) c_ = L"m";  // м
//    else if (c == m_consonantal[19]) c_ = L"t";  // т
//    else if (c == m_consonantal[21]) c_ = L"b";  // б
//    else if (c == m_consonantal[22]) c_ = L"g";  // ґ

//    else if (c == m_loud        [0]) c_ = L"i"; // і
//    else if (c == m_loud        [1]) c_ = L"e"; // е
//    else if (c == m_loud        [2]) c_ = L"a"; // а
//    else if (c == m_loud        [3]) c_ = L"u"; // у
//    else if (c == m_loud        [4]) c_ = L"o"; // о
//    else if (c == m_loud        [5]) c_ = L"y"; // и

//    else if (c == m_doubleLoud  [0]) c_ = L"ji"; // ї
//    else if (c == m_doubleLoud  [1]) c_ = L"je"; // є
//    else if (c == m_doubleLoud  [2]) c_ = L"ja"; // я
//    else if (c == m_doubleLoud  [3]) c_ = L"ju"; // ю

//    if (not isLower)
//        c_[0] = std::towupper(c_[0]);
//    return c_;
//}

//std::wstring Latinka::Converter::translateLetter(wchar_t first, wchar_t second)
//{
//    std::wstring res = translateLetter(first);
//    if (second != L'\'' && !isHissing(first)){
//        std::cout << "ff" << " " << res.size() << std::endl;
//        res += L"\u030C";
//        std::cout << "ff2" << " " << res.size() << std::endl;
//    }

//    if (isDoubleLoud(second)){
//        if (second == m_doubleLoud[0]) second = m_loud[0];
//        else if (second == m_doubleLoud[1]) second = m_loud[1];
//        else if (second == m_doubleLoud[2]) second = m_loud[2];
//        else if (second == m_doubleLoud[3]) second = m_loud[3];
//        res += translateLetter(second);
//    }
//    return res;
//}

void Latinka::Converter::addLetter(Latinka::Converter::Letter::Type type, bool single,
                                   std::wstring latinL, std::wstring latinU, std::wstring ukrL, std::wstring ukrU)
{
    Letter letter;
    letter.type = type;
    letter.single = single;
    letter.latinLower = latinL;
    letter.latinUpper = latinU;
    letter.ukrajinskaLower = ukrL;
    letter.ukrajinskaUpper = ukrU;
    m_list.push_back(letter);
}

std::wstring Latinka::Converter::Letter::translitterate(const Alphabet &type, const std::wstring &letter)
{
    if (type == Alphabet::Latin)
        return toUkrajinska(letter);
    return toLatin(letter);
}
