#include "mainWindow.h"
#include "latinkaConverter.h"
#include "latinkaConverterStd.h"

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
//    static LatinkaConverter latinka;
//    m_result->setText(latinka.toLatinka(m_textEdit->toPlainText()));
    static LatinkaConverterStd latinkaStd;
    m_result->setText(QString::fromStdWString(latinkaStd.toLatinka(m_textEdit->toPlainText().toStdWString())));
}
