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

#ifndef SRC_SESSIONMANAGER_H_
#define SRC_SESSIONMANAGER_H_

#include <QObject>
#include <QList>
#include "src/session.h"
#include "src/viewsettings.h"

class SessionManager : public QObject {
  Q_OBJECT

 public:
  //! Default constructor
  explicit SessionManager(QObject *parent = 0);

  //! Destructor
  ~SessionManager();

  //! Current session pointer getter
  Session* GetCurrentSession(void) const;

  //! Load session file
  void LoadSessionFile(QString filepath);

 signals:
  //! Emitted for adding view for a port
  void AddView(qint8, QJsonObject);

 private:
  //! Session list
  QList<Session*> session_list_;

  //! Index of the current session;
  qint8 current_session_index_ {-1};

  //! Default session
  Session* default_session_ {nullptr};
};

#endif  // SRC_SESSIONMANAGER_H_
