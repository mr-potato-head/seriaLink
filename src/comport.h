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

#ifndef SRC_COMPORT_H_
#define SRC_COMPORT_H_

#include <QObject>
#include "src/comportsettings.h"

class ComPort : public QObject {
  Q_OBJECT

 public:
  //! Port types
  enum class PortType {
    kUnknownPort = 0,
    kLocalPort,
    kRemotePort
  };

  //! Default constructor
  explicit ComPort(QObject *parent = 0);

  //! Setter of port settings
  void SetPortSettings(ComPortSettings* port_settings);

  //! Getter of port settings
  ComPortSettings* GetPortSettings(void);

  //! Getter of port type
  PortType GetPortType(void) const;

 public slots: //NOLINT
  //! Executed to open port
  virtual void OpenPort(void) = 0;

  //! Executed to close port
  virtual void ClosePort(void) = 0;

 signals:
  //! Emitted when new data are received
  void receivedData(QByteArray);

 protected:
  //! COM port settings
  ComPortSettings* com_port_settings_ {NULL};

  //! Port type
  PortType port_type_ {PortType::kUnknownPort};
};

#endif  // SRC_COMPORT_H_