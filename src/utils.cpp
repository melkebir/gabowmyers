/*
 * utils.cpp
 *
 *  Created on: 18-jun-2015
 *      Author: M. El-Kebir
 */

#include "utils.h"

namespace gm {

VerbosityLevel g_verbosity = VERBOSE_ESSENTIAL;

bool readGraph(std::istream& in,
               Digraph& g,
               StringNodeMap& nodeToLabel,
               StringToNodeMap& labelToNode)
{
  std::string label1, label2;
  while (in.good())
  {
    in >> label1;
    if (in.eof())
    {
      return true;
    }
    
    in >> label2;

    if (in.eof())
    {
      std::cerr << "Premature EOF" << std::endl;
      return false;
    }
    
    Node node1 = lemon::INVALID;
    if (labelToNode.find(label1) == labelToNode.end())
    {
      node1 = g.addNode();
      labelToNode[label1] = node1;
      nodeToLabel[node1] = label1;
    }
    else
    {
      node1 = labelToNode[label1];
    }
    
    Node node2 = lemon::INVALID;
    if (labelToNode.find(label2) == labelToNode.end())
    {
      node2 = g.addNode();
      labelToNode[label2] = node2;
      nodeToLabel[node2] = label2;
    }
    else
    {
      node2 = labelToNode[label2];
    }
    
    g.addArc(node1, node2);
  }
  
  return true;
}

} // namespace gm