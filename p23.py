def rotate(l, idx):
  return l[idx:] + l[:idx] 

def sim(l, idx):
  print(f"cups: {l[:10]}")
  n = l[idx] - 1
  rl = rotate(l, idx)
  #print(f"Rotated L {rl}")
  n3 = rl[1:4]
  #print(f"pick up: {n3}")
  rest = rl[4:]
  
  #print(f"N3 {n3} Rest {rest}")
  mi = min(rest)
  mx = max(rest)
  while True:
    if n in n3:
      n -= 1
    elif n in rest:
      break
    
    if n < mi:
      n = mx
  
  #print(f"destination: {n}")
  idx_next = rest.index(n)
  #print(f"Index next {idx_next} n {n}")
  ll = [l[idx]] + rest[:idx_next + 1] + n3 + rest[idx_next + 1:]
  return ll, 1

def pr(nd):
  l = [1]
  n = 1
  while True:
    n = nd[n]
    if n == 1:
      break
    l.append(n)
  return l
  
def sim2(nd, n):
  #print(f"Current Key {n} L {pr(nd)}")
  next_key = n - 1
  next_3 = []
  next_3.append(nd[n])
  next_3.append(nd[nd[n]])
  next_3.append(nd[nd[nd[n]]])
  
  #print(f"N3: {next_3}")
  mi = 1
  mx = 1000000
  while mi in next_3:
    mi += 1
    #print(mi)
  while mx in next_3:
    mx -= 1
    #print(mx)
  
  while True:
    if next_key in next_3:
      next_key -= 1
      continue
    if next_key < mi:
      next_key = mx
      continue
    break
  
  #print(f"Next N: {next_key}")
    
  tmp0 = nd[n]  
  tmp1 = nd[next_key]
  tmp2 = nd[nd[nd[nd[n]]]]
  
  #print(f"TMP {tmp0} {tmp1} {tmp2}")
  
  nd[nd[nd[nd[n]]]] = tmp1
  nd[n] = tmp2
  nd[next_key] = tmp0
  
  return nd, nd[n]
  
def main():
  file = open("input.txt", "r")
  #fo = open("out.txt", "w")
  #file = open("sample_input.txt", "r")
  #file = open("S1.txt", "r")
  inp = [list(line.strip()) for line in file.readlines() if line.strip()]
  
  l = [int(x) for x in inp[0]]
  L = len(l)
  
  big_num = 1000000
  
  nd = dict()
  for i in range(L):
    nd[l[i]] = l[(i + 1) % L]
  mx = max(l)
  nd[l[L - 1]] = mx + 1 
  for x in range(mx + 1, big_num):
    nd[x] = x + 1
  itr = 10000000
  nd[big_num]= l[0]
  #print(nd)
  n = l[0]
  while itr > 0:
    if itr % 1000000 == 0:
      print(f"{itr} iterations left")
    #print(f"N: {n}")
    #print(nd)
    nd, n = sim2(nd, n)
    itr -= 1
    #print(f"Move {10 - itr + 1}")
  #print(f"Final {nd}")
  n = 1
  ret = 1
  itr = 1
  while itr < 3:
    ret *= nd[n]
    print(nd[n])
    n = nd[n]
    itr += 1
    
  print(ret)  
#   i = l.index(1)
#   l = rotate(l, i)
#   print(f"Final {l[:3]}")
#   #print("".join(str(x) for x in l[1:]))
if __name__ == "__main__":
  main()
