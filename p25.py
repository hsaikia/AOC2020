# Incomplete! Part 1 only
def encrypt(val, sn, loop_size):
	itr = 0
	while itr < loop_size:
		val = (sn * val) % 20201227
		itr += 1
	return val

def find(sn):
  n = 0
  itr = 1
  while True:
    if sn % 7 == 0:
      if sn == 7:
        return itr 
      else:
        itr += 1
        n = 0
        sn = sn // 7
        continue
    sn += 20201227
    n += 1

def sim(sn1, sn2):
  d = dict()
  for ls in range(1, 50000):
    v = encrypt(1, 7, ls)
    #print(f"LS {ls} V {v}")
    d[v] = ls
    if sn1 in d and sn2 in d:
      break
  return d[sn1], d[sn2]
def main():
	
	file = open("input.txt", "r")
	#file = open("sample_input.txt", "r")
	inp = [int(line.strip()) for line in file.readlines() if line.strip()]
	
	print(inp)
	#ret = sim(inp[0], inp[1])
	ret1 = find(inp[0])
	ret2 = find(inp[1])
	
	v1 = encrypt(1, 7, ret1)
	v2 = encrypt(1, 7, ret2)
	
	#print(encrypt(1, inp[0], ))
	
	print(f"{ret1} {ret2}")
	print(f"{v1} {v2}")
	
	v3 = encrypt(1, v1, ret2)
	v4 = encrypt(1, v2, ret1)
	print(f"{v3} {v4}")
	
if __name__ == "__main__":
	main()
