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

#include "src/portpage.h"
#include "src/session.h"
#include "src/addormodifyportdialog.h"
#include "src/terminalportview.h"
#include "src/dumpportview.h"
#include "src/tableportview.h"

PortPage::PortPage(Session* session,
                   int page_index,
                   QWidget* parent)
  : QWidget(parent),
    session_(session),
    page_index_{page_index} {
  port_info_area_widget_ = new PortInfoAreaWidget(session, page_index, this);
  send_widget_ = new SendWidget(&port_mgr_list_, this);
  view_widget_ = new QWidget(this);
  view_layout_ = new QHBoxLayout(view_widget_);

  add_view_button_ = new QPushButton(this);
  add_view_button_->setIcon(QIcon(":/icons/icons/plus-8x.png"));
  add_view_button_->setToolTip(tr("Add a view to this port."));
  connect(add_view_button_, SIGNAL(clicked()),
          this, SLOT(OnNewViewClicked()));

  add_port_button_ = new QPushButton(this);
  add_port_button_->setIcon(QIcon(":/icons/icons/plus-8x.png"));
  add_port_button_->setToolTip(tr("Add a port to this page."));
  connect(add_port_button_, SIGNAL(clicked()),
          this, SLOT(OnNewPortClicked()));

  left_glayout_ = new QGridLayout();
  left_glayout_->addWidget(add_port_button_, 0, 0);
  left_glayout_->addWidget(add_view_button_, 0, 1);
  left_vlayout_ = new QVBoxLayout();

  left_vlayout_->addWidget(port_info_area_widget_);
  left_vlayout_->addLayout(left_glayout_);

  main_layout_ = new QGridLayout(this);
  main_layout_->addLayout(left_vlayout_, 0, 0);
  main_layout_->addWidget(view_widget_, 0, 1);
  main_layout_->addWidget(send_widget_, 1, 0, 1, 2);

  main_layout_->setColumnStretch(0, 20);
  main_layout_->setColumnStretch(1, 80);
  main_layout_->setRowStretch(0, 80);
}

PortPage::~PortPage() {
  //  // Delete COM ports for this session
  //  QList<ComPortManager*>::iterator itBeginPort = com_port_mgr_list_.begin();
  //  QList<ComPortManager*>::iterator itEndPort = com_port_mgr_list_.end();
  //  QList<ComPortManager*>::iterator it = itBeginPort;
  //  for (; it != itEndPort ; it++) {
  //    QTimer::singleShot(0, *it, &ComPortManager::ClosePort);
  //  }

  // Delete threads
  foreach (QThread* thread, thread_list_) { // NOLINT
    thread->quit();
    if (!thread->wait(1000)) {
      qDebug() << "Timeout arret du thread.";
    }
    delete thread;
  }

  // Delete port managers
  foreach (ComPortManager* port_mgr, port_mgr_list_) { // NOLINT
    delete port_mgr;
  }

  // Delete views
  foreach (PortView* port_view, view_list_) { // NOLINT
    delete port_view;
  }
}

void PortPage::OnNewViewClicked(void) {
  ViewSettings* view_settings = new ViewSettings();
  ViewSettingDialog view_setting_dialog(view_settings,
                                        ViewSettingDialog::ActionType::kAdd,
                                        this);
  qint32 result = view_setting_dialog.exec();

  switch (result) {
  case QDialog::Accepted:
  {
    session_->AddView(page_index_, view_settings);
    break;
  }
  case QDialog::Rejected:
  default:
    break;
  }
}

void PortPage::OnNewPortClicked(void) {
  ComPortSettings* port_settings = new ComPortSettings();
  AddOrModifyPortDialog addDialog(port_settings,
                                  AddOrModifyPortDialog::ActionType::kAdd,
                                  this);
  qint32 result = addDialog.exec();

  switch (result) {
  case QDialog::Accepted:
  {
    session_->AddPort(page_index_, port_settings);
    break;
  }
  case QDialog::Rejected:
  default:
    break;
  }
}

void PortPage::AddView(ViewSettings* settings) {
  PortView* view;
  switch (settings->GetViewType()) {
  case ViewSettings::ViewType::kDump:
    view = new DumpPortView(settings, this);
    break;
  case ViewSettings::ViewType::kTerminal:
    view = new TerminalPortView(settings, this);
    break;
  case ViewSettings::ViewType::kTable:
    view = new TablePortView(settings, this);
    break;
  default:
    break;
  }
  view_layout_->addWidget(view);
  view_list_.append(view);

  // Connect port managers to this new view
  foreach (ComPortManager* port_mgr, port_mgr_list_) { // NOLINT
    connect(port_mgr, SIGNAL(DataReceived(QByteArray)),
            view, SLOT(OnReceivedData(QByteArray)));
    connect(port_mgr, SIGNAL(DataSent(DataPacket)),
            view, SLOT(OnDataSent(DataPacket)));
  }

  // Process DeleteView signal
  connect(view, &PortView::DeleteView, [=](PortView* view) {
    int view_idx = view_list_.indexOf(view);
    view_list_.removeAt(view_idx);
    delete view;
  });
}

void PortPage::AddPort(ComPortSettings* settings) {
  // Create new port manager
  ComPortManager* port_mgr = new ComPortManager(settings);
  port_mgr_list_.append(port_mgr);

  // Connect views to this port manager
  foreach (PortView* view, view_list_) { // NOLINT
    connect(port_mgr, SIGNAL(Receive(DataPacket const&)),
            view, SLOT(OnReceivedData(DataPacket const&)));
  }

  // Create thread for this port manager
  QThread* thread = new QThread(this);
  thread_list_.append(thread);
  port_mgr->moveToThread(thread);
  thread->start(QThread::TimeCriticalPriority);

  port_info_area_widget_->AddPort(port_mgr_list_.size()-1);
  send_widget_->PortListUpdated();
}

void PortPage::DeletePort(int port_idx) {
  // Delete threads
  QThread* thread = thread_list_.at(port_idx);
  thread->quit();
  if (!thread->wait(1000)) {
    qDebug() << "Timeout arret du thread.";
  }
  delete thread;
  thread_list_.removeAt(port_idx);

  // Delete port managers
  ComPortManager* port_mgr = port_mgr_list_.at(port_idx);
  delete port_mgr;
  port_mgr_list_.removeAt(port_idx);

  port_info_area_widget_->DeletePort(port_idx);
  send_widget_->PortListUpdated();
}

QList<PortView*>* PortPage::GetViewList(void) {
  return &view_list_;
}

QList<ComPortManager*>* PortPage::GetPortMgrList(void) {
  return &port_mgr_list_;
}

void PortPage::SetPageIndex(int page_idx) {
  page_index_ = page_idx;
}

void PortPage::OnOpenPortClicked(void) {
  //  ComPortManager* port_mgr = session_->GetPortManager(port_index_);
  //  port_mgr->OpenPort();
}

void PortPage::OnClosePortClicked(void) {
  //  ComPortManager* port_mgr = session_->GetPortManager(port_index_);
  //  port_mgr->ClosePort();
}
