import os, sys, platform

env = Environment()

# Hax
architecture="x86"
variant = architecture+'/Debug'

# Absolute path for includes and libs
env['SANSKRIT_INCLUDE'] = [os.path.abspath('include/')]
env['SANSKRIT_LIB'] = [os.path.abspath('lib/' + variant)]

libsanskrit = SConscript('src/SConscript', variant_dir='lib/'+variant, duplicate=False, exports='env')
test = SConscript('test/SConscript', variant_dir='bin/'+variant, duplicate=False, exports='env')
