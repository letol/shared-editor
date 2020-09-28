/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QTextBlockFormat>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextCodec>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QFontDialog>
#include <QMimeDatabase>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB

const QString rsrcPath = ":/images";



#include "notepad.h"
#include "ui_notepad.h"

/*#ifdef Q_OS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif*/

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{

    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);


    QToolBar *tb = ui->toolBar;

    const QIcon penMarkerIcon = QIcon::fromTheme("Highlight", QIcon(rsrcPath + "/marker.png"));


    comboStyle = new QComboBox(tb);
    tb->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");
    comboStyle->addItem("Heading 1");
    comboStyle->addItem("Heading 2");
    comboStyle->addItem("Heading 3");
    comboStyle->addItem("Heading 4");
    comboStyle->addItem("Heading 5");
    comboStyle->addItem("Heading 6");


    comboFont = new QFontComboBox(tb);
    tb->addWidget(comboFont);

    comboSize = new QComboBox(tb);
    comboSize->setObjectName("comboSize");
    tb->addWidget(comboSize);
    const QList<int> standardSizes = QFontDatabase::standardSizes();
    for (int size : standardSizes)
           comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    tb->addSeparator();

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = ui->toolBar->addAction(pix, tr("&Color..."), this, &Notepad::textColor);
    tb->addAction(actionTextColor);

    QPixmap pm(16, 16);
    actionHighlight = ui->toolBar->addAction(pm, tr("&Highlight..."), this, &Notepad::textHighlight);
    tb->addAction(actionHighlight);
    actionHighlight->setIcon(penMarkerIcon);




    connect(ui->actionNew, &QAction::triggered, this, &Notepad::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::open);
    connect(ui->actionSave, &QAction::triggered, this, &Notepad::save);
    connect(ui->actionSave_as, &QAction::triggered, this, &Notepad::saveAs);
    connect(ui->actionPrint, &QAction::triggered, this, &Notepad::print);
    connect(ui->actionExit, &QAction::triggered, this, &Notepad::exit);
    connect(ui->actionCopy, &QAction::triggered, this, &Notepad::copy);
    connect(ui->actionCut, &QAction::triggered, this, &Notepad::cut);
    connect(ui->actionPaste, &QAction::triggered, this, &Notepad::paste);
    connect(ui->actionUndo, &QAction::triggered, this, &Notepad::undo);
    connect(ui->actionRedo, &QAction::triggered, this, &Notepad::redo);
    connect(ui->actionFont, &QAction::triggered, this, &Notepad::selectFont);
    connect(ui->actionBold, &QAction::triggered, this, &Notepad::setFontBold);
    connect(ui->actionUnderline, &QAction::triggered, this, &Notepad::setFontUnderline);
    connect(ui->actionItalic, &QAction::triggered, this, &Notepad::setFontItalic);
    connect(ui->actionAbout, &QAction::triggered, this, &Notepad::about);
    connect(ui->actionAt_left,&QAction::triggered,this,&Notepad::on_actionAt_left_triggered);
    connect(ui->actionCentered,&QAction::triggered,this,&Notepad::on_actionCentered_triggered);
    connect(ui->actionAt_right,&QAction::triggered,this,&Notepad::on_actionAt_right_triggered);
    connect(ui->actionAt_left_2,&QAction::triggered,this,&Notepad::on_actionAt_left_triggered);
    connect(ui->actionCentered_2,&QAction::triggered,this,&Notepad::on_actionCentered_triggered);
    connect(ui->actionAt_right_2,&QAction::triggered,this,&Notepad::on_actionAt_right_triggered);
    connect(ui->action6,&QAction::triggered,this,&Notepad::on_action6_triggered);
    connect(ui->action7,&QAction::triggered,this,&Notepad::on_action7_triggered);
    connect(ui->action8,&QAction::triggered,this,&Notepad::on_action8_triggered);
    connect(ui->action9,&QAction::triggered,this,&Notepad::on_action9_triggered);
    connect(ui->action10,&QAction::triggered,this,&Notepad::on_action10_triggered);
    connect(ui->action11,&QAction::triggered,this,&Notepad::on_action11_triggered);
    connect(ui->action12,&QAction::triggered,this,&Notepad::on_action12_triggered);
    connect(ui->action14,&QAction::triggered,this,&Notepad::on_action14_triggered);
    connect(ui->action18,&QAction::triggered,this,&Notepad::on_action18_triggered);
    connect(ui->action24,&QAction::triggered,this,&Notepad::on_action24_triggered);
    connect(ui->action36,&QAction::triggered,this,&Notepad::on_action36_triggered);
    connect(comboSize, SIGNAL(currentTextChanged(QString)), this, SLOT(size(QString)));
    connect(comboFont,SIGNAL(currentFontChanged(const QFont)),this,SLOT(font(QFont)));
    connect(comboStyle, SIGNAL(activated(int)), this, SLOT(style(int)));






// Disable menu actions for unavailable features
#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
    ui->actionPrint->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif
}


Notepad::~Notepad()
{
    delete ui;
}


