/**
 * CS 2110 Fall 2014 HW2 Part 3 - Coding a bit vector
 * 
 * @author Yuen Han Chan
 * 
 *         *** NOTE: The rules are different for each java file! ***
 * 
 *         This class represents a bit vector, which is 32 bits which can be
 *         manipulated through the use of the methods that this class provides.
 * 
 *         The only things you are allowed to use in your code are the
 *         following: - The bitwise operators |, &, ~, ^, <<, >> - Increment and
 *         Decrement (++ and --). - You may also add or subtract 1 from a
 *         number, but it must be only 1. - Boolean operators ||, &&, and !,
 *         which are only allowed in if-statements. - Conditional statements:
 *         if, if-else, switch-case, ? : - However, you may only handle up to
 *         two cases or conditionals. This means ternaries, too! - Equality
 *         comparisons (==, !=, <=, >=, <, >). - String concatenation (+), ONLY
 *         in the toString method. - Iteration may be used for the onesCount,
 *         zerosCount, size, toString methods. - The assignment operator (of
 *         course).
 * 
 *         You are not allowed to use anything not mentioned above. This
 *         includes the following, but is not an exhaustive list: -
 *         Multiplication or Division - Addition or Subtraction with numbers
 *         other than 1. - Iteration in functions other than toString. - The
 *         unsigned right shift operator >>> (C does not provide this operator).
 *         - Modulus (%). - Any functions found in Java libraries (especially
 *         the Math library). - Example: Math.pow, Integer.bitCount, etc. -
 *         Casting (you should not have cast anywhere!) - Recursion, reuse of
 *         other functions, or helper functions.
 */
public class HW2BitVector {
	/**
	 * 32-bit data initialized to all zeros. Here is what you will be using to
	 * represent the Bit Vector. Do not change its scope from private.
	 */
	private int bits;

	/** You may not add any more fields to this class other than the given one. */

	/**
	 * Sets the bit (sets to 1) pointed to by index.
	 * 
	 * @param index
	 *            index of which bit to set. 0 for the least significant bit
	 *            (right most bit). 31 for the most significant bit.
	 */
	public void set(int index) {
		bits = bits | (0x1 << index);
	}

	/**
	 * Clears the bit (sets to 0) pointed to by index.
	 * 
	 * @param index
	 *            index of which bit to set. 0 for the least significant bit
	 *            (right most bit). 31 for the most significant bit.
	 */
	public void clear(int index) {
		bits = bits & (~(0x1 << index));
	}

	/**
	 * Toggles the bit (sets to the opposite of its current value) pointed to by
	 * index.
	 * 
	 * @param index
	 *            index of which bit to set. 0 for the least significant bit
	 *            (right most bit). 31 for the most significant bit.
	 */
	public void toggle(int index) {
		bits = bits ^ (0x1 << index);
	}

	/**
	 * Returns true if the bit pointed to by index is currently set.
	 * 
	 * @param index
	 *            index of which bit to check. 0 for the least significant bit
	 *            (right-most bit). 31 for the most significant bit.
	 * @return true if the bit is set, false if the bit is clear. If the index
	 *         is out of range (index >= 32), then return false.
	 */
	public boolean isSet(int index) {
		if (index >= 32) {
			return false;
		}
		int first_phrase = (0x1 << index);
		bits = first_phrase & bits;
		return (bits >> index) == 1;
	}

	/**
	 * Returns true if the bit pointed to by index is currently clear.
	 * 
	 * @param index
	 *            index of which bit to check. 0 for the least significant bit
	 *            (right-most bit). 31 for the most significant bit.
	 * @return true if the bit is clear, false if the bit is set. If the index
	 *         is out of range (index >= 32), then return true.
	 */
	public boolean isClear(int index) {
		if (index >= 32) {
			return true;
		}
		int first_phrase = (0x1 << index);
		bits = first_phrase & bits;
		return (bits >> index) == 0;
	}

	/**
	 * Returns a string representation of this object. Return a string with the
	 * binary representation of the bit vector. You may use String concatenation
	 * (+) here. You must return a 32-bit string representation. i.e if the bits
	 * field was 2, then return "00000000000000000000000000000010"
	 */
	public String toString() {
		String ans = "";
		int shift = 31;
		while (shift != 0) {
			if ((bits & (0x1 << shift)) == 0) {
				ans += "0";
			} else {
				ans += "1";
			}
			shift--;
		}
		if ((bits & 0x1) == 0) {
			ans += "0";
		} else {
			ans += "1";
		}
		return ans;
	}

	/**
	 * Returns the number of bits currently set (=1) in this bit vector. You may
	 * obviously use the ++ operator to increment your counter.
	 */
	public int onesCount() {
		int count = 0;
		int shift = 31;
		while (shift != 0) {
			if ((bits & (0x1 << shift)) != 0) {
				count++;
			}
			shift--;
		}
		if ((bits & 0x1) != 0) {
			count++;
		}
		return count;
	}

	/**
	 * Returns the number of bits currently clear (=0) in this bit vector. You
	 * may obviously use the ++ operator to increment your counter.
	 */
	public int zerosCount() {
		int count = 0;
		int shift = 31;
		while (shift != 0) {
			if ((bits & (0x1 << shift)) == 0) {
				count++;
			}
			shift--;
		}
		if ((bits & 0x1) == 0) {
			count++;
		}
		return count;
	}

	/**
	 * Returns the "size" of this BitVector. The size of this bit vector is
	 * defined to be the minimum number of bits that will represent all of the
	 * ones. For example, the size of the bit vector 00010000 will be 5.
	 */
	public int size() {
		int count = 32;
		int shift = 31;
		while (((bits & (0x1 << shift)) == 0) && (count>=0)) {
			shift--;
			count--;
		}
		if(bits==0){
			return 1;
		}
		return count;
	}
}