/* 
 * utils.h
 *
 *  Created on: 18-jun-2015
 *      Author: M. El-Kebir
 */

#ifndef UTILS_H
#define UTILS_H

#include <istream>
#include <map>
#include <string>
#include <lemon/list_graph.h>

namespace gm {
  
typedef lemon::ListDigraph Digraph;
DIGRAPH_TYPEDEFS(Digraph);
typedef Digraph::NodeMap<std::string> StringNodeMap;
typedef std::map<std::string, Node> StringToNodeMap;

typedef enum
{
  VERBOSE_NONE,
  VERBOSE_ESSENTIAL,
  VERBOSE_NON_ESSENTIAL,
  VERBOSE_DEBUG
} VerbosityLevel;

extern VerbosityLevel g_verbosity;
  
bool readGraph(std::istream& in,
               Digraph& g,
               StringNodeMap& nodeToLabel,
               StringToNodeMap& labelToNode);

} // namespace gm

#endif /* UTILS_H */