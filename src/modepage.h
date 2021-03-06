/*
 * Copyright (C) 2020 Guilhem GUYONNET
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

#ifndef SRC_MODEPAGE_H_
#define SRC_MODEPAGE_H_

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QRegularExpression>
#include <QList>
#include "src/comportmanager.h"

class ModePage : public QWidget {
  Q_OBJECT

 public:
  //! Constructor
  explicit ModePage(QList<ComPortManager*>* port_mgr_list,
                    QWidget *parent = 0);

  //! Destructor
  ~ModePage();

 public slots: // NOLINT
  //! Change current port manager index
  void ChangePortManagerIndex(int index);

 signals:
  //! Emitted for starting manual sequence
  void StartManualSequence(DataParser::ParserType eParser, QString data,
                           int repeat, int delay);

  //! Emitted for starting manual sequence
  void StartDumpSequence(DataParser::ParserType eParser, QString path,
                         int repeat, int delay);

  //! Emitted for starting manual sequence
  void StartAutoSequence(QString path);

 protected:
  //! Port manager
  ComPortManager* port_manager_ {nullptr};

  //! Main grid layout of the widget
  QGridLayout* main_layout_ {nullptr};

  //! Send button
  QPushButton* start_button_ {nullptr};

  //! Stop button
  QPushButton* stop_button_ {nullptr};

  //! Progress bar layout
  QHBoxLayout* progress_bar_layout_ {nullptr};

  //! Progress bar
  QProgressBar* progress_bar_ {nullptr};

  //! Progression time label
  QLabel* progress_label_ {nullptr};

  //! Button layout
  QVBoxLayout* button_layout_ {nullptr};

  //! COM Port manager list
  QList<ComPortManager*>* port_mgr_list_;

 private slots: // NOLINT
  void OnStopButtonClicked(void);
};

#endif  // SRC_MODEPAGE_H_
