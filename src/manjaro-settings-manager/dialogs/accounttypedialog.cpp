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

#include "accounttypedialog.h"
#include "ui_accounttypedialog.h"

AccountTypeDialog::AccountTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountTypeDialog)
{
    ui->setupUi(this);
    userGroupDataChanged = false;

    // Hide treeWidget
    checkBoxShowGroups_toggled(false);

    ui->treeWidget->setColumnWidth(0, 150);
    ui->treeWidget->setColumnWidth(1, 100);

    // Connect signals and slots
    connect(ui->buttonCancel, SIGNAL(clicked()) ,   this, SLOT(close()));
    connect(ui->buttonApply, SIGNAL(clicked()) ,   this, SLOT(buttonApply_clicked()));
    connect(ui->checkBoxShowGroups, SIGNAL(toggled(bool)) ,   this, SLOT(checkBoxShowGroups_toggled(bool)));
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int))   ,   this, SLOT(treeWidget_itemChanged(QTreeWidgetItem*,int)));
    connect(ui->comboBoxAccountType, SIGNAL(currentIndexChanged(int))   ,   this, SLOT(comboBoxAccountType_currentIndexChanged(int)));
}



AccountTypeDialog::~AccountTypeDialog()
{
    delete ui;
}



int AccountTypeDialog::exec(QString username) {
    // Block signals
    ui->treeWidget->blockSignals(true);

    userGroupDataChanged = false;
    this->username = username;
    ui->treeWidget->clear();

    QList<Global::Group> groups = Global::getAllGroups();

    for (int i = 0; i < groups.size(); i++) {
        const Global::Group *group = &groups.at(i);

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, group->name);

        if (group->members.contains(username))
            item->setCheckState(1, Qt::Checked);
        else
            item->setCheckState(1, Qt::Unchecked);

        // Check the account type
        if (group->name == ADMIN_GROUP) {
            if (group->members.contains(username))
                ui->comboBoxAccountType->setCurrentIndex(1);
            else
                ui->comboBoxAccountType->setCurrentIndex(0);
        }
    }

    // Sort tree widget
    ui->treeWidget->sortItems(0, Qt::AscendingOrder);

    // Unblock signals
    ui->treeWidget->blockSignals(false);

    show();
    checkSudoersFile();
    return QDialog::exec();
}



//###
//### Private
//###


void AccountTypeDialog::checkSudoersFile() {
    QFile file(SUDOERSFILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    bool found = false;

    while (!in.atEnd()) {
        QString line = in.readLine().split("#", QString::KeepEmptyParts).first().remove(" ");

        if (line == "%" + QString(ADMIN_GROUP) + "ALL=(ALL)ALL") {
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        QMessageBox::warning(this,
                             tr("Warning!"),
                             tr("Admin group %1 isn't enabled in '%2'! You have to enable it to be able to set admin rights...").arg(ADMIN_GROUP, SUDOERSFILE),
                             QMessageBox::Ok, QMessageBox::Ok);
}




void AccountTypeDialog::buttonApply_clicked() {
    QStringList groups;

    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
       QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);

       if (item->checkState(1) == Qt::Checked)
           groups.append(item->text(0));
    }

    // Check if default groups have been disabled
    QStringList missingDefaultGroups, defaultGroups = QString(DEFAULT_USER_GROUPS).split(",", QString::SkipEmptyParts);
    foreach (QString defaultGroup, defaultGroups) {
        if (!groups.contains(defaultGroup))
            missingDefaultGroups.append(defaultGroup);
    }

    if (!missingDefaultGroups.isEmpty()
            && QMessageBox::No == QMessageBox::question(this,
                                                        tr("Warning!"),
                                                        tr("Following default user groups have been disabled:\n%1\nIt is recommended to enable those groups. Do you really want to continue?").arg(missingDefaultGroups.join(", ")),
                                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
        return;

    userGroupDataChanged = true;

    // Set groups
    QString errorMessage;
    if (Global::runProcess("usermod",
                           QStringList() << "-G" << groups.join(",") << username,
                           QStringList(),
                           errorMessage) != 0)
        QMessageBox::warning(this, tr("Error!"), QString(tr("Failed to set groups!") + "\n" + errorMessage), QMessageBox::Ok, QMessageBox::Ok);

    close();
}




void AccountTypeDialog::checkBoxShowGroups_toggled(bool toggled) {
    if (toggled)
        ui->treeWidget->setVisible(true);
    else
        ui->treeWidget->setVisible(false);

    adjustSize();
}



void AccountTypeDialog::treeWidget_itemChanged(QTreeWidgetItem *item, int column) {
    if (item->text(0) != ADMIN_GROUP || column != 1)
        return;

    if (item->checkState(1) == Qt::Checked)
        ui->comboBoxAccountType->setCurrentIndex(1);
    else
        ui->comboBoxAccountType->setCurrentIndex(0);
}



void AccountTypeDialog::comboBoxAccountType_currentIndexChanged(int index) {
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
       QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
       if (item->text(0) != ADMIN_GROUP)
           continue;

       if (index == 0)
           item->setCheckState(1, Qt::Unchecked);
       else
           item->setCheckState(1, Qt::Checked);

       break;
    }
}
