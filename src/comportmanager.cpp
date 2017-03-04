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

#include <QFile>
#include "src/comportmanager.h"

ComPortManager::ComPortManager(ComPortSettings *port_settings,
                               QObject *parent)
  : QObject(parent),
    com_port_settings_{port_settings} {
}

ComPortManager::~ComPortManager() {
}

ComPortSettings* ComPortManager::GetPortSettings(void) const {
  return com_port_settings_;
}

void ComPortManager::OpenPort(void) {
  com_port_ = new LocalComPort(this);
  com_port_->SetPortSettings(com_port_settings_);

  connect(com_port_, SIGNAL(Receive(const DataPacket&)),
          this, SIGNAL(Receive(const DataPacket&)));

  com_port_->OpenPort();
}

void ComPortManager::ClosePort(void) {
  // Stop current sequence
  if(sequence_in_progress_) {
    this->OnStopSequence();
  }

  // Close port
  com_port_->ClosePort();
  delete com_port_;
  com_port_ = NULL;
}

void ComPortManager::OnStartManualSequence(QString data, int repeat,
                                           int delay) {
  // Save data
  sequence_data_ = data;
  sequence_repeat_ = repeat;
  pending_repeat_ = repeat;

  // Send first frame
  DataPacket packet(data.toUtf8());
  com_port_->Send(packet);
  pending_repeat_--;

  double progress = (double)(sequence_repeat_ - pending_repeat_)/
                    (double)(sequence_repeat_);
  emit SequenceProgress(static_cast<int>(progress*100.0));

  // Check if a sequence has been requested
  if((repeat > 0) && (delay > 0)) {
    sequence_in_progress_ = true;
    sequence_timer_ = new QTimer(this);
    sequence_timer_->setSingleShot(false);
    sequence_timer_->setInterval(delay);
    connect(sequence_timer_, &QTimer::timeout, [=](void) {
      DataPacket packet(data.toUtf8());
      com_port_->Send(packet);
      pending_repeat_--;

      double progress = (double)(sequence_repeat_ - pending_repeat_)/
                        (double)(sequence_repeat_);
      emit SequenceProgress(static_cast<int>(progress*100.0));

      if(pending_repeat_ == 0) {
        sequence_in_progress_ = false;
        sequence_timer_->stop();
        delete sequence_timer_;
        sequence_timer_ = nullptr;
        emit SequenceOver();
      }
    });
    sequence_timer_->start();
  }
}

void ComPortManager::OnStartDumpSequence(QString path, int repeat,
                                         int delay) {
  // Load file
  frame_list_.clear();
  sequence_file_ = path;
  QFile file(sequence_file_);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    emit SequenceOver();
    return;
  }

  QTextStream in(&file);
  while (!in.atEnd()) {
    frame_list_.append(in.readLine());
  }

  // Init frame number
  global_frame_nbr_ = frame_list_.size() * repeat;
  pending_frame_nbr_ = global_frame_nbr_;

  sequence_in_progress_ = true;

  // Send first frame
  DataPacket packet(frame_list_.at(list_idx_).toUtf8());
  com_port_->Send(packet);
  pending_frame_nbr_--;
  list_idx_++;

  double progress = (double)(global_frame_nbr_ - pending_frame_nbr_)/
                    (double)(global_frame_nbr_);
  emit SequenceProgress(static_cast<int>(progress*100.0));

  if(pending_frame_nbr_ > 0) {
    sequence_in_progress_ = true;
    sequence_timer_ = new QTimer(this);
    sequence_timer_->setSingleShot(false);
    sequence_timer_->setInterval(delay);
    connect(sequence_timer_, &QTimer::timeout, [=](void) {
      DataPacket packet(frame_list_.at(list_idx_).toUtf8());
      com_port_->Send(packet);
      pending_frame_nbr_--;
      list_idx_++;

      if(list_idx_ == frame_list_.size()) {
        list_idx_ = 0;
      }

      double progress = (double)(global_frame_nbr_ - pending_frame_nbr_)/
                        (double)(global_frame_nbr_);
      emit SequenceProgress(static_cast<int>(progress*100.0));

      if(pending_frame_nbr_ == 0) {
        sequence_in_progress_ = false;
        sequence_timer_->stop();
        delete sequence_timer_;
        sequence_timer_ = nullptr;
        emit SequenceOver();
      }
    });
    sequence_timer_->start();
  }
}

void ComPortManager::OnStartAutoSequence(QString path) {

}

void ComPortManager::OnStopSequence(void) {
  frame_list_.clear();
  sequence_in_progress_ = false;
  sequence_timer_->stop();
  delete sequence_timer_;
  sequence_timer_ = nullptr;
}
