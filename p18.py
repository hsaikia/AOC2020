# Day 18 - AOC2020
def flatten(a):
	return ":".join(str(x) for x in a)


def deflatten(s):
	return [int(x) for x in s.split(':')]

def eval(s):
  curr = 0 # curr accumulated result
  last = 0 # last character
  op = 0 # last operator
  curr_num = 0 # current numeral
  for x in s:
    #print(f"X = [{x}] Op = [{op}] Curr [{curr}] Curr_num[{curr_num}]")
    if x.isnumeric():
      last = 0
      #print("X is numeric")
      if last == 0:
        curr_num = curr_num * 10 + int(x)
        #print(f"First num, val {curr_num}")
    else:
      last = 1
      if op == 1:
        curr += curr_num
      elif op == 2:
        curr *= curr_num
      else:
        curr = curr_num
      
      if x == '+':
        op = 1
      else:
        op = 2
      curr_num = 0
  
  if op == 1:
    curr += curr_num
  elif op == 2:
    curr *= curr_num
  else:
    curr = curr_num
  
  #print(f"X = [{x}] Op = [{op}] Curr [{curr}] Curr_num[{curr_num}]")
  return curr

#part 2
def eval_add_first(s):
  
  a = s.find('*')
  if a != -1:
    return eval(list(s[:a])) * eval_add_first(s[a + 1:])
  else:
    return eval(list(s))
  

def eval_b(s):
  if s == "":
    return 0
  a = s.find('(')
  if a != -1:
    b = -1
    for i in range(a + 1, len(s)):
      if s[i] == '(':
        a = i
      if s[i] == ')':
        b = i
        break

    ss = s[a + 1:b]
    #print(f"Evaluating expr [{ss}] ")
    ret_ss = eval_b(ss)
    new_s = s[:a] + str(ret_ss) + s[b + 1:]
    #print(f"New expr [{new_s}]")
    return eval_b(new_s)
    #return 0
  else:
    #return eval(list(s))
    return eval_add_first(s)
  

def main():
	file = open("input.txt", "r")
	#file = open("sample_input.txt", "r")
	inp = [line.strip().replace(" ", "") for line in file.readlines() if line.strip()]
	
	ans = 0
	for expr in inp:
	  print(f"Expr [{expr}]")
	  ret = eval_b(expr)
	  ans += ret
	  print(ret)
	  
	print(ans)

if __name__ == "__main__":
	main()
