S1 = set()
n = int(input("Enter number of elements you want to enter in the set: "))
print("Enter the elements:")
for i in range(n):
    ele = int(input())
    S1.add(ele)

print("Elements in the set are:")
print(S1)

print("\nMENU")
print("1. Add element in set")
print("2. Delete element from set")
print("3. Size of the set")
print("4. Search an element in set")
print("5. Union of sets")
print("6. Intersection of sets")
print("7. Difference of sets")
print("8. Check if subset")
ch = int(input("Enter the choice (operation on set): "))

if ch == 1:
    ele = int(input("Enter the element you want to add in the set: "))
    S1.add(ele)
    print("Now elements in the set are:")
    print(S1)

elif ch == 2:
    ele = int(input("Enter the element you want to remove from the set: "))
    S1.remove(ele)
    print("Now elements in the set are:")
    print(S1)

elif ch == 3:
    print("Size of the set is:", len(S1))

elif ch == 4:
    ele = int(input("Enter the element you want to search in the set: "))
    if ele in S1:
        print("Set contains the element")
    else:
        print("Set does not contain the element")

elif ch == 5:
    print("Enter elements for another set:")
    S2 = set()
    n = int(input("Enter number of elements for the second set: "))
    print("Enter the elements:")
    for i in range(n):
        ele = int(input())
        S2.add(ele)

    print("Elements in the second set are:")
    print(S2)

    U = S1.union(S2)
    print("Union of sets is:")
    print(U)

elif ch == 6:
    print("Enter elements for another set:")
    S2 = set()
    n = int(input("Enter number of elements for the second set: "))
    print("Enter the elements:")
    for i in range(n):
        ele = int(input())
        S2.add(ele)

    print("Elements in the first set are:")
    print(S1)
    print("Elements in the second set are:")
    print(S2)

    I = S1.intersection(S2)
    print("Intersection of sets is:")
    print(I)

elif ch == 7:
    print("Enter elements for another set:")
    S2 = set()
    n = int(input("Enter number of elements for the second set: "))
    print("Enter the elements:")
    for i in range(n):
        ele = int(input())
        S2.add(ele)

    print("Elements in the first set are:")
    print(S1)
    print("Elements in the second set are:")
    print(S2)

    D = S1.difference(S2)
    print("Difference of sets is:")
    print(D)

elif ch == 8:
    print("Enter elements for another set:")
    S2 = set()
    n = int(input("Enter number of elements for the second set: "))
    print("Enter the elements:")
    for i in range(n):
        ele = int(input())
        S2.add(ele)

    print("Elements in the first set are:")
    print(S1)
    print("Elements in the second set are:")
    print(S2)

    if S2.issubset(S1):
        print("S2 is a subset of S1")
    else:
        print("S2 is not a subset of S1")

else:
    print("INVALID CHOICE")


# OUTPUT:
Enter no of element you want to enter in a set:4
Enter the elements:
2
3
5
1
Elements in the set are:
{1, 2, 3, 5}
MENU
1.Add element in set
2.Delete element from set
3.Size of the set
4.Search an element in set
5.Union of sets
6.Intersection of set is:
7.Difference of both is
8.Subset of set
Enter the choice(operation on set):1
Enter the element you want to add in the set:4
Now elements in the set are:
{1, 2, 3, 4, 5}
Enter no of element you want to enter in a set:4
Enter the elements:
12
13
14
25
Elements in the set are:
{25, 12, 13, 14}

MENU
1.Add element in set
2.Delete element from set
3.Size of the set
4.Search an element in set
5.Union of sets
6.Intersection of set is:
7.Difference of both is
8.Subset of set
Enter the choice(operation on set):2
Enter the element you want to remove from set:14
Now elements in the set are:
{25, 12, 13}
Enter the number of elements you want to add to the set: 3
Enter the elements:
5
10
15
Elements in the set are: {10, 5, 15}
MENU
Enter your choice (operation on set): 3
Size of the set: 3
Enter your choice (operation on set): 4
Enter the element you want to search in the set: 10
Element is in the set.
Enter your choice (operation on set): 5
Enter the number of elements for the second set: 3
Enter the elements:
20
25
5

Second set: {25, 20, 5}
Union of sets: {5, 10, 15, 20, 25}
Enter your choice (operation on set): 6
Enter the number of elements for the second set: 3
Enter the elements:
5
10
50
Second set: {10, 50, 5}
Intersection of sets: {10, 5}
Enter your choice (operation on set): 7
Enter the number of elements for the second set: 3
Enter the elements:
5
20
15
Second set: {20, 5, 15}
Difference of sets (S1 - S2): {10}
Enter your choice (operation on set): 8
Enter the number of elements for the second set: 3
Enter the elements:
5
20
25
Second set: {25, 20, 5}
S2 is not a subset of S1.
