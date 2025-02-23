/*
 *  Manjaro Settings Manager
 *  Roland Singer <roland@manjaro.org>
 *
 *  Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ACCOUNTTYPEDIALOG_H
#define ACCOUNTTYPEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QFile>
#include <QTextStream>
#include <const.h>
#include <global.h>


namespace Ui {
class AccountTypeDialog;
}



class AccountTypeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AccountTypeDialog(QWidget *parent = 0);
    ~AccountTypeDialog();

    bool userGroupsChanged() { return userGroupDataChanged; }

public slots:
    int exec(QString username);
    
private:
    Ui::AccountTypeDialog *ui;
    QString username;
    bool userGroupDataChanged;

    void checkSudoersFile();

private slots:
    void buttonApply_clicked();
    void checkBoxShowGroups_toggled(bool toggled);
    void treeWidget_itemChanged(QTreeWidgetItem * item, int column);
    void comboBoxAccountType_currentIndexChanged(int index);

};

#endif // ACCOUNTTYPEDIALOG_H
