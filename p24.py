def sim(bs):
	wd = dict()
	bd = dict()
	for x, y in bs:
		bd[(x, y)] = 0
		count = 0
		t = [-1, 0, 1]
		for i in t:
			for j in t:
				if i == 0 and j == 0:
					continue
				if i + j == -2 or i + j == 2:
					continue
				nx = x + i
				ny = y + j
				
				if (nx, ny) in bs:	
					bd[(x, y)] += 1
				else:
					if (nx, ny) in wd:
						wd[(nx, ny)] += 1
					else:
						wd[(nx, ny)] = 1
			
	for bt, c in bd.items():
		if c == 0 or c > 2:
			bs.remove(bt)
			
	for wt, c in wd.items():
		if c == 2:
			bs.add(wt)
	
	return bs
	
def process(s, x, y):
  if s == "":
    return x, y
  ss = s
  if s[0] == 'n':
    if s[1] == 'e':
      y += 1
    else:
      x -= 1
      y += 1
    ss = s[2:]
  elif s[0] == 's':
    if s[1] == 'e':
      x += 1
      y -= 1
    else:
      y -= 1
    ss = s[2:]
  elif s[0] == 'e':
    x += 1
    ss = s[1:]
  elif s[0] == 'w':
    x -= 1
    ss = s[1:]
  return process(ss, x, y)
  
def main():
	file = open("input.txt", "r")
	#file = open("sample_input.txt", "r")
	inp = [line.strip() for line in file.readlines() if line.strip()]
	
	d = set()
	for s in inp:
	  x, y = process(s, 0, 0)
	  if (x, y) in d:
	  	d.remove((x, y))
	  else:
	  	d.add((x, y))
	
	itr = 0
	while itr < 100:
		d = sim(d)
		itr += 1
		print(f"Day {itr} {len(d)} tiles")
		
	
if __name__ == "__main__":
	main()
