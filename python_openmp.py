"""
cppyy with openmp code...
-------------------------
"""
import datetime as dt
print(dt.datetime.now())
import cppyy 
cppyy.sysconfig._CONFIG_VARS['EXTRA_CLING_ARGS'] = '-fopenmp'
cppyy.add_include_path('../np_vs_eigen/eigen/')
cppyy.include('openmp_trying.cpp')

print(dt.datetime.now())
# run the pll_linalgebra code from python !
uu = cppyy.gbl.pll_linalgebra()
print(dt.datetime.now())