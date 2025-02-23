/*
 *  Manjaro Installation Framework
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


#ifndef PAGE_GPUDRIVER_H
#define PAGE_GPUDRIVER_H

#include "widgets/pagewidget.h"
#include <QString>
#include <QStringList>
#include <QList>
#include <QListWidgetItem>
#include <QIcon>
#include <string>
#include <vector>
#include <mhwd.h>
#include "global.h"


namespace Ui {
class Page_GPUDriver;
}

class Page_GPUDriver : public PageWidget
{
    Q_OBJECT
    
public:
    explicit Page_GPUDriver(QWidget *parent = 0);
    ~Page_GPUDriver();

    void activated();
    
private:
    Ui::Page_GPUDriver *ui;
};

#endif // PAGE_GPUDRIVER_H
