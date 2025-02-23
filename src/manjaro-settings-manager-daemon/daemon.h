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

#ifndef DAEMON_H
#define DAEMON_H

#include <QTimer>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QProcess>
#include <QStringList>
#include <QDir>
#include <global.h>


class Daemon : public QTimer
{
    Q_OBJECT
public:
    explicit Daemon(QObject *parent = 0);
    void start();

private:
    QSystemTrayIcon trayIcon;
    QString messageTitel, messageText;

    void showMessage(QString messageTitel, QString messageText);
    
protected slots:
    void run();
    void trayIcon_clicked();
    void trayIcon_showMessage();

};

#endif // DAEMON_H
