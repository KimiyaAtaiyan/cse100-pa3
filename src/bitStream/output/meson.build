#/**
# * File Name: meson.build
# * Authors: Kimiya Ataiyan, Meghana Sridhar
# * PIDs: A15753878, A13299951
# * Date: 11/1/2019
# */

inc = include_directories('.')

	bit_output_stream = library('bit_output_stream', 
			   sources : ['BitOutputStream.cpp'])

bit_output_stream_dep = declare_dependency(include_directories : inc, 
					  link_with: bit_output_stream)

