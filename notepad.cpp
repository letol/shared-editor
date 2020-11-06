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

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB

#include "notepad.h"
#include "ui_notepad.h"
#include "onlineusersdialog.h"




const QString rsrcPath = ":/images";

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad),
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

    this->setCentralWidget(ui->centralWidget);

    this->setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; }");
    QToolBar *tb = ui->toolBar;
    const QIcon penMarkerIcon = QIcon::fromTheme("Highlight", QIcon(rsrcPath + "/marker.png"));

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

    textEditorEventFilter = new TextEditorEventFilter(this);
    ui->textEdit->installEventFilter(textEditorEventFilter);

    ui->mainToolBar->addAction(ui->actionOnlineUsers);
    QImage usersImage;
    usersImage.load(":/images/users-png.png");
    ui->actionOnlineUsers->setIcon(QIcon(QPixmap::fromImage(usersImage)));


    updateButton = new QToolButton(ui->menuBar);
    updateButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    updateButton->setPopupMode(QToolButton::InstantPopup);
    ui->menuBar->setCornerWidget(updateButton, Qt::TopRightCorner);
    connect(updateButton,&QToolButton::clicked, this, &Notepad::pushUpdateButton);

    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::changeFile);
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
    connect(&sharedEditor, &SharedEditor::remoteCharInserted, this, &Notepad::remoteCharInsert);
    connect(&sharedEditor, &SharedEditor::remoteCharDeleted, this, &Notepad::remoteCharDelete);
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
    connect(ui->textEdit->verticalScrollBar(), &QScrollBar::sliderMoved, this, &Notepad::updateCursors);
    connect(ui->actionOnlineUsers,&QAction::triggered,this,&Notepad::onlineUsersTriggered);
    connect(ui->textEdit,&QTextEdit::cursorPositionChanged,this,&Notepad::localCursorPositionChanged);


// Disable menu actions for unavailable features
#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
    ui->actionPrint->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif

    inactivity = new QTimer(this);
    connect(inactivity, &QTimer::timeout, this, &Notepad::showLabels);
}

Notepad::~Notepad()
{
    delete ui;
}

SharedEditor* Notepad::getSharedEditor()
{
    return &sharedEditor;
}

void Notepad::openNewDocument(const QString& name)
{
    sharedEditor.reset();
    emit newDocument(sharedEditor.getSymbols(), name);
}

void Notepad::updateButtonIcon(const QString &nameSurname, const QImage &image)
{
    QPixmap qImage = QPixmap::fromImage(image);
    QPixmap pixmap(50,50);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, 50, 50);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 50, 50, qImage);

    updateButton->setText(nameSurname);
    updateButton->setIcon(QIcon(pixmap));
}

void Notepad::openExistingDocument(QVector<Symbol>& symbols, QString name, QUuid uri)
{
    ui->textEdit->clear();
    setWindowTitle(name);
    this->uri=uri;
    sharedEditor.reset();
    foreach(Symbol sym, symbols) {
        sharedEditor.remoteInsert(EditingMessage(sym, MSG_INSERT, QUuid()));
    }
    connect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
    this->show();
    inactivity->start(3000);
}

void Notepad::changeFile()
{
    inactivity->stop();
    remoteUserColors.clear();
    showingLabels = false;
    disconnect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
    foreach(RemoteUser ru, remoteSites.values()) {
        ru.hideCursor();
    }
    remoteSites.clear();
    emit fileClosed();
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

    emit logout();
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
   QMessageBox::about(this, tr("About"),
                tr("This is a <b>Shared Editor</b> "));

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
    QTextCharFormat fmt = cursor.charFormat();

    fmt.setFontPointSize(pointSize);
    cursor.setCharFormat(fmt);
    ui->textEdit->setTextCursor( cursor );
    ui->textEdit->setFontPointSize(pointSize);
}

