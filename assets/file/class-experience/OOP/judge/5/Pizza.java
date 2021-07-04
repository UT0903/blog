
public class Pizza{
	private String size;
	private int cheese, pepperoni, ham;
	public Pizza(){
		this.size = "small";
		this.cheese = 1;
		this.pepperoni = 1;
		this.ham = 1;
	}
	public String getSize() {
		return size;
	}
	public void setSize(String size) {
		this.size = size;
	}
	public int getNumberOfCheese() {
		return cheese;
	}
	public void setNumberOfCheese(int cheese) {
		this.cheese = cheese;
	}
	public int getNumberOfPepperoni() {
		return pepperoni;
	}
	public void setNumberOfPepperoni(int pepperoni) {
		this.pepperoni = pepperoni;
	}
	public int getNumberOfHam() {
		return ham;
	}
	public void setNumberOfHam(int ham) {
		this.ham = ham;
	}
	public Pizza(String size, int cheese, int pepperoni, int ham){
		this.size = size;
		this.cheese = cheese;
		this.pepperoni = pepperoni;
		this.ham = ham;
	}
	/**
	 * @return the total cost of the pizza
	 */
	public Double calcCost() {
		int cost;
		if(this.size.equals("small")) cost = 10;
		else if(this.size.equals("large")) cost = 14;
		else cost = 12;
		return Double.valueOf(cost + (this.cheese + this.ham + this.pepperoni) * 2);
	}
	/**
	 * @param pizza Compare with the object whether two pizza are the same
	 * @return True rep. the same False on the contary
	 */
	public boolean equals(Pizza pizza) {
		return this.cheese == pizza.cheese && this.pepperoni == pizza.pepperoni && this.ham == pizza.ham && this.size.equals(pizza.size); 
	}
	/**
	 * @return the formal info of the pizza(String type)
	 */
	public String toString() {
		return String.format("size = %s, numOfCheese = %d, numOfPepperoni = %d, numOfHam = %d", this.size, this.cheese, this.pepperoni, this.ham);
	}
	
}
