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

#include "src/comportsettings.h"

ComPortSettings::ComPortSettings() {
}

QSerialPortInfo ComPortSettings::GetPortInfo(void) {
  return port_info_;
}

QSerialPort::BaudRate ComPortSettings::GetBaudRate(void) const {
  return port_baud_rate_;
}

QSerialPort::Parity ComPortSettings::GetParity(void) const {
  return port_parity_;
}

QSerialPort::DataBits ComPortSettings::GetDataBits(void) const {
  return port_data_bits_;
}

QSerialPort::StopBits ComPortSettings::GetStopBits(void) const {
  return port_stop_bits_;
}

QSerialPort::FlowControl ComPortSettings::GetFlowControl(void) const {
  return port_flow_control_;
}

void ComPortSettings::SetPortInfo(QSerialPortInfo port_info) {
  port_info_ = port_info;
}

void ComPortSettings::SetBaudRate(QSerialPort::BaudRate baud_rate) {
  port_baud_rate_ = baud_rate;
}

void ComPortSettings::SetParity(QSerialPort::Parity parity) {
  port_parity_ = parity;
}

void ComPortSettings::SetDataBits(QSerialPort::DataBits data_bits) {
  port_data_bits_ = data_bits;
}

void ComPortSettings::SetStopBits(QSerialPort::StopBits stop_bits) {
  port_stop_bits_ = stop_bits;
}

void ComPortSettings::SetFlowControl(QSerialPort::FlowControl flow_control) {
  port_flow_control_ = flow_control;
}