
m := [
[1,1,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,1,0,0,1,0,0,1,0,1,0,1,0],
[0,0,0,1,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,0,0,0,0,0,0,0,0,0],
[1,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,0,1,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,1,0,0,0,0,0,0],
[0,0,0,0,0,1,0,0,1,0,0,0,0,0],
[1,0,0,0,0,0,0,0,0,1,0,0,0,0],
[0,0,0,0,0,0,0,0,1,0,1,0,0,0],
[0,0,0,0,1,0,0,1,0,0,0,1,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,1,0],
[0,0,0,0,0,0,0,0,1,0,0,0,0,1],
[0,0,0,0,1,0,0,0,0,0,0,1,0,0]
];

with(LinearAlgebra);
M := Matrix(m);
Eigenvalues(M);