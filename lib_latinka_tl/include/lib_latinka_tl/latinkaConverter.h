#ifndef AF_LIB_LATINKA_CONVERTER_H
#define AF_LIB_LATINKA_CONVERTER_H

#include <string>
#include <list>

namespace Latinka {
    class Converter;
}

class Latinka::Converter
{
public:
    Converter();

    static std::wstring toLatinka(std::wstring text);

private:
    void retranslate(std::wstring& str);
    bool isLoud       (const wchar_t& c);
    bool isDoubleLoud (const wchar_t& c);
    bool isConsonantal(const wchar_t& c);
    bool isLetter     (const wchar_t& c);
    bool isSizzling   (const wchar_t& c);

    std::wstring translateLetter(wchar_t c);
    std::wstring translateLetter(wchar_t c1, wchar_t c2);

    std::wstring m_consonantal;
    std::wstring m_doubleLoud;
    std::wstring m_loud;
};

#endif // AF_LIB_LATINKA_CONVERTER_H
