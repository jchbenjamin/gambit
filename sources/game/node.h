//
// $Source$
// $Date$
// $Revision$
//
// DESCRIPTION:
// Interface to class representing nodes in extensive form games
//
// This file is part of Gambit
// Copyright (c) 2002, The Gambit Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//

#ifndef NODE_H
#define NODE_H

#include "math/rational.h"
#include "efg.h"

#ifdef __GNUG__
#pragma interface
#endif   // __GNUG__

class Lexicon;

template <class T> class BehavAssessment;

class Node    {
  friend class efgGame;
  friend class BehavProfile<double>;
  friend class BehavProfile<gRational>;
  friend class BehavProfile<gNumber>;
  friend class BehavAssessment<double>;
  friend class BehavAssessment<gRational>;
  friend class BehavAssessment<gNumber>;
  friend class Lexicon;
  
  protected:
    bool mark;
    int number; // This is a unique identifier, not related to infoset memship
    efgGame *E;
    gText name;
    Infoset *infoset;
    Node *parent;
    gbt_efg_outcome_rep *outcome;
    gBlock<Node *> children;
    Node *whichbranch, *ptr, *gameroot;

    Node(efgGame *e, Node *p);
    ~Node();

    void DeleteOutcome(gbt_efg_outcome_rep *outc);

  public:
    efgGame *Game(void) const   { return E; }

    int NumChildren(void) const    { return children.Length(); }
    int GetNumber(void) const { return number; }
    int NumberInInfoset(void) const;
    const gArray<Node *> &Children(void) const { return children; }
    Infoset *GetInfoset(void) const   { return infoset; }
    bool IsTerminal(void) const { return (children.Length() == 0); }
    bool IsNonterminal(void) const { return !IsTerminal(); }
    EFPlayer *GetPlayer(void) const
      { if (!infoset)   return 0;
	else  return infoset->GetPlayer(); }
    Action *GetAction(void) const; // returns null if root node
    Node *GetChild(int i) const    { return children[i]; }
    Node *GetChild(const Action& a) const    
      { return children[a.GetNumber()]; }
    Node *GetChild(const Action* a) const    
    { return children[a->GetNumber()]; }
    Node *GetParent(void) const    { return parent; }
    Node *GetSubgameRoot(void) const  { return gameroot; }
    Node *NextSibling(void) const;
    Node *PriorSibling(void) const;

    const gText &GetName(void) const   { return name; }
    void SetName(const gText &s)       { name = s; }

};

#endif   // NODE_H






