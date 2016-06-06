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

#ifndef SRC_PAGESELECTOR_H_
#define SRC_PAGESELECTOR_H_

#include <QWidget>
#include <QHBoxLayout>
#include "src/sessionmanager.h"

class PageSelector : public QWidget {
  Q_OBJECT

 public:
  //! Default constructor
  explicit PageSelector(SessionManager* session_manager,
                        QWidget *parent = 0);

 public slots: // NOLINT
  //! Add button
  void AddButton(qint32 portIndex);

 private:
  //! Button layout
  QHBoxLayout* button_layout_ {NULL};

  //! Pointer on session manager
  SessionManager* session_manager_ {NULL};
};

#endif  // SRC_PAGESELECTOR_H_
