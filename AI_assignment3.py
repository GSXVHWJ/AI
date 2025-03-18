# def dfs(state, goal, visited):
#     if state == goal:
#         return [state]
    
#     visited.add(tuple(map(tuple, state)))

#     for move in get_moves(state):
#         if tuple(map(tuple, move)) not in visited:
#             result = dfs(move, goal, visited)
#             if result:
#                 return [state] + result
#     return None

# def get_moves(state):
    
#     return []

# initial_state = [['C'], ['C', 'B'], ['A', 'B', 'A']]
# goal_state = [['A', 'B', 'C'], [], []]

# visited = set()
# solution = dfs(initial_state, goal_state, visited)

# print("Solution:", solution if solution else "No solution found")








# from collections import deque

# def breadth_first_search(initial_state, goal_state):
#     queue = deque([(initial_state, [])])  # Store state and path

#     visited = {tuple(initial_state.items())}  # Keep track of visited states

#     while queue:
#         current_state, path = queue.popleft()

#         if is_goal_state(current_state, goal_state):
#             return path

#         for action in get_possible_actions(current_state):
#             next_state = apply_action(current_state, action)
#             if tuple(next_state.items()) not in visited:
#                 visited.add(tuple(next_state.items()))
#                 queue.append((next_state, path + [action]))  # Add action to the path

#     return None  # No solution found



# def depth_limited_search(initial_state, goal_state, depth_limit):
#     stack = [(initial_state, [], 0)]  # Store state, path, and depth

#     while stack:
#         current_state, path, depth = stack.pop()

#         if is_goal_state(current_state, goal_state):
#             return path

#         if depth < depth_limit:
#             for action in get_possible_actions(current_state):
#                 next_state = apply_action(current_state, action)
#                 stack.append((next_state, path + [action], depth + 1))

#     return None  # No solution found within the depth limit


# def iterative_deepening_search(initial_state, goal_state):
#     depth = 0
#     while True:
#         result = depth_limited_search(initial_state, goal_state, depth)
#         if result:
#             return result, depth  # Return path and depth at which solution is found
#         depth += 1



#         initial_state = {
#     'A': 'table',
#     'B': 'table',
#     'C': 'A' 
# }

# goal_state = {
#     'A': 'table',
#     'B': 'table',
#     'C': 'table'
# }

# path = depth_first_search(initial_state, goal_state)
# print("DFS Path:", path)

# path = breadth_first_search(initial_state, goal_state)
# print("BFS Path:", path)

# path = depth_limited_search(initial_state, goal_state, 1)
# print("DLS (depth=1) Path:", path)

# path, depth = iterative_deepening_search(initial_state, goal_state)
# print("IDS Path:", path)
# print("Solution found at depth:", depth)


def is_goal_state(state, goal_state):
    return state == goal_state

def get_possible_actions(state):
    actions = []
    for block, on in state.items():
        if on != 'table':
            for other_block, other_on in state.items():
                if block != other_block and other_on != block:  # Prevent moving onto itself
                    actions.append((block, other_block))
            actions.append((block, 'table'))
    return actions

def apply_action(state, action):
    block, to = action
    new_state = state.copy()
    for b, on in new_state.items():
        if on == block:
            new_state[b] = new_state[block]
    new_state[block] = to
    return new_state

def depth_first_search(initial_state, goal_state):
    stack = [(initial_state, [])]
    visited = {tuple(initial_state.items())}  # Keep track of visited states

    while stack:
        current_state, path = stack.pop()

        if is_goal_state(current_state, goal_state):
            return path

        for action in get_possible_actions(current_state):
            next_state = apply_action(current_state, action)
            if tuple(next_state.items()) not in visited:
                visited.add(tuple(next_state.items()))
                stack.append((next_state, path + [action]))

    return None

from collections import deque

def breadth_first_search(initial_state, goal_state):
    queue = deque([(initial_state, [])])
    visited = {tuple(initial_state.items())}

    while queue:
        current_state, path = queue.popleft()

        if is_goal_state(current_state, goal_state):
            return path

        for action in get_possible_actions(current_state):
            next_state = apply_action(current_state, action)
            if tuple(next_state.items()) not in visited:
                visited.add(tuple(next_state.items()))
                queue.append((next_state, path + [action]))

    return None

def depth_limited_search(initial_state, goal_state, depth_limit):
    stack = [(initial_state, [], 0)]

    while stack:
        current_state, path, depth = stack.pop()

        if is_goal_state(current_state, goal_state):
            return path

        if depth < depth_limit:
            for action in get_possible_actions(current_state):
                next_state = apply_action(current_state, action)
                stack.append((next_state, path + [action], depth + 1))

    return None

def iterative_deepening_search(initial_state, goal_state):
    depth = 0
    while True:
        result = depth_limited_search(initial_state, goal_state, depth)
        if result:
            return result, depth
        depth += 1