# BigInt 1024-bit Arithmetic in C

This project implements basic arithmetic operations (addition, subtraction, multiplication) for **1024-bit integers** in C. It allows you to work with very large numbers (up to 309 decimal digits, including sign) that far exceed the limits of standard C integer types.

---

## Features

- **Handles numbers up to 1024 bits (309 decimal digits)**
- **Supports signed numbers** (`+` or `-` at the start)
- **Addition, Subtraction, and Multiplication**
- **User-friendly input and output formatting**
- **Interactive CLI for repeated calculations**

---

## How It Works

- **Numbers are represented as arrays of 9-digit blocks** (base 1,000,000,000) for efficient storage and arithmetic.
- **Sign is handled separately** for correct results on negative numbers.
- **Arithmetic operations** are implemented using helper functions that mimic manual calculation, including carry and borrow handling.

---

## Usage

### 1. Clone the Repository

```bash
git clone https://github.com/Abhiram163/1024-bit-Big-Integer-Arithmetic
cd 1024-bit-Big-Integer-Arithmetic
```

### 2. Compile

```bash
gcc -o bigint main.c
```

### 3. Run

```bash
./bigint
```

### 4. Example Session

```
Enter the first number: +1234567890123456789012345678901234567890
Enter the second number: -999999999999999999999999999999999999999
+1234567890123456789012345678901234567890
-999999999999999999999999999999999999999

Sum: +234567890123456789012345678901234567891
Subtraction: +223456789012345678901234567890123456789
Product: -12345678888888888901111111109888888888987654321098765432109876543210

Would you like to perform another calculation? (y/n): n

Exiting...
```

---

## File Structure

- `main.c` — Main program file containing all logic and functions
- `README.md` — This documentation

---

## Code Structure

- **BigInt struct:** Stores the number as an array and its sign.
- **InitialiseBigInt:** Initializes a BigInt with a given sign.
- **InputBigInt:** Parses a string into a BigInt.
- **PrintBigInt:** Nicely prints a BigInt to the console.
- **AddBigInt, SubBigInt, MultBigInt:** Perform arithmetic operations, handling signs.
- **Helpers:** For addition, subtraction, multiplication, and magnitude comparison.

---

## Limitations

- **No division or modulus operations** (yet).
- **No error checking for invalid input** (e.g., non-digit characters).
- **No support for decimal/fractional numbers.**

---

## Contributing

Pull requests are welcome! If you have suggestions or want to add features (like division, better input validation, or performance improvements), feel free to fork and submit a PR.

---

## License

This project is open source and available under the [MIT License](LICENSE).

---

## Author

- S Revanth

---

## Acknowledgments

- Inspired by the need for high-precision arithmetic in C without external libraries.

---

**Happy Calculating!**

---

> _Feel free to customize the author, repository URL, and add more sections as needed for your GitHub profile!_
