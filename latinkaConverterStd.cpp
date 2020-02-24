#include "latinkaConverterStd.h"
#include <locale>

LatinkaConverterStd::LatinkaConverterStd()
{
    m_consonantal = L"йцкнгшщзхфвпрлджчсмтьбґ";
    m_loud        = L"іеауои";
    m_doubleLoud  = L"їєяю";
}

std::wstring LatinkaConverterStd::toLatinka(std::wstring text)
{
    std::wstring result = L"";
    std::wstring word = L"";
    for (auto it : text){
        if (isLetter(it)){
            word += it;
            continue;
        }
        retranslate(word);
        result += word;
        word = L"";
        result += it;
    }
    retranslate(word);
    result += word;
    return result;
}

void LatinkaConverterStd::retranslate(std::wstring &str)
{
    if (str.empty())
        return;

    // if only one letter
    if (str.length() == 1){
        str = translateLetter(str[0]);
        return;
    }

    std::wstring copyStr = str;
    std::wstring result = L"";
    std::wstring second = L"";
    second += copyStr[1];
    if (second == L"\'" || second == L"ь" || (isDoubleLoud(copyStr[1]) && isConsonantal(copyStr[0]))){
        result += translateLetter(copyStr[0], copyStr[1]);
        copyStr.erase(0, 2);
        retranslate(copyStr);
        result += copyStr;
    }
    else {
        result += translateLetter(copyStr[0]);
        copyStr.erase(0, 1);
        retranslate(copyStr);
        result += copyStr;
    }
    str = result;
}

bool LatinkaConverterStd::isLoud(const wchar_t &c)
{
    auto c_ = std::towlower(c);
    for (auto it : m_loud)
        if (it == wchar_t(c_))
            return true;
    return isDoubleLoud(c);
}

bool LatinkaConverterStd::isDoubleLoud(const wchar_t &c)
{
    auto c_ = std::towlower(c);
    for (auto it : m_doubleLoud)
        if (it == wchar_t(c_))
            return true;
    return false;
}

bool LatinkaConverterStd::isConsonantal(const wchar_t &c)
{
    auto c_ = std::towlower(c);
    for (auto it : m_consonantal)
        if (it == wchar_t(c_))
            return true;
    return false;
}

bool LatinkaConverterStd::isLetter(const wchar_t &c)
{
    if (isLoud(c))
        return true;
    if (isDoubleLoud(c))
        return true;
    if (isConsonantal(c))
        return true;
    if (c == wchar_t(L'\''))
        return true;
    return false;
}

std::wstring LatinkaConverterStd::translateLetter(wchar_t c)
{
    std::wstring c_;
    bool isLower = std::iswlower(c);
    c = std::towlower(c);
         if (c == m_consonantal[ 0]) c_ = L"j";  // й
    else if (c == m_consonantal[ 1]) c_ = L"c";  // ц
    else if (c == m_consonantal[ 2]) c_ = L"k";  // к
    else if (c == m_consonantal[ 3]) c_ = L"n";  // н
    else if (c == m_consonantal[ 4]) c_ = L"h";  // г
    else if (c == m_consonantal[ 5]) c_ = L"ś";  // ш
    else if (c == m_consonantal[ 6]) c_ = L"ść"; // щ
    else if (c == m_consonantal[ 7]) c_ = L"z";  // з
    else if (c == m_consonantal[ 8]) c_ = L"x";  // х
    else if (c == m_consonantal[ 9]) c_ = L"f";  // ф
    else if (c == m_consonantal[10]) c_ = L"v";  // в
    else if (c == m_consonantal[11]) c_ = L"p";  // п
    else if (c == m_consonantal[12]) c_ = L"r";  // р
    else if (c == m_consonantal[13]) c_ = L"l";  // л
    else if (c == m_consonantal[14]) c_ = L"d";  // д
    else if (c == m_consonantal[15]) c_ = L"ʒ";  // ж
    else if (c == m_consonantal[16]) c_ = L"ć";  // ч
    else if (c == m_consonantal[17]) c_ = L"s";  // с
    else if (c == m_consonantal[18]) c_ = L"m";  // м
    else if (c == m_consonantal[19]) c_ = L"t";  // т
    else if (c == m_consonantal[21]) c_ = L"b";  // б
    else if (c == m_consonantal[22]) c_ = L"g";  // ґ

    else if (c == m_loud        [0]) c_ = L"i"; // і
    else if (c == m_loud        [1]) c_ = L"e"; // е
    else if (c == m_loud        [2]) c_ = L"a"; // а
    else if (c == m_loud        [3]) c_ = L"u"; // у
    else if (c == m_loud        [4]) c_ = L"o"; // о
    else if (c == m_loud        [5]) c_ = L"y"; // и

    else if (c == m_doubleLoud  [0]) c_ = L"ji"; // ї
    else if (c == m_doubleLoud  [1]) c_ = L"je"; // є
    else if (c == m_doubleLoud  [2]) c_ = L"ja"; // я
    else if (c == m_doubleLoud  [3]) c_ = L"ju"; // ю

    if (not isLower)
        c_[0] = std::towupper(c_[0]);
    return c_;
}

std::wstring LatinkaConverterStd::translateLetter(wchar_t first, wchar_t second)
{
    std::wstring res = translateLetter(first);
    if (second != L'\'')
        res += L"\u030C";

    if (isDoubleLoud(second)){
        if (second == m_doubleLoud[0]) second = m_loud[0];
        else if (second == m_doubleLoud[1]) second = m_loud[1];
        else if (second == m_doubleLoud[2]) second = m_loud[2];
        else if (second == m_doubleLoud[3]) second = m_loud[3];
        res += translateLetter(second);
    }
    return res;
}
