#ifndef big_integer_h
#define big_integer_h

#include <iostream>
#include <string>
using namespace std;
class Big_Integer
{
protected:
	int sign;
	string nums;
public:
	Big_Integer()
	{
		this->sign = 0;
		this->nums = "";
	}
	Big_Integer(string num)
	{
		if (num[0] == '-')
		{
			num.erase(num.begin());
			while (num[0] == '0')
			{
				num.erase(num.begin());
			}
			if (num == "")
			{
				this->sign = 0;
				num = "0";
			}
			else
			{
				this->sign = -1;
			}
		}
		else
		{
			while (num[0] == '0')
			{
				num.erase(num.begin());
			}
			if (num == "")
			{
				this->sign = 0;
				num = "0";
			}
			else
			{
				this->sign = 1;
			}
		}
		this->nums = num;
	}
public:
	void setSign(int sign)
	{
		this->sign = sign;
	}
	void setNums(string nums)
	{
		this->nums = nums;
	}
	int getSign()
	{
		return this->sign;
	}
	string getNums()
	{
		return this->nums;
	}
	friend istream& operator>> (istream& is, Big_Integer& num)
	{
		string s;
		is >> s;
		num = Big_Integer(s);
		return is;
	}
	friend ostream& operator<< (ostream& out, Big_Integer num)
	{
		if (num.getSign() == 0)
		{
			out << "0";
			return out;
		}
		while (num.getNums()[0] == '0')
		{
			string s = num.getNums();
			s.erase(s.begin());
			num.setNums(s);
		}
		if (num.getSign() == 1)
		{
			out << num.getNums();
			return out;
		}
		else
		{
			out << "-";
			out << num.getNums();
			return out;
		}
	}
	void operator= (Big_Integer number)
	{
		this->sign = number.sign;
		this->nums = number.nums;
	}
	friend bool operator== (Big_Integer nums1, Big_Integer nums2)
	{
		return nums1.sign == nums2.sign && nums1.nums == nums2.nums;
	}
	friend bool operator> (Big_Integer nums1, Big_Integer nums2)
	{
		if (nums1.sign > nums2.sign)
		{
			return true;
		}
		if (nums1.sign < nums2.sign)
		{
			return false;
		}
		if (nums1.sign == 0)
		{
			return false;
		}
		if (nums1.sign == 1)
		{
			return (nums1.nums.length() > nums2.nums.length() ? true : (nums1.nums.length() < nums2.nums.length() ? false : nums1.nums > nums2.nums));
		}
		return (nums1.nums.length() < nums2.nums.length() ? true : (nums1.nums.length() > nums2.nums.length() ? false : nums1.nums < nums2.nums));
	}
	friend bool operator>= (Big_Integer nums1, Big_Integer nums2)
	{
		return (nums1 > nums2 || nums1 == nums2);
	}
	friend bool operator< (Big_Integer nums1, Big_Integer nums2)
	{
		if (nums1.sign < nums2.sign)
		{
			return true;
		}
		if (nums1.sign > nums2.sign)
		{
			return false;
		}
		if (nums1.sign == 0)
		{
			return false;
		}
		if (nums1.sign == 1)
		{
			return (nums1.nums.length() < nums2.nums.length() ? true : (nums1.nums.length() > nums2.nums.length() ? false : nums1.nums < nums2.nums));
		}
		return (nums1.nums.length() > nums2.nums.length() ? true : (nums1.nums.length() < nums2.nums.length() ? false : nums1.nums > nums2.nums));
	}
	friend bool operator<= (Big_Integer nums1, Big_Integer nums2)
	{
		return (nums1 < nums2 || nums1 == nums2);
	}
	Big_Integer opposite(Big_Integer)
	{
		this->sign = -sign;
		return *this;
	}
	friend bool operator!= (Big_Integer nums1, Big_Integer nums2)
	{
		return (nums1.getSign() == nums2.getSign() ? (nums1.getNums() != nums2.getNums() ? true : false) : true);
	}
public:
	static Big_Integer add(Big_Integer nums1, Big_Integer nums2)
	{
		Big_Integer result;
		if (nums1.getNums() == "0")
		{
			return nums2;
		}
		if (nums2.getNums() == "0")
		{
			return nums1;
		}
		if (nums1.getNums().length() < nums2.getNums().length())
		{
			while (nums1.getNums().length() < nums2.getNums().length())
			{
				nums1.setNums('0' + nums1.getNums());
			}
		}
		else if (nums1.getNums().length() > nums2.getNums().length())
		{
			while (nums2.getNums().length() < nums1.getNums().length())
			{
				nums2.setNums('0' + nums2.getNums());
			}
		}
		int carry = 0;
		for (unsigned int i = nums1.getNums().length() - 1; i > 0; i--)
		{
			result.setNums(to_string(((nums1.getNums()[i] - '0') + (nums2.getNums()[i] - '0') + carry) % 10) + result.getNums());
			carry = ((nums1.getNums()[i] - '0') + (nums2.getNums()[i] - '0') + carry) / 10;
		}
		result.setNums(to_string(((nums1.getNums()[0] - '0') + (nums2.getNums()[0] - '0') + carry) % 10) + result.getNums());
		carry = ((nums1.getNums()[0] - '0') + (nums2.getNums()[0] - '0') + carry) / 10;
		if (carry > 0)
		{
			result.setNums(to_string(carry) + result.getNums());
		}
		result.setSign(nums1.getSign());
		return result;
	}
	static Big_Integer subtract(Big_Integer nums1, Big_Integer nums2)
	{
		Big_Integer result;
		if (nums1 == nums2)
		{
			result.setNums("0");
			return result;
		}
		if (nums1 < nums2)
		{
			result = subtract(nums2, nums1);
			result.setSign(-1);
			return result;
		}
		if (nums2.getNums() == "0")
		{
			return nums1;
		}
		if (nums1.getNums().length() > nums2.getNums().length())
		{
			while (nums2.getNums().length() < nums1.getNums().length())
			{
				nums2.setNums('0' + nums2.getNums());
			}
		}
		int borrow = 0;
		for (int i = nums1.getNums().length() - 1; i >= 0; i--)
		{
			int res = 0;
			if ((nums2.getNums()[i] - '0') + borrow == 10)
			{
				result.setNums(nums1.getNums()[i] + result.getNums());
				borrow = 1;
			}
			else
			{
				if (nums1.getNums()[i] - '0' >= nums2.getNums()[i] - '0' + borrow)
				{
					result.setNums(to_string(((nums1.getNums()[i] - '0') - (nums2.getNums()[i] - '0') - borrow)) + result.getNums());
					borrow = 0;
				}
				else
				{
					result.setNums(to_string((10 + (nums1.getNums()[i] - '0') - (nums2.getNums()[i] - '0') - borrow)) + result.getNums());
					borrow = 1;
				}
			}
		}
		string s = result.getNums();
		while (s[0] == '0')
		{
			s.erase(s.begin());
		}
		result.setNums(s);
		result.setSign(1);
		return result;
	}
	friend Big_Integer operator+ (Big_Integer nums1, Big_Integer nums2)
	{
		Big_Integer result;
		if (nums1.getSign() == 0)
		{
			result = nums2;
		}
		else if (nums2.getSign() == 0)
		{
			result = nums1;
		}
		else
		{
			if (nums1.getSign() == nums2.getSign())
			{
				result = add(nums1, nums2);
			}
			if (nums1.getSign() == 1 && nums2.getSign() == -1)
			{
				nums2.setSign(1);
				result = subtract(nums1, nums2);
				nums2.setSign(-1);
			}
			if (nums1.getSign() == -1 && nums2.getSign() == 1)
			{
				nums1.setSign(1);
				result = subtract(nums1, nums2);
				nums1.setSign(-1);
				result.setSign(-result.getSign());
			}
		}
		return result;
	}
	friend Big_Integer operator- (Big_Integer nums1, Big_Integer nums2)
	{
		Big_Integer result;
		if (nums1.getSign() == 0)
		{
			result = nums2;
			result.setSign(-nums2.getSign());
			return result;
		}
		if (nums2.getSign() == 0)
		{
			result = nums1;
			return result;
		}
		if (nums1.getSign() == nums2.getSign())
		{
			if (nums1.getSign() == 1)
			{
				result = subtract(nums1, nums2);
				return result;
			}
			else
			{
				nums2.setSign(1);
				result = nums1 + nums2;
				nums2.setSign(-1);
				return result;
			}
		}
		else
		{
			if (nums1.getSign() == 1)
			{
				nums2.setSign(1);
				result = nums1 + nums2;
				nums2.setSign(-1);
				return result;
			}
			else
			{
				nums2.setSign(-1);
				result = nums1 + nums2;
				nums2.setSign(1);
				return result;
			}
		}
	}
	friend Big_Integer operator* (Big_Integer nums1, Big_Integer nums2)
	{
		Big_Integer result;
		if (nums1.getNums() == "0" || nums2.getNums() == "0")
		{
			result.setNums("0");
			return result;
		}
		result.setSign(1);
		int index = 0;
		for (int i = nums2.getNums().length() - 1; i >= 0; i--)
		{
			int k = 0;
			Big_Integer product;
			product.setSign(1);
			int carry = 0;
			for (int j = nums1.getNums().length() - 1; j > 0; j--)
			{
				product.setNums(to_string(((nums1.getNums()[j] - '0') * (nums2.getNums()[i] - '0') + carry) % 10) + product.getNums());
				carry = ((nums1.getNums()[j] - '0') * (nums2.getNums()[i] - '0') + carry) / 10;
			}
			product.setNums(to_string(((nums1.getNums()[0] - '0') * (nums2.getNums()[i] - '0') + carry) % 10) + product.getNums());
			carry = ((nums1.getNums()[0] - '0') * (nums2.getNums()[i] - '0') + carry) / 10;
			if (carry > 0)
			{
				product.setNums(to_string(carry) + product.getNums());
			}
			while (k < index)
			{
				product.setNums(product.getNums() + '0');
				k++;
			}
			index++;
			result = result + product;
		}
		result.setSign(nums1.getSign() * nums2.getSign());
		return result;
	}
	friend Big_Integer operator/ (Big_Integer nums1, Big_Integer nums2)
	{
		if (nums2.getNums() == "0")
		{
			throw runtime_error("Divide by zero");
		}
		else if (nums1.getNums() == "0")
		{
			Big_Integer result;
			result.setNums("0");
			return result;
		}
		else
		{
			Big_Integer divided, result;
			Big_Integer unit("1");
			Big_Integer tenth("10");
			if (nums1.getNums().length() < nums2.getNums().length())
			{
				result.setNums("0");
				return result;
			}
			else
			{
				result.setSign(nums1.getSign() * nums2.getSign());
				int a = nums1.getSign();
				int b = nums2.getSign();
				nums1.setSign(1);
				nums2.setSign(1);
				string s = nums1.getNums().substr(0, nums2.getNums().length());
				divided.setNums(s);
				divided.setSign(1);
				unsigned int i;
				if (divided < nums2)
				{
					divided.setNums(divided.getNums() + nums1.getNums()[nums2.getNums().length()]);
					i = nums2.getNums().length();
				}
				else
				{
					i = nums2.getNums().length() - 1;
				}
				while (i != nums1.getNums().length())
				{
					Big_Integer ans;
					ans.setNums("0");
					ans.setSign(0);
					while (ans * nums2 <= divided)
					{
						ans = ans + unit;
					}
					ans = ans - unit;
					result.setNums(result.getNums() + ans.getNums());
					divided = divided - ans * nums2;
					i++;
					if (i < nums1.getNums().length())
					{
						string digits = "";
						digits += nums1.getNums()[i];
						Big_Integer digit(digits);
						divided = tenth * divided + digit;
					}
				}
				nums1.setSign(a);
				nums2.setSign(b);
				return result;
			}
		}
	}
	friend Big_Integer operator% (Big_Integer nums1, Big_Integer nums2)
	{
		if (nums2.getNums() == "0")
		{
			throw runtime_error("Divide by zero");
		}
		return nums1 - (nums1 / nums2) * nums2;
	}

