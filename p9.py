# Problem 9 - AOC 2020

def find_as_sum(a, n):
  for x in a:
    for y in a:
      if x + y == n:
        return True
  return False

def main():
    #file = open("sample_input.txt", "r")
    #p = 5
    file = open("input.txt", "r")
    p = 25

    a = [int(line.strip()) for line in file.readlines() if line.strip()]

    invalid = [a[i] for i in range(p,len(a)) if find_as_sum(a[i-p:i], a[i]) == False]
    
    # part1
    print(f"Invalid {invalid[0]}")

    # part2
    sums = [x for x in a] #copy
    found = False
    for l in range(2, len(a)):
      for i in range(0, len(a) - l + 1):
        sums[i] += a[i + l - 1]
        if (sums[i] == invalid[0]):
          mi = min(a[i:i+l])
          mx = max(a[i:i+l])
          print(f"Sum {mi + mx}")
          found = True
          break
      if found:
        break;

    
if __name__ == "__main__":
    main()