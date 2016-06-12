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

#ifndef SRC_PAGECONTAINER_H_
#define SRC_PAGECONTAINER_H_

#include <QStackedWidget>
#include "src/sessionmanager.h"
#include "src/portpage.h"

class PageContainer : public QStackedWidget {
  Q_OBJECT

 public:
  //! Default constructor
  explicit PageContainer(SessionManager* session_manager, QWidget *parent = 0);

 private slots: //NOLINT
  //! Add page in page container
  void AddPage(qint32 port_index);

 private:
  //! Session manager
  SessionManager* session_manager_ {NULL};
};

#endif  // SRC_PAGECONTAINER_H_