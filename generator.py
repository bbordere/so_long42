import random

file = open("map/map_g.ber", 'w')
WIDTH = random.randint(5, 26)
HEIGHT = random.randint(5, 13)

def first_line(width: int) -> str:
	return ("1" * width)

def replace_str_index(text,index=0,replacement=''):
    return '%s%s%s'%(text[:index],replacement,text[index+1:])

map = []
map.append(first_line(WIDTH) + "\n")
for j in range(HEIGHT - 2):
	line = ""
	for i in range(WIDTH - 2):
		r = random.randint(0, 10)
		if (r <= 4):
			line += '0'
		elif (r >= 5 and r <= 8):
			line += '1'
		else:
			line += 'C'
	
	line = "".join(('1', line, '1', '\n'))
	map.append(line)
map.append(first_line(WIDTH))
x = random.randint(2, HEIGHT - 2)
y = random.randint(2, WIDTH - 2)
map[x] = replace_str_index(map[x], y, 'P')

x = random.randint(2, HEIGHT - 2)
y = random.randint(2, WIDTH - 2)
map[x] = replace_str_index(map[x], y, "E")
for l in map:
	file.write(l)
