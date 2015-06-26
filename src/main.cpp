/*
 * main.cpp
 *
 *  Created on: 18-jun-2015
 *      Author: M. El-Kebir
 */

#include "utils.h"
#include "gabowmyers.h"
#include <fstream>

using namespace gm;

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0]
              << " <EDGE_LIST> <ROOT>" << std::endl;
    return 1;
  }
  
  std::ifstream inFile(argv[1]);
  if (!inFile.good())
  {
    std::cerr << "Unable to open '" << argv[1]
              << "' for reading" << std::endl;
    return 1;
  }
  
  Digraph g;
  StringNodeMap nodeToLabel(g);
  StringToNodeMap labelToNode;
  if (!readGraph(inFile, g, nodeToLabel, labelToNode))
  {
    return 1;
  }
  
  if (labelToNode.find(argv[2]) == labelToNode.end())
  {
    std::cerr << "Incorrect root node label '" << argv[2] << "'" << std::endl;
    return 1;
  }
  
  GabowMyers gm_alg(g, nodeToLabel);
  gm_alg.run(labelToNode[argv[2]]);
    
  return 0;
}