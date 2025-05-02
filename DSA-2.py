S1 = set()
n = int(input("Enter number of elements you want to enter in the set: "))
print("Enter the elements:")
for i in range(n):
    ele = int(input())
    S1.add(ele)

while True:
    print("\nCurrent Set:", S1)
    print("\nMENU")
    print("1. Add element in set")
    print("2. Delete element from set")
    print("3. Size of the set")
    print("4. Search an element in set")
    print("5. Union of sets")
    print("6. Intersection of sets")
    print("7. Difference of sets")
    print("8. Check if subset")
    print("9. Exit")

    ch = int(input("Enter the choice (operation on set): "))

    if ch == 1:
        ele = int(input("Enter the element you want to add in the set: "))
        S1.add(ele)
        print("Element added.")

    elif ch == 2:
        ele = int(input("Enter the element you want to remove from the set: "))
        if ele in S1:
            S1.remove(ele)
            print("Element removed.")
        else:
            print("Element not found in the set.")

    elif ch == 3:
        print("Size of the set is:", len(S1))

    elif ch == 4:
        ele = int(input("Enter the element you want to search in the set: "))
        if ele in S1:
            print(f"Set contains the element {ele}")
        else:
            print("Set does not contain the element")

    elif ch == 5:
        S2 = set()
        n = int(input("Enter number of elements for the second set: "))
        print("Enter the elements:")
        for i in range(n):
            ele = int(input())
            S2.add(ele)
        U = S1.union(S2)
        print("Union of sets is:", U)

    elif ch == 6:
        S2 = set()
        n = int(input("Enter number of elements for the second set: "))
        print("Enter the elements:")
        for i in range(n):
            ele = int(input())
            S2.add(ele)
        I = S1.intersection(S2)
        print("Intersection of sets is:", I)

    elif ch == 7:
        S2 = set()
        n = int(input("Enter number of elements for the second set: "))
        print("Enter the elements:")
        for i in range(n):
            ele = int(input())
            S2.add(ele)
        D = S1.difference(S2)
        print("Difference of sets is:", D)

    elif ch == 8:
        S2 = set()
        n = int(input("Enter number of elements for the second set: "))
        print("Enter the elements:")
        for i in range(n):
            ele = int(input())
            S2.add(ele)
        if S2.issubset(S1):
            print("S2 is a subset of S1")
        else:
            print("S2 is not a subset of S1")

    elif ch == 9:
        print("Exiting program.")
        break

    else:
        print("INVALID CHOICE. Try again.")


