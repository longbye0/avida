/*
 *  cHardwareStatusPrinter.cc
 *  Avida
 *
 *  Created by David on 11/30/05.
 *  Copyright 2005-2006 Michigan State University. All rights reserved.
 *  Copyright 1999-2004 California Institute of Technology.
 *
 */

#include "cHardwareStatusPrinter.h"

#include "cHeadCPU.h"
#include "cHardware4Stack.h"
#include "cHardwareBase.h"
#include "cHardwareCPU.h"
#include "cHardwareSMT.h"
#include "cInstSet.h"
#include "cOrganism.h"
#include "cString.h"
#include "cStringUtil.h"

cString cHardwareStatusPrinter::Bonus(const cString &next_name)
{
  return cStringUtil::Stringf("%s (bonus instruction)", static_cast<const char*>(next_name));
}

void cHardwareStatusPrinter::PrintStatus(cHardwareBase& hardware, const cString& next_name)
{
  cOrganism *organism = hardware.GetOrganism();
  if(organism) organism->PrintStatus(m_trace_fp, next_name);
}

// CPU
const cString& cHardwareStatusPrinter::GetNextInstName(cHardwareCPU& hardware)
{
  return hardware.GetInstSet().GetName(hardware.IP().GetInst());
}
void cHardwareStatusPrinter::TraceHardware_CPU(cHardwareCPU &hardware)
{
  PrintStatus(hardware, GetNextInstName(hardware));
}
void cHardwareStatusPrinter::TraceHardware_CPUBonus(cHardwareCPU &hardware)
{
  PrintStatus(hardware, Bonus(GetNextInstName(hardware)));
}

// 4Stack
const cString& cHardwareStatusPrinter::GetNextInstName(cHardware4Stack& hardware)
{
  return hardware.GetInstSet().GetName(hardware.IP().GetInst());
}
void cHardwareStatusPrinter::TraceHardware_4Stack(cHardware4Stack &hardware)
{
  PrintStatus(hardware, GetNextInstName(hardware));
}
void cHardwareStatusPrinter::TraceHardware_4StackBonus(cHardware4Stack &hardware)
{
  PrintStatus(hardware, Bonus(GetNextInstName(hardware)));
}

// SMT
const cString& cHardwareStatusPrinter::GetNextInstName(cHardwareSMT& hardware)
{
  return hardware.GetInstSet().GetName(hardware.IP().GetInst());
}
void cHardwareStatusPrinter::TraceHardware_SMT(cHardwareSMT &hardware)
{
  PrintStatus(hardware, GetNextInstName(hardware));
}
void cHardwareStatusPrinter::TraceHardware_SMTBonus(cHardwareSMT &hardware)
{
  PrintStatus(hardware, Bonus(GetNextInstName(hardware)));
}

void cHardwareStatusPrinter::TraceHardware_TestCPU(
  int time_used,
  int time_allocated,
  int size,
  const cString &final_memory,
  const cString &child_memory
)
{
  if (time_used == time_allocated) {
    m_trace_fp << endl << "# TIMEOUT: No offspring produced." << endl;
  } else if (size == 0) {
    m_trace_fp << endl << "# ORGANISM DEATH: No offspring produced." << endl;
  } else {
    m_trace_fp
    << endl << "# Final Memory: " << final_memory
    << endl << "# Child Memory: " << child_memory << endl;
  }
}