void Notepad::font(const QFont &f)
{

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    qreal size = fmt.fontPointSize();

    fmt.setFont(f);
    fmt.setFontPointSize(size);
    cursor.setCharFormat(fmt);

    ui->textEdit->setTextCursor( cursor );
    ui->textEdit->setCurrentFont(f);
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

void Notepad::localChange(int position, int charsRemoved, int charsAdded)
{
    inactivity->stop();
    if (showingLabels) {
        foreach(RemoteUser ru, remoteSites) {
            ru.hideLabel();
        }
    }

    QTextCursor c(ui->textEdit->document());

    if (charsRemoved == charsAdded && ui->textEdit->document()->characterAt(position+charsRemoved-1) == QChar::ParagraphSeparator) {
        charsRemoved--;
        charsAdded--;
    }

    int symbolsSize = sharedEditor.symbolCount();
    for (int i = position; i < position+charsRemoved && i < symbolsSize; i++) {
        sharedEditor.localErase(position);
    }


    for (int i = position; i < position+charsAdded; i++) {
        QChar ch = ui->textEdit->document()->characterAt(i);
        c.clearSelection();
        c.setPosition(i);
        c.setPosition(i+1, QTextCursor::KeepAnchor);
        QTextCharFormat fmt = c.charFormat();
        if (ui->actionHighlight_owners->isChecked()) fmt.clearBackground();
        QTextBlockFormat bfmt = c.blockFormat();
        sharedEditor.localInsert(ch, fmt, bfmt, i);
    }

    disconnect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
    if (ui->actionHighlight_owners->isChecked()) {
        QTextCursor c(ui->textEdit->document());
        c.setPosition(position);
        c.setPosition(position+charsAdded, QTextCursor::KeepAnchor);
        QTextCharFormat format = c.charFormat();
        format.clearBackground();
        c.setCharFormat(format);
    }
    connect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);

    inactivity->start(3000);
}

void Notepad::remoteCharInsert(QUuid &siteId, QString &owner, QChar value, QTextCharFormat &format, QTextBlockFormat &blockFormat, int index)
{
    disconnect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
    auto it = remoteSites.find(siteId);
    if (it != remoteSites.end()) {
        // Character inserted by online user
        QTextCursor *c = it.value().getCursor();
        c->setPosition(index);

        QTextCharFormat fmt = format;
        QColor ownerColor;

        auto colorsIt = remoteUserColors.find(owner);
        if (colorsIt == remoteUserColors.end()) {
            ownerColor = colors.at(remoteUserColors.size()+1 % colors.size());
            remoteUserColors.insert(owner, ownerColor);
        } else {
            ownerColor = colorsIt.value();
        }

        if (ui->actionHighlight_owners->isChecked() && owner != sharedEditor.getUserEmail()) {
            fmt.setBackground(ownerColor.lighter());
        }

        if (value == QChar::ParagraphSeparator) {
            c->insertBlock();
        } else {
            c->insertText(value, fmt);

            if (c->blockFormat() != blockFormat) {
                c->setBlockFormat(blockFormat);
            }
        }

        it.value().printCursor();
    } else {
        // Character inserted by offline user
        QTextCursor c(ui->textEdit->document());
        c.setPosition(index);

        QTextCharFormat fmt = format;
        QColor ownerColor;

        auto colorsIt = remoteUserColors.find(owner);
        if (colorsIt == remoteUserColors.end()) {
            ownerColor = colors.at(remoteUserColors.size()+1 % colors.size());
            remoteUserColors.insert(owner, ownerColor);
        } else {
            ownerColor = colorsIt.value();
        }

        if (ui->actionHighlight_owners->isChecked()) {
            fmt.setBackground(ownerColor.lighter());
        }

        if (value == QChar::ParagraphSeparator) {
            c.insertBlock();
        } else {
            c.insertText(value, fmt);

            if (c.blockFormat() != blockFormat) {
                c.setBlockFormat(blockFormat);
            }
        }
    }
    connect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
}

void Notepad::remoteCharDelete(QUuid &siteId, int index)
{
    disconnect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
    auto it = remoteSites.find(siteId);
    if (it != remoteSites.end()) {
        QTextCursor *c = it.value().getCursor();
        c->setPosition(index);
        it.value().printCursor();
        c->deleteChar();
    }
    connect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
}

