#File: setup.py
#!/usr/bin/python2.7

from distutils.core import setup, Extension

PySwitchCli_module = Extension('_PySwitchCli', #????,???????
                        sources=['PySwitch_wrap.c',
                        					'gsw_api_func.c',
                        					'gsw_core.c',
                        					'gsw_io_wrap.c',
                        					'gsw_multi.c',
                        					'gsw_pce.c',
                        					'gsw_qos.c',
                        					'gsw_sw_init.c',
                        					'gsw_vlan.c',
                        					'gsw_py_interface.c'
                                ],
                      )

setup(name = 'PySwitchCli',	#??????
        version = '0.1',
        author = 'SWIG Docs',
        description = 'Simple swig pht from docs',
        ext_modules = [PySwitchCli_module], #????????????
        py_modules = ['PySwitchCli'], #?????????
    )