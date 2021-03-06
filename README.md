# The Standalone TwoPunctures code, with a C api 

## Lineage 

This repository contains a C-api (and code) for the 
[TwoPunctures standalone code](https://bitbucket.org/relastro/twopunctures-standalone/src/master/),
which in turn was adapted from the
[TwoPunctures thorn](https://bitbucket.org/einsteintoolkit/einsteininitialdata),
which is part of the [Einstein toolkit](https://einsteintoolkit.org/). 
The standalone code this code is based on also
incorporated some speedups of the spectral interpolation methods,
which are described in
"An efficient spectral interpolation routine for the TwoPunctures code"
*Vasileios Paschalidis, Zachariah B. Etienne, Roman Gold, Stuart L. Shapiro*,
[arXiv:1304.0457](https://arxiv.org/abs/1304.0457)).

The original TwoPunctures code was written in C, but
the standalone TwoPunctures code (which contains some of the improvements
by Paschalidis et. al.) was partially rewritten in C++,
which limits the interoperability of the library with 
numerical relativity software written in C
(namely, the `gh3d2m` numerical relativity code,
which is currently mostly maintained by Will East and Frans Pretorius).
I've added a C-api in the Source files:
`TwoPunctures_c_api.h` and `TwoPunctures_c_api.cc`.

## Physics

The TwoPunctures code computes initial data for two puncture black holes using a single domain
(pseudo)spectral method.
The method used is described in *Marcus Ansorg, Bernd Brügmann, Wolfgang Tichy*,
"A single-domain spectral method for black hole puncture data",
[PRD 70, 064011 (2004)](https://arxiv.org/ct?url=http%3A%2F%2Fdx.doi.org%2F10%252E1103%2FPhysRevD%252E70%252E064011&v=e1b6f829),
[arXiv:gr-qc/0404056](https://arxiv.org/abs/gr-qc/0404056).

## OpenMP and the gh3d2m numerical relativity code 

The default Makefile setting under `/Source` is to not compile with OpenMP.
If you are using `gh3d2m` code,
I would recommend NOT compiling with OpenMP,
as it allows you to call TwoPunctures on each CPU core when using MPI with
that code.
 
## License

The original authors of the TwoPunctures are Marcus Ansorg, Erik Schnetter, Frank Löffler.
Adaptations to make the standalone code were made by Federico Guercilena, Sven Köppel,
and incorporated an fast interpolation code written by 
Vasileios Paschalidis, Zachariah B. Etienne, Roman Gold, and Stuart L. Shapiro.

This code is licensed under the same LGPLv2.1 license as the original
TwoPunctures code; see the LICENSE file for details.
