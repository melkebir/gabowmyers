/*
 * gabowmyers.h
 *
 *  Created on: 25-jun-2015
 *      Author: M. El-Kebir
 */

#ifndef GABOWMYERS_H
#define GABOWMYERS_H

#include <list>
#include <vector>
#include <lemon/adaptors.h>
#include <lemon/bfs.h>

#include "utils.h"

namespace gm {
  
class GabowMyers
{
public:
  GabowMyers(const Digraph& g, const StringNodeMap& label);
  void run(Node root);
  
protected:
  typedef std::list<Arc> ArcList;
  typedef ArcList::const_iterator ArcListIt;
  typedef ArcList::iterator ArcListNonConstIt;
  typedef ArcList::const_reverse_iterator ArcListRevIt;
  
  typedef std::vector<ArcList> ArcListVector;
  
  typedef lemon::SubDigraph<const Digraph> SubDigraph;
  typedef SubDigraph::ArcIt SubArcIt;
  typedef SubDigraph::NodeIt SubNodeIt;
  typedef SubDigraph::OutArcIt SubOutArcIt;
  typedef SubDigraph::InArcIt SubInArcIt;
  
  typedef lemon::Bfs<SubDigraph> SubBfs;
  
  void grow(Node r,
            SubDigraph& G,
            SubDigraph& T,
            SubDigraph& L,
            SubBfs& bfsL,
            ArcList& F);
  
protected:
  const Digraph& _g;
  const int _n;
  ArcListVector _result;
  const StringNodeMap& _label;
};
  
} // namespace gm

#endif // GABOWMYERS_H