void Notepad::newDocument()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::save()
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::print()
{

    QPrinter printDev;
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
    ui->textEdit->print(&printDev);
}

void Notepad::exit()
{
    QCoreApplication::quit();
}

void Notepad::copy()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->copy();
#endif
}

void Notepad::cut()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->cut();
#endif
}

void Notepad::paste()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->paste();
#endif
}

void Notepad::undo()
{
     ui->textEdit->undo();
}

void Notepad::redo()
{
    ui->textEdit->redo();
}

void Notepad::selectFont()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        fmt.setFont(font);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::setFontUnderline(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}

void Notepad::setFontItalic(bool italic)
{
    ui->textEdit->setFontItalic(italic);
}

void Notepad::setFontBold(bool bold)
{
    bold ? ui->textEdit->setFontWeight(QFont::Bold) :
           ui->textEdit->setFontWeight(QFont::Normal);
}

void Notepad::about()
{
   QMessageBox::about(this, tr("About MDI"),
                tr("This is a rech <b>Notepad</b> "));

}



void Notepad::on_actionExport_PDF_triggered()
{
    QFileDialog fileDialog(this, tr("Export PDF"));
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
        fileDialog.setDefaultSuffix("pdf");
        if (fileDialog.exec() != QDialog::Accepted)
            return;
        QString fileName = fileDialog.selectedFiles().first();
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->textEdit->document()->print(&printer);
        statusBar()->showMessage(tr("Exported \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));
}


void Notepad::on_actionAt_left_triggered()
{
    ui->textEdit->
            setAlignment(Qt::AlignLeft);
}

void Notepad::on_actionCentered_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void Notepad::on_actionAt_right_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void Notepad::on_action6_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(6);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action36_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(36);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action7_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(7);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action8_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(8);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action9_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(9);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action10_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(10);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action11_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(11);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action12_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(12);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action14_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(14);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action24_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(24);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::on_action18_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(18);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::size(const QString &text)
{
    qreal pointSize = text.toFloat();
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(pointSize);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
}

void Notepad::font(const QFont &f)
{

   QTextCursor cursor = ui->textEdit->textCursor();
   QTextCharFormat fmt = ui->textEdit->currentCharFormat();
   qreal size = fmt.fontPointSize();
   if(size==0)
       size=8;


   fmt.setFont(f);
   fmt.setFontPointSize(size);
   cursor.mergeCharFormat(fmt);

   ui->textEdit->setTextCursor( cursor );

}

void Notepad::style(int styleIndex){
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextListFormat::Style style = QTextListFormat::ListStyleUndefined;


       switch (styleIndex) {
       case 1:
           style = QTextListFormat::ListDisc;
           break;
       case 2:
           style = QTextListFormat::ListCircle;
           break;
       case 3:
           style = QTextListFormat::ListSquare;
           break;
       case 4:
           style = QTextListFormat::ListDecimal;
           break;
       case 5:
           style = QTextListFormat::ListLowerAlpha;
           break;
       case 6:
           style = QTextListFormat::ListUpperAlpha;
           break;
       case 7:
           style = QTextListFormat::ListLowerRoman;
           break;
       case 8:
           style = QTextListFormat::ListUpperRoman;
           break;
       default:
           break;
       }

       cursor.beginEditBlock();

       QTextBlockFormat blockFmt = cursor.blockFormat();

       if (style == QTextListFormat::ListStyleUndefined) {
           blockFmt.setObjectIndex(-1);
           int headingLevel = styleIndex >= 11 ? styleIndex - 11 + 1 : 0; // H1 to H6, or Standard
           blockFmt.setHeadingLevel(headingLevel);
           cursor.setBlockFormat(blockFmt);

           int sizeAdjustment = headingLevel ? 4 - headingLevel : 0; // H1 to H6: +3 to -2
           QTextCharFormat fmt;
           fmt.setFontWeight(headingLevel ? QFont::Bold : QFont::Normal);
           fmt.setProperty(QTextFormat::FontSizeAdjustment, sizeAdjustment);
           cursor.select(QTextCursor::LineUnderCursor);
           cursor.mergeCharFormat(fmt);
           ui->textEdit->mergeCurrentCharFormat(fmt);
       } else {

           cursor.setBlockFormat(blockFmt);
           QTextListFormat listFmt;
           if (cursor.currentList()) {
               listFmt = cursor.currentList()->format();
           } else {
               listFmt.setIndent(blockFmt.indent() + 1);
               blockFmt.setIndent(0);
               cursor.setBlockFormat(blockFmt);
           }
           listFmt.setStyle(style);
           cursor.createList(listFmt);
       }

       cursor.endEditBlock();

}
void Notepad::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}
void Notepad::textColor()
{
    QColor col = QColorDialog::getColor(ui->textEdit->textColor(), this);
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!col.isValid())
        return;
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setForeground(col);
    cursor.mergeCharFormat(fmt);
    colorChanged(col);
    ui->textEdit->setTextCursor( cursor );
}



void Notepad::textHighlight()
{
    QColor col = QColorDialog::getColor(ui->textEdit->textColor(), this);
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!col.isValid())
        return;
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setBackground(col);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );


}

