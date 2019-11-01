# /**
#  * File Name: src/meson.build
#  * Authors: Kimiya Ataiyan, Meghana Sridhar
#  * PIDs: A15753878, A13299951
#  * Date: 11/1/2019
#  */

subdir('bitStream')
subdir('encoder')

compress_exe = executable('compress.cpp.executable', sources : ['compress.cpp'],
			  dependencies : [bit_stream_dep, encoder_dep],
                           install : true)

uncompress_exe = executable('uncompress.cpp.executable', sources : ['uncompress.cpp'],
			    dependencies : [bit_stream_dep, encoder_dep], 
                           install : true)
