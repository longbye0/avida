/*
 *  cIntegratedSchedule.h
 *  Avida
 *
 *  Created by David on 12/7/05.
 *  Copyright 2005-2006 Michigan State University. All rights reserved.
 *  Copyright 1993-2003 California Institute of Technology
 *
 */

#ifndef cIntegratedSchedule_h
#define cIntegratedSchedule_h

#ifndef cSchedule_h
#include "cSchedule.h"
#endif
#ifndef tArray_h
#include "tArray.h"
#endif

/**
 * The cIntegratedSchedule method relies on breaking up all merits into
 * sums of powers of 2 (i.e. using the binary representation of the merit).
 * All items with merits in the highest power of two will get the most
 * time, and subsequent merit components will have time divided,
 * continuing recursively.  The simplest way of doing this while maximizing
 * evenness of distribution of time slices is to simply alternate executing
 * the best, and everything else (where in everything else we again alternate
 * with the best of this sub-list recursively).
 **/

class cIntegratedScheduleNode;
class cMerit;

class cIntegratedSchedule : public cSchedule
{
private:
  tArray<cIntegratedScheduleNode *> node_array;
  int num_active_nodes;
  cMerit * merit_chart;

  void InsertNode(int node_id);
  void RemoveNode(int node_id);
  void ResizeNodes(int new_size);

  cIntegratedSchedule(); // @not_implemented
  cIntegratedSchedule(const cIntegratedSchedule&); // @not_implemented
  cIntegratedSchedule& operator=(const cIntegratedSchedule&); // @not_implemented

public:
  cIntegratedSchedule(int _item_count);
  ~cIntegratedSchedule();

  void Adjust(int item_id, const cMerit & new_merit);
  int GetNextID();
  double GetStatus(int id);

  bool OK();
};

#endif
