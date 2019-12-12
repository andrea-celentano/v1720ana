from utils import *
from util import cmloptions, loadoptions, check_if_dir_exist
from init_env import init_environment
import platform
import SCons
import os
from SCons.Environment import *
from SCons.Variables import *
from SCons.Script import *



#Need a manual setting
opts = Variables()
cmloptions(opts)
env = Environment(tools=['default'], options = opts, ENV = os.environ)
from loadroot import loadroot
loadroot(env)
from loadxerces import loadxerces
loadxerces(env)
from loadccdb import loadccdb
loadccdb(env)
loadoptions(env)




#A.C. probably do this better
if (platform.system()=="Darwin"):
	print "We are on MAC"
	env.AppendUnique(LINKFLAGS='-flat_namespace')
	env.AppendUnique(SHLINKFLAGS=['-undefined', 'suppress'])
 
env.Append(CPPPATH=Dir('#/src/external').srcnode().abspath)
env.Append(CPPPATH=Dir('#/src/libraries').srcnode().abspath)
env.Append(CPPPATH=Dir('#/src/plugins').srcnode().abspath)
env.Append(CPPPATH=Dir('#/.').srcnode().abspath)
env.Append(LIBPATH = ['#/lib'])

env.Replace(RPATH=Dir('#/lib').srcnode().abspath)

#This drove me crazy! jlab_software jana was including this, and we need it for sophisticated rootspy features..
env.Append(LINKFLAGS = '-rdynamic')
env.Append(LINKFLAGS = '-lSpectrum')
env.Append(CXXFLAGS = '-g')
Export('env')

libExt=SConscript('src/external/SConstruct')
lib=SConscript('src/libraries/SConstruct')
progs=SConscript('src/programs/SConstruct')
plugins=SConscript('src/plugins/SConstruct')










