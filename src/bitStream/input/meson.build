# /**
#  * File Name: src/bitStream/input/meson.build
#  * Authors: Kimiya Ataiyan, Meghana Sridhar
#  * PIDs: A15753878, A13299951
#  * Date: 11/1/2019
#  */

inc = include_directories('.')

	bit_input_stream = library('bit_input_stream', 
			   sources : ['BitInputStream.cpp', 'BitInputStream.hpp'])

bit_input_stream_dep = declare_dependency(include_directories : inc, 
					  link_with: bit_input_stream)