void Notepad::setHighlightOwners(bool highlightOwners)
{
    disconnect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
    QTextCursor c(ui->textEdit->document());
    if (!ui->textEdit->document()->isEmpty()) {
        int pos = 0;
        int numChars = ui->textEdit->document()->characterCount();
        if (highlightOwners) {
            while (pos < numChars-1) {
                c.clearSelection();
                c.setPosition(pos);
                QTextCharFormat format;
                QString owner = sharedEditor.getSymbolOwner(pos);
                int selection = 1;
                if (owner != sharedEditor.getUserEmail()) {
                    QColor remoteUserColor = remoteUserColors.find(owner).value();
                    format.setBackground(remoteUserColor.lighter());
                    if (pos+selection < numChars-1) {
                        QString nextOwner = sharedEditor.getSymbolOwner(pos+selection);
                        while (nextOwner == owner && pos+selection < numChars-2) {
                            selection++;
                            owner = nextOwner;
                            nextOwner = sharedEditor.getSymbolOwner(pos+selection);
                        }
                    }
                    c.setPosition(pos+selection, QTextCursor::KeepAnchor);
                    c.mergeCharFormat(format);
                }
                pos += selection;
            }
        } else {
            while (pos < numChars-1) {
                c.clearSelection();
                c.setPosition(pos);
                c.setPosition(pos+1, QTextCursor::KeepAnchor);
                QTextCharFormat format = sharedEditor.getSymbolFormat(pos);
                c.setCharFormat(format);
                pos++;
            }
        }
    }
    connect(ui->textEdit->document(), &QTextDocument::contentsChange, this, &Notepad::localChange);
}


void Notepad::addRemoteUser(QUuid siteId, User userInfo)
{
    if (!remoteSites.contains(siteId)) {
        QColor userColor;

        auto userColorTuple = remoteUserColors.find(userInfo.getEmail());
        if (userColorTuple == remoteUserColors.end()) {
            userColor = colors.at(remoteUserColors.size()+1 % colors.size());
            remoteUserColors.insert(userInfo.getEmail(), userColor);
        } else {
            userColor = userColorTuple.value();
        }

        auto it = remoteSites.insert(siteId, RemoteUser(ui->textEdit, siteId, userColor, userInfo));
        it.value().printCursor();
    }
}

void Notepad::removeRemoteUser(QUuid siteId)
{
    auto it = remoteSites.find(siteId);
    if (it != remoteSites.end()) {
        it.value().hideCursor();
        remoteSites.remove(siteId);
    }
}

void Notepad::localCursorPositionChanged()
{
    emit newCursorPosition(ui->textEdit->textCursor().position());
}

void Notepad::remoteCursorPositionChanged(QUuid siteId, int newPos)
{
    auto it = remoteSites.find(siteId);
    if (it != remoteSites.end()) {
        QTextCursor *c = it.value().getCursor();
        c->setPosition(newPos);
        it.value().printCursor();
    }
}

void Notepad::getOnlineUsers(QMap<QUuid, User> users)
{
    foreach(QUuid uid, users.keys())
    {
        addRemoteUser(uid,users.value(uid));
    }

}



void Notepad::updateCursors(int)
{
    for (RemoteUser u : remoteSites) {
        u.printCursor();
    }
}

void Notepad::onlineUsersTriggered()
{
    OnlineUsersDialog *onlineUsersDialog = new OnlineUsersDialog(remoteSites.values(), this);
    onlineUsersDialog->show();
}

void Notepad::pushUpdateButton()
{
    emit showUpdateForm();
}

void Notepad::on_actionGet_URI_triggered()
{
   QString uriMessage = this->uri.toString().remove("{");
   uriMessage.remove("}");
   QMessageBox::information(this,"URI","Copy and share with your collaborators:\nshared-editor://"+uriMessage);
}

void Notepad::showLabels() {
    showingLabels = true;
    foreach(RemoteUser ru, remoteSites) {
        ru.printLabel();
    }
}
