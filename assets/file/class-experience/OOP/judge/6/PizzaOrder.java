
public class PizzaOrder extends Pizza{
	private int pizzaNum;
	private Pizza[] pizzas = new Pizza[3];
	public boolean setNumberPizzas(int pizzaNum) {
		if(pizzaNum > 0 && pizzaNum < 4) {
			this.pizzaNum = pizzaNum;
			return true;
		}
		else return false;
	}
	public void setPizza1(Pizza pizza1) {
		this.pizzas[0] = pizza1;
	}
	public void setPizza2(Pizza pizza2) {
		this.pizzas[1] = pizza2;
	}
	public void setPizza3(Pizza pizza3) {
		this.pizzas[2] = pizza3;
	}
	/**
	 * @return the total cost of all the pizzas
	 */
	public double calcTotal() {
		double sum = 0;
		for(int i = 0; i < this.pizzaNum; i++) {
			sum += this.pizzas[i].calcCost();
		}
		return sum;
	}
}
