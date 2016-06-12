/*
 * Copyright (C) 2016 Guilhem GUYONNET
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SENDWIDGET_H
#define SENDWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include "src/sessionmanager.h"

class SendWidget : public QWidget
{
  Q_OBJECT
 public:
  //! Default costructor
  explicit SendWidget(SessionManager* session_manager,
                      qint32 port_index, QWidget *parent = 0);

 signals:
  //! Emitted when data have to be sent
  void sendData(QByteArray);

 private slots:
  //! Executed on click on send button
  void OnSendButtonClicked(void);

 private:
  //! Main grid layout of the widget
  QGridLayout* main_layout_ {NULL};

  //! Line edit of to send text
  QLineEdit* send_line_edit_ {NULL};

  //! Send button
  QPushButton* send_button_ {NULL};

  //! Session manager
  SessionManager* session_manager_ {NULL};

  //! Port index
  qint32 port_index_ {-1};
};

#endif // SENDWIDGET_H
