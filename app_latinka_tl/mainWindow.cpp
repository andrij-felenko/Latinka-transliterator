#include "mainWindow.h"
#include <QtWidgets>
#include <QFile>
#include <QPixmap>

MainWindow::MainWindow() : currentAlp(Latinka::Alphabet::Latin)
{
    tabBar()->setExpanding(true);

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
    headerLayout->addWidget(m_left);
    headerLayout->addWidget(switchB);
    headerLayout->addWidget(m_right);

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
    mainLayout->setContentsMargins(10, 10, 10, 10);

    convertWidget->setLayout(mainLayout);
    this->addTab(convertWidget, "Транслітерування");

    QObject::connect(switchB, &QPushButton::clicked, [=](){
        currentAlp = currentAlp == Latinka::Alphabet::Latin ? Latinka::Alphabet::Cyrillic : Latinka::Alphabet::Latin;
        m_left->setText(currentAlp == Latinka::Alphabet::Latin ? "Latynka" : "Українська");
        m_right->setText(currentAlp == Latinka::Alphabet::Latin ? "Українська" : "Latynka");
        m_textEdit->setText(m_result->toPlainText());
    });
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
    this->resize(750, 600);
}

void MainWindow::createHelpWindow()
{
    QWidget* alpWidget = new QWidget();
    QHBoxLayout* alpLayout = new QHBoxLayout(alpWidget);
    alpLayout->addWidget(new QWidget(this));
    QTextBrowser* alpHtml = new QTextBrowser();
    alpHtml->setSource(QUrl("qrc:/alphabet.html"));
    alpHtml->setMaximumWidth(400);
    alpHtml->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    alpHtml->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    alpLayout->addWidget(alpHtml);
    alpLayout->addWidget(new QWidget(this));
    addTab(alpWidget, "Aлфавіт");

    QTextBrowser* rulesHtml = new QTextBrowser();
    rulesHtml->setSource(QUrl("qrc:/rules.html"));
    rulesHtml->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    rulesHtml->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    addTab(rulesHtml, "Правила");

    QTextBrowser* xkbHtml = new QTextBrowser();
    xkbHtml->setSource(QUrl("qrc:/xkb.html"));
    addTab(xkbHtml, "Xkb файл");

    QWidget* keybWidget = new QWidget();
    QVBoxLayout* keybLayout = new QVBoxLayout(keybWidget);
    keybLayout->addWidget(new QWidget(this));
    QTextBrowser* keybHtml = new QTextBrowser();
    keybHtml->setSource(QUrl("qrc:/keyboard_layout.html"));
    keybHtml->setMaximumHeight(400);
    keybHtml->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    keybHtml->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    keybLayout->addWidget(keybHtml);
    keybLayout->addWidget(new QWidget(this));
    keybWidget->setLayout(keybLayout);
    addTab(keybWidget, "Розкладка");
}
