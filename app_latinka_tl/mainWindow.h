#include <QtWidgets/QTabWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include "lib_latinka_tl/latinkaConverter.h"

class MainWindow : public QTabWidget
{
//    Q_OBJECT
public:
    MainWindow();

    void updateLatinka();

private:
    void createTranslitterateWindow();
    void createHelpWindow();

    QLabel *m_left;
    QLabel *m_right;
    QTextEdit *m_result;
    QTextEdit *m_textEdit;
    Latinka::Alphabet currentAlp;
};
