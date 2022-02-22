from random import randint, sample
from time import sleep

from scipy import rand

from generator import replace_str_index

width = 10
height = 10

N, S, E, W = 1, 2, 4, 8
OPPOSITE = {N: S, S: N, E: W, W: E}
MOVE = {N: lambda x, y: (x, y-1),
		S: lambda x, y: (x, y+1),
		E: lambda x, y: (x+1, y),
		W: lambda x, y: (x-1, y)}


def carve_maze():
	random_ways = lambda: sample((N, S, E, W), 4)
	maze = [[0] * width for _ in range(height)]
	walls = [(0, 0, d) for d in random_ways()]

	while walls:
		cx, cy, way = walls.pop()
		nx, ny = MOVE[way](cx, cy)
		if 0 <= ny < height and 0 <= nx < width and maze[ny][nx] == 0:
			maze[cy][cx] |= way
			maze[ny][nx] |= OPPOSITE[way]
			walls += [(nx, ny, d) for d in random_ways()]
			#draw(maze)
			#sleep(0.05)

	return maze


def draw(maze):
	map = []
	map.append('1' * (width * 2 + 1) + "\n")
	for y, row in enumerate(maze):
		line = ['1']
		for x, cell in enumerate(row):
			line.append('0' if cell & S else '0')
			if cell & E:
				line.append('0' if (cell | maze[y][x+1]) & S else '0')
			else:
				line.append('1')
		map.append(''.join(line))
	map.append('1' * (width * 2 + 1))
	for i in range(1, len(map) - 1):
		r = randint(1, len(map[i]) - 2)
		map[i] = replace_str_index(map[i], r, 'C') + "\n"
	x = randint(1, height - 1)
	y = randint(1, width - 1)
	map[x] = replace_str_index(map[x], r, 'E')
	x = randint(1, height - 1)
	y = randint(1, width - 1)
	map[x] = replace_str_index(map[x], r, 'P')
	for el in map:
		file.write(el)


if __name__ == '__main__':
	from sys import argv
	file = open("map/map_g.ber", 'w')
	if len(argv) == 3:
		width, height = map(int, argv[1:])
	# print(carve_maze())
	draw(carve_maze())