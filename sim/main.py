import pygame
import sys
import serial
import time
import math

pygame.init()
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Serial Data Visualization with Mini-Map, Lines, and Grid')

serial_port = serial.Serial(port="/dev/ttyUSB0", baudrate=9600)
time.sleep(1)

scale = 2.0
mini_map_size = 150
square_size = mini_map_size // 3
mini_map_pos = (width - mini_map_size - 10, 10)

grid_cols, grid_rows = 7, 5
cell_size = 40
grid_pos = (10, height - grid_rows * cell_size - 10)

def draw_line(distance, angle, color=(0, 255, 0)):
    distance *= scale
    angle_rad = math.radians(angle + 90)
    posx = int(width // 2 - distance * math.cos(angle_rad))
    posy = int(height // 2 - distance * math.sin(angle_rad))
    pygame.draw.line(screen, color, (width // 2, height // 2), (posx, posy), 6)

def get_color_by_distance(distance):
    if distance < 18:
        return (255, 0, 0)
    elif distance < 40:
        return (255, 255, 0)
    else:
        return (0, 255, 0)

def draw_mini_map(left, front, right, back):
    for row in range(3):
        for col in range(3):
            square_x = mini_map_pos[0] + col * square_size
            square_y = mini_map_pos[1] + row * square_size
            color = (200, 200, 200)
            if row == 0 and col == 1:
                color = get_color_by_distance(front)
            elif row == 1 and col == 0:
                color = get_color_by_distance(left)
            elif row == 1 and col == 2:
                color = get_color_by_distance(right)
            elif row == 2 and col == 1:
                color = get_color_by_distance(back)
            pygame.draw.rect(screen, color, (square_x, square_y, square_size, square_size))

def draw_grid():
    for row in range(grid_rows):
        for col in range(grid_cols):
            cell_x = grid_pos[0] + col * cell_size
            cell_y = grid_pos[1] + row * cell_size
            pygame.draw.rect(screen, (255, 255, 255), (cell_x, cell_y, cell_size, cell_size), 1)

def update_grid_cell(row, col, color):
    if 0 <= row < grid_rows and 0 <= col < grid_cols:
        cell_x = grid_pos[0] + col * cell_size
        cell_y = grid_pos[1] + row * cell_size
        pygame.draw.rect(screen, color, (cell_x + 1, cell_y + 1, cell_size - 2, cell_size - 2))

def draw_text(text, pos, color=(255, 255, 255)):
    font = pygame.font.SysFont('Arial', 20)
    text_surface = font.render(text, True, color)
    screen.blit(text_surface, pos)

try:
    read_buffer = ''
    start_reading = False

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                raise KeyboardInterrupt

        if serial_port.inWaiting() > 0:
            data = serial_port.read().decode('utf-8')
            # print(data)
            if data == '#':
                start_reading = True
                read_buffer = ''
            elif data == '%' and start_reading:
                start_reading = False
                try:
                    left, front, right, back , pidout  , moveLeft , moveRight = map(float, read_buffer.split(','))
                    print("Left: {}, Front: {}, Right: {}, Back: {}".format(left, front, right, back , pidout , moveLeft , moveRight))
                    screen.fill((0, 0, 0))
                    draw_line(left, -90)
                    draw_line(front, 0)
                    draw_line(right, 90)
                    draw_line(back, 180, (255, 0, 0))
                    draw_text(str(pidout), (10, 10))
                    draw_text(str(moveLeft), (10, 30))
                    draw_text(str(moveRight), (10, 50))
                    draw_mini_map(left, front, right, back)
                    draw_grid()
                    update_grid_cell(2, 3, (0, 255, 0))
                    pygame.display.flip()
                except ValueError:
                    print("Invalid data format")
                read_buffer = ''
            elif start_reading:
                read_buffer += data

except KeyboardInterrupt:
    print("Exiting Program")

except Exception as exception_error:
    print("Error occurred. Exiting Program")
    print("Error: " + str(exception_error))

finally:
    serial_port.close()
    pygame.quit()
    sys.exit()
