#include <QtCore>

class LatinkaConverter
{
public:
    LatinkaConverter();

    QString toLatinka(QString text);

private:
    void retranslate(QString& str);
    bool isLoud       (const QChar& c);
    bool isDoubleLoud (const QChar& c);
    bool isConsonantal(const QChar& c);
    bool isLetter     (const QChar& c);

    QString translateLetter(QChar c);
    QString translateLetter(QChar c1, QChar c2);

    QString m_consonantal;
    QString m_doubleLoud;
    QString m_loud;
};
