# The TwoPunctures Standalone code, adapted for C/C++ 

## Lineage

This code is a modified version of the
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

The standalone TwoPunctures code added some C++ functionality,
which limits the interoperability of the library with legacy software
numerical relativit software.
I've added a C-api in the Source files: `TwoPunctures_c_api.h` and `TwoPunctures_c_api.cc`.

## Physics

The original twopunctures code created initial data for two puncture black holes using a single domain spectral method.
The method used is described in *Marcus Ansorg, Bernd Brügmann, Wolfgang Tichy*,
"A single-domain spectral method for black hole puncture data",
[PRD 70, 064011 (2004)](https://arxiv.org/ct?url=http%3A%2F%2Fdx.doi.org%2F10%252E1103%2FPhysRevD%252E70%252E064011&v=e1b6f829),
[arXiv:gr-qc/0404056](https://arxiv.org/abs/gr-qc/0404056).

The main changes we have added is features to compute the full metric and first derivatives of it
(see the Documentation).

## TODO

* Add features to compute modified gravity equations
* Add time derivatives of lapse and shift as functions of generalized harmonic
source terms. 

## License

The original authors of the TwoPunctures are Marcus Ansorg, Erik Schnetter, Frank Löffler.
Adaptions to make the standalone code were made by Federico Guercilena, Sven Köppel,
and incorporated code written by 
Vasileios Paschalidis, Zachariah B. Etienne, Roman Gold, and Stuart L. Shapiro.

This code is licensed under the same LGPLv2.1 license as the original
TwoPunctures code; see the LICENSE file for details.
