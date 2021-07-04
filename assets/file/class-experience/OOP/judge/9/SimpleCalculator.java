public class SimpleCalculator {
	private char operator;
	private double value;
	private double result;
	private int count;
	private boolean isEnded;

	public void calResult(String cmd) throws UnknownCmdException {
		String[] cmdArr;
		cmdArr = cmd.split(" ");
		//Check cmd length
		if(cmdArr.length != 2)
			throw new UnknownCmdException("Please enter 1 operator and 1 value separated by 1 space");
		boolean operatorValid = true;
		boolean valueValid = true;
		//check if operator is valid
		if (cmdArr[0].length() > 1 || !(cmdArr[0].charAt(0) == '+' || 
			cmdArr[0].charAt(0) == '-' || cmdArr[0].charAt(0) == '*' ||
			cmdArr[0].charAt(0) == '/')) {
			operatorValid = false;
		}
		else {
			operator = cmdArr[0].charAt(0);
		}
		//check if value is valid
		try {
			value = Double.parseDouble(cmdArr[1]);
		} catch (NumberFormatException e) {
			valueValid = false;
		}
		// error handling
		if(!operatorValid && !valueValid) {
			throw new UnknownCmdException("" + cmdArr[0] +
				" is an unknown operator and " + cmdArr[1] + " is an unknown value");
		}
		else if(!operatorValid) {
			throw new UnknownCmdException(cmdArr[0] + " is an unknown operator");
		}
		else if(!valueValid){
			throw new UnknownCmdException(cmdArr[1] + " is an unknown value");	
		}
		//check if devided by zero
		if(operator == '/' && value == 0)
			throw new UnknownCmdException("Can not divide by 0");

		switch (operator) {
		case '+':
			result += value;
			break;
		case '-':
			result -= value;
			break;
		case '*':
			result *= value;
			break;
		case '/':
			result /= value;
			break;
		}
		count++;
	}
	/*
	 * different count number will lead to different result
	 */
	public String getMsg() {
		String resultStr = String.format("%.2f", this.result);
		String valueStr = String.format("%.2f", this.value);
		if (isEnded)
			return ("Final result = " + resultStr);
		if (count == 0)
			return ("Calculator is on. Result = " + resultStr);
		else if (count == 1)
			return ("Result " + operator + " " + valueStr + " = " +
					resultStr + ". " + "New result = " + resultStr);
		else
			return ("Result " + operator + " " + valueStr + " = " +
					resultStr + ". " + "Updated result = " + resultStr);
	}
	//handle the end of calculating
	public boolean endCalc(String cmd) {
		if (cmd.length() == 1 && (cmd.equals("R") || cmd.equals("r"))) {
			isEnded = true;
			return true;
		} else
			return false;
	}
}