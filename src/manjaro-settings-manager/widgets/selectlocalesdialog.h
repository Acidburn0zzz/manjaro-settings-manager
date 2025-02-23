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

#ifndef SELECTLOCALESDIALOG_H
#define SELECTLOCALESDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <global.h>


namespace Ui {
class SelectLocalesDialog;
}



class SelectLocalesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectLocalesDialog(QWidget *parent = 0);
    ~SelectLocalesDialog();

    int exec();
    bool localeAdded();
    Global::LocaleInfo getLocale();
    
private:
    Ui::SelectLocalesDialog *ui;
    QHash<QString, QHash<QString, QList<Global::Locale> > > locales;
    QHash<QString, QList<Global::Locale> > currentTerritories;
    QList<Global::Locale> currentLocales;
    bool accepted;

    void updateApplyEnabledState();

private slots:
    void listWidgetLanguageItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void listWidgetTerritoryItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void comboBoxLocaleIndexChanged(const QString &text);
    void buttonAdd_clicked();

};

#endif // SELECTLOCALESDIALOG_H
