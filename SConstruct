import os
# On Windows, the path is incorrect, so change the path to
# the environment one. Even though windows is the problem,
# do it for all platforms
newpath=os.environ.get('PATH')
env = Environment(ENV = { 'PATH' : newpath })

boost_libs = ['boost_program_options', 'boost_system','pthread','fann']
env.Program('holdembot', ['src/main.cpp','src/HoldemBot.cpp','src/HoldemGame.cpp'], LIBS=boost_libs)
