#include "mainWindow.h"
#include <QtWidgets>
#include <QFile>

MainWindow::MainWindow() : currentAlp(Latinka::Alphabet::Latin)
{
    createTranslitterateWindow();
    createHelpWindow();
}

void MainWindow::updateLatinka()
{
    auto converted = Latinka::Converter::run(currentAlp, m_textEdit->toPlainText().toStdWString());
    m_result->setText(QString::fromStdWString(converted));
}

void MainWindow::createTranslitterateWindow()
{
    QWidget* convertWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QWidget* header = new QWidget(this);
    header->setMaximumHeight(50);

    QHBoxLayout* headerLayout = new QHBoxLayout(header);
    m_left = new QLabel(this);
    m_right = new QLabel(this);
    m_right->setAlignment(Qt::AlignRight);
    QPushButton* switchB = new QPushButton("< – >");
    switchB->setFixedWidth(40);
    QPushButton* helpB = new QPushButton("?");
    helpB->setFixedSize(30, 30);
    headerLayout->addWidget(m_left);
    headerLayout->addWidget(switchB);
    headerLayout->addWidget(m_right);
    headerLayout->addWidget(helpB);

    QHBoxLayout* textLayout = new QHBoxLayout();
    m_result = new QTextEdit(this);
    m_result->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_result->setReadOnly(true);

    m_textEdit = new QTextEdit(this);

    textLayout->addWidget(m_textEdit, 2);
    textLayout->addWidget(m_result, 2);

    mainLayout->addWidget(header);
    mainLayout->addLayout(textLayout);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(10);

    convertWidget->setLayout(mainLayout);
    this->addWidget(convertWidget);

    QObject::connect(switchB, &QPushButton::clicked, [=](){
        currentAlp = currentAlp == Latinka::Alphabet::Latin ? Latinka::Alphabet::Cyrillic : Latinka::Alphabet::Latin;
        m_left->setText(currentAlp == Latinka::Alphabet::Latin ? "Latinka" : "Українська");
        m_right->setText(currentAlp == Latinka::Alphabet::Latin ? "Українська" : "Latinka");
        m_textEdit->setText(m_result->toPlainText());
    });
    QObject::connect(helpB, &QPushButton::clicked, [=](){ setCurrentIndex(1); });
    switchB->click();

    QObject::connect(m_textEdit, &QTextEdit::textChanged, this, &MainWindow::updateLatinka);
    QObject::connect(m_textEdit->verticalScrollBar(), &QScrollBar::valueChanged, m_result->verticalScrollBar(), &QScrollBar::setValue);
    QObject::connect(m_result->verticalScrollBar(), &QScrollBar::valueChanged, m_textEdit->verticalScrollBar(), &QScrollBar::setValue);

    QFile file(":/choven.txt");
    if (file.open(QIODevice::Text | QIODevice::ReadOnly)){
        m_textEdit->setText(file.readAll());
    }
    else
        qDebug() << "File not open: " << file.errorString();

    this->setMinimumSize(500, 400);
    this->resize(700, 600);
}

void MainWindow::createHelpWindow()
{
    QWidget* helpWidget = new QWidget();
    QGridLayout* grid = new QGridLayout(helpWidget);

    QPushButton* backB = new QPushButton("x");
    backB->setFixedWidth(25);
    QObject::connect(backB, &QPushButton::clicked, [=](){ setCurrentIndex(0); });
    grid->addWidget(backB, 0, 8, 1, 1);

    QTextBrowser* alpHtml = new QTextBrowser();
    alpHtml->setFixedWidth(120);
    auto alpFont = alpHtml->font();
    alpFont.setFamily("monospace [Consolas]");
    alpFont.setFixedPitch(true);
    alpHtml->setFont(alpFont);
    alpHtml->setText("  Алфавіт\n"
                     "а  А  a  A\n"
                     "б  Б  b  B\n"
                     "в  В  v  V\n"
                     "г  Г  h  H\n"
                     "ґ  Ґ  g  G\n"
                     "д  Д  d  D\n"
                     "е  Е  e  E\n"
                     "є  Є  je Je\n"
                     "ж  Ж  ʒ  Ʒ\n"
                     "з  З  z  Z\n"
                     "и  И  y  Y\n"
                     "і  І  i  I\n"
                     "ї  Ї  ji Ji\n"
                     "й  Й  j  J\n"
                     "к  К  k  K\n"
                     "л  Л  l  L\n"
                     "м  М  m  M\n"
                     "н  Н  n  N\n"
                     "о  О  o  O\n"
                     "п  П  p  P \n"
                     "р  Р  r  R\n"
                     "с  С  s  S\n"
                     "т  Т  t  T\n"
                     "у  У  u  U\n"
                     "ф  Ф  f  F\n"
                     "х  Х  x  X\n"
                     "ц  Ц  c  C\n"
                     "ч  Ч  ć  Č\n"
                     "ш  Ш  ś  Š\n"
                     "щ  Щ  ść Šć\n"
                     "я  Я  ja Ja\n"
                     "ю  Ю  ju Ju\n"
                     "вв Вв w  W\n");
//    alpHtml->document()->setPageSize(QSize(120, 1000));
    grid->addWidget(alpHtml, 0, 0, 15, 1);
    alpHtml->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    alpHtml->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    QTextBrowser* rulesHtml = new QTextBrowser();
    rulesHtml->setSource(QUrl("qrc:/rules.html"));
    grid->addWidget(rulesHtml, 0, 1, 8, 4);
    rulesHtml->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    rulesHtml->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    QLabel* xkbTitle = new QLabel();
    xkbTitle->setText("XKB файл");
    xkbTitle->setAlignment(Qt::AlignCenter);
    grid->addWidget(xkbTitle, 0, 5, 1, 3);

    QTextBrowser* xkbHtml = new QTextBrowser();
    xkbHtml->setSource(QUrl("qrc:/latinka_rules.html"));
    grid->addWidget(xkbHtml, 1, 5, 7, 4);

    QLabel* keybLayout = new QLabel();
    grid->addWidget(keybLayout, 8, 1, 7, 8);

    helpWidget->setLayout(grid);
    this->addWidget(helpWidget);
}
