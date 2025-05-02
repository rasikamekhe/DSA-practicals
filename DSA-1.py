def Hash(value, n):
    return value % n

def linear_probing_insert(H, value, n):
    index = Hash(value, n)
    i = 0
    while H[(index + i) % n] != -1 and i < n:
        i += 1
    if i == n:
        print("Linear probing failed: Table full")
    else:
        H[(index + i) % n] = value
        print(f"Inserted phone number {value} at index {(index + i) % n}")

def search_linear_probing(H, value, n):
    index = Hash(value, n)
    i = 0
    while H[(index + i) % n] != value and H[(index + i) % n] != -1 and i < n:
        i += 1
    if H[(index + i) % n] == value:
        print(f"Found phone number {value} at index {(index + i) % n} with {i + 1} comparisons.")
    else:
        print("Phone number not found!")

def delete_linear_probing(H, value, n):
    index = Hash(value, n)
    i = 0
    while H[(index + i) % n] != value and H[(index + i) % n] != -1 and i < n:
        i += 1
    if H[(index + i) % n] == value:
        H[(index + i) % n] = -1
        print(f"Deleted phone number {value} from index {(index + i) % n}")
    else:
        print("Phone number not found!")

def quadratic_probing_insert(H, value, n):
    index = Hash(value, n)
    i = 0
    while i < n and H[(index + i * i) % n] != -1:
        i += 1
    if i == n:
        print("Quadratic probing failed: Table full")
    else:
        H[(index + i * i) % n] = value
        print(f"Inserted phone number {value} at index {(index + i * i) % n}")

def search_quadratic_probing(H, value, n):
    index = Hash(value, n)
    i = 0
    while i < n and H[(index + i * i) % n] != value and H[(index + i * i) % n] != -1:
        i += 1
    if H[(index + i * i) % n] == value:
        print(f"Found phone number {value} at index {(index + i * i) % n} with {i + 1} comparisons.")
    else:
        print("Phone number not found!")

def delete_quadratic_probing(H, value, n):
    index = Hash(value, n)
    i = 0
    while i < n and H[(index + i * i) % n] != value and H[(index + i * i) % n] != -1:
        i += 1
    if H[(index + i * i) % n] == value:
        H[(index + i * i) % n] = -1
        print(f"Deleted phone number {value} from index {(index + i * i) % n}")
    else:
        print("Phone number not found!")

def display(H, label):
    print(f"\nHash Table ({label} Probing):")
    for i in range(len(H)):
        print(f"{i} -> {H[i] if H[i] != -1 else 'empty'}")

# --- Main Execution Loop ---
n = int(input("Enter the size of the telephone book (hash table size): "))
H1 = [-1] * n  # Linear Probing Table
H2 = [-1] * n  # Quadratic Probing Table

while True:
    print("\n___TELEPHONE BOOK MENU___")
    print("1. Insert phone number using Linear Probing")
    print("2. Search phone number using Linear Probing")
    print("3. Delete phone number using Linear Probing")
    print("4. Insert phone number using Quadratic Probing")
    print("5. Search phone number using Quadratic Probing")
    print("6. Delete phone number using Quadratic Probing")
    print("7. Display both hash tables")
    print("8. Exit")
    
    choice = int(input("Enter your choice: "))

    if choice == 1:
        x = int(input("Enter phone number to insert: "))
        linear_probing_insert(H1, x, n)
    elif choice == 2:
        x = int(input("Enter phone number to search: "))
        search_linear_probing(H1, x, n)
    elif choice == 3:
        x = int(input("Enter phone number to delete: "))
        delete_linear_probing(H1, x, n)
    elif choice == 4:
        x = int(input("Enter phone number to insert: "))
        quadratic_probing_insert(H2, x, n)
    elif choice == 5:
        x = int(input("Enter phone number to search: "))
        search_quadratic_probing(H2, x, n)
    elif choice == 6:
        x = int(input("Enter phone number to delete: "))
        delete_quadratic_probing(H2, x, n)
    elif choice == 7:
        display(H1, "Linear")
        display(H2, "Quadratic")
    elif choice == 8:
        print("Exiting Telephone Book System.")
        break
    else:
        print("Invalid choice. Please try again.")
