#include "latinkaConverter.h"

LatinkaConverter::LatinkaConverter()
{
    m_consonantal = QString("йцкнгшщзхфвпрлджчсмтьбґ");
    m_loud = QString("уеіаои");
    m_doubleLoud = QString("їєяю");
}

QString LatinkaConverter::toLatinka(QString text)
{
    QString result = "";
    QString word = QString("");
    for (auto it : text){
        if (isLetter(it)){
            word += it;
            continue;
        }
        retranslate(word);
        result += word;
        word = "";
        result += it;
    }
    retranslate(word);
    result += word;
    return result;
}

void LatinkaConverter::retranslate(QString &str)
{
    if (str.isEmpty())
        return;

    // if only one letter
    if (str.length() == 1){
        str = translateLetter(str[0]);
        return;
    }

    QString copyStr = str;
    QString result = "";
    QString second = QString(copyStr[1]);
    if (second == "\'" || second == "ь" || (isDoubleLoud(copyStr[1]) && isConsonantal(copyStr[0]))){
        result += translateLetter(copyStr[0], copyStr[1]);
        copyStr.remove(0, 2);
        retranslate(copyStr);
        result += copyStr;
//        return;
    }
    else {
        result += translateLetter(copyStr[0]);
        copyStr.remove(0, 1);
        retranslate(copyStr);
        result += copyStr;
    }
    str = result;
}

bool LatinkaConverter::isLoud(const QChar &c)
{
    auto c_ = c.toLower();
    for (auto it : m_loud)
        if (it == c_)
            return true;
    return isDoubleLoud(c);
}

bool LatinkaConverter::isDoubleLoud(const QChar &c)
{
    auto c_ = c.toLower();
    for (auto it : m_doubleLoud)
        if (it == c_)
            return true;
    return false;
}

bool LatinkaConverter::isConsonantal(const QChar &c)
{
    auto c_ = c.toLower();
    for (auto it : m_consonantal)
        if (it == c_)
            return true;
    return false;
}

bool LatinkaConverter::isLetter(const QChar &c)
{
    if (isLoud(c))
        return true;
    if (isDoubleLoud(c))
        return true;
    if (isConsonantal(c))
        return true;
    if (c == QChar('\''))
        return true;
    return false;
}

QString LatinkaConverter::translateLetter(QChar c)
{
    QString c_;
    bool isLower = c.isLower();
    c = c.toLower();
         if (c.unicode() == m_consonantal[ 0].unicode()) c_ = QString("j" ); // й
    else if (c.unicode() == m_consonantal[ 1].unicode()) c_ = QString("c" ); // ц
    else if (c.unicode() == m_consonantal[ 2].unicode()) c_ = QString("k" ); // к
    else if (c.unicode() == m_consonantal[ 3].unicode()) c_ = QString("n" ); // н
    else if (c.unicode() == m_consonantal[ 4].unicode()) c_ = QString("h" ); // г
    else if (c.unicode() == m_consonantal[ 5].unicode()) c_ = QString("ś" ); // ш
    else if (c.unicode() == m_consonantal[ 6].unicode()) c_ = QString("ść"); // щ
    else if (c.unicode() == m_consonantal[ 7].unicode()) c_ = QString("z" ); // з
    else if (c.unicode() == m_consonantal[ 8].unicode()) c_ = QString("x" ); // х
    else if (c.unicode() == m_consonantal[ 9].unicode()) c_ = QString("f" ); // ф
    else if (c.unicode() == m_consonantal[10].unicode()) c_ = QString("v" ); // в
    else if (c.unicode() == m_consonantal[11].unicode()) c_ = QString("p" ); // п
    else if (c.unicode() == m_consonantal[12].unicode()) c_ = QString("r" ); // р
    else if (c.unicode() == m_consonantal[13].unicode()) c_ = QString("l" ); // л
    else if (c.unicode() == m_consonantal[14].unicode()) c_ = QString("d" ); // д
    else if (c.unicode() == m_consonantal[15].unicode()) c_ = QString("ʒ" ); // ж
    else if (c.unicode() == m_consonantal[16].unicode()) c_ = QString("ć" ); // ч
    else if (c.unicode() == m_consonantal[17].unicode()) c_ = QString("s" ); // с
    else if (c.unicode() == m_consonantal[18].unicode()) c_ = QString("m" ); // м
    else if (c.unicode() == m_consonantal[19].unicode()) c_ = QString("t" ); // т
    else if (c.unicode() == m_consonantal[21].unicode()) c_ = QString("b" ); // б
    else if (c.unicode() == m_consonantal[22].unicode()) c_ = QString("g" ); // ґ

    else if (c.unicode() == m_loud        [0].unicode()) c_ = QString("u" ); // у
    else if (c.unicode() == m_loud        [1].unicode()) c_ = QString("e" ); // е
    else if (c.unicode() == m_loud        [2].unicode()) c_ = QString("i" ); // і
    else if (c.unicode() == m_loud        [3].unicode()) c_ = QString("a" ); // а
    else if (c.unicode() == m_loud        [4].unicode()) c_ = QString("o" ); // о
    else if (c.unicode() == m_loud        [5].unicode()) c_ = QString("y" ); // и

    else if (c.unicode() == m_doubleLoud  [0].unicode()) c_ = QString("ji" ); // ї
    else if (c.unicode() == m_doubleLoud  [1].unicode()) c_ = QString("je" ); // є
    else if (c.unicode() == m_doubleLoud  [2].unicode()) c_ = QString("ja" ); // я
    else if (c.unicode() == m_doubleLoud  [3].unicode()) c_ = QString("ju" ); // ю

    if (not isLower)
        c_[0] = c_[0].toUpper();
    return c_;
}

QString LatinkaConverter::translateLetter(QChar first, QChar second)
{
    QString res = translateLetter(first);
    if (second != QChar('\''))
        res += QString::fromUtf8("\u030C");

    if (isDoubleLoud(second)){
             if (second == m_doubleLoud[0]) second = m_loud[2];
        else if (second == m_doubleLoud[1]) second = m_loud[1];
        else if (second == m_doubleLoud[2]) second = m_loud[3];
        else if (second == m_doubleLoud[3]) second = m_loud[0];
        res += translateLetter(second);
    }
    return res;
}
