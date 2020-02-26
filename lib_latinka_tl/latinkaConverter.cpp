#include "latinkaConverter.h"

std::wstring Latinka::Converter::run(Alphabet from, std::wstring text)
{
    static Converter ltl;
    std::wstring result = L"";
    std::wstring word = L"";
    for (auto it : text){
        if (ltl.isLetterCompareAlphabet(from, std::wstring(&it))){
            word += it;
            continue;
        }

        result += ltl.translitterateWord(from, word);
        word = L"";
        result += it;
    }
    result += ltl.translitterateWord(from, word);
    return result;
}

Latinka::Converter::Converter()
{
    addLetter(LType::DoubleLoud, L"ji", L"Ji", L"ї", L"Ї");
    addLetter(LType::DoubleLoud, L"je", L"Je", L"є", L"Є");
    addLetter(LType::DoubleLoud, L"ja", L"Ja", L"я", L"Я");
    addLetter(LType::DoubleLoud, L"ju", L"Ju", L"ю", L"Ю");

    addLetter(LType::Loud, L"i", L"I", L"і", L"І");
    addLetter(LType::Loud, L"e", L"E", L"е", L"Е");
    addLetter(LType::Loud, L"a", L"A", L"а", L"А");
    addLetter(LType::Loud, L"u", L"U", L"у", L"У");
    addLetter(LType::Loud, L"o", L"O", L"о", L"О");
    addLetter(LType::Loud, L"y", L"Y", L"и", L"И");

    addLetter(LType::Hissing, L"x",  L"X",  L"х", L"Х");
    addLetter(LType::Hissing, L"ć",  L"Č",  L"ч", L"Ч");
    addLetter(LType::Hissing, L"ś",  L"Š",  L"ш", L"Ш");
    addLetter(LType::Hissing, L"ść", L"Šč", L"щ", L"Щ");

    addLetter(LType::Consonantal, L"j", L"J", L"й", L"Й");
    addLetter(LType::Consonantal, L"c", L"C", L"ц", L"Ц");
    addLetter(LType::Consonantal, L"k", L"K", L"к", L"К");
    addLetter(LType::Consonantal, L"n", L"N", L"н", L"Н");
    addLetter(LType::Consonantal, L"h", L"H", L"г", L"Г");
    addLetter(LType::Consonantal, L"z", L"Z", L"з", L"З");
    addLetter(LType::Consonantal, L"x", L"X", L"х", L"Х");
    addLetter(LType::Consonantal, L"f", L"F", L"ф", L"Ф");
    addLetter(LType::Consonantal, L"v", L"V", L"в", L"В");
    addLetter(LType::Consonantal, L"p", L"P", L"п", L"П");
    addLetter(LType::Consonantal, L"r", L"R", L"р", L"Р");
    addLetter(LType::Consonantal, L"l", L"L", L"л", L"Л");
    addLetter(LType::Consonantal, L"d", L"D", L"д", L"Д");
    addLetter(LType::Consonantal, L"ʒ", L"Ʒ", L"ж", L"Ж");
    addLetter(LType::Consonantal, L"s", L"S", L"с", L"С");
    addLetter(LType::Consonantal, L"m", L"M", L"м", L"М");
    addLetter(LType::Consonantal, L"t", L"T", L"т", L"Т");
    addLetter(LType::Consonantal, L"b", L"B", L"б", L"Б");
    addLetter(LType::Consonantal, L"g", L"G", L"ґ", L"Ґ");
}

void Latinka::Converter::addLetter(Latinka::Converter::Letter::Type type, std::wstring latinL, std::wstring latinU, std::wstring ukrL, std::wstring ukrU)
{
    Letter letter;
    letter.type = type;
    letter.latinLower = latinL;
    letter.latinUpper = latinU;
    letter.ukrajinskaLower = ukrL;
    letter.ukrajinskaUpper = ukrU;
    m_list.push_back(letter);
}

bool Latinka::Converter::Letter::contains(const std::wstring &letter) const
{
    return isLatin(letter) || isUkrajinska(letter);
}

bool Latinka::Converter::Letter::isLatin(const std::wstring &letter) const
{
    return latinLower == letter || latinUpper == letter;
}

bool Latinka::Converter::Letter::isUkrajinska(const std::wstring &letter) const
{
    return ukrajinskaLower == letter || ukrajinskaUpper == letter;
}

bool Latinka::Converter::Letter::isLower(const std::wstring &letter) const
{
    return latinLower == letter || ukrajinskaLower == letter;
}

