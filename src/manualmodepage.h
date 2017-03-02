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

#ifndef SRC_MANUALMODEPAGE_H_
#define SRC_MANUALMODEPAGE_H_

#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include "modepage.h"

class ManualModePage : public ModePage
{
 public:
  //! Constructor
  ManualModePage(ComPortManager* port_mgr, QWidget *parent = 0);

 private:
  //! Manual mode data line
  QLineEdit* manual_data_line_ {nullptr};

  //! Manual mode loop group box
  QGroupBox* manual_loop_groupbox_ {nullptr};

  //! Parser choice group box
  QGroupBox* manual_parser_groupbox_ {nullptr};

  //! Radio button "ASCII"
  QRadioButton* ascii_radio_ {nullptr};

  //! Radio button "HEX"
  QRadioButton* hex_radio_ {nullptr};

  //! Radio button "DEC"
  QRadioButton* dec_radio_ {nullptr};

  //! Parser vertical layout
  QVBoxLayout* parser_layout_ {nullptr};

  //! Grid layout of the loop groupbox
  QGridLayout* loop_layout_ {nullptr};

  //! Label "Delay"
  QLabel* delay_label_ {nullptr};

  //! Label "ms"
  QLabel* ms_label_ {nullptr};

  //! Label "Repeat"
  QLabel* repeat_label_ {nullptr};

  //! Label "frames"
  QLabel* frames_label_ {nullptr};

  //! Delay spinbox
  QSpinBox* delay_spinbox_ {nullptr};

  //! Frame number splinbox
  QSpinBox* repeat_spinbox_ {nullptr};

  //! Vertical line
  QWidget* vertical_line_ {nullptr};
};

#endif // SRC_MANUALMODEPAGE_H_