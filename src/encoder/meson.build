#/**
# * File Name: meson.build
# * Authors: Kimiya Ataiyan, Meghana Sridhar
# * PIDs: A15753878, A13299951
# * Date: 11/1/2019
#*/

inc = include_directories('.')

encoder = library('encoder', sources : ['HCNode.hpp', 'HCTree.cpp', 'HCTree.hpp'])

encoder_dep = declare_dependency(include_directories : inc, 
					  link_with: encoder)






