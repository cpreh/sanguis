/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
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
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
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

#include <sanguis/tools/animations/qtutil/flow_layout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QtWidgets>
#include <fcppt/config/external_end.hpp>

sanguis::tools::animations::qtutil::FlowLayout::FlowLayout(
    QWidget *_parent, int _margin, int hSpacing, int vSpacing)
    : QLayout(_parent), itemList(), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
  setContentsMargins(_margin, _margin, _margin, _margin);
}

sanguis::tools::animations::qtutil::FlowLayout::FlowLayout(int _margin, int hSpacing, int vSpacing)
    : QLayout(), itemList(), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
  setContentsMargins(_margin, _margin, _margin, _margin);
}

sanguis::tools::animations::qtutil::FlowLayout::~FlowLayout()
{
  QLayoutItem *item = nullptr;
  while ((item = takeAt(0)) != nullptr)
  {
    delete item;
  }
}

void sanguis::tools::animations::qtutil::FlowLayout::addItem(QLayoutItem *item)
{
  itemList.append(item);
}

int sanguis::tools::animations::qtutil::FlowLayout::horizontalSpacing() const
{
  if (m_hSpace >= 0)
  {
    return m_hSpace;
  }
  return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
}

int sanguis::tools::animations::qtutil::FlowLayout::verticalSpacing() const
{
  if (m_vSpace >= 0)
  {
    return m_vSpace;
  }
  return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
}

int sanguis::tools::animations::qtutil::FlowLayout::count() const { return itemList.size(); }

QLayoutItem *sanguis::tools::animations::qtutil::FlowLayout::itemAt(int index) const
{
  return itemList.value(index);
}

QLayoutItem *sanguis::tools::animations::qtutil::FlowLayout::takeAt(int index)
{
  if (index >= 0 && index < itemList.size())
  {
    return itemList.takeAt(index);
  }
  return nullptr;
}

Qt::Orientations sanguis::tools::animations::qtutil::FlowLayout::expandingDirections() const
{
  return Qt::Orientations{};
}

bool sanguis::tools::animations::qtutil::FlowLayout::hasHeightForWidth() const { return true; }

int sanguis::tools::animations::qtutil::FlowLayout::heightForWidth(int width) const
{
  int height = doLayout(QRect(0, 0, width, 0), true);
  return height;
}

void sanguis::tools::animations::qtutil::FlowLayout::setGeometry(const QRect &rect)
{
  QLayout::setGeometry(rect);
  doLayout(rect, false);
}

QSize sanguis::tools::animations::qtutil::FlowLayout::sizeHint() const { return minimumSize(); }

QSize sanguis::tools::animations::qtutil::FlowLayout::minimumSize() const
{
  QSize size;
  QLayoutItem *item = nullptr;
  foreach (item, itemList)
    size = size.expandedTo(item->minimumSize());

  size += QSize(2 * margin(), 2 * margin());
  return size;
}

int sanguis::tools::animations::qtutil::FlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
  int left;
  int top;
  int right;
  int bottom;
  getContentsMargins(&left, &top, &right, &bottom);
  QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
  int x = effectiveRect.x();
  int y = effectiveRect.y();
  int lineHeight = 0;

  QLayoutItem *item = nullptr;
  foreach (item, itemList)
  {
    QWidget *wid = item->widget();
    int spaceX = horizontalSpacing();
    if (spaceX == -1)
    {
      spaceX = wid->style()->layoutSpacing(
          QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
    }
    int spaceY = verticalSpacing();
    if (spaceY == -1)
    {
      spaceY = wid->style()->layoutSpacing(
          QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
    }
    int nextX = x + item->sizeHint().width() + spaceX;
    if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
    {
      x = effectiveRect.x();
      y = y + lineHeight + spaceY;
      nextX = x + item->sizeHint().width() + spaceX;
      lineHeight = 0;
    }

    if (!testOnly)
    {
      item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
    }

    x = nextX;
    lineHeight = qMax(lineHeight, item->sizeHint().height());
  }
  return y + lineHeight - rect.y() + bottom;
}
int sanguis::tools::animations::qtutil::FlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
  QObject *cur_parent = this->parent();
  if (cur_parent == nullptr)
  {
    return -1;
  }
  if (cur_parent->isWidgetType())
  {
    QWidget *pw = static_cast<QWidget *>(cur_parent);
    return pw->style()->pixelMetric(pm, nullptr, pw);
  }
  else
  {
    return static_cast<QLayout *>(cur_parent)->spacing();
  }
}
