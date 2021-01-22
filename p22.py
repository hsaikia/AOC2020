def hsh(l1, l2):
  return flatten(l1) + ':' + flatten(l2)

def flatten(l):
  return ",".join(str(x) for x in l)

def sim(d1, d2, m):
  #print(f"P1 deck {d1}")
  #print(f"P2 deck {d2}")
  while d1 and d2:
    h = hsh(d1, d2)
    if h in m:
      return d1, d2, m, d1, True
    m.add(h)
    
    #print(m)
    
    a = d1[0]
    b = d2[0]
    
    #print(f"P1 plays {a}")
    #print(f"P2 plays {b}")
    
    d1.pop(0)
    d2.pop(0)
      
    d = None  
    
    if a <= len(d1) and b <= len(d2):
      #print("Starting Recursive Game")
      d11 = d1[:a]
      d22 = d2[:b]
      
      mm = set()
      d11, d22, mm, d, p1_wins = sim(d11, d22, mm)
      
      if p1_wins:
        #print("P1 wins the sub game (loop)")
        d1.append(a)
        d1.append(b)
        #return d1, d2, mm, d11, True
      elif len(d11) > len(d22):
        #print("P1 wins the sub game")
        d1.append(a)
        d1.append(b)
        d = d1
      else:
        #print("P2 wins the sub game")
        d2.append(b)
        d2.append(a)
        d = d2
    else:    
      if a > b:
        #print("P1 wins this round")
        d1.append(a)
        d1.append(b)
        d = d1
      else:
        #print("P2 wins this round")
        d2.append(b)
        d2.append(a)
        d = d2
    
    if len(d1) == 0:
      return d1, d2, m, d2, False
    elif len(d2) == 0:
      return d1, d2, m, d1, False
  
  #return sim(d1, d2, m)

def main():
	file = open("input.txt", "r")
	#fo = open("out.txt", "w")
	#file = open("sample_input.txt", "r")
	#file = open("S1.txt", "r")
	inp = [line.strip() for line in file.readlines() if line.strip()]
	
	print(inp)
	d1 = []
	d2 = []
	sz = len(inp) // 2
	print(sz)
	for i in range(sz - 1):
	  d1.append(int(inp[i + 1]))
	  d2.append(int(inp[i + sz + 1]))
	  
	# game 1
	m = set()
	d1, d2, m, d, st = sim(d1, d2, m)
	
	print(d)
	s = 0
	for i in range(len(d)):
	  s += (len(d) - i) * d[i]
	  
	print(s)
	
if __name__ == "__main__":
	main()
