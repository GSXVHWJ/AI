import heapq
import numpy as np

def get_neighbors(state):
    """Returns a list of possible moves from the current state."""
    neighbors = []
    blank = state.index(0)  # Find the empty tile (0)
    row, col = blank // 3, blank % 3
    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # Up, Down, Left, Right
    for dr, dc in moves:
        new_row, new_col = row + dr, col + dc
        if 0 <= new_row < 3 and 0 <= new_col < 3:
            new_blank = new_row * 3 + new_col
            new_state = list(state)
            new_state[blank], new_state[new_blank] = new_state[new_blank], new_state[blank]
            neighbors.append(tuple(new_state))
    return neighbors

def misplaced_tiles(state, goal):
    """Heuristic function: Number of misplaced tiles."""
    return sum(1 for i in range(9) if state[i] != goal[i] and state[i] != 0)

def correctly_placed_tiles(state, goal):
    """Heuristic function: Number of correctly placed tiles."""
    return sum(1 for i in range(9) if state[i] == goal[i])

def print_puzzle(state):
    """Prints the puzzle state in a readable format."""
    for i in range(0, 9, 3):
        print(" ".join(str(x) if x != 0 else "_" for x in state[i:i+3]))
    print("\n")

def best_first_search(initial, goal):
    """Best First Search using misplaced tiles heuristic."""
    pq = []
    heapq.heappush(pq, (misplaced_tiles(initial, goal), initial, []))
    visited = set()
    while pq:
        _, state, path = heapq.heappop(pq)
        print_puzzle(state)
        if state == goal:
            return path + [state]
        visited.add(state)
        for neighbor in get_neighbors(state):
            if neighbor not in visited:
                heapq.heappush(pq, (misplaced_tiles(neighbor, goal), neighbor, path + [state]))
    return None

def hill_climbing(initial, goal):
    """Hill Climbing algorithm using misplaced tiles heuristic."""
    state = initial
    path = [state]
    while state != goal:
        print_puzzle(state)
        neighbors = get_neighbors(state)
        best_neighbor = min(neighbors, key=lambda x: misplaced_tiles(x, goal))
        if misplaced_tiles(best_neighbor, goal) >= misplaced_tiles(state, goal):
            break  # Stop if no better neighbor is found
        state = best_neighbor
        path.append(state)
    return path

def a_star_search(initial, goal):
    """A* Search algorithm using correctly placed tiles heuristic."""
    pq = []
    heapq.heappush(pq, (0, initial, []))
    visited = set()
    while pq:
        cost, state, path = heapq.heappop(pq)
        print_puzzle(state)
        if state == goal:
            return path + [state]
        visited.add(state)
        for neighbor in get_neighbors(state):
            if neighbor not in visited:
                g = len(path) + 1  # Path cost
                h = correctly_placed_tiles(neighbor, goal)
                heapq.heappush(pq, (g - h, neighbor, path + [state]))
    return None

# Example Usage
initial_state = (1, 2, 3, 4, 0, 5, 6, 7, 8)
goal_state = (1, 2, 3, 4, 5, 6, 7, 8, 0)

print("Best First Search Solution:")
best_first_search(initial_state, goal_state)

print("Hill Climbing Solution:")
hill_climbing(initial_state, goal_state)

print("A* Search Solution:")
a_star_search(initial_state, goal_state)
