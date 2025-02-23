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

#include "listwidget.h"



ListWidgetItemSeperatorDelegate::ListWidgetItemSeperatorDelegate(QListWidget *parent, QListWidgetItem *item) :
    QStyledItemDelegate(parent)
{
    this->parent = parent;
    this->item = item;
}



void ListWidgetItemSeperatorDelegate::parentResized() {
    item->setSizeHint(QSize(parent->width() - 2*parent->spacing(), 30));
}



void ListWidgetItemSeperatorDelegate::paint ( QPainter * painter,
                                           const QStyleOptionViewItem & option,
                                           const QModelIndex & index ) const
{
    QPen origPen, pen = painter->pen();
    origPen = pen;
    pen.setBrush(parent->palette().midlight());
    painter->setPen(pen);
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->setPen(origPen);

    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);

    QFontMetrics fm(font);
    QString text = index.data(Qt::DisplayRole).toString();

    QRect fnBound = fm.boundingRect(text);
    fnBound.moveLeft(option.rect.left());
    fnBound.translate(0, option.rect.bottom() - 8);

    painter->drawText(fnBound, Qt::AlignBottom | Qt::AlignLeft, text);
}


QSize ListWidgetItemSeperatorDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const {
    return QSize(parent->width() - 2*parent->spacing(), 30);
}



ListWidget::ListWidget(QWidget *parent) :
    QListWidget(parent)
{
}



void ListWidget::addSeparator(QString text) {
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setText(text);

    ListWidgetItemSeperatorDelegate *delegate = new ListWidgetItemSeperatorDelegate(this, item);
    setItemDelegateForRow(count()-1, delegate);
    connect(this, SIGNAL(resized()) ,   delegate, SLOT(parentResized()));
}



void ListWidget::resizeEvent(QResizeEvent *e) {
    emit resized();
    QListWidget::resizeEvent(e);
}
