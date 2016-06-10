// GDB RSP tid class.

// Copyright (C) 2016, Pedro Alves

// Contributor: Pedro Alves <pedro@palves.net>

// This file is part of the Adapteva RSP server.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 3 of the License, or (at your option)
// any later version.

// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.

// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef GDB_TID_H
#define GDB_TID_H

#include <sstream>

class ProcessInfo;
class Thread;

class GdbTid
{
public:
  GdbTid()
    : m_pid(-1), m_tid(0)
  {}

  GdbTid (int pid, int tid)
    : m_pid (pid), m_tid (tid)
  {}

  GdbTid (ProcessInfo *process, Thread *thread);

  int pid () const { return m_pid; }
  int tid () const { return m_tid; }

  static GdbTid from_string (const char *str);

  friend std::ostream& operator<< (std::ostream &out, const GdbTid &gtid);

  static const GdbTid ALL_THREADS;

private:
  int m_pid;
  int m_tid;
};

#endif

// Local Variables:
// mode: C++
// c-file-style: "gnu"
// show-trailing-whitespace: t
// End:
