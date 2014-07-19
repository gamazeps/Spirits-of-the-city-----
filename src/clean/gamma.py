#!/usr/bin/env python
import sys, os

GAMMA = 1.3
planes = 8
maxval = (1 << planes) - 1;

l=[]
l.append(0)
for i in range(255):
    v = pow(float(i+1) / 255.0, GAMMA) * (float(maxval) + 0.5)
    v = int(v)
    if v==0:
        v = 1
    l.append(v)

for i in range(256):
    print "0x%02x"%(l[i]),
    if i < 255:
        if (i&7) == 7:
            print ","
        else:
            print ",",
