debug = False
#debug = True

def pr(s):
	if debug:
		print(s)

def match(rules, key, s):
	if s == "":
		return True, s
	pr(f"Matching {s} with key {key}")
	# any matching sub-rule r returns True
	for r in rules[key]:
		ss = s
		pr(f"Checking sub-rule {r}")
		# All child rules must match for r to match
		match_r = True
		for child_key in r:
			if ss == "":
				match_r = False
				pr(f"Rule {r} s [{ss}] failed at key {child_key} Empty")
				break
			elif '"' in rules[child_key][0][0]:
				if ss[0] != rules[child_key][0][0].strip('"'):
					match_r = False
					pr(f"Rule {r} s [{ss}] failed at key {child_key} Wrong Char")
					break
				else:
					pr(f"Matched character {ss[0]}")
					ss = ss[1:]
			else:
				match_r, ss = match(rules, child_key, ss)
				if match_r == False:
					pr(f"Rule {r} s [{ss}] failed at key {child_key} Child Key")
					break
				else:
					pr(f"Rule {r} s [{ss}] passed at key {child_key} Child Key")
		if match_r :
			pr(f"Matched rule {r}, returning rest of string [{ss}]")
			return True, ss
	#print(f"Some rules failed.. Ret {s}")
	return False, s

def main():
	#file = open("input.txt", "r")
	file = open("S1.txt", "r")
	#file = open("S2.txt", "r")
	#file = open("sample_input.txt", "r")
	inp = [line.strip() for line in file.readlines() if line.strip()]
	
	#print(inp)
	
	queries = []
	
	d = dict()
	for x in inp:
	  l = x.split(" ")
	  if l[0][-1] == ':':
	    idx = l[0][0:-1] 
	    d[idx] = []
	    ll = []
	    for i in range(1, len(l)):
	      if l[i] == '|':
	        d[idx].append(ll)
	        ll = []
	      else:
	        ll.append(l[i])
	    d[idx].append(ll)
	    #red(d, idx)
	  else:
	    queries.append(x)
	  
	#print(d)
	sz = 8
	count = 0
	for q in queries:
	  #print(f"Checking [{q}]")
	  i = sz
	  matched = False
	  while i <= len(q) - sz:
	    first_half = q[:i]
	    second_half = q[i:]
	    
	    ret1 = True 
	    s1 = ""
	    for j in range(0, i//sz):
	      t_ret1, t_s1 = match(d, '8', first_half[sz*j:sz*j+sz])
	      if t_ret1 == False:
	        ret1 = False
	        break
	    
	    ret2, s2 = match(d, '11', second_half)
	    
	    #print(f"FH [{first_half}] matches 8? {ret1} Rem {s1}")
	    #print(f"SH [{second_half}] matches 11? {ret2} Rem {s2}")
	    
	    if ret1 and ret2 and s1 == "" and s2 == "":
	      print(f"{q} matched [{s1}] [{s2}]")
	      count += 1
	      break
	    i += sz
      
# 	ret, s = match(d, '0', queries[4])
# 	print(f"Matching {queries[4]} Ret {ret} Rem {s}")
	# count = 0
	# for q in queries:
	# 	ret, s = match(d, '0', q)
	# 	m = ret and s == ""
	# 	count += m
	# 	print(f"{q} ret {ret} rem [{s}] MATCHED {m}")
	
	print(count)
	
if __name__ == "__main__":
	main()
