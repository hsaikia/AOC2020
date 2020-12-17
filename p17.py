# Day 17 - AOC2020
def flatten(a):
    return ":".join(str(x) for x in a)

def deflatten(s):
	return [int(x) for x in s.split(':')] 

def is_active(m, i, j, k):
	if flatten([i, j, k]) in m :
		if m[flatten([i, j, k])] == '#':
			return True
	return False

def p(m, c):
	for z in range(-c, c + 1):
		print(f"z={z}")
		for x in range(-c, c + 1):
			for y in range(-c, c + 1):
				if flatten([x, y, z]) in m :
					print(m[flatten([x, y, z])], end='')
				else:
					print('.', end='')
			print('\n')

def set(m, i, j, k, tmp_m):
	d = [-1, 0, 1]
	count = 0
	for x in d:
		for y in d:
			for z in d:
				if x == 0 and y == 0 and z == 0:
					continue
				else:
					if is_active(m, i + x, j + y, k + z):
						count += 1
	
	print(f"Count for {i},{j},{k} is {count}")

	if is_active(m, i, j, k) and (count < 2 or count > 3) :
		tmp_m[flatten([i, j, k])] = '.'
	elif is_active(m, i, j, k) == False and count == 3 :
		tmp_m[flatten([i, j, k])] = '#'
	
	return tmp_m

def main():
    #file = open("input.txt", "r")
    file = open("sample_input.txt", "r")
    inp = [list(line.strip()) for line in file.readlines() if line.strip()]
    #print(inp)

    m = dict()

    cycles = 1

    for x in range(len(inp)) :
    	for y in range(len(inp[0])) :
    		for z in range(-1, 1):
    			m[flatten([x - 1, y - 1, z])] = inp[x][y]


    p(m, 1)

    tmp_m = {k:v for (k, v) in m.items()}
    for c in range(1, cycles + 1):
    	print(f"After {c} cycles")
    	for k in range(-c, c + 1):
    		for i in range(-c, c + 1):
    			for j in range(-c, c + 1):
    				tmp_m = set(m, i, j, k, tmp_m)
    	# for coordinate in m.keys():
    	# 	[i, j, k] = deflatten(coordinate)
    	# 	tmp_m = set(m, i, j, k, tmp_m)
    	m = {k:v for (k, v) in tmp_m.items()}
    	p(m, c)
    			

    # for z in range(-cycles, cycles + 1):
    # 	print(f"z={z}")
    # 	for x in range(len(inp)) :
    # 		for y in range(len(inp[0])) :
    # 			if flatten([x, y, z]) in m :
    # 				print(m[flatten([x, y, z])])
    # 			else:
    # 				print('.')
    # 		print("\n\n")



if __name__ == "__main__":
    main()