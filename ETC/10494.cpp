#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

class BigInt
{
    friend std::ostream& operator<<(std::ostream& out, const BigInt& number);
	friend std::istream& operator>>(std::istream& inp, BigInt& number);
	friend BigInt operator+(const BigInt& a, const BigInt& b);
    friend BigInt operator-(const BigInt& a, const BigInt& b);
    friend BigInt operator*(const BigInt& a, const BigInt& b);
    friend BigInt operator/(const BigInt& a, const BigInt& b);
	friend BigInt operator%(const BigInt& a, const BigInt& b);
	friend int comparison(const BigInt& a, const BigInt& b);
	
    private:
    public:
	BigInt(const string& number = "0");
	deque<int> digits;
	
};
BigInt::BigInt(const string& number){
	int l = number.size();
	for(int i = 0; i < l; ++i){
		char ch = number[i];
		digits.push_back(ch - '0');
	}
	
}

BigInt operator+(const BigInt& a, const BigInt& b){
	BigInt result;
	result.digits.erase(result.digits.begin());
	
	int i = a.digits.size() - 1;
	int j = b.digits.size() - 1;
	int carry = 0;

	while (i > -1 or j > -1 or carry != 0) {
		int sum = carry;
		if (i > -1) {
			sum += a.digits[i];
			--i;
		}
		if (j > -1) {
			sum += b.digits[j];
			--j;
		}
		carry = sum / 10;
		int d = sum % 10;
		result.digits.push_front(d);
	}

	return result;
}
BigInt operator-(const BigInt& a, const BigInt& b){
	BigInt result;
	result.digits.erase(result.digits.begin());
	
	int i = a.digits.size() - 1;
	int j = b.digits.size() - 1;
	int carry = 0;
	while (i > -1 || j > -1) {
		int sum = carry;
		carry = 0;
		if (i > -1) {
			sum += a.digits[i];
			--i;
		}
		if (j > -1) {
			sum -= b.digits[j];
			--j;
		}
		int d = 0;
		if (sum < 0) {
			d = 10 + sum;
			carry = -1;
		} else {
			d = sum;
		}
		result.digits.push_front(d);
	}
	for (int k = result.digits.size(); k > 0; --k) {
			if (result.digits[0] == 0 and result.digits.size() > 1)
				result.digits.pop_front();
			
		}
	return result;
}

BigInt operator*(const BigInt& a, const BigInt& b){
	BigInt result;
	result.digits.erase(result.digits.begin());
	
	int i = a.digits.size() - 1;
	int j = b.digits.size() - 1;
	int k = j;
	while (j > -1) {
		BigInt smthg;
		smthg.digits.erase(smthg.digits.begin());
		int carry = 0;
		while (i > -1 || carry != 0) {
			int sum = carry;
			if (i > -1) {
				sum += a.digits[i] * b.digits[j];
				--i;
			}
			carry = sum / 10;
			int d = sum % 10;
			smthg.digits.push_front(d);
		}
		if (j < k) {
			for (int s = j; s < k; ++s) {
				smthg.digits.push_back(0);
			}
		}
		--j;
		result = result + smthg;
		i = a.digits.size() - 1;
	}
	return result;
}
int comparison(const BigInt& a, const BigInt& b) {
	int i = a.digits.size() - 1;
	int j = b.digits.size() - 1;
	if (i > j)
		return 1;
	if (i < j)
		return -1;
	for (int k = 0; k <= i; ++k) {
		if (a.digits[k] < b.digits[k]) {
			return -1;
		}
		if (a.digits[k] > b.digits[k]) {
			return 1;
		}
	}
	return 0;
}
BigInt operator/(const BigInt& a, const BigInt& b){
	BigInt result;
	result.digits.erase(result.digits.begin());
	int comp = comparison(a,b);
	int i = a.digits.size() - 1;
	if(comp == -1) result.digits.push_back(0);
	else if(comp == 0) result.digits.push_back(1);
	else{
		BigInt tmp;	
		for(int k = 0; k <= i; ++k) {
			int carry = 0;
			if(k != 0) tmp = tmp * BigInt("10");
			tmp = tmp + BigInt(to_string(a.digits[k]));
			while(comparison(tmp, b) >= 0){
				tmp = tmp - b;
				++carry;
			}
			result.digits.push_back(carry);
		}
    }
	for (int k = result.digits.size(); k > 0; --k) {
			if (result.digits[0] == 0 and result.digits.size() > 1)
				result.digits.pop_front();
			
	}
	return result;
}

BigInt operator%(const BigInt& a, const BigInt& b){
	return a - b*(a/b);
}
istream& operator>>(istream& inp, BigInt& number)
{
	string num;
	if(inp >> num){
		BigInt t(num);
		number = t;
	}
	return inp >> skipws;
}

ostream& operator<<(ostream& out,const BigInt& number)
{
	int l = number.digits.size();
	for(int i = 0; i < l; ++i){
		out << number.digits[i];
	}
	return out;
}

int main(){	
	string line;
	BigInt a;
	BigInt b;
	char op;
	while(getline(cin, line)){
		istringstream sinp(line);
		sinp >> a >> op >> b;
		BigInt c;
		switch(op){
			case '/':
				c = a / b;
				cout << c << endl;
				break;
			case '%':
				c = a % b;
				cout << c << endl;
				break;
			
		}
	}
	cout << endl;
	return 0;
}