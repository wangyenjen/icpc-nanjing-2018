#!/usr/bin/env python3

def generate(s, t):
    for i in range(len(s)):
        for j in range(i + 1, len(s) + 1):
            for k in range(1, min(j - i, len(t) + 1)):
                x = s[i:j] + t[:k]
                if x == x[::-1]:
                    yield i, j, k

s = input()
t = input()
print(sum(1 for _ in generate(s, t)))
