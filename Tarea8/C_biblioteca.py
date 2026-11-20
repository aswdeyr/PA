import ctypes
import platform
import numpy as np

lib = ctypes.CDLL("./Mult_Matrices.dll") #Esta compilado para funcionar en winwdows

FLOAT_P = np.ctypeslib.ndpointer(dtype=np.float32, ndim=2, flags="C_CONTIGUOUS")


lib.Multi.argtypes = [FLOAT_P, FLOAT_P, FLOAT_P, ctypes.c_int]
lib.Multi.restype = None


N = 16
A = np.random.rand(N, N).astype(np.float32)
B = np.random.rand(N, N).astype(np.float32)
C = np.zeros((N, N), dtype=np.float32)


lib.Multi(A, B, C, N)


Res_NP = A @ B
if(np.sum(C != Res_NP) == 0):
    print("El resultado usando la biblioteca creada es igual al resultado de numpy")
else:
    print("Los resultados son diferentes")
