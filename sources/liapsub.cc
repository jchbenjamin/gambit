//
// FILE: liapsub.cc -- Solve efg by liap on nfg
//
// @(#)liapsub.cc	2.5 19 Jul 1997
//

#include "liapsub.h"

int NFLiapBySubgame::SolveSubgame(const Efg &E, const EFSupport &sup,
				   gList<BehavSolution<double> > &solns)
{
  BehavProfile<double> bp(E, sup);
  
  subgame_number++;

  gArray<int> infosets(infoset_subgames.Lengths());

  for (int pl = 1; pl <= E.NumPlayers(); pl++)  {
    int niset = 1;
    for (int iset = 1; iset <= infosets[pl]; iset++)  {
      if (infoset_subgames(pl, iset) == subgame_number)  {
	for (int act = 1; act <= bp.Support().NumActions(pl, niset); act++)
	  bp(pl, niset, act) = start(pl, iset, act);
	niset++;
      }
    }
  }

  Nfg *N = MakeReducedNfg(E, EFSupport(E));

  NFSupport *S = new NFSupport(*N);

  ViewNormal(*N, S);

  MixedProfile<double> mp(*N, *S);

  BehavToMixed(E, bp, *N, mp);

  MixedProfile<gNumber> start(*N, *S);
  for (int i = 1; i <= start.Length(); i++)
    start[i] = mp[i];

  long this_nevals, this_niters;

  gList<MixedSolution<double> > subsolns;
  Liap(*N, params, start, subsolns, this_nevals, this_niters);

  nevals += this_nevals;

  for (int i = 1; i <= subsolns.Length(); i++)  {
    BehavProfile<double> bp(E);
    MixedToBehav(*N, subsolns[i], E, bp);
    solns.Append(bp);
  }

  delete S;
  delete N;
  return params.status.Get();
}

NFLiapBySubgame::NFLiapBySubgame(const Efg &E, const NFLiapParams &p,
				 const BehavProfile<gNumber> &s, int max)
  : SubgameSolver<double>(E, s.Support(), max),
    nevals(0), subgame_number(0),
    infoset_subgames(E.NumInfosets()), params(p), start(s)
{ }

NFLiapBySubgame::~NFLiapBySubgame()   { }
