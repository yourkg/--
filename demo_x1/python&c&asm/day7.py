from ctypes import *
'''参考：https://www.cnblogs.com/night-ride-depart/p/4907613.html
dll = CDLL("ok.dll")
dll.addf.restype = c_float
dll.addf.argtypes = (c_float, c_float)
print(dll.addf(8.3, 3.1))
'''
print("Python print：Hello, world.")

dll = CDLL("day7.dll")

print("\n  DLL in ok.\n\n")
dll.addf.restype = c_float
dll.addf.argtypes = (c_float, c_float)
print(dll.addf(8.3, 3.1))

dll.asmp()
