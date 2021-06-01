#!/usr/bin/env python3

from svgelements import *
import re

regex = re.compile('cx="(.*?)".*?cy="(.*?)".*?r="(.*?)"')
group_coords = []

with open('a250001_all_tweaked.svg', 'r') as svg, open('circles.txt', 'w') as coords:
    for line_num, line in enumerate(svg):
        if line[:5] == "<path":
            x1, y1, x2, y2 = Path(line.split('"')[1]).bbox()
            cx, cy = (x1 + x2) / 2, (y1 + y2) / 2
            r = (abs(x2 - x1) + abs(y2 - y1)) / 4
            print(f'<circle cx="{cx:.4f}" cy="{cy:.4f}" r="{r:.4f}"/>')
        else:
            line_pos = line_num % 6
            if line_pos < 2: continue
            cx, cy, r = map(float, regex.search(line.strip()).groups())
            group_coords.append([cx, cy, r])

            if line_pos == 5:
                print(group_coords)
                group_coords = []

            #coords.write(', '.join(line.split('"')[1::2])
                #+ ('}},\n{{' if line_pos == 5 else '}, {'))
