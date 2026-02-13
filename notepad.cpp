#include "notepad.h"
#include "./ui_notepad.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QPalette>
#include <QColor>
#include <QFont>
#include <QTextCharFormat>
#include <QApplication>
#include <QFontDialog>
#include <QTextEdit>
#include <QBrush>
#include <QComboBox>
#include <QToolBar>
#include <QSpinBox>
#include <QStatusBar>
#include <QLineEdit>
#include <QCloseEvent>
Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);



    toolbar = ui->toolBar;
    statusbar = ui->statusBar;

    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItem("Sitka");
    comboBox->addItem("Arial");
    comboBox->addItem("Times New Roman");
    comboBox->addItem("Impact");
    comboBox->addItem("MS Serif");

    connect(comboBox, &QComboBox::currentTextChanged,
            [this](const QString &text) {
                ui->textEdit->setFontFamily(text);
            });
    toolbar->insertWidget(ui->actionItalic,comboBox);

    QComboBox *comboBox1 = new QComboBox(this);
    comboBox1->addItem("White");
    comboBox1->addItem("Black");
    comboBox1->addItem("Blue");
    comboBox1->addItem("Red");
    comboBox1->addItem("Green");

    connect(comboBox1, &QComboBox::currentTextChanged,
            [this](const QString &colorName) {
                QColor color = Qt::white;
                if (colorName == "White") color = Qt::white;
                else if (colorName == "Black") color = Qt::black;
                else if (colorName == "Blue") color = Qt::blue;
                else if (colorName == "Red") color = Qt::red;
                else if (colorName == "Green") color = Qt::green;

                QTextCharFormat format;
                format.setForeground(color);
                ui->textEdit->mergeCurrentCharFormat(format);
            });
    toolbar->insertWidget(ui->actionAlignLeft,comboBox1);

    QSpinBox *spinbox = new QSpinBox(this);
    spinbox->setRange(8,72);
    connect(spinbox, &QSpinBox::valueChanged, [this](const int &size_text) {ui->textEdit->setFontPointSize(size_text);});
    toolbar->insertWidget(ui->actionItalic,spinbox);

    connect(ui->textEdit, &QTextEdit::textChanged, this, &Notepad::updateStats);
}


Notepad::~Notepad()
{
    delete ui;
}

void Notepad::closeEvent(QCloseEvent *event) {
    if (maybeSave())
        event->accept();
    else
        event->ignore();
}

void Notepad::updateStats() {
    QString text = ui->textEdit->toPlainText();
    int chars = text.length();
    int words = text.simplified().split(' ', Qt::SkipEmptyParts).count();
    int lines = text.count('\n') + 1;

    statusBar()->showMessage(
        QString("Chars: %1 | Words: %2 | Lines: %3")
        .arg(chars).arg(words).arg(lines)
    );
}

bool Notepad::maybeSave()
{
    if(!ui->textEdit->document()->isModified())
        return true;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Notepad", "Save changes?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (reply == QMessageBox::Save){
        on_actionSave_triggered();
        return !ui->textEdit->document()->isModified();
    }
    else if (reply == QMessageBox::Discard) {
        return true;
    }
    else {
        return false;
    }
}

void Notepad::on_actionCreate_triggered()
{
    if (!maybeSave())
        return;

    file_path.clear();
    ui->textEdit->clear();
    ui->textEdit->document()->setModified(false);
}


void Notepad::on_actionOpen_triggered()
{
    if (!maybeSave())
        return;

    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    if (file_name.isEmpty())
        return;

    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "File not open!");
        return;
    }

    QTextStream in(&file);
    ui->textEdit->setHtml(in.readAll());
    file.close();

    file_path = file_name;
    ui->textEdit->document()->setModified(false);
}


void Notepad::on_actionSave_triggered()
{
    if (file_path.isEmpty()) {
            on_actionSave_us_triggered();
            return;
        }

    QFile file(file_path);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error 1", "File not open!");
        return;
    }
    QTextStream out(&file);
    QString text = ui -> textEdit->toHtml();
    out << text;
    file.flush();
    file.close();

    ui->textEdit->document()->setModified(false);
}


void Notepad::on_actionSave_us_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save the file");
    if (file_name.isEmpty())
        return;

    QFile file(file_name);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "Cannot save file!");
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toHtml();
    file.flush();
    file.close();

    file_path = file_name;
    ui->textEdit->document()->setModified(false);
}


void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void Notepad::on_actionAbout_triggered()
{
    QString inf = "This is Simple Notepad!\n"
                  "version: 1.0 'SAO'\n"
                  "Made by Grisha Oshi =)                    ";
    QMessageBox::about(this, "About Programm", inf);
}

void Notepad::on_actionStrikeOut_triggered()
{
    QTextCharFormat format;
    format.setFontStrikeOut(!ui->textEdit->textCursor().charFormat().fontStrikeOut());
    ui->textEdit->mergeCurrentCharFormat(format);
}

void Notepad::on_actionBold_triggered()
{
    QTextCharFormat format;
    format.setFontWeight(ui->textEdit->textCursor().charFormat().fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
    ui->textEdit->mergeCurrentCharFormat(format);
}


void Notepad::on_actionItalic_triggered()
{
    QTextCharFormat format;
    format.setFontItalic(!ui->textEdit->textCursor().charFormat().fontItalic());
    ui->textEdit->mergeCurrentCharFormat(format);
}

void Notepad::on_actionUnderline_triggered()
{
    QTextCharFormat format;
    format.setFontUnderline(!ui->textEdit->textCursor().charFormat().fontUnderline());
    ui->textEdit->mergeCurrentCharFormat(format);
}

void Notepad::on_actionBacklight_triggered()   //часто ли вы юзаете разные цвета подсветки? how often do you use different colors?
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;

    if (cursor.charFormat().background().color() == QColor(0, 240, 240, 120)) {
        format.setBackground(Qt::NoBrush);
    } else {
        format.setBackground(QColor(0, 240, 240, 120));
    }

    cursor.mergeCharFormat(format);
}


void Notepad::on_actionAlignLeft_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}


void Notepad::on_actionAlign_enter_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}


void Notepad::on_actionAlignRight_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

