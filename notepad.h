#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Notepad;
}
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_actionCreate_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_us_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionAbout_triggered();

    void on_actionItalic_triggered();

    void on_actionBold_triggered();

    void on_actionStrikeOut_triggered();

    void on_actionUnderline_triggered();

    void on_actionBacklight_triggered();

    void on_actionAlignLeft_triggered();

    void on_actionAlign_enter_triggered();

    void on_actionAlignRight_triggered();

private:
    Ui::Notepad *ui;
    QString file_path;
    QToolBar *toolbar;
    QStatusBar *statusbar;
    void updateStats();
    bool maybeSave();
};
#endif // NOTEPAD_H
