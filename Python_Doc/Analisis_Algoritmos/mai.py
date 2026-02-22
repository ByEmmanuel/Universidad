import pygame as pg
import numpy as np
from collections import deque


class MapaNode:
    def __init__(self, position, parent=None):
        self.parent = parent
        self.position = position

    def __eq__(self, other):
        return self.position == other.position


class BreadthSearch(object):
    def run(self, mapa, start, end):
        startNode = MapaNode(start[::-1])
        endNode = MapaNode(end[::-1])

        path = []
        cola = deque([startNode])

        mapaRows, mapaCols = mapa.shape
        visited = np.zeros(mapa.shape)
        visited[startNode.position[0]][startNode.position[1]] = 1

        found = False

        while cola:
            currentNode = cola.popleft()

            if currentNode == endNode:
                found = True
                break

            movements = [[0, -1], [-1, 0], [1, 0], [0, 1]]

            for movement in movements:
                newPosition = [
                    currentNode.position[0] + movement[0],
                    currentNode.position[1] + movement[1]
                ]

                if (newPosition[0] < 0 or newPosition[1] < 0 or
                        newPosition[0] >= mapaRows or newPosition[1] >= mapaCols):
                    continue

                if visited[newPosition[0]][newPosition[1]] == 1:
                    continue

                if mapa[newPosition[0]][newPosition[1]] == 0:
                    continue

                adjacentNode = MapaNode(newPosition, currentNode)
                cola.append(adjacentNode)
                visited[newPosition[0]][newPosition[1]] = 1

        if found:
            temp = currentNode
            while temp is not None:
                path.append(temp.position)
                temp = temp.parent

        return path, visited


pg.init()

mapaAlg = np.load('mapaProfundidad.npy')
height, width = mapaAlg.shape


# ===============================
# OBSTACLES TO FORCE LONG ROUTE
# ===============================

# Vertical wall
for i in range(5, height - 5):
    mapaAlg[i][25] = 0

# Horizontal wall
for j in range(25, width - 5):
    mapaAlg[height - 15][j] = 0

# Corridor openings
mapaAlg[height - 15][25] = 1
mapaAlg[10][25] = 1


BLACK = pg.Color('black')
WHITE = pg.Color('white')
GREEN = pg.Color('green')
RED = pg.Color('red')
BLUE = pg.Color('blue')

color_light = (170, 170, 170)
color_dark = (100, 100, 100)

smallfont = pg.font.SysFont('verdana', 17)
text = smallfont.render('BFS Search', True, RED)

tile_size = 15
topPadding = 50

start = [13, 25]
goal = [43, 46]

search = BreadthSearch()
screen = pg.display.set_mode((width * tile_size, height * tile_size + topPadding))
clock = pg.time.Clock()

background = pg.Surface((width * tile_size, height * tile_size))
buttons = pg.Surface((width * tile_size, topPadding))

for y in range(height):
    for x in range(width):
        rect = (x * tile_size, y * tile_size, tile_size, tile_size)

        if mapaAlg[y, x] == 0:
            color = BLACK
        else:
            color = WHITE

        if x == start[0] and y == start[1]:
            color = GREEN

        if x == goal[0] and y == goal[1]:
            color = RED

        pg.draw.rect(background, color, rect)


game_exit = False
while not game_exit:
    mouse = pg.mouse.get_pos()

    for event in pg.event.get():
        if event.type == pg.QUIT:
            game_exit = True

        if event.type == pg.MOUSEBUTTONDOWN:
            if 10 <= mouse[0] <= 150 and 10 <= mouse[1] <= 40:
                camino, _ = search.run(mapaAlg, start, goal)

                for point in camino:
                    rect = (
                        point[1] * tile_size,
                        point[0] * tile_size,
                        tile_size,
                        tile_size
                    )
                    pg.draw.rect(background, BLUE, rect)

    if 10 <= mouse[0] <= 150 and 10 <= mouse[1] <= 40:
        pg.draw.rect(buttons, color_light, [10, 10, 140, 30])
    else:
        pg.draw.rect(buttons, color_dark, [10, 10, 140, 30])

    screen.fill((0, 0, 0))
    screen.blit(buttons, (0, 0))
    screen.blit(background, (0, 50))
    screen.blit(text, (10, 12))

    pg.display.flip()
    clock.tick(30)

pg.quit()