"""
cppyy with openmp code...
-------------------------
"""
import datetime as dt
print('Just started...', dt.datetime.now())
import cppyy 
import cppyy_backend.loader as l
cppyy.sysconfig._CONFIG_VARS['EXTRA_CLING_ARGS'] = '-fopenmp'
l.set_cling_compile_options(True) 
cppyy.add_include_path('../np_vs_eigen/eigen/')
cppyy.include('openmp_trying.cpp')

start = dt.datetime.now()
print(start)
# run the pll_linalgebra code from python !
uu = cppyy.gbl.pll_linalgebra()
stop = dt.datetime.now()
print(stop)
print(f'{(stop-start)/20000} duration')