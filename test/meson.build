#/**
# * File Name: test/meson.build
# * Authors: Kimiya Ataiyan, Meghana Sridhar
# * PIDs: A15753878, A13299951
# * Date: 11/1/2019
# */


# === BitInpustream Test ====

test_bit_input_exe = executable('test_BitInputStream.cpp.executable', 
		     sources : ['test_BitInputStream.cpp'], 
                     dependencies : [bit_input_stream_dep, encoder_dep, gtest_dep])
test('my BitInputStream test', test_bit_input_exe)




# === BitOutputStream Test ===

test_bit_output_exe = executable('test_BitOutputStream.cpp.executable', 
                                 sources : ['test_BitOutputStream.cpp'],
				 dependencies : [bit_output_stream_dep,encoder_dep, gtest_dep])
test('my BitOutputStream test', test_bit_output_exe)



# === HCTree Test ===
test_hc_tree_exe = executable('test_HCTree.cpp.executable', 
			      sources : ['test_HCTree.cpp'],
			      dependencies : [bit_input_stream_dep, bit_output_stream_dep, encoder_dep, gtest_dep])
test('my HCTree test', test_hc_tree_exe)

