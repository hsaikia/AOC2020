def main():
    file = open("input.txt", "r")
    inp = [line.split(',') for line in file.readlines() if line.strip()]
    nums = [int(x) for x in inp[0]]
    num_map = dict((y, x + 1) for x, y in enumerate(nums[:-1]))
    # We start from the last
    # number on the list
    num = nums[-1]
    # current turn
    turn = len(nums)
    # part 1
    num_turns = 2020
    # part 2
    # num_turns = 30000000
    while turn < num_turns :
      if num not in num_map.keys():
        # number appearing for the first time
        # next will be 0
        num_map[num] = turn
        num = 0
      else:
        # number appearing again
        # next = now_idx - last_idx
        num_map[num], num = turn, turn - num_map[num]
      turn += 1
    print(f"Turn {turn} Ans {num}")
if __name__ == "__main__":
    main()