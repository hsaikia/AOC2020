# Day 11 - AOC 2020

def flatten(a):
  return "".join("".join(x) for x in a)

def flip1(m, x, y):
  count = 0
  d = [-1, 0, 1]
  for dx in d:
    for dy in d:
      if dx == 0 and dy == 0:
        continue
      nx = x + dx
      ny = y + dy
      if nx >= 0 and ny >= 0 and nx < len(m) and ny < len(m[0]):
        count += m[nx][ny] == '#'

  if count == 0 and m[x][y] == 'L':
    return True

  if count >= 4 and m[x][y] == '#':
    return True

  return False

def flip2(m, x, y):
  count = 0
  d = [-1, 0, 1]
  for dx in d:
    for dy in d:
      if dx == 0 and dy == 0:
        continue
      nx = x
      ny = y
      while True:
        nx += dx
        ny += dy
        if nx >= 0 and ny >= 0 and nx < len(m) and ny < len(m[0]):
          if m[nx][ny] == '.':
            continue
          count += m[nx][ny] == '#'
          break
        break

  if count == 0 and m[x][y] == 'L':
    return True

  if count >= 5 and m[x][y] == '#':
    return True

  return False

def sim(m):
  m_next = [['.' for _ in r] for r in m]
  for i in range(len(m)):
    for j in range(len(m[0])):
      if m[i][j] == '.':
        continue
      
      if flip2(m, i, j):
        m_next[i][j] = 'L' if m[i][j] == '#' else '#'
      else:
        m_next[i][j] = '#' if m[i][j] == '#' else 'L'

  stab = True

  if flatten(m) != flatten(m_next):
    stab = False

  return stab, m_next

def main():
    #file = open("sample_input.txt", "r")    
    file = open("input.txt", "r")
    m = [list(line.strip()) for line in file.readlines() if line.strip()]
    while True:
      stab, m = sim(m)
      if stab :
        break

    ans = flatten(m).count('#')

    print(ans)

    
if __name__ == "__main__":
    main()