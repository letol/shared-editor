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
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB
#include <QFont>
#include <QFontDialog>
#include <QDebug>
#include <QTextBlock>
#include <QPainter>

#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad),
    server(),
    sharedEditor(server),
    fakeRemoteEditor(server), // TO BE REMOVED
    fakeRemoteChar('a'), // TO BE REMOVED
    colors{
        QColorConstants::Green,
        QColorConstants::Red,
        QColorConstants::Cyan,
        QColorConstants::Magenta,
        QColorConstants::Yellow,
        QColorConstants::LightGray
        }
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

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
    connect(ui->actionHighlight_owners, &QAction::triggered, this, &Notepad::setHighlightOwners);
    connect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
    connect(&sharedEditor, &SharedEditor::remoteCharInserted, this, &Notepad::remoteCharInsert);
    connect(&sharedEditor, &SharedEditor::remoteCharDeleted, this, &Notepad::remoteCharDelete);

// Disable menu actions for unavailable features
#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
    ui->actionPrint->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif

    // TO BE REMOVED
    addRemoteUser(fakeRemoteEditor.getSiteId());
    startTimer(5000);
}

Notepad::~Notepad()
{
    delete ui;
}

// TO BE REMOVED
void Notepad::timerEvent(QTimerEvent *event)
{
    int pos = rand()%ui->textEdit->document()->characterCount();
    qDebug() << "Remote typed: " << fakeRemoteChar << ", at pos: " << pos;
    fakeRemoteEditor.localInsert(fakeRemoteChar, pos);
    qDebug() << "fakeRemoteEditor: " << fakeRemoteEditor.to_string();
    server.dispatchMessages();
    fakeRemoteChar = fakeRemoteChar.toLatin1()+1;
}


void Notepad::newDocument()
{
    // TODO: new online document creation
}

void Notepad::open()
{
    // TODO: open online document
}

void Notepad::save()
{
    // TODO: remove
}

void Notepad::saveAs()
{
    // TODO: remove
}

void Notepad::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif // QT_CONFIG(printdialog)
    ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
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
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
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
                tr("The <b>Notepad</b> example demonstrates how to code a basic "
                   "text editor using QtWidgets"));

}

void Notepad::localChange(int position, int charsRemoved, int charsAdded)
{
    qDebug() << "pos" << position << "removed" << charsRemoved << "added" << charsAdded;

    if (!(ui->textEdit->document()->isEmpty() && ui->textEdit->document()->characterAt(0) == 0x2029)) {
        for (int i = position; i < position+charsRemoved; i++) {
            sharedEditor.localErase(position);
        }
        for (int i = position; i < position+charsAdded; i++) {
            sharedEditor.localInsert(ui->textEdit->document()->characterAt(i), i);
        }
    }

    //TODO: review signal blocking correctness
    bool oldState = ui->textEdit->document()->blockSignals(true);
    if (ui->actionHighlight_owners->isChecked()) {
        QTextCursor c(ui->textEdit->document());
        c.setPosition(position);
        c.setPosition(position+charsAdded, QTextCursor::KeepAnchor);
        QTextCharFormat format = c.charFormat();
        format.clearBackground();
        c.setCharFormat(format);
    }
    ui->textEdit->document()->blockSignals(oldState);

    qDebug() << "sharedEditor:" << sharedEditor.to_string();
    qDebug() << "TotChar:" << ui->textEdit->document()->characterCount();
    qDebug() << "TotBlocks:" << ui->textEdit->document()->blockCount();
    server.dispatchMessages(); // TODO: to be removed with real server
}

void Notepad::remoteCharInsert(int siteId, QChar value, int index)
{
    //TODO: review signal blocking correctness
    bool oldState = ui->textEdit->document()->blockSignals(true);
    auto it = remoteUserCursors.find(siteId);
    if (it != remoteUserCursors.end()) {
        QTextCursor c = it.value();
        c.setPosition(index);
        if (ui->actionHighlight_owners->isChecked()) {
            QTextCharFormat format;
            QColor remoteUserColor = remoteUserColors.find(siteId).value();
            format.setBackground(remoteUserColor);
            c.insertText(value, format);
        } else {
            c.insertText(value);
        }
    }
    ui->textEdit->document()->blockSignals(oldState);
    qDebug() << "TotChar:" << ui->textEdit->document()->characterCount();
    qDebug() << "TotBlocks:" << ui->textEdit->document()->blockCount();
}

void Notepad::remoteCharDelete(int siteId, int index)
{
    //TODO: review signal blocking correctness
    bool oldState = ui->textEdit->document()->blockSignals(true);
    auto it = remoteUserCursors.find(siteId);
    if (it != remoteUserCursors.end()) {
        QTextCursor c = it.value();
        c.setPosition(index);
        c.deleteChar();
    }
    ui->textEdit->document()->blockSignals(oldState);
    qDebug() << "TotChar:" << ui->textEdit->document()->characterCount();
    qDebug() << "TotBlocks:" << ui->textEdit->document()->blockCount();
}

void Notepad::setHighlightOwners(bool highlightOwners)
{
    //TODO: review signal blocking correctness
    bool oldState = ui->textEdit->document()->blockSignals(true);
    QTextCursor c(ui->textEdit->document());
    if (!ui->textEdit->document()->isEmpty()) {
        if (highlightOwners) {
            int pos = 0;
            int numChars = ui->textEdit->document()->characterCount();
            while (pos < numChars) {
                c.clearSelection();
                c.setPosition(pos);
                QTextCharFormat format;
                int siteId = sharedEditor.getSymbolSiteId(pos);
                int selection = 1;
                if (siteId != sharedEditor.getSiteId()) {
                    QColor remoteUserColor = remoteUserColors.find(siteId).value();
                    format.setBackground(remoteUserColor);
                    int nextSiteId = sharedEditor.getSymbolSiteId(pos+selection);
                    while (nextSiteId == siteId) {
                        selection++;
                        siteId = nextSiteId;
                        nextSiteId = sharedEditor.getSymbolSiteId(pos+selection);
                    }
                    c.setPosition(pos+selection, QTextCursor::KeepAnchor);
                    c.mergeCharFormat(format);
                }
                pos += selection;
            }
        } else {
            c.clearSelection();
            c.setPosition(0);
            c.setPosition(ui->textEdit->document()->characterCount()-1, QTextCursor::KeepAnchor);
            QTextCharFormat format = c.charFormat();
            format.clearBackground();
            c.setCharFormat(format);
        }
    }
    ui->textEdit->document()->blockSignals(oldState);
}

void Notepad::addRemoteUser(int siteId)
{
    if (!remoteUserCursors.contains(siteId)) {
        QColor c = colors[remoteUserCursors.size() % colors.size()];
        remoteUserCursors.insert(siteId, QTextCursor(ui->textEdit->document()));
        remoteUserColors.insert(siteId, c);
    }
}

void Notepad::removeRemoteUser(int siteId)
{
    if (remoteUserCursors.contains(siteId)) {
        remoteUserCursors.remove(siteId);
        remoteUserColors.remove(siteId);
    }
}

void Notepad::remoteCursorPositionChanged(int siteId, int newPos)
{
    auto it = remoteUserCursors.find(siteId);
    if (it != remoteUserCursors.end()) {
        QTextCursor c = it.value();
        c.setPosition(newPos);
    }
}

