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

#ifndef SRC_PORTINFOWIDGET_H_
#define SRC_PORTINFOWIDGET_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QList>
#include "src/comportmanager.h"
#include "src/comportsettings.h"

class PortInfoWidget : public QWidget {
  Q_OBJECT

 public:
  //! Default constructor
  explicit PortInfoWidget(QList<ComPortManager*>* port_mgr_list,
                          QWidget *parent = 0);

  //! Set port settings
  void SetPortSettings(ComPortSettings* port_settings);

 signals:
  //! Emitted when the new port button is clicked
  void NewPortClicked(void);

  //! Emitted when the new view button is clicked
  void NewViewClicked(void);

  //! Emitted on click on open button
  void OpenPortClicked(void);

  //! Emitted on click on close button
  void ClosePortClicked(void);

 private:
  //! Group box of settings
  QGroupBox* settings_group_box_ {NULL};

  //! Group box vertical layout
  QVBoxLayout* group_box_layout_ {NULL};

  //! Port index
  qint32 port_index_ {-1};

  //! Main vertical layout
  QVBoxLayout* main_layout_ {NULL};

  //! Port name label
  QLabel* port_name_label_ {NULL};

  //! Port name value
  QLabel* port_name_value_ {NULL};

  //! Port baud rate label
  QLabel* port_baud_rate_label_ {NULL};

  //! Port baud rate value
  QLabel* port_baud_rate_value_ {NULL};

  //! Port parity label
  QLabel* port_parity_label_ {NULL};

  //! Port parity value
  QLabel* port_parity_value_ {NULL};

  //! Port data bits label
  QLabel* port_data_bits_label_ {NULL};

  //! Port data bits value
  QLabel* port_data_bits_value_ {NULL};

  //! Port stop bits label
  QLabel* port_stop_bits_label_ {NULL};

  //! Port stop bits value
  QLabel* port_stop_bits_value_ {NULL};

  //! Port flow control label
  QLabel* port_flow_control_label_ {NULL};

  //! Port flow control value
  QLabel* port_flow_control_value_ {NULL};

  //! Open COM port button
  QPushButton* open_button_ {NULL};

  //! Close COM port button
  QPushButton* close_button_ {NULL};

  //! Create new view
  QPushButton* new_view_button_ {NULL};

  //! Add new port
  QPushButton* new_port_button_ {NULL};

  //! COM Port manager list
  QList<ComPortManager*>* port_mgr_list_;
};

#endif  // SRC_PORTINFOWIDGET_H_
