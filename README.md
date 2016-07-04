DESCRIPTION:

Poker bot enging based on FANN framework written in C++ as practical and exprimental part of Bachelor's thesis.
Require slightly more development to be perfect. Project finished in Jan 2016.

HOWTO:

- install 'scons' tools to proces SConstruct make file
- run 'scons' in main directory
- run poker engine: cd mitbots && java -jar engine
- run bot: ./holdembot

EXTERNAL DEPENDENCIES:

- mitpokerbots: engine designed for poker bots championship released by MIT and available on their website (mitbots directory)
- FANN framework: neural networks framework (fann subrepo)
- SpecialKEval: naive tool for scoring hands (SpecialKEval subrepo)

DOCS:

Comments and source code of course :)

TODO

- provide some better way of scoring cards strength 

OTHER:

- build SpecialKEval subrepo first, its not added to scons because its usage should be exchanged with something else

STRUCTURE:

- ./src: source code
- ./inc: header files
- ./mitbots: mitpokerbots testing platform
- ./data: some runtime data like currently used neutal network and saved trained networks