	friend Big_Integer Factorial(Big_Integer nums)
	{
		Big_Integer unit("1");
		Big_Integer i("1");
		Big_Integer result("1");
		while (i <= nums)
		{
			result = result * i;
			i = i + unit;
		}
		return result;
	}
	friend Big_Integer pow(Big_Integer nums1, Big_Integer nums2)
	{
		if (nums2.getNums() == "0")
		{
			return Big_Integer("1");
		}
		else
		{
			if (nums2 % Big_Integer("2") == Big_Integer("0"))
			{
				return pow(nums1, nums2 / Big_Integer("2")) * pow(nums1, nums2 / Big_Integer("2"));
			}
			return nums1 * pow(nums1, (nums2 - Big_Integer("1")) / Big_Integer("2")) * pow(nums1, (nums2 - Big_Integer("1")) / Big_Integer("2"));
		}
	}
	Big_Integer operator++()
	{
		*this = *this + Big_Integer("1");
		return *this;
	}
	Big_Integer operator++(int)
	{
		Big_Integer temp = *this;
		++* this;
		return temp;
	}
	Big_Integer operator--()
	{
		*this = *this - Big_Integer("1");
		return *this;
	}
	Big_Integer operator--(int)
	{
		Big_Integer temp = *this;
		--* this;
		return temp;
	}
	Big_Integer& operator+= (Big_Integer other)
	{
		*this = *this + other;
		return *this;
	}
	Big_Integer& operator-= (Big_Integer other)
	{
		*this = *this - other;
		return *this;
	}
	Big_Integer& operator*= (Big_Integer other)
	{
		*this = *this * other;
		return *this;
	}
	Big_Integer& operator/= (Big_Integer other)
	{
		*this = *this / other;
		return *this;
	}
	Big_Integer& operator%= (Big_Integer other)
	{
		*this = *this % other;
		return *this;
	}
};
#endif

