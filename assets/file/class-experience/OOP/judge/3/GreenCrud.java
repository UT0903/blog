public class GreenCrud {
	/**
	 * @author b07902048
	 * @param init The size start in the Fibonacci sequence
	 * @param days The frequency that bacterium grow
	 * @return The num of bacterium at the [days]
	 */
	public int calPopulation(int init, int days) {
		int[] x;
		x = new int[101]; // new an array to store the Fibonacci sequence
		x[0] = 0;x[1] = init;
		for(int i = 0; i < days / 5; i++) {
			x[i+2] = x[i+1] + x[i];
		}
		return x[days/5+1];
	}
}
