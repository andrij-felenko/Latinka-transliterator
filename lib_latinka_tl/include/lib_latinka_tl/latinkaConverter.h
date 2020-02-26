#ifndef AF_LIB_LATINKA_CONVERTER_H
#define AF_LIB_LATINKA_CONVERTER_H

#include <string>
#include <list>

namespace Latinka {
    class Converter;

    enum Alphabet {
        Latin,
        Cyrillic,
        SubLetter, // use for: '`', 'ь' in cyrillic alphabet
        Other
    };
}

class Latinka::Converter
{
public:
    static std::wstring run(Alphabet from, std::wstring text);

private:
    Converter();

    struct Letter {
        enum Type {
            Loud,
            DoubleLoud,
            Consonantal,
            Hissing,
            None = 0xFF
            };

        Type type;
        std::wstring latinLower;
        std::wstring latinUpper;
        std::wstring ukrajinskaLower;
        std::wstring ukrajinskaUpper;

        bool contains    (const std::wstring& letter) const;
        bool isLatin     (const std::wstring& letter) const;
        bool isUkrajinska(const std::wstring& letter) const;
        bool isLower     (const std::wstring& letter) const;
        bool isUpper     (const std::wstring& letter) const;
    };
    typedef Letter::Type LType;
    inline std::wstring toWStr(const wchar_t& c) const;
    void addLetter(Letter::Type type, std::wstring latinL, std::wstring latinU,
                   std::wstring ukrL, std::wstring ukrU);

    // work with letter list
    std::list <Letter> m_list;
    LType    getLetterType      (const std::wstring& str) const;
    Alphabet getLetterAlphabet  (const std::wstring& str) const;
    LType    getLetterType      (const wchar_t& l) const;
    Alphabet getLetterAlphabet  (const wchar_t& l) const;
    bool isLetterCompareAlphabet(const Alphabet& type, const std::wstring& str) const;
    bool isLower(const std::wstring& l) const;
    bool testSoftLetterWithDoubleEnd(const std::wstring& str) const;

    std::wstring toLower     (const std::wstring& letter) const;
    std::wstring toUpper     (const std::wstring& letter) const;
    std::wstring toLatin     (const std::wstring& letter) const;
    std::wstring toUkrajinska(const std::wstring& letter) const;

    // we send current alphabet type, and translitterate to another one
    std::wstring translitterateWord  (const Alphabet &from, std::wstring str) const;
    std::wstring translitterateLetter(const Alphabet &from, const std::wstring &c )  const;
    std::wstring translitterateLetter(const Alphabet &from, const std::wstring &c1,  const std::wstring &c2)  const;
    std::wstring translitterateLetter(const Alphabet &from, const wchar_t &c1,  const wchar_t &c2)  const;
    std::wstring translitterateLetter(const Alphabet &from, const wchar_t &c )  const;
};

#endif // AF_LIB_LATINKA_CONVERTER_H
