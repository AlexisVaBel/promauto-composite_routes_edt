#pragma once

#include <QInputDialog>
#include <QString>
#include <QTextCodec>
#include <QLineEdit>



QString get_user_input(QString str, QString strLabel = "----", QString strCaption = "QInputDialog::getText()" )
{

    bool ok;
    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QString strUserInput = QInputDialog::getText(nullptr, ("QInputDialog::getText()"), strLabel,
                                                          QLineEdit::Normal, codec->toUnicode(str.toLocal8Bit()), &ok);


    if(ok && !strUserInput.isEmpty()) return strUserInput;

    return "";

}
