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
    static std::wstring run(Alphabet alphabet, std::wstring text);

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
        bool single;
        std::wstring latinLower;
        std::wstring latinUpper;
        std::wstring ukrajinskaLower;
        std::wstring ukrajinskaUpper;

        Alphabet compare(const std::wstring& letter) const;
        std::wstring toLower(const std::wstring& letter) const;
        std::wstring toUpper(const std::wstring& letter) const;
        std::wstring toLatin(const std::wstring& letter) const;
        std::wstring toUkrajinska(const std::wstring& letter) const;

        // we send current alphabet type, and translitterate to another one
        std::wstring translitterate(const Alphabet& type, const std::wstring& letter) const;
    };
    typedef Letter::Type LType;
    void addLetter(Letter::Type type, bool single, std::wstring latinL,
                   std::wstring latinU, std::wstring ukrL, std::wstring ukrU);

    // work with letter list
    std::list <Letter> m_list;
    LType    getLetterType      (const std::wstring& str) const;
    Alphabet getLetterAlphabet  (const std::wstring& str) const;
    bool isLetterCompareAlphabet(const Alphabet& type, const std::wstring& str) const;

    std::wstring translitterateWord  (const Alphabet& type, const std::wstring& str) const;
    std::wstring translitterateLetter(const wchar_t&  c1,   const wchar_t&      c2)  const;
    std::wstring translitterateLetter(const wchar_t& c ) const;
};

#endif // AF_LIB_LATINKA_CONVERTER_H
