# from collections import *
# from functools import lru_cache
# import heapq
# import itertools
# import math
# import random
# import sys

import re


def flatten(a):
    return "".join("".join(x) for x in a)

def add_to_all(l, b):
  new_l = []
  for x in l:
    y = x + b
    new_l.append(y)
  return new_l

def copy_01(l):
  new_l = []
  for x in l:
    y0 = x + '0'
    y1 = x + '1'
    new_l.append(y0)
    new_l.append(y1)

  return new_l


def main():
    #file = open("sample_input.txt", "r")
    file = open("input.txt", "r")
    m = [line.strip() for line in file.readlines() if line.strip()]

    mask = ""
    d = dict()

    for i in range(len(m)):
      a = m[i].split()
      if a[0] == 'mask':
        mask = a[2]
      else:
        pos_str = re.sub(']', '', a[0])
        pos = int(pos_str[4:])
        val = int(a[2])
        new_val = ['']

        for j in range(len(mask)):
          bit = pos % 2
          pos >>= 1
          if mask[len(mask) - j - 1] == '1':
            new_val = add_to_all(new_val, '1')
          elif mask[len(mask) - j - 1] == '0':
            new_val = add_to_all(new_val, str(bit))
          else:
            new_val = copy_01(new_val)
            
        for x in new_val:
          d[int(x[::-1], 2)] = val
    s = 0
    for k, v in d.items():
      s += v

    print(s)


if __name__ == "__main__":
    main()
