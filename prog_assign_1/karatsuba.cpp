#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>


void read_numbers(std::string path, std::string& n1, std::string& n2) {
	std::ifstream file(path);
  if (file.is_open()) {
    getline(file, n1);
    getline(file, n2);
    file.close();
  }
  else {
  	std::cout << "Unable to open file." << std::endl;
  }
}

struct Int {
	std::vector<int> digits;
	int size;

	Int(int size) : size(size) { 
		for (int i = 0; i < size; i++) {
			digits.push_back(0);
		}
	}
	~Int() {}

	Int(const Int& that) {
		for (std::size_t i = 0; i < that.length(); ++i) {
			digits.push_back(that.digits[i]);
		}	
		size = that.length();
	}

	void set(long long val) {
		for (std::size_t i = 0; i < digits.size(); ++i) {
			digits[i] = val % 10;
			val /= 10; 
		}
	}

	void print() {
		for (std::size_t i = 0; i < digits.size(); ++i) {
			std::cout << digits[digits.size() - i - 1]; 
		}
		std::cout << "\n";
	}

	friend
	Int add(const Int& x, const Int& y) {	
		Int x_cp(x);
		Int y_cp(y);
		align_length(x_cp, y_cp);

		Int res(x_cp.length() + 1);
		int carry = 0;
		for (std::size_t i = 0; i < x_cp.length(); ++i) {
			int s = x_cp.digits[i] + y_cp.digits[i] + carry;
			int ones = s % 10;
			res.digits[i] = ones;
			carry = int(s / 10);
		}
		res.digits[x_cp.length()] = carry;
		return res;
	}

	friend
	Int sub(const Int& x, const Int& y) {
		// Assume x >= y.
		Int x_cp(x);
		Int y_cp(y);
		align_length(x_cp, y_cp);

		Int res(x_cp.length());
		int carry = 0;
		for (std::size_t i = 0; i < x_cp.length(); ++i) {
			int diff = carry + x_cp.digits[i] - y_cp.digits[i];
			if (diff < 0) { 
				carry = -1;
				diff = 10 + diff;
			} else { 
				carry = 0;
			}
			res.digits[i] = diff;
		}
		return res;
	}

	Int first_half() const {
		std::size_t n = this->length();
		std::size_t len = int(ceil(float(n) / 2));
		Int half(len);
		for (std::size_t i = 0; i < (n - len); ++i) {
			half.digits[i] = digits[len + i];
		}
		return half;
	}

	Int second_half() const {
		std::size_t n = this->length();
		std::size_t len = int(ceil(float(n) / 2));
		Int half(len);
		for (std::size_t i = 0; i < len; ++i) {
			half.digits[i] = digits[i];
		}
		return half;
	}

	Int zero_pad(std::size_t n) {
		for (std::size_t i = 0; i < n; ++i) {
			digits.push_back(0);
		}
		size = digits.size();
		return *this;
	}

	friend
	void align_length(Int& x, Int& y) {
		std::size_t x_len = x.length();
		std::size_t y_len = y.length();
		if (x_len > y_len) { y.zero_pad(x_len - y_len); }
		else { x.zero_pad(y_len - x_len); }
	}

	friend
	void remove_zeros(Int& x, Int& y) {
		// Assume same length.
		std::size_t i = x.length() - 1;
		while (x.digits[i] == 0 && y.digits[i] == 0 && x.length() > 1) {
			x.digits.pop_back();
			y.digits.pop_back();
			x.size--;
			y.size--;
			i--;
		}
	}

	void remove_zeros() {
	std::size_t i = this->length() - 1;
		while (digits[i] == 0 && this->length() > 1) {
			digits.pop_back();
			size--;
			i--;
		}	
	}

	Int shift(std::size_t n) {
		std::size_t len = this->length();
		Int shifted(n + len);		
		for (std::size_t i = 0; i < len; ++i) {
			shifted.digits[n + i] = digits[i];
		}
		return shifted;
	}

	int length() const { return digits.size(); }

};

Int mult(Int& x, Int& y) {
	// Remove insiginificant zeros.
	remove_zeros(x, y);

	std::size_t n = x.length();

	Int prod(2 * n);

	if (n == 1) {
		prod.set(x.digits[0] * y.digits[0]);
		return prod;
	} else {
		// Length a, b, c, d = l.
		Int a = x.first_half();
		Int b = x.second_half();
		Int c = y.first_half();
		Int d = y.second_half();

		// Save length for later.
		std::size_t l = a.length();

		// Length = l + 1 after addition.
		Int p = add(a, b);
		Int q = add(c, d);

		Int ac = mult(a, c); // 2 * (l)
		Int bd = mult(b, d); // 2 * (l)
		Int pq = mult(p, q); // 2 * (l + 1)

		Int adbc = sub(pq, add(ac, bd));

		Int ac_shifted = ac.shift(2 * l);
		Int adbc_shifted = adbc.shift(l);

		prod = add(ac_shifted, adbc_shifted);
		prod = add(prod, bd);
		prod.remove_zeros();

		return prod;
	}
}


int main(int argc, char* argv[]) {

	std::string path = argv[1];

	// First read the numbers to strings.
	std::string x_str, y_str;
	read_numbers(path, x_str, y_str);

	std::cout << x_str << "\n";
	std::cout << y_str << "\n";
	std::cout << y_str.length() << "\n";

	// Assume that both numbers have the same size and it is a power of 2.
	int num_digits = x_str.length();

	Int x(num_digits);
	Int y(num_digits);	
	x.print();
	y.print();

	// Read digits into Int objects.
	for (int i = 0; i < num_digits; ++i) {
		x.digits[i] = x_str[num_digits - i - 1] - 48;
		y.digits[i] = y_str[num_digits - i - 1] - 48;
	}
	x.print();
	y.print();

	Int prod = mult(x, y);
	prod.print();
	std::cout << prod.length() << "\n";

	return 0;
}
