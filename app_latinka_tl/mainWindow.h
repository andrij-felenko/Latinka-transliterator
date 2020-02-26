#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLabel>
#include "lib_latinka_tl/latinkaConverter.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();

    void updateLatinka();

private:
    QLabel *m_left;
    QLabel *m_right;
    QTextEdit *m_result;
    QTextEdit *m_textEdit;
    Latinka::Alphabet currentAlp;
};
