# The TwoPunctures Standalone code, adapted for (modified) generalized harmonic evolution

This code is a modified version of the [TwoPunctures standalone code](https://bitbucket.org/relastro/twopunctures-standalone/src/master/),
which in turn was adapted from the [TwoPunctures thorn](https://bitbucket.org/einsteintoolkit/einsteininitialdata),
which is part of the [Einstein toolkit](https://einsteintoolkit.org/). 

## Physics

The original twopunctures code created initial data for two puncture black holes using a single domain spectral method.
The method used is described in *Marcus Ansorg, Bernd Brügmann, Wolfgang Tichy*,
"A single-domain spectral method for black hole puncture data",
[PRD 70, 064011 (2004)](https://arxiv.org/ct?url=http%3A%2F%2Fdx.doi.org%2F10%252E1103%2FPhysRevD%252E70%252E064011&v=e1b6f829),
[arXiv:gr-qc/0404056](https://arxiv.org/abs/gr-qc/0404056).
The basic drivers have remained unchanged.

The main changes we have added is features to compute the full metric and first derivatives of it
(see the Documentation).

TODO: add features to compute modified gravity equations.

## License

The original authors of the TwoPunctures are Marcus Ansorg, Erik Schnetter, Frank Löffler.
Adaptions to make the standalone code were made by Federico Guercilena, Sven Köppel.

This code is licensed under the LGPLv2.1 license. Please see the LICENSE file for details.
