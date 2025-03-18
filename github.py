# 1.1

print("hello world")
print("hello world")
print("hello world")

# 2.1

x = 2
y = 4
z = 4
c = x+y+z
print("Sum of x,y,z = ",c)

x = 2
y = 4
z = 4
print("Sum of x,y,z = ",x+y+z)

# 2.2

x = "Gurnoor"
y= " sandhu"
print("x+y = ",x+y)

i = 5
while i <= 3:
    print(i)
    i = i+1

# 4.1 

a = int(input("Enter the number for table: "))

for i in range(1, 11):
    print(f"{a} * {i} = {a * i}")


print("range(10)        --> ", list(range(10)))
print("range(10,20)     --> ", list(range(10, 20)))
print("range(0,20,2)    --> ", list(range(0, 20, 2)))
print("range(-10,-20,2) --> ", list(range(-10, -20, 2)))
print("range(-10,-20,-2)--> ", list(range(-10, -20, -2)))

# 4.3

s = 0 
n = int(input("Enter the number :"))
for i in range(1,n):
    s=s+i
print("sum of numbers are ",s)


# 5.1
 
a = int(input("Enter the value of a : "))
b = int(input("Enter the value of b : "))
c = int(input("enter the value of c : "))

if a > b and a>c:
          print(a,"is greater")
elif b > a and b>c :
       print(b,"is greater")

else :
        print(c,"is greater")


# 5.2

n = int(input("Enter the value for n : "))
s =0 
for i in range(1,n):
    if i%7 == 0 and i%9 ==0:
        s=s+i 
print("sum = ",s)


# 5.3

n = int(input("Enter a number n: "))
total = 0

for num in range(2, n + 1):
    for i in range(2, num):
        if num % i == 0:
            break
    else:
        total += num

print("The sum of all prime numbers from 1 to", n, "is:", total)
  

# 6.1


def oddnumber(n):
    s = 0
    for i in range(1, n + 1):
        if i % 2 != 0:
            s += i
    return s

n = int(input("Enter the value for n: "))
result = oddnumber(n)
print(f"Sum of odd numbers from 1 to {n}: {result}")

# 6.2

def sum_of_primes(n):
    total = 0
    for num in range(2, n + 1):
        is_prime = True
        for i in range(2, int(num**0.5) + 1):
            if num % i == 0:
                is_prime = False
                break
        if is_prime:
            total += num
    return total

n = int(input("Enter a number n: "))
result = sum_of_primes(n)
print(f"Sum of prime numbers from 1 to {n}: {result}")