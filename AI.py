# Simple Python program to solve the sliding puzzle problem

# Puzzle dimensions (3x3 for an 8-puzzle)
n = 3

# Directions for tile movement (down, left, up, right)
rows = [1, 0, -1, 0]
cols = [0, -1, 0, 1]

def is_safe(x, y):
    return 0 <= x < n and 0 <= y < n

def print_matrix(matrix):
    for row in matrix:
        print(" ".join(map(str, row)))
    print()

def calculate_cost(matrix, goal):
    return sum(1 for i in range(n) for j in range(n) if matrix[i][j] and matrix[i][j] != goal[i][j])

def solve_puzzle(start, goal, empty_pos):
    queue = [(calculate_cost(start, goal), 0, start, empty_pos, None)]  # (cost, level, matrix, empty_pos, parent)
    visited = set()

    while queue:
        queue.sort()  # Sort by cost (priority)
        cost, level, matrix, empty_pos, parent = queue.pop(0)

        if tuple(map(tuple, matrix)) in visited:
            continue

        visited.add(tuple(map(tuple, matrix)))

        if cost == 0:  # Puzzle solved
            path = []
            while parent:
                path.append(matrix)
                _, _, matrix, _, parent = parent
            path.append(matrix)
            for step in reversed(path):
                print_matrix(step)
            return

        x, y = empty_pos
        for i in range(4):
            new_x, new_y = x + rows[i], y + cols[i]
            if is_safe(new_x, new_y):
                new_matrix = [row[:] for row in matrix]
                new_matrix[x][y], new_matrix[new_x][new_y] = new_matrix[new_x][new_y], new_matrix[x][y]
                queue.append((calculate_cost(new_matrix, goal), level + 1, new_matrix, (new_x, new_y), (cost, level, matrix, empty_pos, parent)))

# Initial and goal configurations
initial = [[1, 2, 3],
           [8, 0, 4],
           [7, 6, 5]]

goal = [[2, 8, 1],
        [0, 4, 3],
        [7, 6, 5]]

empty_tile_pos = (1, 2)

# Solve the puzzle
solve_puzzle(initial, goal, empty_tile_pos)