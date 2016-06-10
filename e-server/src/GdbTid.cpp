// GDB thread IDs.

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

#include "GdbServer.h"
#include "GdbTid.h"
#include "Thread.h"
#include "IosUtils.h"

const GdbTid GdbTid::ALL_THREADS(-1, 0);

std::ostream &
operator<< (std::ostream &out, const GdbTid &rtid)
{
  IosFlagsSaver iosfs (out);

  out << "p" << std::hex << rtid.pid () << "." << rtid.tid ();
  return out;
}

GdbTid::GdbTid(ProcessInfo *process, Thread *thread)
  : m_pid(process->pid ()), m_tid(thread->tid ())
{}

static long
rspParseHexNumber (const char **str_p)
{
  const char *str = *str_p;
  char *end;
  long num;
  bool neg = false;

  if (*str == '-')
    {
      str++;
      neg = true;
    }

  num = strtoul (str, &end, 16);
  *str_p = end;
  return neg ? -num : num;
}

//-----------------------------------------------------------------------------
//! Get a thread ID from a packet.

//! Valid values are "p-1", "0" or a big-endian hex string.

//! @param[in] str   The string to recognize
//! @return  The thread ID,  or -2 if we don't recognize the thread ID.
//-----------------------------------------------------------------------------
GdbTid
GdbTid::from_string (const char *str)
{
  if (strncmp ("-1", str, strlen ("-1")) == 0)
    {
      return GdbTid (0, -1);
    }
  else if (strncmp ("0", str, strlen ("0")) == 0)
    {
      return GdbTid ();
    }
  else
    {
      GdbTid rtid;

      /* Skip 'p'.  */
      ++str;
      rtid.m_pid = rspParseHexNumber (&str);
      /* Skip '.'.  */
      ++str;
      rtid.m_tid = rspParseHexNumber (&str);
      return rtid;
    }
}

// Local Variables:
// mode: C++
// c-file-style: "gnu"
// show-trailing-whitespace: t
// End:
