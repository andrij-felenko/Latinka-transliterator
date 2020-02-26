#include "mainWindow.h"
#include <QtWidgets>
#include <QFile>

MainWindow::MainWindow() : currentAlp(Latinka::Alphabet::Latin)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QWidget* header = new QWidget(this);
    header->setMaximumHeight(50);

    QHBoxLayout* headerLayout = new QHBoxLayout(header);
    m_left = new QLabel(this);
    m_left->setText("Latinka");
    m_right = new QLabel(this);
    m_right->setText("Українська");
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
    mainLayout->setMargin(10);

    this->setLayout(mainLayout);

    QObject::connect(switchB, &QPushButton::clicked, [=](){
        currentAlp = currentAlp == Latinka::Alphabet::Latin ? Latinka::Alphabet::Cyrillic : Latinka::Alphabet::Latin;
        m_left->setText(currentAlp == Latinka::Alphabet::Latin ? "Latinka" : "Українська");
        m_right->setText(currentAlp == Latinka::Alphabet::Latin ? "Українська" : "Latinka");
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
    this->resize(700, 600);
}

void MainWindow::updateLatinka()
{
    auto converted = Latinka::Converter::run(currentAlp, m_textEdit->toPlainText().toStdWString());
    m_result->setText(QString::fromStdWString(converted));
}
