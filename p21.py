from collections import OrderedDict

def intersect(l1, l2):
  l3 = [x for x in l1 if x in l2]
  return l3

def red(d, ing, dd):
  allergen = None
  ingr = None
  for k, v in d.items():
    if len(v) == 1:
      allergen = k
      ingr = v[0]
      break
  
  del(d[allergen])
  del(ing[ingr])
  
  dd[allergen] = ingr
  
  for k, v in d.items():
    if ingr in v:
      v.remove(ingr)
      d[k] = v
  
  return d, ing, dd
  
def main():
	file = open("input.txt", "r")
	fo = open("out.txt", "w")
	#file = open("sample_input.txt", "r")
	inp = [line.strip() for line in file.readlines() if line.strip()]
	
	ing = dict()
	d = dict()
	
	for x in inp:
	  y = x.replace('(', '').strip(')')
	  yl = y.split(' ')
	  idx = yl.index('contains')
	  ing_list = yl[:idx]
	  #print(f"Ing List {ing_list}")
	    
	  for xx in ing_list:
	    if xx in ing:
	      ing[xx] = ing[xx] + 1
	    else:
	      ing[xx] = 1
	    
	  for i in range(idx + 1, len(yl)):
	    allergen = yl[i].strip(',')
	    
	    #print(f"Allergen {allergen} in one of {ing_list}")
	    if allergen in d.keys():
	      d[allergen] = intersect(d[allergen], ing_list)
	      #print(f"{allergen} already seen, updated {d[allergen]}")
	    else:
	      d[allergen] = ing_list
	      #print(f"New allergen {allergen}")
	
	#print(ing)
	
	dd = OrderedDict()
	while d:
	  #print(d)
	  #print(ing)
	  d, ing, dd = red(d, ing, dd)
	  	  
	ans = 0  	  
	for v in ing.values():
	  ans += v
	  
	print(ans)
	
	print(dd)
	
	ans2 = []
	ddk = sorted(dd.keys())
	
	print(dd)
	for k in ddk:
	  ans2.append(dd[k])
	  
	fo.write(",".join(ans2))  
	print(",".join(ans2))
	
if __name__ == "__main__":
	main()
