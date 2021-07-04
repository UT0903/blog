public class IsLeapYear {
	/**
	 * @param year The year to determine
	 * @return a boolean whether the input year is leap 
	 */
	public static boolean determine(int year){ 
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; 
	}
}
