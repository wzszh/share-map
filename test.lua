local ffi = require 'ffi'


ffi.cdef [[
	int sharemap_test();
]]

local C = ffi.C

sm = ffi.load('./sharemap.so')

sm.sharemap_test()
