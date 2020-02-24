#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLabel>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();

    void updateLatinka();

private:
    QLabel *m_result;
    QTextEdit *m_textEdit;
    QVBoxLayout *m_layout;
};
