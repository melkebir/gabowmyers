/*
 * gabowmyers.cpp
 *
 *  Created on: 25-jun-2015
 *      Author: M. El-Kebir
 */

#include "gabowmyers.h"
#include <cassert>

namespace gm {

GabowMyers::GabowMyers(const Digraph& g,
                       const StringNodeMap& label)
  : _g(g)
  , _n(lemon::countNodes(_g))
  , _result()
  , _label(label)
{
}
  
void GabowMyers::run(Node root)
{
  _result.clear();
  
  BoolNodeMap nodesG(_g, true);
  BoolNodeMap nodesT(_g, false);
  BoolNodeMap nodesL(_g, false);
  
  BoolArcMap arcsG(_g, true);
  BoolArcMap arcsT(_g, false);
  BoolArcMap arcsL(_g, false);
  
  SubDigraph G(_g, nodesG, arcsG);
  SubDigraph T(_g, nodesT, arcsT);
  SubDigraph L(_g, nodesL, arcsL);
  
  SubBfs bfsL(L);
  bfsL.init();

  ArcList F;
  for (SubOutArcIt a(G, root); a != lemon::INVALID; ++a)
  {
    F.push_back(a);
  }
  
  T.enable(root);
  grow(root, G, T, L, bfsL, F);
}
  
void GabowMyers::grow(Node r,
                      SubDigraph& G,
                      SubDigraph& T,
                      SubDigraph& L,
                      SubBfs& bfsL,
                      ArcList& F)
{
  // finds all spanning trees rooted at r containing T
  if (lemon::countArcs(T) == _n - 1)
  {
    // clear L
    for (NodeIt v(_g); v != lemon::INVALID; ++v)
    {
      L.disable(v);
    }
    for (ArcIt a(_g); a != lemon::INVALID; ++a)
    {
      L.disable(a);
    }

    // report T and copy to L
    ArcList arcsL;
    L.enable(r);
    for (SubArcIt a(T); a != lemon::INVALID; ++a)
    {
      arcsL.push_back(a);
      L.enable((Arc)a);
      L.enable((Node)T.target(a));
      std::cout << _label[T.source(a)] << " -> " << _label[T.target(a)] << std::endl;
    }
    std::cout << std::endl;
    _result.push_back(arcsL);
  }
  else
  {
    ArcList FF;
    
    bool done;
    do
    {
      assert(!F.empty());

      Arc uv = F.back();
      F.pop_back();
      Node u = _g.source(uv);
      Node v = _g.target(uv);
      
      assert(T.status(u));
      assert(!T.status(v));
      assert(!T.status(uv));
      
      // add uv to T
      T.enable(uv);
      T.enable(v);
//      std::cout << _label[u] << " -> " << _label[v] << std::endl;

      ArcList newF = F;
      
      // push each arc vw where w not in V(T) onto F
      for (SubOutArcIt vw(G, v); vw != lemon::INVALID; ++vw)
      {
        Node w = G.target(vw);
        if (!T.status(w))
        {
          newF.push_back(vw);
        }
      }
      
      // remove each arc wv where w in T from F
      for (ArcListNonConstIt it = newF.begin(); it != newF.end();)
      {
        if (_g.target(*it) == v && T.status(_g.source(*it)))
        {
          it = newF.erase(it);
        }
        else
        {
          ++it;
        }
      }
      
      grow(r, G, T, L, bfsL, newF);
      
      G.disable(uv);
      T.disable(uv);
      T.disable(v);
      
      FF.push_back(uv);

      done = true;
      if (lemon::countNodes(L) != 0)
      {
        bfsL.run(v);
//        for (SubArcIt a(L); a != lemon::INVALID; ++a)
//        {
//          std::cout << "// L: " << _label[L.source(a)] << " -> " << _label[L.target(a)] << std::endl;
//        }
//        
//        for (SubNodeIt w(L); w != lemon::INVALID; ++w)
//        {
//          if (bfsL.reached(w))
//          {
//            std::cout << "Reached " << _label[w] << std::endl;
//          }
//        }
//        std::cout << std::endl;
        
        for (SubInArcIt wv(G, v); wv != lemon::INVALID; ++wv)
        {
//          std::cout << "// " << _label[G.source(wv)] << " -> " << _label[G.target(wv)] << std::endl;
          Node w = G.source(wv);
          if (!bfsL.reached(w))
            done = false;
        }
      }
    } while (!done);
    
    for (ArcListRevIt it = FF.rbegin(); it != FF.rend(); ++it)
    {
      Arc a = *it;
      assert(!G.status(a));
      
      F.push_back(*it);
      G.enable(a);
    }
  }
}
  
} // namespace gm
