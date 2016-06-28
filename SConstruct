import os
# On Windows, the path is incorrect, so change the path to
# the environment one. Even though windows is the problem,
# do it for all platforms
newpath=os.environ.get('PATH')
env = Environment(ENV = { 'PATH' : newpath } )
env.Append(CPPPATH = ['SpecialKEval/src'])

libs = ['boost_program_options', 'boost_system','pthread','fann']
env.Program('holdembot', ['src/main.cpp','src/HoldemBot.cpp','src/Game.cpp', 'src/GameState.cpp','src/Decision.cpp','src/Utils.cpp','SpecialKEval/SevenEval.o','SpecialKEval/FiveEval.o'], LIBS=libs)
