External dependencies:

- mitpokerbots: engine desinged for poger bots championship released by MIT and available on their website (mitbots directory)
- FANN framework: neural networks framework (fann subrepo)
- SpecialKEval: naive tool for scoring hands (SpecialKEval subrepo)

HOWTO:

- install 'scons' tools to proces SConstruct make file
- run 'scons' in main directory
- run poker engine: cd mitbots && java -jar engine*
- run bot: ./holdembot

DOCS:

Comments and source code of course :)

OTHER:

- build SpecialKEval subrepo first, its not added to scons
