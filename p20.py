# Incomplete! Only Part 1 done

import math

def rev_map(d):
	rd = dict()
	for key, val in d.items():
		for x in val:
			for y in x:
				if y in rd:
					rd[y].append(key)
				else:
					rd[y] = [key]
	return rd

def count_map(rd):
	assoc = dict()
	for v in rd.values():
		if len(v) < 2:
			continue
		assoc = add_to_assoc(v, assoc)
	return assoc

def add_to_assoc(l, assoc):
	for x in l:
		if x not in assoc:
			assoc[x] = set()
		for y in l:
			if x == y:
				continue
			if y not in assoc:
				assoc[y] = set()
			assoc[x].add(y)
			assoc[y].add(x)
	return assoc

def get_neighbors(idx, dim):
	x = idx // dim
	y = idx % dim
	d = [-1, 0, 1]
	ret = []
	for i in d:
		for j in d:
			if i == j or i == -j:
				continue
			nx = x + i
			ny = y + j
			if nx < 0 or nx >= dim:
				continue
			if ny < 0 or ny >= dim:
				continue
			nidx = dim * nx + ny
			ret.append(nidx)
	return ret

def fits(nbs_s, nbs_c):
	for x in nbs_c:
		if x not in nbs_s:
			return False
	return True

def make_full(assoc, mp, dim):
	for idx in range(len(mp)):
		nbs = get_neighbors(idx, dim)
		nbs_c = [mp[x] for x in nbs if x < idx]
		for i in range(idx + 1, len(mp)):
			if len(assoc[mp[i]]) == len(nbs) and fits(assoc[mp[i]], nbs_c):
				tmp = mp[idx]
				mp[idx] = mp[i]
				mp[i] = tmp
				break
	return mp
		
# convert tile to borders
def reduce(tl):
	#print(tl)
	rtl = list(zip(*tl[::-1]))
	#print(rtl)
	a = "".join(tl[0])
	b = "".join(reversed(rtl[-1]))
	c = "".join(reversed(tl[-1]))
	d = "".join(rtl[0])
	r1 = [a, b, c, d]
	r2 = [a[::-1], d[::-1], c[::-1], b[::-1]]
	return r1, r2

def get_neighbors_trbl(idx, mp, dim):
	x = idx // dim
	y = idx % dim
	
	t = None
	r = None
	b = None
	l = None
	
	if x > 0:
		t = mp[(x - 1) * dim + y]
	if y < dim - 1:
		r = mp[x * dim + y + 1]
	if x < dim - 1:
		b = mp[(x + 1) * dim + y]
	if y > 0:
		l = mp[x * dim + y - 1]
		
	return [t, r, b, l]

def arrange(d, fd, mp, dim):
	for idx in range(len(mp)):
		ret = get_neighbors_trbl(idx, mp, dim)
		print(f"Arrangement of Tile {mp[idx]}: {ret}")

def main():
	#file = open("input.txt", "r")
	file = open("S1.txt", "r")
	#file = open("S2.txt", "r")
	#file = open("sample_input.txt", "r")
	fo = open("out.txt", "w")
	inp = [line.strip() for line in file.readlines() if line.strip()]
	fd = dict()
	d = dict()
	tl = []
	old = None
	for x in inp:
		#print(x[0:4])
		if 'Tile' == x[0:4]:
			if old is not None:
				fd[old] = tl
				d[old] = reduce(tl)
				tl = []
			old = int(x[5:-1])
		else:
			tl.append(list(x))
	fd[old] = tl
	d[old] = reduce(tl)
	
	print(d)

	dim = int(math.sqrt(len(d)))
	print(dim)
	rd = rev_map(d)
	assoc = count_map(rd)
	#print(d)
	#print(cd)
	#print(rd)
	#print(assoc)
	
	ans = 1
	
	for k, v in assoc.items():
		if len(v) == 2:
			ans *= k
	print(ans)
	fo.write(str(ans))
	
	# randomly assign
	mp = [k for k in assoc.keys()]
	# assign properly
	mp = make_full(assoc, mp, dim)
	print(mp)
	
	arrange(d, fd, mp, dim)
	
if __name__ == "__main__":
	main()
