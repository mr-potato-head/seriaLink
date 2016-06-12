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

#include "src/centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) :
  QWidget(parent) {
  // Instanciate session manager
  session_manager_ = new SessionManager(this);

  top_bar_ = new TopBar(session_manager_, this);
  page_container_ = new PageContainer(session_manager_, this);

  main_layout_ = new QVBoxLayout(this);
  main_layout_->addWidget(top_bar_);
  main_layout_->addWidget(page_container_);

  main_layout_->setStretchFactor(static_cast<QWidget*>(top_bar_), 10);
  main_layout_->setStretchFactor(static_cast<QWidget*>(page_container_), 90);

  main_layout_->setMargin(0);
  main_layout_->setSpacing(0);
}