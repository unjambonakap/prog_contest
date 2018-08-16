
A := sqrt(10 + 2*sqrt(5));
cpi5 := 1 / 4 * (1 + sqrt(5));
spi5 := 1 / 4 * simplify(sqrt(10 - 2*sqrt(5)) / A) * A;
c2pi5 := 1 / 4 * (-1 + sqrt(5));
s2pi5 := 1 / 4 * A;

circle_points := [
  [1, 0],
  [c2pi5, s2pi5],
  [-cpi5, spi5],
  [-cpi5, -spi5],
  [c2pi5, -s2pi5]
  ];

orth := x -> [-x[2], x[1]];
tangents := map(orth, circle_points);



next_pt := proc(tangent_and_dir)
  tangent := tangent_and_dir[1];
  dir := tangent_and_dir[2];
  dirx := tangents[tangent];
  diry := orth(dirx);
  nt := 1 + ((tangent - 1 + 5 + dir) mod 5);
  return [nt, 8 * simplify(dirx *~ s2pi5 +~ dir *~ diry *~ (1 - c2pi5))];
end proc;

basis := MutableSet(1, sqrt(5), A, A*sqrt(5));
sym_ops_list := [basis, basis];

process_op := proc(sym_ops, operation_)
  operation := expand(operation_);
  if type(operation, `+`) then
    a := process_op(sym_ops, op(1, operation));
    b := process_op(sym_ops, op(2, operation));
    print(a, b);
    print(op(a));
    return [op(a), op(b)];
  end if;

  for sym in sym_ops do
    if type(operation / sym, rational) then
      return [[sym, operation / sym]];
    fi;
  od;

  error "Bad stuff";

  print("INSERT ", operation);
  insert(sym_ops, operation);
  print("AA");
  return [operation, 1];
end proc;


actions := [];
for i from 1 to 5 do
  actions := [op(actions), [i, next_pt([i, -1])], [i, next_pt([i, 1])] ];
od;

results := [];
for action in actions do
  v1 := process_op(sym_ops_list[1], action[2][2][1]):
  v2 := process_op(sym_ops_list[2], action[2][2][2]):
  print("V1 >>> ", action[2][2][1], v1);
  print("V2 >>> ", action[2][2][2], v2);
  results := [op(results), [
    action,
    v1, v2
    ]]:
od;


print(sym_ops_list);
veclist := [];
for result in results do
  vec := []:
  print("ON >>> ", result[2], result[3]);
  for i from 0 to 1 do
    for sym in sym_ops_list[1+i] do
      v:=0:
      for entry in result[2+i] do
        if entry[1] = sym then
          v := entry[2]:
          break;
        fi;
      od;
      vec := [op(vec), v]:
    od;
  od;
  veclist := [op(veclist), [result[1][1], result[1][2][1], vec]]:
od;

print(veclist);


