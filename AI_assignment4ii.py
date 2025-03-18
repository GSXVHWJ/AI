import heapq
from copy import deepcopy

class PuzzleState:
    def __init__(self, board, parent=None, move=None, depth=0):
        self.board = board
        self.parent = parent
        self.move = move
        self.depth = depth
        
    def __eq__(self, other):
        return self.board == other.board
    
    def __lt__(self, other):
        return False
        
    def get_blank_pos(self):
        for i in range(3):
            for j in range(3):
                if self.board[i][j] == 0:
                    return i, j
                    
    def get_possible_moves(self):
        moves = []
        i, j = self.get_blank_pos()
        
        # Check all possible moves (up, down, left, right)
        for di, dj in [(-1,0), (1,0), (0,-1), (0,1)]:
            new_i, new_j = i + di, j + dj
            if 0 <= new_i < 3 and 0 <= new_j < 3:
                moves.append((new_i, new_j))
        return moves
        
    def get_new_state(self, move):
        new_board = deepcopy(self.board)
        i, j = self.get_blank_pos()
        new_i, new_j = move
        
        # Swap the blank tile with the target position
        new_board[i][j], new_board[new_i][new_j] = new_board[new_i][new_j], new_board[i][j]
        return PuzzleState(new_board, self, move, self.depth + 1)

def misplaced_tiles(current, goal):
    """Heuristic function: number of misplaced tiles"""
    count = 0
    for i in range(3):
        for j in range(3):
            if current.board[i][j] != goal.board[i][j] and current.board[i][j] != 0:
                count += 1
    return count

def correctly_placed_tiles(current, goal):
    """Heuristic function: number of correctly placed tiles"""
    count = 0
    for i in range(3):
        for j in range(3):
            if current.board[i][j] == goal.board[i][j] and current.board[i][j] != 0:
                count += 1
    return count

def print_solution(state):
    """Print the solution path"""
    path = []
    current = state
    while current:
        path.append(current)
        current = current.parent
    
    print(f"\nSolution found in {len(path)-1} moves:")
    for state in reversed(path):
        for row in state.board:
            print(row)
        print()

def best_first_search(initial_state, goal_state):
    """Implementation of Best First Search algorithm"""
    frontier = [(misplaced_tiles(initial_state, goal_state), initial_state)]
    explored = set()
    
    while frontier:
        _, current_state = heapq.heappop(frontier)
        current_board_tuple = tuple(map(tuple, current_state.board))
        
        if current_state == goal_state:
            return current_state
            
        if current_board_tuple in explored:
            continue
            
        explored.add(current_board_tuple)
        
        for move in current_state.get_possible_moves():
            new_state = current_state.get_new_state(move)
            new_board_tuple = tuple(map(tuple, new_state.board))
            
            if new_board_tuple not in explored:
                heapq.heappush(frontier, (misplaced_tiles(new_state, goal_state), new_state))
    
    return None

def hill_climbing(initial_state, goal_state):
    """Implementation of Hill Climbing algorithm"""
    current_state = initial_state
    
    while True:
        neighbors = []
        for move in current_state.get_possible_moves():
            new_state = current_state.get_new_state(move)
            neighbors.append((misplaced_tiles(new_state, goal_state), new_state))
        
        if not neighbors:
            return None
            
        best_neighbor = min(neighbors, key=lambda x: x[0])
        
        if best_neighbor[0] >= misplaced_tiles(current_state, goal_state):
            return current_state
            
        current_state = best_neighbor[1]

def a_star(initial_state, goal_state):
    """Implementation of A* algorithm"""
    frontier = [(correctly_placed_tiles(initial_state, goal_state) + initial_state.depth, initial_state)]
    explored = set()
    
    while frontier:
        _, current_state = heapq.heappop(frontier)
        current_board_tuple = tuple(map(tuple, current_state.board))
        
        if current_state == goal_state:
            return current_state
            
        if current_board_tuple in explored:
            continue
            
        explored.add(current_board_tuple)
        
        for move in current_state.get_possible_moves():
            new_state = current_state.get_new_state(move)
            new_board_tuple = tuple(map(tuple, new_state.board))
            
            if new_board_tuple not in explored:
                f_score = correctly_placed_tiles(new_state, goal_state) + new_state.depth
                heapq.heappush(frontier, (f_score, new_state))
    
    return None

# Example usage
if __name__ == "__main__":
    # Example initial and goal states
    initial_board = [
        [2, 8, 3],
        [1, 6, 4],
        [7, 0, 5]
    ]
    
    goal_board = [
        [1, 2, 3],
        [8, 0, 4],
        [7, 6, 5]
    ]
    
    initial_state = PuzzleState(initial_board)
    goal_state = PuzzleState(goal_board)
    
    # Solve using Best First Search
    print("Solving using Best First Search:")
    solution = best_first_search(initial_state, goal_state)
    if solution:
        print_solution(solution)
    else:
        print("No solution found!")
    
    # Solve using Hill Climbing
    print("\nSolving using Hill Climbing:")
    solution = hill_climbing(initial_state, goal_state)
    if solution:
        print_solution(solution)
    else:
        print("No solution found!")
    
    # Solve using A*
    print("\nSolving using A*:")
    solution = a_star(initial_state, goal_state)
    if solution:
        print_solution(solution)
    else:
        print("No solution found!")