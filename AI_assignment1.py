
# # 2.
# basic_salary = float(input("Enter basic salary: "))

# if basic_salary <= 10000:
#     hra = 0.2 * basic_salary
#     da = 0.8 * basic_salary
# elif basic_salary <= 20000:
#     hra = 0.25 * basic_salary
#     da = 0.9 * basic_salary
# else:
#     hra = 0.3 * basic_salary
#     da = 0.95 * basic_salary

# gross_salary = basic_salary + hra + da
# print(f"Gross Salary: {gross_salary:.2f}")


# # 3.

# password = input("Enter a password: ")

# def contains_lowercase(s):
#     for char in s:
#         if 'a' <= char <= 'z':
#             return True
#     return False

# def contains_uppercase(s):
#     for char in s:
#         if 'A' <= char <= 'Z':
#             return True
#     return False

# def contains_digit(s):
#     for char in s:
#         if '0' <= char <= '9':
#             return True
#     return False

# def contains_special_char(s):
#     for char in s:
#         if char in "$#@":
#             return True
#     return False

# if (6 <= len(password) <= 16 and
#     contains_lowercase(password) and
#     contains_uppercase(password) and
#     contains_digit(password) and
#     contains_special_char(password)):
#     print("Password is valid.")
# else:
#     print("Password is invalid.")



# # 4.

# L = [10, 20, 30, 40, 50, 60, 70, 80]
# L += [200, 300]
# L.remove(10)
# L.remove(30)
# L.sort()
# L.sort(reverse=True)
# print("Updated List:", L)

# # 5.

# D = {1: "One", 2: "Two", 3: "Three", 4: "Four", 5: "Five"}
# D[6] = "Six"
# D.pop(2)
# print("Key 6 exists:", 6 in D)
# print("Number of elements:", len(D))
# print("All values:", ' '.join(D.values()))


# # 6.

# numbers = [(i * 7 + 3) % 801 + 100 for i in range(100)]

# odd_numbers = [num for num in numbers if num % 2 != 0]
# even_numbers = [num for num in numbers if num % 2 == 0]

# def is_prime(n):
#     if n < 2:
#         return False
#     for i in range(2, n):
#         if n % i == 0:
#             return False
#     return True

# prime_numbers = [num for num in numbers if is_prime(num)]

# print("Odd Numbers:", odd_numbers)
# print("Even Numbers:", even_numbers)
# print("Prime Numbers:", prime_numbers)


# # 7.

# def compound_interest(principal, rate, time):
#     return principal * (1 + rate / 100) ** time


# principal = float(input("Enter principal amount: "))
# rate = float(input("Enter interest rate: "))
# time = float(input("Enter time: "))


# ci = compound_interest(principal, rate, time)
# print(f"Compound Interest: {ci:.2f}")



# # 8.

# class Restaurant:
#     def __init__(self, restaurant_name, cuisine_type):
#         self.restaurant_name = restaurant_name
#         self.cuisine_type = cuisine_type

#     def describe_restaurant(self):
#         print(f"Restaurant Name: {self.restaurant_name}")
#         print(f"Cuisine Type: {self.cuisine_type}")

#     def open_restaurant(self):
#         print(f"{self.restaurant_name} is now open!")

# restaurant = Restaurant("The Food Place", "Italian")
# print(restaurant.restaurant_name)
# print(restaurant.cuisine_type)
# restaurant.describe_restaurant()
# restaurant.open_restaurant()



# 1.

scores = {
    "Maths": [87, 76, 94, 68, 88, 91, 72, 85, 79, 84],
    "Science": [81, 89, 78, 92, 85, 87, 73, 88, 90, 80],
    "English": [75, 82, 79, 88, 91, 85, 77, 90, 86, 84],
    "IT": [93, 88, 95, 81, 84, 86, 92, 89, 90, 87]
}

def get_stats(scores):
    return max(scores), min(scores), sum(scores) / len(scores)

all_scores = [score for subject_scores in scores.values() for score in subject_scores]

print("Subject-wise Statistics:")
for subject, subject_scores in scores.items():
    high, low, avg = get_stats(subject_scores)
    print(f"{subject}: Highest = {high}, Lowest = {low}, Average = {avg:.2f}")

high, low, avg = get_stats(all_scores)
print("\nOverall Statistics:")
print(f"Highest = {high}, Lowest = {low}, Average = {avg:.2f}")