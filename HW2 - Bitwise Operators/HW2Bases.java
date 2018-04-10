/**
 * CS 2110 Fall 2014 HW2 Part 1 - Coding with bases
 * 
 * @author Yuen Han Chan
 * 
 *         *** NOTE: The rules are different for each java file! ***
 * 
 *         You may not use any of the following: - Any functions found in Java
 *         libraries (especially the Math library) - Example Math.pow,
 *         Integer.bitCount, String.valueOf, etc. - Basically, any function that
 *         does everything for you. The purpose of this homework is to learn how
 *         to do these operations yourself, and the Java API! - The only
 *         exception to this rule is String.charAt to get a character from a
 *         String, and you may use String.length to get the size of the string.
 *         - Any Java 7 feature / standard library function (we will be grading
 *         using Java 6)
 * 
 *         - You my not implement any Java library functions as helpers to use
 *         in other functions.
 * 
 *         - String concatenation with a number for more than one digit. - For
 *         example, "" + 123 is banned. "" + 6 is allowed, though.
 * 
 *         - You may only use 2 conditionals in if-else clauses max per
 *         function. - This means you may have 2 separate conditions, making
 *         this okay:
 * 
 *         if(cond1) { code; } else { moreCode; } if(cond2) { code; } else {
 *         modeCode; }
 * 
 *         - You may not use a switch statement. - No nested for-loops! This is
 *         completely doable with one level of looping. - Recursion is not
 *         allowed. - You may not reuse any function to implement another
 *         function.
 */
public class HW2Bases {
	/**
	 * strdtoi - Decimal String to int
	 * 
	 * Convert a string containing ASCII characters (in decimal) to an int. You
	 * do not have to handle negative numbers. The Strings we will pass in will
	 * be valid decimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strdtoi("123"); // => 123
	 */
	public static int strdtoi(String decimal) {
		int length = decimal.length();
		int answer = 0;
		int current_time = 10; // Base is 10
		for (int end = (length - 2); end >= 0; end--) {
			answer += (current_time * (decimal.charAt(end) - 48));
			current_time *= 10;
		}
		answer += (decimal.charAt(length - 1)) - 48;
		return answer;
	}

	/**
	 * strbtoi - Binary String to int
	 * 
	 * Convert a string containing ASCII characters (in binary) to an int. You
	 * do not have to handle negative numbers. The Strings we will pass in will
	 * be valid binary numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strbtoi("111"); // => 7
	 */
	public static int strbtoi(String binary) {
		int length = binary.length();
		int answer = 0;
		int current_time = 2;
		for (int end = (length - 2); end >= 0; end--) {
			if (binary.charAt(end) == '1') {
				answer += current_time;
			}
			current_time *= 2;
		}
		if (binary.charAt(length - 1) == '1') {
			answer += 1;
		}
		return answer;
	}

	/**
	 * strxtoi - Hexadecimal String to int
	 * 
	 * Convert a string containing ASCII characters (in hex) to an int. You do
	 * not have to handle negative numbers. The Strings we will pass in will be
	 * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strxtoi("A6"); // => 166
	 */
	public static int strxtoi(String hex) {
		int length = hex.length();
		int answer = 0;
		int current_time = 16;
		int current_int;
		for (int end = (length - 2); end >= 0; end--) {
			current_int = hex.charAt(end) - 48; // Return 0 -9
			if (current_int > 16) {
				current_int -= 7; // Return A-F
			}
			answer += current_int * current_time;
			current_time *= 16;
		}
		current_int = hex.charAt(length - 1) - 48;
		if (current_int > 16) {
			current_int -= 7;
		}
		answer += current_int;
		return answer;
	}

	/**
	 * itostrb - int to Binary String
	 * 
	 * Convert a int into a String containing ASCII characters (in binary). You
	 * do not have to handle negative numbers. The String returned should
	 * contain the minimum number of characters necessary to represent the
	 * number that was passed in.
	 * 
	 * Example: itostrb(7); // => "111"
	 */
	public static String itostrb(int binary) {
		String backward_binary = "";
		String frontward_binary = "";
		while (binary / 2 > 0) {
			if (binary % 2 != 0) {
				backward_binary += ("1");
			} else {
				backward_binary += ("0");
			}
			binary /= 2;
		}
		if ((binary % 2) != 0) {
			backward_binary += ("1");
		} else {
			backward_binary += ("0");
		}
		int back_length = backward_binary.length() - 1;
		for (int end = back_length; end >= 0; end--) {
			frontward_binary += backward_binary.charAt(end) - 48;
		}
		return frontward_binary;
	}

	/**
	 * itostrx - int to Hexadecimal String
	 * 
	 * Convert a int into a String containing ASCII characters (in hexadecimal).
	 * You do not have to handle negative numbers. The String returned should
	 * contain the minimum number of characters necessary to represent the
	 * number that was passed in.
	 * 
	 * Example: itostrx(166); // => "A6"
	 */
	public static String itostrx(int hex) {
		String backward_hex = "";
		String frontward_hex = "";
		while (hex / 16 > 0) {
			int remainder = hex - (16 * (hex / 16));
			if (remainder > 9) { // If A-F
				backward_hex += (char) ('A' + (remainder - 10));
			} else {
				backward_hex += remainder;
			}
			hex /= 16;
		}
		if (hex > 9) { // Calculate last digit as it's not cover in while loop
			backward_hex += (char) ('A' + (hex - 10));
		} else {
			backward_hex += hex;
		}
		int back_length = backward_hex.length() - 1;
		for (int end = back_length; end >= 0; end--) {
			frontward_hex += (char) backward_hex.charAt(end);
		}
		return frontward_hex;
	}
}