bool Latinka::Converter::Letter::isUpper(const std::wstring &letter) const
{
    return latinUpper == letter || ukrajinskaUpper == letter;
}

Latinka::Converter::LType Latinka::Converter::getLetterType(const std::wstring &str) const
{
    for (auto it : m_list)
        if (it.contains(str))
            return it.type;
    return LType::None;
}

Latinka::Alphabet Latinka::Converter::getLetterAlphabet(const std::wstring &str) const
{
    if ( str == L"'" || str == L"ь")
        return Alphabet::SubLetter;

    for (auto it : m_list){
        if (it.latinLower == str || it.latinUpper == str)
            return Alphabet::Latin;
        if (it.ukrajinskaLower == str || it.ukrajinskaUpper == str)
            return Alphabet::Cyrillic;
    }
    return Alphabet::Other;
}

Latinka::Converter::LType Latinka::Converter::getLetterType(const wchar_t &l) const
{
    return getLetterType(std::wstring(&l));
}

Latinka::Alphabet Latinka::Converter::getLetterAlphabet(const wchar_t &l) const
{
    return getLetterAlphabet(std::wstring(&l));
}

bool Latinka::Converter::isLetterCompareAlphabet(const Alphabet &type, const std::wstring &str) const
{
    auto alp = getLetterAlphabet(str);
    return alp == type || (alp == Alphabet::SubLetter && type == Alphabet::Cyrillic);
}

std::wstring Latinka::Converter::translitterateWord(const Alphabet &from, std::wstring str) const
{
    // for now it must work only for ukraine to latinka
    if (str.empty())
        return L"";

//     if only one letter
    if (str.size() == 1)
        return translitterateLetter(from, str);

    std::wstring result = L"";
    if (getLetterAlphabet(str[1]) == Alphabet::SubLetter || (getLetterType(str[0]) == LType::Consonantal && getLetterType(str[1]) == LType::DoubleLoud)){
        result += translitterateLetter(from, str[0], str[1]);
        str.erase(0, 2);
        result += translitterateWord(from, str);
    }
    else {
        result += translitterateLetter(from, str[0]);
        str.erase(0, 1);
        result += translitterateWord(from, str);
    }
    return result;
}

std::wstring Latinka::Converter::translitterateLetter(const Alphabet& from, const std::wstring &c1, const std::wstring &c2) const
{
    std::wstring res = translitterateLetter(from, c1);
    if (c2 == L"\'" && getLetterType(c1) != LType::Hissing)
        res += L"\u030C";

    if (getLetterType(c2) == LType::DoubleLoud){
        auto letter = translitterateLetter(from, c2);
        res += letter[1];
    }
    return res;
}

std::wstring Latinka::Converter::translitterateLetter(const Alphabet &from, const wchar_t &c1, const wchar_t &c2) const
{
    return translitterateLetter(from, std::wstring(&c1), std::wstring(&c2));
}

std::wstring Latinka::Converter::translitterateLetter(const Alphabet &from, const wchar_t &c) const
{
    return translitterateLetter(from, std::wstring(&c));
}

std::wstring Latinka::Converter::translitterateLetter(const Alphabet &from, const std::wstring &c) const
{
    if (from == Alphabet::Latin)
        return toUkrajinska(c);
    return toLatin(c);
}

std::wstring Latinka::Converter::toLower(const std::wstring &letter) const
{
    for (auto it : m_list){
        if (it.isLatin(letter))
            return it.latinLower;
        if (it.isUkrajinska(letter))
            return it.ukrajinskaLower;
    }
    return letter;
}

std::wstring Latinka::Converter::toUpper(const std::wstring &letter) const
{
    for (auto it : m_list){
        if (it.isLatin(letter))
            return it.latinUpper;
        if (it.isUkrajinska(letter))
            return it.ukrajinskaUpper;
    }
    return letter;
}

std::wstring Latinka::Converter::toLatin(const std::wstring &letter) const
{
    for (auto it : m_list)
        if (it.isUkrajinska(letter)){
            if (it.isLower(letter))
                return it.latinLower;
            else
                return it.latinUpper;
        }
    return letter;
}

std::wstring Latinka::Converter::toUkrajinska(const std::wstring &letter) const
{
    for (auto it : m_list)
        if (it.isLatin(letter)){
            if (it.isLower(letter))
                return it.ukrajinskaLower;
            else
                return it.ukrajinskaUpper;
        }
    return letter;
}
