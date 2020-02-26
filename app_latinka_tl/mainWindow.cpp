#include "mainWindow.h"
#include "lib_latinka_tl/latinkaConverter.h"

MainWindow::MainWindow()
{
    m_result = new QLabel(this);
    m_result->setFixedHeight(200);
    m_result->setAlignment(Qt::AlignTop);

    m_textEdit = new QTextEdit(this);
    m_layout = new QVBoxLayout(this);

    this->resize(500, 500);
    m_layout->addWidget(m_textEdit);
    m_layout->addWidget(m_result);

    m_layout->setMargin(10);
    m_layout->setSpacing(10);

    this->setLayout(m_layout);
    QObject::connect(m_textEdit, &QTextEdit::textChanged, this, &MainWindow::updateLatinka);
}

void MainWindow::updateLatinka()
{
    auto newText = Latinka::Converter::run(Latinka::Alphabet::Latin,m_textEdit->toPlainText().toStdWString());
    m_result->setText(QString::fromStdWString(newText));
}
