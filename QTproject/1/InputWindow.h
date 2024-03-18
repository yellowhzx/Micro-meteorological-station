#ifndef CLASSSUBWINDOW_H
#define CLASSSUBWINDOW_H

#include <QDialog>
#include <ClassData.h>

namespace Ui {
class InputWindow;
}

class InputWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InputWindow(QWidget *parent = nullptr);
    ~InputWindow();

    void showDataFromMainWindow(ClassData &info39, ClassData &info3000);
    void closeEvent(QCloseEvent *event);

private:
    Ui::InputWindow *ui;
    ClassData m_InputData;

public slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void signal_sendDataToMainWindow(int nFlag, ClassData &info39, ClassData &info3000);
};

#endif // INPUTWINDOW_H
